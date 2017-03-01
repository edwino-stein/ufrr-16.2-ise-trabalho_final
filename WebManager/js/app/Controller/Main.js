App.define('Controller.Main',{

    storageUrl: "storage.json",

    firmwareApiUrls: {
        's' : 'getstatus.php',
        'o' : 'override.php',
        'r' : 'updaterfid.php',
        't' : 'settime.php'
    },

    petInfoView: 'View.PetInfo',
    foodMeasurerView: 'View.FoodMeasurer',
    setTimerFormView: 'View.SetTimerForm',
    ajax: 'Util.Ajax',

    $overrideBtn: '#override',
    $rfidChangeBtn: '#rfid-change',

    foodPercentage: 0,
    timer: 0,
    timeLeft: 0,
    data:{},

    autoUpdateEnabled: true,
    autoUpdateHandle: null,
    updateTime: 10000,

    Timer: {

        time: 0,
        handle: null,
        callback: null,

        onTimeOut: function(){

            var me = this;
            me.time--;
            me.callback(me.time);

            if(me.time <= 0){
                me.stop();
                return;
            }

            var me = this;
            this.handle = setTimeout(function(){
                me.onTimeOut();
            }, 1000);
        },

        start: function(time, callback){

            if(this.handle !== null) return;

            var me = this;
            this.time = time;
            this.callback = callback;

            this.handle = setTimeout(function(){
                me.onTimeOut();
            }, 1000);
        },

        stop: function(){
            if(this.handle === null) return;
            this.time = 0;
            clearTimeout(this.handle);
            this.handle = null;
        },

        updateTime: function(newTime){
            this.time = newTime;
        },

        isRunning: function(){
            return this.handle !== null;
        }
    },

    onOverriderBtnClick: function(e){
        this.$overrideBtn.prop("disabled", true);
        this.sendMessage('o');
    },

    onRfidChangeBtnClick: function(e){
        this.$rfidChangeBtn.prop("disabled", true);
        this.sendMessage('r');
    },

    onSetTimeSubmit: function(data){
        this.setTimerFormView.disable(true);
        this.sendMessage('t', data);
        this.timer = data.t * 1000 * 60 * (data.u === 'hour' ? 60 : 1);
    },

    onDataLoaded: function(data){
        this.data = data;
        if(this.data.currentUid !== ''){
            this.updatePetInfo(this.data.currentUid);
        }
    },

    sendMessage: function(message, data){

        var me = this;
        var url = me.firmwareApiUrls[message];

        if(typeof(url) !== 'string') return false;
        data = typeof(data) === 'object' ? data : null;

        me.ajax.request({
            url: url,
            data: data,
            fail: function(){
                console.log("Fail sendMessage");
                me.onResponseReceives(message, null, false);
            },
            success: function(data, response){
                me.onResponseReceives(message, data, true);
            }
        });
    },

    onResponseReceives: function(message, data, success){
        switch (message) {
            case 's':
                if(success) this.onStatusUpdate(data);
                else this.enableAutoUpdate(true);
            break;
            case 'o':
                if(success){
                    this.$overrideBtn.prop("disabled", false);
                    this.setState(0);

                    this.timeLeft = this.timer/1000;
                    var me = this;
                    me.petInfoView.setClock(me.timeLeft);

                    if(this.Timer.isRunning()){
                        me.Timer.stop();
                    }

                    me.Timer.start(me.timeLeft, function(t){
                        me.timeLeft = t;
                        me.petInfoView.setClock(t);
                        if(t == 0) me.setState(1);
                    });
                }
            break;
            case 'r':
                this.$rfidChangeBtn.prop("disabled", false);
            break;

            case 't':

                if(success){

                    this.setTimerFormView.disable(false);

                    if(data.timeLeft <= 0){
                        this.setState(1);
                        this.petInfoView.setClock(0);
                    }
                    else{

                        this.setState(0);
                        this.timeLeft = data.timeLeft/1000;
                        var me = this;
                        me.petInfoView.setClock(me.timeLeft);

                        if(this.Timer.isRunning()){
                            me.Timer.stop();
                        }

                        me.Timer.start(me.timeLeft, function(t){
                            me.timeLeft = t;
                            me.petInfoView.setClock(t);
                            if(t == 0) me.setState(1);
                        });
                    }
                }
            break;
        }
    },

    onStatusUpdate: function(data){

        console.log(data);

        if(this.data.currentUid !== data.currentUid){
            if(data.currentUid === ""){
                this.petInfoView.setEmptyInfo();
            }
            else{
                this.updatePetInfo(data.currentUid);
            }

            this.data.currentUid = data.currentUid;
        }
        else if(this.data.currentUid === ""){
            this.petInfoView.setEmptyInfo();
        }


        if(this.timer != data.time){
            this.timer = data.time;
            this.setTimerFormView.setTime(this.timer);
        }

        if(data.state != 1){

            this.timeLeft = data.timeLeft/1000;
            var me = this;

            if(this.Timer.isRunning()){
                me.petInfoView.setClock(me.timeLeft);
                me.Timer.stop();
            }

            me.Timer.start(me.timeLeft, function(t){
                me.timeLeft = t;
                me.petInfoView.setClock(t);
                if(t == 0) me.setState(1);
            });
        }

        this.setState(data.state);

        this.foodPercentage = data.foodPercentage;
        this.foodMeasurerView.setFoodPercent(this.foodPercentage);

        this.enableAutoUpdate(this.autoUpdateEnabled);
    },

    setState: function(code){
        switch (code) {
            case 0:
                this.petInfoView.setState("Tempo restante", 'glyphicon-time');
            break;

            case 1:
                this.petInfoView.setState("Pronto para servir", 'glyphicon-ok');
            break;

            case 2:
                this.petInfoView.setState("Aguarando etiqueta...", 'glyphicon-hourglass');
            break;
        }
    },

    enableAutoUpdate: function(enable){
        var me = this;
        if(enable){
            me.autoUpdateHandle = me.autoUpdateHandle = setTimeout(function(){
                me.sendMessage('s');
            }, me.updateTime);
        }
        else{
            clearTimeout(me.autoUpdateHandle);
            me.autoUpdateHandle = null;
        }
    },

    updatePetInfo: function(uid){

        var info = null;
        for(var i in this.data.pets){
            if(this.data.pets[i].uid === uid){
                info = this.data.pets[i];
            }
        }

        if(info == null){
            this.petInfoView.setName("Não cadastrado");
            this.petInfoView.setUid(uid);
            this.petInfoView.setAvatar(null);
        }
        else{
            this.petInfoView.setName(info.name);
            this.petInfoView.setUid(info.uid);
            this.petInfoView.setAvatar(info.avatar);
        }

        return info;
    },

    ready: function(){
        var me = this;

        me.setTimerFormView.onSubmit(function(data){
            me.onSetTimeSubmit(data);
        });

        me.ajax.request({
            url: me.storageUrl,
            fail: function(){
                console.log("Fail storageUrl");
            },
            success: function(data, response){
                me.onDataLoaded(data);
            }
        });

        me.sendMessage('s');
    },

    init: function(){

        var me = this;

        me.petInfoView = me._appRoot_.get(me.petInfoView);
        me.foodMeasurerView = me._appRoot_.get(me.foodMeasurerView);
        me.setTimerFormView = me._appRoot_.get(me.setTimerFormView);
        me.ajax = me._appRoot_.get(me.ajax);

        me.$overrideBtn = $(me.$overrideBtn);
        me.$overrideBtn.click(function(e){
            me.onOverriderBtnClick(e);
        });

        me.$rfidChangeBtn = $(me.$rfidChangeBtn);
        me.$rfidChangeBtn.click(function(e){
            me.onRfidChangeBtnClick(e);
        });
    }
});

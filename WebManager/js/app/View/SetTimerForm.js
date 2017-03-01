App.define('View.SetTimerForm',{

    $form: '#set-timer-form',
    submitCallback: function(){},

    submit: function(e){

        var inputData = this.$form.serializeArray();
        var data = {};

        for(var i in inputData){
            value = this.validate(inputData[i].name, inputData[i].value);
            if(value === null) continue;
            data[inputData[i].name] = value;
        }

        this.submitCallback(data);
    },

    setData: function(data){
        for(var i in data){
            var input = this.$form.find('*[name='+i+']');
            if(input.attr('type') == 'checkbox'){
                input.prop('checked', data[i] ? true : false);
            }
            else{
                input.val(data[i]);
            }
        }
    },

    setTime: function(time){

        time /= 1000;
        time /= 60;
        var unit = 'minute';

        if(time > 127){
            time /= 60;
            unit = 'hour';
        }

        this.setData({
            't': time,
            'u': unit
        });
    },

    onSubmit: function(callback){
        this.submitCallback = callback;
    },

    validate: function(key, value){

        switch (key) {
            case "t":
                value = parseInt(value);
                if(isNaN(value) || value < 0)
                    value = 0;
                if(value > 127) value = 127;
            break;

            case "u":
                if(value !== "hour" && value !== "minute") value = "minute";
            break;

            case "r":
                value = value == "on" ? "1" : null;
            break;

            default:
                value = null;
        }

        return value;
    },

    disable: function(disable){
        this.$form.find('input, select, button').prop("disabled", disable);
    },

    init: function(){
        var me = this;
        me.$form = $(me.$form);
        me.$form.submit(function(e){
            e.preventDefault();
            me.submit();
        });

        me.setData({
            t: 0,
            u: 'minute',
            r: false
        });
    }

});

App.define('View.PetInfo',{

    $petName: "#pet-name",
    $petUid: "#pet-uid",
    $petAvatar: "#pet-avatar",
    $state: "#state",
    $clock: '#clock',

    defaultAvatar: "img/default-avatar.png",

    setEmptyInfo: function(){
        this.setName("Nenhum Pet");
        this.setUid("&mdash;");
        this.setAvatar(null);
    },

    setName: function(name){
        this.$petName.html(name);
    },

    setUid: function(uid){
        this.$petUid.html(uid);
    },

    setAvatar: function(url){
        if(url === null) url = this.defaultAvatar;
        url = new this._appRoot_.Base.Url(url);
        this.$petAvatar.find("img").attr('src', url.toString());
    },

    setState: function(text, icon){
        this.$state.find('.text').html(text);
        this.$state.find('.glyphicon').removeClass().addClass('glyphicon '+icon);
    },

    setClock: function(seconds){

        var hours = 0,
            minutes = 0;

        if(seconds > 0){
            hours = seconds/3600,
            minutes = parseInt(hours * 60) % 60;
            seconds = seconds % 60;
        }
        else{
            seconds = 0;
        }

        this.$clock.find('.hour').html((hours < 10 ? '0' : '') + parseInt(hours));
        this.$clock.find('.minute').html((minutes < 10 ? '0' : '') + parseInt(minutes));
        this.$clock.find('.second').html((seconds < 10 ? '0' : '') + parseInt(seconds));
    },

    init: function(){
        this.$petName = $(this.$petName);
        this.$petUid = $(this.$petUid);
        this.$petAvatar = $(this.$petAvatar);
        this.$state = $(this.$state);
        this.$clock = $(this.$clock);

        this.setEmptyInfo();
        this.setState("Aguarde...", "glyphicon-hourglass");
        this.setClock(0);

    }

});

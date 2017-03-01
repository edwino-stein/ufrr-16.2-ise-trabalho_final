App.define('Util.Classes',{

    instantiable: [],
    
    getInstance: function(className){

        if(this.instantiable.indexOf(className) < 0)
            throw  'Classe inválida';

        var args = Array.prototype.slice.call(arguments);
        args.shift();

        return new this[className](...args);
    },


    init: function(){
        var unInstantiable = ['_appRoot_', '_initted_', '_namespace_', '_parent_', '_super_', 'apply', 'hasProperty', 'init', 'ready', 'getInstance', 'instantiable'];

        for(var i in this){
            if(unInstantiable.indexOf(i) < 0){
                this.instantiable.push(i);
                this[i].classScope = this;
            }

        }
    }
});

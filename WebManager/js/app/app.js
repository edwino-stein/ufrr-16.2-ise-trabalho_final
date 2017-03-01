(function(){
    App = new Application({
        modules:[
            'Util.Ajax',
            'Util.Classes',
            'View.FoodMeasurer',
            'View.PetInfo',
            'View.SetTimerForm',
            'Controller.Main'
        ],
        modulesPath: 'js/app/'
    });
})();

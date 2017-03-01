App.define('View.FoodMeasurer',{

    $domObj: '#food-measurer',
    $label: '#food-measurer-label',

    setFoodPercent: function(percent){

        if(percent >= 99.5) percent = 100;
        if(percent < 0.5) percent = 0;

        this.$domObj.find('.bar').height(percent+'%');
        this.$label.html(Math.round(percent));
    },

    init: function(){
        this.$domObj = $(this.$domObj);
        this.$label = $(this.$label);
        this.setFoodPercent(50);
    }
});

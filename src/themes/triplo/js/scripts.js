(function($){
    $( document ).ready(function() {

        if ($('.field-name-field-header-image').length) {
            var $header_image = $('.field-name-field-header-image img').attr('src');
            $(".header_bg").css("background-image", "url("+"'"+$header_image+"'"+")");
        }

        // Scroll top Button
        var $div_scroll = $('<div class="scroll_to_top"><div class="scroll_to_top_button"></div></div>');
        $( "body" ).append($div_scroll);
        $(".scroll_to_top").click(function(){
            $("html, body").animate({ scrollTop: 0 }, "slow");
        });

        $(window).scroll(function(){
            if ($(window).scrollTop() > 250) {
                $(".scroll_to_top").show();
                $("header").addClass("sticky-header") // Scroll top Button
            }else{
                $(".scroll_to_top").hide();
                $("header").removeClass("sticky-header") // Scroll top Button
            } 
        });
        
    });
})(jQuery);
document.addEventListener('DOMContentLoaded', function() {

    let mandolin = document.querySelector('.mandolin');
    mandolin.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('mandolin.jpg')";
        document.querySelector(".education_main").style.backgroundPosition = 'top';
    })

    let guitar = document.querySelector('.guitar');
    guitar.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('guitar.jpg')";
        document.querySelector(".education_main").style.backgroundPosition = 'center';

    })

});

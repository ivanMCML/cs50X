document.addEventListener('DOMContentLoaded', function() {

    let onk = document.querySelector('.onk');
    onk.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('onk.jpg')";
        document.querySelector(".education_main").style.backgroundPosition = 'top';
    })

    let hajduk = document.querySelector('.hajduk');
    hajduk.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('hajduk.jpg')";
                document.querySelector(".education_main").style.backgroundPosition = 'right';
    })

    let karate = document.querySelector('.karate');
    karate.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('karate.png')";
        document.querySelector(".education_main").style.backgroundPosition = 'top';
        document.querySelector(".education_main").style.backgroundSize = 'auto 100%'
    })

    let maraton = document.querySelector('.maraton');
    maraton.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('maraton.jpeg')";
        document.querySelector(".education_main").style.backgroundPosition = 'center';
    })

    let jerkovac = document.querySelector('.jerkovac');
    jerkovac.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('jerkovac.jpg')";
        document.querySelector(".education_main").style.backgroundPosition = 'center';

    })
});

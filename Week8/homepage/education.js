document.addEventListener('DOMContentLoaded', function() {

    let primary = document.querySelector('.primary');
    primary.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('primary.jpg')";
        document.querySelector(".education_main").style.backgroundPosition = 'center';

    })

    let secondary = document.querySelector('.secondary');
    secondary.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('secondary.jpg')";
        document.querySelector(".education_main").style.backgroundPosition = 'center';
    })

    let university = document.querySelector('.university');
    university.addEventListener('click', function(){
        document.querySelector(".education_main").style.backgroundImage = "url('university.jpg')";
        document.querySelector(".education_main").style.backgroundPosition = 'center';
    })
});

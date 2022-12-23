var btn = document.getElementById("btn");
var menu = document.getElementById("menu");
var btn1 = document.getElementById("btn1");
var btn2 = document.getElementById("btn2");
var btn3 = document.getElementById("btn3");
var btn4 = document.getElementById("btn4");
var btn5 = document.getElementById("btn5");
var btn6 = document.getElementById("btn6");
var modal1 = document.getElementById("modal1");
var modal2 = document.getElementById("modal2");

btn.onclick = function () {
    menu.classList.toggle("is-active")
    btn.classList.toggle("is-active")
};

btn1.onclick = function () {
    modal1.classList.toggle("is-active")
};

btn2.onclick = function () {
    modal1.classList.toggle("is-active")
};

btn3.onclick = function () {
    modal1.classList.toggle("is-active")
};

btn4.onclick = function () {
    modal2.classList.toggle("is-active")
};

btn5.onclick = function () {
    modal2.classList.toggle("is-active")
};

btn6.onclick = function () {
    modal2.classList.toggle("is-active")
};

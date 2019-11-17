var opp = document.getElementById("lengst-oppe");
var ned = document.getElementById("litt-lengre-ned");
function at_top() {
    ned.classList.remove("active");
    opp.classList.add("active");
}
function at_lengerned() {
    opp.classList.remove("active");
    ned.classList.add("active");
}

var bilde = document.getElementById("bilde");
var sticky = bilde.offsetTop;
function myFunction() {
  if (window.pageYOffset  >= sticky) {
    at_lengerned()
  } else {
    at_top()
  }
}

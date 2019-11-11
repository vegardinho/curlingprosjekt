function forsvinn() {
  var x = document.getElementById("bane2");
  var y = document.getElementById("knapp1");
  if (x.style.display === "none") {
    x.style.display = "block";
    y.style.display = "none";
  } else {
    x.style.display = "none";
    y.style.display = "block";
  }
}
function forsvinn2() {
  var x = document.getElementById("bane3");
  var y = document.getElementById("knapp2");
  if (x.style.display === "none") {
    x.style.display = "block";
    y.style.display = "none";
  }
  else {
    x.style.display = "none";
    y.style.display = "block";
  }
}
let htmlStyles = window.getComputedStyle(document.querySelector("html"));
let rowNum = parseInt(htmlStyles.getPropertyValue("--rowNum"));

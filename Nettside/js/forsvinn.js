function forsvinn() {
  var x = document.getElementById("bane2");
  if (x.style.display === "none") {
    x.style.display = "block";
  } else {
    x.style.display = "none";
  }
  document.getElementById("hele-grid").style.setProperty("--colNum", 3);
}
function forsvinn2() {
  var x = document.getElementById("bane3");
  if (x.style.display === "none") {
    x.style.display = "block";
  } else {
    x.style.display = "none";
  }
  document.documentElement.style.setProperty("--rowNum", 2);
}
let htmlStyles = window.getComputedStyle(document.querySelector("html"));
let rowNum = parseInt(htmlStyles.getPropertyValue("--rowNum"));

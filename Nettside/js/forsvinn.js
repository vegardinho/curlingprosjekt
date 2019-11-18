var bane2 = document.getElementById("bane2");
var knapp1 = document.getElementById("knapp1");
var bane3 = document.getElementById("bane3");
var knapp2 = document.getElementById("knapp2");


function forsvinn() {
    if (knapp1.style.display === "none") {
      knapp1.style.display = "block";
      bane2.style.display = "none";
    } else {
      knapp1.style.display = "none";
      bane2.style.display = "block";
    }
}
function forsvinn2() {
  if (knapp2.style.display === "none") {
    knapp2.style.display = "block";
    bane3.style.display = "none";
  }
  else {
    knapp2.style.display = "none";
    bane3.style.display = "block";
  }
}
try {document.getElementById("banenummersend").addEventListener("click", function(event) {
   var inputfrabruker = parseInt(document.getElementById("banenummer1").value);
   var banenummer = "Bane nr. " + inputfrabruker;
   document.getElementById("sett_banenummer").style.display= "none";
   document.getElementById("banenummer_1_tekst").innerHTML = banenummer;

});
} catch(e) {}

try{
document.getElementById("lengst-oppe").addEventListener("click", function(event) {
  document.body.scrollTop = 0; // For Safari
  document.documentElement.scrollTop = 0; // For Chrome, Firefox, IE and Opera
});
} catch (e) {}

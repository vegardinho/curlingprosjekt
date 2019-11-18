document.getElementById("banenummersend").addEventListener("click", function(event) {
   var inputfrabruker = parseInt(document.getElementById("banenummer1").value);
   var banenummer = "Bane nr. " + inputfrabruker;
   document.getElementById("sett_banenummer").style.display= "none";
   document.getElementById("banenummer_1_tekst").innerHTML = banenummer;

});

var body = document.getElementById("body");
body.addEventListener("load", function(event){
    if (typeof inputfrabruker !== 'undefined') {
      console.log("hei");
      function setbane() {
        var banenummer = "Bane nr. " + inputfrabruker;
        document.getElementById("sett_banenummer").style.display= "none";
        document.getElementById("banenummer_1_tekst").innerHTML = banenummer;
      }
    }
    else {
      console.log("Ikke noe lagret");
    }
  });

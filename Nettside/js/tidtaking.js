var hvitTid = 2280;
var roedTid = 2280;
var hvitRunde = true;
var stoppet = true;

document.getElementById("hvit");
document.getElementById("hvit").style.border = "solid #001f3f";
document.getElementById("start_stopp_knapp").onmouseover = function() {
   this.style.backgroundColor = "#00ff00";
}

document.getElementById("start_stopp_knapp").onmouseout = function() {
   this.style.backgroundColor = "white";
}

function gronn_time() {
   document.getElementById("start_stopp_knapp").style.backgroundColor = "white";
   document.getElementById("start_stopp_knapp").style.border = "solid #00ff00";
   document.getElementById("start_stopp_knapp").innerText = "Start";
   document.getElementById("start_stopp_knapp").onmouseover = function() {
      this.style.backgroundColor = "#00ff00";
   }
}

function roed_time() {
   document.getElementById("start_stopp_knapp").style.backgroundColor = "white";
   document.getElementById("start_stopp_knapp").style.border = "solid #f44336";
   document.getElementById("start_stopp_knapp").innerText = "Stopp";
   document.getElementById("start_stopp_knapp").onmouseover = function() {
      this.style.backgroundColor = "#f44336";
   }
}
// sjekk om nytt i json-fil, og endre etter dette
// intervall = setInterval(lesJson, 1);

// var requestURL = 'data.json';
// var request = new XMLHttpRequest();
// request.open('GET', requestURL);
// request.responseType = 'json';
// request.send();
// request.onload = function() {
//    var svar = request.response;
//
// };

function loadJSON(callback) {   

   var xobj = new XMLHttpRequest();
   xobj.overrideMimeType("application/json");
   xobj.open('GET', 'data.json', true); // Replace 'my_data' with the path to your file
   xobj.onreadystatechange = function () {
      if (xobj.readyState == 4 && xobj.status == "200") {
	 // Required use of an anonymous callback as .open will NOT
	 // return a value but simply returns undefined in asynchronous mode
	 callback(xobj.responseText);
      }
   };
   xobj.send(null);  
}

   loadJSON(function(response) {
      // Parse JSON string into object
      var actual_JSON = JSON.parse(response);
   });

// function lesJson() {
//    console.log(jsonData[0].aks);
// }

// Trekk fra et sekund hvert sekund og oppdater siden
function counter() {
   if (hvitRunde) {
      hvitTid --;
      tidStreng = lagTidStreng(hvitTid);
      document.getElementById("hvitTid").innerHTML = tidStreng;
   } else {
      roedTid --;
      tidStreng = lagTidStreng(roedTid);
      document.getElementById("roedTid").innerHTML = tidStreng;
   }
}

function lagTidStreng(tid) {
   var min = Math.floor(tid/60);
   var sek = tid % 60;
   var minStreng, sekStreng;

   if (min === 0) {
      minStreng = "00:";
   } else {
      minStreng = min;
   }

   if (sek === 0) {
      sekStreng = "00";
   } else {
      sekStreng = sek;
   }

   return `${minStreng}:${sekStreng}`;
}

// Start og stopp timer ved klikk
document.getElementById("start_stop").addEventListener("click", function(event) {
   if (stoppet) {
      intervall = setInterval(counter, 1000);
      stoppet = false;
      roed_time()

   } else {
      clearInterval(intervall);
      gronn_time()
      stoppet = true;
   }
});

// Endre lag manuelt
document.getElementById("bytt_lag").addEventListener("click", function(event) {
   if (hvitRunde === true) {
      hvitRunde = false;
      document.getElementById("roed").style.border = "solid #001f3f";
      document.getElementById("hvit").style.border = "white";
   } else {
      hvitRunde = true;
      document.getElementById("hvit").style.border = "solid #001f3f";
      document.getElementById("roed").style.border = "white";
   }
});

// Oppdater tid hvis bruker manuelt endrer tid
document.getElementById("settTid").addEventListener("click", function(event) {
   var nyMin = parseInt(document.getElementById("nyMin").value);
   var nySek = parseInt(document.getElementById("nySek").value);
   if (isNaN(nyMin) || isNaN(nySek)) {
      alert("Skriv inn gyldige verdier for tid!");
   } else {
      if (nyMin > 38 || nySek > 60 || (nyMin === 38 && nySek > 0)) {
	 alert("Ugyldig inndata. Tid må være mellom 00:00 og 38:00");
      } else {
	 var nyTid = (60 * nyMin) + nySek;
	 if (hvitRunde) {
	    hvitTid = nyTid;
	    document.getElementById("hvitTid").innerHTML = lagTidStreng(nyTid);
	 } else {
	    roedTid = nyTid;
	    document.getElementById("roedTid").innerHTML = lagTidStreng(nyTid);
	 }
      }
   }
});

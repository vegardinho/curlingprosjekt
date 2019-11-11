var hvitTid = 2280;
var roedTid = 2280;
var hvitRunde = true;
document.getElementById("hvit").style.color = "#cccc00";
var stoppet = true;

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
   } else {
      clearInterval(intervall);
      stoppet = true;
   }
});

// Endre lag manuelt
document.getElementById("bytt_lag").addEventListener("click", function(event) {
   if (hvitRunde === true) {
      hvitRunde = false;
      document.getElementById("roed").style.color = "#cccc00";
      document.getElementById("hvit").style.color = "black";
   } else {
      hvitRunde = true;
      document.getElementById("hvit").style.color = "#cccc00";
      document.getElementById("roed").style.color = "black";
   }
});

// Oppdater tid hvis bruker manuelt endrer tid
document.getElementById("settTid").addEventListener("click", function(event) {
   var nyMin = parseInt(document.getElementById("nyMin").value);
   var nySek = parseInt(document.getElementById("nySek").value);
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
});

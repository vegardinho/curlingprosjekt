var hvitTid = 2280;
var roedTid = 2280;
var hvitRunde = true;
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
   var streng = `${min}:${sek}`;
   return streng;
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

document.getElementById("bytt_lag").addEventListener("click", function(event) {
   if (hvitRunde === true) {
      hvitRunde = false;
   } else {
      hvitRunde = true;
   }
});

document.getElementById("settTid").addEventListener("click", function(event) {
   var nyMin = parseInt(document.getElementById("nyMin").value);
   var nySek = parseInt(document.getElementById("nySek").value);
   if (nyMin > 38 || nySek > 60 || (nyMin === 38 && nySek > 0)) {
      alert("Ugyldig inndata. Tid må være mellom 00:00 og 38:00");
   } else {
      console.log(nyMin);
      console.log(nySek);
      var nyTid = (60 * nyMin) + nySek;
      if (hvitTid) {
	 hvitTid = nyTid;
	 document.getElementById("hvitTid").innerHTML = lagTidStreng(hvitTid);
      } else {
	 roedTid = nyTid;
	 document.getElementById("roedTid").innerHTML = lagTidStreng(hvitTid);
      }
   }
});

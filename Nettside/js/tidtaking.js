var hvitTid = 2160;
var roedTid = 2160;
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


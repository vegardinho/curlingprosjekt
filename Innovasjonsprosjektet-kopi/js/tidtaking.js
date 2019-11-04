var hvitTid = 2160;
var roead_tid = 2160;
var hvitRunde = true;
var stoppet = true;

function counter() {
   if (hvitRunde) {
      endreTid(hvitTid);
      document.getElementById("hvitTid").innerHTML = tid_streng;
   } else {
      endreTid(roedTid);
      document.getElementById("roedTid").innerHTML = tid_streng;
   }
}

function endreTid(tid) {
   tid --;
   tidStreng = lagTidStreng(tid);
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

document.getElementById("bytt_lag").addEventListener("click:wqa


var dbAdd = [];
var dbRecv = [];
var dbDiff = [];

var av = 0;

//Firebase kode
  // Your web app's Firebase configuration
  var firebaseConfig = {
    apiKey: "AIzaSyAiZ7O5u4reFJDmEo4ZwzvZvczccREeijs",
    authDomain: "innovasjonsprosjektet-11.firebaseapp.com",
    databaseURL: "https://innovasjonsprosjektet-11.firebaseio.com",
    projectId: "innovasjonsprosjektet-11",
    storageBucket: "innovasjonsprosjektet-11.appspot.com",
    messagingSenderId: "104701095266",
    appId: "1:104701095266:web:e1471d5c6009b04458503b",
    measurementId: "G-TCK6GJTDZ0"
  };
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);
  firebase.analytics();

  // Get a reference to the database service
  let database = firebase.database();
  var output = document.getElementById('output');
  var steiner = database.ref("data");

// Legger til steininfo i database
function addStein() {
      var ny_aks = parseInt(document.getElementById("nyaks").value);
      var ny_gyro = parseInt(document.getElementById("nygyro").value);
      var ny_cond = parseInt(document.getElementById("nycond").value);

      let nyStein = {
        "aks": ny_aks,
        "gyro": ny_gyro,
        "cond": ny_cond
      }

      dbAdd.push(Date.now());
      pushStein(nyStein);
  }

function pushStein(stein) {
  steiner.push(stein);
};

  // var steinTilstand = firebase.database().ref('data/');
  // steinTilstandRef.on('value', function(snapshot) {
  //   updateTilstand(output, snapshot.val());
// });
var naa_aks =  0;
var naa_gyro = 0;
var naa_cond = 0;


//var steinRef = database.ref('data');
let aks = document.getElementById("aks");
let gyro = document.getElementById("gyro");
let cond = document.getElementById("cond");

// Oppdaterer verdier for aks, gyro og kap basert på databaseverdier, og kaller på auto_start_stop()
function visSteiner(snapshot) {
   dbRecv.push(Date.now());

   var recvInd = dbRecv.length - 1;
   var addInd = dbAdd.length - 1;

   var diff = dbRecv[recvInd] - dbAdd[addInd];
   dbDiff.push(diff);

   if (diff != NaN) {
      var ant = ant + 1;
      var forrigeSum = av * (ant);
      av = (forrigeSum + diff) / (ant + 1);
      console.log(diff);
      console.log(av);
   }

  var stein = snapshot.val();
  var naa_aks = `${stein.aks}`;
  var naa_gyro = `${stein.gyro}`;
  var naa_cond = `${stein.cond}`;

  aks.innerHTML = "Aks: " + naa_aks;
  gyro.innerHTML = "Gyro: " + naa_gyro;
  cond.innerHTML = "Cond: " + naa_cond;
  automatic_start_stop(naa_aks, naa_gyro, naa_cond);

}

// Kall på visSteiner() hvis noe legges til i databasen
steiner.on('child_added', visSteiner);

knapp = document.getElementById("firebase");
console.log(knapp);
knapp.addEventListener("click", addStein);





//TIDTAKNING
var stein_paa_vei = false;
var start_game = false;
var stein_aktivert = false;
var hvitTid = 2280;
var roedTid = 2280;
var hvitRunde = true;
document.getElementById("hvit");
var stoppet = true;
document.getElementById("hvit").style.border = "solid #001f3f";

document.getElementById("start_stop").onmouseover = function()
  {
    this.style.backgroundColor = "#00ff00";
  }
document.getElementById("start_stop").onmouseout = function()
{
  this.style.backgroundColor = "white";
}

function gronn_time() {
    document.getElementById("start_stop").style.backgroundColor = "white";
    document.getElementById("start_stop").style.border = "solid #00ff00";
    document.getElementById("start_stop").innerText = "Start";
    document.getElementById("start_stop").onmouseover = function()
      {
        this.style.backgroundColor = "#00ff00";
      }
}
function roed_time(){
    document.getElementById("start_stop").style.backgroundColor = "white";
    document.getElementById("start_stop").style.border = "solid #f44336";
    document.getElementById("start_stop").innerText = "Stopp";
    document.getElementById("start_stop").onmouseover = function()
    {
      this.style.backgroundColor = "#f44336";
    }
}

function counter() {
   if (hvitRunde) {
      hvitTid -= 0.01
      tidStreng = lagTidStreng(Math.round(hvitTid));
      document.getElementById("hvitTid").innerHTML = tidStreng;
   } else {
      roedTid -= 0.01;
      tidStreng = lagTidStreng(Math.round(roedTid));
      document.getElementById("roedTid").innerHTML = tidStreng;
   }
}

function lagTidStreng(tid) {
   var min = Math.floor(tid/60);
   var sek = tid % 60;
   var minStreng, sekStreng;

   if (min === 0) {
      minStreng = "00:";
   }
   else if (min < 10){
      minStreng = "0" + min;
   }
   else {
      minStreng = min;
   }

   if (sek === 0) {
      sekStreng = "00";
   }
   else if (sek < 10) {
     sekStreng = "0" + sek
   }
   else {
      sekStreng = sek;
   }

   return `${minStreng}:${sekStreng}`;
}

// Start og stopp timer ved klikk
function start_stopp_tid (){
     if (stoppet) {
        intervall = setInterval(counter, 10);
        stoppet = false;
        roed_time();

     } else {
        clearInterval(intervall);
        gronn_time();
        stoppet = true;
     }
  }

function manual_stopp() {
  if (start_game) {
    start_game = false;
  }
  else {
    start_game = true;
  }
  start_stopp_tid ();
}


function automatic_start_stop (naa_aks, naa_gyro, naa_cond) {
  // console.log(stein_aktivert);
  if (start_game) {
    if (naa_aks == 0 && naa_gyro == 0 && naa_cond == 0 && stein_paa_vei) {
      console.log("Steinen har stoppet");
      bytt_lag ();
      start_stopp_tid ();
      stein_paa_vei = false;
    }
    else if (naa_cond == 1 && (naa_aks == 1 || naa_gyro == 1)){
      console.log("Steinen er aktivert");
      stein_aktivert = true;
    }
    else if(naa_cond == 0 && (naa_aks == 1 || naa_gyro == 1) && (stein_aktivert)){
      console.log("Steinen er sluppet og i bevegelse");
      start_stopp_tid();
      stein_aktivert = false;
      stein_paa_vei = true;
    }
  }

}



// Kall på manual_stopp() hvis noen klikker på start-stopp-knappen
document.getElementById("start_stop").addEventListener("click", manual_stopp);

// Endre lag manuelt
function bytt_lag (){
   if (hvitRunde === true) {
      hvitRunde = false;
      document.getElementById("roed").style.border = "solid #001f3f";
      document.getElementById("hvit").style.border = "white";
   } else {
      hvitRunde = true;
      document.getElementById("hvit").style.border = "solid #001f3f";
      document.getElementById("roed").style.border = "white";
   }
}

document.getElementById("bytt_lag").addEventListener("click", bytt_lag);



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

//Firebase kode
  // Setter opp en kobling mellom nettsiden og Firebase database
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
  // Starter Firebase
  firebase.initializeApp(firebaseConfig);
  firebase.analytics();

  // Lager en referanse til databasen
  let database = firebase.database();
  var steiner = database.ref("data");

// Funksjon for testing av databasen og de boolske funksjonene
function addStein() {
      var ny_aks = parseInt(document.getElementById("nyaks").value);
      var ny_gyro = parseInt(document.getElementById("nygyro").value);
      var ny_cond = parseInt(document.getElementById("nycond").value);

      let nyStein = {
        "aks": ny_aks,
        "gyro": ny_gyro,
        "cond": ny_cond
      }
      pushStein(nyStein);
  }

      function pushStein(stein) {
      steiner.push(stein);
      };

// Knapp for sending av verdier til Firebase
knapp = document.getElementById("firebase");
console.log(knapp);
knapp.addEventListener("click", addStein);

// De tre variablene som funksjonene baserer seg på
var naa_aks =  0;
var naa_gyro = 0;
var naa_cond = 0;

//Setter opp for visning av data på nettsiden
let aks = document.getElementById("aks");
let gyro = document.getElementById("gyro");
let cond = document.getElementById("cond");

// Viser verdiene som ligger i databasen på nettsiden
function visSteiner(snapshot) {
  var stein = snapshot.val();
  // Her oppdateres variablene ved innsending av ny data til databasen
  var naa_aks = `${stein.aks}`;
  var naa_gyro = `${stein.gyro}`;
  var naa_cond = `${stein.cond}`;

  aks.innerHTML = "Aks: " + naa_aks;
  gyro.innerHTML = "Gyro: " + naa_gyro;
  cond.innerHTML = "Cond: " + naa_cond;
  automatic_start_stop(naa_aks, naa_gyro, naa_cond);

}
// Aktiverer visSteiner funksjonen når nye data dukker opp i databasen
steiner.on('child_added', visSteiner);

// Reseter all data på Firebase når nettsiden lukkes
  body = document.getElementById("body");
  body.addEventListener ("unload", removeFirebaseData);

  function removeFirebaseData(){
    steiner.remove();
    let rendatabase = {
      "data": 0
    }
    database.set(rendatabase);
  }


//TIDTAKNING
var stein_paa_vei = false; //Er steinen i bevegelse og på vei
var start_game = false; //Er kampen manuelt startet enda
var stein_aktivert = false; //Er steinen holdt i og i bevegelse

// Tiden til de to lagene i sekunder
var hvitTid = 2280;
var roedTid = 2280;
//Hvem sin runde er det?
var hvitRunde = true;
//For logfunksjonen på nettsiden
var log = document.getElementById("log");
document.getElementById("hvit");
var stoppet = true;

document.getElementById("hvit").style.border = "solid #001f3f";
document.getElementById("start_stop").onmouseover = function(){
    this.style.backgroundColor = "#00ff00";
  }
document.getElementById("start_stop").onmouseout = function(){
  this.style.backgroundColor = "white";
}

//Endrer farge og tekst på knappen etter om kampen er startet eller stoppet
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

// Funksjonene for å telle tid og vise en tidsstreng på nettsiden
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

// Automatisk start og stopp av tidtakningsfunksjon
function automatic_start_stop (naa_aks, naa_gyro, naa_cond) {
  if (start_game) {
    if (naa_aks == 0 && naa_gyro == 0 && naa_cond == 0 && stein_paa_vei) {
      console.log("Steinen har stoppet");
      bytt_lag ();
      start_stopp_tid ();
      stein_paa_vei = false;
      writelog("Steinen har stoppet, tiden startes for det andre laget.")
    }
    else if (naa_cond == 1 && (naa_aks == 1 || naa_gyro == 1) && stein_aktivert == false){
      console.log("Steinen er aktivert");
      stein_aktivert = true;
      writelog("Steinen er aktivert");
    }
    else if(naa_cond == 0 && (naa_aks == 1 || naa_gyro == 1) && (stein_aktivert)){
      console.log("Steinen er sluppet og i bevegelse");
      start_stopp_tid();
      stein_aktivert = false;
      stein_paa_vei = true;
      writelog("Steinen er sluppet og på vei. Tiden stoppes.");
    }
  }

}

document.getElementById("start_stop").addEventListener("click", manual_stopp);

function writelog(tekst){
  if (hvitRunde) {
    log.innerHTML += "<br> <b> Hvit: </b>" + lagTidStreng(Math.round(hvitTid)) + ": " + tekst;
  }
  else {
    log.innerHTML += "<br> <b> Rød: </b>" + lagTidStreng(Math.round(roedTid)) + ": " + tekst;
  }
  log.scrollTop = log.scrollHeight;
}

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

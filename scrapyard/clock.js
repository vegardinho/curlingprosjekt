<script>
// Update the count down every 1 second
var x = setInterval(function() {

  // Find the distance between now and the count down date
  var distance = 4320;

  // Time calculations for days, hours, minutes and seconds
  var minutes = Math.floor((distance ) / (60));
  var seconds = Math.floor((distance % (60)));

  // Display the result in the element with id="demo"
	document.getElementById("clock").innerHTML = 
	minutes + "m " + seconds + "s ";

  // If the count down is finished, write some text
  if (distance < 0) {
    clearInterval(x);
    document.getElementById("clock").innerHTML = "EXPIRED";
  }
}, 1000);
</script>
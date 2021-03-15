function submit() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("name").innerHTML = this.responseText;
    }
  };
  xhttp.open("POST", "/get_path", true);
  xhttp.send();
}

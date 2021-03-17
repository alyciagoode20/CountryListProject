$(document).ready(function () {
  // console.log("HERE");

  $("#name").keydown(function(e) {  // on enter
    // console.log(e.keyCode);
    if (e.keyCode == 13) {
      // console.log("YES");

      var name = $("#name").val();

      $.post("/get_path", {
        name: name
      }).success(function(result) {
        var obj = document.getElementById("container");
        if (obj) {  // if there is a container
          obj.remove();
        }
        // alert(result);
        var div = document.createElement("DIV");
        div.id = "container";
        div.innerHTML = result;
        var form = document.getElementById("dest");
        form.after(div)  // insert result within body, after form.
      });
    }
  });
  // Listen to click event on the submit button
  $('#button').click(function (e) {  // on clicking submit button
    // console.log("2");
    e.preventDefault();  // prevents the page from refreshing.

    var name = $("#name").val();

    $.post("/get_path", {
      name: name
    }).success(function(result) {
      var obj = document.getElementById("container");
      if (obj) {  // if there is a container
        obj.remove();
      }
      // alert(result);
      var div = document.createElement("DIV");
      div.id = "container";
      div.innerHTML = result;
      var form = document.getElementById("dest");
      form.after(div)  // insert result within body, after form.
    });
  });
});

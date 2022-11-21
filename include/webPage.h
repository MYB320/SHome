String webPage = R"***(
<!DOCTYPE html>
<head>
  <title>TTGO Web Server</title>
</head>
<html>
  <body>
    <div>
      <h1>Hello From TTGO</h1>
      <hr />
      <div>
        <h4>Send msg to TTGO's screen:</h4>
        <input type="text" id="input" />
        <input
          type="button"
          value="send"
          onclick="postData('post', document.getElementById('input').value)"
        />
      </div>
      <hr />
      <div>
        <h4>Read msg from TTGO:</h4>
        <div id="msg"></div>
      </div>
      <hr />
      <div>
        <h4>Read Temperature from sensor:</h4>
        <div id="temp"></div>
      </div>
    </div>
  </body>
  <script>
    setInterval(() => {
      fetch("get")
        .then((response) => response.text())
        .then((text) => (document.getElementById("msg").innerHTML = text));
    }, 100);

    setInterval(() => {
      fetch("getTemp")
        .then((response) => response.text())
        .then((text) => (document.getElementById("temp").innerHTML = text));
    }, 1000);

    function postData(route, Content) {
      fetch(route, {
        method: "POST",
        headers: {
          "Content-Type": "text/plane",
        },
        body: Content,
      })
        .then((response) => response.text())
        .then((data) => {
          console.log(data);
        });
    }
  </script>
</html>
)***";

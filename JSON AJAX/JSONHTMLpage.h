  /*
   * HTML Header file for nodemcu ajax sketch
   * Author: John Glatts
   * Date: 4/8/19
   * Use stats feature from ESP-DASH to display better stats
   *
   */


  const char page[] = R"=====(
       <head>
       <title>JDG SERVER</title>
       <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
       </head>
       <body>
       <h1 class="name">JDG ESP SERVER</h1>
        <div class="rc_nav" id="centered_nav">
        <a href="/">Home</a>
        <a href="Stats">Board Stats</a>
        <a href="About">About</a>
        <a href="Reboot">Reboot</a>
        <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
        </div>
       <h1 class="content">Sensor to Node MCU Web Server</h1>
       <div id = "all-buttons">
       <button class="content-buttons"><a href="Time">Time It</a></button>
       <br>
       <button class="content-buttons"><a href="MotorOn">Motor On</a></button>
       </div>
       </body>
        <script>
              var x = setInterval(function() {loadData('data.txt',updateData)}, 500)
              function loadData(url, callback){
                var xhttp = new XMLHttpRequest()
                xhttp.onreadystatechange = function(){
                if(this.readyState == 4 && this.status == 200){
                    callback.apply(xhttp)
                  }
                };
                xhttp.open("GET", url, true)
                xhttp.send()
              }
              function updateData(){
                console.log(this.responseText)
              }
              function myFunction() {
                var x = document.getElementById("centered_nav");
                if (x.className === "rc_nav") {
                    x.className += " responsive";
                } else {
                    x.className = "rc_nav";
                }
              }
          </script>
          <style>
            body {
              background-color: whitesmoke;
              font-family: 'Roboto', sans-serif;
            }
            .name {
              size: 4em;
              text-align: center;
            }
            a {
              text-decoration: none;
            }
            .content {
              text-align: center;
            }
            #all-buttons {
                text-align: center;
            }
            .content-buttons {
              margin-top: 2em;
              padding: 15px;
              background-color: Gainsboro;
              font-size: 2em;
              text-align: center;
             }

            .rc_nav {
              overflow: hidden;
              background-color: #363841;
              text-align: center;
              z-index: 6;
            }

            .rc_nav a {
             display: inline-block;
             margin-right: -4px;  /* inline-block gap fix */
             color: #fff;
             padding: 22px 22px;
             text-decoration: none;
             font-family: Poppins;
             font-size: 18px;
             -webkit-transition: background 0.3s linear;
             -moz-transition: background 0.3s linear;
             -ms-transition: background 0.3s linear;
             -o-transition: background 0.3s linear;
             transition: background 0.3s linear;
             z-index: 9;
            }

            .rc_nav a:hover {
              background-color: #575b69;
              color: #bdfe0e2;
            }

            .rc_nav .icon {
              display: none;
            }

            .rc_content {
              text-align: center;
              padding-left:14px;
              font-family: Poppins;
              margin-top: 100px;
              color: #8e909b;
            }


            @media screen and (max-width: 820px) {
              .rc_nav a {display: none;}
              .rc_nav a.icon {
                float: right;
                display: block;
                width: 60px;
              }
            }

            @media screen and (max-width: 820px) {
              .rc_nav.responsive {position: relative; top: 73px;}
              .rc_nav.responsive .icon {
                position: fixed;
                right: 0;
                top: 0;
              }
              .rc_nav.responsive a {
                float: none;
                display: block;
                text-align: center;
              }
            }
          </style>
  )=====";


  // elapsed time page
  const char time_page[] = R"=====(
      <head>
       <meta charset="UTF-8">
       <title>JDG SERVER</title>
       <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
      </head>
      <h1 class="name">JDG ESP SERVER</h1>
      <div class="rc_nav" id="centered_nav">
        <a href="/">Home</a>
        <a href="Stats">Board Stats</a>
        <a href="About">About</a>
        <a href="Reboot">Reboot</a>
        <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
      </div>
      <div class="time-content">
      <h1>Sensor to Node MCU Web Server</h1>
      <h1 style="display:inline;">Elapsed Time: </h1><h1 id="mins" style="display:inline;"></h1><h1 style="display:inline;"> mins </h1>
      <h1 style="display:inline;"> and </h1><h1 id="secs" style="display:inline;"></h1>
      <h1 style="display:inline;"> secs. </h1>
      </div>
        <script>
          var x = setInterval(function() {loadTime("time.txt",updateTime)}, 500)
          function loadTime(url, callback){
              var xhttp_time = new XMLHttpRequest()
              xhttp_time.onreadystatechange = function(){
              if(this.readyState == 4 && this.status == 200){
                  callback.apply(xhttp_time)
              }
          };
          xhttp_time.open("GET", url, true)
          xhttp_time.send()
          }
          function updateTime(){
              var timeArray = this.responseText.split("||")
              console.log(timeArray[0])
              console.log(timeArray[1])
              console.log("----------- ")
              document.getElementById("mins").innerHTML = timeArray[0]
              document.getElementById("secs").innerHTML = timeArray[1]
          }
          function myFunction() {
                var x = document.getElementById("centered_nav");
                if (x.className === "rc_nav") {
                    x.className += " responsive";
                } else {
                    x.className = "rc_nav";
                }
          }
      </script>
       <style>
            body {
              background-color: whitesmoke;
              font-family: 'Roboto', sans-serif;
            }
            .name {
              size: 4em;
              text-align: center;
            }
            .time-content {
              text-align: center;
            }
            .content {
              text-align: center;
            }
            .rc_nav {
              overflow: hidden;
              background-color: #363841;
              text-align: center;
              z-index: 6;
            }

            .rc_nav a {
             display: inline-block;
             margin-right: -4px;  /* inline-block gap fix */
             color: #fff;
             padding: 22px 22px;
             text-decoration: none;
             font-family: Poppins;
             font-size: 18px;
             -webkit-transition: background 0.3s linear;
             -moz-transition: background 0.3s linear;
             -ms-transition: background 0.3s linear;
             -o-transition: background 0.3s linear;
             transition: background 0.3s linear;
             z-index: 9;
            }

            .rc_nav a:hover {
              background-color: #575b69;
              color: #bdfe0e2;
            }

            .rc_nav .icon {
              display: none;
            }

            .rc_content {
              text-align: center;
              padding-left:14px;
              font-family: Poppins;
              margin-top: 100px;
              color: #8e909b;
            }


            @media screen and (max-width: 820px) {
              .rc_nav a {display: none;}
              .rc_nav a.icon {
                float: right;
                display: block;
                width: 60px;
              }
            }

            @media screen and (max-width: 820px) {
              .rc_nav.responsive {position: relative; top: 73px;}
              .rc_nav.responsive .icon {
                position: fixed;
                right: 0;
                top: 0;
              }
              .rc_nav.responsive a {
                float: none;
                display: block;
                text-align: center;
              }
            }
        </style>
  )=====";


  // stats page
  // the bug is because the JSON loses it format when it makes thr browser, poss. issue with Arduino.JSON
  // 4-19-19 the bug seems to be a type with statsObj and (was) jsonObj
  const char board_stats_page[] = R"=====(
      <head>
       <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1.0">
       <title>JDG SERVER</title>
       <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
      </head>
      <body>
      <h1 class="name">JDG ESP SERVER</h1>
      <div class="rc_nav" id="centered_nav">
        <a href="/">Home</a>
        <a href="Stats">Board Stats</a>
        <a href="About">About</a>
        <a href="Reboot">Reboot</a>
        <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
      </div>
      <div class="time-content">
      <h2 style="display:inline-block;">Chip ID: </h2>
      <h2 id = "chipID" style="display:inline-block;"></h2>
      <br>
      <h2 style="display:inline-block;">MAC Address: </h2>
      <h2 id = "mac_address" style="display:inline-block;"></h2>
      <br>
      <h2 style="display:inline-block;">Sketch Hash: </h2>
      <h2 id = "sketch_hash" style="display:inline-block;"></h2>
      <br>
      <h2 style="display:inline-block;">WiFi Mode: </h2>
      <h2 id = "wifi_mode" style="display:inline-block;"></h2>
      <br>
      </div>
      </body>
        <script>
              var x = setInterval(function() {loadJSON('stats.json',updateJSON)}, 1000)
              function loadJSON(url, callback){
                var xhttp = new XMLHttpRequest()
                xhttp.onreadystatechange = function(){
                if(this.readyState == 4 && this.status == 200){
                    callback.apply(xhttp)
                  }
                };
                xhttp.open("GET", url, true)
                xhttp.send()
              }
              function updateJSON(){
                  console.log(this.responseText)
                  console.log('Test')
                  var statsObj = JSON.parse(this.responseText)
                  document.getElementById("chipID").innerHTML = statsObj.chipID
                  document.getElementById("mac_address").innerHTML = statsObj.mac_address
                  document.getElementById("sketch_hash").innerHTML = statsObj.sketch_hash
                  document.getElementById("wifi_mode").innerHTML = statsObj.wifi_mode
              }
              function myFunction() {
                var x = document.getElementById("centered_nav");
                if (x.className === "rc_nav") {
                    x.className += " responsive";
                } else {
                    x.className = "rc_nav";
                }
              }
      </script>
       <style>
            body {
              background-color: whitesmoke;
              font-family: 'Roboto', sans-serif;
            }
            .name {
              size: 4em;
              text-align: center;
            }
            .time-content {
              text-align: center;
            }
            .content {
              text-align: center;
            }
            .rc_nav {
              overflow: hidden;
              background-color: #363841;
              text-align: center;
              z-index: 6;
            }

            .rc_nav a {
             display: inline-block;
             margin-right: -4px;  /* inline-block gap fix */
             color: #fff;
             padding: 22px 22px;
             text-decoration: none;
             font-family: Poppins;
             font-size: 18px;
             -webkit-transition: background 0.3s linear;
             -moz-transition: background 0.3s linear;
             -ms-transition: background 0.3s linear;
             -o-transition: background 0.3s linear;
             transition: background 0.3s linear;
             z-index: 9;
            }

            .rc_nav a:hover {
              background-color: #575b69;
              color: #bdfe0e2;
            }

            .rc_nav .icon {
              display: none;
            }

            .rc_content {
              text-align: center;
              padding-left:14px;
              font-family: Poppins;
              margin-top: 100px;
              color: #8e909b;
            }


            @media screen and (max-width: 820px) {
              .rc_nav a {display: none;}
              .rc_nav a.icon {
                float: right;
                display: block;
                width: 60px;
              }
            }

            @media screen and (max-width: 820px) {
              .rc_nav.responsive {position: relative; top: 73px;}
              .rc_nav.responsive .icon {
                position: fixed;
                right: 0;
                top: 0;
              }
              .rc_nav.responsive a {
                float: none;
                display: block;
                text-align: center;
              }
            }
        </style>
  )=====";

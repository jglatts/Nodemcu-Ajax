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
        <ul>
            <li><a class="active" href="/" id="first-nav">Home</a></li>
            <li onclick="window.alert('BOARD: ESP8266')"><a>Board Info</a></li>
            <li onclick="updateStatsXML()"><a href="">Stats</a></li>
            <li onclick="window.alert('John Glatts 2019')"><a>About</a></li>
         </ul>
       <h1 class="content">Sensor to Node MCU Web Server</h1>
       <h1 class="content"><br><a href="Time">Time It</a></h1>
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
            .content {
              text-align: center;
            }
            #first-nav {
               margin-left: 37em;
            }
            ul {
              list-style-type: none;
              margin: 0;
              padding: 5px;
              overflow: hidden;
              background-color: #333;
            }

            li {
              float: left
            }

            li a {
              display: inline-block;
              color: white;
              text-align: center;
              padding: 14px 16px;
              text-decoration: none;
            }

            li a:hover {
              background-color: #111;
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
      <ul>
            <li><a class="active" href="/" id="first-nav">Home</a></li>
            <li onclick="window.alert('BOARD: ESP8266')"><a>Board Info</a></li>
            <li onclick="window.alert('STATS: EVERYTHING BE GUCCI')"><a href="Stats">Stats</a></li>
            <li onclick="window.alert('John Glatts 2019')"><a>About</a></li>
      </ul>
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
            #first-nav {
               margin-left: 37em;
            }
            ul {
              list-style-type: none;
              margin: 0;
              padding: 5px;
              overflow: hidden;
              background-color: #333;
            }

            li {
              float: left
            }

            li a {
              display: inline-block;
              color: white;
              text-align: center;
              padding: 14px 16px;
              text-decoration: none;
            }

            li a:hover {
              background-color: #111;
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
      <ul class = "topnav">
            <li><a class="active" href="/" id="first-nav">Home</a></li>
            <li onclick="window.alert('BOARD: ESP8266')"><a>Board Info</a></li>
            <li onclick="window.alert('STATS: EVERYTHING BE GUCCI')"><a href="Stats">Stats</a></li>
            <li onclick="window.alert('John Glatts 2019')"><a>About</a></li>
      </ul>
      <div class="time-content">
      <h1 style="display:inline-block;">Chip ID: </h1>
      <h1 id = "chipID" style="display:inline-block;"></h1>
      <br>
      <h1 style="display:inline-block;">MAC Address: </h1>
      <h1 id = "mac_address" style="display:inline-block;"></h1>
      <br>
      <h1 style="display:inline-block;">Sketch Hash: </h1>
      <h1 id = "sketch_hash" style="display:inline-block;"></h1>
      <br>
      <h1 style="display:inline-block;">WiFi Mode: </h1>
      <h1 id = "wifi_mode" style="display:inline-block;"></h1>
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
            ul {
              text-align: center;
              list-style-type: none;
              margin: 0;
              padding: 5px;
              overflow: hidden;
              background-color: #333;
            }

            li {
              text-align: center;
            }

            li a {
              text-align: center;
              color: white;
              text-align: center;
              padding: 14px 16px;
              text-decoration: none;
            }

            li a:hover {
              background-color: #111;
            }
            @media screen and (max-width: 600px) {
              ul.topnav li {float: none;}
            }
        </style>
  )=====";

/*
 * HTML Header file for nodemcu ajax sketch
 * Author: John Glatts
 * Date: 4/8/19
 * Use stats feature from ESP-DASH to display better stats
 *
 *    ToDo:
 *        - test if the one-time JSON 'GET' will work for about -- than transfer to the stats page
 *        - Add more fn's() and var's to the .h file
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
           <button class="content-buttons" id="button1"><a href="Time">Time It</a></button>
           <button class="content-buttons"><a href="MotorOn">Motor On</a></button>
           <button class="content-buttons"><a href="Pixel">Control Pixel</a></button>
           <button class="content-buttons"><a href="RFID">RFID Access</a></button>
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
                  margin-top: 1em;
                  margin-right: 14px;
                  padding: 20px;
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
// loads JSON in intervals, get the fn() to go the page just once
const char board_stats_page[] = R"=====(
            <script>
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
                      document.getElementById("local_ip").innerHTML = statsObj.local_ip
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
          <head>
           <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1.0">
           <title>JDG SERVER</title>
           <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
          </head>
          <body onload="loadJSON('stats.json', updateJSON)"
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
          <h2 style="display:inline-block;">Local IP: </h2>
          <h2 id = "local_ip" style="display:inline-block;"></h2></div>
          </body>
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


/* About Page
 *  - The JS works, only loads the JSON one time
 *  - Change some other pages to this JS style
 *
 */
const char board_about_page[] = R"=====(
            <script>
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
                      var aboutObj = JSON.parse(this.responseText)
                      document.getElementById("author").innerHTML = aboutObj.author
                      document.getElementById("created").innerHTML = aboutObj.created
                      document.getElementById("brief").innerHTML = aboutObj.brief
                      document.getElementById("version").innerHTML = aboutObj.version
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
          <head>
           <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1.0">
           <title>JDG SERVER</title>
           <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
          </head>
          <body onload="loadJSON('about.json', updateJSON)">
          <h1 class="name">JDG ESP SERVER</h1>
          <div class="rc_nav" id="centered_nav">
            <a href="/">Home</a>
            <a href="Stats">Board Stats</a>
            <a href="About">About</a>
            <a href="Reboot">Reboot</a>
            <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
          </div>
          <div class="time-content">
          <h2 style="display:inline-block;">Author: </h2>
          <h2 id = "author" style="display:inline-block;"></h2>
          <br>
          <h2 style="display:inline-block;">Date Created: </h2>
          <h2 id = "created" style="display:inline-block;"></h2>
          <br>
          <h2 style="display:inline-block;">Program Brief: </h2>
          <h2 id = "brief" style="display:inline-block;"></h2>
          <br>
          <h2 style="display:inline-block;">JDG-ESP Version: </h2>
          <h2 id = "version" style="display:inline-block;"></h2>
          <br>
          </body>
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


// Pixel control page -- send a color command to display on the Pixel
/*
 *  ToDo:
 *    - ATM, not working and not in use
 *    - Add pre-set values for color options
 *
 */
const char pixel_control_page[] = R"=====(
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
          <div id = "pix-command-wrapper">
            <h1>Enter A Number, (0 to 255), and Display on the Pixel!</h1>
            <form action = "/pixel-control.json">
            <p onclick="addPixelColor()"><input type="text" name="color" id="color_input"></input>
            </form>
          </div>
          <script>
            function addPixelColor() {
                var color_code = document.getElementById("color_input")
                var url = "data.txt"
                console.log(color_code)
            }
          </script>
          </body>
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

/*
 * RFID Module HTML/JS page
 *      - Displays current user and cards that are checked
 * */
const char rfid_page_html[] = R"=====(
            <script>
                  var x = setInterval(function() {loadData('RFID.json',updateData)}, 500)
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
                    var rfidObj = JSON.parse(this.responseText)
                      document.getElementById("user").innerHTML = rfidObj.user
                      document.getElementById("tag_card_id").innerHTML = rfidObj.tag_card_id
                  }
                  function resetUID(url_reset, callback_reset){
                    var xhttp_reset = new XMLHttpRequest()
                    xhttp_reset.onreadystatechange = function(){
                    if(this.readyState == 4 && this.status == 200){
                        callback.apply(xhttp_reset)
                      }
                    };
                    xhttp_reset.open("GET", url_reset, true)
                    xhttp_reset.send()
                  }
                  function resetCardUID(){
                      console.log(this.responseText)
                      console.log('Test')
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
           <div id="rfid-wrapper">
           <h1 class="content">Sensor to Node MCU Web Server</h1>
           <br>
           <h1 class="content" style="display:inline-block;">Current User: </h1>
           <h1 class="content" id="user" style="display:inline-block;"> </h1>
           <br>
           <h1 class="content" style="display:inline-block;">Card ID: </h1>
           <h1 class="content" id="tag_card_id" style="display:inline-block;"> </h1>
           <br>
           <button class="content" id="btn-content" style="display:inline-block;" onclick="resetUID('resetUID.json', resetCardUID)">Reset Card Reader</button>
           </div>
           </body>
              <style>
                body {
                  background-color: whitesmoke;
                  font-family: 'Roboto', sans-serif;
                }
                #user-title {
                  display: inline-block;
                  text-align: center;
                }
                #user {
                  display: inline-block;
                  text-align: center;
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
                #btn-content {
                  padding: 15px;
                }
                #all-buttons {
                    text-align: center;
                }
                #rfid-wrapper {
                    text-align: center;
                }
                .content-buttons {
                  margin-top: 1em;
                  margin-right: 14px;
                  padding: 20px;
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

  /*
   * HTML Header file for nodemcu ajax sketch
   * Author: John Glatts
   * Date: 4/8/19
   *
   */
  
  
  const char page[] = R"=====(
       <h1>Sensor to Node MCU Web Server</h1>
       <h1><br><a href="Time">Time It</a></h1>
        <script>
              var x = setInterval(function() {loadData("data.txt",updateData)}, 1000)
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
  )=====";
  
  
  // elapsed time page
  const char time_page[] = R"=====(
      <h1>Sensor to Node MCU Web Server</h1>
      <h1 style="display:inline;">Elapsed Time: </h1><h1 id="mins" style="display:inline;"></h1><h1 style="display:inline;"> mins </h1>
      <h1 style="display:inline;"> and </h1><h1 id="secs" style="display:inline;"></h1>
      <h1 style="display:inline;"> secs. </h1>
      <script>
          var x = setInterval(function() {loadTime("time.txt",updateTime)}, 1000)
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
  )=====";

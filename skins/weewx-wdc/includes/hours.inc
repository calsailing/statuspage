<div class="bx--tile tile-hours">
    
    <style>
    table#hours{
    width:100%;
    
    }
    table#hours th{
    font-weight:600;
    }
    table#hours td,table#hours th{
    text-align:left;
    padding-bottom:3px;
    padding-top:3px;
    padding-left:10px;
    padding-right:10px;
    width:20%;
    }
    </style>
    
    <table id="hours">

</table>
    
    <script>
    var url = "https://www.cal-sailing.org/index.php?option=com_csctides&view=gettidedatalist&task=gettidedatalist&tmpl=component&output=json&random="+Math.random()* 100000000000000000000;

var xmlHttp = new XMLHttpRequest();
xmlHttp.onreadystatechange = function() {
  if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
    var hours = JSON.parse(xmlHttp.responseText);
    
    
        
        try { 

        //club closed
        if (hours["data"].clubclosed == true){
            document.getElementById('hours').innerHTML = "<tr><td><h5><a href='https://www.cal-sailing.org/resources/csc-openclose-times?view=month'>Club Hours</a></h5>"+hours.data["date"]+"</td><td style='background-color:hsla(358, 100%, 82%, 1);'>Club is closed due to tides unless announced otherwise on the Whiteboard.</td></tr>";
        } else {
    
        //no restrictions
        if (hours.data.clubclosed == false){
            document.getElementById('hours').innerHTML = "<tr><th><h5><a href='https://www.cal-sailing.org/resources/csc-openclose-times?view=month'>Club Hours</a></h5></th><th>Open Time</th><th>Dock Time</th><th>Sunset</th></tr><tr><td>"+hours.data["date"]+"</td><td>"+hours.data["opentime"]+"</td><td>"+hours.data["docktime"]+"</td><td>"+hours.data["sunsettime"]+"</td></tr>";
        }
        //early close
            if (hours.data["restriction"] == "EARLY CLOSE"){
            document.getElementById('hours').innerHTML = "<tr><th><h5><a href='https://www.cal-sailing.org/resources/csc-openclose-times?view=month'>Club Hours</a></h5></th><th>Open Time</th><th>Dock Time</th><th>Sunset</th></tr><tr><td>"+hours.data["date"]+"</td><td>"+hours.data["opentime"]+"</td><td style='background-color:hsla(358, 100%, 82%, 1)'>Early Close: "+hours.data["docktime"]+"</td><td>"+hours.data["sunsettime"]+"</td></tr>";
        }
        // late open
        if (hours.data["restriction"] == "LATE OPEN"){
            document.getElementById('hours').innerHTML = "<tr><th><h5><a href='https://www.cal-sailing.org/resources/csc-openclose-times?view=month'>Club Hours</a></h5></th><th>Open Time</th><th>Dock Time</th><th>Sunset</th></tr><tr><td>"+hours.data["date"]+"</td><td style='background-color:hsla(358, 100%, 82%, 1);'>Late Open: "+hours.data["opentime"]+"</td><td>"+hours.data["docktime"]+"</td><td>"+hours.data["sunsettime"]+"</td></tr>";
        }
        // mid-day close
        if (hours.data["restriction"] == "MID-DAY CLOSE"){
            document.getElementById('hours').innerHTML = "<tr><th><h5><a href='https://www.cal-sailing.org/resources/csc-openclose-times?view=month'>Club Hours</a></h5></th><th>Open Time</th><th></th><th>Dock Time</th><th>Sunset</th></tr><tr><td>"+hours.data["date"]+"</td><td>"+hours.data["opentime"]+"</td><td style='background-color:hsla(358, 100%, 82%, 1);'>"+hours.data["middayclosetext"]+"</td><td>"+hours.data["docktime"]+"</td><td>"+hours.data["sunsettime"]+"<td></td>";
        }
        
        }
        
        } catch (error) {
    
  }
    
    
}

xmlHttp.open("GET", url, true);
xmlHttp.send();
    </script>
    
    
    
   
    
     </div>
          <br/><br/>
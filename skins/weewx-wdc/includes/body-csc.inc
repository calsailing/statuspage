<!--prettier-ignore-->
#errorCatcher Echo
#encoding UTF-8
#from datetime import datetime, timedelta

#set $diagrams_config = $DisplayOptions.get("diagrams", {})
#set global $layout = 'alternative'
#set $gauges_display = $DisplayOptions.get('gauges_display', 'before')
#set $show_gauges = 'Gauges' in $DisplayOptions and $context in $DisplayOptions['Gauges']


<link rel="stylesheet" href="https://cdn.aerisapi.com/wxblox/latest/aeris-wxblox.css">
<script src="https://cdn.aerisapi.com/wxblox/latest/aeris-wxblox.js"></script>
 
<style>
.advisories{
margin-top:0px!important;
padding-top:10px!important;
background-color: rgb(254, 215, 215)!important;
border:solid 1px rgb(197, 31, 31)!important;
color:hsl(116,0%,20%)!important;
}
.advisories a{
color:hsl(116,0%,20%)!important;
}
</style> 
 
<div id="wxblox" class="aeris-wrapper"></div>
 
<script>    
const aeris = new AerisWeather('6mHXhibAPUlZfTTiuE5r1', 'FJsUv4NWSB2DcjaJARF23g6LNuEBWAcBezqh9bt0');
aeris.on('ready', () => {
    var view = new aeris.wxblox.views.Advisories('#wxblox', {
    fullDetails: false
});
view.load({
    p: "37.86,-122.31"
});
});
</script>

<style>
.gauge-label
{font-family:"IBM Plex Sans"!important;
}
.gauge-text text{font-family:"IBM Plex Sans"!important;}

@media only screen and (min-device-width : 320px) and (max-device-width : 480px)  { 
.gauge-text{font-size:70%;font-weight:300!important;font-family:"IBM Plex Sans"!important;}
.gauge-text text{font-family:"IBM Plex Sans"!important;}
.gauge-label
{font-family:"IBM Plex Sans"!important;
}
}
</style>

<div class="bx--row">
  <div class="bx--col">
    <div class="bx--row">
<div class="bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-8">




#def render_gauges($gauge_config)
  #set $gauges_index = 0
  #for $gauge_obs in $gauge_config
    #set $gauge_obs_data_binding = $get_data_binding($gauge_obs)

    ## I dont know why but $alltime($data_binding=$skin_obs_binding) crashes on the month-%Y-%m and year-%Y pages:
    ## ValueError: start time (1654034700) is greater than stop time (1640991600)
    #set $alltime_tag = None if $use_parameter_year or $use_parameter_month else $alltime($data_binding=$gauge_obs_data_binding)
    #set global $gauge_obs_binding = $getattr($get_time_span_from_context($context, $day($data_binding=$gauge_obs_data_binding), $week($data_binding=$gauge_obs_data_binding), $month($data_binding=$gauge_obs_data_binding), $year($data_binding=$gauge_obs_data_binding), $alltime_tag, $yesterday($data_binding=$gauge_obs_data_binding)), $get_custom_data_binding_obs_key($gauge_obs))

    #if $gauge_obs_binding.has_data
      #set global $gauges_index = $gauges_index
      #set global $partial_obs = $gauge_obs
      #include "includes/gauge-tile.inc"
      #set $gauges_index = $gauges_index + 1
    #end if
  #end for
#end def

#set $stat_tiles_xaggs_same_row = []
#set $stat_tiles_xaggs_extra_row = []
#if 'stat_tiles_xaggs' in $DisplayOptions
  #set $stat_tiles_xaggs = $DisplayOptions.stat_tiles_xaggs

  #for $xaggs in $stat_tiles_xaggs
    #if $context != "day" and ('avg_context' not in $stat_tiles_xaggs[$xaggs] or $context not in $stat_tiles_xaggs[$xaggs]['avg_context'])
      #continue
    #end if

    #set $xaggs_to_append = {'obs': $xaggs, **$stat_tiles_xaggs[$xaggs]}

    #if $context == "day"
      #silent $xaggs_to_append['aggregate_types'] = $list(filter(lambda aggregate_type: 'historical' in aggregate_type, $xaggs_to_append['aggregate_types']))
    #else
      #silent $xaggs_to_append['aggregate_types'] = $list(filter(lambda aggregate_type: 'historical' not in aggregate_type, $xaggs_to_append['aggregate_types']))
    #end if

    #if $to_bool($stat_tiles_xaggs[$xaggs]['show_extra_row']) is True
      #silent $stat_tiles_xaggs_extra_row.append($xaggs_to_append)
    #else
      #silent $stat_tiles_xaggs_same_row.append($xaggs_to_append)
    #end if
  #end for
#end if





<!--prettier-ignore-->
#if $show_gauges and $gauges_display == 'before'
<!--prettier-ignore-->
<div class="bx--row">
$render_gauges($DisplayOptions['Gauges'][$context])
</div>
#end if

<div class="bx--row">

  <!--prettier-ignore-->
  #for $skin_obs in $DisplayOptions.get('stat_tile_observations')
    #if $skin_obs == 'windSpeed' or $skin_obs == 'windGust'
      #set $skin_obs_binding = $get_data_binding($skin_obs)

      #set $show_sum = $get_show_sum($skin_obs)
      #set $show_min = $get_show_min($skin_obs)
      #set $show_max = $get_show_max($skin_obs)
      #set $use_day = $show_sum or $show_min or $show_max

      ## I dont know why but $alltime($data_binding=$skin_obs_binding) crashes on the month-%Y-%m and year-%Y pages:
      ## ValueError: start time (1654034700) is greater than stop time (1640991600)
      #set $alltime_tag = $alltime($data_binding=$skin_obs_binding) if $context == 'alltime' else None

      #if $context == 'day' and not $daily_archive and $use_day
        #set $stat_tile_check = $day
      #elif $context == 'day' and not $daily_archive and not $use_day
        #set $stat_tile_check = $current
      #else
        #set $stat_tile_check = $get_time_span_from_context($context, $day($data_binding=$skin_obs_binding), $week($data_binding=$skin_obs_binding), $month($data_binding=$skin_obs_binding), $year($data_binding=$skin_obs_binding), $alltime_tag, $yesterday($data_binding=$skin_obs_binding))
      #end if

      #if $getattr($stat_tile_check, $get_custom_data_binding_obs_key($skin_obs)).has_data
        #set global $partial_obs = $skin_obs
       #if $context != "day"
        #include "includes/stat-tile.inc"
       #end if


      #end if
    #end if
  #end for

  <!--prettier-ignore-->
  #if $stat_tiles_xaggs_same_row
    #set global $hide_xaggs_heading = False
    #for $stat_xaggs in $stat_tiles_xaggs_same_row
      #set global $stat_xaggs = $stat_xaggs
      #include "includes/stat-tile-xaggs.inc"
    #end for
  #end if
</div>


<!--prettier-ignore-->
#if $show_gauges and $gauges_display == 'after'
<!--prettier-ignore-->
<div class="bx--row">
$render_gauges($DisplayOptions['Gauges'][$context])
</div>
#end if

<!--prettier-ignore-->
#if $stat_tiles_xaggs_extra_row
#set global $hide_xaggs_heading = True
<!--prettier-ignore-->
<header class="bx--col section-header">
  #if $context == 'day'
  <h2>$gettext("Historical values for today")</h2>
  #else
  <h2>$gettext("Historical values")</h2>
  #end if
</header>
<!--prettier-ignore-->
<div class="bx--row">
  #for $stat_xaggs in $stat_tiles_xaggs_extra_row
    #set global $stat_xaggs = $stat_xaggs
    #include "includes/stat-tile-xaggs.inc"
  #end for
</div>
#end if


<!--prettier-ignore-->
<div class="bx--row">
  #include "includes/section-heading.inc"
</div>


<!-- prettier-ignore -->

<div class="bx--row">
#set $diagram_index = 0
#set $context_for_diagrams = $context if $context != 'yesterday' else 'day'
#set $diagram_context_config = $DisplayOptions.get("diagrams", {}).get($context_for_diagrams, {}).get('observations', {})
#if "combined_observations" in $diagrams_config
  #set $combined = $diagrams_config.combined_observations
#else
  #set $combined = {}
#end if

#for $skin_obs in $diagram_context_config
  #if $skin_obs in $combined.keys()
    #set $combined_diagram = $combined[$skin_obs]
    #for $combined_obs in $combined_diagram.obs.keys()
      #set $skin_obs_binding = $get_data_binding_combined_diagram($combined_obs, $combined_diagram, $skin_obs, $context)

      ## I dont know why but $alltime($data_binding=$skin_obs_binding) crashes on the month-%Y-%m and year-%Y pages:
      ## ValueError: start time (1654034700) is greater than stop time (1640991600)
      #set $alltime_tag = $alltime($data_binding=$skin_obs_binding) if $context == 'alltime' else None

      #if $getattr($get_time_span_from_context($context, $day($data_binding=$skin_obs_binding), $week($data_binding=$skin_obs_binding), $month($data_binding=$skin_obs_binding), $year($data_binding=$skin_obs_binding), $alltime_tag, $yesterday($data_binding=$skin_obs_binding)), $get_custom_data_binding_obs_key($combined_diagram.obs[$combined_obs].observation)).has_data or $combined_diagram.obs[$combined_obs].observation in $get_software_obs
        #set global $comb_obs = $skin_obs
        #set global $combined_diagram = $combined_diagram
        #set global $diagram_index = $diagram_index
        #include "includes/combined-diagram-tile.inc"
        #set $diagram_index = $diagram_index + 1
        #break
      #end if
    #end for
  #else
    #set $skin_obs_binding = $get_data_binding($skin_obs, $context)
    #set $alltime_tag = $alltime($data_binding=$skin_obs_binding) if $context == 'alltime' else None
    #if $getattr($get_time_span_from_context($context, $day($data_binding=$skin_obs_binding), $week($data_binding=$skin_obs_binding), $month($data_binding=$skin_obs_binding), $year($data_binding=$skin_obs_binding), $alltime_tag, $yesterday($data_binding=$skin_obs_binding)), $get_custom_data_binding_obs_key($skin_obs)).has_data or (($skin_obs == 'windDir' or $skin_obs == 'windRose') and $getattr($get_time_span_from_context($context, $day, $week, $month, $year, $alltime, $yesterday), 'windSpeed').has_data or $skin_obs in $get_software_obs)
      #set global $partial_obs = $skin_obs
      #set global $diagram_index = $diagram_index
      #if $skin_obs == 'windRose'
        #include "includes/diagram-tile-wind-rose.inc"
      #else
        #include "includes/diagram-tile.inc"
      #end if
      #set $diagram_index = $diagram_index + 1
    #end if
  #end if
#end for



</div>

<!--prettier-ignore-->
#if $context == "day" and $daily_archive == False
#include "includes/forecast.inc"
#end if
</div>




#set $warn_region_front = $Extras['weewx-DWD']['show_warnings_on_front'] if 'weewx-DWD' in $Extras and 'show_warnings_on_front' in $Extras['weewx-DWD'] else False
#set $show_warn = True if $warn_region_front and $dwd_warning_has_warning($warn_region_front) else False


#set $externals_list = []
#if 'externals' in $Extras and $len($Extras['externals']) > 0
  #for $external in $Extras['externals']
    #if $external == 'description'
      #continue
    #end if
    #if $to_bool($Extras['externals'][$external].show_on_front)
      #silent $externals_list.append($external)
    #end if
  #end for
#end if

#set $radar_externals = 'radar_html' in $Extras or $len($externals_list) > 0

#set $radar_externals_list = $externals_list
#if 'radar_html' in $Extras
  #set $radar_externals_list = ['radar'] + $externals_list
#end if


<!--prettier-ignore-->
      #if $radar_externals or $show_warn
      #set radar_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-4"
      #if 'forecast_radar_equal_width' in $Extras and $to_bool($Extras.forecast_radar_equal_width) and $DisplayOptions.get('layout', 'alternative') == 'alternative'
        #set radar_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-6"
      #end if
      #if $DisplayOptions.get('layout', 'alternative') == 'classic'
        #set radar_classes = "bx--col-sm-4 bx--col-md-12 bx--col-lg-12 bx--col-xlg-12 bx--col-max-12"
      #end if

      <!--prettier-ignore-->
      <div class="$radar_classes radar-container">
        #if $show_warn
          #set global $region = $get_dwd_warning_region_name($warn_region_front)
          #set global $region_key = $warn_region_front
          #include "includes/dwd-warning.inc"
        #end if

        #if $radar_externals
        
        <style>
          .radar-container .bx-ce-demo-devenv--tab-panels > div {
            padding-bottom: 1rem;
          }
          .radar-container .bx-ce-demo-devenv--tab-panels > div > .bx--tile {
            padding: 0;
          }
        </style>

        #if len($radar_externals_list) == 1
          <style>
            .radar-container .bx-ce-demo-devenv--tab-panels .bx--tile {
              padding: 0;
            }
          </style>
        #end if

   
   
   
    <h3><strong>Hours, Tides & Webcams</strong></h3><br/>
   
    #include "includes/hours.inc"
    
    
	<div class="bx--tile tile-radar-forecast">
<h5><strong><a href="https://tidesandcurrents.noaa.gov/noaatidepredictions.html?id=9414816">Today's Tides</a></strong></h5>
                 
		<img id="cscimage1" src="https://www.cal-sailing.org/components/com_cscupload/assets/uploads/wind_0.svg" />
 		<script>document.getElementById("cscimage1").src=document.getElementById("cscimage1").src + "?" + Math.random()* 100000000000000000000;</script>

<style>
    table#tidestext{
    width:100%;
    
    }

    table#tidestext td{
    text-align:center;
    padding:5px;
    width:25%;
    
    }
    
    
    @media only screen and (min-device-width : 320px) and (max-device-width : 480px)  { 
table#tidestext{
    width:100%;
    
    }
}}
    
    </style>

<table id="tidestext">
    </table>

<script>
    
    Date.prototype.yyyymmdd = function() {
  var mm = this.getMonth() + 1; // getMonth() is zero-based
  var dd = this.getDate();

  return [this.getFullYear(),
          (mm>9 ? '' : '0') + mm,
          (dd>9 ? '' : '0') + dd
         ].join('');
};

var date = new Date();

    var url = "https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=predictions&application=NOS.COOPS.TAC.WL&begin_date="+date.yyyymmdd()+"&end_date="+date.yyyymmdd()+"&datum=MLLW&station=9414816&time_zone=lst_ldt&units=english&interval=hilo&format=json";

var xmlHttp2 = new XMLHttpRequest();
xmlHttp2.onreadystatechange = function() {
  if (xmlHttp2.readyState == 4 && xmlHttp2.status == 200)
    var tides = JSON.parse(xmlHttp2.responseText);
    
    try {

     if (typeof tides.predictions[3] == "undefined" ){
    document.getElementById('tidestext').innerHTML = "<tr><td>"+tides.predictions[0]["t"].substring(11)+" "+tides.predictions[0]["type"]+" "+Number(tides.predictions[0]["v"]).toFixed(1)+" ft</td>"+"<td>"+tides.predictions[1]["t"].substring(11)+" "+tides.predictions[1]["type"]+" "+Number(tides.predictions[1]["v"]).toFixed(1)+" ft</td>"+"<td>"+tides.predictions[2]["t"].substring(11)+" "+tides.predictions[2]["type"]+" "+Number(tides.predictions[2]["v"]).toFixed(1)+" ft</td></tr>";
    }

    if (typeof tides.predictions[3] != "undefined" ){
    document.getElementById('tidestext').innerHTML = "<tr><td>"+tides.predictions[0]["t"].substring(11)+" "+tides.predictions[0]["type"]+" "+Number(tides.predictions[0]["v"]).toFixed(1)+" ft</td>"+"<td>"+tides.predictions[1]["t"].substring(11)+" "+tides.predictions[1]["type"]+" "+Number(tides.predictions[1]["v"]).toFixed(1)+" ft</td>"+"<td>"+tides.predictions[2]["t"].substring(11)+" "+tides.predictions[2]["type"]+" "+Number(tides.predictions[2]["v"]).toFixed(1)+" ft</td>"+"<td>"+tides.predictions[3]["t"].substring(11)+" "+tides.predictions[3]["type"]+" "+Number(tides.predictions[3]["v"]).toFixed(1)+" ft</td></tr>";
    }
    
    } catch (error) {
    
  }
        
    
    
}
xmlHttp2.open("GET", url, true);
xmlHttp2.send();
    </script>

                </div><br/><br/>
                
                
                
                
                

        #if len($radar_externals_list) > 1
        <bx-tabs trigger-content="Select an item" value="$radar_externals_list[0]" type="container">
          #if 'radar_html' in $Extras
          <bx-tab id="tab-radar" target="panel-radar" value="radar">
            $gettext("Recent radar")
          </bx-tab>
          #end if

          #if len($externals_list) > 0
            #for $external in $externals_list
              <bx-tab id="tab-$external" target="panel-$external" value="$external">
                $Extras['externals'][$external].title
              </bx-tab>
            #end for
          #end if
        </bx-tabs>
        #end if
        <div class="bx-ce-demo-devenv--tab-panels">
          #if 'radar_html' in $Extras
          <div id="panel-radar" role="tabpanel" aria-labelledby="tab-radar">
            <div class="bx--tile tile-radar-forecast">
              $Extras.radar_html
            </div>
          </div>
          #end if

          #if len($externals_list) > 0
            #for $external in $externals_list
              <div id="panel-$external" role="tabpanel" aria-labelledby="tab-$external">
                <div class="bx--tile tile-radar-forecast">
                  $Extras['externals'][$external].source
                  <p class="bx--type-caption-01" style="margin-top: 0.25rem;">$Extras['externals'][$external].title_long</p>
                </div>
              </div>
            #end for
          #end if
        </div>


    <h3><strong>Cal Sailing Club on various Weather Services</strong></h3><br/><br/>
	<div class="bx--tile tile-radar-forecast">
    
    <a target="_blank" href="https://tempestwx.com/station/127241/grid">Tempest (Real-time from our Weather Station)</a><br><br>
    <a target="_blank" href="https://www.sailflow.com/spot/624475">Sailflow </a><br><br>
   <a target="_blank" href="https://wx.iwindsurf.com/spot/624475">iWindsurf</a><br><br>
   <a target="_blank" href="https://www.windalert.com/spot/624475">WindAlert</a><br><br>
    <a target="_blank" href="https://www.pwsweather.com/station/pws/calsailingclub">PWS Weather</a><br><br>
   <a target="_blank" href="https://www.windy.com/station/pws-f07682d7">Windy</a><br><br>
    <a target="_blank" href="https://www.wunderground.com/dashboard/pws/KCABERKE302">Weather Underground</a>
    
    
    </div>

        #end if
      </div>
      #end if
    </div>
  </div>
</div>





<br/><br/>

#if 'table_tile_observations' in $DisplayOptions
<div class="bx--row">
  <!-- prettier-ignore -->
  #set global $table_obs = None
  #include "includes/data-table-tile.inc"
</div>
#end if

#errorCatcher Echo
#encoding UTF-8
#set diagram_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-6"
#if $DisplayOptions.get('layout', 'alternative') == 'classic'
  #set diagram_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-6"
#end if

<div class="$diagram_classes">
  <div class="bx--tile diagram-tile" data-test="windrose">
    <div class="bx--row">
      <div class="bx--col">
        <p class="label">
          #set $icon = $get_icon("windDir", $use_diagram_config=True, $context=$context)
          #if $icon != 'none' and "includes/icons/" in $icon and '.svg' in $icon
            #include $icon
          #elif $icon != 'none' and "includes/icons/" not in $icon
            <img src="$icon" alt="$obs.label['windDir']" />
          #end if
          $obs.label["windDir"]
        </p>
        <div class="value">
          #set $series_name = $partial_obs + 'Series' + str($diagram_index)

          #if $context == 'month' and $use_parameter_month
          <script>
            var $series_name = $get_windrose_data($month.start.raw, $month.end.raw, $context)
          </script>
          #else if $context == 'year' and $use_parameter_year
          <script>
            var $series_name = $get_windrose_data($year.start.raw, $year.end.raw, $context)
          </script>
          #else
          <script>
            #set $time_span = $get_time_span_from_context($context, $day, $week, $month, $year, $alltime, $yesterday)
            var $series_name = $get_windrose_data($time_span.start.raw, $time_span.end.raw, $context)
          </script>
          #end if

          <div
            class="diagram plotly windrose"
            data-labels="['$obs.label[$partial_obs]']"
            data-color="['$get_color($partial_obs, $context)']"
            data-value="$series_name"
            data-unit="$getattr($unit.label, 'windSpeed')"
            data-obs="$partial_obs"
            data-diagram="$get_diagram($partial_obs, $context)"
            data-context="$context"
            data-aggregate-type="['$get_aggregate_type($partial_obs, $context)']"
            data-nivo-props="$get_diagram_props($partial_obs, $context)"
            data-show-legend-unit="$DisplayOptions.get('windRose_legend_show_units', False)"
            data-show-beaufort="$DisplayOptions.get('windRose_show_beaufort', True)"
          ></div>
        </div>
      </div>
    </div>
  </div>
</div>
<!--prettier-ignore-->
#errorCatcher Echo
#encoding UTF-8
#set diagram_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-6"
#if $DisplayOptions.get('layout', 'alternative') == 'classic'
  #set diagram_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-6"
#end if
#set $partial_obs_key = $get_custom_data_binding_obs_key($partial_obs)

#set $diagram_props = $get_diagram_props($partial_obs, $context)

<div class="$diagram_classes">
  <div class="bx--tile diagram-tile" data-test="$partial_obs">
    <div class="bx--row">
      <div class="bx--col">
        <!--prettier-ignore-->
        <p class="label">
          #set $icon = $get_icon($partial_obs_key, $use_diagram_config=True, $context=$context)
          #if $icon != 'none' and "includes/icons/" in $icon and '.svg' in $icon
            #include $icon
          #elif $icon != 'none' and "includes/icons/" not in $icon
            <img src="$icon" alt="$obs.label[$partial_obs]" />
          #end if
          $obs.label[$partial_obs]
        </p>
        <div class="value">
          <!--prettier-ignore-->
          #set $series_name = $partial_obs + 'Series' + str($diagram_index)
          #set $partial_obs_binding = $get_data_binding($partial_obs, $context)

          <!--TODO: Implement custom context logic from combined-diagram-tile template-->
          <!--prettier-ignore-->
          #if $context == 'month' and $use_parameter_month
            #set $obs_context = $month($data_binding=$partial_obs_binding)
          #else if $context == 'year' and $use_parameter_year
            #set $obs_context = $year($data_binding=$partial_obs_binding)
          #else if $context == 'alltime'
            #set $obs_context = $alltime($data_binding=$partial_obs_binding)
          #else if $context == 'yesterday'
            #set $obs_context = $yesterday($data_binding=$partial_obs_binding)
          #else if $context == 'day' and $daily_archive == False
            #set $obs_context = $span($data_binding=$partial_obs_binding, $hour_delta=$get_hour_delta($context)-12, $boundary=$get_diagram_boundary($context))
          #else
            #set $obs_context = $span($data_binding=$partial_obs_binding, $hour_delta=$get_hour_delta($context), $boundary=$get_diagram_boundary($context))
          #end if

          <script>
            /* prettier-ignore */
            var $series_name = $get_diagram_data($observation=$partial_obs, $observation_key=$partial_obs_key, $context_key=$context, $start_ts=$obs_context.start.raw, $end_ts=$obs_context.end.raw, $data_binding=$partial_obs_binding, $alltime_start=$alltime.start.format('%d.%m.%Y'), alltime_end=$alltime.end.format('%d.%m.%Y'));
          </script>

          <!--prettier-ignore-->
          <div
            class="diagram"
            data-labels="['$obs.label[$partial_obs]']"
            data-color="['$get_color($partial_obs, $context)']"
            data-value="$series_name"
            data-unit="['$get_unit_label($get_unit_for_obs($partial_obs, $partial_obs_key, $context))']"
            data-observations="['$partial_obs']"
            ## Not used, just for consistency with combined-diagram-tile template
            data-combinedkeys="['$partial_obs']"
            data-diagram="['$get_diagram($partial_obs, $context)']"
            data-context="$context"
            data-aggregate-type="['$get_aggregate_type($partial_obs, $context)']"
            data-nivo-props="$diagram_props"
          ></div>
        </div>
      </div>
    </div>
  </div>
</div>

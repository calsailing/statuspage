<script src="https://d3js.org/d3.v7.min.js"></script>
<script src="https://cdn.tailwindcss.com"></script>
<script>
/* #raw */
    tailwind.config = {
            darkMode: 'media',
            theme: {
                extend: {
                    animation: {
                        'float': 'float 4s ease-in-out infinite',
                        'spin-slow': 'spin 4s linear infinite',
                    },
                    keyframes: {
                        float: {
                            '0%, 100%': { transform: 'translateY(0)' },
                            '50%': { transform: 'translateY(-4px)' },
                        }
                    }
                }
            }
        }
/* #end raw */
</script>
<style>
    @import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700;800;900&display=swap');
        
        #isolated-weather-widget {
            font-family: 'Inter', sans-serif;
            --bg-color: #ffffff;
            --card-bg: #ffffff;
            --card-border: #e2e8f0;
            --text-primary: #0f172a;
            --text-secondary: #94a3b8;
            --text-muted: #475569;
            --dial-tick: #cbd5e1;
            --dial-tick-major: #94a3b8;
            --track-bg: #f1f5f9; 
            --temp-color: #ef4444;
            --bubble-bg: #f1f5f9;
            --grey-tick: #cbd5e1; 
        }

        @media (prefers-color-scheme: dark) {
            #isolated-weather-widget {
                --bg-color: #0f172a;
                --card-bg: #1e293b;
                --card-border: #334155;
                --text-primary: #f8fafc;
                --text-secondary: #cbd5e1;
                --text-muted: #94a3b8;
                --dial-tick: #334155;
                --dial-tick-major: #475569;
                --track-bg: #1e293b;
                --bubble-bg: #334155;
                --grey-tick: #475569;
            }
        }

        /* D3 Gauge specific styles scoped to widget */
        #isolated-weather-widget .center-speed {
            font-size: 32px;
            font-weight: 800;
            fill: #0f172a;
            letter-spacing: -1px;
        }

        #isolated-weather-widget .center-gust {
            font-size: 14px;
            font-weight: 700;
            fill: #0f172a;
            letter-spacing: 0;
        }

        #isolated-weather-widget .speed-tick {
            stroke: rgba(128, 128, 128, 0.3);
            stroke-width: 1.5;
            stroke-linecap: round;
            pointer-events: none;
        }

        #isolated-weather-widget .gauge-label {
            font-size: 10px;
            font-weight: 300; 
            fill: var(--text-muted); 
        }
    </style>

    <!-- Instrument Panel Container (Isolated & Responsive) -->
    <div id="isolated-weather-widget" class="flex flex-col md:flex-row gap-6 p-2 w-full">
        
        <!-- Column 1: Live Wind Dial -->
        <div class="relative flex-1 w-full bg-white dark:bg-slate-800 p-1 shadow-sm border border-slate-100 dark:border-slate-700/50 overflow-hidden flex flex-col items-center justify-center">
            <div id="gauge-mount" class="relative w-full h-full flex justify-center items-center"></div>
        </div>

        <!-- Column 2: Weather Dashboard (New Design) -->
        <div class="relative flex-1 w-full flex flex-col font-sans text-slate-800 dark:text-slate-100">
            <div class="grid grid-cols-2 gap-3 flex-grow w-full h-full">
                
                <!-- HERO CARD: Temperature & Condition (Spans 2 columns) -->
                <div class="col-span-2 bg-gradient-to-br from-blue-50 to-slate-50 dark:from-slate-800 dark:to-slate-800/50 p-4 shadow-sm border border-white/60 dark:border-slate-700/50 hover:shadow-md transition-all duration-300 group flex flex-col justify-center">
                    <div class="flex justify-between items-center px-2">
                        <!-- Left: Temperature -->
                        <div class="flex flex-col">
                            <div class="flex items-center gap-1.5 mb-1 text-slate-500 dark:text-slate-400">
                                <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-3.5 h-3.5 text-blue-500"><path d="M14 14.76V3.5a2.5 2.5 0 0 0-5 0v11.26a4.5 4.5 0 1 0 5 0z"/></svg>
                                <span class="text-[10px] font-semibold uppercase tracking-wider">Current</span>
                            </div>
                            <div class="flex items-baseline gap-1">
                                <!-- ID: val-temp-f -->
                                <h1 id="val-temp-f" class="text-4xl font-bold tracking-tighter text-slate-800 dark:text-white transition-opacity duration-300">--&deg;F</h1>
                            </div>
                            <!-- ID: val-temp-c -->
                            <p id="val-temp-c" class="text-slate-500 dark:text-slate-400 font-medium mt-0.5 text-sm transition-opacity duration-300">--&deg;C</p>
                        </div>

                        <!-- Right: Condition -->
                        <div class="flex flex-col items-center justify-center pt-1">
                            <!-- ID: icon-weather -->
                            <div id="icon-weather" class="w-12 h-12 text-slate-700 dark:text-slate-300 animate-float drop-shadow-sm flex items-center justify-center transition-all duration-300">
                                <!-- Default loading icon -->
                                <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full opacity-50"><path d="M12 2v4"/><path d="M12 18v4"/><path d="M4.93 4.93l2.83 2.83"/><path d="M16.24 16.24l2.83 2.83"/><path d="M2 12h4"/><path d="M18 12h4"/><path d="M4.93 19.07l2.83-2.83"/><path d="M16.24 7.76l2.83-2.83"/></svg>
                            </div>
                            <!-- ID: val-conditions -->
                            <p id="val-conditions" class="font-semibold text-slate-700 dark:text-slate-300 mt-2 text-sm text-center leading-tight transition-opacity duration-300">Loading...</p>
                        </div>
                    </div>
                </div>

                <!-- CARD 2: Pressure -->
                <div class="col-span-1 bg-white dark:bg-slate-800 p-4 shadow-sm border border-slate-100 dark:border-slate-700/50 hover:shadow-md hover:-translate-y-1 transition-all duration-300">
                    <div class="flex flex-col h-full justify-between">
                        <div class="flex items-center justify-between mb-2">
                            <div class="w-7 h-7 bg-indigo-50 dark:bg-indigo-500/10 flex items-center justify-center">
                                <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-3.5 h-3.5 text-indigo-500 dark:text-indigo-400"><path d="m12 14 4-4"/><path d="M3.34 19a10 10 0 1 1 17.32 0"/></svg>
                            </div>
                        </div>
                        
                        <div>
                            <!-- ID: val-pressure -->
                            <h2 id="val-pressure" class="text-2xl font-bold tracking-tight text-slate-800 dark:text-white transition-opacity duration-300">--</h2>
                            <p class="text-[10px] font-semibold text-slate-400 dark:text-slate-500 uppercase tracking-wider mt-0.5">Pressure (mb)</p>
                        </div>

                        <!-- ID: val-pressure-trend -->
                        <div id="val-pressure-trend" class="mt-2 flex items-center gap-1.5 text-xs font-medium text-slate-500 dark:text-slate-400 bg-slate-50 dark:bg-slate-900/50 w-fit px-2 py-0.5 min-h-[24px]">
                            <!-- Trend injected via JS -->
                        </div>
                    </div>
                </div>

                <!-- CARD 3: UV Index -->
                <div class="col-span-1 bg-white dark:bg-slate-800 p-4 shadow-sm border border-slate-100 dark:border-slate-700/50 hover:shadow-md hover:-translate-y-1 transition-all duration-300">
                    <div class="flex flex-col h-full justify-between">
                        <div class="flex items-center justify-between mb-2">
                            <div class="w-7 h-7 bg-amber-50 dark:bg-amber-500/10 flex items-center justify-center">
                                <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-3.5 h-3.5 text-amber-500 dark:text-amber-400 group-hover:animate-spin-slow"><circle cx="12" cy="12" r="4"/><path d="M12 2v2"/><path d="M12 20v2"/><path d="m4.93 4.93 1.41 1.41"/><path d="m17.66 17.66 1.41 1.41"/><path d="M2 12h2"/><path d="M20 12h2"/><path d="m6.34 17.66-1.41 1.41"/><path d="m19.07 4.93-1.41 1.41"/></svg>
                            </div>
                        </div>
                        
                        <div>
                            <!-- ID: val-uv -->
                            <h2 id="val-uv" class="text-2xl font-bold tracking-tight text-slate-800 dark:text-white transition-opacity duration-300">--</h2>
                            <p class="text-[10px] font-semibold text-slate-400 dark:text-slate-500 uppercase tracking-wider mt-0.5">UV Index</p>
                        </div>

                        <!-- Visual Context Scale (FIXED) -->
                        <div class="mt-2.5 w-full relative flex items-center h-2">
                            <!-- Background color segments -->
                            <div class="w-full h-1 flex">
                                <div class="h-full bg-green-400 w-[30%]"></div>
                                <div class="h-full bg-amber-400 w-[30%]"></div>
                                <div class="h-full bg-red-400 w-[40%]"></div>
                            </div>
                            <!-- Floating Marker Element -->
                            <div id="uv-marker" class="absolute top-1/2 -translate-y-1/2 w-1.5 h-1.5 bg-white shadow border border-slate-500 hidden transition-all duration-500 z-10" style="left: 0%;"></div>
                        </div>
                    </div>
                </div>

            </div>
        </div>
    </div>

    <!-- API Logic -->
    <script>
/* #raw */
        // API Endpoints
        const API_OBS = "https://swd.weatherflow.com/swd/rest/observations/station/127241?token=0acb5251-7e01-4de2-af32-7d3f46f1edec";
        const API_FCST = "https://swd.weatherflow.com/swd/rest/better_forecast?station_id=127241&units_wind=kts&token=0acb5251-7e01-4de2-af32-7d3f46f1edec";

        // Dictionaries for mapping API data to visual elements
        const weatherIcons = {
            'clear-day': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-amber-500"><circle cx="12" cy="12" r="4"></circle><path d="M12 2v2"></path><path d="M12 20v2"></path><path d="m4.93 4.93 1.41 1.41"></path><path d="m17.66 17.66 1.41 1.41"></path><path d="M2 12h2"></path><path d="M20 12h2"></path><path d="m6.34 17.66-1.41 1.41"></path><path d="m19.07 4.93-1.41 1.41"></path></svg>`,
            'clear-night': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-indigo-400"><path d="M12 3a6 6 0 0 0 9 9 9 9 0 1 1-9-9Z"></path></svg>`,
            'cloudy': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-slate-400"><path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path></svg>`,
            'partly-cloudy-day': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-sky-500"><path d="M12 2v2"></path><path d="m4.93 4.93 1.41 1.41"></path><path d="M20 12h2"></path><path d="m19.07 4.93-1.41 1.41"></path><path d="M15.94 14A5 5 0 0 0 6 12a3 3 0 0 0 0 6h9.5a3.5 3.5 0 1 0 0-7h-.5Z"></path></svg>`,
            'partly-cloudy-night': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-indigo-300"><path d="M10 6.13A6 6 0 0 0 15 15h3.5a3.5 3.5 0 1 0 0-7h-.5A5 5 0 0 0 10 6.13Z"></path></svg>`,
            'rain': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-blue-500"><path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path><path d="M16 23v-2"></path><path d="M8 23v-2"></path><path d="M12 23v-2"></path></svg>`,
            'snow': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-sky-300"><path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path><path d="M8 23h.01"></path><path d="M12 23h.01"></path><path d="M16 23h.01"></path></svg>`,
            'wind': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-slate-500"><path d="M17.7 7.7a2.5 2.5 0 1 1 1.8 4.3H2"></path><path d="M9.6 4.6A2 2 0 1 1 11 8H2"></path><path d="M12.6 19.4A2 2 0 1 0 14 16H2"></path></svg>`,
            'default': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-full h-full text-blue-400"><path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path></svg>`
        };

        const trendIcons = {
            'falling': '<svg class="w-3 h-3 text-red-500" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M12 5v14M19 12l-7 7-7-7"/></svg> <span class="text-red-500 dark:text-red-400">Falling</span>',
            'rising': '<svg class="w-3 h-3 text-green-500" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M12 19V5M5 12l7-7 7 7"/></svg> <span class="text-green-500 dark:text-green-400">Rising</span>',
            'steady': '<svg class="w-3 h-3 text-slate-400" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M5 12h14"/></svg> <span class="text-slate-500 dark:text-slate-400">Steady</span>',
        };

        // --- D3 WIND DIAL SETUP ---
        const width = 330;
        const height = 280; 
        const center = { x: width / 2, y: 154.5 };
        const scale = 1.055; 
        const R = { speedTrack: 130, compass: 110 };

        const SWEEP_START = -0.75 * Math.PI;
        const SWEEP_END = 0.75 * Math.PI;
        const TRANSITION_DURATION = 2400;
        
        let currentMaxSpeed = 30;

        const svg = d3.select("#gauge-mount")
            .append("svg")
            .attr("viewBox", `0 0 ${width} ${height}`)
            .attr("class", "w-full h-auto block")
            .append("g")
            .attr("transform", `translate(${center.x},${center.y}) scale(${scale})`);

        const colorScale = d3.scaleLinear()
            .domain([0, 8, 10, 13, 15, 18, 20, 30, 40, 50])
            .range([
                "#1e3a8a", "#3b82f6", "#22c55e", "#84cc16", "#eab308", 
                "#f97316", "#ef4444", "#991b1b", "#7f1d1d", "#450a0a"
            ]).clamp(true);

        const speedScale = d3.scaleLinear().domain([0, currentMaxSpeed]).range([SWEEP_START, SWEEP_END]);

        const arcSpeedBackground = d3.arc().innerRadius(R.speedTrack - 10).outerRadius(R.speedTrack).cornerRadius(0);
        svg.append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_END}).attr("d", arcSpeedBackground).attr("fill", "var(--track-bg)");

        const defs = svg.append("defs");
        const speedMaskPath = defs.append("clipPath").attr("id", "speed-mask").append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_START});
        const gustMaskPath = defs.append("clipPath").attr("id", "gust-mask").append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_START});
        
        const bubbleMask = defs.append("mask")
            .attr("id", "bottom-bubble-cutout")
            .attr("maskUnits", "userSpaceOnUse")
            .attr("x", -200).attr("y", -200).attr("width", 400).attr("height", 400);
            
        bubbleMask.append("rect").attr("x", -200).attr("y", -200).attr("width", 400).attr("height", 400).attr("fill", "white");
        bubbleMask.append("circle").attr("cx", 0).attr("cy", 0).attr("r", 33).attr("fill", "black");

        const gustTrackGroup = svg.append("g").attr("clip-path", "url(#gust-mask)").attr("opacity", 0.3);
        const colorTrackGroup = svg.append("g").attr("clip-path", "url(#speed-mask)");
        const tickGroup = svg.append("g");
        const arcSpeed = d3.arc().innerRadius(R.speedTrack - 10).outerRadius(R.speedTrack).cornerRadius(0);

        const lullMarker = svg.append("line")
            .attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 10))
            .attr("stroke", "#1e3a8a").attr("stroke-width", 3);

        const speedMarker = svg.append("line")
            .attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 10))
            .attr("stroke", "#22c55e").attr("stroke-width", 3);

        const gustMarker = svg.append("line")
            .attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 10))
            .attr("stroke", "#ef4444").attr("stroke-width", 3);

        function drawSpeedTrack(maxSpeed) {
            currentMaxSpeed = maxSpeed;
            speedScale.domain([0, maxSpeed]);

            gustTrackGroup.selectAll("*").remove();
            colorTrackGroup.selectAll("*").remove();
            tickGroup.selectAll("*").remove();

            for (let i = 0; i < 120; i++) {
                const start = SWEEP_START + (i * (SWEEP_END - SWEEP_START) / 120);
                const end = start + ((SWEEP_END - SWEEP_START) / 120);
                const segmentSpeed = (i / 120) * maxSpeed;
                gustTrackGroup.append("path").datum({startAngle: start, endAngle: end}).attr("d", arcSpeed).attr("fill", colorScale(segmentSpeed));
                colorTrackGroup.append("path").datum({startAngle: start, endAngle: end}).attr("d", arcSpeed).attr("fill", colorScale(segmentSpeed));
            }

            for (let v = 0; v <= maxSpeed; v += 5) {
                const angle = speedScale(v);
                tickGroup.append("line")
                    .attr("x1", R.speedTrack * Math.sin(angle)).attr("y1", -R.speedTrack * Math.cos(angle))
                    .attr("x2", (R.speedTrack - 10) * Math.sin(angle)).attr("y2", -(R.speedTrack - 10) * Math.cos(angle))
                    .attr("class", "speed-tick");
                tickGroup.append("text")
                    .attr("x", (R.speedTrack + 10) * Math.sin(angle)).attr("y", -(R.speedTrack + 10) * Math.cos(angle))
                    .attr("class", "gauge-label").attr("text-anchor", "middle").attr("dominant-baseline", "central").text(v);
            }
        }
        drawSpeedTrack(currentMaxSpeed);

        const compassTicks = svg.append("g").attr("class", "compass-ticks");
        for (let i = 0; i < 360; i += 22.5) {
            const angle = (i * Math.PI) / 180;
            const isMajor = i % 90 === 0;
            compassTicks.append("line")
                .attr("x1", R.compass * Math.sin(angle)).attr("y1", -R.compass * Math.cos(angle))
                .attr("x2", (R.compass - (isMajor ? 10 : 7)) * Math.sin(angle)).attr("y2", -(R.compass - (isMajor ? 10 : 7)) * Math.cos(angle))
                .attr("stroke", "var(--grey-tick)").attr("stroke-width", 1); 
        }

        const pointer = svg.append("g");
        const vane = pointer.append("path").attr("d", "M 0,115 L 65,-95 L 0,-71 L -65,-95 Z").attr("opacity", 0.7);

        const bottomBubbleWrapper = svg.append("g").attr("mask", "url(#bottom-bubble-cutout)");
        const bottomBubble = bottomBubbleWrapper.append("g");
        bottomBubble.append("circle").attr("cx", 0).attr("cy", -50).attr("r", 21).attr("fill", "white").attr("fill-opacity", 0.75);
        
        const dirTextGroup = bottomBubble.append("g").attr("transform", "translate(0, -50)");
        const dirReadout = dirTextGroup.append("text").attr("y", -5).attr("class", "text-[10px] font-black").attr("fill", "#0f172a").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("---");
        const dirAngle = dirTextGroup.append("text").attr("y", 7).attr("class", "text-[9px] font-medium").attr("fill", "#0f172a").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("---\xB0");

        const topBubble = svg.append("g");
        topBubble.append("circle").attr("cx", 0).attr("cy", 0).attr("r", 32).attr("fill", "white").attr("fill-opacity", 0.75);
        topBubble.append("text").attr("y", -22).attr("class", "text-[8px] font-normal uppercase").attr("fill", "#0f172a").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("KNOTS");
        const speedVal = topBubble.append("text").attr("y", -6).attr("class", "center-speed text-[28px]").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("0");
        topBubble.append("text").attr("y", 10).attr("class", "text-[7px] font-normal uppercase").attr("fill", "#0f172a").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("GUSTING");
        const gustVal = topBubble.append("text").attr("y", 20).attr("class", "center-gust").style("font-size", "11px").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("0 to 0");

        function update(data) {
            const l = data.lull || 0, s = data.speed || 0, g = data.gust || 0, d = data.direction || 0;
            let targetMax = 30;
            if (g > 40 || s > 40) targetMax = 50;
            else if (g > 30 || s > 30) targetMax = 40;
            if (targetMax !== currentMaxSpeed) drawSpeedTrack(targetMax);

            const t = d3.transition().duration(TRANSITION_DURATION).ease(d3.easeCubicInOut);
            
            speedMaskPath.transition(t).attrTween("d", d => {
                const i = d3.interpolate(d.endAngle, speedScale(s));
                return t => { d.endAngle = i(t); return d3.arc().innerRadius(R.speedTrack - 15).outerRadius(R.speedTrack + 5)(d); };
            });

            gustMaskPath.transition(t).attrTween("d", d => {
                const i = d3.interpolate(d.endAngle, speedScale(g));
                return t => { d.endAngle = i(t); return d3.arc().innerRadius(R.speedTrack - 15).outerRadius(R.speedTrack + 5)(d); };
            });

            lullMarker.transition(t).attr("transform", `rotate(${(speedScale(l) * 180) / Math.PI})`);
            speedMarker.transition(t).attr("transform", `rotate(${(speedScale(s) * 180) / Math.PI})`);
            gustMarker.transition(t).attr("transform", `rotate(${(speedScale(g) * 180) / Math.PI})`);

            pointer.transition(t).attr("transform", `rotate(${d})`);
            bottomBubble.transition(t).attr("transform", `rotate(${d})`);
            dirTextGroup.transition(t).attr("transform", `translate(0, -50) rotate(${-d})`);
            
            const currentColor = colorScale(s);
            vane.transition(t).attr("fill", currentColor);
            dirReadout.text(getCompassPoint(d));
            dirAngle.text(Math.round(d) + "\xB0");
            
            speedVal.transition(t).tween("text", function() {
                const startS = this._currentS || 0;
                const i = d3.interpolateNumber(startS, s);
                return t => { this._currentS = i(t); this.textContent = Math.round(this._currentS); };
            });
            
            gustVal.transition(t).tween("text", function() {
                const startL = this._currentL || 0, startG = this._currentG || 0;
                const iLull = d3.interpolateNumber(startL, l), iGust = d3.interpolateNumber(startG, g);
                return t => {
                    this._currentL = iLull(t); this._currentG = iGust(t);
                    this.textContent = `${Math.round(this._currentL)} to ${Math.round(this._currentG)}`;
                };
            });
        }

        function getCompassPoint(degrees) {
            const val = Math.floor((degrees / 22.5) + 0.5);
            const arr = ["N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"];
            return arr[(val % 16)];
        }

        // --- API DATA FETCHING ---
        async function fetchWeatherData() {
            try {
                // Fetch real data simultaneously
                const [obsRes, fcstRes] = await Promise.all([ fetch(API_OBS), fetch(API_FCST) ]);
                const obsData = await obsRes.json();
                const fcstData = await fcstRes.json();
                
                let currentObs = null;

                // Update D3 Chart & Obs Dashboard
                if (obsData && obsData.obs && obsData.obs.length > 0) {
                    currentObs = obsData.obs[0];
                    update({
                        lull: (currentObs.wind_lull || 0) * 1.94384,
                        speed: (currentObs.wind_avg || 0) * 1.94384,
                        gust: (currentObs.wind_gust || 0) * 1.94384,
                        direction: currentObs.wind_direction || 0
                    });

                    // Update Temperature
                    if (currentObs.air_temperature != null) {
                        const tempF = (currentObs.air_temperature * 9/5) + 32;
                        document.getElementById('val-temp-f').innerText = `${tempF.toFixed(1)}\xB0F`;
                        document.getElementById('val-temp-c').innerText = `${currentObs.air_temperature.toFixed(1)}\xB0C`;
                    }

                    // Update Pressure
                    const pressure = currentObs.sea_level_pressure || currentObs.barometric_pressure || currentObs.station_pressure;
                    if (pressure != null) {
                        document.getElementById('val-pressure').innerText = pressure.toFixed(1);
                    }

                    // Update UV
                    if (currentObs.uv != null) {
                        document.getElementById('val-uv').innerText = currentObs.uv.toFixed(1);
                        const marker = document.getElementById('uv-marker');
                        if(marker) {
                            marker.classList.remove('hidden');
                            
                            // UV Index scale fix:
                            // We cap the math at 11 since a standard UV scale usually goes from 0 to 11+
                            let uvPercentage = Math.min((currentObs.uv / 11) * 100, 100);
                            
                            // Position it via "left" and offset slightly to center the marker element perfectly
                            marker.style.left = `calc(${uvPercentage}% - 3px)`; 
                        }
                    }
                }

                // Update Forecast conditions
                if (fcstData && fcstData.current_conditions) {
                    const cc = fcstData.current_conditions;
                    let displayCondition = cc.conditions || '--';
                    let displayIcon = cc.icon || 'default';

                    // Override logic: If forecast predicts rain but actual observation precip is 0
                    if (currentObs && Number(currentObs.precip) === 0) {
                        if (displayIcon.includes('rain') || displayCondition.toLowerCase().includes('rain')) {
                            displayCondition = 'Cloudy';
                            displayIcon = 'cloudy';
                        }
                    }

                    document.getElementById('val-conditions').innerText = displayCondition;
                    document.getElementById('icon-weather').innerHTML = weatherIcons[displayIcon] || weatherIcons['default'];
                    document.getElementById('val-pressure-trend').innerHTML = trendIcons[cc.pressure_trend] || '';
                }

            } catch (e) {
                console.error("API error:", e);
            }
        }

        // Boot up
        update({ lull: 0, speed: 0, gust: 0, direction: 0 });
        fetchWeatherData();
        
        setInterval(fetchWeatherData, 10000);
/* #end raw */
    </script>

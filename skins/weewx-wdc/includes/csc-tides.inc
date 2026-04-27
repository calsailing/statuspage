<div class="bx--tile tile-radar-forecast">
    <script src="https://d3js.org/d3.v7.min.js"></script>

    <style>
        /* --- SCOPED CSS RESET --- */
        #tide-chart-widget-container * {
            box-sizing: border-box;
            font-family: 'Inter', sans-serif;
            -webkit-font-smoothing: antialiased;
            -moz-osx-font-smoothing: grayscale;
        }
        #tide-chart-widget-container p,
        #tide-chart-widget-container h1,
        #tide-chart-widget-container h2,
        #tide-chart-widget-container h3 {
            margin: 0;
            padding: 0;
            font-weight: normal;
        }
        #tide-chart-widget-container strong {
            font-weight: 500;
        }
        #tide-chart-widget-container button {
            background-color: transparent;
            border: none;
            padding: 0;
            margin: 0;
            cursor: pointer;
        }
        #tide-chart-widget-container svg {
             display: inline-block;
        }
        #tide-chart-widget-container table {
            border-collapse: collapse;
            border-spacing: 0;
        }

        /* --- THEME VARIABLES & BASE STYLES --- */
        #tide-chart-widget-container {
            /* Light theme variables */
            --color-page-bg: #ffffff;
            --color-icon-bg: #ffffff;
            --color-text-primary: #374151;
            --color-text-secondary: #6b7280;
            --color-text-tertiary: #6b7280;
            --color-text-danger: #ef4444;
            --color-event-text: #000000;
            --color-button-hover-bg: #f3f4f6;
            --color-axis-stroke: #d1d5db;
            --color-chart-day: #FFFFFF;
            --color-chart-night: #f3f4f6;
            --color-chart-open-overlay: rgba(34, 197, 94, 0.15);
            --color-chart-danger-area: rgba(239, 68, 68, 0.7);
            --color-chart-rising: #6da9e9;
            --color-chart-falling: #558bc7;
            --color-chart-tide-line: #2b609c;
            --color-open-line: #22c55e;
            --color-dock-line: #f97316;
            --color-event-circle-fill: #f3f4f6;
            --color-event-circle-stroke: #1f2937;
            --color-hover-line: #9ca3af;
            --color-hover-circle-fill: #ef4444;
            --color-hover-circle-stroke: #ffffff;
            --color-now-indicator: #facc15;
            --color-observed-line: #3b82f6;
            --color-table-border: #e5e7eb;
            --icon-color-open: #22c55e;
            --icon-color-dock: #f97316;
            --icon-color-high: #22d3ee;
            --icon-color-low: #3b82f6;
            --icon-color-sunset: #f97316;

            background-color: var(--color-page-bg);
            color: var(--color-text-primary);
            touch-action: manipulation;
            border-radius: 1rem;
            width: 100%;
            max-width: 600px;
            margin-left: auto;
            margin-right: auto;
        }

        /* Dark theme variables */
        .dark #tide-chart-widget-container {
            --color-page-bg: transparent;
            --color-icon-bg: #1f2937;
            --color-text-primary: #d1d5db;
            --color-text-secondary: #9ca3af;
            --color-text-tertiary: #9ca3af;
            --color-text-danger: #f87171;
            --color-event-text: #ffffff;
            --color-button-hover-bg: #374151;
            --color-axis-stroke: #4b5563;
            --color-chart-day: #1f2937;
            --color-chart-night: #111827;
            --color-chart-open-overlay: rgba(22, 163, 74, 0.25);
            --color-chart-danger-area: rgba(220, 38, 38, 0.6);
            --color-chart-rising: #375a7f;
            --color-chart-falling: #223e5e;
            --color-chart-tide-line: #74a8d0;
            --color-open-line: #4ade80;
            --color-dock-line: #fb923c;
            --color-event-circle-fill: #374151;
            --color-event-circle-stroke: #d1d5db;
            --color-hover-line: #6b7280;
            --color-hover-circle-fill: #f87171;
            --color-hover-circle-stroke: #111827;
            --color-now-indicator: #fde047;
            --color-observed-line: #60a5fa;
            --color-table-border: #374151;
            --icon-color-open: #4ade80;
            --icon-color-dock: #fb923c;
            --icon-color-high: #67e8f9;
            --icon-color-low: #60a5fa;
            --icon-color-sunset: #fb923c;
        }

        /* --- CUSTOM CSS STYLES --- */
        #tide-chart-widget-container .widget-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 0 1rem;
        }
        @media (min-width: 640px) {
            #tide-chart-widget-container .widget-header { padding: 0 1.5rem; }
        }

        #tide-chart-widget-container .nav-button {
            padding: 0.5rem;
            border-radius: 9999px;
            transition: background-color 0.2s;
        }
        #tide-chart-widget-container .nav-button:hover {
            background-color: var(--color-button-hover-bg);
        }
        #tide-chart-widget-container .nav-button svg {
            width: 1.5rem;
            height: 1.5rem;
            color: var(--color-text-secondary);
        }

        #tide-chart-widget-container .info-center { text-align: center; }
        #tide-chart-widget-container .date-picker-wrapper { position: relative; }
        #tide-chart-widget-container .date-display {
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 0.5rem;
            padding: 0.25rem;
        }
        #tide-chart-widget-container #current-date { font-size: 0.875rem; color: var(--color-text-secondary); }
        #tide-chart-widget-container .date-display svg { width: 1.25rem; height: 1.25rem; color: var(--color-text-tertiary); }
        
        #tide-chart-widget-container #date-picker {
            position: absolute;
            top: 0; right: 0; bottom: 0; left: 0;
            width: 100%; height: 100%;
            opacity: 0;
            cursor: pointer;
        }

        #tide-chart-widget-container #current-tide-status { font-size: 1.125rem; font-weight: 600; min-height: 1.75rem; color: var(--color-text-primary); }
        #tide-chart-widget-container #observed-tide-status { font-size: 0.75rem; min-height: 1rem; color: var(--color-text-secondary); font-weight: normal; font-style: italic; }
        #tide-chart-widget-container #next-tide-event { font-size: 0.875rem; min-height: 1.25rem; color: var(--color-text-secondary); }
        #tide-chart-widget-container #club-status-alert { font-size: 0.875rem; min-height: 1.25rem; color: var(--color-text-danger); }
        #tide-chart-widget-container #current-tide-status:empty,
        #tide-chart-widget-container #observed-tide-status:empty,
        #tide-chart-widget-container #next-tide-event:empty,
        #tide-chart-widget-container #club-status-alert:empty {
            min-height: 0;
        }

        #tide-chart-widget-container .chart-aspect-wrapper { position: relative; width: 100%; }
        #tide-chart-widget-container #chart-container { position: absolute; top: 0; left: 0; width: 100%; height: 100%; }

        #tide-chart-widget-container #legend {
            display: flex;
            flex-wrap: wrap;
            justify-content: center;
            align-items: center;
            gap: 0.25rem 1rem;
            font-size: 0.75rem;
            margin-top: 0.5rem;
            padding-left: 1rem; padding-right: 1rem;
            color: var(--color-text-secondary);
        }
        #tide-chart-widget-container #legend > div { display: flex; align-items: center; gap: 0.25rem; }

        #tide-chart-widget-container #events-list {
            margin-top: 1rem;
            font-size: 0.875rem;
            padding-left: 1rem; padding-right: 1rem;
            padding-bottom: 1rem;
            color: var(--color-text-secondary);
        }
        @media (min-width: 640px) {
            #tide-chart-widget-container #legend { padding-left: 1.5rem; padding-right: 1.5rem; }
            #tide-chart-widget-container #events-list { padding-left: 1.5rem; padding-right: 1.5rem; padding-bottom: 1.5rem; }
        }
        #tide-chart-widget-container #events-list table { width: 100%; text-align: left; }
        #tide-chart-widget-container #events-list tr { border-top: 1px solid var(--color-table-border); }
        #tide-chart-widget-container #events-list td { padding-top: 0.25rem; padding-bottom: 0.25rem; vertical-align: middle; }
        #tide-chart-widget-container #events-list td:first-child { width: 1.5rem; }
        #tide-chart-widget-container #events-list td:nth-child(2) { padding-right: 1rem; }
        #tide-chart-widget-container #events-list td:last-child { text-align: right; }
        #tide-chart-widget-container #events-list strong { font-weight: 500; color: var(--color-text-primary); }
        
        #tide-chart-widget-container .icon-sm { width: 1rem; height: 1rem; }
        #tide-chart-widget-container .icon-open { color: var(--icon-color-open); }
        #tide-chart-widget-container .icon-dock { color: var(--icon-color-dock); }
        #tide-chart-widget-container .icon-high { color: var(--icon-color-high); }
        #tide-chart-widget-container .icon-low { color: var(--icon-color-low); }
        #tide-chart-widget-container .icon-sunset { color: var(--icon-color-sunset); }

        /* --- TOOLTIP STYLES --- */
        #tide-chart-tooltip {
            /* Default (Light Theme) Variables */
            --color-tooltip-bg: rgba(255, 255, 255, 0.95);
            --color-tooltip-text: #1f2937;
            --color-tooltip-border: #e5e7eb;

            position: absolute;
            pointer-events: none;
            opacity: 0;
            transition: opacity 0.2s;
            backdrop-filter: blur(4px);
            -webkit-backdrop-filter: blur(4px);
            font-family: 'Inter', sans-serif;
            font-size: 0.7rem;
            border-radius: 0.5rem;
            padding: 2px;
            box-shadow: 0 4px 6px -1px rgb(0 0 0 / 0.1), 0 2px 4px -2px rgb(0 0 0 / 0.1);
            background-color: var(--color-tooltip-bg);
            color: var(--color-tooltip-text);
            border: 1px solid var(--color-tooltip-border);
            z-index: 9999;
        }
        #tide-chart-tooltip p {
            margin: 0;
            padding: 0;
            line-height: 1.1;
        }
        .dark #tide-chart-tooltip {
            /* Dark Theme Override Variables */
            --color-tooltip-bg: rgba(17, 24, 39, 0.95);
            --color-tooltip-text: #f9fafb;
            --color-tooltip-border: #374151;
        }
        #tide-chart-tooltip #tooltip-height { font-weight: 700; }

        #tide-chart-widget-container .axis path,
        #tide-chart-widget-container .axis line { stroke: var(--color-axis-stroke); }
        
        /* Font size reduced for mobile, restored for larger screens */
        #tide-chart-widget-container .axis text { fill: var(--color-text-tertiary); font-size: 0.6rem; }
        @media (min-width: 640px) {
            #tide-chart-widget-container .axis text { font-size: 0.75rem; }
        }
        
        #tide-chart-widget-container .event-label { 
            font-size: 0.7rem; 
            fill: var(--color-event-text); 
            font-weight: normal; 
        }
        #tide-chart-widget-container #chart-container svg { display: block; width: 100%; height: 100%; }
        #tide-chart-widget-container .aspect-wrapper { padding-top: 66.67%; position: relative; width: 100%; }
        @media (min-width: 640px) { #tide-chart-widget-container .aspect-wrapper { padding-top: 50%; } }
        #tide-chart-widget-container .wave-container { display: flex; justify-content: center; align-items: center; height: 100%; flex-direction: column; gap: 1rem; }
        #tide-chart-widget-container .wave .bar { width: 8px; height: 5px; margin: 0 3px; background-color: #60a5fa; border-radius: 9999px; animation: wave-animation 1.2s ease-in-out infinite; }
        #tide-chart-widget-container .wave .bar:nth-child(2) { animation-delay: 0.1s; }
        #tide-chart-widget-container .wave .bar:nth-child(3) { animation-delay: 0.2s; }
        #tide-chart-widget-container .wave .bar:nth-child(4) { animation-delay: 0.3s; }
        
        @keyframes wave-animation {
            0% { transform: scaleY(1); } 50% { transform: scaleY(4); } 100% { transform: scaleY(1); }
        }
    </style>

    <div id="tide-chart-widget-container">
        <div class="widget-header">
            <button id="prev-day" class="nav-button" aria-label="Previous Day">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                    <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 19l-7-7 7-7" />
                </svg>
            </button>
            <div class="info-center">
                 <div class="date-picker-wrapper">
                     <div class="date-display">
                         <p id="current-date"></p>
                         <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                             <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M8 7V3m8 4V3m-9 8h10M5 21h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v12a2 2 0 002 2z" />
                         </svg>
                     </div>
                     <input type="date" id="date-picker" title="Select Date" aria-label="Select Date">
                 </div>
                 <p id="current-tide-status"></p>
                 <p id="next-tide-event"></p>
                 <p id="club-status-alert"></p>
                 <p id="observed-tide-status"></p>
            </div>
            <button id="next-day" class="nav-button" aria-label="Next Day">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                    <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 5l7 7-7 7" />
                </svg>
            </button>
        </div>

        <div class="aspect-wrapper">
            <div id="chart-container" style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></div>
            
            <!-- Tooltip (Now securely housed inside the relative wrapper) -->
            <div id="tide-chart-tooltip" style="display: none;" aria-hidden="true">
                <p id="tooltip-time"></p>
                <p id="tooltip-height"></p>
            </div>
        </div>
        
        <div id="legend"></div>
        
        <div id="events-list"></div>

    </div>

    <script>
        /* #raw */
        document.addEventListener('DOMContentLoaded', () => {
            const initialDate = new Date();
            const DANGEROUS_LOW_TIDE = 1.5;
            const chartContainer = d3.select("#chart-container");
            const dateDisplay = document.getElementById('current-date');
            const datePicker = document.getElementById('date-picker');
            const nextTideDisplay = document.getElementById('next-tide-event');
            const clubStatusAlert = document.getElementById('club-status-alert');
            const currentTideStatus = document.getElementById('current-tide-status');
            const eventsList = document.getElementById('events-list');
            
            // --- Tooltip Handling ---
            const tooltip = d3.select("#tide-chart-tooltip");
            tooltip.style("display", "block"); // Reveal to DOM layout so width is calculable, remains invisible via opacity: 0
            
            let currentDate = new Date(initialDate);
            let countdownInterval = null;
            const tideDataCache = {};
            const observedDataCache = {};
            const NOAA_STATION_ID = "9414816";
            const RICHMOND_STATION_ID = "9414863";
            const LOCATION_LAT = 37.8716;
            const LOCATION_LNG = -122.2727;
            let isHoveringOnEvent = false;
            let svg, xScale, yScale, chartDataForUpdate;

            // --- THEME REACTIVITY ---
            let resizeTimeout;
            const redrawChartOnThemeChange = () => {
                if (chartContainer.node() && chartContainer.select("svg").node()) {
                    drawChart();
                }
            };
            const observer = new MutationObserver((mutationsList) => {
                for (const mutation of mutationsList) {
                    if (mutation.type === 'attributes' && mutation.attributeName === 'class') {
                        redrawChartOnThemeChange();
                    }
                }
            });
            observer.observe(document.documentElement, { attributes: true });
            window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', redrawChartOnThemeChange);

            // --- HELPERS ---
            const parseNOAADate = d3.timeParse("%Y-%m-%d %H:%M");
            function isPDT(date) {
                const year = date.getFullYear();
                const dstStart = new Date(year, 2, 1);
                const firstDayOfMonth = dstStart.getDay();
                const firstSunday = new Date(year, 2, 1 + (7 - firstDayOfMonth) % 7);
                const secondSundayInMarch = new Date(firstSunday.getTime() + 7 * 24 * 60 * 60 * 1000);
                secondSundayInMarch.setHours(2, 0, 0, 0); 
                const dstEnd = new Date(year, 10, 1);
                const firstDayOfNov = dstEnd.getDay();
                const firstSundayInNovember = new Date(year, 10, 1 + (7 - firstDayOfNov) % 7);
                firstSundayInNovember.setHours(2, 0, 0, 0);
                return date >= secondSundayInMarch && date < firstSundayInNovember;
            }
            
            function calculateSunriseSunset(date, latitude, longitude) {
                const toRad = Math.PI / 180;
                const dayOfYear = d => Math.floor((d - new Date(d.getFullYear(), 0, 0)) / 86400000);
                const day = dayOfYear(date);
                const B = 2 * Math.PI * (day - 81) / 364;
                const equationOfTime = 9.87 * Math.sin(2 * B) - 7.53 * Math.cos(B) - 1.5 * Math.sin(B);
                const solarDeclination = -23.44 * Math.cos(2 * Math.PI * (day + 10) / 365);
                const zenith = 90.833;
                const latRad = latitude * toRad;
                const decRad = solarDeclination * toRad;
                const hourAngleRad = Math.acos(Math.cos(zenith * toRad) / (Math.cos(latRad) * Math.cos(decRad)) - Math.tan(latRad) * Math.tan(decRad));
                const hourAngle = hourAngleRad * (180 / Math.PI);
                const berkeleyTimezoneOffsetMinutes = isPDT(date) ? -7 * 60 : -8 * 60;
                const solarNoonMinutes = 720 - 4 * longitude - equationOfTime + berkeleyTimezoneOffsetMinutes;
                const sunriseMinutes = solarNoonMinutes - hourAngle * 4;
                const sunsetMinutes = solarNoonMinutes + hourAngle * 4;
                const sunrise = new Date(date);
                sunrise.setHours(Math.floor(sunriseMinutes / 60), Math.round(sunriseMinutes % 60), 0, 0);
                const sunset = new Date(date);
                sunset.setHours(Math.floor(sunsetMinutes / 60), Math.round(sunsetMinutes % 60), 0, 0);
                return { sunrise, sunset };
            }

            // Function to find exact tide height for specific marker times using interpolation
            function getTideHeightAtTime(chartData, time) {
                if (!chartData || chartData.length === 0) return 0;
                const bisect = d3.bisector(d => d.time).left;
                const index = bisect(chartData, time, 1);
                const a = chartData[index - 1], b = chartData[index];
                if (!a) return b ? b.height : 0;
                if (!b) return a ? a.height : 0;
                if (a.time.getTime() === b.time.getTime()) return a.height;
                const tRatio = (time.getTime() - a.time.getTime()) / (b.time.getTime() - a.time.getTime());
                return a.height + tRatio * (b.height - a.height);
            }

            async function fetchTideData(date) {
                const dateString = date.toISOString().split('T')[0];
                if (tideDataCache[dateString]) return tideDataCache[dateString];
                const yyyymmdd = date.getFullYear() + ('0' + (date.getMonth() + 1)).slice(-2) + ('0' + date.getDate()).slice(-2);
                const url = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=predictions&application=NOS.CO-OPS.CAT&begin_date=${yyyymmdd}&end_date=${yyyymmdd}&datum=MLLW&station=${NOAA_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;
                
                const maxRetries = 10;
                const retryDelay = 1000; 

                for (let attempt = 1; attempt <= maxRetries; attempt++) {
                    try {
                        const response = await fetch(url);
                        if (!response.ok) throw new Error(`NOAA API request failed: ${response.statusText} (Attempt ${attempt})`);
                        const data = await response.json();
                        if (data.error || !data.predictions) {
                            console.warn(`NOAA returned no predictions for ${dateString} (Attempt ${attempt})`);
                            tideDataCache[dateString] = [];
                            return [];
                        }
                        const formattedData = data.predictions.map(p => ({ time: parseNOAADate(p.t), height: parseFloat(p.v) })).filter(p => p.time !== null);
                        tideDataCache[dateString] = formattedData;
                        return formattedData;
                    } catch (error) {
                        console.error(`Failed to fetch tide data on attempt ${attempt}:`, error);
                        if (attempt < maxRetries) {
                            await new Promise(resolve => setTimeout(resolve, retryDelay));
                        } else {
                            console.error(`All ${maxRetries} attempts to fetch tide data failed.`);
                            return null;
                        }
                    }
                }
                return null; 
            }
            
            function findTideExtremes(tideData) {
                if (!tideData || tideData.length < 3) return [];
                const extremes = [];
                let initialIndex = 1;
                let initialDirection = 0;
                while(initialIndex < tideData.length) {
                    initialDirection = Math.sign(tideData[initialIndex].height - tideData[initialIndex-1].height);
                    if (initialDirection !== 0) break;
                    initialIndex++;
                }
                if (initialDirection === 0) return [];
                let lastDirection = initialDirection;
                for (let i = initialIndex; i < tideData.length - 1; i++) {
                    const currentDirection = Math.sign(tideData[i+1].height - tideData[i].height);
                    if (currentDirection === 0) continue;
                    if (currentDirection !== lastDirection) {
                        if (lastDirection === 1 && currentDirection === -1) {
                            extremes.push({ type: 'High', ...tideData[i] });
                        } else if (lastDirection === -1 && currentDirection === 1) {
                            extremes.push({ type: 'Low', ...tideData[i] });
                        }
                    }
                    lastDirection = currentDirection;
                }
                return extremes;
            }

            async function fetchClubStatus(date) {
                const yyyymmdd = date.getFullYear() + '-' + ('0' + (date.getMonth() + 1)).slice(-2) + '-' + ('0' + date.getDate()).slice(-2);
                const url = `https://www.cal-sailing.org/index.php?option=com_csctides&view=gettidedatalist&task=gettidedatalist&tmpl=component&output=json&tidedate=${yyyymmdd}`;
                const maxRetries = 10;
                const retryDelay = 1000;

                for (let attempt = 1; attempt <= maxRetries; attempt++) {
                    try {
                        const response = await fetch(url);
                        if (!response.ok) throw new Error(`Cal Sailing API request failed: ${response.statusText} (Attempt ${attempt})`);
                        
                        const rawText = await response.text();
                        const jsonString = rawText.replace(/<pre.*?>|<\/pre>/g, '');
                        const responseData = JSON.parse(jsonString);
                        const clubData = responseData.data;

                        if (!clubData) throw new Error("Malformed club status JSON: 'data' property is missing.");

                        const parseClubTime = (timeStr) => {
                            if (!timeStr) return null;
                            timeStr = timeStr.toLowerCase().trim();
                            if (timeStr === 'sunset') return 'sunset';
                            const d = new Date(date);
                            if (timeStr === 'noon') { d.setHours(12, 0, 0, 0); return d; }
                            const pm = timeStr.includes('pm');
                            const parts = timeStr.replace(/am|pm/i, '').trim().split(':');
                            let hours = parseInt(parts[0], 10);
                            const minutes = parts.length > 1 ? parseInt(parts[1], 10) : 0;
                            if (isNaN(hours) || isNaN(minutes)) return null;
                            if (pm && hours < 12) hours += 12;
                            else if (!pm && hours === 12) hours = 0;
                            d.setHours(hours, minutes, 0, 0);
                            return d;
                        };
                        
                        const isClosed = clubData.clubclosed === true || clubData.clubclosed === 'true';
                        const sunsetTime = parseClubTime(clubData.sunsettime);

                        if (isClosed) return { isClosed: true, alertMessage: 'Club Closed Due To Tide', sunsetTime };

                        const openTime = parseClubTime(clubData.opentime);
                        const dockTime = parseClubTime(clubData.docktime);
                        let midDayDockTime = null;
                        let midDayOpenTime = null;
                        const alerts = new Set();
                        
                        if (clubData.restriction) {
                            if (clubData.restriction.toUpperCase().includes('EARLY CLOSE')) alerts.add('Early Close Due To Tide');
                            if (clubData.restriction.toUpperCase().includes('LATE OPEN')) alerts.add('Late Open Due To Tide');
                        }

                        if (clubData.middayclosetext && clubData.middayclosetext !== 'null') {
                            alerts.add('Mid-Day Closure Due To Tide');
                            const times = clubData.middayclosetext.match(/(\d{1,2}:\d{2}\s*(am|pm))/gi);
                            if (times && times.length >= 2) {
                                midDayDockTime = parseClubTime(times[0]);
                                midDayOpenTime = parseClubTime(times[1]);
                            }
                        }
                        const alertMessage = Array.from(alerts).join(' & ');
                        return { isClosed: false, openTime, dockTime, midDayDockTime, midDayOpenTime, alertMessage, sunsetTime };

                    } catch (error) {
                        console.error(`Failed to fetch or parse club status on attempt ${attempt}:`, error);
                        if (attempt < maxRetries) {
                            await new Promise(resolve => setTimeout(resolve, retryDelay));
                        } else {
                            console.error(`All ${maxRetries} attempts to fetch club status failed.`);
                            return { isClosed: true, alertMessage: 'Could not load club status', sunsetTime: null };
                        }
                    }
                }
                return { isClosed: true, alertMessage: 'Could not load club status', sunsetTime: null };
            }

            async function fetchObservedTideData(date, forceRefresh = false) {
                const dateString = date.toISOString().split('T')[0];
                if (!forceRefresh && observedDataCache[dateString]) return observedDataCache[dateString];

                const yyyymmdd = date.getFullYear() + ('0' + (date.getMonth() + 1)).slice(-2) + ('0' + date.getDate()).slice(-2);
                const predUrl = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=predictions&application=NOS.CO-OPS.CAT&begin_date=${yyyymmdd}&end_date=${yyyymmdd}&datum=MLLW&station=${RICHMOND_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;
                const obsUrl = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=water_level&application=NOS.CO-OPS.CAT&begin_date=${yyyymmdd}&end_date=${yyyymmdd}&datum=MLLW&station=${RICHMOND_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;

                const maxRetries = 10;
                const retryDelay = 1000;

                for (let attempt = 1; attempt <= maxRetries; attempt++) {
                    try {
                        const [predRes, obsRes] = await Promise.all([fetch(predUrl), fetch(obsUrl)]);
                        if (!predRes.ok) throw new Error(`NOAA Richmond Pred API failed`);
                        if (!obsRes.ok) throw new Error(`NOAA Richmond Obs API failed`);
                        
                        const predData = await predRes.json();
                        const obsData = await obsRes.json();

                        // No observed data for this date (e.g. it's in the future)
                        if (obsData.error || !obsData.data) {
                            observedDataCache[dateString] = [];
                            return [];
                        }

                        const richmondPreds = new Map((predData.predictions || []).map(p => [p.t, parseFloat(p.v)]));
                        const observedPoints = [];

                        (obsData.data || []).forEach(o => {
                            if (o.v) {
                                const obsVal = parseFloat(o.v);
                                const predVal = richmondPreds.get(o.t);
                                if (predVal !== undefined) {
                                    observedPoints.push({
                                        time: parseNOAADate(o.t),
                                        anomaly: obsVal - predVal
                                    });
                                }
                            }
                        });

                        observedDataCache[dateString] = observedPoints;
                        return observedPoints;
                    } catch (error) {
                        console.error(`Failed to fetch observed data on attempt ${attempt}:`, error);
                        if (attempt < maxRetries) {
                            await new Promise(resolve => setTimeout(resolve, retryDelay));
                        } else {
                            return [];
                        }
                    }
                }
                return [];
            }

            async function drawChart() {
                const loadingHTML = `<div class='wave-container'><div style='color: var(--color-text-secondary)'>Loading tide data...</div><div class='wave'><div class='bar'></div><div class='bar'></div><div class='bar'></div><div class='bar'></div></div></div>`;
                chartContainer.html(loadingHTML);
                clubStatusAlert.textContent = '';
                document.getElementById('observed-tide-status').textContent = '';
                eventsList.innerHTML = '';
                const [currentTides, clubStatus, observedAnomalies] = await Promise.all([fetchTideData(currentDate), fetchClubStatus(currentDate), fetchObservedTideData(currentDate)]);
                chartContainer.html("");
                if (!currentTides || currentTides.length === 0) {
                    const message = !currentTides ? "Could not load tide data." : "No tide data available for this date.";
                    chartContainer.html(`<div style="color: red; padding: 1rem; display: flex; align-items: center; justify-content: center; height: 100%;">${message}</div>`);
                    return;
                }
                const chartData = currentTides;
                chartDataForUpdate = chartData;
                const startOfDay = d3.timeDay.floor(currentDate);
                const endOfDay = d3.timeDay.ceil(currentDate);
                const prevDay = new Date(currentDate); prevDay.setDate(prevDay.getDate() - 1);
                const nextDay = new Date(currentDate); nextDay.setDate(nextDay.getDate() + 1);
                const [prevTides, nextTides] = await Promise.all([ fetchTideData(prevDay), fetchTideData(nextDay) ]);
                const allTidesData = [...(prevTides || []), ...currentTides, ...(nextTides || [])];
                const allExtremes = findTideExtremes(allTidesData);
                const tideEvents = allExtremes.filter(event => event.time >= startOfDay && event.time < endOfDay);
                
                const berkeleyObserved = [];
                const berkeleyPredsMap = new Map(chartData.map(p => [p.time.getTime(), p.height]));
                observedAnomalies.forEach(obs => {
                    const predHeight = berkeleyPredsMap.get(obs.time.getTime());
                    if (predHeight !== undefined) {
                        berkeleyObserved.push({ time: obs.time, height: predHeight + obs.anomaly, anomaly: obs.anomaly });
                    }
                });

                const widgetContainer = document.querySelector('#tide-chart-widget-container');
                if (!widgetContainer) return;
                const computedStyles = getComputedStyle(widgetContainer);
                const nightColor = computedStyles.getPropertyValue('--color-chart-night').trim();
                const dayColor = computedStyles.getPropertyValue('--color-chart-day').trim();
                const openOverlayColor = computedStyles.getPropertyValue('--color-chart-open-overlay').trim();
                const risingColor = computedStyles.getPropertyValue('--color-chart-rising').trim();
                const fallingColor = computedStyles.getPropertyValue('--color-chart-falling').trim();
                const tideLineColor = computedStyles.getPropertyValue('--color-chart-tide-line').trim();
                const redAreaColor = computedStyles.getPropertyValue('--color-chart-danger-area').trim();
                const eventCircleFill = computedStyles.getPropertyValue('--color-event-circle-fill').trim();
                const eventCircleStroke = computedStyles.getPropertyValue('--color-event-circle-stroke').trim();
                const hoverLineColor = computedStyles.getPropertyValue('--color-hover-line').trim();
                const hoverCircleFill = computedStyles.getPropertyValue('--color-hover-circle-fill').trim();
                const hoverCircleStroke = computedStyles.getPropertyValue('--color-hover-circle-stroke').trim();

                const containerRect = chartContainer.node().getBoundingClientRect();
                const isMobile = window.innerWidth < 640;
                
                // PERFORMANCE/UI FIX: Margins properly adjusted to prevent axis text clipping on mobile
                const margin = { top: isMobile ? 25 : 20, right: isMobile ? 0 : 20, bottom: isMobile ? 24 : 40, left: isMobile ? 32 : 45 };
                
                const width = containerRect.width - margin.left - margin.right;
                const height = containerRect.height - margin.top - margin.bottom;
                svg = chartContainer.append("svg").attr("width", containerRect.width).attr("height", containerRect.height)
                    .append("g").attr("transform", `translate(${margin.left},${margin.top})`);
                xScale = d3.scaleTime().domain([startOfDay, endOfDay]).range([0, width]);
                
                // Incorporate both predicted and observed heights to ensure the graph scale covers all drawn lines
                const allHeights = chartData.map(d => d.height).concat(berkeleyObserved.map(d => d.height));
                const minTide = Math.min(...allHeights);
                const maxTide = Math.max(...allHeights);
                
                // Scale the Y-axis to be exactly 2 feet below the lowest tide
                yScale = d3.scaleLinear().domain([minTide - 2, maxTide + 1]).range([height, 0]);
                
                // PERFORMANCE FIX: Use curveMonotoneX instead of curveBasis to prevent the plotted
                // line from overshooting or missing actual data points (tide chart integrity)
                const curve = d3.curveMonotoneX;
                
                const areaGenerator = (y0) => d3.area().x(d => xScale(d.time)).y0(y0).y1(d => yScale(d.height)).curve(curve);
                const lineGenerator = d3.line().x(d => xScale(d.time)).y(d => yScale(d.height)).curve(curve);
                
                const { sunrise: calculatedSunrise } = calculateSunriseSunset(currentDate, LOCATION_LAT, LOCATION_LNG);
                const sunriseTime = calculatedSunrise; 
                const sunsetTime = clubStatus.sunsetTime || calculateSunriseSunset(currentDate, LOCATION_LAT, LOCATION_LNG).sunset;

                if (clubStatus.dockTime === 'sunset') clubStatus.dockTime = sunsetTime;
                if (clubStatus.midDayDockTime === 'sunset') clubStatus.midDayDockTime = sunsetTime;

                const overlap = 1;
                svg.append("rect").attr("x", xScale(startOfDay)).attr("width", (xScale(sunriseTime) - xScale(startOfDay)) + overlap).attr("height", height).attr("fill", nightColor);
                svg.append("rect").attr("x", xScale(sunriseTime)).attr("width", (xScale(sunsetTime) - xScale(sunriseTime)) + overlap).attr("height", height).attr("fill", dayColor);
                svg.append("rect").attr("x", xScale(sunsetTime)).attr("width", xScale(endOfDay) - xScale(sunsetTime)).attr("height", height).attr("fill", nightColor);
                const redAreaGenerator = d3.area().x(d => xScale(d.time)).y0(yScale(DANGEROUS_LOW_TIDE)).y1(d => yScale(d.height)).curve(curve);
                const redSegments = []; let currentSegment = [];
                for (let i = 0; i < chartData.length; i++) {
                    const d = chartData[i], prev = i > 0 ? chartData[i - 1] : null;
                    const isBelow = d.height < DANGEROUS_LOW_TIDE, wasBelow = prev ? prev.height < DANGEROUS_LOW_TIDE : false;
                    if (prev && isBelow !== wasBelow) {
                        const t0 = prev.time.getTime(), t1 = d.time.getTime(), h0 = prev.height, h1 = d.height;
                        const intersectionTime = new Date(t0 + (t1 - t0) * (DANGEROUS_LOW_TIDE - h0) / (h1 - h0));
                        const intersectionPoint = { time: intersectionTime, height: DANGEROUS_LOW_TIDE };
                        if (isBelow) currentSegment.push(intersectionPoint);
                        else { currentSegment.push(intersectionPoint); if (currentSegment.length > 1) redSegments.push(currentSegment); currentSegment = []; }
                    }
                    if (isBelow) currentSegment.push(d);
                }
                const lastDataPoint = chartData.length > 0 ? chartData[chartData.length - 1] : null;
                if (lastDataPoint && lastDataPoint.height < DANGEROUS_LOW_TIDE && currentSegment.length > 0) {
                    if (lastDataPoint.time < endOfDay) currentSegment.push({ time: endOfDay, height: lastDataPoint.height });
                }
                if (currentSegment.length > 1) redSegments.push(currentSegment);
                
                const dayEvents = [];
                const specialIcons = []; // For storing Open/Dock icons on the tideline
                clubStatusAlert.textContent = clubStatus.alertMessage || '';
                
                if (!clubStatus.isClosed) {
                    const openPeriods = [];
                    if (clubStatus.midDayDockTime && clubStatus.midDayOpenTime) {
                        if (clubStatus.openTime && clubStatus.midDayDockTime > clubStatus.openTime) openPeriods.push({ start: clubStatus.openTime, end: clubStatus.midDayDockTime, type: 'morning' });
                        if (clubStatus.midDayOpenTime && clubStatus.dockTime > clubStatus.midDayOpenTime) openPeriods.push({ start: clubStatus.midDayOpenTime, end: clubStatus.dockTime, type: 'afternoon' });
                    } 
                    else if (clubStatus.openTime && clubStatus.dockTime > clubStatus.openTime) openPeriods.push({ start: clubStatus.openTime, end: clubStatus.dockTime, type: 'full_day' });
                    
                    openPeriods.forEach(({start, end, type}) => {
                        svg.append("rect").attr("x", xScale(start)).attr("width", xScale(end) - xScale(start)).attr("height", height).attr("fill", openOverlayColor);
                        const openText = type === 'afternoon' ? "Club Re-Opens" : "Club Opens";
                        const dockText = type === 'morning' ? "Mid-Day Dock Time" : "Dock Time (Club Closes)";
                        if (start > startOfDay && start < endOfDay) {
                            svg.append("line").attr("x1", xScale(start)).attr("x2", xScale(start)).attr("y1", 0).attr("y2", height).attr("stroke", "var(--color-open-line)").attr("stroke-width", 1);
                            dayEvents.push({time: start, text: openText, type: 'open'});
                            specialIcons.push({ time: start, type: 'open', yHeight: getTideHeightAtTime(chartData, start) });
                        }
                        if (end > start && end < endOfDay) {
                             svg.append("line").attr("x1", xScale(end)).attr("x2", xScale(end)).attr("y1", 0).attr("y2", height).attr("stroke", "var(--color-dock-line)").attr("stroke-width", 1);
                             dayEvents.push({time: end, text: dockText, type: 'dock'});
                             specialIcons.push({ time: end, type: 'dock', yHeight: getTideHeightAtTime(chartData, end) });
                        }
                    });
                }
                
                const eventPoints = [chartData[0], ...tideEvents, chartData[chartData.length - 1]].sort((a, b) => a.time - b.time).filter((d, i, arr) => !d || i === 0 || d.time.getTime() !== arr[i-1].time.getTime());
                const segments = [];
                for (let i = 0; i < eventPoints.length - 1; i++) {
                    const startPoint = eventPoints[i], endPoint = eventPoints[i+1];
                    if (!startPoint || !endPoint) continue;
                    segments.push({ rising: endPoint.height > startPoint.height, data: chartData.filter(d => d.time >= startPoint.time && d.time <= endPoint.time) });
                }
                if (segments.length > 0) {
                    const lastSegment = segments[segments.length - 1], lastDataPoint = chartData[chartData.length - 1];
                    if (lastDataPoint.time < endOfDay) lastSegment.data.push({ time: endOfDay, height: lastDataPoint.height });
                }
                
                segments.forEach(seg => svg.append("path").datum(seg.data).attr("fill", seg.rising ? risingColor : fallingColor).attr("d", areaGenerator(height)));
                svg.append("path").datum(chartData).attr("fill", "none").attr("stroke", tideLineColor).attr("stroke-width", 2).attr("d", lineGenerator);
                
                if (berkeleyObserved.length > 0) {
                    const observedLineGenerator = d3.line().x(d => xScale(d.time)).y(d => yScale(d.height)).curve(curve);
                    svg.append("path").datum(berkeleyObserved).attr("fill", "none").attr("stroke", "var(--color-observed-line)").attr("stroke-width", 1).style("opacity", 0.85).attr("d", observedLineGenerator);
                }

                redSegments.forEach(segment => svg.append("path").datum(segment).attr("fill", redAreaColor).attr("d", redAreaGenerator));
                
                // Hide the midnight labels (00:00) so the graph text doesn't clip on the zero-margin edges
                svg.append("g").attr("transform", `translate(0,${height})`).call(d3.axisBottom(xScale).ticks(d3.timeHour.every(6)).tickFormat(d => {
                    const timeStr = d3.timeFormat("%H:%M")(d);
                    return timeStr === "00:00" ? "" : timeStr;
                })).attr("class", "axis x-axis");
                
                const yAxis = d3.axisLeft(yScale), ticks = yScale.ticks(), uniqueRoundedTicks = [...new Set(ticks.map(t => Math.round(t)))];
                
                yAxis.tickValues(uniqueRoundedTicks).tickFormat(d => `${d} ft`);
                svg.append("g").call(yAxis).attr("class", "axis y-axis");
                
                // --- Tide Event Markers (High / Low) ---
                const eventsGroup = svg.selectAll(".event").data(tideEvents).enter().append("g").attr("class", "event").attr("transform", d => `translate(${xScale(d.time)},${yScale(d.height)})`);
                eventsGroup.append("circle").attr("r", 5).attr("fill", eventCircleFill).attr("stroke", eventCircleStroke).attr("stroke-width", 1.5);
                eventsGroup.each(function(d) {
                    const tStr = d3.timeFormat("%H:%M")(d.time);
                    const hStr = `${d.height.toFixed(1)}ft`;

                    // Hardcoded to strictly place text below the tide marker
                    const textY1 = 20;
                    const textY2 = 34;

                    // Draw text (styling is now handled purely by the .event-label CSS class to prevent conflicts)
                    const textGroup = d3.select(this).append("text").attr("class", "event-label").attr("text-anchor", "middle");
                    textGroup.append("tspan").attr("x", 0).attr("y", textY1).text(tStr);
                    textGroup.append("tspan").attr("x", 0).attr("y", textY2).text(hStr);
                });

                // --- Open and Dock Icons on Tideline ---
                const specialIconGroup = svg.selectAll(".special-icon")
                    .data(specialIcons)
                    .enter()
                    .append("g")
                    .attr("class", "special-icon")
                    .attr("transform", d => `translate(${xScale(d.time)},${yScale(d.yHeight)})`);
                    
                specialIconGroup.each(function(d) {
                    const g = d3.select(this);
                        
                    const svgIcon = g.append("svg")
                        .attr("x", -7).attr("y", -7)
                        .attr("width", 14).attr("height", 14)
                        .attr("viewBox", "0 0 24 24")
                        .attr("fill", "none")
                        .attr("stroke", d.type === 'open' ? "var(--icon-color-open)" : "var(--icon-color-dock)")
                        .attr("stroke-width", "2")
                        .attr("stroke-linecap", "round")
                        .attr("stroke-linejoin", "round");
                        
                    // Background covering the icon area
                    svgIcon.append("circle")
                        .attr("cx", 12)
                        .attr("cy", 12)
                        .attr("r", 9)
                        .attr("fill", "var(--color-icon-bg)")
                        .attr("stroke", "none");
                        
                    if (d.type === 'open') {
                        svgIcon.append("path").attr("d", "M14.752 11.168l-3.197-2.132A1 1 0 0010 9.87v4.263a1 1 0 001.555.832l3.197-2.132a1 1 0 000-1.664z");
                        svgIcon.append("path").attr("d", "M21 12a9 9 0 11-18 0 9 9 0 0118 0z");
                    } else if (d.type === 'dock') {
                        svgIcon.append("path").attr("d", "M10 9v6m4-6v6m7-3a9 9 0 11-18 0 9 9 0 0118 0z");
                    }
                });

                updateNowIndicator();

                // Hover functionality
                eventsGroup.on("mouseover", (event, d) => { 
                    isHoveringOnEvent = true; 
                    
                    // 1. Update text FIRST so the tooltip resizes to the correct width
                    tooltip.select("#tooltip-time").text(`Event: ${d3.timeFormat("%H:%M")(d.time)}`); 
                    tooltip.select("#tooltip-height").text(`${d.height.toFixed(1)} ft`); 

                    // 2. Measure dimensions
                    const tooltipNode = tooltip.node();
                    const tooltipRect = tooltipNode.getBoundingClientRect();
                    const containerRect = chartContainer.node().getBoundingClientRect();
                    
                    // 3. Align perfectly with the marker's X position, relative to wrapper
                    const snappedX = margin.left + xScale(d.time);
                    let leftPos = snappedX - (tooltipRect.width / 2);
                    
                    // Prevent tooltip from overflowing the widget edges
                    leftPos = Math.max(0, Math.min(leftPos, containerRect.width - tooltipRect.width));
                    
                    tooltip.style("opacity", 1)
                           .style("left", `${leftPos}px`)
                           .style("top", `10px`); 
                }).on("mouseout", () => { 
                    isHoveringOnEvent = false; 
                    tooltip.style("opacity", 0); 
                });
                
                const hoverGroup = svg.append("g").attr("class", "hover-group").style("display", "none");
                hoverGroup.append("line").attr("stroke", hoverLineColor).attr("stroke-width", 1).attr("y1", 0).attr("y2", height);
                const hoverCircle = hoverGroup.append("circle").attr("r", 5).attr("fill", hoverCircleFill).attr("stroke", hoverCircleStroke).attr("stroke-width", 1.5);
                
                function handleInteractionMove(event) {
                    event.preventDefault();
                    if (isHoveringOnEvent) { hoverGroup.style("display", "none"); return; }
                    hoverGroup.style("display", null);
                    const pointer = event.touches ? event.touches[0] : event;
                    if (!pointer) return; // Prevent errors on fast touch actions
                    
                    const [mx] = d3.pointer(pointer, chartContainer.node());
                    const innerX = mx - margin.left; // Fix: Adjust for the left margin offset
                    const time = xScale.invert(innerX);
                    
                    const bisect = d3.bisector(d => d.time).left;
                    const index = bisect(chartData, time, 1);
                    const a = chartData[index - 1], b = chartData[index];
                    let d = !a ? b : !b ? a : (time - a.time > b.time - time) ? b : a;
                    if (!d) return;
                    hoverGroup.attr("transform", `translate(${xScale(d.time)}, 0)`);
                    hoverCircle.attr("cy", yScale(d.height));
                    
                    // 1. Update text FIRST so the tooltip resizes to the correct width
                    tooltip.select("#tooltip-time").text(d3.timeFormat("%H:%M")(d.time));
                    tooltip.select("#tooltip-height").text(`${d.height.toFixed(1)} ft`);

                    // 2. Measure dimensions
                    const tooltipNode = tooltip.node();
                    const tooltipRect = tooltipNode.getBoundingClientRect();
                    const containerRect = chartContainer.node().getBoundingClientRect();
                    
                    // 3. Align perfectly with the vertical hover line's X position, relative to wrapper
                    const snappedX = margin.left + xScale(d.time);
                    let leftPos = snappedX - (tooltipRect.width / 2);
                    
                    // Prevent tooltip from overflowing the widget edges
                    leftPos = Math.max(0, Math.min(leftPos, containerRect.width - tooltipRect.width));
                    
                    tooltip.style("left", `${leftPos}px`)
                           .style("top", `10px`);
                }
                
                svg.append("rect").attr("width", width).attr("height", height).attr("fill", "none").attr("pointer-events", "all")
                    .on("mouseover", () => { if (!isHoveringOnEvent) { hoverGroup.style("display", null); tooltip.style("opacity", 1); }})
                    .on("mouseout", () => { hoverGroup.style("display", "none"); if (!isHoveringOnEvent) tooltip.style("opacity", 0); })
                    .on("mousemove", handleInteractionMove)
                    .on("touchstart", (e) => { e.preventDefault(); if (!isHoveringOnEvent) { hoverGroup.style("display", null); tooltip.style("opacity", 1); }}, { passive: false })
                    .on("touchmove", handleInteractionMove, { passive: false })
                    .on("touchend", () => { hoverGroup.style("display", "none"); if (!isHoveringOnEvent) tooltip.style("opacity", 0);})
                    .on("touchcancel", () => { hoverGroup.style("display", "none"); if (!isHoveringOnEvent) tooltip.style("opacity", 0);});
                
                tideEvents.forEach(event => {
                    if (event.time >= sunriseTime && event.time <= sunsetTime) {
                        dayEvents.push({ time: event.time, text: `${event.type} Tide: ${event.height.toFixed(1)} ft`, type: event.type.toLowerCase() });
                    }
                });
                dayEvents.push({ time: sunsetTime, text: "Sunset", type: 'sunset' });
                dayEvents.sort((a, b) => a.time - b.time);
                const uniqueEvents = [...new Set(dayEvents.map(e => JSON.stringify(e)))].map(s => JSON.parse(s));
                uniqueEvents.sort((a,b) => new Date(a.time) - new Date(b.time));
                if (uniqueEvents.length > 0) {
                     const eventIcons = {
                          open: `<svg class="icon-sm icon-open" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M14.752 11.168l-3.197-2.132A1 1 0 0010 9.87v4.263a1 1 0 001.555.832l3.197-2.132a1 1 0 000-1.664z"></path><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M21 12a9 9 0 11-18 0 9 9 0 0118 0z"></path></svg>`,
                          dock: `<svg class="icon-sm icon-dock" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M10 9v6m4-6v6m7-3a9 9 0 11-18 0 9 9 0 0118 0z"></path></svg>`,
                          high: `<svg class="icon-sm icon-high" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M5 10l7-7m0 0l7 7m-7-7v18"></path></svg>`,
                          low: `<svg class="icon-sm icon-low" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 14l-7 7m0 0l-7-7m7 7V3"></path></svg>`,
                          sunset: `<svg class="icon-sm icon-sunset" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" viewBox="0 0 24 24"><path d="M17 18a5 5 0 00-10 0M12 2v7m-5.66 2.34l1.42 1.42M1 18h2m18 0h2M18.36 11.64l1.42-1.42M23 22H1m15-17l-4 4-4-4"/></svg>`
                     };
                     let tableHTML = `<table><tbody>${uniqueEvents.map(e => { const icon = eventIcons[e.type] || ''; return `<tr><td>${icon}</td><td>${e.text}</td><td><strong>${d3.timeFormat("%H:%M")(new Date(e.time))}</strong></td></tr>`; }).join('')}</tbody></table>`;
                     eventsList.innerHTML = tableHTML;
                } else {
                     eventsList.innerHTML = `<p>No scheduled events during daylight hours.</p>`;
                }
                updateUI();
            }

            function updateNowIndicator() {
                if (!svg || !xScale || !yScale || !chartDataForUpdate) return;
                svg.select(".now-indicator").remove();
                const now = new Date();
                const startOfDay = d3.timeDay.floor(currentDate);
                const endOfDay = d3.timeDay.ceil(currentDate);
                if (currentDate.toDateString() === now.toDateString() && now >= startOfDay && now <= endOfDay) {
                    const bisect = d3.bisector(d => d.time).left;
                    const index = bisect(chartDataForUpdate, now, 1);
                    const a = chartDataForUpdate[index - 1], b = chartDataForUpdate[index];
                    const currentDataPoint = !a ? b : !b ? a : (now - a.time > b.time - now) ? b : a;
                    if (currentDataPoint) {
                         const widgetContainer = document.querySelector('#tide-chart-widget-container');
                         if (!widgetContainer) return;
                         const computedStyles = getComputedStyle(widgetContainer);
                         const nowIndicatorColor = computedStyles.getPropertyValue('--color-now-indicator').trim();
                         svg.append("circle").attr("class", "now-indicator").attr("cx", xScale(now)).attr("cy", yScale(currentDataPoint.height)).attr("r", 5).attr("fill", nowIndicatorColor).style("pointer-events", "none");
                    }
                }
            }

            function updateUI() {
                const isMobile = window.innerWidth < 640;
                const dateFormatOptions = { weekday: 'long', month: 'long', day: 'numeric' };
                if (!isMobile) dateFormatOptions.year = 'numeric';
                dateDisplay.textContent = currentDate.toLocaleString(undefined, dateFormatOptions);
                const yyyy = currentDate.getFullYear(), mm = String(currentDate.getMonth() + 1).padStart(2, '0'), dd = String(currentDate.getDate()).padStart(2, '0');
                datePicker.value = `${yyyy}-${mm}-${dd}`;
                if(countdownInterval) {
                    clearInterval(countdownInterval);
                    countdownInterval = null;
                }
                const isCurrentDay = currentDate.toDateString() === new Date().toDateString();
                nextTideDisplay.style.display = isCurrentDay ? 'block' : 'none';
                currentTideStatus.style.display = isCurrentDay ? 'block' : 'none';
                if (isCurrentDay) {
                    updateNextTideEvent();
                    countdownInterval = setInterval(updateNextTideEvent, 60000); 
                }
                
                // Reflected the updated Circular Icons logic in the Legend UI
                document.getElementById('legend').innerHTML = `
                    <div><div style="width: 0.75rem; height: 0.75rem; border-radius: 0.125rem; background-color: var(--color-chart-open-overlay);"></div><span>Club Open</span></div>
                    <div><div style="width: 1rem; height: 1px; background-color: var(--color-observed-line); opacity: 0.85;"></div><span>Observed tide</span></div>
                    <div>
                        <svg style="width:0.875rem;height:0.875rem;color:var(--icon-color-open);" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2">
                            <circle cx="12" cy="12" r="9" fill="var(--color-icon-bg)" stroke="none"></circle>
                            <path stroke-linecap="round" stroke-linejoin="round" d="M14.752 11.168l-3.197-2.132A1 1 0 0010 9.87v4.263a1 1 0 001.555.832l3.197-2.132a1 1 0 000-1.664z"></path>
                            <path stroke-linecap="round" stroke-linejoin="round" d="M21 12a9 9 0 11-18 0 9 9 0 0118 0z"></path>
                        </svg>
                        <span>Open Time</span>
                    </div>
                    <div>
                        <svg style="width:0.875rem;height:0.875rem;color:var(--icon-color-dock);" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2">
                            <circle cx="12" cy="12" r="9" fill="var(--color-icon-bg)" stroke="none"></circle>
                            <path stroke-linecap="round" stroke-linejoin="round" d="M10 9v6m4-6v6m7-3a9 9 0 11-18 0 9 9 0 0118 0z"></path>
                        </svg>
                        <span>Dock Time</span>
                    </div>
                    <div><div style="width: 0.75rem; height: 0.75rem; border-radius: 9999px; background-color: var(--color-now-indicator);"></div><span>Now</span></div>
                    <div><div style="width: 0.75rem; height: 0.75rem; background-color: var(--color-chart-danger-area);"></div><span>Club Closed &lt; 1.5'</span></div>`;
            }

            async function updateNextTideEvent() {
                 try {
                    const now = new Date();
                    const [prevTides, currentTides, nextTides, nextNextTides] = await Promise.all([ 
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() - 1)), 
                        fetchTideData(now), 
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() + 1)),
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() + 2)) 
                    ]);
                    if (!prevTides || !currentTides || !nextTides || !nextNextTides) { 
                        nextTideDisplay.innerHTML = ""; 
                        currentTideStatus.innerHTML = "";
                        document.getElementById('observed-tide-status').textContent = '';
                        return; 
                    }
                    const combinedTideDataForLookup = [...prevTides, ...currentTides, ...nextTides, ...nextNextTides];
                    
                    // Exact real-time interpolation
                    const currentHeight = getTideHeightAtTime(combinedTideDataForLookup, now);
                    const timeIn5Mins = new Date(now.getTime() + 5 * 60000);
                    const futureHeight = getTideHeightAtTime(combinedTideDataForLookup, timeIn5Mins);
                    
                    let directionArrow = '';
                    if (futureHeight > currentHeight) directionArrow = `<svg class="icon-sm" style="display: inline-block; vertical-align: middle; color: var(--icon-color-high);" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2"><path stroke-linecap="round" stroke-linejoin="round" d="M5 10l7-7m0 0l7 7m-7-7v18"></path></svg>`;
                    else if (futureHeight < currentHeight) directionArrow = `<svg class="icon-sm" style="display: inline-block; vertical-align: middle; color: var(--icon-color-low);" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2"><path stroke-linecap="round" stroke-linejoin="round" d="M19 14l-7 7m0 0l-7-7m7 7V3"></path></svg>`;
                    
                    currentTideStatus.innerHTML = `<span style="display: inline-flex; align-items: center;">${directionArrow}<span style="margin-left: 0.25rem;">${currentHeight.toFixed(1)} ft</span></span>`;
                    
                    // Handle accurate real-time observed status mapping anomaly to current interpolation
                    const observedStatusEl = document.getElementById('observed-tide-status');
                    if (currentDate.toDateString() === now.toDateString()) {
                        const obsAnomalies = await fetchObservedTideData(now, true);
                        if (obsAnomalies && obsAnomalies.length > 0) {
                            const latestAnomaly = obsAnomalies[obsAnomalies.length - 1].anomaly;
                            const exactObservedHeight = currentHeight + latestAnomaly;
                            const sign = latestAnomaly >= 0 ? '+' : '';
                            observedStatusEl.textContent = `Observed tide: ${exactObservedHeight.toFixed(1)} ft (${sign}${latestAnomaly.toFixed(1)} ft)`;
                        } else {
                            observedStatusEl.textContent = '';
                        }
                    } else {
                        observedStatusEl.textContent = '';
                    }

                    const allRawTides = [...prevTides, ...currentTides, ...nextTides, ...nextNextTides];
                    const allTideExtremes = findTideExtremes(allRawTides);
                    const nextEvent = allTideExtremes.find(event => event.time > now);
                    if (nextEvent) {
                        const diff = nextEvent.time - now, hours = Math.floor(diff / 3600000), minutes = Math.floor((diff % 3600000) / 60000);
                        nextTideDisplay.innerHTML = `<span>${nextEvent.type} tide in ${hours}h ${minutes}m at ${nextEvent.height.toFixed(1)} ft</span>`;
                    } else {
                        nextTideDisplay.innerHTML = "";
                    }
                    updateNowIndicator();
                } catch (error) {
                    console.error("Error during periodic tide update:", error);
                    currentTideStatus.innerHTML = "";
                    nextTideDisplay.innerHTML = "<span>Could not update status</span>";
                }
            }

            function clearHeaderInfo() {
                dateDisplay.textContent = '';
                currentTideStatus.innerHTML = '';
                document.getElementById('observed-tide-status').textContent = '';
                nextTideDisplay.innerHTML = '';
                clubStatusAlert.textContent = '';
            }

            document.getElementById('prev-day').addEventListener('click', () => {
                currentDate.setDate(currentDate.getDate() - 1);
                clearHeaderInfo();
                drawChart();
            });
            document.getElementById('next-day').addEventListener('click', () => {
                currentDate.setDate(currentDate.getDate() + 1);
                clearHeaderInfo();
                drawChart();
            });
            datePicker.addEventListener('change', (event) => {
                const dateString = event.target.value;
                if (!dateString) return;
                const [year, month, day] = dateString.split('-').map(Number);
                const selectedDate = new Date(currentDate.getTime());
                selectedDate.setFullYear(year, month - 1, day);
                if (!isNaN(selectedDate.getTime()) && selectedDate.toDateString() !== currentDate.toDateString()) {
                    currentDate = selectedDate;
                    clearHeaderInfo();
                    drawChart();
                }
            });
            
            // PERFORMANCE FIX: Debounce the resize event to prevent heavy CPU usage when manipulating the browser window
            window.addEventListener('resize', () => {
                clearTimeout(resizeTimeout);
                resizeTimeout = setTimeout(drawChart, 200);
            });

            drawChart();
        });
        /* #end raw */
    </script>
</div>

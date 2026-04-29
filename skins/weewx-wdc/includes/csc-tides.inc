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
            --color-chart-rising: #a0c0e0;
            --color-chart-falling: #80a8d0;
            --color-chart-tide-line: #4575a5;
            --color-open-line: #22c55e;
            --color-dock-line: #f97316;
            --color-open-bg: rgba(34, 197, 94, 0.15);
            --color-dock-bg: rgba(249, 115, 22, 0.15);
            --color-event-circle-fill: #f3f4f6;
            --color-event-circle-stroke: #1f2937;
            --color-hover-line: #9ca3af;
            --color-hover-circle-fill: #ef4444;
            --color-hover-circle-stroke: #ffffff;
            --color-now-indicator: #facc15;
            --color-observed-line: #3b82f6;
            --color-table-border: #e5e7eb;
            --color-box-bg: #ffffff;
            --color-box-border: #e5e7eb;
            --color-box-border-active: #94a3b8;
            --color-box-bg-subtle: #f8fafc;
            --color-fade-overlay: rgba(255, 255, 255, 0.65);
            --shadow-sm: 0 1px 2px 0 rgb(0 0 0 / 0.05);
            --icon-color-open: #22c55e;
            --icon-color-dock: #f97316;
            --icon-color-high: #22d3ee;
            --icon-color-low: #3b82f6;
            --icon-color-sunset: #f97316;

            background-color: var(--color-page-bg);
            color: var(--color-text-primary);
            touch-action: manipulation;
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
            --color-chart-tide-line: #6ea8e0;
            --color-open-line: #4ade80;
            --color-dock-line: #fb923c;
            --color-open-bg: rgba(74, 222, 128, 0.15);
            --color-dock-bg: rgba(251, 146, 60, 0.15);
            --color-event-circle-fill: #374151;
            --color-event-circle-stroke: #d1d5db;
            --color-hover-line: #6b7280;
            --color-hover-circle-fill: #f87171;
            --color-hover-circle-stroke: #111827;
            --color-now-indicator: #fde047;
            --color-observed-line: #60a5fa;
            --color-table-border: #374151;
            --color-box-bg: #1f2937;
            --color-box-border: #4b5563;
            --color-box-border-active: #6b7280;
            --color-box-bg-subtle: #111827;
            --color-fade-overlay: rgba(17, 24, 39, 0.65);
            --shadow-sm: 0 1px 3px 0 rgb(0 0 0 / 0.3);
            --icon-color-open: #4ade80;
            --icon-color-dock: #fb923c;
            --icon-color-high: #67e8f9;
            --icon-color-low: #60a5fa;
            --icon-color-sunset: #fb923c;
        }

        /* --- CUSTOM CSS STYLES --- */
        #tide-chart-widget-container .widget-top-container {
            padding: 0 1rem;
            margin-bottom: 0.75rem;
            display: flex;
            flex-direction: column;
            gap: 0.75rem;
        }
        @media (min-width: 640px) {
            #tide-chart-widget-container .widget-top-container { padding: 0 1.5rem; }
        }

        #tide-chart-widget-container .date-nav-box {
            display: flex; justify-content: space-between; align-items: center;
            background-color: var(--color-box-bg); border: 1px solid var(--color-box-border);
            box-shadow: var(--shadow-sm);
            padding: 0.25rem; width: 100%;
        }

        #tide-chart-widget-container .nav-button {
            padding: 0.5rem;
            border-radius: 9999px; /* Keeping round buttons */
            transition: background-color 0.2s;
        }
        #tide-chart-widget-container .nav-button:hover:not(:disabled) {
            background-color: var(--color-button-hover-bg);
        }
        #tide-chart-widget-container .nav-button:disabled {
            opacity: 0.5;
            cursor: not-allowed;
        }
        #tide-chart-widget-container .nav-button svg {
            width: 1.5rem;
            height: 1.5rem;
            color: var(--color-text-secondary);
        }

        #tide-chart-widget-container .info-center { text-align: center; }
        #tide-chart-widget-container .date-picker-wrapper { position: relative; cursor: pointer; }
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
            z-index: 10;
        }
        
        /* This CSS trick stretches the native clickable area to cover the entire wrapper */
        #tide-chart-widget-container #date-picker::-webkit-calendar-picker-indicator {
            position: absolute;
            top: 0; right: 0; bottom: 0; left: 0;
            width: 100%; height: 100%;
            opacity: 0;
            cursor: pointer;
        }

        #tide-chart-widget-container .status-boxes-container {
            /* display is handled dynamically in JS */
            grid-template-columns: repeat(3, 1fr); gap: 0.5rem; width: 100%;
            max-height: 0;
            opacity: 0;
            overflow: hidden;
            margin-top: -0.75rem; /* Negates parent flex gap when collapsed */
            transition: max-height 0.4s ease-in-out, opacity 0.4s ease-in-out, margin-top 0.4s ease-in-out;
        }
        
        #tide-chart-widget-container .status-boxes-container.visible {
            max-height: 200px;
            opacity: 1;
            margin-top: 0;
        }

        #tide-chart-widget-container .status-box {
            background-color: var(--color-box-bg); border: 1px solid var(--color-box-border);
            box-shadow: var(--shadow-sm); padding: 0.5rem 0.25rem;
            text-align: center; display: flex; flex-direction: column; align-items: center; min-height: 4rem;
        }
        #tide-chart-widget-container .box-primary {
            border: 1px solid var(--color-box-border-active);
            box-shadow: var(--shadow-sm), 0 0 0 1px var(--color-box-border-active);
        }
        #tide-chart-widget-container .box-secondary {
            background-color: var(--color-box-bg-subtle);
        }
        #tide-chart-widget-container .status-label {
            font-size: 0.65rem; color: var(--color-text-tertiary); text-transform: uppercase;
            letter-spacing: 0.05em; margin-bottom: 0.25rem;
        }
        #tide-chart-widget-container .status-value {
            font-size: 0.875rem; color: var(--color-text-primary); line-height: 1.2;
            display: flex; flex-direction: column; align-items: center; justify-content: center; flex-grow: 1;
        }

        #tide-chart-widget-container .status-banner {
            /* display is handled dynamically in JS */
            align-items: center; justify-content: center; gap: 0.5rem;
            font-size: 0.875rem; font-weight: 500; text-align: center;
            max-height: 0; opacity: 0; overflow: hidden;
            padding: 0 1rem;
            margin-top: -0.75rem; /* Negates parent flex gap when collapsed */
            transition: max-height 0.4s ease-in-out, opacity 0.4s ease-in-out, padding 0.4s ease-in-out, margin-top 0.4s ease-in-out;
        }
        
        #tide-chart-widget-container .status-banner.visible {
            max-height: 100px;
            opacity: 1;
            padding: 0.5rem 1rem;
            margin-top: 0;
        }
        
        #tide-chart-widget-container .banner-yellow { background-color: #fef08a; color: #854d0e; }
        #tide-chart-widget-container .banner-red { background-color: #fecaca; color: #991b1b; }
        .dark #tide-chart-widget-container .banner-yellow { background-color: rgba(234, 179, 8, 0.15); color: #fde047; border: 1px solid rgba(234, 179, 8, 0.3); }
        .dark #tide-chart-widget-container .banner-red { background-color: rgba(239, 68, 68, 0.15); color: #fca5a5; border: 1px solid rgba(239, 68, 68, 0.3); }

        #tide-chart-widget-container .chart-aspect-wrapper { position: relative; width: 100%; }
        #tide-chart-widget-container #chart-container { 
            position: absolute; top: 0; left: 0; width: 100%; height: 100%; 
            overflow: hidden; 
        }

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
        
        #tide-chart-widget-container .event-row-next { font-weight: 700; background-color: var(--color-button-hover-bg); }
        #tide-chart-widget-container .event-row-next td { color: var(--color-text-primary); }
        #tide-chart-widget-container .event-row-next td:first-child { padding-left: 0.25rem; border-top-left-radius: 0.25rem; border-bottom-left-radius: 0.25rem; }
        #tide-chart-widget-container .event-row-next td:last-child { padding-right: 0.25rem; border-top-right-radius: 0.25rem; border-bottom-right-radius: 0.25rem; }
        
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
            --color-tooltip-text-muted: #6b7280;
            --color-tooltip-border: #e5e7eb;

            position: absolute;
            pointer-events: none;
            opacity: 0;
            transition: opacity 0.2s ease-in-out;
            backdrop-filter: blur(8px);
            -webkit-backdrop-filter: blur(8px);
            font-family: 'Inter', sans-serif;
            padding: 0.35rem 0.5rem;
            box-shadow: 0 10px 15px -3px rgb(0 0 0 / 0.1), 0 4px 6px -4px rgb(0 0 0 / 0.1);
            background-color: var(--color-tooltip-bg);
            border: 1px solid var(--color-tooltip-border);
            z-index: 9999;
            display: flex;
            flex-direction: column;
            gap: 0.15rem;
            text-align: center;
            min-width: 70px;
        }
        #tide-chart-tooltip p {
            margin: 0;
            padding: 0;
            line-height: 1;
        }
        .dark #tide-chart-tooltip {
            /* Dark Theme Override Variables */
            --color-tooltip-bg: rgba(31, 41, 55, 0.95);
            --color-tooltip-text: #f9fafb;
            --color-tooltip-text-muted: #9ca3af;
            --color-tooltip-border: #4b5563;
            box-shadow: 0 10px 15px -3px rgb(0 0 0 / 0.5), 0 4px 6px -4px rgb(0 0 0 / 0.5);
        }
        #tide-chart-tooltip #tooltip-time { 
            font-size: 0.6rem; 
            color: var(--color-tooltip-text-muted); 
            font-weight: 500;
            text-transform: uppercase;
            letter-spacing: 0.05em;
        }
        #tide-chart-tooltip #tooltip-height { 
            font-size: 0.85rem;
            font-weight: 700;
            color: var(--color-tooltip-text);
        }

        #tide-chart-widget-container .axis path,
        #tide-chart-widget-container .axis line { stroke: var(--color-axis-stroke); }
        
        /* Font size reduced for mobile, restored for larger screens */
        #tide-chart-widget-container .axis text { fill: var(--color-text-tertiary); font-size: 0.55rem; }
        @media (min-width: 640px) {
            #tide-chart-widget-container .axis text { font-size: 0.7rem; }
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
        <div class="widget-top-container">
            <div class="date-nav-box">
                <button id="prev-day" class="nav-button" aria-label="Previous Day">
                    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 19l-7-7 7-7" />
                    </svg>
                </button>
                <div class="date-picker-wrapper">
                     <div class="date-display">
                         <p id="current-date"></p>
                         <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                             <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M8 7V3m8 4V3m-9 8h10M5 21h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v12a2 2 0 002 2z" />
                         </svg>
                     </div>
                     <input type="date" id="date-picker" title="Select Date" aria-label="Select Date">
                </div>
                <button id="next-day" class="nav-button" aria-label="Next Day">
                    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 5l7 7-7 7" />
                    </svg>
                </button>
            </div>

            <div id="club-status-banner" style="display: none;"></div>
            
            <div id="status-boxes-container" class="status-boxes-container" style="display: none;">
                <div class="status-box box-primary">
                    <div class="status-label">Tide Now</div>
                    <div id="current-tide-status" class="status-value"></div>
                    <div id="observed-tide-status" style="margin-top: 0.25rem;"></div>
                </div>
                <div class="status-box box-secondary">
                    <div class="status-label">Next Tide</div>
                    <div id="next-tide-event" class="status-value"></div>
                </div>
                <div id="club-schedule-box" class="status-box box-secondary">
                    <div id="club-schedule-label" class="status-label">Schedule</div>
                    <div id="club-schedule-status" class="status-value"></div>
                </div>
            </div>
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
            // ALWAYS initialize core dates to Pacific Time to ensure out-of-state visitors see precise local Berkeley predictions
            function getPTNow() {
                return new Date(new Date().toLocaleString("en-US", { timeZone: "America/Los_Angeles" }));
            }
            
            const DANGEROUS_LOW_TIDE = 1.5;
            const chartContainer = d3.select("#chart-container");
            const dateDisplay = document.getElementById('current-date');
            const datePicker = document.getElementById('date-picker');
            const nextTideDisplay = document.getElementById('next-tide-event');
            const clubStatusBanner = document.getElementById('club-status-banner');
            const currentTideStatus = document.getElementById('current-tide-status');
            const observedStatusEl = document.getElementById('observed-tide-status');
            const clubScheduleBoxEl = document.getElementById('club-schedule-box');
            const clubScheduleLabelEl = document.getElementById('club-schedule-label');
            const clubScheduleStatusEl = document.getElementById('club-schedule-status');
            const statusBoxesContainer = document.getElementById('status-boxes-container');
            const eventsList = document.getElementById('events-list');
            
            // --- Tooltip Handling ---
            const tooltip = d3.select("#tide-chart-tooltip");
            tooltip.style("display", "block"); // Reveal to DOM layout so width is calculable, remains invisible via opacity: 0
            
            let currentDate = getPTNow();
            let countdownInterval = null;
            let lastRealDateString = getPTNow().toDateString();
            let isRendering = false; // Lock to prevent race conditions during rapid clicking
            
            // --- Caching Stores ---
            const tideDataCache = {};
            const observedDataCache = {};
            const clubStatusCache = {}; 
            
            const NOAA_STATION_ID = "9414816";
            const RICHMOND_STATION_ID = "9414863";
            const LOCATION_LAT = 37.8716;
            const LOCATION_LNG = -122.2727;
            let isHoveringOnEvent = false;
            let currentClubStatus = null;
            let svg, xScale, yScale, chartDataForUpdate;

            // --- THEME REACTIVITY ---
            let resizeTimeout;
            const redrawChartOnThemeChange = () => {
                if (chartContainer.node() && chartContainer.select("svg").node()) {
                    drawChart(currentDate, 0);
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
            // Parses NOAA predictions directly matching wall clock time
            const parseNOAADate = d3.timeParse("%Y-%m-%d %H:%M");
            
            // Returns a timezone-safe YYYYMMDD string for caching to prevent UTC roll-over bugs
            function getLocalCacheKey(date) {
                const yyyy = date.getFullYear();
                const mm = ('0' + (date.getMonth() + 1)).slice(-2);
                const dd = ('0' + date.getDate()).slice(-2);
                return `${yyyy}${mm}${dd}`;
            }
            
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
                const sunrise = new Date(date.getTime());
                sunrise.setHours(Math.floor(sunriseMinutes / 60), Math.round(sunriseMinutes % 60), 0, 0);
                const sunset = new Date(date.getTime());
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
                const cacheKey = getLocalCacheKey(date);
                if (tideDataCache[cacheKey]) return tideDataCache[cacheKey];
                
                const url = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=predictions&application=NOS.CO-OPS.CAT&begin_date=${cacheKey}&end_date=${cacheKey}&datum=MLLW&station=${NOAA_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;
                
                const maxRetries = 10;
                const retryDelay = 1000; 

                for (let attempt = 1; attempt <= maxRetries; attempt++) {
                    try {
                        const response = await fetch(url);
                        if (!response.ok) throw new Error(`NOAA API request failed: ${response.statusText} (Attempt ${attempt})`);
                        const data = await response.json();
                        if (data.error || !data.predictions || !Array.isArray(data.predictions)) {
                            console.warn(`NOAA returned no valid predictions for ${cacheKey} (Attempt ${attempt})`);
                            tideDataCache[cacheKey] = [];
                            return [];
                        }
                        const formattedData = data.predictions.map(p => ({ time: parseNOAADate(p.t), height: parseFloat(p.v) })).filter(p => p.time !== null && !isNaN(p.height));
                        tideDataCache[cacheKey] = formattedData;
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
                const cacheKey = getLocalCacheKey(date);
                if (clubStatusCache[cacheKey]) return clubStatusCache[cacheKey];
                
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

                        const parseClubTime = (timeStr, baseDate) => {
                            if (!timeStr) return null;
                            timeStr = timeStr.toLowerCase().trim();
                            if (timeStr === 'sunset') return 'sunset'; // Prevent string from corrupting D3 scale
                            const d = new Date(baseDate.getTime());
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
                        const sunsetTime = parseClubTime(clubData.sunsettime, date);

                        if (isClosed) {
                            const result = { isClosed: true, alertMessage: 'Club Closed Due To Tide', sunsetTime };
                            clubStatusCache[cacheKey] = result;
                            return result;
                        }

                        const openTime = parseClubTime(clubData.opentime, date);
                        const dockTime = parseClubTime(clubData.docktime, date);
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
                                midDayDockTime = parseClubTime(times[0], date);
                                midDayOpenTime = parseClubTime(times[1], date);
                            }
                        }
                        const alertMessage = Array.from(alerts).join(' & ');
                        
                        const result = { isClosed: false, openTime, dockTime, midDayDockTime, midDayOpenTime, alertMessage, sunsetTime };
                        clubStatusCache[cacheKey] = result;
                        return result;

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
                const cacheKey = getLocalCacheKey(date);
                if (!forceRefresh && observedDataCache[cacheKey]) return observedDataCache[cacheKey];

                const predUrl = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=predictions&application=NOS.CO-OPS.CAT&begin_date=${cacheKey}&end_date=${cacheKey}&datum=MLLW&station=${RICHMOND_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;
                const obsUrl = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=water_level&application=NOS.CO-OPS.CAT&begin_date=${cacheKey}&end_date=${cacheKey}&datum=MLLW&station=${RICHMOND_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;

                const maxRetries = 10;
                const retryDelay = 1000;

                for (let attempt = 1; attempt <= maxRetries; attempt++) {
                    try {
                        const [predRes, obsRes] = await Promise.all([fetch(predUrl), fetch(obsUrl)]);
                        if (!predRes.ok) throw new Error(`NOAA Richmond Pred API failed`);
                        if (!obsRes.ok) throw new Error(`NOAA Richmond Obs API failed`);
                        
                        const predData = await predRes.json();
                        const obsData = await obsRes.json();

                        // Gracefully fail without permanently poisoning the historical cache
                        if (obsData.error || !obsData.data) {
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

                        observedDataCache[cacheKey] = observedPoints;
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

            async function drawChart(renderDate, direction = 0) {
                if (isRendering) return; // Prevent concurrent renders if user clicks rapidly
                isRendering = true;
                
                const navButtons = document.querySelectorAll('.nav-button, #date-picker');
                navButtons.forEach(btn => btn.disabled = true);
                
                try {
                    tooltip.style("opacity", 0); 
                    const isFirstLoad = !chartContainer.select("svg").node();
                    
                    // Show loading screen only if it's the very first time the widget spins up
                    if (isFirstLoad) {
                        chartContainer.html(""); 
                        const loadingHTML = `<div class='wave-container'><div style='color: var(--color-text-secondary)'>Loading tide data...</div><div class='wave'><div class='bar'></div><div class='bar'></div><div class='bar'></div><div class='bar'></div></div></div>`;
                        chartContainer.html(loadingHTML);
                        
                        clubStatusBanner.classList.remove('visible');
                        clubStatusBanner.style.display = 'none';
                        clubStatusBanner.className = 'status-banner';
                        
                        observedStatusEl.innerHTML = '';
                        clubScheduleStatusEl.innerHTML = '';
                        eventsList.innerHTML = '';
                    }

                    const [currentTides, clubStatus, observedAnomalies] = await Promise.all([
                        fetchTideData(renderDate), 
                        fetchClubStatus(renderDate), 
                        fetchObservedTideData(renderDate)
                    ]);
                    
                    if (!currentTides || currentTides.length === 0) {
                        const message = !currentTides ? "Could not load tide data." : "No tide data available for this date.";
                        chartContainer.html(`<div style="color: red; padding: 1rem; display: flex; align-items: center; justify-content: center; height: 100%;">${message}</div>`);
                        clearHeaderInfo();
                        isRendering = false;
                        navButtons.forEach(btn => btn.disabled = false);
                        return;
                    }
                    
                    const chartData = currentTides;
                    chartDataForUpdate = chartData;
                    const startOfDay = d3.timeDay.floor(renderDate);
                    const endOfDay = d3.timeDay.ceil(renderDate);
                    const prevDay = new Date(renderDate); prevDay.setDate(prevDay.getDate() - 1);
                    const nextDay = new Date(renderDate); nextDay.setDate(nextDay.getDate() + 1);
                    
                    // Fallbacks to empty arrays [] guarantee that map spreads don't crash if adjacent data failed to fetch
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

                currentClubStatus = clubStatus;

                const widgetContainer = document.querySelector('#tide-chart-widget-container');
                if (!widgetContainer) {
                    isRendering = false;
                    navButtons.forEach(btn => btn.disabled = false);
                    return;
                }
                const computedStyles = getComputedStyle(widgetContainer);
                const nightColor = computedStyles.getPropertyValue('--color-chart-night').trim();
                const dayColor = computedStyles.getPropertyValue('--color-chart-day').trim();
                const openOverlayColor = computedStyles.getPropertyValue('--color-chart-open-overlay').trim();
                const risingColor = computedStyles.getPropertyValue('--color-chart-rising').trim();
                const fallingColor = computedStyles.getPropertyValue('--color-chart-falling').trim();
                const tideLineColor = computedStyles.getPropertyValue('--color-chart-tide-line').trim();
                const redAreaColor = computedStyles.getPropertyValue('--color-chart-danger-area').trim();
                const dangerColor = computedStyles.getPropertyValue('--color-text-danger').trim();
                const eventCircleFill = computedStyles.getPropertyValue('--color-event-circle-fill').trim();
                const eventCircleStroke = computedStyles.getPropertyValue('--color-event-circle-stroke').trim();
                const hoverLineColor = computedStyles.getPropertyValue('--color-hover-line').trim();
                const hoverCircleFill = computedStyles.getPropertyValue('--color-hover-circle-fill').trim();
                const hoverCircleStroke = computedStyles.getPropertyValue('--color-hover-circle-stroke').trim();

                const containerRect = chartContainer.node().getBoundingClientRect();
                const isMobile = window.innerWidth < 640;
                
                const margin = { top: isMobile ? 25 : 20, right: isMobile ? 0 : 20, bottom: isMobile ? 24 : 40, left: isMobile ? 32 : 45 };
                
                // QA FIX: Protect against negative dimensions rendering fatal DOM exceptions if window scales out of bounds
                const width = Math.max(0, containerRect.width - margin.left - margin.right);
                const height = Math.max(0, containerRect.height - margin.top - margin.bottom);
                
                // --- SVG SKELETON SETUP (Only runs on initial load OR browser resize) ---
                if (isFirstLoad || direction === 0) {
                    chartContainer.html(""); // Safely clear only when data is finished processing to avoid flashing
                    
                    svg = chartContainer.append("svg").attr("width", containerRect.width).attr("height", containerRect.height)
                        .append("g").attr("transform", `translate(${margin.left},${margin.top})`);
                        
                    svg.append("defs").append("clipPath").attr("id", "chart-clip")
                       .append("rect").attr("width", width).attr("height", height);
                       
                    svg.append("g").attr("class", "axis x-axis x-axis-group").attr("transform", `translate(0,${height})`);
                    svg.append("g").attr("class", "axis y-axis y-axis-group");
                    
                    svg.select(".y-axis-group").append("text")
                        .attr("class", "y-axis-label")
                        .attr("x", -9).attr("y", height + 15)
                        .attr("text-anchor", "end").text("\u2032");
                        
                    const chartWindow = svg.append("g").attr("class", "chart-window").attr("clip-path", "url(#chart-clip)");
                    
                    // Invisible overlay to catch all pointer events across the whole chart window
                    chartWindow.append("rect").attr("class", "hover-overlay").attr("fill", "none").attr("pointer-events", "all");
                    
                    // Set pointer-events to none so backgrounds don't block the hover overlay beneath them
                    chartWindow.append("g").attr("class", "slides-container").style("pointer-events", "none");
                    
                    // Ensure the follow-cursor group also doesn't block events
                    const hoverGroup = chartWindow.append("g").attr("class", "hover-group").style("display", "none").style("pointer-events", "none");
                    hoverGroup.append("line").attr("class", "hover-line").attr("stroke-width", 1).attr("y1", 0);
                    hoverGroup.append("circle").attr("class", "hover-circle").attr("r", 5).attr("stroke-width", 1.5);
                }
                
                svg.select(".hover-overlay").attr("width", width).attr("height", height);
                svg.select("#chart-clip rect").attr("width", width).attr("height", height);
                
                const hoverGroup = svg.select(".hover-group");
                hoverGroup.select(".hover-line").attr("stroke", hoverLineColor).attr("y2", height);
                hoverGroup.select(".hover-circle").attr("fill", hoverCircleFill).attr("stroke", hoverCircleStroke);
                
                xScale = d3.scaleTime().domain([startOfDay, endOfDay]).range([0, width]);
                
                const allHeights = chartData.map(d => d.height).concat(berkeleyObserved.map(d => d.height));
                const minTide = Math.min(...allHeights);
                const maxTide = Math.max(...allHeights);
                yScale = d3.scaleLinear().domain([minTide - 2, maxTide + 1]).range([height, 0]);
                
                // Kill any previous axis transitions to prevent bouncing
                svg.select(".x-axis-group").interrupt();
                svg.select(".y-axis-group").interrupt();

                // Smoothly transition static axes
                const t = d3.transition().duration(400).ease(d3.easeCubicInOut);
                
                const xAxis = d3.axisBottom(xScale).ticks(d3.timeHour.every(6)).tickFormat(d => {
                    const timeStr = d3.timeFormat("%H:%M")(d);
                    return timeStr === "00:00" ? "" : timeStr;
                });
                svg.select(".x-axis-group").transition(t).call(xAxis);
                
                const yAxis = d3.axisLeft(yScale);
                const ticks = yScale.ticks(), uniqueRoundedTicks = [...new Set(ticks.map(tick => Math.round(tick)))];
                yAxis.tickValues(uniqueRoundedTicks).tickFormat(d => `${d}`);
                svg.select(".y-axis-group").transition(t).call(yAxis);
                svg.select(".y-axis-label").attr("y", height + 15);
                
                const curve = d3.curveMonotoneX;
                const areaGenerator = (y0) => d3.area().x(d => xScale(d.time)).y0(y0).y1(d => yScale(d.height)).curve(curve);
                const lineGenerator = d3.line().x(d => xScale(d.time)).y(d => yScale(d.height)).curve(curve);
                
                const { sunrise: calculatedSunrise, sunset: calculatedSunset } = calculateSunriseSunset(renderDate, LOCATION_LAT, LOCATION_LNG);
                const sunriseTime = calculatedSunrise; 
                
                // Strict safety catch to prevent the word 'sunset' from reaching the numeric xScale
                let sunsetTime = clubStatus.sunsetTime;
                if (!sunsetTime || sunsetTime === 'sunset') {
                    sunsetTime = calculatedSunset;
                }

                if (clubStatus.dockTime === 'sunset') clubStatus.dockTime = sunsetTime;
                if (clubStatus.midDayDockTime === 'sunset') clubStatus.midDayDockTime = sunsetTime;
                if (clubStatus.openTime === 'sunset') clubStatus.openTime = sunsetTime;

                // --- GENERATE SLIDE LAYER ---
                const slidesContainer = svg.select(".slides-container");
                const slideGroup = slidesContainer.append("g").attr("class", "slide-group");
                
                if (direction !== 0) {
                    slideGroup.attr("transform", `translate(${direction > 0 ? width : -width}, 0)`);
                }

                const overlap = 1;
                // QA FIX: Replaced direct width calculation with clamped Math.max boundaries
                slideGroup.append("rect").attr("x", xScale(startOfDay)).attr("width", Math.max(0, (xScale(sunriseTime) - xScale(startOfDay)) + overlap)).attr("height", height).attr("fill", nightColor);
                slideGroup.append("rect").attr("x", xScale(sunriseTime)).attr("width", Math.max(0, (xScale(sunsetTime) - xScale(sunriseTime)) + overlap)).attr("height", height).attr("fill", dayColor);
                slideGroup.append("rect").attr("x", xScale(sunsetTime)).attr("width", Math.max(0, xScale(endOfDay) - xScale(sunsetTime))).attr("height", height).attr("fill", nightColor);
                
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
                const topLabelsData = []; // For the top boxes
                
                // Update Warning Banner
                let newBannerClass = '';
                let bannerHTML = '';
                
                if (clubStatus.isClosed) {
                    newBannerClass = 'banner-red';
                    bannerHTML = `<svg class="icon-sm" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"/></svg> <span>${clubStatus.alertMessage}</span>`;
                } else if (clubStatus.alertMessage) {
                    newBannerClass = 'banner-yellow';
                    bannerHTML = `<svg class="icon-sm" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"/></svg> <span>${clubStatus.alertMessage}</span>`;
                }
                
                if (newBannerClass) {
                    const isVisible = clubStatusBanner.classList.contains('visible');
                    clubStatusBanner.className = `status-banner ${newBannerClass} ${isVisible ? 'visible' : ''}`;
                    clubStatusBanner.innerHTML = bannerHTML;
                    clubStatusBanner.style.display = 'flex';
                    
                    if (!isVisible) {
                        clubStatusBanner.offsetHeight; // Force reflow
                        clubStatusBanner.classList.add('visible');
                    }
                } else {
                    clubStatusBanner.classList.remove('visible');
                    setTimeout(() => {
                        if (!clubStatusBanner.classList.contains('visible')) {
                            clubStatusBanner.style.display = 'none';
                            clubStatusBanner.className = 'status-banner';
                        }
                    }, 400); // 400ms matches the CSS transition duration
                }
                
                if (!clubStatus.isClosed) {
                    const openPeriods = [];
                    if (clubStatus.midDayDockTime && clubStatus.midDayOpenTime) {
                        if (clubStatus.openTime && clubStatus.midDayDockTime > clubStatus.openTime) openPeriods.push({ start: clubStatus.openTime, end: clubStatus.midDayDockTime, type: 'morning' });
                        if (clubStatus.midDayOpenTime && clubStatus.dockTime > clubStatus.midDayOpenTime) openPeriods.push({ start: clubStatus.midDayOpenTime, end: clubStatus.dockTime, type: 'afternoon' });
                    } 
                    else if (clubStatus.openTime && clubStatus.dockTime > clubStatus.openTime) openPeriods.push({ start: clubStatus.openTime, end: clubStatus.dockTime, type: 'full_day' });
                    
                    openPeriods.forEach(({start, end, type}) => {
                        slideGroup.append("rect").attr("x", xScale(start)).attr("width", Math.max(0, xScale(end) - xScale(start))).attr("height", height).attr("fill", openOverlayColor);
                        const openText = type === 'afternoon' ? "Club Re-Opens" : "Club Opens";
                        const dockText = type === 'morning' ? "Mid-Day Dock Time" : "Dock Time (Club Closes)";
                        if (start > startOfDay && start < endOfDay) {
                            slideGroup.append("line").attr("x1", xScale(start)).attr("x2", xScale(start)).attr("y1", 0).attr("y2", height).attr("stroke", "var(--color-open-line)").attr("stroke-width", 1);
                            dayEvents.push({time: start, text: openText, type: 'open'});
                            specialIcons.push({ time: start, type: 'open', yHeight: getTideHeightAtTime(chartData, start) });
                            topLabelsData.push({ time: start, text: 'Open', isOpen: true });
                        }
                        if (end > start && end < endOfDay) {
                             slideGroup.append("line").attr("x1", xScale(end)).attr("x2", xScale(end)).attr("y1", 0).attr("y2", height).attr("stroke", "var(--color-dock-line)").attr("stroke-width", 1);
                             dayEvents.push({time: end, text: dockText, type: 'dock'});
                             specialIcons.push({ time: end, type: 'dock', yHeight: getTideHeightAtTime(chartData, end) });
                             topLabelsData.push({ time: end, text: 'Dock', isOpen: false });
                        }
                    });
                }
                
                // QA FIX: Placed safety `.filter(Boolean)` directly prior to `.sort()` so unexpected edge-case API responses cannot poison the sorting function
                const eventPoints = [chartData[0], ...tideEvents, chartData[chartData.length - 1]].filter(Boolean).sort((a, b) => a.time - b.time).filter((d, i, arr) => !d || i === 0 || d.time.getTime() !== arr[i-1].time.getTime());
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
                
                segments.forEach(seg => slideGroup.append("path").datum(seg.data).attr("fill", seg.rising ? risingColor : fallingColor).attr("d", areaGenerator(height)));
                
                // Draw red danger areas before the stroke lines so they sit in the background
                redSegments.forEach(segment => slideGroup.append("path").datum(segment).attr("fill", redAreaColor).attr("d", redAreaGenerator));
                
                // --- UNIQUE LINE GRADIENT PER SLIDE FOR DANGER ZONE ---
                const gradientId = "tide-gradient-" + Math.round(Math.random() * 1000000);
                const dangerY = yScale(DANGEROUS_LOW_TIDE);
                const dangerOffset = Math.max(0, Math.min(1, dangerY / height));
                
                const localDefs = slideGroup.append("defs");
                localDefs.append("linearGradient")
                    .attr("id", gradientId)
                    .attr("gradientUnits", "userSpaceOnUse")
                    .attr("x1", 0).attr("y1", 0)
                    .attr("x2", 0).attr("y2", height)
                    .selectAll("stop")
                    .data([
                        {offset: 0, color: tideLineColor},
                        {offset: dangerOffset, color: tideLineColor},
                        {offset: dangerOffset, color: dangerColor},
                        {offset: 1, color: dangerColor}
                    ])
                    .enter().append("stop")
                    .attr("offset", d => d.offset)
                    .attr("stop-color", d => d.color);

                slideGroup.append("path").datum(chartData).attr("fill", "none").attr("stroke", `url(#${gradientId})`).attr("stroke-width", 2).attr("d", lineGenerator);
                
                if (berkeleyObserved.length > 0) {
                    const observedLineGenerator = d3.line().x(d => xScale(d.time)).y(d => yScale(d.height)).curve(curve);
                    slideGroup.append("path").datum(berkeleyObserved).attr("fill", "none").attr("stroke", "var(--color-observed-line)").attr("stroke-width", 1).style("opacity", 0.9).attr("d", observedLineGenerator);
                }
                
                // --- Tide Event Markers (High / Low) ---
                // Override the pointer-events so these markers remain individually hoverable
                const eventsGroup = slideGroup.selectAll(".event").data(tideEvents).enter().append("g").attr("class", "event").attr("transform", d => `translate(${xScale(d.time)},${yScale(d.height)})`).style("pointer-events", "all").style("cursor", "pointer");
                
                eventsGroup.each(function(d) {
                    const g = d3.select(this);
                    
                    if (d.height < DANGEROUS_LOW_TIDE) {
                        g.append("circle")
                         .attr("r", 4.5)
                         .attr("fill", dangerColor);
                        g.append("path")
                         .attr("d", "M-2,-2 L2,2 M-2,2 L2,-2")
                         .attr("stroke", "#ffffff")
                         .attr("stroke-width", 1.5)
                         .attr("stroke-linecap", "round");
                    } else {
                        g.append("circle")
                         .attr("r", 3.5)
                         .attr("fill", tideLineColor);
                    }

                    const tStr = d3.timeFormat("%H:%M")(d.time);
                    const hStr = `${d.height.toFixed(1)}\u2032`;

                    const textY1 = 20;
                    const textY2 = 34;

                    const textGroup = d3.select(this).append("text").attr("class", "event-label").attr("text-anchor", "middle");
                    textGroup.append("tspan").attr("x", 0).attr("y", textY1).text(tStr).style("font-size", "0.65rem");
                    textGroup.append("tspan").attr("x", 0).attr("y", textY2).text(hStr).style("font-weight", "bold");
                });

                // --- Open and Dock Icons on Tideline ---
                const specialIconGroup = slideGroup.selectAll(".special-icon")
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

                // --- Top Labels for Open / Dock Times ---
                const topBoxes = [];
                topLabelsData.forEach(label => {
                    const timeStr = d3.timeFormat("%H:%M")(label.time);
                    const labelText = `${label.text} ${timeStr}`;
                    const boxWidth = 66;
                    const boxHeight = 18;
                    const xPos = xScale(label.time);
                    
                    let rectX = label.isOpen ? (xPos - boxWidth + 6) : (xPos - 6);
                    
                    if (rectX < 0) rectX = 0;
                    if (rectX + boxWidth > width) rectX = width - boxWidth;
                    
                    let rectY = 4;
                    let collision = true;
                    let loopCounter = 0; // Prevent infinite loop in edge case stacking
                    while(collision && loopCounter < 15) {
                        collision = false;
                        for (let b of topBoxes) {
                            if (rectX < b.x + b.w && rectX + boxWidth > b.x &&
                                rectY < b.y + b.h && rectY + boxHeight > b.y) {
                                rectY += boxHeight + 4; 
                                collision = true;
                                break;
                            }
                        }
                        loopCounter++;
                    }
                    topBoxes.push({x: rectX, y: rectY, w: boxWidth, h: boxHeight});

                    const g = slideGroup.append("g").attr("class", "top-time-label");
                    
                    g.append("rect")
                        .attr("x", rectX).attr("y", rectY)
                        .attr("width", Math.max(0, boxWidth)).attr("height", Math.max(0, boxHeight))
                        .attr("fill", label.isOpen ? "var(--color-open-line)" : "var(--color-dock-line)")
                        .attr("stroke", "none");
                        
                    g.append("text")
                        .attr("x", rectX + (boxWidth / 2))
                        .attr("y", rectY + (boxHeight / 2) + 1)
                        .attr("text-anchor", "middle").attr("dominant-baseline", "middle")
                        .attr("font-size", "0.6rem").attr("font-weight", "600")
                        .attr("fill", "#000000")
                        .text(labelText);
                });

                updateNowIndicator(renderDate, slideGroup);

                // --- INTERACTION & HOVER BINDING ---
                function handleInteractionMove(event) {
                    event.preventDefault();
                    if (isHoveringOnEvent) { hoverGroup.style("display", "none"); return; }
                    hoverGroup.style("display", null);
                    const pointer = event.touches ? event.touches[0] : event;
                    if (!pointer) return; 
                    
                    // Chart window is translated by margin.left, so mx maps exactly to chart coordinates
                    const [mx] = d3.pointer(pointer, svg.select(".chart-window").node());
                    const time = xScale.invert(mx);
                    
                    const bisect = d3.bisector(d => d.time).left;
                    const index = bisect(chartDataForUpdate, time, 1);
                    const a = chartDataForUpdate[index - 1], b = chartDataForUpdate[index];
                    let d = !a ? b : !b ? a : (time - a.time > b.time - time) ? b : a;
                    if (!d) return;
                    hoverGroup.attr("transform", `translate(${xScale(d.time)}, 0)`);
                    hoverGroup.select(".hover-circle").attr("cy", yScale(d.height));
                    
                    tooltip.select("#tooltip-time").text(d3.timeFormat("%H:%M")(d.time));
                    tooltip.select("#tooltip-height").text(`${d.height.toFixed(1)}\u2032`);

                    const tooltipNode = tooltip.node();
                    const tooltipRect = tooltipNode.getBoundingClientRect();
                    const containerRect = chartContainer.node().getBoundingClientRect();
                    
                    const snappedX = margin.left + xScale(d.time);
                    let leftPos = snappedX - (tooltipRect.width / 2);
                    
                    // Clamp tooltip strictly within the widget bounds
                    leftPos = Math.max(10, Math.min(leftPos, containerRect.width - tooltipRect.width - 10));
                    
                    tooltip.style("left", `${leftPos}px`)
                           .style("top", `10px`);
                }

                // Re-bind hover logic cleanly on every draw to ensure closures hold the newest data scale
                svg.select(".hover-overlay")
                    .on("mouseover", () => { if (!isHoveringOnEvent) { hoverGroup.style("display", null); tooltip.style("opacity", 1); }})
                    .on("mouseout", () => { hoverGroup.style("display", "none"); if (!isHoveringOnEvent) tooltip.style("opacity", 0); })
                    .on("mousemove", handleInteractionMove)
                    .on("touchstart", (e) => { e.preventDefault(); if (!isHoveringOnEvent) { hoverGroup.style("display", null); tooltip.style("opacity", 1); }}, { passive: false })
                    .on("touchmove", handleInteractionMove, { passive: false })
                    .on("touchend", () => { hoverGroup.style("display", "none"); if (!isHoveringOnEvent) tooltip.style("opacity", 0);})
                    .on("touchcancel", () => { hoverGroup.style("display", "none"); if (!isHoveringOnEvent) tooltip.style("opacity", 0);});
                
                eventsGroup.on("mouseover", (event, d) => { 
                    isHoveringOnEvent = true; 
                    tooltip.select("#tooltip-time").text(`Event: ${d3.timeFormat("%H:%M")(d.time)}`); 
                    tooltip.select("#tooltip-height").text(`${d.height.toFixed(1)}\u2032`); 
                    const tooltipNode = tooltip.node();
                    const tooltipRect = tooltipNode.getBoundingClientRect();
                    const containerRect = chartContainer.node().getBoundingClientRect();
                    const snappedX = margin.left + xScale(d.time);
                    let leftPos = snappedX - (tooltipRect.width / 2);
                    leftPos = Math.max(10, Math.min(leftPos, containerRect.width - tooltipRect.width - 10));
                    tooltip.style("opacity", 1).style("left", `${leftPos}px`).style("top", `10px`); 
                }).on("mouseout", () => { 
                    isHoveringOnEvent = false; 
                    tooltip.style("opacity", 0); 
                });

                // Update text below the chart
                tideEvents.forEach(event => {
                    if (event.time >= sunriseTime && event.time <= sunsetTime) {
                        dayEvents.push({ time: event.time, text: `${event.type} Tide: ${event.height.toFixed(1)}\u2032`, type: event.type.toLowerCase() });
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
                     
                     let foundNextTableEvent = false;
                     let tableHTML = `<table><tbody>${uniqueEvents.map(e => { 
                         const icon = eventIcons[e.type] || ''; 
                         const eventTime = new Date(e.time);
                         const nowForTable = getPTNow();
                         let rowClass = "";
                         
                         if (renderDate.toDateString() === nowForTable.toDateString()) {
                             if (eventTime >= nowForTable && !foundNextTableEvent) {
                                 rowClass = "event-row-next";
                                 foundNextTableEvent = true;
                             }
                         }
                         
                         return `<tr class="${rowClass}"><td>${icon}</td><td>${e.text}</td><td><strong>${d3.timeFormat("%H:%M")(eventTime)}</strong></td></tr>`; 
                     }).join('')}</tbody></table>`;
                     eventsList.innerHTML = tableHTML;
                } else {
                     eventsList.innerHTML = `<p>No scheduled events during daylight hours.</p>`;
                }
                updateUI(renderDate);
                
                // --- EXECUTE D3 SLIDE ANIMATION ON THE GRAPH DATA GROUP ---
                if (direction !== 0) {
                    const oldSlideGroup = slidesContainer.select(".slide-group.active");
                    
                    // Cancel any previous transitions gracefully to prevent jumping
                    oldSlideGroup.interrupt();
                    
                    // Temporarily disable hover interactions during slide to prevent ghost tooltips
                    if (svg && svg.select(".hover-overlay").node()) {
                         svg.select(".hover-overlay").style("pointer-events", "none");
                    }
                    
                    oldSlideGroup.classed("active", false)
                        .transition(t)
                        .attr("transform", `translate(${direction > 0 ? -width : width}, 0)`)
                        .remove();
                        
                    slideGroup.classed("active", true)
                        .transition(t)
                        .attr("transform", `translate(0, 0)`)
                        .on("end", () => {
                            if (svg && svg.select(".hover-overlay").node()) {
                                 svg.select(".hover-overlay").style("pointer-events", "all");
                            }
                            isRendering = false;
                            navButtons.forEach(btn => btn.disabled = false);
                        });
                        
                } else {
                    slidesContainer.selectAll(".slide-group.active").remove();
                    slideGroup.classed("active", true).attr("transform", "translate(0,0)");
                    if (svg && svg.select(".hover-overlay").node()) {
                         svg.select(".hover-overlay").style("pointer-events", "all");
                    }
                    isRendering = false;
                    navButtons.forEach(btn => btn.disabled = false);
                }
                
                } catch (error) {
                    console.error("Critical rendering error:", error);
                    chartContainer.html(`<div style="color: red; padding: 1rem; text-align: center; display: flex; align-items: center; justify-content: center; height: 100%;">An error occurred generating the chart. Check developer console for details.</div>`);
                    isRendering = false;
                    navButtons.forEach(btn => btn.disabled = false);
                }
            }

            function updateNowIndicator(renderDate, targetSlideGroup = null) {
                const activeSlide = targetSlideGroup || (svg ? svg.select(".slide-group.active") : null);
                if (!activeSlide || activeSlide.empty() || !xScale || !yScale || !chartDataForUpdate) return;
                
                activeSlide.selectAll(".now-indicator, .now-group").remove();
                const now = getPTNow();
                const startOfDay = d3.timeDay.floor(renderDate);
                const endOfDay = d3.timeDay.ceil(renderDate);

                if (renderDate.toDateString() === now.toDateString() && now >= startOfDay && now <= endOfDay) {
                    const bisect = d3.bisector(d => d.time).left;
                    const index = bisect(chartDataForUpdate, now, 1);
                    const a = chartDataForUpdate[index - 1], b = chartDataForUpdate[index];
                    const currentDataPoint = !a ? b : !b ? a : (now - a.time > b.time - now) ? b : a;
                    
                    if (currentDataPoint) {
                         const widgetContainer = document.querySelector('#tide-chart-widget-container');
                         if (!widgetContainer) return;
                         const computedStyles = getComputedStyle(widgetContainer);
                         const nowIndicatorColor = computedStyles.getPropertyValue('--color-now-indicator').trim();
                         
                         const xPos = xScale(now);
                         const yPos = yScale(currentDataPoint.height);
                         const chartWidth = xScale.range()[1];
                         
                         const nowGroup = activeSlide.append("g").attr("class", "now-group").style("pointer-events", "none");
                         
                         const flagWidth = 28;
                         const flagHeight = 14;
                         let flagX = xPos;
                         
                         if (xPos + flagWidth > chartWidth) {
                             flagX = xPos - flagWidth;
                         }
                         
                         let maxLabelY = 0;
                         activeSlide.selectAll(".top-time-label rect").each(function() {
                             const lx = parseFloat(d3.select(this).attr("x"));
                             const lw = parseFloat(d3.select(this).attr("width"));
                             const ly = parseFloat(d3.select(this).attr("y"));
                             const lh = parseFloat(d3.select(this).attr("height"));
                             
                             if (!isNaN(lx) && !isNaN(lw) && (flagX < lx + lw + 2) && (flagX + flagWidth + 2 > lx)) {
                                 if (!isNaN(ly) && !isNaN(lh) && (ly + lh > maxLabelY)) {
                                     maxLabelY = ly + lh;
                                 }
                             }
                         });
                         const flagY = maxLabelY > 0 ? maxLabelY + 4 : 0;
                         
                         nowGroup.append("line")
                             .attr("x1", xPos)
                             .attr("x2", xPos)
                             .attr("y1", flagY)
                             .attr("y2", yPos)
                             .attr("stroke", nowIndicatorColor)
                             .attr("stroke-width", 2);

                         nowGroup.append("circle")
                             .attr("cx", xPos)
                             .attr("cy", yPos)
                             .attr("r", 5)
                             .attr("fill", nowIndicatorColor);
                             
                         nowGroup.append("rect")
                             .attr("x", flagX)
                             .attr("y", flagY)
                             .attr("width", Math.max(0, flagWidth))
                             .attr("height", Math.max(0, flagHeight))
                             .attr("fill", nowIndicatorColor); 
                             
                         nowGroup.append("text")
                             .attr("x", flagX + (flagWidth / 2))
                             .attr("y", flagY + 10.5) 
                             .attr("fill", "#000000") 
                             .attr("font-size", "0.6rem")
                             .attr("font-weight", "bold")
                             .attr("text-anchor", "middle")
                             .text("Now");
                    }
                }
            }

            function updateUI(renderDate) {
                const isMobile = window.innerWidth < 640;
                const dateFormatOptions = { weekday: 'long', month: 'long', day: 'numeric' };
                if (!isMobile) dateFormatOptions.year = 'numeric';
                dateDisplay.textContent = renderDate.toLocaleString(undefined, dateFormatOptions);
                const yyyy = renderDate.getFullYear(), mm = String(renderDate.getMonth() + 1).padStart(2, '0'), dd = String(renderDate.getDate()).padStart(2, '0');
                datePicker.value = `${yyyy}-${mm}-${dd}`;
                if(countdownInterval) {
                    clearInterval(countdownInterval);
                    countdownInterval = null;
                }
                const nowForUI = getPTNow();
                const isCurrentDay = renderDate.toDateString() === nowForUI.toDateString();
                
                // Smoothly animate the appearance/disappearance of the status boxes
                if (isCurrentDay) {
                    statusBoxesContainer.style.display = 'grid';
                    statusBoxesContainer.offsetHeight; // Force reflow to ensure CSS transition triggers
                    statusBoxesContainer.classList.add('visible');
                    
                    updateNextTideEvent();
                    countdownInterval = setInterval(updateNextTideEvent, 60000); 
                } else {
                    statusBoxesContainer.classList.remove('visible');
                    setTimeout(() => {
                        if (!statusBoxesContainer.classList.contains('visible')) {
                            statusBoxesContainer.style.display = 'none';
                        }
                    }, 400); // 400ms matches the CSS transition duration
                }
                
                // Reflected the updated Circular Icons logic in the Legend UI
                document.getElementById('legend').innerHTML = `
                    <div><div style="width: 0.75rem; height: 0.75rem; background-color: var(--color-chart-open-overlay);"></div><span>Club Open</span></div>
                    <div><div style="width: 1rem; height: 1px; background-color: var(--color-observed-line); opacity: 0.9;"></div><span>Observed tide</span></div>
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
                    <div><div style="width: 0.75rem; height: 0.75rem; background-color: var(--color-chart-danger-area);"></div><span>Club Closed &lt; 1.5\u2032</span></div>`;
            }

            async function updateNextTideEvent() {
                 try {
                    const now = getPTNow();

                    const [prevTides, currentTides, nextTides, nextNextTides] = await Promise.all([ 
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() - 1)), 
                        fetchTideData(now), 
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() + 1)),
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() + 2)) 
                    ]);
                    if (!prevTides || !currentTides || !nextTides || !nextNextTides) { 
                        nextTideDisplay.innerHTML = ""; 
                        currentTideStatus.innerHTML = "";
                        observedStatusEl.innerHTML = "";
                        return; 
                    }
                    const combinedTideDataForLookup = [...prevTides, ...currentTides, ...nextTides, ...nextNextTides];
                    
                    // Exact real-time interpolation
                    const currentHeight = getTideHeightAtTime(combinedTideDataForLookup, now);
                    const timeIn5Mins = new Date(now.getTime() + 5 * 60000);
                    const futureHeight = getTideHeightAtTime(combinedTideDataForLookup, timeIn5Mins);
                    
                    const currentHeightDisplay = currentHeight.toFixed(1);
                    let directionArrow = '';
                    if (futureHeight > currentHeight) directionArrow = `<svg class="icon-sm" style="display: inline-block; vertical-align: middle; color: var(--icon-color-high);" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2"><path stroke-linecap="round" stroke-linejoin="round" d="M5 10l7-7m0 0l7 7m-7-7v18"></path></svg>`;
                    else if (futureHeight < currentHeight) directionArrow = `<svg class="icon-sm" style="display: inline-block; vertical-align: middle; color: var(--icon-color-low);" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2"><path stroke-linecap="round" stroke-linejoin="round" d="M19 14l-7 7m0 0l-7-7m7 7V3"></path></svg>`;
                    
                    currentTideStatus.innerHTML = `<div style="display: flex; align-items: center; justify-content: center; font-weight: 600; font-size: 1.25rem;">${directionArrow}<span style="margin-left: 0.25rem;">${currentHeightDisplay}\u2032</span></div>`;
                    
                    // Handle accurate real-time observed status mapping anomaly to current interpolation
                    if (currentDate.toDateString() === now.toDateString()) {
                        const obsAnomalies = await fetchObservedTideData(now, true);
                        if (obsAnomalies && obsAnomalies.length > 0) {
                            const latestAnomaly = obsAnomalies[obsAnomalies.length - 1].anomaly;
                            
                            // Recalculate based on displayed numbers to prevent rounding inaccuracies
                            const roundedPredicted = parseFloat(currentHeight.toFixed(1));
                            const roundedObserved = parseFloat((currentHeight + latestAnomaly).toFixed(1));
                            const visualAnomaly = roundedObserved - roundedPredicted;
                            
                            const sign = visualAnomaly > 0 ? '+' : '';
                            
                            observedStatusEl.innerHTML = `<div style="font-size: 0.65rem; color: var(--color-text-secondary);">Observed: ${roundedObserved.toFixed(1)}\u2032 <span style="font-size: 0.6rem; color: var(--color-text-tertiary);">(${sign}${visualAnomaly.toFixed(1)}\u2032)</span></div>`;
                        } else {
                            observedStatusEl.innerHTML = `<div style="font-size: 0.65rem; color: var(--color-text-secondary);">Waiting for observed data...</div>`;
                        }
                        
                        // Handle Dynamic Club Schedule Countdown
                        let scheduleColorState = 'neutral';
                        let hasScheduleData = true;

                        if (!currentClubStatus) {
                            clubScheduleStatusEl.innerHTML = "-";
                            hasScheduleData = false;
                        } else if (currentClubStatus.isClosed) {
                            clubScheduleStatusEl.innerHTML = `<div style="font-weight: 600; color: var(--color-text-primary);">Closed</div><div style="font-size:0.75rem; color:var(--color-text-secondary); margin-top:2px;">for the day</div>`;
                            scheduleColorState = 'neutral';
                        } else {
                            const timeDiffMs = (targetDate) => Math.max(0, targetDate - now);
                            const formatTimeDiff = (diff) => {
                                const h = Math.floor(diff / 3600000);
                                const m = Math.floor((diff % 3600000) / 60000);
                                return `${h > 0 ? h + 'h ' : ''}${m}m`;
                            };

                            let nextEventText = "";
                            let nextEventTime = "";

                            if (currentClubStatus.openTime && now < currentClubStatus.openTime) {
                                nextEventText = "Club Opens";
                                nextEventTime = `in ${formatTimeDiff(timeDiffMs(currentClubStatus.openTime))}`;
                                scheduleColorState = 'neutral';
                            } else if (currentClubStatus.midDayDockTime && currentClubStatus.midDayOpenTime) {
                                if (now >= currentClubStatus.openTime && now < currentClubStatus.midDayDockTime) {
                                    const diff = timeDiffMs(currentClubStatus.midDayDockTime);
                                    if (diff < 3600000) { // Less than 60 minutes
                                        nextEventText = "Mid-Day Dock";
                                        nextEventTime = `in ${formatTimeDiff(diff)}`;
                                    } else {
                                        nextEventText = "Open";
                                        nextEventTime = `for ${formatTimeDiff(diff)}`;
                                    }
                                    scheduleColorState = 'open';
                                } else if (now >= currentClubStatus.midDayDockTime && now < currentClubStatus.midDayOpenTime) {
                                    nextEventText = "Re-opens";
                                    nextEventTime = `in ${formatTimeDiff(timeDiffMs(currentClubStatus.midDayOpenTime))}`;
                                    scheduleColorState = 'dock';
                                } else if (now >= currentClubStatus.midDayOpenTime && now < currentClubStatus.dockTime) {
                                    const diff = timeDiffMs(currentClubStatus.dockTime);
                                    if (diff < 3600000) {
                                        nextEventText = "Dock Time";
                                        nextEventTime = `in ${formatTimeDiff(diff)}`;
                                    } else {
                                        nextEventText = "Open";
                                        nextEventTime = `for ${formatTimeDiff(diff)}`;
                                    }
                                    scheduleColorState = 'open';
                                } else if (now >= currentClubStatus.dockTime) {
                                    nextEventText = "Closed";
                                    nextEventTime = "for the day";
                                    scheduleColorState = 'dock';
                                }
                            } else {
                                if (now >= currentClubStatus.openTime && now < currentClubStatus.dockTime) {
                                    const diff = timeDiffMs(currentClubStatus.dockTime);
                                    if (diff < 3600000) {
                                        nextEventText = "Dock Time";
                                        nextEventTime = `in ${formatTimeDiff(diff)}`;
                                    } else {
                                        nextEventText = "Open";
                                        nextEventTime = `for ${formatTimeDiff(diff)}`;
                                    }
                                    scheduleColorState = 'open';
                                } else if (now >= currentClubStatus.dockTime) {
                                    nextEventText = "Closed";
                                    nextEventTime = "for the day";
                                    scheduleColorState = 'dock';
                                }
                            }

                            if (nextEventText) {
                                clubScheduleStatusEl.innerHTML = `<div style="font-weight: 600; color: var(--color-text-primary);">${nextEventText}</div><div style="font-size:0.75rem; color:var(--color-text-secondary); margin-top:2px;">${nextEventTime}</div>`;
                            } else {
                                clubScheduleStatusEl.innerHTML = "-";
                                hasScheduleData = false;
                            }
                        }

                        // Apply Dynamic Box Styling safely for Mobile Safari
                        if (hasScheduleData && scheduleColorState !== 'neutral') {
                            clubScheduleBoxEl.style.setProperty('background-color', scheduleColorState === 'open' ? 'var(--color-open-bg)' : 'var(--color-dock-bg)', 'important');
                            clubScheduleBoxEl.style.setProperty('border-color', scheduleColorState === 'open' ? 'var(--color-open-line)' : 'var(--color-dock-line)', 'important');
                            clubScheduleLabelEl.style.setProperty('color', scheduleColorState === 'open' ? 'var(--color-open-line)' : 'var(--color-dock-line)', 'important');
                        } else {
                            clubScheduleBoxEl.style.removeProperty('background-color');
                            clubScheduleBoxEl.style.removeProperty('border-color');
                            clubScheduleLabelEl.style.removeProperty('color');
                        }
                    } else {
                        observedStatusEl.innerHTML = '';
                        clubScheduleStatusEl.innerHTML = '';
                        clubScheduleBoxEl.style.removeProperty('background-color');
                        clubScheduleBoxEl.style.removeProperty('border-color');
                        clubScheduleLabelEl.style.removeProperty('color');
                    }

                    const allRawTides = [...prevTides, ...currentTides, ...nextTides, ...nextNextTides];
                    const allTideExtremes = findTideExtremes(allRawTides);
                    const nextEvent = allTideExtremes.find(event => event.time > now);
                    if (nextEvent) {
                        const diff = nextEvent.time - now, hours = Math.floor(diff / 3600000), minutes = Math.floor((diff % 3600000) / 60000);
                        nextTideDisplay.innerHTML = `<div style="font-weight: 600;">${nextEvent.type} Tide ${nextEvent.height.toFixed(1)}\u2032</div><div style="font-size:0.75rem; color:var(--color-text-secondary); margin-top:2px;">in ${hours}h ${minutes}m</div>`;
                    } else {
                        nextTideDisplay.innerHTML = "-";
                    }
                    updateNowIndicator(currentDate);
                } catch (error) {
                    console.error("Error during periodic tide update:", error);
                    currentTideStatus.innerHTML = "-";
                    nextTideDisplay.innerHTML = "-";
                }
            }

            function clearHeaderInfo() {
                dateDisplay.textContent = '';
                currentTideStatus.innerHTML = '';
                observedStatusEl.innerHTML = '';
                clubScheduleStatusEl.innerHTML = '';
                clubScheduleBoxEl.style.removeProperty('background-color');
                clubScheduleBoxEl.style.removeProperty('border-color');
                clubScheduleLabelEl.style.removeProperty('color');
                nextTideDisplay.innerHTML = '';
                
                clubStatusBanner.classList.remove('visible');
                clubStatusBanner.style.display = 'none';
                clubStatusBanner.className = 'status-banner';
            }

            document.getElementById('prev-day').addEventListener('click', () => {
                if (isRendering) return;
                currentDate.setDate(currentDate.getDate() - 1);
                drawChart(new Date(currentDate), -1);
            });
            document.getElementById('next-day').addEventListener('click', () => {
                if (isRendering) return;
                currentDate.setDate(currentDate.getDate() + 1);
                drawChart(new Date(currentDate), 1);
            });
            datePicker.addEventListener('change', (event) => {
                if (isRendering) return;
                const dateString = event.target.value;
                if (!dateString) return;
                
                const [year, month, day] = dateString.split('-').map(Number);
                
                // Safely update the date without running into the JS 31st Day Bug
                const selectedDate = new Date(currentDate.getTime());
                selectedDate.setFullYear(year, month - 1, day);
                
                if (!isNaN(selectedDate.getTime()) && selectedDate.toDateString() !== currentDate.toDateString()) {
                    const direction = selectedDate > currentDate ? 1 : -1;
                    currentDate = selectedDate;
                    drawChart(new Date(currentDate), direction);
                }
            });
            
            // PERFORMANCE FIX: Debounce the resize event to prevent heavy CPU usage when manipulating the browser window
            window.addEventListener('resize', () => {
                clearTimeout(resizeTimeout);
                resizeTimeout = setTimeout(() => {
                    // Instantly snap to the current view during resize to avoid breaking transitions
                    chartContainer.selectAll(".slide-group").interrupt();
                    isRendering = false; 
                    drawChart(currentDate, 0);
                }, 200);
            });

            // Midnight checker: Auto-refresh chart to the new "today" if local day rolls over while browser is left open
            setInterval(() => {
                const currentRealDateString = getPTNow().toDateString();
                if (currentRealDateString !== lastRealDateString && !isRendering) {
                    lastRealDateString = currentRealDateString;
                    currentDate = getPTNow();
                    drawChart(currentDate, 0);
                }
            }, 60000);

            drawChart(currentDate, 0);
        });
        /* #end raw */
    </script>
</div>

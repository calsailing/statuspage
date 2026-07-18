
<div class="bx--tile tile-radar-forecast">
   
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
            /* Foreground text drawn on the solid open/dock/now flag backgrounds */
            --color-on-flag: #000000;
            /* Stroke of the "X" marker drawn on top of the red danger circle */
            --color-on-danger: #ffffff;
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
            /* Flag backgrounds stay bright in dark mode, so keep dark text and a light X */
            --color-on-flag: #000000;
            --color-on-danger: #ffffff;
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
        #tide-chart-widget-container .date-display svg { width: 1.25rem; height: 1.25rem; color: var(--text-tertiary); }
        
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
        #tide-chart-widget-container #events-list td:first-child { width: 1.5rem; text-align: center; }
        #tide-chart-widget-container #events-list td:first-child svg { display: block; margin: 0 auto; }
        #tide-chart-widget-container #events-list td:nth-child(2) { padding-left: 0.75rem; padding-right: 1rem; }
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
        /* --- CUSTOM HOVER TOOLTIP (TABLE) --- */
        #tide-chart-widget-container .event-warning-tooltip {
            position: relative;
            display: inline-flex;
            align-items: center;
            cursor: help;
            vertical-align: middle;
            margin-left: 0.25rem;
        }
        #tide-chart-widget-container .event-warning-tooltip .tooltip-content {
            visibility: hidden;
            width: 200px; /* Increased from 175px to fit the new longer message cleanly */
            background-color: var(--color-box-bg);
            color: var(--color-text-danger);
            text-align: center;
            border: 1px solid var(--color-box-border);
            box-shadow: 0 4px 6px -1px rgb(0 0 0 / 0.1), 0 2px 4px -2px rgb(0 0 0 / 0.1);
            padding: 0.4rem 0.5rem;
            position: absolute;
            z-index: 9999;
            bottom: 130%;
            left: 50%;
            transform: translateX(-50%);
            opacity: 0;
            transition: opacity 0.2s ease-in-out;
            font-size: 0.65rem;
            line-height: 1.3;
            border-radius: 4px;
            white-space: normal;
            pointer-events: none;
        }
        #tide-chart-widget-container .event-warning-tooltip .tooltip-content::before {
            content: "";
            position: absolute;
            top: 100%;
            left: 50%;
            transform: translateX(-50%);
            border-width: 6px;
            border-style: solid;
            border-color: var(--color-box-border) transparent transparent transparent;
        }
        #tide-chart-widget-container .event-warning-tooltip .tooltip-content::after {
            content: "";
            position: absolute;
            top: 100%;
            left: 50%;
            transform: translateX(-50%);
            border-width: 5px;
            border-style: solid;
            border-color: var(--color-box-bg) transparent transparent transparent;
            margin-top: -2px;
        }
        #tide-chart-widget-container .event-warning-tooltip:hover .tooltip-content {
            visibility: visible;
            opacity: 1;
        }
        .dark #tide-chart-widget-container .event-warning-tooltip .tooltip-content {
            box-shadow: 0 4px 6px -1px rgb(0 0 0 / 0.5), 0 2px 4px -2px rgb(0 0 0 / 0.5);
        }
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
            max-width: 200px;
            word-wrap: break-word;
            white-space: normal;
        }
        @media (min-width: 640px) {
            #tide-chart-tooltip {
                max-width: 400px; /* twice as large on desktop */
            }
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
            word-wrap: break-word;
            white-space: normal;
        }
        #tide-chart-tooltip .pill {
            display: inline-block;
            font-size: 0.6rem;
            font-weight: 700;
            padding: 0.15rem 0.4rem;
            border-radius: 9999px;
            text-transform: uppercase;
            line-height: 1;
            vertical-align: middle;
        }
        #tide-chart-tooltip .pill-start {
            background-color: #dcfce7;
            color: #15803d;
        }
        .dark #tide-chart-tooltip .pill-start {
            background-color: rgba(34, 197, 94, 0.2);
            color: #4ade80;
        }
        #tide-chart-tooltip .pill-end {
            background-color: #ffedd5;
            color: #ea580c;
        }
        .dark #tide-chart-tooltip .pill-end {
            background-color: rgba(249, 115, 22, 0.2);
            color: #fb923c;
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
        
        /* --- WATER WAVE FILLING ANIMATION --- */
        #tide-chart-widget-container .liquid-loader {
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 1.25rem;
            height: 100%;
            flex-direction: column;
        }
        #tide-chart-widget-container .wave-container {
            position: relative;
            width: 64px;
            height: 64px;
            background-color: var(--color-chart-night);
            border: 2px solid var(--color-chart-tide-line);
            border-radius: 50%;
            overflow: hidden;
            transform: translateZ(0); /* Webkit/Safari circular clipping mask guard */
        }
        #tide-chart-widget-container .wave,
        #tide-chart-widget-container .wave-behind {
            position: absolute;
            width: 128px;
            height: 128px;
            background: linear-gradient(135deg, #0ea5e9, #38bdf8);
            border-radius: 43%;
            left: -32px;
            bottom: -128px; /* Start completely empty (0% filled) */
            transition: bottom 0.6s cubic-bezier(0.4, 0, 0.2, 1); /* Animate height smoothly on change */
            animation: wave-spin 6s infinite linear;
            transform-origin: 50% 50%;
            opacity: 0.85;
        }
        #tide-chart-widget-container .wave-behind {
            background: var(--color-chart-tide-line);
            opacity: 0.45;
            animation: wave-spin 10s infinite linear;
            border-radius: 40%;
            bottom: -124px; /* Start at 0% with depth offset */
        }
        @keyframes wave-spin {
            from { transform: rotate(0deg); }
            to { transform: rotate(360deg); }
        }
        #tide-chart-widget-container .liquid-loader-text {
            color: var(--color-text-tertiary);
            font-size: 0.75rem;
            font-weight: 600;
            text-transform: uppercase;
            letter-spacing: 0.1em;
            animation: pulse-opacity 2s infinite ease-in-out;
        }
        @keyframes pulse-opacity {
            0%, 100% { opacity: 0.4; }
            50% { opacity: 1; }
        }

        /* --- LESSONS CARD STYLES --- */
        #tide-chart-widget-container .lessons-card {
            background-color: var(--color-box-bg);
            border: 1px solid var(--color-box-border);
            box-shadow: var(--shadow-sm);
            border-left: 4px solid #0284c7;
            padding: 0.75rem 1rem;
            margin-top: 0.75rem;
            display: flex;
            align-items: center;
            gap: 1rem;
            border-radius: 4px;
        }
        .dark #tide-chart-widget-container .lessons-card {
            border-left-color: #38bdf8;
        }
        #tide-chart-widget-container .lessons-card-icon {
            display: flex;
            align-items: center;
            justify-content: center;
            background-color: rgba(2, 132, 199, 0.1);
            color: #0284c7;
            border-radius: 50%;
            width: 46px;
            height: 46px;
            flex-shrink: 0;
        }
        .dark #tide-chart-widget-container .lessons-card-icon {
            background-color: rgba(56, 189, 248, 0.15);
            color: #38bdf8;
        }
        #tide-chart-widget-container .lessons-card-content {
            flex-grow: 1;
            min-width: 0; /* Critical: Prevent inner grids/flex elements from overflowing layout */
        }
        #tide-chart-widget-container .lessons-card-title {
            font-size: 0.85rem;
            font-weight: 600;
            color: var(--color-text-primary);
            margin-bottom: 0.35rem;
            display: flex;
            align-items: center;
            justify-content: space-between;
            gap: 0.5rem;
        }
        #tide-chart-widget-container .lessons-card-grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 0.5rem;
        }
        #tide-chart-widget-container .lessons-stat {
            background-color: var(--color-box-bg-subtle);
            border: 1px solid var(--color-box-border);
            padding: 0.25rem 0.5rem;
            border-radius: 4px;
            text-align: center;
            transition: all 0.2s ease-in-out;
        }
        #tide-chart-widget-container .lessons-stat-val {
            font-size: 0.95rem;
            font-weight: 700;
            color: var(--color-text-primary);
            line-height: 1.2;
        }
        #tide-chart-widget-container .lessons-stat-lbl {
            font-size: 0.55rem;
            color: var(--color-text-tertiary);
            text-transform: uppercase;
            letter-spacing: 0.05em;
        }
        #tide-chart-widget-container .lessons-badge {
            display: inline-block;
            font-size: 0.6rem;
            font-weight: 700;
            padding: 0.1rem 0.4rem;
            border-radius: 9999px;
            text-transform: uppercase;
            line-height: 1.2;
            white-space: nowrap; /* Prevents "In Progress" badge from breaking into lines */
            flex-shrink: 0;
        }
        #tide-chart-widget-container .lessons-badge-active {
            background-color: rgba(34, 197, 94, 0.15);
            color: #22c55e;
        }
        #tide-chart-widget-container .lessons-badge-inactive {
            background-color: rgba(107, 114, 128, 0.15);
            color: var(--color-text-secondary);
        }

        /* --- CONDITIONAL ALERT STYLES --- */
        #tide-chart-widget-container .lessons-stat.stat-danger {
            background-color: rgba(239, 68, 68, 0.12) !important;
            border-color: rgba(239, 68, 68, 0.35) !important;
        }
        #tide-chart-widget-container .lessons-stat.stat-danger .lessons-stat-val {
            color: #ef4444 !important;
        }
        .dark #tide-chart-widget-container .lessons-stat.stat-danger {
            background-color: rgba(239, 68, 68, 0.22) !important;
            border-color: rgba(239, 68, 68, 0.5) !important;
        }
        .dark #tide-chart-widget-container .lessons-stat.stat-danger .lessons-stat-val {
            color: #fca5a5 !important;
        }

        /* --- MOBILE LAYOUT OVERRIDES --- */
        @media (max-width: 480px) {
            #tide-chart-widget-container .lessons-card {
                padding: 0.6rem 0.75rem;
                gap: 0.75rem;
            }
            #tide-chart-widget-container .lessons-card-icon {
                width: 38px;
                height: 38px;
            }
            #tide-chart-widget-container .lessons-card-icon svg {
                width: 26px;
                height: 26px;
            }
            #tide-chart-widget-container .lessons-card-title {
                font-size: 0.8rem;
            }
            #tide-chart-widget-container .lessons-card-grid {
                gap: 0.35rem;
            }
            #tide-chart-widget-container .lessons-stat {
                padding: 0.2rem 0.25rem;
            }
            #tide-chart-widget-container .lessons-stat-val {
                font-size: 0.85rem;
            }
            #tide-chart-widget-container .lessons-stat-lbl {
                font-size: 0.5rem;
                letter-spacing: 0.02em;
            }
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

            <!-- Lessons real-time status card -->
            <div id="lessons-status-box" style="display: none;"></div>
        </div>
        <div class="aspect-wrapper">
            <div id="chart-container" style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></div>
            
            <!-- Tooltip (Now securely housed inside the relative wrapper) -->
            <div id="tide-chart-tooltip" style="display: none;" aria-hidden="true">
                <p id="tooltip-time"></p>
                <p id="tooltip-height"></p>
                <p id="tooltip-warning" style="display: none; font-size: 0.65rem; color: var(--color-text-danger); margin-top: 0.25rem; width: 100%; white-space: normal; line-height: 1.2;"></p>
            </div>
        </div>
        
        <div id="legend"></div>
        
        <div id="events-list"></div>
    </div>
    <script>
        /* #raw */
        document.addEventListener('DOMContentLoaded', () => {
            // --- SOURCE CONFIGURATION FLAGS ---
            // Set these to true or false to enable/disable specific data source integrations
            const ENABLE_NOAA_PREDICTIONS = true; // Primary tide predictions from NOAA
            const ENABLE_OBSERVED_TIDES   = true; // Observed tide anomalies from Richmond NOAA station
            const ENABLE_CLUB_STATUS      = true; // Cal Sailing Club status API (opens, docks, restrictions, closures)
            const ENABLE_CLUB_EVENTS      = true; // Scheduled club calendar events from DP Calendar API
            const ENABLE_DINGHY_LESSONS   = true; // Real-time dinghy lessons status API (active lessons, instructors, waiting)

            // --- ENVIRONMENT CONFIGURATION ---
            // Set to true to load from the live environment (www.cal-sailing.org), or false to use the test environment (test.cal-sailing.org)
            const USE_LIVE_ENVIRONMENT = true; 
            const CAL_SAILING_DOMAIN = USE_LIVE_ENVIRONMENT ? "www.cal-sailing.org" : "test.cal-sailing.org";

            // ALWAYS initialize core dates to Pacific Time to ensure out-of-state visitors see precise local Berkeley predictions.
            // Uses Intl.formatToParts to read the wall-clock fields in America/Los_Angeles directly, avoiding the
            // fragile toLocaleString -> Date re-parse round-trip that could drift by an hour near DST boundaries.
            const _ptFormatter = new Intl.DateTimeFormat("en-US", {
                timeZone: "America/Los_Angeles",
                year: "numeric", month: "numeric", day: "numeric",
                hour: "numeric", minute: "numeric", second: "numeric",
                hour12: false
            });
            // Returns a timezone-adjusted Pacific Time Date object
            function getPTNow() {
                const parts = {};
                for (const p of _ptFormatter.formatToParts(new Date())) {
                    if (p.type !== "literal") parts[p.type] = p.value;
                }
                // Intl can emit "24" for midnight hour; normalize to 0
                const hour = parts.hour === "24" ? 0 : parseInt(parts.hour, 10);
                return new Date(
                    parseInt(parts.year, 10),
                    parseInt(parts.month, 10) - 1,
                    parseInt(parts.day, 10),
                    hour,
                    parseInt(parts.minute, 10),
                    parseInt(parts.second, 10)
                );
            }
            // Escapes untrusted strings before they are interpolated into innerHTML.
            function escapeHtml(str) {
                return String(str ?? '')
                    .replace(/&/g, '&amp;')
                    .replace(/</g, '&lt;')
                    .replace(/>/g, '&gt;')
                    .replace(/"/g, '&quot;')
                    .replace(/'/g, '&#39;');
            }
            // Returns a safe href for untrusted URLs: only allows http(s) and site-relative paths, else '#'.
            function sanitizeUrl(url) {
                const raw = String(url ?? '').trim();
                if (!raw) return '#';
                if (raw.startsWith('/')) return raw; // site-relative path
                try {
                    const parsed = new URL(raw, `https://${CAL_SAILING_DOMAIN}`);
                    if (parsed.protocol === 'http:' || parsed.protocol === 'https:') return parsed.href;
                } catch (e) { /* fall through */ }
                return '#';
            }
            // Runs an async operation with retry-and-backoff. The operation should throw to trigger a retry.
            // Returns the operation's result, or `fallback` after all attempts are exhausted.
            async function withRetry(operation, { maxRetries = 3, retryDelay = 1000, label = 'operation', fallback = null } = {}) {
                for (let attempt = 1; attempt <= maxRetries; attempt++) {
                    try {
                        return await operation(attempt);
                    } catch (error) {
                        console.warn(`Failed ${label} on attempt ${attempt}:`, error.message);
                        if (attempt < maxRetries) {
                            await new Promise(resolve => setTimeout(resolve, retryDelay));
                        } else {
                            console.warn(`All ${maxRetries} attempts for ${label} failed.`);
                        }
                    }
                }
                return fallback;
            }
            // Fetches raw text, trying a direct request first, then the allorigins JSON-wrapped proxy.
            // Throws if both routes fail so callers can apply their own final fallback (e.g. mock data).
            async function fetchTextWithProxyFallback(url) {
                try {
                    const response = await fetch(url);
                    if (!response.ok) throw new Error("Direct fetch failed");
                    return await response.text();
                } catch (e) {
                    const proxyUrl = `https://api.allorigins.win/get?url=${encodeURIComponent(url)}`;
                    const proxyResponse = await fetch(proxyUrl);
                    if (!proxyResponse.ok) throw new Error("Proxy fetch failed");
                    const proxyData = await proxyResponse.json();
                    if (!proxyData.contents) throw new Error("Proxy returned empty contents");
                    return proxyData.contents;
                }
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
            let activeRenderId = 0;   // Unique ID to track concurrent rendering chains
            
            // --- Caching Stores ---
            const tideDataCache = {};
            const observedDataCache = {};
            const clubStatusCache = {}; 
            const clubEventsCache = {}; // Cache for scheduled club events
            
            const NOAA_STATION_ID = "9414816";
            const RICHMOND_STATION_ID = "9414863";
            const LOCATION_LAT = 37.8716;
            const LOCATION_LNG = -122.2727;
            let isHoveringOnEvent = false;
            let currentClubStatus = null;
            let svg, xScale, yScale, chartDataForUpdate;

            // --- Lessons Real-time Control Variables ---
            let lessonsInterval = null;

            // --- THEME REACTIVITY ---
            let resizeTimeout;
            // Resolved-palette cache. getComputedStyle is expensive, so we read the CSS custom
            // properties once and reuse them until the theme actually changes (invalidatePalette()).
            const PALETTE_PROPS = [
                '--color-chart-night', '--color-chart-day', '--color-chart-open-overlay',
                '--color-chart-rising', '--color-chart-falling', '--color-chart-tide-line',
                '--color-chart-danger-area', '--color-text-danger', '--color-event-circle-fill',
                '--color-event-circle-stroke', '--color-hover-line', '--color-hover-circle-fill',
                '--color-hover-circle-stroke', '--color-now-indicator', '--color-icon-bg',
                '--color-event-text', '--color-on-flag', '--color-on-danger'
            ];
            let _paletteCache = null;
            function getPalette() {
                if (_paletteCache) return _paletteCache;
                const widgetContainer = document.querySelector('#tide-chart-widget-container');
                if (!widgetContainer) return {};
                const cs = getComputedStyle(widgetContainer);
                const palette = {};
                for (const prop of PALETTE_PROPS) {
                    palette[prop] = cs.getPropertyValue(prop).trim();
                }
                _paletteCache = palette;
                return palette;
            }
            function invalidatePalette() { _paletteCache = null; }
            // Reports whether the dark theme is currently active (class hook OR OS preference).
            const isDarkMode = () => document.documentElement.classList.contains('dark')
                || window.matchMedia('(prefers-color-scheme: dark)').matches;
            let _wasDark = isDarkMode();
            const redrawChartOnThemeChange = () => {
                invalidatePalette();
                if (chartContainer.node() && chartContainer.select("svg").node()) {
                    drawChart(currentDate, 0);
                }
            };
            // Only react when the dark-mode state actually flips, ignoring unrelated <html> class churn.
            const observer = new MutationObserver((mutationsList) => {
                for (const mutation of mutationsList) {
                    if (mutation.type === 'attributes' && mutation.attributeName === 'class') {
                        const nowDark = isDarkMode();
                        if (nowDark !== _wasDark) {
                            _wasDark = nowDark;
                            redrawChartOnThemeChange();
                        }
                        return;
                    }
                }
            });
            observer.observe(document.documentElement, { attributes: true, attributeFilter: ['class'] });
            window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', () => {
                _wasDark = isDarkMode();
                redrawChartOnThemeChange();
            });
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
                
                // Hardened math clamping against potential latitude/longitude domain boundary NaN exceptions
                const clampedCosValue = Math.max(-1, Math.min(1, Math.cos(zenith * toRad) / (Math.cos(latRad) * Math.cos(decRad)) - Math.tan(latRad) * Math.tan(decRad)));
                const hourAngleRad = Math.acos(clampedCosValue);
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
            // Preloads next day data directly into caching structures in the background
            function preloadNextDay(date) {
                const nextDay = new Date(date.getTime());
                nextDay.setDate(nextDay.getDate() + 1);
                
                Promise.all([
                    fetchTideData(nextDay),
                    fetchClubStatus(nextDay),
                    fetchObservedTideData(nextDay),
                    fetchClubEvents(nextDay)
                ]).catch(() => {}); // catch silently to ensure background API failures never disrupt runtime
            }
            
            // --- STREAMING_CHUNK: Hardening data fetch operations with safe offline recovery ---
            async function fetchTideData(date) {
                if (!ENABLE_NOAA_PREDICTIONS) {
                    return [];
                }
                const cacheKey = getLocalCacheKey(date);
                if (tideDataCache[cacheKey]) {
                    return tideDataCache[cacheKey];
                }
                
                const url = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=predictions&application=NOS.CO-OPS.CAT&begin_date=${cacheKey}&end_date=${cacheKey}&datum=MLLW&station=${NOAA_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;
                return await withRetry(async () => {
                    const response = await fetch(url);
                    if (!response.ok) throw new Error(`NOAA API request failed: ${response.statusText}`);
                    const data = await response.json();
                    if (data.error || !data.predictions || !Array.isArray(data.predictions)) {
                        console.warn(`NOAA returned no valid predictions for ${cacheKey}`);
                        tideDataCache[cacheKey] = [];
                        return [];
                    }
                    const formattedData = data.predictions.map(p => ({ time: parseNOAADate(p.t), height: parseFloat(p.v) })).filter(p => p.time !== null && !isNaN(p.height));
                    tideDataCache[cacheKey] = formattedData;
                    return formattedData;
                }, { label: 'tide data', fallback: [] }); // Soft fallback of empty array to prevent code crashes
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
            async function fetchClubEvents(date) {
                if (!ENABLE_CLUB_EVENTS) {
                    return [];
                }
                const cacheKey = getLocalCacheKey(date);
                if (clubEventsCache[cacheKey]) {
                    return clubEventsCache[cacheKey];
                }
                const yyyy = date.getFullYear();
                const mm = String(date.getMonth() + 1).padStart(2, '0');
                const dd = String(date.getDate()).padStart(2, '0');
                const startDateStr = encodeURIComponent(`${yyyy}-${mm}-${dd}T00:00:00`);
                
                const nextDate = new Date(date);
                nextDate.setDate(nextDate.getDate() + 1);
                const n_yyyy = nextDate.getFullYear();
                const n_mm = String(nextDate.getMonth() + 1).padStart(2, '0');
                const n_dd = String(nextDate.getDate()).padStart(2, '0');
                const endDateStr = encodeURIComponent(`${n_yyyy}-${n_mm}-${n_dd}T00:00:00`);
                const targetUrl = `https://${CAL_SAILING_DOMAIN}/index.php?option=com_dpcalendar&view=events&format=raw&limit=0&Itemid=1402&filter%5Bcalendars%5D%5B%5D=61&filter%5Bcalendars%5D%5B%5D=sq-1&filter%5Bcalendars%5D%5B%5D=sq-2&filter%5Bcalendars%5D%5B%5D=sq-3&filter%5Bcalendars%5D%5B%5D=sq-4&list%5Bstart-date%5D=${startDateStr}&list%5Bend-date%5D=${endDateStr}&filter%5Bsearch%5D=&filter%5Blocation%5D=&filter%5Bradius%5D=20&filter%5Blength-type%5D=m&filter%5Bstate%5D=&filter%5Bcreated_by%5D=&Itemid=1402&filter%5Bcalendars%5D%5B%5D=-2`;
                try {
                    let jsonString = null;
                    try {
                        jsonString = await fetchTextWithProxyFallback(targetUrl);
                    } catch (proxyError) {
                        // Safe Sandbox mockup generator
                        const mockStart1 = new Date(date); mockStart1.setHours(10, 0, 0, 0);
                        const mockEnd1 = new Date(date); mockEnd1.setHours(12, 0, 0, 0);
                        const mockStart2 = new Date(date); mockStart2.setHours(13, 0, 0, 0);
                        const mockEnd2 = new Date(date); mockEnd2.setHours(16, 0, 0, 0);
                        jsonString = JSON.stringify({
                            data: {
                                events: [
                                    { title: "Intro to Sailing (Preview Mock)", start: mockStart1.toISOString(), end: mockEnd1.toISOString(), url: "/lessons", classNames: ["dp-event-calendar-sq-1"] },
                                    { title: "Open House (Preview Mock)", start: mockStart2.toISOString(), end: mockEnd2.toISOString(), url: "/openhouse", classNames: ["dp-event-calendar-sq-2"] }
                                ]
                            }
                        });
                    }
                    
                    jsonString = jsonString.replace(/<pre.*?>|<\/pre>/g, '');
                    const json = JSON.parse(jsonString);
                    
                    let rawEvents = [];
                    if (json.data && Array.isArray(json.data.events)) rawEvents = json.data.events;
                    else if (json.data && Array.isArray(json.data)) rawEvents = json.data;
                    else if (Array.isArray(json)) rawEvents = json;
                    
                    const events = rawEvents.map(e => {
                        let eventUrl = e.url || '';
                        if (eventUrl && !eventUrl.startsWith('http')) {
                            eventUrl = `https://${CAL_SAILING_DOMAIN}` + (eventUrl.startsWith('/') ? eventUrl : '/' + eventUrl);
                        }
                        return {
                            title: e.title || 'Untitled Event',
                            start: new Date(e.start),
                            end: new Date(e.end),
                            url: eventUrl,
                            classNames: Array.isArray(e.classNames) ? e.classNames : (typeof e.classNames === 'string' ? [e.classNames] : [])
                        };
                    });
                    
                    clubEventsCache[cacheKey] = events;
                    return events;
                } catch (error) {
                    console.warn("Failed to fetch club events:", error.message);
                    return [];
                }
            }
            async function fetchClubStatus(date) {
                if (!ENABLE_CLUB_STATUS) {
                    return { 
                        isClosed: false, 
                        openTime: null, 
                        dockTime: null, 
                        midDayDockTime: null, 
                        midDayOpenTime: null, 
                        alertMessage: '', 
                        sunsetTime: null 
                    };
                }
                const cacheKey = getLocalCacheKey(date);
                if (clubStatusCache[cacheKey]) {
                    return clubStatusCache[cacheKey];
                }
                
                const yyyymmdd = date.getFullYear() + '-' + ('0' + (date.getMonth() + 1)).slice(-2) + '-' + ('0' + date.getDate()).slice(-2);
                const targetUrl = `https://${CAL_SAILING_DOMAIN}/index.php?option=com_csctides&view=gettidedatalist&task=gettidedatalist&tmpl=component&output=json&tidedate=${yyyymmdd}`;
                const result = await withRetry(async () => {
                        let rawText = null;
                        try {
                            rawText = await fetchTextWithProxyFallback(targetUrl);
                        } catch (proxyError) {
                            rawText = JSON.stringify({
                                data: { clubclosed: false, opentime: "1:00 PM", docktime: "sunset", sunsettime: "sunset", restriction: "", middayclosetext: "null" }
                            });
                        }
                        const jsonString = rawText.replace(/<pre.*?>|<\/pre>/g, '');
                        const responseData = JSON.parse(jsonString);
                        const clubData = responseData.data;
                        if (!clubData) throw new Error("Malformed club status JSON.");
                        const parseClubTime = (timeStr, baseDate) => {
                            if (!timeStr) return null;
                            timeStr = timeStr.toLowerCase().trim();
                            if (timeStr === 'sunset') return 'sunset';
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
                }, { label: 'club status', fallback: null });
                
                // Return gracefully instead of bricking the card if club schedule server fails
                return result || { 
                    isClosed: false, 
                    openTime: null, 
                    dockTime: null, 
                    midDayDockTime: null, 
                    midDayOpenTime: null, 
                    alertMessage: 'Club schedule unavailable (API offline)', 
                    sunsetTime: null 
                };
            }
            async function fetchObservedTideData(date, forceRefresh = false) {
                if (!ENABLE_OBSERVED_TIDES) {
                    return [];
                }
                const nowPT = getPTNow();
                const startOfToday = d3.timeDay.floor(nowPT);
                if (d3.timeDay.floor(date) > startOfToday) {
                    return [];
                }
                const cacheKey = getLocalCacheKey(date);
                if (!forceRefresh && observedDataCache[cacheKey]) {
                    return observedDataCache[cacheKey];
                }
                const predUrl = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=predictions&application=NOS.CO-OPS.CAT&begin_date=${cacheKey}&end_date=${cacheKey}&datum=MLLW&station=${RICHMOND_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;
                const obsUrl = `https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=water_level&application=NOS.CO-OPS.CAT&begin_date=${cacheKey}&end_date=${cacheKey}&datum=MLLW&station=${RICHMOND_STATION_ID}&time_zone=lst_ldt&units=english&format=json`;
                return await withRetry(async () => {
                    const [predRes, obsRes] = await Promise.all([fetch(predUrl), fetch(obsUrl)]);
                    if (!predRes.ok) throw new Error(`NOAA Richmond Pred API failed`);
                    if (!obsRes.ok) throw new Error(`NOAA Richmond Obs API failed`);
                    const predData = await predRes.json();
                    const obsData = await obsRes.json();
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
                }, { label: 'observed data', fallback: [] });
            }

            // --- STREAMING_CHUNK: Managing the main progressive chart renderer and Y scale offsets ---
            async function drawChart(renderDate, direction = 0) {
                const currentRenderId = ++activeRenderId;
                
                if (isRendering) return; 
                isRendering = true;
                
                const navButtons = document.querySelectorAll('.nav-button, #date-picker');
                navButtons.forEach(btn => btn.disabled = true);
                
                try {
                    tooltip.style("opacity", 0); 
                    const isFirstLoad = !chartContainer.select("svg").node();
                    
                    if (isFirstLoad) {
                        chartContainer.html(""); 
                        const loadingHTML = `
                            <div class='liquid-loader'>
                                <div class='wave-container'>
                                    <div class='wave'></div>
                                    <div class='wave-behind'></div>
                                </div>
                                <div class='liquid-loader-text'>Loading Tides</div>
                            </div>
                        `;
                        chartContainer.html(loadingHTML);
                        
                        clubStatusBanner.classList.remove('visible');
                        clubStatusBanner.style.display = 'none';
                        clubStatusBanner.className = 'status-banner';
                        
                        observedStatusEl.innerHTML = '';
                        clubScheduleStatusEl.innerHTML = '';
                        eventsList.innerHTML = '';
                    }

                    let loadedCount = 0;
                    const trackProgress = async (promise) => {
                        try {
                            const result = await promise;
                            loadedCount++;
                            const progress = loadedCount / 4;
                            const bottomMain = -128 + (progress * 128);
                            const bottomBehind = -124 + (progress * 128);
                            const waveMain = document.querySelector('#tide-chart-widget-container .wave');
                            const waveBehind = document.querySelector('#tide-chart-widget-container .wave-behind');
                            if (waveMain) waveMain.style.bottom = `${bottomMain}px`;
                            if (waveBehind) waveBehind.style.bottom = `${bottomBehind}px`;
                            return result;
                        } catch (err) {
                            loadedCount++;
                            const progress = loadedCount / 4;
                            const bottomMain = -128 + (progress * 128);
                            const bottomBehind = -124 + (progress * 128);
                            const waveMain = document.querySelector('#tide-chart-widget-container .wave');
                            const waveBehind = document.querySelector('#tide-chart-widget-container .wave-behind');
                            if (waveMain) waveMain.style.bottom = `${bottomMain}px`;
                            if (waveBehind) waveBehind.style.bottom = `${bottomBehind}px`;
                            return null; // Return null on error to ensure Promise.all does not drop entirely
                        }
                    };

                    const [currentTides, clubStatus, observedAnomalies, clubEvents] = await Promise.all([
                        trackProgress(fetchTideData(renderDate)), 
                        trackProgress(fetchClubStatus(renderDate)), 
                        trackProgress(fetchObservedTideData(renderDate)),
                        trackProgress(fetchClubEvents(renderDate))
                    ]);
                    
                    if (currentRenderId !== activeRenderId) {
                        return;
                    }
                    preloadNextDay(renderDate);
                    
                    const tideDataUnavailable = !currentTides || currentTides.length === 0;
                    
                    // --- STREAMING_CHUNK: Drawing graph layouts and handling offline warnings ---
                    if (tideDataUnavailable) {
                        // Render NOAA Offline Warning in graph area instead of bricking entire application
                        chartContainer.html(`
                            <div class="noaa-offline-warning" style="display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100%; padding: 1.5rem; text-align: center; color: var(--color-text-danger);">
                                <svg style="width: 2.5rem; height: 2.5rem; margin-bottom: 0.5rem; color: var(--color-text-danger);" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                                    <path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"/>
                                </svg>
                                <p style="font-weight: 600; font-size: 0.9rem; margin-bottom: 0.25rem;">Tide Graph Offline</p>
                                <p style="font-size: 0.75rem; color: var(--color-text-secondary); max-width: 280px; line-height: 1.3;">NOAA prediction services are currently offline or unreachable.</p>
                            </div>
                        `);
                    }

                    const chartData = currentTides || [];
                    chartDataForUpdate = chartData;
                    const startOfDay = d3.timeDay.floor(renderDate);
                    const endOfDay = d3.timeDay.ceil(renderDate);
                    const prevDay = new Date(renderDate); prevDay.setDate(prevDay.getDate() - 1);
                    const nextDay = new Date(renderDate); nextDay.setDate(nextDay.getDate() + 1);
                    
                    let tideEvents = [];
                    if (!tideDataUnavailable) {
                        const [prevTides, nextTides] = await Promise.all([ fetchTideData(prevDay), fetchTideData(nextDay) ]);
                        const allTidesData = [...(prevTides || []), ...chartData, ...(nextTides || [])];
                        const allExtremes = findTideExtremes(allTidesData);
                        tideEvents = allExtremes.filter(event => event.time >= startOfDay && event.time < endOfDay);
                    }
                
                const berkeleyObserved = [];
                if (!tideDataUnavailable && observedAnomalies) {
                    observedAnomalies.forEach(obs => {
                        const predHeight = getTideHeightAtTime(chartData, obs.time);
                        if (predHeight !== undefined) {
                            berkeleyObserved.push({ time: obs.time, height: predHeight + obs.anomaly, anomaly: obs.anomaly });
                        }
                    });
                }
                currentClubStatus = clubStatus || { isClosed: false, openTime: null, dockTime: null, midDayDockTime: null, midDayOpenTime: null, alertMessage: '', sunsetTime: null };
                const widgetContainer = document.querySelector('#tide-chart-widget-container');
                if (!widgetContainer) {
                    isRendering = false;
                    navButtons.forEach(btn => btn.disabled = false);
                    return;
                }
                const palette = getPalette();
                const nightColor = palette['--color-chart-night'];
                const dayColor = palette['--color-chart-day'];
                const openOverlayColor = palette['--color-chart-open-overlay'];
                const risingColor = palette['--color-chart-rising'];
                const fallingColor = palette['--color-chart-falling'];
                const tideLineColor = palette['--color-chart-tide-line'];
                const redAreaColor = palette['--color-chart-danger-area'];
                const dangerColor = palette['--color-text-danger'];
                const eventCircleFill = palette['--color-event-circle-fill'];
                const eventCircleStroke = palette['--color-event-circle-stroke'];
                const hoverLineColor = palette['--color-hover-line'];
                const hoverCircleFill = palette['--color-hover-circle-fill'];
                const hoverCircleStroke = palette['--color-hover-circle-stroke'];
                const containerRect = chartContainer.node().getBoundingClientRect();
                const isMobile = window.innerWidth < 640;
                
                const margin = { top: isMobile ? 25 : 20, right: isMobile ? 0 : 20, bottom: isMobile ? 24 : 40, left: isMobile ? 32 : 45 };
                
                const width = Math.max(0, containerRect.width - margin.left - margin.right);
                const height = Math.max(0, containerRect.height - margin.top - margin.bottom);
                
                const { sunrise: calculatedSunrise, sunset: calculatedSunset } = calculateSunriseSunset(renderDate, LOCATION_LAT, LOCATION_LNG);
                const sunriseTime = calculatedSunrise; 
                
                let sunsetTime = currentClubStatus.sunsetTime;
                if (!sunsetTime || sunsetTime === 'sunset') {
                    sunsetTime = calculatedSunset;
                }
                if (currentClubStatus.dockTime === 'sunset') currentClubStatus.dockTime = sunsetTime;
                if (currentClubStatus.midDayDockTime === 'sunset') currentClubStatus.midDayDockTime = sunsetTime;
                if (currentClubStatus.openTime === 'sunset') currentClubStatus.openTime = sunsetTime;

                // --- STREAMING_CHUNK: Setup SVG container skeleton if NOAA data is available ---
                if (!tideDataUnavailable) {
                    if (isFirstLoad || direction === 0) {
                        chartContainer.html(""); 
                        
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
                        
                        chartWindow.append("rect").attr("class", "hover-overlay").attr("fill", "none").attr("pointer-events", "all");
                        chartWindow.append("g").attr("class", "slides-container").style("pointer-events", "none");
                        
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
                    
                    let upperPadding = 1;
                    let needsExtraSpace = false;
                    
                    if (currentClubStatus && !currentClubStatus.isClosed) {
                        const scheduleTimes = [
                            currentClubStatus.openTime,
                            currentClubStatus.dockTime,
                            currentClubStatus.midDayDockTime,
                            currentClubStatus.midDayOpenTime
                        ].filter(t => t && t >= startOfDay && t <= endOfDay && t !== 'sunset');
                        
                        const heightsToCheck = scheduleTimes.map(t => getTideHeightAtTime(chartData, t));
                        
                        for (const h of heightsToCheck) {
                            if (maxTide - h < 1.2) {
                                needsExtraSpace = true;
                                break;
                            }
                        }
                        
                        const highTideTimes = tideEvents.filter(e => e.type === 'High').map(e => e.time);
                        for (const sTime of scheduleTimes) {
                            for (const hTime of highTideTimes) {
                                const diffHours = Math.abs(sTime.getTime() - hTime.getTime()) / 3600000;
                                if (diffHours < 1.5) {
                                    needsExtraSpace = true;
                                    break;
                                }
                            }
                            if (needsExtraSpace) break;
                        }
                    }
                    
                    if (needsExtraSpace) {
                        upperPadding = 3; 
                    }
                    
                    yScale = d3.scaleLinear().domain([minTide - 2, maxTide + upperPadding]).range([height, 0]);
                    
                    svg.select(".x-axis-group").interrupt();
                    svg.select(".y-axis-group").interrupt();
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
                }
                
                const dayEvents = [];
                const specialIcons = []; 
                const topLabelsData = []; 
                
                let newBannerClass = '';
                let bannerHTML = '';
                
                if (currentClubStatus.isClosed) {
                    newBannerClass = 'banner-red';
                    bannerHTML = `<svg class="icon-sm" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"/></svg> <span>${currentClubStatus.alertMessage}</span>`;
                } else if (currentClubStatus.alertMessage) {
                    newBannerClass = 'banner-yellow';
                    bannerHTML = `<svg class="icon-sm" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"/></svg> <span>${currentClubStatus.alertMessage}</span>`;
                }
                
                if (newBannerClass) {
                    const isVisible = clubStatusBanner.classList.contains('visible');
                    clubStatusBanner.className = `status-banner ${newBannerClass} ${isVisible ? 'visible' : ''}`;
                    clubStatusBanner.innerHTML = bannerHTML;
                    clubStatusBanner.style.display = 'flex';
                    
                    if (!isVisible) {
                        clubStatusBanner.offsetHeight; 
                        clubStatusBanner.classList.add('visible');
                    }
                } else {
                    clubStatusBanner.classList.remove('visible');
                    setTimeout(() => {
                        if (!clubStatusBanner.classList.contains('visible')) {
                            clubStatusBanner.style.display = 'none';
                            clubStatusBanner.className = 'status-banner';
                        }
                    }, 400); 
                }
                
                // --- STREAMING_CHUNK: Splicing in Open/Dock boundaries dynamically ---
                if (!currentClubStatus.isClosed) {
                    const openPeriods = [];
                    if (currentClubStatus.midDayDockTime && currentClubStatus.midDayOpenTime) {
                        if (currentClubStatus.openTime && currentClubStatus.midDayDockTime > currentClubStatus.openTime) openPeriods.push({ start: currentClubStatus.openTime, end: currentClubStatus.midDayDockTime, type: 'morning' });
                        if (currentClubStatus.midDayOpenTime && currentClubStatus.dockTime > currentClubStatus.midDayOpenTime) openPeriods.push({ start: currentClubStatus.midDayOpenTime, end: currentClubStatus.dockTime, type: 'afternoon' });
                    } 
                    else if (currentClubStatus.openTime && currentClubStatus.dockTime > currentClubStatus.openTime) openPeriods.push({ start: currentClubStatus.openTime, end: currentClubStatus.dockTime, type: 'full_day' });
                    
                    openPeriods.forEach(({start, end, type}) => {
                        const openText = type === 'afternoon' ? "Club Re-Opens" : "Club Opens";
                        const dockText = type === 'morning' ? "Mid-Day Dock Time" : "Dock Time (Club Closes)";
                        if (start > startOfDay && start < endOfDay) {
                            dayEvents.push({time: start, text: openText, type: 'open'});
                            if (!tideDataUnavailable) {
                                specialIcons.push({ time: start, type: 'open', yHeight: getTideHeightAtTime(chartData, start) });
                                topLabelsData.push({ time: start, text: 'Open', isOpen: true });
                            }
                        }
                        if (end > start && end < endOfDay) {
                             dayEvents.push({time: end, text: dockText, type: 'dock'});
                             if (!tideDataUnavailable) {
                                 specialIcons.push({ time: end, type: 'dock', yHeight: getTideHeightAtTime(chartData, end) });
                                 topLabelsData.push({ time: end, text: 'Dock', isOpen: false });
                             }
                        }
                    });
                }
                
                // Mix in Club Events to display in schedule table
                if (clubEvents && clubEvents.length > 0) {
                    clubEvents.forEach((e, i) => {
                        const eStart = new Date(Math.max(e.start.getTime(), startOfDay.getTime()));
                        const eEnd = new Date(Math.min(e.end.getTime(), endOfDay.getTime()));
                        
                        let isAffected = false;
                        const hasSkipWarningClass = Array.isArray(e.classNames) && 
                            (e.classNames.includes('dp-event-calendar-sq-2') || e.classNames.includes('dp-event-calendar-sq-3'));
                        
                        if (!tideDataUnavailable && eStart < eEnd && !hasSkipWarningClass) {
                            let minHeight = Math.min(getTideHeightAtTime(chartData, eStart), getTideHeightAtTime(chartData, eEnd));
                            chartData.forEach(d => {
                                if (d.time > eStart && d.time < eEnd && d.height < minHeight) {
                                    minHeight = d.height;
                                }
                            });
                            if (minHeight < DANGEROUS_LOW_TIDE) {
                                isAffected = true;
                            }
                        }
                        if (e.start >= startOfDay && e.start <= endOfDay) {
                            let textHtml = `<a href="${sanitizeUrl(e.url)}" target="_blank" rel="noopener noreferrer" style="color: var(--color-observed-line); text-decoration: none;">${escapeHtml(e.title)}</a>`;
                            
                            if (isAffected) {
                                textHtml += ` <span class="event-warning-tooltip">
                                    <svg class="icon-sm" style="color: var(--color-text-danger); display: block;" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                                        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"></path>
                                    </svg>
                                    <span class="tooltip-content">Low tide impact possible. Check announcements for schedule changes.</span>
                                </span>`;
                            }
                            
                            dayEvents.push({
                                time: e.start,
                                text: textHtml,
                                type: 'club_event'
                            });
                        }
                    });
                }
                
                // --- STREAMING_CHUNK: Plot D3 SVG Paths if NOAA service is active ---
                if (!tideDataUnavailable) {
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
                    
                    // Render Sunrise/Sunset Day Overlays
                    slideGroup.append("rect").attr("x", xScale(startOfDay)).attr("width", Math.max(0, (xScale(sunriseTime) - xScale(startOfDay)) + overlap)).attr("height", height).attr("fill", nightColor);
                    slideGroup.append("rect").attr("x", xScale(sunriseTime)).attr("width", Math.max(0, (xScale(sunsetTime) - xScale(sunriseTime)) + overlap)).attr("height", height).attr("fill", dayColor);
                    slideGroup.append("rect").attr("x", xScale(sunsetTime)).attr("width", Math.max(0, xScale(endOfDay) - xScale(sunsetTime))).attr("height", height).attr("fill", nightColor);

                    if (currentClubStatus && !currentClubStatus.isClosed) {
                        openPeriods.forEach(({start, end}) => {
                            slideGroup.append("rect").attr("x", xScale(start)).attr("width", Math.max(0, xScale(end) - xScale(start))).attr("height", height).attr("fill", openOverlayColor);
                            if (start > startOfDay && start < endOfDay) {
                                slideGroup.append("line").attr("x1", xScale(start)).attr("x2", xScale(start)).attr("y1", 0).attr("y2", height).attr("stroke", "var(--color-open-line)").attr("stroke-width", 1);
                            }
                            if (end > start && end < endOfDay) {
                                 slideGroup.append("line").attr("x1", xScale(end)).attr("x2", xScale(end)).attr("y1", 0).attr("y2", height).attr("stroke", "var(--color-dock-line)").attr("stroke-width", 1);
                            }
                        });
                    }

                    segments.forEach(seg => slideGroup.append("path").datum(seg.data).attr("fill", seg.rising ? risingColor : fallingColor).attr("d", areaGenerator(height)));
                    redSegments.forEach(segment => slideGroup.append("path").datum(segment).attr("fill", redAreaColor).attr("d", redAreaGenerator));
                    
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
                    
                    // Add tooltips to high/low tide markers with Touch support
                    const eventsGroup = slideGroup.selectAll(".event").data(tideEvents).enter().append("g").attr("class", "event").attr("transform", d => `translate(${xScale(d.time)},${yScale(d.height)})`).style("pointer-events", "all").style("cursor", "pointer");
                    eventsGroup.each(function(d) {
                        const g = d3.select(this);
                        if (d.height < DANGEROUS_LOW_TIDE) {
                            g.append("circle").attr("r", 4.5).attr("fill", dangerColor);
                            g.append("path").attr("d", "M-2,-2 L2,2 M-2,2 L2,-2").attr("stroke", palette['--color-on-danger']).attr("stroke-width", 1.5).attr("stroke-linecap", "round");
                        } else {
                            g.append("circle").attr("r", 3.5).attr("fill", tideLineColor);
                        }
                        const tStr = d3.timeFormat("%H:%M")(d.time);
                        const hStr = `${d.height.toFixed(1)}\u2032`;
                        const textY1 = 20; const textY2 = 34;
                        const textGroup = d3.select(this).append("text").attr("class", "event-label").attr("text-anchor", "middle");
                        textGroup.append("tspan").attr("x", 0).attr("y", textY1).text(tStr).style("font-size", "0.65rem");
                        textGroup.append("tspan").attr("x", 0).attr("y", textY2).text(hStr).style("font-weight", "bold");
                    });
                    
                    eventsGroup
                        .on("mouseover", (event, d) => { showTideEventTooltip(d); })
                        .on("mouseout", () => { isHoveringOnEvent = false; tooltip.style("opacity", 0); })
                        .on("touchstart", (event, d) => { event.preventDefault(); event.stopPropagation(); showTideEventTooltip(d); });
                }
                
                // --- STREAMING_CHUNK: Build Daylight Events list (Tides, Sunset, Events) ---
                if (!tideDataUnavailable) {
                    tideEvents.forEach(event => {
                        if (event.time >= sunriseTime && event.time <= sunsetTime) {
                            dayEvents.push({ time: event.time, text: `${event.type} Tide: ${event.height.toFixed(1)}\u2032`, type: event.type.toLowerCase() });
                        }
                    });
                }
                dayEvents.push({ time: sunsetTime, text: "Sunset", type: 'sunset' });
                dayEvents.sort((a, b) => a.time - b.time);
                
                const uniqueEventsMap = new Map();
                for (const e of dayEvents) {
                    const key = `${e.time instanceof Date ? e.time.getTime() : new Date(e.time).getTime()}|${e.type}|${e.text}`;
                    if (!uniqueEventsMap.has(key)) uniqueEventsMap.set(key, e);
                }
                const uniqueEvents = [...uniqueEventsMap.values()];
                uniqueEvents.sort((a,b) => new Date(a.time) - new Date(b.time));
                
                // Build HTML Table - guaranteed to draw even when NOAA is offline!
                if (uniqueEvents.length > 0) {
                     const eventIcons = {
                          open: `<svg class="icon-sm icon-open" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M14.752 11.168l-3.197-2.132A1 1 0 0010 9.87v4.263a1 1 0 001.555.832l3.197-2.132a1 1 0 000-1.664z"></path><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M21 12a9 9 0 11-18 0 9 9 0 0118 0z"></path></svg>`,
                          dock: `<svg class="icon-sm icon-dock" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M10 9v6m4-6v6m7-3a9 9 0 11-18 0 9 9 0 0118 0z"></path></svg>`,
                          high: `<svg class="icon-sm icon-high" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M5 10l7-7m0 0l7 7m-7-7v18"></path></svg>`,
                          low: `<svg class="icon-sm icon-low" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 14l-7 7m0 0l-7-7m7 7V3"></path></svg>`,
                          sunset: `<svg class="icon-sm icon-sunset" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" viewBox="0 0 24 24"><path d="M17 18a5 5 0 00-10 0M12 2v7m-5.66 2.34l1.42 1.42M1 18h2m18 0h2M18.36 11.64l1.42-1.42M23 22H1m15-17l-4 4-4-4"/></svg>`,
                          club_event: `<svg class="icon-sm" style="color: #00c853;" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M8 7V3m8 4V3m-9 8h10M5 21h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v12a2 2 0 002 2z"></path></svg>`
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
                         
                         return `<tr class="${rowClass}"><td>${icon}</td><td style="width: 100%;">${e.text}</td><td style="white-space: nowrap; text-align: right;"><strong>${d3.timeFormat("%H:%M")(eventTime)}</strong></td></tr>`; 
                     }).join('')}</tbody></table>`;
                     eventsList.innerHTML = tableHTML;
                } else {
                     eventsList.innerHTML = `<p>No scheduled events during daylight hours.</p>`;
                }
                
                updateUI(renderDate);
                
                if (!tideDataUnavailable) {
                    if (direction !== 0) {
                        const oldSlideGroup = slidesContainer.select(".slide-group.active");
                        oldSlideGroup.interrupt();
                        
                        svg.select(".hover-overlay").style("pointer-events", "none");
                        
                        oldSlideGroup.classed("active", false)
                            .transition(t)
                            .attr("transform", `translate(${direction > 0 ? -width : width}, 0)`)
                            .remove();
                            
                        slideGroup.classed("active", true)
                            .transition(t)
                            .attr("transform", `translate(0, 0)`)
                            .on("end", () => {
                                svg.select(".hover-overlay").style("pointer-events", "all");
                                isRendering = false;
                                navButtons.forEach(btn => btn.disabled = false);
                            });
                    } else {
                        slidesContainer.selectAll(".slide-group.active").remove();
                        slideGroup.classed("active", true).attr("transform", "translate(0,0)");
                        svg.select(".hover-overlay").style("pointer-events", "all");
                        isRendering = false;
                        navButtons.forEach(btn => btn.disabled = false);
                    }
                } else {
                    isRendering = false;
                    navButtons.forEach(btn => btn.disabled = false);
                }
                
                } catch (error) {
                    console.error("Critical rendering error:", error);
                    chartContainer.html(`<div style="color: var(--color-text-danger); padding: 1rem; text-align: center; display: flex; align-items: center; justify-content: center; height: 100%;">An error occurred generating the chart. Check developer console for details.</div>`);
                    isRendering = false;
                    navButtons.forEach(btn => btn.disabled = false);
                }
            }
            
            // --- STREAMING_CHUNK: Managing dynamic updates, countdowns, and observed tides ---
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
                         const nowPalette = getPalette();
                         const nowIndicatorColor = nowPalette['--color-now-indicator'];
                         
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
                             .attr("fill", nowPalette['--color-on-flag']) 
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
                const BasketCaseNow = getPTNow();
                const isCurrentDay = renderDate.toDateString() === BasketCaseNow.toDateString();
                
                if (isCurrentDay) {
                    statusBoxesContainer.style.display = 'grid';
                    statusBoxesContainer.offsetHeight; 
                    statusBoxesContainer.classList.add('visible');
                    
                    updateNextTideEvent();
                    countdownInterval = setInterval(updateNextTideEvent, 60000); 
                } else {
                    statusBoxesContainer.classList.remove('visible');
                    setTimeout(() => {
                        if (!statusBoxesContainer.classList.contains('visible')) {
                            statusBoxesContainer.style.display = 'none';
                        }
                    }, 400); 
                }

                updateLessonsUI();
                
                document.getElementById('legend').innerHTML = `
                    <div><div style="width: 0.75rem; height: 0.75rem; background-color: var(--color-chart-open-overlay);"></div><span>Open</span></div>
                    <div><div style="width: 1rem; height: 1px; background-color: var(--color-observed-line); opacity: 0.9;"></div><span>Observed tide</span></div>
                    <div><div style="width: 0.75rem; height: 0.75rem; background-color: var(--color-chart-danger-area);"></div><span>Closed: Tide &lt; 1.5\u2032</span></div>`;
            }
            
            // --- STREAMING_CHUNK: Safe schedule countdown updater even when NOAA tides go offline ---
            async function updateNextTideEvent() {
                 try {
                    const now = getPTNow();
                    
                    // Concurrent fetch wrapped in error catches so failure does not drop other components
                    const [prevTides, currentTides, nextTides, nextNextTides] = await Promise.all([ 
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() - 1)), 
                        fetchTideData(now), 
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() + 1)),
                        fetchTideData(new Date(now.getFullYear(), now.getMonth(), now.getDate() + 2)) 
                    ]);
                    
                    const tideDataUnavailable = !currentTides || currentTides.length === 0;
                    
                    if (tideDataUnavailable) {
                        currentTideStatus.innerHTML = `<div style="font-weight: 500; font-size: 0.95rem; color: var(--color-text-secondary);">Offline</div>`;
                        observedStatusEl.innerHTML = `<div style="font-size: 0.65rem; color: var(--color-text-danger);">NOAA offline</div>`;
                        nextTideDisplay.innerHTML = `<div style="font-weight: 500; font-size: 0.95rem; color: var(--color-text-secondary);">Offline</div>`;
                    } else {
                        const combinedTideDataForLookup = [...prevTides, ...currentTides, ...nextTides, ...nextNextTides];
                        
                        const currentHeight = getTideHeightAtTime(combinedTideDataForLookup, now);
                        const timeIn5Mins = new Date(now.getTime() + 5 * 60000);
                        const futureHeight = getTideHeightAtTime(combinedTideDataForLookup, timeIn5Mins);
                        
                        const currentHeightDisplay = currentHeight.toFixed(1);
                        let directionArrow = '';
                        if (futureHeight > currentHeight) directionArrow = `<svg class="icon-sm" style="display: inline-block; vertical-align: middle; color: var(--icon-color-high);" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2"><path stroke-linecap="round" stroke-linejoin="round" d="M5 10l7-7m0 0l7 7m-7-7v18"></path></svg>`;
                        else if (futureHeight < currentHeight) directionArrow = `<svg class="icon-sm" style="display: inline-block; vertical-align: middle; color: var(--icon-color-low);" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2"><path stroke-linecap="round" stroke-linejoin="round" d="M19 14l-7 7m0 0l-7-7m7 7V3"></path></svg>`;
                        
                        currentTideStatus.innerHTML = `<div style="display: flex; align-items: center; justify-content: center; font-weight: 600; font-size: 1.25rem;">${directionArrow}<span style="margin-left: 0.25rem;">${currentHeightDisplay}\u2032</span></div>`;
                        
                        if (currentDate.toDateString() === now.toDateString()) {
                            const obsAnomalies = await fetchObservedTideData(now, true);
                            if (obsAnomalies && obsAnomalies.length > 0) {
                                const latestAnomaly = obsAnomalies[obsAnomalies.length - 1].anomaly;
                                const roundedPredicted = parseFloat(currentHeight.toFixed(1));
                                const roundedObserved = parseFloat((currentHeight + latestAnomaly).toFixed(1));
                                const visualAnomaly = roundedObserved - roundedPredicted;
                                const sign = visualAnomaly > 0 ? '+' : '';
                                observedStatusEl.innerHTML = `<div style="font-size: 0.65rem; color: var(--color-text-secondary);">Observed: ${roundedObserved.toFixed(1)}\u2032 <span style="font-size: 0.6rem; color: var(--color-text-tertiary);">(${sign}${visualAnomaly.toFixed(1)}\u2032)</span></div>`;
                            } else {
                                observedStatusEl.innerHTML = `<div style="font-size: 0.65rem; color: var(--color-text-secondary);">Waiting for observed...</div>`;
                            }
                        } else {
                            observedStatusEl.innerHTML = '';
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
                    }

                    // --- STREAMING_CHUNK: Handle schedule box rendering (fully works even if tides are offline) ---
                    if (currentDate.toDateString() === now.toDateString()) {
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
                                    if (diff < 3600000) {
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
                        
                        if (hasScheduleData && scheduleColorState !== 'neutral') {
                            clubScheduleBoxEl.style.setProperty('background-color', scheduleColorState === 'open' ? 'var(--color-open-bg)' : 'var(--color-dock-bg)', 'important');
                            clubScheduleBoxEl.style.setProperty('border-color', scheduleColorState === 'open' ? 'var(--color-open-line)' : 'var(--color-dock-line)', 'important');
                            clubScheduleBoxEl.style.setProperty('box-shadow', scheduleColorState === 'open' ? 'var(--shadow-sm), 0 0 0 1px var(--color-open-line)' : 'var(--shadow-sm), 0 0 0 1px var(--color-dock-line)', 'important');
                            clubScheduleLabelEl.style.setProperty('color', scheduleColorState === 'open' ? 'var(--color-open-line)' : 'var(--color-dock-line)', 'important');
                        } else {
                            clubScheduleBoxEl.style.removeProperty('background-color');
                            clubScheduleBoxEl.style.removeProperty('border-color');
                            clubScheduleBoxEl.style.removeProperty('box-shadow');
                            clubScheduleLabelEl.style.removeProperty('color');
                        }
                    } else {
                        clubScheduleStatusEl.innerHTML = '';
                        clubScheduleBoxEl.style.removeProperty('background-color');
                        clubScheduleBoxEl.style.removeProperty('border-color');
                        clubScheduleBoxEl.style.removeProperty('box-shadow');
                        clubScheduleLabelEl.style.removeProperty('color');
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
                clubScheduleBoxEl.style.removeProperty('box-shadow');
                clubScheduleLabelEl.style.removeProperty('color');
                nextTideDisplay.innerHTML = '';
                
                clubStatusBanner.classList.remove('visible');
                clubStatusBanner.style.display = 'none';
                clubStatusBanner.className = 'status-banner';
            }

            function checkLessonsActive() {
                if (!ENABLE_DINGHY_LESSONS) return false;
                
                // Read ?debug=true query parameter from URL
                const urlParams = new URLSearchParams(window.location.search);
                const isDebugParam = urlParams.get('debug') === 'true';
                if (isDebugParam) return true;

                const now = getPTNow();
                return currentDate.toDateString() === now.toDateString();
            }

            async function updateLessonsUI() {
                const showBox = checkLessonsActive();
                const lessonsBox = document.getElementById('lessons-status-box');
                if (!lessonsBox) return;

                if (showBox) {
                    const isLiveEnvironment = window.location.hostname === "status.cal-sailing.org" || window.location.hostname === "www.cal-sailing.org";
                    let data = null;

                    // Read ?debug=true query parameter from URL
                    const urlParams = new URLSearchParams(window.location.search);
                    const isDebugParam = urlParams.get('debug') === 'true';

                    if (!isLiveEnvironment) {
                        // Fallback directly to mock data if loaded outside live servers
                        data = {
                            active_lessons: isDebugParam ? false : true, // If debug=true in test env, mock as inactive to preview that state
                            instructors: isDebugParam ? 1 : 3,           // Instructor warning trigger test state
                            students_in_lesson: isDebugParam ? 3 : 8,
                            students_waiting: isDebugParam ? 12 : 2      // Student waiting alert trigger test state
                        };
                    } else {
                        try {
                            const url = "https://signout.cal-sailing.org/api/lessons/status";
                            const rawText = await fetchTextWithProxyFallback(url);
                            const jsonString = rawText.replace(/<pre.*?>|<\/pre>/g, '');
                            data = JSON.parse(jsonString);
                        } catch (e) {
                            console.warn("Could not retrieve active dinghy lessons status:", e.message);
                            data = { active_lessons: false, instructors: 0, students_in_lesson: 0, students_waiting: 0 };
                        }
                    }

                    // Display the lessons box if active_lessons is true, OR if debug=true URL parameter is parsed!
                    if (data && (data.active_lessons === true || isDebugParam)) {
                        const badgeClass = data.active_lessons ? 'lessons-badge-active' : 'lessons-badge-inactive';
                        const badgeText = data.active_lessons ? 'In Progress' : 'No Active Lessons';
                        
                        // Apply conditional danger alert states
                        const instructorAlertClass = data.instructors === 1 ? 'stat-danger' : '';
                        const waitingAlertClass = data.students_waiting > 10 ? 'stat-danger' : '';
                        
                        lessonsBox.innerHTML = `
                            <div class="lessons-card">
                                <div class="lessons-card-icon">
                                    <svg viewBox="0 0 64 64" width="34" height="34" fill="currentColor">
                                        <!-- Classic Sailing Dinghy Hull -->
                                        <path d="M12,42 L10,47 C18,50 44,50 52,44 C53,42 51,41 49,42 Z" />
                                        <!-- Rudder & Tiller -->
                                        <path d="M10,47 L6,53" stroke="currentColor" stroke-width="2" stroke-linecap="round" />
                                        <!-- Mast -->
                                        <line x1="32" y1="8" x2="32" y2="43" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" />
                                        <!-- Boom -->
                                        <line x1="32" y1="40" x2="14" y2="40" stroke="currentColor" stroke-width="2" stroke-linecap="round" />
                                        <!-- Curved Main Sail -->
                                        <path d="M32,10 C27,22 19,32 15,39 L32,39 Z" opacity="0.8" />
                                        <!-- Triangular Jib Sail -->
                                        <path d="M33,18 C38,26 43,34 46,39 L33,39 Z" opacity="0.95" />
                                        <!-- Gentle Water ripples -->
                                        <path d="M4,50 Q16,48 28,51 T52,49" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" />
                                    </svg>
                                </div>
                                <div class="lessons-card-content">
                                    <div class="lessons-card-title">
                                        <span style="font-size:0.75rem; color:var(--color-text-secondary); text-transform:uppercase; letter-spacing:0.05em;">Dinghy Lessons</span>
                                        <span class="lessons-badge ${badgeClass}">${badgeText}</span>
                                    </div>
                                    <div class="lessons-card-grid">
                                        <div class="lessons-stat ${instructorAlertClass}">
                                            <div class="lessons-stat-val">${data.instructors}</div>
                                            <div class="lessons-stat-lbl">Instructors</div>
                                        </div>
                                        <div class="lessons-stat">
                                            <div class="lessons-stat-val">${data.students_in_lesson}</div>
                                            <div class="lessons-stat-lbl">In Lesson</div>
                                        </div>
                                        <div class="lessons-stat ${waitingAlertClass}">
                                            <div class="lessons-stat-val">${data.students_waiting}</div>
                                            <div class="lessons-stat-lbl">Waiting</div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        `;
                        lessonsBox.style.display = 'block';
                    } else {
                        lessonsBox.style.display = 'none';
                        lessonsBox.innerHTML = '';
                    }
                } else {
                    lessonsBox.style.display = 'none';
                    lessonsBox.innerHTML = '';
                }
            }

            function startLessonsPolling() {
                updateLessonsUI();
                if (lessonsInterval) clearInterval(lessonsInterval);
                lessonsInterval = setInterval(() => {
                    updateLessonsUI();
                }, 60000); 
            }

            // --- EVENT BINDINGS FOR INTERACTION CONTROLS ---
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
                const selectedDate = new Date(currentDate.getTime());
                selectedDate.setFullYear(year, month - 1, day);
                
                if (!isNaN(selectedDate.getTime()) && selectedDate.toDateString() !== currentDate.toDateString()) {
                    const direction = selectedDate > currentDate ? 1 : -1;
                    currentDate = selectedDate;
                    drawChart(new Date(currentDate), direction);
                }
            });
            
            window.addEventListener('resize', () => {
                clearTimeout(resizeTimeout);
                resizeTimeout = setTimeout(() => {
                    chartContainer.selectAll(".slide-group").interrupt();
                    isRendering = false; 
                    drawChart(currentDate, 0);
                }, 200);
            });
            
            setInterval(() => {
                const currentRealDateString = getPTNow().toDateString();
                if (currentRealDateString !== lastRealDateString && !isRendering) {
                    lastRealDateString = currentRealDateString;
                    currentDate = getPTNow();
                    drawChart(currentDate, 0);
                }
            }, 60000);

            const dismissAllTooltips = (e) => {
                const container = document.getElementById('tide-chart-widget-container');
                if (container && !container.contains(e.target)) {
                    isHoveringOnEvent = false;
                    d3.select("#tide-chart-tooltip").style("opacity", 0);
                    d3.selectAll(".hover-group").style("display", "none");
                }
            };
            document.addEventListener('touchstart', dismissAllTooltips, { passive: true });
            document.addEventListener('click', dismissAllTooltips, { passive: true });

            startLessonsPolling();
            drawChart(currentDate, 0);
        });
        /* #end raw */
    </script>
</div>

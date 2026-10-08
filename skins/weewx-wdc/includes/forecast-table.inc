<!-- IBM Plex Sans Font -->
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=IBM+Plex+Sans:wght@300;400;500;600;700&display=swap" rel="stylesheet">

<style>
  :root {
    --cds-ui-background: #ffffff;
    --cds-text-primary: #161616;
    --cds-text-secondary: #525252;
    --cds-ui-border: #e0e0e0;
    --cds-interactive-01: #0f62fe;
    --club-open-hour-bg: rgba(34, 197, 94, 0.15);
    --night-hour-bg: #f3f4f6;
  }

  html.dark {
    --cds-ui-background: #161616;
    --cds-text-primary: #f4f4f4;
    --cds-text-secondary: #c6c6c6;
    --cds-ui-border: #393939;
    --club-open-hour-bg: rgba(34, 197, 94, 0.15);
    --night-hour-bg: #111827;
  }

  .app-card {
    font-family: 'IBM Plex Sans', -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
    background: #ffffff;
    border: none;
    border-radius: 0;
    box-shadow: none;
    width: 100%;
    max-width: 100%;
    margin: 0;
    overflow: hidden;
    color: var(--cds-text-primary);
    box-sizing: border-box;
  }

  .app-card * {
    box-sizing: border-box;
    -webkit-font-smoothing: antialiased;
  }

  .view-switcher-container {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0.6rem 0.85rem;
    border-bottom: 1px solid var(--cds-ui-border);
    background-color: #ffffff;
  }

  .carbon-switcher {
    display: inline-flex;
    border: 1px solid #161616;
    border-radius: 2px;
    overflow: hidden;
    background-color: #ffffff;
  }

  .carbon-switcher-btn {
    padding: 0.35rem 1.1rem;
    font-size: 0.82rem;
    font-weight: 500;
    cursor: pointer;
    border: none;
    background: #ffffff;
    color: #161616;
    transition: all 0.15s ease-in-out;
    outline: none;
    user-select: none;
  }

  .carbon-switcher-btn.active {
    background: #161616;
    color: #ffffff;
  }

  /* Micro Footer Status Pill */
  .footer-actions {
    display: inline-flex;
    align-items: center;
    gap: 0.35rem;
  }

  .status-badge.micro {
    font-size: 0.62rem;
    border-radius: 9999px;
    padding: 0.18rem 0.5rem;
    display: inline-flex;
    align-items: center;
    gap: 0.3rem;
    font-weight: 500;
    letter-spacing: -0.01em;
    border: none;
    line-height: 1.1;
    text-decoration: none;
    color: inherit;
    cursor: pointer;
    transition: background-color 0.2s ease, color 0.2s ease, opacity 0.15s ease;
  }

  .status-badge.micro:hover {
    opacity: 0.88;
    text-decoration: none;
    color: inherit;
  }

  .status-badge.micro.live {
    background-color: #defbe6;
    color: #0e6027;
  }

  .status-badge.micro.updating {
    background-color: #fef3c7;
    color: #92400e;
  }

  .status-badge.micro.demo {
    background-color: #edf5ff;
    color: #0353e9;
  }

  .status-badge.micro .status-dot {
    width: 5px;
    height: 5px;
    border-radius: 50%;
    background-color: #24a148;
    flex-shrink: 0;
  }

  .table-scroll-container {
    width: 100%;
    overflow-x: auto;
    overflow-y: hidden;
    background: #ffffff;
    position: relative;
    scrollbar-width: thin;
    scrollbar-color: #c6c6c6 #f4f4f4;
    -webkit-overflow-scrolling: touch;
  }

  .table-scroll-container::-webkit-scrollbar {
    height: 6px;
  }
  .table-scroll-container::-webkit-scrollbar-track {
    background: #f4f4f4;
  }
  .table-scroll-container::-webkit-scrollbar-thumb {
    background-color: #c6c6c6;
    border-radius: 3px;
  }

  table.structured-forecast {
    border-collapse: collapse;
    width: max-content;
    min-width: 100%;
    text-align: center;
    font-size: 0.8125rem;
  }

  table.structured-forecast th,
  table.structured-forecast td {
    border-bottom: 1px solid #e0e0e0;
    border-right: 1px solid #e0e0e0;
    vertical-align: middle;
    padding: 0.45rem 0.4rem;
    white-space: nowrap;
  }

  /* Sticky first column */
  table.structured-forecast th:first-child,
  table.structured-forecast td:first-child {
    position: sticky;
    left: 0;
    z-index: 25;
    background-color: #ffffff;
    text-align: left;
    font-weight: 400;
    color: var(--cds-text-primary);
    border-right: 1px solid #d4d4d4;
    box-shadow: 4px 0 8px -2px rgba(0, 0, 0, 0.08);
    min-width: 68px;
    max-width: 68px;
    padding-left: 0.4rem;
    padding-right: 0.25rem;
  }

  /* Subtle drop shadow extending to the right of the sticky labels column */
  table.structured-forecast th:first-child::after,
  table.structured-forecast td:first-child::after {
    content: "";
    position: absolute;
    top: 0;
    right: -6px;
    bottom: -1px;
    width: 6px;
    pointer-events: none;
    background: linear-gradient(to right, rgba(0, 0, 0, 0.08), rgba(0, 0, 0, 0));
  }

  .unit-label {
    display: block;
    font-size: 0.65rem;
    color: #6f6f6f;
    font-weight: normal;
    margin-top: 1px;
  }

  table.structured-forecast.hourly-view th,
  table.structured-forecast.hourly-view td {
    padding: 0.25rem 0;
    min-width: 27px;
    max-width: 29px;
    font-size: 0.72rem;
  }

  table.structured-forecast.hourly-view th:first-child,
  table.structured-forecast.hourly-view td:first-child {
    min-width: 68px;
    max-width: 68px;
    padding: 0.3rem 0.25rem;
    font-size: 0.7rem;
  }

  table.structured-forecast.hourly-view .day-group-header {
    text-align: center;
    font-size: 0.75rem;
    font-weight: 600;
    color: #161616;
    background-color: transparent;
    border-bottom: 1px solid #c6c6c6;
    border-right: 1px solid #c6c6c6;
    padding: 0.25rem 0.4rem;
  }

  table.structured-forecast.hourly-view .hour-time {
    font-size: 0.7rem;
    font-weight: 400;
    color: #525252;
    display: block;
    letter-spacing: -0.02em;
    position: relative;
    z-index: 12;
  }

  .row-hour-header th {
    transition: background-color 0.2s ease;
    position: relative;
  }

  table.structured-forecast.hourly-view .row-temp td {
    padding-top: 0 !important;
    padding-bottom: 0 !important;
    height: 20px;
  }

  /* Wind histogram in Daily hourly view */
  table.structured-forecast.hourly-view .wind-histo-cell {
    height: 139px;
    vertical-align: bottom !important;
    padding: 0 !important;
    background-color: transparent !important;
    position: relative;
    overflow: visible;
  }

  /* Light green fill between Open and Dock schedule lines */
  .wind-sched-fill {
    position: absolute;
    top: 0;
    background-color: var(--club-open-hour-bg);
    z-index: 1;
    pointer-events: none;
  }

  /* Light grey fill for night hours */
  .wind-night-fill {
    position: absolute;
    top: 0;
    background-color: var(--night-hour-bg);
    z-index: 1;
    pointer-events: none;
  }

  /* Vertical line indicating exact Open / Dock times */
  .wind-sched-line {
    position: absolute;
    top: 0;
    width: 2px;
    z-index: 11;
    pointer-events: none;
  }

  .wind-sched-line.line-open {
    background-color: rgba(22, 163, 74, 0.7);
  }

  .wind-sched-line.line-dock {
    background-color: rgba(234, 88, 12, 0.7);
  }

  /* Inline Open / Dock badge flags positioned right on the wind row */
  .wind-sched-marker {
    position: absolute;
    top: -3px;
    z-index: 12;
    pointer-events: none;
    white-space: nowrap;
  }

  /* Open time box is placed BEFORE the line, overlapping it slightly */
  .wind-sched-marker.marker-open {
    transform: translateX(-100%);
    margin-left: 1.5px;
  }

  /* Dock time box is placed AFTER the line, overlapping it slightly */
  .wind-sched-marker.marker-dock {
    transform: translateX(0);
    margin-left: 0.5px;
  }

  .wind-club-flag {
    font-size: 0.58rem;
    font-weight: 600;
    line-height: 1.15;
    padding: 0.12rem 0.32rem;
    border-radius: 2px;
    box-shadow: none;
    pointer-events: none;
    letter-spacing: -0.01em;
  }

  .wind-club-flag.flag-open {
    background-color: #22c55e;
    color: #000000;
  }

  .wind-club-flag.flag-dock {
    background-color: #f97316;
    color: #000000;
  }

  .wind-histo-container {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: flex-end;
    height: 139px;
    width: 100%;
    position: relative;
    z-index: 2;
  }

  .wind-histo-val {
    font-size: 0.72rem;
    font-weight: 400;
    color: #161616;
    line-height: 1.1;
    margin-bottom: 2px;
  }

  .wind-histo-bar {
    width: 100%;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: flex-end;
    border-top: 1px solid rgba(0, 0, 0, 0.12);
    box-sizing: border-box;
    padding: 2px 0 3px 0;
    transition: height 0.2s ease;
  }

  table.structured-forecast.hourly-view .weather-icon-cell {
    height: 24px;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: help;
  }
  table.structured-forecast.hourly-view .weather-icon-cell svg {
    width: 20px;
    height: 20px;
  }

  table.structured-forecast.seven-day-view th,
  table.structured-forecast.seven-day-view td {
    min-width: 52px;
    padding: 0.35rem 0.2rem;
    font-size: 0.76rem;
  }

  table.structured-forecast.seven-day-view th:first-child,
  table.structured-forecast.seven-day-view td:first-child {
    min-width: 68px;
    max-width: 68px;
    padding: 0.35rem 0.25rem;
    font-size: 0.7rem;
  }

  table.structured-forecast.seven-day-view .day-name {
    font-size: 0.78rem;
    font-weight: 600;
    color: #161616;
    display: block;
  }

  table.structured-forecast.seven-day-view .day-date {
    font-size: 0.68rem;
    color: #525252;
    display: block;
  }

  /* Wind Colors */
  .wind-calm      { background-color: #eef8fc !important; color: #161616 !important; }
  .wind-light     { background-color: #dcf4fb !important; color: #161616 !important; }
  .wind-mod       { background-color: #b4e7fa !important; color: #161616 !important; }
  .wind-breeze    { background-color: #abf0d4 !important; color: #161616 !important; }
  .wind-green     { background-color: #80ff80 !important; color: #161616 !important; }
  .wind-yellow    { background-color: #ffea29 !important; color: #161616 !important; }
  .wind-lt-orange { background-color: #ffba42 !important; color: #161616 !important; }
  .wind-dk-orange { background-color: #ff8c1a !important; color: #161616 !important; }
  .wind-red       { background-color: #e52222 !important; color: #ffffff !important; }
  .wind-dk-red    { background-color: #b70c18 !important; color: #ffffff !important; }
  .wind-purple    { background-color: #9f135b !important; color: #ffffff !important; }

  .wind-arrow {
    display: inline-block;
    transition: transform 0.2s ease;
    color: inherit;
  }

  .wind-deg {
    font-size: 0.62rem;
    line-height: 1;
    display: block;
    color: inherit;
    opacity: 0.92;
    margin-top: 1px;
  }

  .wind-overview-section {
    background: #ffffff;
    border-top: 1px solid #e0e0e0;
    padding: 0.55rem 0.75rem 0.45rem 0.75rem;
    user-select: none;
    -webkit-user-select: none;
  }

  .overview-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 0.35rem;
    flex-wrap: wrap;
    gap: 0.25rem;
  }

  .overview-title {
    font-size: 0.7rem;
    font-weight: 600;
    text-transform: uppercase;
    letter-spacing: 0.04em;
    color: #525252;
    display: flex;
    align-items: center;
    gap: 0.4rem;
  }

  .peak-badge {
    font-size: 9.5px;
    font-weight: 600;
    background-color: #f3f4f6;
    color: #374151;
    padding: 0.1rem 0.35rem;
    border-radius: 3px;
  }

  .overview-hint {
    font-size: 10.5px;
    color: #9ca3af;
  }

  .timeline-wrapper {
    position: relative;
    background: #f4f4f4;
    border: 1px solid #dcdcdc;
    border-radius: 4px;
    height: 74px;
    overflow: hidden;
    cursor: pointer;
    touch-action: pan-y;
  }

  .timeline-bars-container {
    display: flex;
    height: 55px;
    align-items: flex-end;
    width: 100%;
  }

  .timeline-bar {
    flex: 1;
    min-width: 1px;
    transition: height 0.2s ease;
    position: relative;
  }

  .timeline-days-labels {
    display: flex;
    height: 18px;
    border-top: 1px solid #e0e0e0;
    background: #ffffff;
    width: 100%;
  }

  .timeline-day-label {
    flex: 1;
    text-align: center;
    font-size: 0.63rem;
    font-weight: 600;
    color: #525252;
    line-height: 18px;
    border-right: 1px solid #f0f0f0;
    overflow: hidden;
    text-overflow: ellipsis;
  }
  .timeline-day-label:last-child {
    border-right: none;
  }

  .timeline-selector {
    position: absolute;
    top: 0;
    bottom: 0;
    border: 2px solid #0f62fe;
    background-color: rgba(15, 98, 254, 0.12);
    border-radius: 3px;
    pointer-events: none;
    transition: left 0.08s ease-out, width 0.15s ease;
    z-index: 5;
  }

  .issued-footer {
    padding: 0.45rem 0.8rem;
    font-size: 0.68rem;
    color: #6f6f6f;
    border-top: 1px solid #f0f0f0;
    background: #fafafa;
    display: flex;
    justify-content: space-between;
    align-items: center;
    flex-wrap: wrap;
    gap: 0.4rem;
  }

  .footer-meta {
    display: flex;
    align-items: center;
    gap: 0.6rem;
    flex-wrap: wrap;
  }

  /* Dark Mode Scoped Overrides */
  html.dark .app-card {
    background-color: #161616;
    color: #f4f4f4;
  }

  html.dark .view-switcher-container {
    background-color: #161616;
    border-bottom-color: #393939;
  }

  html.dark .carbon-switcher {
    border-color: #525252;
    background-color: #262626;
  }

  html.dark .carbon-switcher-btn {
    background: #262626;
    color: #f4f4f4;
  }

  html.dark .carbon-switcher-btn.active {
    background: #f4f4f4;
    color: #161616;
  }

  html.dark .table-scroll-container {
    background: #161616;
    scrollbar-color: #525252 #262626;
  }
  html.dark .table-scroll-container::-webkit-scrollbar-track {
    background: #262626;
  }
  html.dark .table-scroll-container::-webkit-scrollbar-thumb {
    background-color: #525252;
  }

  html.dark table.structured-forecast th,
  html.dark table.structured-forecast td {
    border-bottom-color: #2e2e2e;
    border-right-color: #2e2e2e;
  }

  html.dark table.structured-forecast th:first-child,
  html.dark table.structured-forecast td:first-child {
    background-color: #161616;
    color: #f4f4f4;
    border-right-color: #333333;
    box-shadow: 4px 0 10px -2px rgba(0, 0, 0, 0.5);
  }

  html.dark table.structured-forecast th:first-child::after,
  html.dark table.structured-forecast td:first-child::after {
    background: linear-gradient(to right, rgba(0, 0, 0, 0.4), rgba(0, 0, 0, 0));
  }

  html.dark .unit-label {
    color: #a8a8a8;
  }

  html.dark table.structured-forecast.hourly-view .day-group-header {
    color: #f4f4f4;
    border-bottom-color: #393939;
    border-right-color: #393939;
  }

  html.dark table.structured-forecast.hourly-view .hour-time {
    color: #a8a8a8;
  }

  html.dark table.structured-forecast.hourly-view .wind-histo-val {
    color: #f4f4f4;
  }

  html.dark table.structured-forecast.seven-day-view .day-name {
    color: #f4f4f4;
  }

  html.dark table.structured-forecast.seven-day-view .day-date {
    color: #a8a8a8;
  }

  html.dark .wind-sched-line.line-open {
    background-color: rgba(74, 222, 128, 0.8);
  }

  html.dark .wind-sched-line.line-dock {
    background-color: rgba(251, 146, 60, 0.8);
  }

  html.dark .wind-club-flag.flag-open {
    background-color: #4ade80;
    color: #000000;
  }

  html.dark .wind-club-flag.flag-dock {
    background-color: #fb923c;
    color: #000000;
  }

  html.dark .wind-overview-section {
    background: #161616;
    border-top-color: #393939;
  }

  html.dark .overview-title {
    color: #c6c6c6;
  }

  html.dark .peak-badge {
    background-color: #262626;
    color: #e0e0e0;
  }

  html.dark .timeline-wrapper {
    background: #262626;
    border-color: #393939;
  }

  html.dark .timeline-days-labels {
    background: #161616;
    border-top-color: #393939;
  }

  html.dark .timeline-day-label {
    color: #a8a8a8;
    border-right-color: #262626;
  }

  html.dark .issued-footer {
    background: #1c1c1c;
    border-top-color: #2e2e2e;
    color: #a8a8a8;
  }

  html.dark .status-badge.micro.live {
    background-color: rgba(36, 161, 72, 0.22);
    color: #42be65;
  }
  html.dark .status-badge.micro.updating {
    background-color: rgba(217, 119, 6, 0.25);
    color: #fcd34d;
  }
  html.dark .status-badge.micro.demo {
    background-color: rgba(15, 98, 254, 0.22);
    color: #78a9ff;
  }

  /* Mobile Responsive */
  @media (max-width: 640px) {
    .app-card {
      border: none;
      border-radius: 0;
      box-shadow: none;
      width: 100%;
      max-width: 100%;
    }

    .view-switcher-container {
      padding: 0.5rem 0.6rem;
      justify-content: center;
    }

    .carbon-switcher {
      width: 100%;
      max-width: 280px;
    }

    .carbon-switcher-btn {
      flex: 1;
      text-align: center;
      padding: 0.35rem 0.5rem;
    }

    table.structured-forecast.hourly-view th:first-child,
    table.structured-forecast.hourly-view td:first-child {
      min-width: 58px;
      max-width: 58px;
      padding: 0.25rem 0.2rem;
      font-size: 0.65rem;
    }

    table.structured-forecast.seven-day-view th,
    table.structured-forecast.seven-day-view td {
      min-width: 44px;
      padding: 0.25rem 0.15rem;
      font-size: 0.68rem;
    }

    table.structured-forecast.seven-day-view th:first-child,
    table.structured-forecast.seven-day-view td:first-child {
      min-width: 58px;
      max-width: 58px;
      padding: 0.25rem 0.2rem;
      font-size: 0.65rem;
    }

    table.structured-forecast.seven-day-view .weather-icon-cell svg {
      width: 20px;
      height: 20px;
    }

    .overview-hint {
      display: none;
    }

    .issued-footer {
      flex-direction: row;
      justify-content: space-between;
      align-items: center;
      flex-wrap: nowrap;
      gap: 0.35rem;
      padding: 0.35rem 0.6rem;
    }

    .footer-meta {
      font-size: 0.64rem;
      line-height: 1.1;
      flex-direction: row;
      align-items: center;
      white-space: nowrap;
      overflow: hidden;
      text-overflow: ellipsis;
    }

    .footer-actions {
      align-self: center;
      margin-top: 0;
      flex-shrink: 0;
    }
  }
</style>

<div class="app-card">
  <!-- Top Bar with Centered Carbon Switcher -->
  <div class="view-switcher-container">
    <div class="carbon-switcher">
      <button id="tabDaily" class="carbon-switcher-btn active" type="button">Daily</button>
      <button id="tab7Day" class="carbon-switcher-btn" type="button">7 Day</button>
    </div>
  </div>

  <!-- Table Container with Horizontal Scroll -->
  <div class="table-scroll-container">
    <table id="forecastTable" class="structured-forecast hourly-view">
      <thead id="tableHead"></thead>
      <tbody id="tableBody"></tbody>
    </table>
  </div>

  <!-- 7-Day Wind Gust Overview Graph Scrubber -->
  <div class="wind-overview-section">
    <div class="overview-header">
      <div class="overview-title">
        <span>7-Day Wind Gusts</span>
        <span id="overviewPeakBadge" class="peak-badge">Peak: -- kts</span>
      </div>
      <div class="overview-hint">Touch or drag anywhere to scrub</div>
    </div>

    <div class="timeline-wrapper" id="timelineWrapper" title="Drag or tap to jump to day">
      <div class="timeline-bars-container" id="timelineBars"></div>
      <div class="timeline-days-labels" id="timelineLabels"></div>
      <div class="timeline-selector" id="timelineSelector"></div>
    </div>
  </div>

  <!-- Footer with Metadata and Micro Actions -->
  <div class="issued-footer">
    <div class="footer-meta">
      <span id="footerTimestamp">Updated: Loading...</span>
    </div>
    <div class="footer-actions">
      <a href="https://docs.meteoblue.com/en/weather-apis/forecast-api/overview" target="_blank" rel="noopener noreferrer" class="status-badge micro live" id="statusBadge" title="View Meteoblue API Documentation">
        <span class="status-dot" id="statusDot"></span>
        <span id="statusText">Meteoblue</span>
      </a>
    </div>
  </div>
</div>

<script>
/* #raw */
  // Server-side cached forecast endpoint
  const METEOBLUE_CACHE_URL = 'https://status.cal-sailing.org/meteoblue_cache.json';

  let weatherData = null;
  let currentMode = 'hour'; // 'hour' = Daily view; 'day' = 7 Day view
  let isProgrammaticScrolling = false;
  let programmaticScrollTimeout = null;
  const clubStatusCache = {};
  const clubScheduleCache = clubStatusCache; // Alias for backward compatibility

  function toKnots(speedVal, unitStr) {
    if (speedVal === null || speedVal === undefined) return null;
    const u = (unitStr || 'ms').toLowerCase();
    if (u.includes('knot') || u === 'kn' || u === 'kt') return Math.round(speedVal);
    if (u.includes('km') || u === 'km/h') return Math.round(speedVal * 0.539957);
    if (u.includes('m/s') || u === 'ms') return Math.round(speedVal * 1.94384);
    if (u.includes('mph')) return Math.round(speedVal * 0.868976);
    return Math.round(speedVal * 1.94384);
  }

  function toFahrenheit(tempVal, unitStr) {
    if (tempVal === null || tempVal === undefined) return null;
    const u = (unitStr || 'c').toLowerCase();
    if (u.includes('f')) return Math.round(tempVal);
    return Math.round((tempVal * 9 / 5) + 32);
  }

  function getWindClass(speedKnots) {
    if (!speedKnots || speedKnots <= 0) return '';
    if (speedKnots <= 3) return 'wind-calm';
    if (speedKnots <= 5) return 'wind-light';
    if (speedKnots <= 7) return 'wind-mod';
    if (speedKnots <= 9) return 'wind-breeze';
    if (speedKnots <= 14) return 'wind-green';
    if (speedKnots <= 16) return 'wind-yellow';
    if (speedKnots === 17) return 'wind-lt-orange';
    if (speedKnots <= 19) return 'wind-dk-orange';
    if (speedKnots <= 23) return 'wind-red';
    if (speedKnots <= 29) return 'wind-dk-red';
    return 'wind-purple';
  }

  function getWindHexColor(spd) {
    if (!spd || spd <= 0) return '#f4f4f4';
    if (spd <= 3) return '#eef8fc';
    if (spd <= 5) return '#dcf4fb';
    if (spd <= 7) return '#b4e7fa';
    if (spd <= 9) return '#abf0d4';
    if (spd <= 14) return '#80ff80';
    if (spd <= 16) return '#ffea29';
    if (spd === 17) return '#ffba42';
    if (spd <= 19) return '#ff8c1a';
    if (spd <= 23) return '#e52222';
    if (spd <= 29) return '#b70c18';
    return '#9f135b';
  }

  function getTemperatureColor(valF) {
    if (valF === null || valF === undefined || isNaN(valF)) {
      return { bg: '#525252', text: '#525252' };
    }
    const stops = [
      { t: 32, r: 35,  g: 105, b: 215 },
      { t: 45, r: 25,  g: 135, b: 195 },
      { t: 52, r: 18,  g: 155, b: 150 },
      { t: 57, r: 40,  g: 160, b: 70  },
      { t: 61, r: 190, g: 140, b: 15  },
      { t: 65, r: 220, g: 115, b: 20  },
      { t: 69, r: 228, g: 85,  b: 25  },
      { t: 75, r: 220, g: 50,  b: 38  },
      { t: 82, r: 205, g: 25,  b: 28  },
      { t: 95, r: 160, g: 12,  b: 35  }
    ];

    const first = stops[0];
    const last = stops[stops.length - 1];

    if (valF <= first.t) return { bg: `rgb(${first.r}, ${first.g}, ${first.b})` };
    if (valF >= last.t) return { bg: `rgb(${last.r}, ${last.g}, ${last.b})` };

    let lower = first;
    let upper = last;
    for (let i = 0; i < stops.length - 1; i++) {
      if (valF >= stops[i].t && valF <= stops[i + 1].t) {
        lower = stops[i];
        upper = stops[i + 1];
        break;
      }
    }

    const factor = (valF - lower.t) / (upper.t - lower.t);
    const r = Math.round(lower.r + factor * (upper.r - lower.r));
    const g = Math.round(lower.g + factor * (upper.g - lower.g));
    const b = Math.round(lower.b + factor * (upper.b - lower.b));
    return { bg: `rgb(${r}, ${g}, ${b})` };
  }

  function createWindArrowSvg(degrees) {
    if (degrees === null || degrees === undefined || isNaN(degrees)) return '';
    const reversedDeg = (Math.round(degrees) + 180) % 360;
    return `
      <div class="wind-arrow" style="transform: rotate(${reversedDeg}deg);">
        <svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round">
          <line x1="12" y1="19" x2="12" y2="5"></line>
          <polyline points="5 12 12 5 19 12"></polyline>
        </svg>
      </div>
      <span class="wind-deg">${Math.round(degrees)}</span>
    `;
  }

  function getPictocodeIcon(code) {
    const c = Number(code) || 1;
    // 1: Clear / Sunny
    if (c === 1) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none" stroke="#e57e00" stroke-width="2" stroke-linecap="round"><circle cx="12" cy="12" r="4"/><path d="M12 2v2M12 20v2M4.93 4.93l1.41 1.41M17.66 17.66l1.41 1.41M2 12h2M20 12h2M6.34 17.66l-1.41 1.41M19.07 4.93l-1.41 1.41"/></svg>`;
    }

    // Fog / Mist / Haze (Daily: 5; Hourly: 13, 14, 15, 16, 17, 18)
    if (c === 5 || (c >= 13 && c <= 18)) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none" stroke="#78909c" stroke-width="2" stroke-linecap="round"><line x1="4" y1="8" x2="20" y2="8"/><line x1="3" y1="12" x2="21" y2="12"/><line x1="5" y1="16" x2="19" y2="16"/></svg>`;
    }

    // Thunderstorms (Daily: 8; Hourly: 10, 11, 12, 27, 28, 30)
    if (c === 8 || (c >= 10 && c <= 12) || c === 27 || c === 28 || c === 30) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none">
        <path d="M6 14h11a3.5 3.5 0 0 0 .5-6.96 4.5 4.5 0 0 0-8.2-2.2A4 4 0 0 0 6 14z" fill="#cfd8dc" stroke="#546e7a" stroke-width="1.4" stroke-linejoin="round"/>
        <polygon points="12,13 9.5,17.5 12.5,17.5 11,22 15.5,16.5 12.5,16.5" fill="#f59e0b" stroke="#d97706" stroke-width="0.8" stroke-linejoin="round"/>
      </svg>`;
    }

    // Snow / Sleet (Daily: 9, 10, 11, 13, 15, 17; Hourly: 24, 26, 29, 32, 34, 35)
    if (c === 9 || c === 10 || c === 11 || c === 15 || c === 24 || c === 26 || c === 29 || c === 32 || c === 34 || c === 35) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none">
        <path d="M6 14h11a3.5 3.5 0 0 0 .5-6.96 4.5 4.5 0 0 0-8.2-2.2A4 4 0 0 0 6 14z" fill="#eceff1" stroke="#546e7a" stroke-width="1.4" stroke-linejoin="round"/>
        <line x1="8" y1="18" x2="8" y2="20" stroke="#90caf9" stroke-width="2" stroke-linecap="round"/>
        <line x1="12" y1="18" x2="12" y2="20" stroke="#90caf9" stroke-width="2" stroke-linecap="round"/>
        <line x1="16" y1="18" x2="16" y2="20" stroke="#90caf9" stroke-width="2" stroke-linecap="round"/>
      </svg>`;
    }

    // Rain / Showers (Daily: 6, 7, 12, 14, 16; Hourly: 23, 25, 31, 33)
    if (c === 6 || c === 7 || c === 12 || c === 14 || c === 16 || c === 23 || c === 25 || c === 31 || c === 33) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none">
        <path d="M6 14h11a3.5 3.5 0 0 0 .5-6.96 4.5 4.5 0 0 0-8.2-2.2A4 4 0 0 0 6 14z" fill="#eceff1" stroke="#546e7a" stroke-width="1.4" stroke-linejoin="round"/>
        <line x1="8" y1="17.5" x2="6.8" y2="21" stroke="#0284c7" stroke-width="1.8" stroke-linecap="round"/>
        <line x1="12" y1="17.5" x2="10.8" y2="21" stroke="#0284c7" stroke-width="1.8" stroke-linecap="round"/>
        <line x1="16" y1="17.5" x2="14.8" y2="21" stroke="#0284c7" stroke-width="1.8" stroke-linecap="round"/>
      </svg>`;
    }

    // Overcast / Cloudy / Partly Cloudy (Clean cloud with no drops or sun rays)
    return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none">
      <path d="M6.5 18h11a4 4 0 0 0 .5-7.97 5 5 0 0 0-9.8-1.53A4 4 0 0 0 6.5 18z" fill="#eceff1" stroke="#607d8b" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
    </svg>`;
  }

  function getPictocodeDescription(code, isDaily = false) {
    const c = Number(code) || 1;
    if (isDaily) {
      const dailyMap = {
        1: 'Sunny, clear sky',
        2: 'Sunny with few clouds',
        3: 'Partly cloudy',
        4: 'Overcast',
        5: 'Fog',
        6: 'Overcast with rain',
        7: 'Mixed with showers',
        8: 'Showers, thunderstorms likely',
        9: 'Overcast with snow',
        10: 'Mixed with snow showers',
        11: 'Mostly cloudy with snow and rain',
        12: 'Overcast with light rain',
        13: 'Overcast with light snow',
        14: 'Mostly cloudy with rain',
        15: 'Mostly cloudy with snow',
        16: 'Mostly cloudy with light rain',
        17: 'Mostly cloudy with light snow'
      };
      if (dailyMap[c]) return dailyMap[c];
    }

    const hourlyMap = {
      1: 'Clear sky',
      2: 'Clear with few cirrus',
      3: 'Clear with cirrus',
      4: 'Clear with few low clouds',
      5: 'Clear with low clouds and cirrus',
      6: 'Clear with low clouds and cirrus',
      7: 'Partly cloudy',
      8: 'Partly cloudy with few cirrus',
      9: 'Partly cloudy with cirrus',
      10: 'Mixed with possible thunderstorms',
      11: 'Mixed with possible thunderstorms',
      12: 'Mixed with possible thunderstorms',
      13: 'Clear but hazy',
      14: 'Hazy with few cirrus',
      15: 'Hazy with cirrus',
      16: 'Fog / low stratus',
      17: 'Fog / low stratus with cirrus',
      18: 'Fog / low stratus with cirrus',
      19: 'Mostly cloudy',
      20: 'Mostly cloudy with cirrus',
      21: 'Mostly cloudy with cirrus',
      22: 'Overcast',
      23: 'Overcast with rain',
      24: 'Overcast with snow',
      25: 'Overcast with heavy rain',
      26: 'Overcast with heavy snow',
      27: 'Rain, thunderstorms likely',
      28: 'Light rain, thunderstorms likely',
      29: 'Storm with heavy snow',
      30: 'Heavy rain, thunderstorms likely',
      31: 'Mixed with showers',
      32: 'Mixed with snow showers',
      33: 'Overcast with light rain',
      34: 'Overcast with light snow',
      35: 'Overcast with snow and rain'
    };

    return hourlyMap[c] || (c === 1 ? 'Clear sky' : 'Partly cloudy');
  }

  function getSunTimes(dateStr) {
    try {
      const parts = dateStr.split('-');
      const year = parseInt(parts[0], 10);
      const month = parseInt(parts[1], 10) - 1;
      const day = parseInt(parts[2], 10);
      const date = new Date(Date.UTC(year, month, day, 12, 0, 0));

      const lat = 37.855;
      const lon = -122.312;
      const dayOfYear = Math.floor((date - new Date(Date.UTC(year, 0, 0))) / 86400000);
      const b = (2 * Math.PI / 365) * (dayOfYear - 81);
      const eot = 9.87 * Math.sin(2 * b) - 7.53 * Math.cos(b) - 1.5 * Math.sin(b);
      const declination = 23.45 * Math.sin((2 * Math.PI / 365) * (dayOfYear - 81)) * (Math.PI / 180);

      const latRad = lat * (Math.PI / 180);
      const zenithRad = 90.833 * (Math.PI / 180);
      const cosH = (Math.cos(zenithRad) - Math.sin(latRad) * Math.sin(declination)) / (Math.cos(latRad) * Math.cos(declination));
      const hourAngleDeg = Math.acos(Math.max(-1, Math.min(1, cosH))) * (180 / Math.PI);

      const isDst = (month > 2 && month < 10) || (month === 2 && day > 8) || (month === 10 && day < 5);
      const tzOffsetHours = isDst ? -7 : -8;

      const solarNoonUtcMinutes = 720 - (lon * 4) - eot;
      const halfDayMinutes = (hourAngleDeg / 15) * 60;
      const sunriseUtcMinutes = solarNoonUtcMinutes - halfDayMinutes;
      const sunsetUtcMinutes = solarNoonUtcMinutes + halfDayMinutes;

      const formatMinutes = (utcMinutes) => {
        let localMinutes = utcMinutes + (tzOffsetHours * 60);
        while (localMinutes < 0) localMinutes += 1440;
        while (localMinutes >= 1440) localMinutes -= 1440;
        const h = Math.floor(localMinutes / 60);
        const m = Math.floor(localMinutes % 60);
        return `${String(h).padStart(2, '0')}:${String(m).padStart(2, '0')}`;
      };

      const sunriseStr = formatMinutes(sunriseUtcMinutes);
      const sunsetStr = formatMinutes(sunsetUtcMinutes);
      const parseToHourFloat = (str) => {
        const p = str.split(':');
        return parseInt(p[0], 10) + (parseInt(p[1], 10) / 60);
      };

      return {
        sunrise: sunriseStr,
        sunset: sunsetStr,
        sunriseHour: parseToHourFloat(sunriseStr),
        sunsetHour: parseToHourFloat(sunsetStr)
      };
    } catch (e) {
      return { sunrise: '07:11', sunset: '18:41', sunriseHour: 7.183, sunsetHour: 18.683 };
    }
  }

  function getClubSchedule(dateStr) {
    if (clubStatusCache[dateStr]) {
      return clubStatusCache[dateStr];
    }

    const dParts = dateStr.split('-');
    const year = parseInt(dParts[0], 10);
    const month = parseInt(dParts[1], 10) - 1;
    const day = parseInt(dParts[2], 10);
    const dateObj = new Date(year, month, day);
    const dayOfWeek = dateObj.getDay(); // 0 = Sun, 6 = Sat
    const isWeekend = (dayOfWeek === 0 || dayOfWeek === 6);

    const sun = getSunTimes(dateStr);
    const openTimeStr = isWeekend ? '10:00' : '13:00';
    const dockTimeStr = sun.sunset || '18:41';

    const parseToHourFloat = (str) => {
      const parts = str.split(':');
      return parseInt(parts[0], 10) + (parseInt(parts[1], 10) / 60);
    };

    const schedule = {
      isClosed: false,
      openTime: openTimeStr,
      dockTime: dockTimeStr,
      openHour: parseToHourFloat(openTimeStr),
      dockHour: parseToHourFloat(dockTimeStr),
      sunriseTime: sun.sunrise,
      sunsetTime: sun.sunset,
      sunriseHour: sun.sunriseHour,
      sunsetHour: sun.sunsetHour
    };

    clubStatusCache[dateStr] = schedule;
    return schedule;
  }

  function getCurrentHourStartIndex(times) {
    if (!times || !times.length) return 0;
    const now = new Date();
    const threshold = now.getTime() - (55 * 60 * 1000);

    for (let i = 0; i < times.length; i++) {
      const tStr = times[i].replace(' ', 'T');
      const tDate = new Date(tStr);
      if (!isNaN(tDate.getTime())) {
        if (tDate.getTime() >= threshold) {
          return i;
        }
      } else {
        const yr = now.getFullYear();
        const mo = String(now.getMonth() + 1).padStart(2, '0');
        const da = String(now.getDate()).padStart(2, '0');
        const hr = String(now.getHours()).padStart(2, '0');
        const currentPrefix = `${yr}-${mo}-${da} ${hr}`;
        if (times[i] >= currentPrefix) {
          return i;
        }
      }
    }
    return 0;
  }

  async function fetchClubStatusForDate(dateStr) {
    if (clubStatusCache[dateStr]) {
      return clubStatusCache[dateStr];
    }

    const cleanKey = dateStr.replace(/-/g, '');
    if (window.clubStatusCache && window.clubStatusCache[cleanKey]) {
      clubStatusCache[dateStr] = window.clubStatusCache[cleanKey];
      return clubStatusCache[dateStr];
    }

    const domain = window.location.hostname.includes('test.cal-sailing.org') ? 'test.cal-sailing.org' : 'www.cal-sailing.org';
    const targetUrl = `https://${domain}/index.php?option=com_csctides&view=gettidedatalist&task=gettidedatalist&tmpl=component&output=json&tidedate=${dateStr}`;

    try {
      let rawText = null;
      try {
        const resp = await fetch(targetUrl);
        if (resp.ok) rawText = await resp.text();
      } catch (directErr) {
        const proxyUrl = `https://api.allorigins.win/get?url=${encodeURIComponent(targetUrl)}`;
        const pResp = await fetch(proxyUrl);
        if (pResp.ok) {
          const pData = await pResp.json();
          rawText = pData.contents;
        }
      }

      if (rawText) {
        const jsonString = rawText.replace(/<pre.*?>|<\/pre>/g, '');
        const responseData = JSON.parse(jsonString);
        const clubData = responseData.data;

        if (clubData) {
          const parseTime = (timeStr) => {
            if (!timeStr) return null;
            timeStr = timeStr.toLowerCase().trim();
            if (timeStr === 'sunset') return 'sunset';
            if (timeStr === 'noon') return '12:00';
            const pm = timeStr.includes('pm');
            const parts = timeStr.replace(/am|pm/i, '').trim().split(':');
            let hours = parseInt(parts[0], 10);
            const minutes = parts.length > 1 ? parseInt(parts[1], 10) : 0;
            if (isNaN(hours)) return null;
            if (pm && hours < 12) hours += 12;
            else if (!pm && hours === 12) hours = 0;
            return `${String(hours).padStart(2, '0')}:${String(minutes).padStart(2, '0')}`;
          };

          const isClosed = clubData.clubclosed === true || clubData.clubclosed === 'true';
          const sunsetTime = parseTime(clubData.sunsettime);
          const openTime = parseTime(clubData.opentime);
          const dockTime = parseTime(clubData.docktime);

          let midDayDock = null;
          let midDayOpen = null;
          if (clubData.middayclosetext && clubData.middayclosetext !== 'null') {
            const times = clubData.middayclosetext.match(/(\d{1,2}:\d{2}\s*(am|pm))/gi);
            if (times && times.length >= 2) {
              midDayDock = parseTime(times[0]);
              midDayOpen = parseTime(times[1]);
            }
          }

          const sunTimes = getSunTimes(dateStr);
          const sunsetFormatted = sunsetTime || sunTimes.sunset || "18:41";
          const finalDockTime = (dockTime === 'sunset' || !dockTime) ? sunsetFormatted : dockTime;

          const dObj = new Date(dateStr + 'T12:00:00Z');
          const dayOfWeek = dObj.getUTCDay();
          const isWeekend = (dayOfWeek === 0 || dayOfWeek === 6);
          const finalOpenTime = openTime || (isWeekend ? "10:00" : "13:00");

          const parseToHourFloat = (str) => {
            if (!str) return null;
            const parts = str.split(':');
            return parseInt(parts[0], 10) + (parseInt(parts[1], 10) / 60);
          };

          const parsed = {
            isClosed,
            openTime: finalOpenTime,
            dockTime: finalDockTime,
            openHour: parseToHourFloat(finalOpenTime),
            dockHour: parseToHourFloat(finalDockTime),
            midDayDock,
            midDayOpen,
            sunsetTime: sunsetFormatted,
            sunriseTime: sunTimes.sunrise,
            sunriseHour: sunTimes.sunriseHour,
            sunsetHour: parseToHourFloat(sunsetFormatted)
          };
          clubStatusCache[dateStr] = parsed;
          return parsed;
        }
      }
    } catch (e) {
      // Fallback calculation will handle below
    }

    const sunTimes = getSunTimes(dateStr);
    const dObj = new Date(dateStr + 'T12:00:00Z');
    const dayOfWeek = dObj.getUTCDay();
    const isWeekend = (dayOfWeek === 0 || dayOfWeek === 6);

    const parseToHourFloat = (str) => {
      if (!str) return null;
      const parts = str.split(':');
      return parseInt(parts[0], 10) + (parseInt(parts[1], 10) / 60);
    };

    const openTimeStr = isWeekend ? "10:00" : "13:00";
    const dockTimeStr = sunTimes.sunset || "18:41";

    const fallback = {
      isClosed: false,
      openTime: openTimeStr,
      dockTime: dockTimeStr,
      openHour: parseToHourFloat(openTimeStr),
      dockHour: parseToHourFloat(dockTimeStr),
      midDayDock: null,
      midDayOpen: null,
      midDayDockHour: null,
      midDayOpenHour: null,
      sunsetTime: dockTimeStr,
      sunriseTime: sunTimes.sunrise,
      sunriseHour: sunTimes.sunriseHour,
      sunsetHour: sunTimes.sunsetHour
    };

    clubStatusCache[dateStr] = fallback;
    return fallback;
  }

  function getHourHeaderBackground(hourNum, sched) {
    if (!sched) return '';
    const oH = (!sched.isClosed && sched.openHour !== null) ? sched.openHour : null;
    const dH = (!sched.isClosed && sched.dockHour !== null) ? sched.dockHour : null;
    const srH = sched.sunriseHour !== undefined && sched.sunriseHour !== null ? sched.sunriseHour : 7.18;
    const ssH = sched.sunsetHour !== undefined && sched.sunsetHour !== null ? sched.sunsetHour : 18.68;

    // Full night before sunrise
    if (hourNum + 1 <= srH) {
      return 'background-color: var(--night-hour-bg);';
    }

    // Sunrise transition hour
    if (hourNum < srH && hourNum + 1 > srH) {
      const srPct = Math.round((srH - hourNum) * 100);
      return `background: linear-gradient(to right, var(--night-hour-bg) ${srPct}%, transparent ${srPct}%);`;
    }

    // Full night after sunset
    if (hourNum >= ssH) {
      return 'background-color: var(--night-hour-bg);';
    }

    // Sunset transition hour
    if (hourNum < ssH && hourNum + 1 > ssH) {
      const ssPct = Math.round((ssH - hourNum) * 100);
      if (dH !== null && Math.abs(dH - ssH) < 0.1 && hourNum >= (oH || 0)) {
        return `background: linear-gradient(to right, var(--club-open-hour-bg) ${ssPct}%, var(--night-hour-bg) ${ssPct}%);`;
      }
      return `background: linear-gradient(to right, transparent ${ssPct}%, var(--night-hour-bg) ${ssPct}%);`;
    }

    // Club open hours during daylight
    if (oH !== null && dH !== null) {
      if (hourNum >= oH && hourNum + 1 <= dH) {
        return 'background-color: var(--club-open-hour-bg);';
      }

      if (hourNum < oH && hourNum + 1 > oH) {
        const startPct = Math.round((oH - hourNum) * 100);
        if (hourNum + 1 <= dH) {
          return `background: linear-gradient(to right, transparent ${startPct}%, var(--club-open-hour-bg) ${startPct}%);`;
        }
      }

      if (hourNum < dH && hourNum + 1 > dH) {
        const endPct = Math.round((dH - hourNum) * 100);
        return `background: linear-gradient(to right, var(--club-open-hour-bg) ${endPct}%, transparent ${endPct}%);`;
      }
    }

    return '';
  }

  function renderHourlyTable(thead, tbody) {
    const data = weatherData.data_1h;
    const units = weatherData.units;
    if (!data || !data.time || !data.time.length) return;

    const startIdx = getCurrentHourStartIndex(data.time);
    const numHours = Math.min(data.time.length, 168);
    thead.innerHTML = '';
    tbody.innerHTML = '';

    const daySpans = [];
    let currentDayStr = null;
    let currentSpan = 0;
    let currentFirstIdx = startIdx;

    for (let i = startIdx; i < numHours; i++) {
      const dayStr = data.time[i].substring(0, 10);
      if (dayStr !== currentDayStr) {
        if (currentDayStr !== null) {
          daySpans.push({ dayStr: currentDayStr, span: currentSpan, firstHour: currentFirstIdx });
        }
        currentDayStr = dayStr;
        currentSpan = 1;
        currentFirstIdx = i;
      } else {
        currentSpan++;
      }
    }
    if (currentSpan > 0) {
      daySpans.push({ dayStr: currentDayStr, span: currentSpan, firstHour: currentFirstIdx });
    }

    // Group Header Row
    const groupHeaderRow = document.createElement('tr');
    groupHeaderRow.innerHTML = `<th></th>`;
    daySpans.forEach((ds) => {
      const th = document.createElement('th');
      th.className = 'day-group-header';
      th.colSpan = ds.span;
      const dObj = new Date(ds.dayStr + 'T12:00:00Z');
      const formatted = dObj.toLocaleDateString('en-US', { weekday: 'short', day: 'numeric', month: 'short' });
      th.textContent = formatted;
      th.style.cursor = 'pointer';
      th.title = 'Click to jump to this day';
      th.onclick = () => jumpToTimelineDay(0, ds.firstHour);
      groupHeaderRow.appendChild(th);
    });
    thead.appendChild(groupHeaderRow);

    // Hourly Subheader Row
    const hourHeaderRow = document.createElement('tr');
    hourHeaderRow.className = 'row-hour-header';
    hourHeaderRow.innerHTML = `<th>Hour</th>`;
    for (let i = startIdx; i < numHours; i++) {
      const th = document.createElement('th');
      th.id = `col-hour-${i}`;
      const timeStr = data.time[i];
      const hourNum = parseInt(timeStr.substring(11, 13), 10) || 0;
      const dayStr = timeStr.substring(0, 10);
      const sched = getClubSchedule(dayStr);

      const bgStyle = getHourHeaderBackground(hourNum, sched);
      if (bgStyle) {
        th.style.cssText = bgStyle;
      }

      let headerLinesHtml = '';
      if (sched && !sched.isClosed && sched.openHour !== null && sched.dockHour !== null) {
        const openCellHour = Math.floor(sched.openHour);
        const dockCellHour = Math.floor(sched.dockHour);
        const openFraction = sched.openHour - openCellHour;
        const dockFraction = sched.dockHour - dockCellHour;
        const openPct = Math.round(openFraction * 100);
        const dockPct = Math.round(dockFraction * 100);

        if (hourNum === openCellHour) {
          headerLinesHtml += `<div class="wind-sched-line line-open" style="left: ${openPct}%; top: 0; bottom: 0;"></div>`;
        }
        if (hourNum === dockCellHour) {
          headerLinesHtml += `<div class="wind-sched-line line-dock" style="left: ${dockPct}%; top: 0; bottom: 0;"></div>`;
        }
      }

      th.innerHTML = `${headerLinesHtml}<span class="hour-time">${String(hourNum).padStart(2, '0')}</span>`;
      hourHeaderRow.appendChild(th);
    }
    thead.appendChild(hourHeaderRow);

    // 1. Wind (kts) Row with Schedule Badges, Fill & Lines
    const windRow = document.createElement('tr');
    windRow.innerHTML = `<td>Wind<span class="unit-label">(kts)</span></td>`;
    for (let i = startIdx; i < numHours; i++) {
      const spdKt = toKnots(data.windspeed ? data.windspeed[i] : null, units.windspeed);
      const dirDeg = (data.winddirection && data.winddirection[i] !== undefined) ? data.winddirection[i] : 230;
      const td = document.createElement('td');
      td.className = 'wind-histo-cell';

      const barHeight = Math.max(38, Math.min(110, Math.round(35 + ((spdKt || 0) / 24) * 73)));
      const windClass = getWindClass(spdKt);

      const timeStr = data.time[i];
      const dayStr = timeStr.substring(0, 10);
      const hourNum = parseInt(timeStr.substring(11, 13), 10) || 0;
      const sched = getClubSchedule(dayStr);

      let nightHtml = '';
      if (sched) {
        const srH = sched.sunriseHour !== undefined && sched.sunriseHour !== null ? sched.sunriseHour : 7.18;
        const ssH = sched.sunsetHour !== undefined && sched.sunsetHour !== null ? sched.sunsetHour : 18.68;

        if (hourNum + 1 <= srH) {
          nightHtml = `<div class="wind-night-fill" style="left: 0%; width: 100%; bottom: ${barHeight}px;"></div>`;
        } else if (hourNum < srH && hourNum + 1 > srH) {
          const srPct = Math.round((srH - hourNum) * 100);
          nightHtml = `<div class="wind-night-fill" style="left: 0%; width: ${srPct}%; bottom: ${barHeight}px;"></div>`;
        } else if (hourNum >= ssH) {
          nightHtml = `<div class="wind-night-fill" style="left: 0%; width: 100%; bottom: ${barHeight}px;"></div>`;
        } else if (hourNum < ssH && hourNum + 1 > ssH) {
          const ssPct = Math.round((ssH - hourNum) * 100);
          nightHtml = `<div class="wind-night-fill" style="left: ${ssPct}%; width: ${100 - ssPct}%; bottom: ${barHeight}px;"></div>`;
        }
      }

      let scheduleHtml = '';
      if (sched && !sched.isClosed && sched.openHour !== null && sched.dockHour !== null) {
        const openCellHour = Math.floor(sched.openHour);
        const dockCellHour = Math.floor(sched.dockHour);

        const openFraction = sched.openHour - openCellHour;
        const dockFraction = sched.dockHour - dockCellHour;

        const openPct = Math.round(openFraction * 100);
        const dockPct = Math.round(dockFraction * 100);

        // Fill area between the Open and Dock lines with the same light green
        if (hourNum >= openCellHour && hourNum <= dockCellHour) {
          let fillLeft = '0%';
          let fillWidth = '100%';

          if (hourNum === openCellHour && hourNum === dockCellHour) {
            fillLeft = `${openPct}%`;
            fillWidth = `${Math.max(0, dockPct - openPct)}%`;
          } else if (hourNum === openCellHour) {
            fillLeft = `${openPct}%`;
            fillWidth = `${100 - openPct}%`;
          } else if (hourNum === dockCellHour) {
            fillLeft = '0%';
            fillWidth = `${dockPct}%`;
          }

          if (fillWidth !== '0%') {
            scheduleHtml += `<div class="wind-sched-fill" style="left: ${fillLeft}; width: ${fillWidth}; bottom: ${barHeight}px;"></div>`;
          }
        }

        // Render Open line and box at exact opening time
        if (hourNum === openCellHour) {
          scheduleHtml += `
            <div class="wind-sched-line line-open" style="left: ${openPct}%; bottom: ${barHeight}px;"></div>
            <div class="wind-sched-marker marker-open" style="left: ${openPct}%;">
              <div class="wind-club-flag flag-open" title="Club Opens: ${sched.openTime}">Open ${sched.openTime}</div>
            </div>
          `;
        }

        // Render Dock line and box at exact sunset/dock time
        if (hourNum === dockCellHour) {
          scheduleHtml += `
            <div class="wind-sched-line line-dock" style="left: ${dockPct}%; bottom: ${barHeight}px;"></div>
            <div class="wind-sched-marker marker-dock" style="left: ${dockPct}%;">
              <div class="wind-club-flag flag-dock" title="Dock Time: ${sched.dockTime}">Dock ${sched.dockTime}</div>
            </div>
          `;
        }
      }

      td.innerHTML = `
        ${nightHtml}
        ${scheduleHtml}
        <div class="wind-histo-container">
          <span class="wind-histo-val">${spdKt !== null ? spdKt : '-'}</span>
          <div class="wind-histo-bar ${windClass}" style="height: ${barHeight}px;">
            ${createWindArrowSvg(dirDeg)}
          </div>
        </div>
      `;
      windRow.appendChild(td);
    }
    tbody.appendChild(windRow);

    // 2. Gust Row
    const gustRow = document.createElement('tr');
    gustRow.innerHTML = `<td>Gust</td>`;
    for (let i = startIdx; i < numHours; i++) {
      let gustKt = (data.gust && data.gust[i] !== undefined && data.gust[i] !== null)
        ? toKnots(data.gust[i], units.windspeed)
        : null;
      if (gustKt === null && data.windspeed) {
        const baseKt = toKnots(data.windspeed[i], units.windspeed);
        gustKt = baseKt ? Math.round(baseKt * 1.35) : 0;
      }
      const td = document.createElement('td');
      td.className = getWindClass(gustKt);
      td.innerHTML = `<span style="font-weight:400; font-size:0.75rem;">${gustKt !== null ? gustKt : '-'}</span>`;
      gustRow.appendChild(td);
    }
    tbody.appendChild(gustRow);

    // 3. Sky Row
    const skyRow = document.createElement('tr');
    skyRow.innerHTML = `<td>Sky</td>`;
    for (let i = startIdx; i < numHours; i++) {
      const code = (data.pictocode && data.pictocode[i] !== undefined) ? data.pictocode[i] : 2;
      const desc = getPictocodeDescription(code, false);
      const td = document.createElement('td');
      td.title = desc;
      td.innerHTML = `<div class="weather-icon-cell" title="${desc}">${getPictocodeIcon(code)}</div>`;
      skyRow.appendChild(td);
    }
    tbody.appendChild(skyRow);

    // 4. Temp Row
    const tempRow = document.createElement('tr');
    tempRow.className = 'row-temp';
    tempRow.innerHTML = `<td>°F</td>`;
    for (let i = startIdx; i < numHours; i++) {
      const valF = toFahrenheit(data.temperature ? data.temperature[i] : null, units.temperature);
      const tempColor = getTemperatureColor(valF);
      const td = document.createElement('td');
      td.innerHTML = `<span class="hourly-temp-pill" style="color: ${tempColor.bg}; font-weight: 400;">${valF !== null ? valF : '-'}</span>`;
      tempRow.appendChild(td);
    }
    tbody.appendChild(tempRow);

    // 5. Rain % Row
    const popRow = document.createElement('tr');
    popRow.innerHTML = `<td>Rain %</td>`;
    for (let i = startIdx; i < numHours; i++) {
      const td = document.createElement('td');
      let pop = null;
      if (data.precipitation_probability && data.precipitation_probability[i] !== undefined && data.precipitation_probability[i] !== null) {
        pop = data.precipitation_probability[i];
      } else if (weatherData.data_day && weatherData.data_day.precipitation_probability) {
        const dayIdx = Math.min(Math.floor(i / 24), weatherData.data_day.precipitation_probability.length - 1);
        pop = weatherData.data_day.precipitation_probability[dayIdx];
      }
      td.textContent = (pop !== null && pop > 0) ? `${Math.round(pop)}%` : '-';
      popRow.appendChild(td);
    }
    tbody.appendChild(popRow);

    updateTimelineSelector(0);
  }

  function render7DayTable(thead, tbody) {
    const data = weatherData.data_day;
    const units = weatherData.units;
    if (!data || !data.time || !data.time.length) return;

    const numDays = Math.min(data.time.length, 7);
    thead.innerHTML = '';
    tbody.innerHTML = '';

    // Date Header Row
    const headerRow = document.createElement('tr');
    headerRow.innerHTML = `<th></th>`;
    for (let i = 0; i < numDays; i++) {
      const th = document.createElement('th');
      th.id = `col-day-${i}`;
      const dObj = new Date(data.time[i] + 'T12:00:00Z');
      const dayName = dObj.toLocaleDateString('en-US', { weekday: 'short' });
      const dateStr = dObj.toLocaleDateString('en-US', { day: '2-digit', month: 'short' });
      th.innerHTML = `
        <span class="day-name">${dayName}</span>
        <span class="day-date">${dateStr}</span>
      `;
      th.style.cursor = 'pointer';
      th.onclick = () => jumpToTimelineDay(i);
      headerRow.appendChild(th);
    }
    thead.appendChild(headerRow);

    // 1. Wind (kts) Row
    const windRow = document.createElement('tr');
    windRow.innerHTML = `<td>Wind<span class="unit-label">(kts)</span></td>`;
    for (let i = 0; i < numDays; i++) {
      const minKt = toKnots(data.windspeed_min ? data.windspeed_min[i] : null, units.windspeed);
      const maxKt = toKnots(data.windspeed_max ? data.windspeed_max[i] : null, units.windspeed);
      const dirDeg = (data.winddirection && data.winddirection[i] !== undefined) ? data.winddirection[i] : 230;
      const td = document.createElement('td');
      const maxVal = maxKt !== null ? maxKt : 0;
      td.className = getWindClass(maxVal);

      const spdText = (minKt !== null && maxKt !== null)
        ? ((minKt === maxKt) ? `${minKt}` : `${minKt} - ${maxKt}`)
        : (maxKt !== null ? `${maxKt}` : '-');
      td.innerHTML = `
        <div style="font-size:0.82rem; font-weight:400;">${spdText}</div>
        ${createWindArrowSvg(dirDeg)}
      `;
      windRow.appendChild(td);
    }
    tbody.appendChild(windRow);

    // 2. Gust Row
    const gustRow = document.createElement('tr');
    gustRow.innerHTML = `<td>Gust</td>`;
    for (let i = 0; i < numDays; i++) {
      let gustVal = null;
      if (data.gust_max && data.gust_max[i] !== undefined) {
        gustVal = toKnots(data.gust_max[i], units.windspeed);
      } else if (weatherData.data_1h && weatherData.data_1h.gust) {
        const thisDayStr = data.time[i];
        const hourlyGusts = [];
        for (let h = 0; h < weatherData.data_1h.time.length; h++) {
          if (weatherData.data_1h.time[h].startsWith(thisDayStr) && weatherData.data_1h.gust[h] !== null) {
            hourlyGusts.push(weatherData.data_1h.gust[h]);
          }
        }
        if (hourlyGusts.length > 0) {
          gustVal = toKnots(Math.max(...hourlyGusts), units.windspeed);
        }
      }
      if (gustVal === null && data.windspeed_max) {
        const maxKt = toKnots(data.windspeed_max[i], units.windspeed);
        gustVal = maxKt ? Math.round(maxKt * 1.35) : 0;
      }

      const td = document.createElement('td');
      td.className = getWindClass(gustVal);
      td.innerHTML = `<span style="font-weight:400; font-size:0.8rem;">${gustVal !== null ? gustVal : '-'}</span>`;
      gustRow.appendChild(td);
    }
    tbody.appendChild(gustRow);

    // 3. Sky Row
    const outlookRow = document.createElement('tr');
    outlookRow.innerHTML = `<td>Sky</td>`;
    for (let i = 0; i < numDays; i++) {
      const code = data.pictocode ? data.pictocode[i] : 2;
      const desc = getPictocodeDescription(code, true);
      const iconSvg = getPictocodeIcon(code);
      const td = document.createElement('td');
      td.title = desc;
      td.innerHTML = `<div class="weather-icon-cell" title="${desc}" style="width:24px; height:24px; margin:0 auto; cursor:help;">${iconSvg}</div>`;
      outlookRow.appendChild(td);
    }
    tbody.appendChild(outlookRow);

    // 4. Temp Row
    const tempRow = document.createElement('tr');
    tempRow.innerHTML = `<td>Temp<span class="unit-label">in °F</span></td>`;
    for (let i = 0; i < numDays; i++) {
      const maxF = toFahrenheit(data.temperature_max ? data.temperature_max[i] : null, units.temperature);
      const minF = toFahrenheit(data.temperature_min ? data.temperature_min[i] : null, units.temperature);
      const hiColor = getTemperatureColor(maxF);
      const loColor = getTemperatureColor(minF);
      const td = document.createElement('td');
      td.innerHTML = `
        <span style="color: ${hiColor.bg}; font-weight:400;">${maxF !== null ? maxF : '-'}</span><br/>
        <span style="color: ${loColor.bg}; font-weight:400;">${minF !== null ? minF : '-'}</span>
      `;
      tempRow.appendChild(td);
    }
    tbody.appendChild(tempRow);

    // 5. Sunrise & Sunset Row
    const sunRow = document.createElement('tr');
    sunRow.innerHTML = `<td>Sunrise<br/>Sunset</td>`;
    for (let i = 0; i < numDays; i++) {
      const times = getSunTimes(data.time[i]);
      const td = document.createElement('td');
      td.innerHTML = `<span style="font-size:0.68rem; line-height:1.2; display:block;">${times.sunrise}<br/>${times.sunset}</span>`;
      sunRow.appendChild(td);
    }
    tbody.appendChild(sunRow);

    // 6. Rain % Row
    const popRow = document.createElement('tr');
    popRow.innerHTML = `<td>Rain %</td>`;
    for (let i = 0; i < numDays; i++) {
      const td = document.createElement('td');
      const pop = data.precipitation_probability ? data.precipitation_probability[i] : null;
      td.textContent = (pop !== null && pop > 0) ? `${Math.round(pop)}%` : '-';
      popRow.appendChild(td);
    }
    tbody.appendChild(popRow);
  }

  function renderWindOverview() {
    const barsContainer = document.getElementById('timelineBars');
    const labelsContainer = document.getElementById('timelineLabels');
    const peakBadge = document.getElementById('overviewPeakBadge');
    if (!barsContainer || !labelsContainer || !weatherData) return;

    barsContainer.innerHTML = '';
    labelsContainer.innerHTML = '';

    const hourly = weatherData.data_1h;
    const units = weatherData.units;
    if (!hourly || !hourly.time) return;

    const totalHours = Math.min(hourly.time.length, 168);
    const dayData = weatherData.data_day;
    const numDays = Math.min((dayData?.time?.length || 7), 7);

    for (let d = 0; d < numDays; d++) {
      const lbl = document.createElement('div');
      lbl.className = 'timeline-day-label';
      const dateStr = dayData ? dayData.time[d] : hourly.time[d * 24]?.substring(0, 10);
      if (dateStr) {
        const dObj = new Date(dateStr + 'T12:00:00Z');
        lbl.textContent = dObj.toLocaleDateString('en-US', { weekday: 'short', day: 'numeric' });
      } else {
        lbl.textContent = `Day ${d + 1}`;
      }
      lbl.onclick = (e) => {
        e.stopPropagation();
        jumpToTimelineDay(d, d * 24);
      };
      labelsContainer.appendChild(lbl);
    }

    const gustsKnots = [];
    for (let h = 0; h < totalHours; h++) {
      let g = (hourly.gust && hourly.gust[h] !== null && hourly.gust[h] !== undefined)
        ? toKnots(hourly.gust[h], units.windspeed)
        : null;
      if (g === null && hourly.windspeed) {
        const base = toKnots(hourly.windspeed[h], units.windspeed);
        g = base ? Math.round(base * 1.35) : 0;
      }
      gustsKnots.push(g || 0);
    }

    const peakGust = Math.max(...gustsKnots, 10);
    if (peakBadge) peakBadge.textContent = `Peak: ${peakGust} kts`;

    const startIdx = getCurrentHourStartIndex(hourly.time);

    for (let h = 0; h < totalHours; h++) {
      const val = gustsKnots[h];
      const bar = document.createElement('div');
      bar.className = 'timeline-bar';
      const heightPct = Math.max(12, Math.round((val / (peakGust * 1.1)) * 100));
      bar.style.height = `${heightPct}%`;
      bar.style.backgroundColor = getWindHexColor(val);
      if (h < startIdx) {
        bar.style.opacity = '0.35';
      }
      bar.title = `${hourly.time[h].replace('T', ' ')}: Gust ${val} kts`;

      const dayIdx = Math.floor(h / 24);
      bar.onclick = (e) => {
        e.stopPropagation();
        jumpToTimelineDay(dayIdx, h);
      };
      barsContainer.appendChild(bar);
    }

    const timelineWrapper = document.getElementById('timelineWrapper');
    if (timelineWrapper) {
      const handleTimelineScrub = (clientX) => {
        const rect = timelineWrapper.getBoundingClientRect();
        const clickX = Math.max(0, Math.min(rect.width, clientX - rect.left));
        const total = Math.min((weatherData?.data_1h?.time?.length || 168), 168);
        const targetHour = Math.min(total - 1, Math.floor((clickX / rect.width) * total));
        const dayIdx = Math.floor(targetHour / 24);
        jumpToTimelineDay(dayIdx, targetHour);
      };

      timelineWrapper.onclick = (e) => handleTimelineScrub(e.clientX);

      timelineWrapper.addEventListener('touchmove', (e) => {
        if (e.touches && e.touches.length > 0) {
          handleTimelineScrub(e.touches[0].clientX);
        }
      }, { passive: true });
    }
  }

  function getCurrentHourIndex() {
    if (!weatherData || !weatherData.data_1h || !weatherData.data_1h.time) return 0;
    const times = weatherData.data_1h.time;
    const now = new Date();

    const pad = (n) => String(n).padStart(2, '0');
    const localNowPrefix = `${now.getFullYear()}-${pad(now.getMonth() + 1)}-${pad(now.getDate())} ${pad(now.getHours())}`;
    const localNowIsoPrefix = `${now.getFullYear()}-${pad(now.getMonth() + 1)}-${pad(now.getDate())}T${pad(now.getHours())}`;

    for (let i = 0; i < times.length; i++) {
      const t = times[i];
      if (t.startsWith(localNowPrefix) || t.startsWith(localNowIsoPrefix)) {
        return i;
      }
    }

    const nowMs = now.getTime();
    let closestIdx = 0;
    let minDiff = Infinity;

    for (let i = 0; i < times.length; i++) {
      const parsedDate = new Date(times[i].replace(' ', 'T'));
      if (!isNaN(parsedDate.getTime())) {
        const diff = Math.abs(parsedDate.getTime() - nowMs);
        if (diff < minDiff) {
          minDiff = diff;
          closestIdx = i;
        }
      }
    }

    return closestIdx;
  }

  function scrollToHour(hourIdx, smooth = true) {
    const scrollContainer = document.querySelector('.table-scroll-container');
    const targetCol = document.getElementById(`col-hour-${hourIdx}`);
    if (!scrollContainer || !targetCol) return;

    isProgrammaticScrolling = true;
    if (programmaticScrollTimeout) clearTimeout(programmaticScrollTimeout);

    const stickyWidth = window.innerWidth <= 640 ? 58 : 68;
    const targetLeft = Math.max(0, targetCol.offsetLeft - stickyWidth);

    if (smooth) {
      scrollContainer.scrollTo({ left: targetLeft, behavior: 'smooth' });
    } else {
      scrollContainer.scrollLeft = targetLeft;
    }

    const dayIdx = Math.floor(hourIdx / 24);
    updateTimelineSelector(dayIdx);

    programmaticScrollTimeout = setTimeout(() => {
      isProgrammaticScrolling = false;
    }, 750);
  }

  function jumpToTimelineDay(dayIndex, hourIndex = null) {
    if (currentMode === 'day') {
      currentMode = 'hour';
      const tabDaily = document.getElementById('tabDaily');
      const tab7Day = document.getElementById('tab7Day');
      if (tabDaily && tab7Day) {
        tabDaily.classList.add('active');
        tab7Day.classList.remove('active');
      }
      renderForecast();
    }

    isProgrammaticScrolling = true;
    if (programmaticScrollTimeout) clearTimeout(programmaticScrollTimeout);

    const startIdx = weatherData?.data_1h?.time ? getCurrentHourStartIndex(weatherData.data_1h.time) : 0;
    let targetHourIdx = hourIndex !== null ? hourIndex : dayIndex * 24;
    if (targetHourIdx < startIdx) targetHourIdx = startIdx;

    setTimeout(() => {
      const targetCol = document.getElementById(`col-hour-${targetHourIdx}`);
      if (targetCol) {
        targetCol.scrollIntoView({ behavior: 'smooth', inline: 'start', block: 'nearest' });
      }
      updateTimelineSelector(dayIndex);
    }, 40);

    programmaticScrollTimeout = setTimeout(() => {
      isProgrammaticScrolling = false;
    }, 750);
  }

  function updateTimelineSelector(dayIndex) {
    const selector = document.getElementById('timelineSelector');
    const timelineWrapper = document.getElementById('timelineWrapper');
    if (!selector || !timelineWrapper) return;

    const totalWidth = timelineWrapper.clientWidth || 680;
    const dayWidth = totalWidth / 7;
    selector.style.display = 'block';
    selector.style.width = `${dayWidth}px`;
    selector.style.left = `${dayIndex * dayWidth}px`;
  }

  function syncTimelineOnTableScroll() {
    if (isProgrammaticScrolling || !weatherData) return;
    const scrollContainer = document.querySelector('.table-scroll-container');
    const selector = document.getElementById('timelineSelector');
    const timelineWrapper = document.getElementById('timelineWrapper');
    if (!scrollContainer || !selector || !timelineWrapper) return;

    const totalWrapperWidth = timelineWrapper.clientWidth || 680;
    const dayWidth = totalWrapperWidth / 7;
    selector.style.width = `${dayWidth}px`;
    selector.style.display = 'block';

    const stickyWidth = window.innerWidth <= 640 ? 58 : 68;

    if (currentMode === 'hour') {
      const currentScroll = scrollContainer.scrollLeft;
      const hourCols = document.querySelectorAll('th[id^="col-hour-"]');
      if (!hourCols.length) return;

      let activeHourIndex = 0;
      for (let i = 0; i < hourCols.length; i++) {
        const col = hourCols[i];
        if (col.offsetLeft + col.offsetWidth > currentScroll + stickyWidth + 10) {
          activeHourIndex = i;
          break;
        }
      }
      const totalHours = Math.min((weatherData.data_1h?.time?.length || 168), 168);
      const progress = activeHourIndex / Math.max(1, totalHours);
      const maxLeft = totalWrapperWidth - dayWidth;
      const targetLeft = Math.min(maxLeft, Math.max(0, progress * totalWrapperWidth));
      selector.style.left = `${targetLeft}px`;
    } else {
      const currentScroll = scrollContainer.scrollLeft;
      const dayCols = document.querySelectorAll('th[id^="col-day-"]');
      if (!dayCols.length) return;

      let activeDayIndex = 0;
      for (let i = 0; i < dayCols.length; i++) {
        const col = dayCols[i];
        if (col.offsetLeft + col.offsetWidth > currentScroll + stickyWidth + 20) {
          activeDayIndex = i;
          break;
        }
      }
      const maxLeft = totalWrapperWidth - dayWidth;
      const targetLeft = Math.min(maxLeft, Math.max(0, activeDayIndex * dayWidth));
      selector.style.left = `${targetLeft}px`;
    }
  }

  function getFallbackMockData() {
    const now = new Date();
    const dailyTimes = [];
    const hourlyTimes = [];

    for (let d = 0; d < 7; d++) {
      const dt = new Date(now.getTime() + d * 86400000);
      dailyTimes.push(dt.toISOString().substring(0, 10));
    }

    for (let h = 0; h < 168; h++) {
      const ht = new Date(now.getTime() + h * 3600000);
      hourlyTimes.push(ht.toISOString().substring(0, 16).replace('T', ' '));
    }

    const isoNow = now.toISOString().substring(0, 16).replace('T', ' ');

    return {
      units: {
        temperature: '°C',
        windspeed: 'm/s',
        precipitation: 'mm',
        precipitation_probability: '%'
      },
      metadata: {
        latitude: 37.855,
        longitude: -122.312,
        modelrun_utc: isoNow,
        modelrun_updatetime_utc: isoNow
      },
      data_day: {
        time: dailyTimes,
        temperature_max: [21.1, 20.0, 18.3, 16.1, 17.2, 18.8, 19.4],
        temperature_min: [16.6, 15.5, 16.1, 15.0, 14.4, 15.0, 15.5],
        windspeed_min: [1.0, 1.0, 1.5, 5.6, 4.5, 3.0, 2.0],
        windspeed_max: [3.1, 3.1, 6.2, 6.2, 8.5, 7.0, 5.5],
        winddirection: [220, 225, 230, 240, 235, 225, 220],
        gust_max: [5.1, 5.1, 8.7, 8.7, 12.0, 9.5, 7.8],
        pictocode: [2, 2, 2, 2, 3, 1, 2],
        precipitation: [0, 0, 0, 0, 0, 0, 0],
        precipitation_probability: [0, 0, 5, 0, 10, 0, 0]
      },
      data_1h: {
        time: hourlyTimes,
        temperature: Array.from({ length: 168 }, (_, i) => 15.5 + Math.sin(i / 12) * 4.5),
        windspeed: Array.from({ length: 168 }, (_, i) => {
          const dayIdx = Math.floor(i / 24);
          const hourOfDay = i % 24;
          const cycle = (hourOfDay >= 11 && hourOfDay <= 19) ? 6.5 : 2.5;
          return cycle + (dayIdx === 3 ? 3.5 : 0) + (Math.sin(i) * 1.2);
        }),
        gust: Array.from({ length: 168 }, (_, i) => {
          const dayIdx = Math.floor(i / 24);
          const hourOfDay = i % 24;
          const base = (hourOfDay >= 11 && hourOfDay <= 19) ? 9.5 : 4.0;
          return base + (dayIdx === 3 ? 4.5 : 0) + (Math.cos(i) * 1.5);
        }),
        winddirection: Array.from({ length: 168 }, () => 220 + Math.floor(Math.random() * 30)),
        pictocode: Array.from({ length: 168 }, () => 2),
        precipitation_probability: Array.from({ length: 168 }, (_, i) => (i % 24 >= 14 && i % 24 <= 17 && Math.floor(i / 24) === 4 ? 20 : 0)),
        precipitation: Array.from({ length: 168 }, () => 0)
      }
    };
  }

  function parseUtcTimestamp(utcString) {
    if (!utcString) return null;
    let cleanStr = String(utcString).trim();
    if (cleanStr.includes(' ')) {
      cleanStr = cleanStr.replace(' ', 'T');
    }
    if (!cleanStr.endsWith('Z') && !cleanStr.includes('+') && !cleanStr.slice(10).includes('-')) {
      cleanStr += 'Z';
    }
    const d = new Date(cleanStr);
    return isNaN(d.getTime()) ? null : d;
  }

  async function loadWeatherData() {
    const statusBadge = document.getElementById('statusBadge');
    const statusText = document.getElementById('statusText');
    const statusDot = document.getElementById('statusDot');
    const footerTimestamp = document.getElementById('footerTimestamp');

    statusText.textContent = 'Updating...';
    if (statusBadge) {
      statusBadge.className = 'status-badge micro updating';
    }
    statusDot.style.backgroundColor = '#d97706';

    let json = null;

    try {
      const response = await fetch(METEOBLUE_CACHE_URL, { cache: 'no-store' });
      if (response.ok) {
        json = await response.json();
      }

      if (json && (json.data_day || json.data_1h)) {
        weatherData = json;

        statusText.textContent = 'Meteoblue';
        if (statusBadge) {
          statusBadge.className = 'status-badge micro live';
        }
        statusDot.style.backgroundColor = '#24a148';
      } else {
        throw new Error('Unexpected JSON schema from cache');
      }
    } catch (cacheErr) {
      console.warn('Server cache fetch failed:', cacheErr.message);

      weatherData = getFallbackMockData();
      statusText.textContent = 'Demo Mode';
      if (statusBadge) {
        statusBadge.className = 'status-badge micro demo';
      }
      statusDot.style.backgroundColor = '#0f62fe';
    }

    const datesToPreload = new Set();
    if (weatherData.data_day?.time) {
      weatherData.data_day.time.forEach(t => datesToPreload.add(t.substring(0, 10)));
    }
    if (weatherData.data_1h?.time) {
      weatherData.data_1h.time.forEach(t => datesToPreload.add(t.substring(0, 10)));
    }

    await Promise.all(Array.from(datesToPreload).map(dStr => fetchClubStatusForDate(dStr)));

    renderForecast();
    renderWindOverview();

    setTimeout(() => {
      if (currentMode === 'hour') {
        const curIdx = getCurrentHourIndex();
        scrollToHour(curIdx, false);
      } else {
        updateTimelineSelector(0);
      }
    }, 50);

    let modelRunDate = null;
    const rawUpdateUtc = weatherData?.metadata?.modelrun_updatetime_utc 
      || weatherData?.metadata?.modelrun_utc 
      || weatherData?.modelrun_updatetime_utc;

    if (rawUpdateUtc) {
      modelRunDate = parseUtcTimestamp(rawUpdateUtc);
    }

    const displayDate = modelRunDate || new Date();
    const timeNow = displayDate.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit', hour12: false });
    const dateNow = displayDate.toLocaleDateString([], { day: '2-digit', month: 'short', year: 'numeric' });
    footerTimestamp.textContent = `Issued: ${dateNow} ${timeNow}`;
  }

  function renderForecast() {
    const table = document.getElementById('forecastTable');
    const thead = document.getElementById('tableHead');
    const tbody = document.getElementById('tableBody');

    if (currentMode === 'hour') {
      table.className = 'structured-forecast hourly-view';
      renderHourlyTable(thead, tbody);
    } else {
      table.className = 'structured-forecast seven-day-view';
      render7DayTable(thead, tbody);
    }
  }

  function initForecastApp() {
    const tabDaily = document.getElementById('tabDaily');
    const tab7Day = document.getElementById('tab7Day');
    const scrollContainer = document.querySelector('.table-scroll-container');

    if (scrollContainer) {
      scrollContainer.addEventListener('scroll', syncTimelineOnTableScroll, { passive: true });
    }

    if (tabDaily) {
      tabDaily.addEventListener('click', () => {
        if (currentMode === 'hour') return;
        currentMode = 'hour';
        tabDaily.classList.add('active');
        if (tab7Day) tab7Day.classList.remove('active');
        renderForecast();
        setTimeout(() => {
          const curIdx = getCurrentHourIndex();
          scrollToHour(curIdx, true);
        }, 50);
      });
    }

    if (tab7Day) {
      tab7Day.addEventListener('click', () => {
        if (currentMode === 'day') return;
        currentMode = 'day';
        tab7Day.classList.add('active');
        if (tabDaily) tabDaily.classList.remove('active');
        renderForecast();
        updateTimelineSelector(0);
      });
    }

    window.addEventListener('resize', () => {
      syncTimelineOnTableScroll();
    });

    loadWeatherData();
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initForecastApp);
  } else {
    initForecastApp();
  }
/* #end raw */
</script>

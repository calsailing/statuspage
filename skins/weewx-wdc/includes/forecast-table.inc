<!-- Forecast table include. Settings (time zone, refresh timing, club-hours proxy) are the constants at the top of the script. Add ?demo=1 to the page URL to preview with sample data. -->
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
    --skeleton-base: #ececec;
    --skeleton-highlight: #f8f8f8;
    --fc-sticky-w: 68px;   /* width of the sticky label column */
    --fc-focus: #0f62fe;   /* keyboard focus ring */
  }

  html.dark {
    --cds-ui-background: #161616;
    --cds-text-primary: #f4f4f4;
    --cds-text-secondary: #c6c6c6;
    --cds-ui-border: #393939;
    --club-open-hour-bg: rgba(34, 197, 94, 0.15);
    --night-hour-bg: #111827;
    --skeleton-base: #262626;
    --skeleton-highlight: #333333;
    --fc-focus: #78a9ff;
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

  /* Skeleton Shimmer Keyframes and Classes */
  @keyframes skeleton-shimmer {
    0% {
      background-position: -200% 0;
    }
    100% {
      background-position: 200% 0;
    }
  }

  .skeleton-shimmer {
    background: linear-gradient(
      90deg,
      var(--skeleton-base) 0%,
      var(--skeleton-highlight) 50%,
      var(--skeleton-base) 100%
    );
    background-size: 200% 100%;
    animation: skeleton-shimmer 1.5s infinite linear;
    border-radius: 2px;
  }

  .skeleton-pill {
    display: inline-block;
    height: 11px;
    width: 18px;
    margin: 0 auto;
  }

  .skeleton-pill.wide {
    width: 32px;
  }

  .skeleton-circle {
    display: inline-block;
    width: 16px;
    height: 16px;
    border-radius: 50%;
    margin: 0 auto;
  }

  .skeleton-bar-fill {
    width: 80%;
    margin: 0 auto;
    border-radius: 2px 2px 0 0;
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
    min-width: var(--fc-sticky-w);
    max-width: var(--fc-sticky-w);
    padding-left: 0.4rem;
    padding-right: 0.25rem;
  }

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
    min-width: var(--fc-sticky-w);
    max-width: var(--fc-sticky-w);
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

  table.structured-forecast.hourly-view .wind-histo-cell {
    height: 139px;
    vertical-align: bottom !important;
    padding: 0 !important;
    background-color: transparent !important;
    position: relative;
    overflow: visible;
  }

  .wind-sched-fill {
    position: absolute;
    top: 0;
    background-color: var(--club-open-hour-bg);
    z-index: 1;
    pointer-events: none;
  }

  .wind-night-fill {
    position: absolute;
    top: 0;
    background-color: var(--night-hour-bg);
    z-index: 1;
    pointer-events: none;
  }

  .wind-sched-line {
    position: absolute;
    top: 0;
    width: 1px;
    z-index: 11;
    pointer-events: none;
  }

  .wind-sched-line.line-open {
    background-color: #22c55e;
  }

  .wind-sched-line.line-dock {
    background-color: #f97316;
  }

  .wind-sched-marker {
    position: absolute;
    top: -3px;
    z-index: 12;
    pointer-events: none;
    white-space: nowrap;
  }

  .wind-sched-marker.marker-open {
    transform: translateX(-100%);
    margin-left: 4px;
  }

  .wind-sched-marker.marker-dock {
    transform: translateX(0);
    margin-left: -4px;
  }

  .wind-club-flag {
    font-size: 0.58rem;
    font-weight: 600;
    line-height: 1.15;
    padding: 0.12rem 0.32rem;
    border-radius: 0;
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
    min-width: var(--fc-sticky-w);
    max-width: var(--fc-sticky-w);
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
    touch-action: none;
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
    touch-action: none;
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
    text-align: center;
    font-size: 0.63rem;
    font-weight: 600;
    color: #525252;
    line-height: 18px;
    border-right: 1px solid #f0f0f0;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
    cursor: pointer;
  }
  .timeline-day-label:last-child {
    border-right: none;
  }

  /* Rigid, non-expanding selector box with zero transition lag */
  .timeline-selector {
    position: absolute;
    top: 0;
    bottom: 0;
    border: 2px solid #0f62fe;
    background-color: rgba(15, 98, 254, 0.12);
    border-radius: 3px;
    pointer-events: none;
    z-index: 5;
    box-sizing: border-box;
    will-change: left;
    display: none;
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
    background-color: #4ade80;
  }

  html.dark .wind-sched-line.line-dock {
    background-color: #fb923c;
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

  @media (max-width: 640px) {
    :root {
      --fc-sticky-w: 52px;
    }

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

    /* Narrower sticky label column on mobile (width comes from --fc-sticky-w) */
    table.structured-forecast th:first-child,
    table.structured-forecast td:first-child {
      padding: 0.25rem 0.2rem;
      font-size: 0.64rem;
    }

    table.structured-forecast.hourly-view th:first-child,
    table.structured-forecast.hourly-view td:first-child {
      padding: 0.25rem 0.2rem;
      font-size: 0.64rem;
    }

    /* Compact hourly columns on mobile so more hours fit */
    table.structured-forecast.hourly-view th,
    table.structured-forecast.hourly-view td {
      min-width: 24px;
      max-width: 26px;
      padding: 0.2rem 0;
      font-size: 0.68rem;
    }

    /* Streamlined, narrower day columns for 7-Day view on mobile */
    table.structured-forecast.seven-day-view th,
    table.structured-forecast.seven-day-view td {
      min-width: 37px;
      max-width: 44px;
      padding: 0.25rem 0.1rem;
      font-size: 0.68rem;
    }

    table.structured-forecast.seven-day-view th:first-child,
    table.structured-forecast.seven-day-view td:first-child {
      padding: 0.25rem 0.2rem;
      font-size: 0.64rem;
    }

    table.structured-forecast.seven-day-view .day-name {
      font-size: 0.72rem;
      letter-spacing: -0.02em;
    }

    table.structured-forecast.seven-day-view .day-date {
      font-size: 0.62rem;
      letter-spacing: -0.03em;
    }

    table.structured-forecast.seven-day-view .weather-icon-cell {
      height: 22px;
    }

    table.structured-forecast.seven-day-view .weather-icon-cell svg {
      width: 18px;
      height: 18px;
    }

    table.structured-forecast.seven-day-view .wind-arrow svg {
      width: 10px;
      height: 10px;
    }

    table.structured-forecast.seven-day-view .wind-deg {
      font-size: 0.58rem;
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

  /* ------------------------------------------------------------------
     Header buttons: keyboard-accessible "jump to day" controls
     ------------------------------------------------------------------ */
  .th-btn {
    display: block;
    width: 100%;
    margin: 0;
    padding: 0;
    border: 0;
    background: none;
    color: inherit;
    font: inherit;
    letter-spacing: inherit;
    text-align: inherit;
    cursor: pointer;
  }

  /* Visible keyboard focus */
  .th-btn:focus-visible,
  .carbon-switcher-btn:focus-visible,
  .status-badge.micro:focus-visible,
  .msg-retry:focus-visible,
  .table-scroll-container:focus-visible {
    outline: 2px solid var(--fc-focus);
    outline-offset: -2px;
  }

  /* ------------------------------------------------------------------
     Missing / estimated values and closed days
     ------------------------------------------------------------------ */
  .no-data {
    color: #6f6f6f;
  }

  .est-value {
    font-style: italic;
  }

  .day-closed-tag {
    display: inline-block;
    margin-left: 0.35rem;
    padding: 0 0.3rem;
    font-size: 0.62rem;
    font-weight: 600;
    line-height: 1.5;
    color: #a2191f;
    background-color: #fff1f1;
    border-radius: 2px;
  }

  table.structured-forecast.seven-day-view .day-closed-tag {
    display: block;
    width: max-content;
    margin: 2px auto 0;
  }

  html.dark .no-data {
    color: #a8a8a8;
  }

  html.dark .day-closed-tag {
    color: #ff8389;
    background-color: rgba(250, 77, 86, 0.2);
  }

  /* ------------------------------------------------------------------
     Notices (errors, stale data) and the extra status badges
     ------------------------------------------------------------------ */
  .forecast-message {
    display: flex;
    align-items: center;
    justify-content: space-between;
    flex-wrap: wrap;
    gap: 0.75rem;
    padding: 0.6rem 0.85rem;
    font-size: 0.8125rem;
    line-height: 1.4;
    border-bottom: 1px solid var(--cds-ui-border);
  }

  .forecast-message[hidden] {
    display: none;
  }

  .forecast-message.error {
    background-color: #fff1f1;
    color: #750e13;
  }

  .forecast-message.warn {
    background-color: #fcf4d6;
    color: #684e00;
  }

  html.dark .forecast-message.error {
    background-color: rgba(250, 77, 86, 0.16);
    color: #ffb3b8;
  }

  html.dark .forecast-message.warn {
    background-color: rgba(241, 194, 27, 0.14);
    color: #f1c21b;
  }

  .msg-retry {
    font: inherit;
    font-weight: 500;
    padding: 0.3rem 0.8rem;
    border: 1px solid currentColor;
    border-radius: 2px;
    background: transparent;
    color: inherit;
    cursor: pointer;
  }

  /* When there is no usable forecast, show only the notice */
  .app-card.is-error .table-scroll-container,
  .app-card.is-error .wind-overview-section {
    display: none;
  }

  .footer-note[hidden] {
    display: none;
  }

  .footer-note {
    text-decoration: underline dotted;
    text-underline-offset: 2px;
    cursor: help;
  }

  .status-badge.micro.stale {
    background-color: #fef3c7;
    color: #92400e;
  }

  .status-badge.micro.error {
    background-color: #fff1f1;
    color: #a2191f;
  }

  html.dark .status-badge.micro.stale {
    background-color: rgba(217, 119, 6, 0.25);
    color: #fcd34d;
  }

  html.dark .status-badge.micro.error {
    background-color: rgba(250, 77, 86, 0.22);
    color: #ff8389;
  }

  /* ------------------------------------------------------------------
     Respect reduced-motion preferences
     ------------------------------------------------------------------ */
  @media (prefers-reduced-motion: reduce) {
    .skeleton-shimmer {
      animation: none;
    }

    .carbon-switcher-btn,
    .status-badge.micro,
    .row-hour-header th,
    .wind-histo-bar,
    .wind-arrow,
    .timeline-bar {
      transition: none;
    }
  }
</style>

<div class="app-card" id="forecastCard">
  <!-- Top Bar with Centered Carbon Switcher -->
  <div class="view-switcher-container">
    <div class="carbon-switcher" role="tablist" aria-label="Forecast view">
      <button id="tabDaily" class="carbon-switcher-btn active" type="button" role="tab" aria-selected="true" aria-controls="forecastPanel" tabindex="0">Daily</button>
      <button id="tab7Day" class="carbon-switcher-btn" type="button" role="tab" aria-selected="false" aria-controls="forecastPanel" tabindex="-1">7 Day</button>
    </div>
  </div>

  <!-- Errors and stale-data notices -->
  <div id="forecastMessage" class="forecast-message" role="status" hidden></div>

  <noscript>
    <div class="forecast-message warn">The wind and weather forecast loads with JavaScript. Turn JavaScript on in your browser to see it.</div>
  </noscript>

  <!-- Table Container with Horizontal Scroll -->
  <div class="table-scroll-container" id="forecastPanel" role="tabpanel" aria-labelledby="tabDaily" aria-busy="true" tabindex="0">
    <table id="forecastTable" class="structured-forecast hourly-view" aria-label="Weather forecast">
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
      <div class="overview-hint" id="overviewHint">Touch or drag anywhere to scrub</div>
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
      <span id="footerTimestamp" aria-live="polite">Updated: Loading...</span>
      <span id="footerClubNote" class="footer-note" hidden></span>
    </div>
    <div class="footer-actions">
      <a href="https://docs.meteoblue.com/en/weather-apis/forecast-api/overview#what-is-the-meteoblue-learning-multimodel-mlm" target="_blank" rel="noopener noreferrer" class="status-badge micro updating" id="statusBadge" title="View Meteoblue Learning MultiModel (mLM) Documentation">
        <span class="status-dot" id="statusDot" style="background-color: #d97706;"></span>
        <span id="statusText">Loading...</span>
      </a>
    </div>
  </div>
</div>

<script>
/* #raw */
  // ===========================================================================
  // Configuration
  // ===========================================================================
  const METEOBLUE_CACHE_URL = 'https://status.cal-sailing.org/meteoblue_cache.json';

  // The club's location. Forecast time strings are read as wall-clock times in
  // SITE_TZ (not the viewer's zone), and "now" is computed in SITE_TZ too, so
  // the table lines up for viewers in any time zone.
  const SITE_TZ = 'America/Los_Angeles';
  const SITE_LAT = 37.855;
  const SITE_LON = -122.312;

  const FETCH_TIMEOUT_MS = 6000;            // every network request
  const CLUB_FIRST_PAINT_WAIT_MS = 1200;    // how long first paint waits for club hours
  const CLUB_TTL_MS = 60 * 60 * 1000;       // re-check club hours after this long
  const CLUB_RETRY_AFTER_MS = 5 * 60 * 1000;// back-off after a failed club-hours request
  const STALE_AFTER_HOURS = 12;             // warn when the model run is older than this
  const REFRESH_INTERVAL_MS = 15 * 60 * 1000;
  const RESUME_REFRESH_AFTER_MS = 5 * 60 * 1000;
  const GUST_ESTIMATE_FACTOR = 1.35;        // only used (and flagged "~") when the feed has no gust data

  // Club hours come from www.cal-sailing.org. If the browser blocks that request
  // (for example CORS on another origin), the table shows the standard schedule
  // and says so. Set this to true to route the request through a public proxy
  // instead; that sends every visitor's request via a third party.
  const USE_PUBLIC_CORS_PROXY = false;

  // Add ?demo=1 to the page URL to show sample data (never used as a fallback).
  const DEMO_MODE = /[?&]demo=1(?:&|$)/.test(window.location.search);

  // ===========================================================================
  // State
  // ===========================================================================
  let weatherData = null;
  let currentMode = 'hour'; // 'hour' = Daily view; 'day' = 7 Day view
  let loadState = 'loading'; // 'loading' | 'ready' | 'error'
  let isLoading = false;
  let lastLoadAt = 0;
  let programmaticScrollTimeout = null;
  let clubVersion = 0;
  let renderedClubVersion = 0;
  const clubStatusCache = {};       // dateStr -> schedule fetched from the club
  const clubFailedAt = {};          // dateStr -> timestamp of the last failed request
  const defaultScheduleCache = {};  // dateStr -> standard schedule
  const noticeState = { error: null, refreshFailed: false, stale: null };

  // ===========================================================================
  // Small helpers
  // ===========================================================================
  const $id = (id) => document.getElementById(id);
  const pad2 = (n) => String(n).padStart(2, '0');
  const sleep = (ms) => new Promise((resolve) => setTimeout(resolve, ms));

  function toHourFloat(str) {
    if (!str || typeof str !== 'string') return null;
    const m = /^(\d{1,2}):(\d{2})$/.exec(str.trim());
    if (!m) return null;
    const h = parseInt(m[1], 10);
    const mi = parseInt(m[2], 10);
    if (h > 23 || mi > 59) return null;
    return h + mi / 60;
  }

  function prefersReducedMotion() {
    try { return window.matchMedia('(prefers-reduced-motion: reduce)').matches; } catch (_) { return false; }
  }

  function isDarkTheme() {
    return document.documentElement.classList.contains('dark');
  }

  // Fetch text with a hard timeout covering both the headers and the body.
  // Resolves { ok, status, text }; rejects on network errors and timeouts.
  async function fetchTextWithTimeout(url, options = {}, timeoutMs = FETCH_TIMEOUT_MS) {
    const controller = new AbortController();
    const timer = setTimeout(() => controller.abort(), timeoutMs);
    try {
      const resp = await fetch(url, Object.assign({}, options, { signal: controller.signal }));
      const text = await resp.text();
      return { ok: resp.ok, status: resp.status, text };
    } finally {
      clearTimeout(timer);
    }
  }

  // ---- Site wall-clock helpers ---------------------------------------------
  // A "wall ms" is a wall-clock time expressed as milliseconds-since-epoch as if
  // it were UTC. It is only used for comparing and formatting wall-clock strings.
  const siteClockFormatter = (() => {
    try {
      return new Intl.DateTimeFormat('en-CA', {
        timeZone: SITE_TZ, year: 'numeric', month: '2-digit', day: '2-digit',
        hour: '2-digit', minute: '2-digit', hourCycle: 'h23'
      });
    } catch (e) { return null; }
  })();

  function getSiteWallMs(date = new Date()) {
    if (siteClockFormatter) {
      const p = {};
      siteClockFormatter.formatToParts(date).forEach((part) => { p[part.type] = part.value; });
      return Date.UTC(+p.year, +p.month - 1, +p.day, +p.hour % 24, +p.minute);
    }
    return Date.UTC(date.getFullYear(), date.getMonth(), date.getDate(), date.getHours(), date.getMinutes());
  }

  function wallStringToMs(str) {
    if (!str) return NaN;
    const m = /^(\d{4})-(\d{2})-(\d{2})(?:[ T](\d{2})(?::(\d{2}))?)?/.exec(String(str));
    if (!m) return NaN;
    return Date.UTC(+m[1], +m[2] - 1, +m[3], +(m[4] || 0), +(m[5] || 0));
  }

  function wallMsToString(ms) {
    const d = new Date(ms);
    return `${d.getUTCFullYear()}-${pad2(d.getUTCMonth() + 1)}-${pad2(d.getUTCDate())} ${pad2(d.getUTCHours())}:${pad2(d.getUTCMinutes())}`;
  }

  // Labels for calendar dates ("YYYY-MM-DD"). Pinned to UTC so the date never
  // shifts for viewers far from the club's time zone.
  function formatDayLabel(dayStr, options) {
    return new Date(dayStr + 'T12:00:00Z').toLocaleDateString('en-US', Object.assign({}, options, { timeZone: 'UTC' }));
  }

  function isWeekendDate(dateStr) {
    const dow = new Date(dateStr + 'T12:00:00Z').getUTCDay();
    return dow === 0 || dow === 6;
  }

  // ===========================================================================
  // Layout helpers
  // ===========================================================================
  // Width of the sticky label column. Read from the rendered table so it always
  // matches the CSS (--fc-sticky-w).
  function getStickyWidth() {
    const cell = document.querySelector('#forecastTable th:first-child');
    if (cell && cell.offsetWidth) return cell.offsetWidth;
    return window.innerWidth <= 640 ? 52 : 68;
  }

  // ===========================================================================
  // Notices, status badge and footer
  // ===========================================================================
  function showMessage(kind, text, options = {}) {
    const el = $id('forecastMessage');
    if (!el) return;
    el.className = `forecast-message ${kind}`;
    el.textContent = '';
    const span = document.createElement('span');
    span.textContent = text;
    el.appendChild(span);
    if (options.retry) {
      const btn = document.createElement('button');
      btn.type = 'button';
      btn.className = 'msg-retry';
      btn.textContent = 'Try again';
      btn.onclick = () => loadWeatherData();
      el.appendChild(btn);
    }
    el.hidden = false;
  }

  function clearMessage() {
    const el = $id('forecastMessage');
    if (!el) return;
    el.hidden = true;
    el.textContent = '';
  }

  function hasHourlyData() {
    return !!(weatherData && weatherData.data_1h && weatherData.data_1h.time && weatherData.data_1h.time.length);
  }

  function hasDailyData() {
    return !!(weatherData && weatherData.data_day && weatherData.data_day.time && weatherData.data_day.time.length);
  }

  function formatAge(hours) {
    if (hours < 1) return 'under an hour';
    if (hours < 48) return `${Math.round(hours)} hours`;
    return `${Math.round(hours / 24)} days`;
  }

  // Shows the single most important notice for the current state.
  function updateNotice() {
    const n = noticeState;
    if (n.error) {
      showMessage('error', n.error.text, { retry: n.error.retry });
      return;
    }
    if (weatherData) {
      if (currentMode === 'hour' && !hasHourlyData()) {
        showMessage('warn', "Hourly data isn't included in the latest forecast. Try the 7 Day view.");
        return;
      }
      if (currentMode === 'day' && !hasDailyData()) {
        showMessage('warn', "Daily data isn't included in the latest forecast. Try the Daily view.");
        return;
      }
    }
    if (n.refreshFailed) {
      showMessage('warn', `Couldn't refresh the forecast. Showing the last forecast received${n.issuedText ? ' (issued ' + n.issuedText + ')' : ''}.`);
      return;
    }
    if (n.stale) {
      showMessage('warn', `This forecast was issued ${formatAge(n.stale.ageHours)} ago and may be out of date.`);
      return;
    }
    clearMessage();
  }

  function setStatus(kind, text) {
    const badge = $id('statusBadge');
    const statusText = $id('statusText');
    const dot = $id('statusDot');
    const colors = { live: '#24a148', updating: '#d97706', stale: '#d97706', error: '#da1e28', demo: '#0f62fe' };
    if (statusText) statusText.textContent = text;
    if (badge) badge.className = `status-badge micro ${kind}`;
    if (dot) dot.style.backgroundColor = colors[kind] || '#24a148';
  }

  function formatIssued(date) {
    const opts = { day: '2-digit', month: 'short', year: 'numeric', hour: '2-digit', minute: '2-digit', hour12: false };
    try {
      return date.toLocaleString([], Object.assign({}, opts, { timeZone: SITE_TZ, timeZoneName: 'short' }));
    } catch (e) {
      return date.toLocaleString([], opts);
    }
  }

  function getModelRunDate(json) {
    const raw = (json && json.metadata && (json.metadata.modelrun_updatetime_utc || json.metadata.modelrun_utc))
      || (json && json.modelrun_updatetime_utc);
    return raw ? parseUtcTimestamp(raw) : null;
  }

  function updateFooter() {
    const el = $id('footerTimestamp');
    if (!el) return;
    const d = weatherData ? getModelRunDate(weatherData) : null;
    el.textContent = d ? `Issued: ${formatIssued(d)}` : (weatherData ? 'Issued: unknown' : (loadState === 'error' ? 'No forecast available' : 'Updated: Loading...'));
  }

  // Tells the viewer when live club hours could not be loaded and the standard
  // schedule is being shown instead.
  function updateClubNote() {
    const note = $id('footerClubNote');
    if (!note) return;
    let usingDefaults = false;
    if (weatherData && !DEMO_MODE && loadState === 'ready') {
      const dates = new Set();
      if (weatherData.data_day && weatherData.data_day.time) weatherData.data_day.time.forEach((t) => dates.add(t.substring(0, 10)));
      if (weatherData.data_1h && weatherData.data_1h.time) weatherData.data_1h.time.forEach((t) => dates.add(t.substring(0, 10)));
      dates.forEach((d) => { if (!clubStatusCache[d]) usingDefaults = true; });
    }
    note.hidden = !usingDefaults;
    if (usingDefaults) {
      note.textContent = 'Club hours: standard schedule';
      note.title = "Live club hours couldn't be loaded, so the standard schedule is shown: open 13:00 on weekdays and 10:00 on weekends, docking at sunset.";
    }
  }

  // ===========================================================================
  // Skeleton (loading placeholder)
  // ===========================================================================
  function renderTableSkeleton() {
    const thead = document.getElementById('tableHead');
    const tbody = document.getElementById('tableBody');
    const barsContainer = document.getElementById('timelineBars');
    const labelsContainer = document.getElementById('timelineLabels');
    if (!thead || !tbody) return;
    const panel = document.getElementById('forecastPanel');
    if (panel) panel.setAttribute('aria-busy', 'true');

    if (currentMode === 'hour') {
      const colCount = 72; // Representative 3-day window for immediate layout stabilization
      let groupThs = '';
      for (let d = 0; d < 3; d++) {
        groupThs += `<th class="day-group-header" colspan="24"><div class="skeleton-shimmer skeleton-pill wide" style="height:12px; width:65px;"></div></th>`;
      }
      let hourThs = '';
      for (let c = 0; c < colCount; c++) {
        hourThs += `<th><div class="skeleton-shimmer skeleton-pill" style="height:9px; width:14px;"></div></th>`;
      }

      thead.innerHTML = `
        <tr><th></th>${groupThs}</tr>
        <tr class="row-hour-header"><th>Hour</th>${hourThs}</tr>
      `;

      // 1. Wind Row
      let windTds = '';
      for (let c = 0; c < colCount; c++) {
        const mockBarHeight = Math.round(35 + ((c * 7) % 55));
        windTds += `
          <td class="wind-histo-cell">
            <div class="wind-histo-container">
              <div class="skeleton-shimmer skeleton-pill" style="height:9px; width:14px; margin-bottom:4px;"></div>
              <div class="wind-histo-bar" style="height:${mockBarHeight}px; border-top:none;">
                <div class="skeleton-shimmer skeleton-bar-fill" style="height:100%; opacity:0.65;"></div>
              </div>
            </div>
          </td>`;
      }

      // 2. Gust Row
      let gustTds = '';
      for (let c = 0; c < colCount; c++) {
        gustTds += `<td><div class="skeleton-shimmer skeleton-pill" style="height:10px; width:15px;"></div></td>`;
      }

      // 3. Sky Row
      let skyTds = '';
      for (let c = 0; c < colCount; c++) {
        skyTds += `<td><div class="skeleton-shimmer skeleton-circle"></div></td>`;
      }

      // 4. Temp Row
      let tempTds = '';
      for (let c = 0; c < colCount; c++) {
        tempTds += `<td><div class="skeleton-shimmer skeleton-pill" style="height:10px; width:16px;"></div></td>`;
      }

      // 5. Rain % Row
      let popTds = '';
      for (let c = 0; c < colCount; c++) {
        popTds += `<td><div class="skeleton-shimmer skeleton-pill" style="height:9px; width:12px;"></div></td>`;
      }

      tbody.innerHTML = `
        <tr><td>Wind<span class="unit-label">(kts)</span></td>${windTds}</tr>
        <tr><td>Gust</td>${gustTds}</tr>
        <tr><td>Sky</td>${skyTds}</tr>
        <tr class="row-temp"><td>°F</td>${tempTds}</tr>
        <tr><td>Rain %</td>${popTds}</tr>
      `;
    } else {
      // 7-Day Skeleton
      let dayThs = '';
      for (let d = 0; d < 7; d++) {
        dayThs += `<th>
          <div class="skeleton-shimmer skeleton-pill" style="height:11px; width:26px; margin-bottom:3px;"></div>
          <div class="skeleton-shimmer skeleton-pill" style="height:9px; width:22px;"></div>
        </th>`;
      }
      thead.innerHTML = `<tr><th></th>${dayThs}</tr>`;

      const makeRow = (label, isDouble = false, isCircle = false) => {
        let cells = '';
        for (let d = 0; d < 7; d++) {
          if (isCircle) {
            cells += `<td><div class="skeleton-shimmer skeleton-circle" style="width:20px; height:20px;"></div></td>`;
          } else if (isDouble) {
            cells += `<td>
              <div class="skeleton-shimmer skeleton-pill" style="height:10px; width:18px; margin-bottom:3px;"></div>
              <div class="skeleton-shimmer skeleton-pill" style="height:10px; width:18px;"></div>
            </td>`;
          } else {
            cells += `<td><div class="skeleton-shimmer skeleton-pill" style="height:11px; width:22px;"></div></td>`;
          }
        }
        return `<tr><td>${label}</td>${cells}</tr>`;
      };

      tbody.innerHTML = `
        ${makeRow('Wind<span class="unit-label">(kts)</span>')}
        ${makeRow('Gust')}
        ${makeRow('Sky', false, true)}
        ${makeRow('Temp<span class="unit-label">in °F</span>', true)}
        ${makeRow('Sunrise<br/>Sunset', true)}
        ${makeRow('Rain %')}
      `;
    }

    // Timeline Overview Skeleton
    if (barsContainer && labelsContainer && barsContainer.children.length === 0) {
      barsContainer.innerHTML = '';
      labelsContainer.innerHTML = '';
      for (let b = 0; b < 64; b++) {
        const bar = document.createElement('div');
        bar.className = 'timeline-bar';
        const h = Math.round(18 + ((b * 9) % 55));
        bar.innerHTML = `<div class="skeleton-shimmer" style="height:${h}%; width:90%; margin:0 auto; border-radius:2px 2px 0 0; opacity:0.6;"></div>`;
        barsContainer.appendChild(bar);
      }
      for (let l = 0; l < 7; l++) {
        const lbl = document.createElement('div');
        lbl.className = 'timeline-day-label';
        lbl.style.flex = '1';
        lbl.innerHTML = `<div class="skeleton-shimmer skeleton-pill" style="height:8px; width:34px; margin-top:5px;"></div>`;
        labelsContainer.appendChild(lbl);
      }
    }
  }

  // ===========================================================================
  // Units, colors, icons
  // ===========================================================================
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

  // One table drives both the CSS class and the hex color for each wind band.
  const WIND_BANDS = [
    { max: 3,        cls: 'wind-calm',      hex: '#eef8fc' },
    { max: 5,        cls: 'wind-light',     hex: '#dcf4fb' },
    { max: 7,        cls: 'wind-mod',       hex: '#b4e7fa' },
    { max: 9,        cls: 'wind-breeze',    hex: '#abf0d4' },
    { max: 14,       cls: 'wind-green',     hex: '#80ff80' },
    { max: 16,       cls: 'wind-yellow',    hex: '#ffea29' },
    { max: 17,       cls: 'wind-lt-orange', hex: '#ffba42' },
    { max: 19,       cls: 'wind-dk-orange', hex: '#ff8c1a' },
    { max: 23,       cls: 'wind-red',       hex: '#e52222' },
    { max: 29,       cls: 'wind-dk-red',    hex: '#b70c18' },
    { max: Infinity, cls: 'wind-purple',    hex: '#9f135b' }
  ];

  function getWindBand(speedKnots) {
    if (!speedKnots || speedKnots <= 0) return null;
    return WIND_BANDS.find((band) => speedKnots <= band.max) || null;
  }

  function getWindClass(speedKnots) {
    const band = getWindBand(speedKnots);
    return band ? band.cls : '';
  }

  function getWindHexColor(speedKnots) {
    const band = getWindBand(speedKnots);
    return band ? band.hex : '#f4f4f4';
  }

  function relativeLuminance(r, g, b) {
    const f = (c) => { c /= 255; return c <= 0.03928 ? c / 12.92 : Math.pow((c + 0.055) / 1.055, 2.4); };
    return 0.2126 * f(r) + 0.7152 * f(g) + 0.0722 * f(b);
  }

  function contrastRatio(l1, l2) {
    const hi = Math.max(l1, l2);
    const lo = Math.min(l1, l2);
    return (hi + 0.05) / (lo + 0.05);
  }

  // Temperatures are drawn as colored text, so each color is nudged (toward black
  // on the light theme, toward white on the dark theme) until it reaches a 4.5:1
  // contrast ratio against the card background.
  function ensureTextContrast(r, g, b) {
    const dark = isDarkTheme();
    const bgLum = dark ? 0.008 : 1; // #161616 vs #ffffff
    const toward = dark ? 255 : 0;
    let t = 0;
    let R = r, G = g, B = b;
    while (contrastRatio(relativeLuminance(R, G, B), bgLum) < 4.5 && t < 1) {
      t = Math.min(1, t + 0.04);
      R = Math.round(r + (toward - r) * t);
      G = Math.round(g + (toward - g) * t);
      B = Math.round(b + (toward - b) * t);
    }
    return `rgb(${R}, ${G}, ${B})`;
  }

  function getTemperatureColor(valF) {
    if (valF === null || valF === undefined || isNaN(valF)) {
      return { bg: isDarkTheme() ? '#c6c6c6' : '#525252' };
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

    if (valF <= first.t) return { bg: ensureTextContrast(first.r, first.g, first.b) };
    if (valF >= last.t) return { bg: ensureTextContrast(last.r, last.g, last.b) };

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
    return { bg: ensureTextContrast(r, g, b) };
  }

  function createWindArrowSvg(degrees) {
    if (degrees === null || degrees === undefined || isNaN(degrees)) return '';
    const reversedDeg = (Math.round(degrees) + 180) % 360;
    return `
      <div class="wind-arrow" style="transform: rotate(${reversedDeg}deg);" aria-hidden="true">
        <svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round">
          <line x1="12" y1="19" x2="12" y2="5"></line>
          <polyline points="5 12 12 5 19 12"></polyline>
        </svg>
      </div>
      <span class="wind-deg">${Math.round(degrees)}</span>
    `;
  }

  // Icons are decorative: the cell around them carries the text alternative.
  function getPictocodeIconRaw(code, isDaily = false) {
    const c = Number(code) || 1;
    // Clear / Sunny (Daily: 1, 2; Hourly: 1, 2, 3)
    if (isDaily ? (c === 1 || c === 2) : (c === 1 || c === 2 || c === 3)) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none" stroke="#e57e00" stroke-width="2" stroke-linecap="round"><circle cx="12" cy="12" r="4"/><path d="M12 2v2M12 20v2M4.93 4.93l1.41 1.41M17.66 17.66l1.41 1.41M2 12h2M20 12h2M6.34 17.66l-1.41 1.41M19.07 4.93l-1.41 1.41"/></svg>`;
    }

    // Fog / Mist / Haze (Daily: 5; Hourly: 13, 14, 15, 16, 17, 18)
    if (isDaily ? (c === 5) : (c >= 13 && c <= 18)) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none" stroke="#78909c" stroke-width="2" stroke-linecap="round"><line x1="4" y1="8" x2="20" y2="8"/><line x1="3" y1="12" x2="21" y2="12"/><line x1="5" y1="16" x2="19" y2="16"/></svg>`;
    }

    // Thunderstorms (Daily: 8; Hourly: 10, 11, 12, 27, 28, 30)
    if (isDaily ? (c === 8) : ((c >= 10 && c <= 12) || c === 27 || c === 28 || c === 30)) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none">
        <path d="M6 14h11a3.5 3.5 0 0 0 .5-6.96 4.5 4.5 0 0 0-8.2-2.2A4 4 0 0 0 6 14z" fill="#cfd8dc" stroke="#546e7a" stroke-width="1.4" stroke-linejoin="round"/>
        <polygon points="12,13 9.5,17.5 12.5,17.5 11,22 15.5,16.5 12.5,16.5" fill="#f59e0b" stroke="#d97706" stroke-width="0.8" stroke-linejoin="round"/>
      </svg>`;
    }

    // Snow / Sleet (Daily: 9, 10, 11, 13, 15, 17; Hourly: 24, 26, 29, 32, 34, 35)
    if (isDaily ? (c === 9 || c === 10 || c === 11 || c === 13 || c === 15 || c === 17) : (c === 24 || c === 26 || c === 29 || c === 32 || c === 34 || c === 35)) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none">
        <path d="M6 14h11a3.5 3.5 0 0 0 .5-6.96 4.5 4.5 0 0 0-8.2-2.2A4 4 0 0 0 6 14z" fill="#eceff1" stroke="#546e7a" stroke-width="1.4" stroke-linejoin="round"/>
        <line x1="8" y1="18" x2="8" y2="20" stroke="#90caf9" stroke-width="2" stroke-linecap="round"/>
        <line x1="12" y1="18" x2="12" y2="20" stroke="#90caf9" stroke-width="2" stroke-linecap="round"/>
        <line x1="16" y1="18" x2="16" y2="20" stroke="#90caf9" stroke-width="2" stroke-linecap="round"/>
      </svg>`;
    }

    // Rain / Showers (Daily: 6, 7, 12, 14, 16; Hourly: 23, 25, 31, 33)
    if (isDaily ? (c === 6 || c === 7 || c === 12 || c === 14 || c === 16) : (c === 23 || c === 25 || c === 31 || c === 33)) {
      return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none">
        <path d="M6 14h11a3.5 3.5 0 0 0 .5-6.96 4.5 4.5 0 0 0-8.2-2.2A4 4 0 0 0 6 14z" fill="#eceff1" stroke="#546e7a" stroke-width="1.4" stroke-linejoin="round"/>
        <line x1="8" y1="17.5" x2="6.8" y2="21" stroke="#0284c7" stroke-width="1.8" stroke-linecap="round"/>
        <line x1="12" y1="17.5" x2="10.8" y2="21" stroke="#0284c7" stroke-width="1.8" stroke-linecap="round"/>
        <line x1="16" y1="17.5" x2="14.8" y2="21" stroke="#0284c7" stroke-width="1.8" stroke-linecap="round"/>
      </svg>`;
    }

    // Overcast / Cloudy / Partly Cloudy (Clean cloud with NO rain drops)
    return `<svg viewBox="0 0 24 24" width="20" height="20" fill="none">
      <path d="M6.5 18h11a4 4 0 0 0 .5-7.97 5 5 0 0 0-9.8-1.53A4 4 0 0 0 6.5 18z" fill="#eceff1" stroke="#607d8b" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
    </svg>`;
  }

  function getPictocodeIcon(code, isDaily = false) {
    return getPictocodeIconRaw(code, isDaily).replace('<svg ', '<svg aria-hidden="true" focusable="false" ');
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

    return hourlyMap[c] || `Sky condition ${c}`;
  }

  // ===========================================================================
  // Sun times and club schedule
  // ===========================================================================
  // US Pacific daylight time: second Sunday in March through the first Sunday in
  // November. (Computed per year; sunrise/sunset are never within the 2am switch.)
  function nthSundayOfMonth(year, monthIdx, n) {
    const firstDow = new Date(Date.UTC(year, monthIdx, 1)).getUTCDay();
    return 1 + ((7 - firstDow) % 7) + (n - 1) * 7;
  }

  function isPacificDst(year, monthIdx, day) {
    if (monthIdx < 2 || monthIdx > 10) return false;
    if (monthIdx > 2 && monthIdx < 10) return true;
    if (monthIdx === 2) return day >= nthSundayOfMonth(year, 2, 2);
    return day < nthSundayOfMonth(year, 10, 1);
  }

  // Approximate sunrise and sunset (computed, not from a data feed) as "HH:MM".
  function getSunTimes(dateStr) {
    try {
      const parts = dateStr.split('-');
      const year = parseInt(parts[0], 10);
      const month = parseInt(parts[1], 10) - 1;
      const day = parseInt(parts[2], 10);
      if (isNaN(year) || isNaN(month) || isNaN(day)) throw new Error('Invalid date');
      const date = new Date(Date.UTC(year, month, day, 12, 0, 0));

      const lat = SITE_LAT;
      const lon = SITE_LON;
      const dayOfYear = Math.floor((date - new Date(Date.UTC(year, 0, 0))) / 86400000);
      const b = (2 * Math.PI / 365) * (dayOfYear - 81);
      const eot = 9.87 * Math.sin(2 * b) - 7.53 * Math.cos(b) - 1.5 * Math.sin(b);
      const declination = 23.45 * Math.sin((2 * Math.PI / 365) * (dayOfYear - 81)) * (Math.PI / 180);

      const latRad = lat * (Math.PI / 180);
      const zenithRad = 90.833 * (Math.PI / 180);
      const cosH = (Math.cos(zenithRad) - Math.sin(latRad) * Math.sin(declination)) / (Math.cos(latRad) * Math.cos(declination));
      const hourAngleDeg = Math.acos(Math.max(-1, Math.min(1, cosH))) * (180 / Math.PI);

      const tzOffsetHours = isPacificDst(year, month, day) ? -7 : -8;

      const solarNoonUtcMinutes = 720 - (lon * 4) - eot;
      const halfDayMinutes = (hourAngleDeg / 15) * 60;

      const formatMinutes = (utcMinutes) => {
        let localMinutes = Math.round(utcMinutes + tzOffsetHours * 60);
        localMinutes = ((localMinutes % 1440) + 1440) % 1440;
        return `${pad2(Math.floor(localMinutes / 60))}:${pad2(localMinutes % 60)}`;
      };

      const sunriseStr = formatMinutes(solarNoonUtcMinutes - halfDayMinutes);
      const sunsetStr = formatMinutes(solarNoonUtcMinutes + halfDayMinutes);
      return {
        sunrise: sunriseStr,
        sunset: sunsetStr,
        sunriseHour: toHourFloat(sunriseStr),
        sunsetHour: toHourFloat(sunsetStr)
      };
    } catch (e) {
      return { sunrise: null, sunset: null, sunriseHour: null, sunsetHour: null };
    }
  }

  // Builds the schedule object used by every renderer. `intervals` are the open
  // windows in decimal hours (two when there is a midday closure); `events` are
  // the open/close markers drawn on the grid.
  function buildSchedule(o) {
    const openHour = toHourFloat(o.openTime);
    const dockHour = toHourFloat(o.dockTime);
    const midDayDockHour = toHourFloat(o.midDayDock);
    const midDayOpenHour = toHourFloat(o.midDayOpen);
    const hasHours = !o.isClosed && openHour !== null && dockHour !== null && dockHour > openHour;

    const intervals = [];
    const events = [];
    if (hasHours) {
      const hasBreak = midDayDockHour !== null && midDayOpenHour !== null
        && openHour < midDayDockHour && midDayDockHour < midDayOpenHour && midDayOpenHour < dockHour;
      events.push({ hour: openHour, type: 'open', label: `Open ${o.openTime}`, title: `Club Opens: ${o.openTime}` });
      if (hasBreak) {
        intervals.push([openHour, midDayDockHour], [midDayOpenHour, dockHour]);
        events.push({ hour: midDayDockHour, type: 'dock', label: `Closed ${o.midDayDock}\u2013${o.midDayOpen}`, title: `Midday closure: ${o.midDayDock}\u2013${o.midDayOpen}` });
        events.push({ hour: midDayOpenHour, type: 'open', label: null, title: `Club reopens: ${o.midDayOpen}` });
      } else {
        intervals.push([openHour, dockHour]);
      }
      events.push({ hour: dockHour, type: 'dock', label: `Dock ${o.dockTime}`, title: `Dock Time: ${o.dockTime}` });
    }

    return {
      source: o.source || 'default',
      isClosed: !!o.isClosed,
      hasHours,
      openTime: o.openTime,
      dockTime: o.dockTime,
      midDayDock: o.midDayDock || null,
      midDayOpen: o.midDayOpen || null,
      openHour,
      dockHour,
      sunriseTime: o.sunriseTime || null,
      sunsetTime: o.sunsetTime || null,
      sunriseHour: toHourFloat(o.sunriseTime),
      sunsetHour: toHourFloat(o.sunsetTime),
      intervals,
      events,
      signature: [!!o.isClosed, o.openTime, o.dockTime, o.midDayDock, o.midDayOpen, o.sunsetTime].join('|'),
      fetchedAt: Date.now()
    };
  }

  // Standard schedule, used when live club hours are not available.
  function getDefaultSchedule(dateStr) {
    if (defaultScheduleCache[dateStr]) return defaultScheduleCache[dateStr];
    const sun = getSunTimes(dateStr);
    const schedule = buildSchedule({
      source: 'default',
      isClosed: false,
      openTime: isWeekendDate(dateStr) ? '10:00' : '13:00',
      dockTime: sun.sunset,
      sunriseTime: sun.sunrise,
      sunsetTime: sun.sunset
    });
    defaultScheduleCache[dateStr] = schedule;
    return schedule;
  }

  function getClubSchedule(dateStr) {
    return clubStatusCache[dateStr] || getDefaultSchedule(dateStr);
  }

  // ===========================================================================
  // Forecast time helpers (all in site wall-clock time)
  // ===========================================================================
  // Index of the first forecast hour that is still "current" (up to 55 minutes
  // into the hour counts), or -1 when every hour is in the past.
  function findFirstCurrentIndex(times) {
    if (!times || !times.length) return -1;
    const threshold = getSiteWallMs() - (55 * 60 * 1000);
    for (let i = 0; i < times.length; i++) {
      const ms = wallStringToMs(times[i]);
      if (!isNaN(ms) && ms >= threshold) return i;
    }
    return -1;
  }

  function getCurrentHourStartIndex(times) {
    const idx = findFirstCurrentIndex(times);
    return idx === -1 ? 0 : idx;
  }

  // Hourly rows run for 7 days from "now", not from the start of the feed.
  function getHourlyEndIndex(times, startIdx) {
    return Math.min(times.length, startIdx + 168);
  }

  function getHourlyDaySpans(times, startIdx, numHours) {
    const daySpans = [];
    let currentDayStr = null;
    let currentSpan = 0;
    let currentFirstIdx = startIdx;

    for (let i = startIdx; i < numHours; i++) {
      const dayStr = times[i].substring(0, 10);
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
    return daySpans;
  }

  function isForecastExpired(json) {
    const times = json && json.data_1h && json.data_1h.time;
    if (times && times.length) return findFirstCurrentIndex(times) === -1;
    const days = json && json.data_day && json.data_day.time;
    if (days && days.length) {
      const today = wallMsToString(getSiteWallMs()).substring(0, 10);
      return days[days.length - 1].substring(0, 10) < today;
    }
    return false;
  }

  // ===========================================================================
  // Club hours (fetched, cached, never blocks rendering)
  // ===========================================================================
  async function fetchClubStatusForDate(dateStr) {
    const cached = clubStatusCache[dateStr];
    if (cached && (Date.now() - cached.fetchedAt) < CLUB_TTL_MS) return cached;

    // Optional host-provided prefetch: window.clubStatusCache['YYYYMMDD'] holding
    // { isClosed, openTime, dockTime, sunriseTime, sunsetTime, midDayDock, midDayOpen }.
    const cleanKey = dateStr.replace(/-/g, '');
    if (window.clubStatusCache && window.clubStatusCache[cleanKey]) {
      const injected = window.clubStatusCache[cleanKey];
      const sched = buildSchedule(Object.assign({}, injected, { source: 'club' }));
      if (sched.hasHours || sched.isClosed) {
        clubStatusCache[dateStr] = sched;
        clubVersion++;
        return sched;
      }
    }

    const failedAt = clubFailedAt[dateStr];
    if (failedAt && (Date.now() - failedAt) < CLUB_RETRY_AFTER_MS) return cached || null;

    const targetUrl = `https://www.cal-sailing.org/index.php?option=com_csctides&view=gettidedatalist&task=gettidedatalist&tmpl=component&output=json&tidedate=${dateStr}`;

    try {
      let rawText = null;
      try {
        const resp = await fetchTextWithTimeout(targetUrl);
        if (resp.ok) rawText = resp.text;
      } catch (directErr) {
        if (!USE_PUBLIC_CORS_PROXY) throw directErr;
        const proxyUrl = `https://api.allorigins.win/get?url=${encodeURIComponent(targetUrl)}`;
        const pResp = await fetchTextWithTimeout(proxyUrl);
        if (pResp.ok) rawText = JSON.parse(pResp.text).contents;
      }
      if (!rawText) throw new Error('No club data in response');

      const jsonString = rawText.replace(/<pre.*?>|<\/pre>/g, '');
      const clubData = JSON.parse(jsonString).data;
      if (!clubData) throw new Error('Club response has no data field');

      const parseTime = (timeStr) => {
        if (!timeStr || typeof timeStr !== 'string') return null;
        const s = timeStr.toLowerCase().trim();
        if (s === 'sunset') return 'sunset';
        if (s === 'noon') return '12:00';
        const hasPm = /pm/.test(s);
        const hasAm = /am/.test(s);
        const parts = s.replace(/am|pm/g, '').trim().split(':');
        let hours = parseInt(parts[0], 10);
        const minutes = parts.length > 1 ? parseInt(parts[1], 10) : 0;
        if (isNaN(hours) || isNaN(minutes) || minutes > 59) return null;
        if (hasPm && hours < 12) hours += 12;
        else if (hasAm && hours === 12) hours = 0;
        if (hours > 23) return null;
        return `${pad2(hours)}:${pad2(minutes)}`;
      };

      const isClosed = clubData.clubclosed === true || clubData.clubclosed === 'true';
      const sunsetParsed = parseTime(clubData.sunsettime);
      const openParsed = parseTime(clubData.opentime);
      const dockParsed = parseTime(clubData.docktime);

      let midDayDock = null;
      let midDayOpen = null;
      if (clubData.middayclosetext && clubData.middayclosetext !== 'null') {
        const times = String(clubData.middayclosetext).match(/(\d{1,2}:\d{2}\s*(am|pm))/gi);
        if (times && times.length >= 2) {
          midDayDock = parseTime(times[0]);
          midDayOpen = parseTime(times[1]);
        }
      }

      const sun = getSunTimes(dateStr);
      const sunsetStr = (sunsetParsed && sunsetParsed !== 'sunset') ? sunsetParsed : sun.sunset;
      const openStr = (openParsed && openParsed !== 'sunset') ? openParsed : (isWeekendDate(dateStr) ? '10:00' : '13:00');
      const dockStr = (!dockParsed || dockParsed === 'sunset') ? sunsetStr : dockParsed;

      const sched = buildSchedule({
        source: 'club',
        isClosed,
        openTime: openStr,
        dockTime: dockStr,
        sunriseTime: sun.sunrise,
        sunsetTime: sunsetStr,
        midDayDock,
        midDayOpen
      });

      if (!cached || cached.signature !== sched.signature) clubVersion++;
      clubStatusCache[dateStr] = sched;
      delete clubFailedAt[dateStr];
      return sched;
    } catch (e) {
      clubFailedAt[dateStr] = Date.now();
      console.warn(`Club hours unavailable for ${dateStr}:`, e && e.message ? e.message : e);
      return cached || null;
    }
  }

  async function preloadClubHours() {
    if (!weatherData || DEMO_MODE) return;
    const dates = new Set();
    if (weatherData.data_day && weatherData.data_day.time) weatherData.data_day.time.forEach((t) => dates.add(t.substring(0, 10)));
    if (weatherData.data_1h && weatherData.data_1h.time) weatherData.data_1h.time.forEach((t) => dates.add(t.substring(0, 10)));
    await Promise.all(Array.from(dates).map((d) => fetchClubStatusForDate(d)));
  }

  // ===========================================================================
  // Day/night + club-open shading
  // ===========================================================================
  function subtractIntervals(segments, cuts) {
    let out = segments;
    cuts.forEach(([cs, ce]) => {
      const next = [];
      out.forEach(([s, e]) => {
        if (ce <= s || cs >= e) { next.push([s, e]); return; }
        if (cs > s) next.push([s, cs]);
        if (ce < e) next.push([ce, e]);
      });
      out = next;
    });
    return out;
  }

  // Returns the shaded portions of one hour cell as fractions (0..1): night
  // always wins over "club open".
  function getHourSegments(hourNum, sched) {
    if (!sched) return [];
    const clip = (s, e) => {
      const a = Math.max(s, hourNum);
      const b = Math.min(e, hourNum + 1);
      return b > a ? [a - hourNum, b - hourNum] : null;
    };
    const nightRanges = [];
    if (sched.sunriseHour !== null && sched.sunriseHour !== undefined) nightRanges.push([-Infinity, sched.sunriseHour]);
    if (sched.sunsetHour !== null && sched.sunsetHour !== undefined) nightRanges.push([sched.sunsetHour, Infinity]);
    const night = nightRanges.map(([s, e]) => clip(s, e)).filter(Boolean);
    const open = sched.hasHours ? subtractIntervals(sched.intervals.map(([s, e]) => clip(s, e)).filter(Boolean), night) : [];
    return night.map(([from, to]) => ({ from, to, type: 'night' }))
      .concat(open.map(([from, to]) => ({ from, to, type: 'open' })))
      .sort((a, b) => a.from - b.from);
  }

  function buildHourBackground(segments) {
    if (!segments.length) return '';
    const colorOf = (type) => (type === 'night' ? 'var(--night-hour-bg)' : 'var(--club-open-hour-bg)');
    const pct = (v) => Math.round(v * 100);
    if (segments.length === 1 && segments[0].from <= 0.0001 && segments[0].to >= 0.9999) {
      return `background-color: ${colorOf(segments[0].type)};`;
    }
    const stops = [];
    let cursor = 0;
    segments.forEach((sg) => {
      if (sg.from > cursor + 0.0001) stops.push(`transparent ${pct(cursor)}%`, `transparent ${pct(sg.from)}%`);
      stops.push(`${colorOf(sg.type)} ${pct(sg.from)}%`, `${colorOf(sg.type)} ${pct(sg.to)}%`);
      cursor = sg.to;
    });
    if (cursor < 0.9999) stops.push(`transparent ${pct(cursor)}%`, 'transparent 100%');
    return `background: linear-gradient(to right, ${stops.join(', ')});`;
  }

  function getHourHeaderBackground(hourNum, sched) {
    return buildHourBackground(getHourSegments(hourNum, sched));
  }

  // ===========================================================================
  // Data accessors (no invented values: estimates are flagged, gaps stay empty)
  // ===========================================================================
  function getHourlyGust(data, units, i) {
    const raw = data.gust ? data.gust[i] : null;
    if (raw !== null && raw !== undefined) {
      const kt = toKnots(raw, units.windspeed);
      if (kt !== null) return { kt, est: false };
    }
    const base = data.windspeed ? toKnots(data.windspeed[i], units.windspeed) : null;
    if (base !== null && base !== undefined) return { kt: Math.round(base * GUST_ESTIMATE_FACTOR), est: true };
    return { kt: null, est: false };
  }

  function getDailyGust(data, units, i) {
    if (data.gust_max && data.gust_max[i] !== undefined && data.gust_max[i] !== null) {
      const kt = toKnots(data.gust_max[i], units.windspeed);
      if (kt !== null) return { kt, est: false };
    }
    const hourly = weatherData && weatherData.data_1h;
    if (hourly && hourly.gust && hourly.time) {
      const dayStr = data.time[i];
      let max = null;
      for (let h = 0; h < hourly.time.length; h++) {
        if (hourly.time[h].startsWith(dayStr) && hourly.gust[h] !== null && hourly.gust[h] !== undefined) {
          if (max === null || hourly.gust[h] > max) max = hourly.gust[h];
        }
      }
      if (max !== null) return { kt: toKnots(max, units.windspeed), est: false };
    }
    const maxKt = data.windspeed_max ? toKnots(data.windspeed_max[i], units.windspeed) : null;
    if (maxKt !== null && maxKt !== undefined) return { kt: Math.round(maxKt * GUST_ESTIMATE_FACTOR), est: true };
    return { kt: null, est: false };
  }

  function gustCellHtml(gust) {
    if (gust.kt === null) return '<span class="no-data" title="No gust data">\u2013</span>';
    if (gust.est) return `<span class="est-value" style="font-size:0.75rem;" title="Estimated from wind speed (no gust data in the forecast)">~${gust.kt}</span>`;
    return `<span style="font-weight:400; font-size:0.75rem;">${gust.kt}</span>`;
  }

  // Hourly chance of rain. When the feed has no hourly value, the matching
  // day's value is used and marked as an estimate.
  function getHourlyPop(data, i) {
    if (data.precipitation_probability && data.precipitation_probability[i] !== undefined && data.precipitation_probability[i] !== null) {
      return { pop: data.precipitation_probability[i], est: false };
    }
    const day = weatherData && weatherData.data_day;
    if (day && day.precipitation_probability && day.time) {
      const dayIdx = day.time.findIndex((t) => t.substring(0, 10) === data.time[i].substring(0, 10));
      if (dayIdx !== -1 && day.precipitation_probability[dayIdx] !== undefined && day.precipitation_probability[dayIdx] !== null) {
        return { pop: day.precipitation_probability[dayIdx], est: true };
      }
    }
    return { pop: null, est: false };
  }

  function popCellHtml(p) {
    if (p.pop === null) return '<span class="no-data" title="No data">\u2013</span>';
    if (!(p.pop > 0)) return '-';
    const text = `${Math.round(p.pop)}%`;
    return p.est ? `<span class="est-value" title="Daily chance (no hourly value in the forecast)">~${text}</span>` : text;
  }

  function hasPictocode(arr, i) {
    return !!arr && arr[i] !== undefined && arr[i] !== null && !isNaN(Number(arr[i]));
  }

  function skyCellHtml(code, isDaily, extraStyle) {
    const desc = getPictocodeDescription(code, isDaily);
    return `<div class="weather-icon-cell" role="img" aria-label="${desc}" title="${desc}"${extraStyle ? ` style="${extraStyle}"` : ''}>${getPictocodeIcon(code, isDaily)}</div>`;
  }

  // ===========================================================================
  // Table renderers
  // ===========================================================================
  function renderHourlyTable(thead, tbody) {
    const data = weatherData.data_1h;
    const units = weatherData.units || {};
    if (!data || !data.time || !data.time.length) return;

    const startIdx = getCurrentHourStartIndex(data.time);
    const numHours = getHourlyEndIndex(data.time, startIdx);
    const pct = (v) => Math.round(v * 100);
    thead.innerHTML = '';
    tbody.innerHTML = '';

    const daySpans = getHourlyDaySpans(data.time, startIdx, numHours);

    // Group Header Row
    const groupHeaderRow = document.createElement('tr');
    groupHeaderRow.innerHTML = `<th></th>`;
    daySpans.forEach((ds) => {
      const th = document.createElement('th');
      th.className = 'day-group-header';
      th.colSpan = ds.span;
      const formatted = formatDayLabel(ds.dayStr, { weekday: 'short', day: 'numeric', month: 'short' });
      const sched = getClubSchedule(ds.dayStr);

      const btn = document.createElement('button');
      btn.type = 'button';
      btn.className = 'th-btn';
      btn.textContent = formatted;
      btn.title = sched.isClosed ? `${formatted}: club closed. Click to jump to this day` : 'Click to jump to this day';
      btn.setAttribute('aria-label', `Jump to ${formatted}${sched.isClosed ? ' (club closed)' : ''}`);
      btn.onclick = () => jumpToTimelineDay(0, ds.firstHour, true, false);
      if (sched.isClosed && ds.span >= 5) {
        const tag = document.createElement('span');
        tag.className = 'day-closed-tag';
        tag.textContent = 'Closed';
        btn.appendChild(tag);
      }
      th.appendChild(btn);
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
      th.dataset.time = data.time[i];
      const timeStr = data.time[i];
      const hourNum = parseInt(timeStr.substring(11, 13), 10) || 0;
      const dayStr = timeStr.substring(0, 10);
      const sched = getClubSchedule(dayStr);

      const bgStyle = getHourHeaderBackground(hourNum, sched);
      if (bgStyle) {
        th.style.cssText = bgStyle;
      }

      let headerLinesHtml = '';
      sched.events.forEach((ev) => {
        if (Math.floor(ev.hour) === hourNum) {
          headerLinesHtml += `<div class="wind-sched-line line-${ev.type}" style="left: ${pct(ev.hour - hourNum)}%; top: 0; bottom: 0;"></div>`;
        }
      });

      th.innerHTML = `${headerLinesHtml}<span class="hour-time">${pad2(hourNum)}</span>`;
      hourHeaderRow.appendChild(th);
    }
    thead.appendChild(hourHeaderRow);

    // 1. Wind Row
    const windRow = document.createElement('tr');
    windRow.innerHTML = `<td>Wind<span class="unit-label">(kts)</span></td>`;
    for (let i = startIdx; i < numHours; i++) {
      const spdKt = toKnots(data.windspeed ? data.windspeed[i] : null, units.windspeed);
      const dirDeg = (data.winddirection && data.winddirection[i] !== undefined && data.winddirection[i] !== null) ? data.winddirection[i] : null;
      const td = document.createElement('td');
      td.className = 'wind-histo-cell';

      const barHeight = Math.max(38, Math.min(110, Math.round(35 + ((spdKt || 0) / 24) * 73)));
      const windClass = getWindClass(spdKt);

      const timeStr = data.time[i];
      const dayStr = timeStr.substring(0, 10);
      const hourNum = parseInt(timeStr.substring(11, 13), 10) || 0;
      const sched = getClubSchedule(dayStr);

      let shadingHtml = '';
      getHourSegments(hourNum, sched).forEach((sg) => {
        const cls = sg.type === 'night' ? 'wind-night-fill' : 'wind-sched-fill';
        shadingHtml += `<div class="${cls}" style="left: ${pct(sg.from)}%; width: ${pct(sg.to) - pct(sg.from)}%; bottom: ${barHeight}px;"></div>`;
      });

      let markerHtml = '';
      sched.events.forEach((ev) => {
        if (Math.floor(ev.hour) !== hourNum) return;
        const p = pct(ev.hour - hourNum);
        markerHtml += `<div class="wind-sched-line line-${ev.type}" style="left: ${p}%; bottom: ${barHeight}px;"></div>`;
        if (ev.label) {
          markerHtml += `
            <div class="wind-sched-marker marker-${ev.type}" style="left: ${p}%;">
              <div class="wind-club-flag flag-${ev.type}" title="${ev.title}">${ev.label}</div>
            </div>
          `;
        }
      });

      td.innerHTML = `
        ${shadingHtml}
        ${markerHtml}
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
      const gust = getHourlyGust(data, units, i);
      const td = document.createElement('td');
      td.className = getWindClass(gust.kt);
      td.innerHTML = gustCellHtml(gust);
      gustRow.appendChild(td);
    }
    tbody.appendChild(gustRow);

    // 3. Sky Row
    const skyRow = document.createElement('tr');
    skyRow.innerHTML = `<td>Sky</td>`;
    for (let i = startIdx; i < numHours; i++) {
      const td = document.createElement('td');
      if (hasPictocode(data.pictocode, i)) {
        const code = data.pictocode[i];
        td.title = getPictocodeDescription(code, false);
        td.innerHTML = skyCellHtml(code, false);
      } else {
        td.innerHTML = '<span class="no-data" title="Sky conditions unavailable">\u2013</span>';
      }
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
      td.innerHTML = popCellHtml(getHourlyPop(data, i));
      popRow.appendChild(td);
    }
    tbody.appendChild(popRow);

    syncTimelineOnTableScroll();
  }

  function render7DayTable(thead, tbody) {
    const data = weatherData.data_day;
    const units = weatherData.units || {};
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
      const dayName = formatDayLabel(data.time[i].substring(0, 10), { weekday: 'short' });
      const dateStr = formatDayLabel(data.time[i].substring(0, 10), { day: '2-digit', month: 'short' });
      const sched = getClubSchedule(data.time[i].substring(0, 10));
      const btn = document.createElement('button');
      btn.type = 'button';
      btn.className = 'th-btn';
      btn.setAttribute('aria-label', `Show hourly forecast for ${dayName} ${dateStr}${sched.isClosed ? ' (club closed)' : ''}`);
      btn.innerHTML = `
        <span class="day-name">${dayName}</span>
        <span class="day-date">${dateStr}</span>
        ${sched.isClosed ? '<span class="day-closed-tag">Closed</span>' : ''}
      `;
      btn.onclick = () => jumpToTimelineDay(i, null, true, false);
      th.appendChild(btn);
      headerRow.appendChild(th);
    }
    thead.appendChild(headerRow);

    // 1. Wind (kts) Row
    const windRow = document.createElement('tr');
    windRow.innerHTML = `<td>Wind<span class="unit-label">(kts)</span></td>`;
    for (let i = 0; i < numDays; i++) {
      const minKt = toKnots(data.windspeed_min ? data.windspeed_min[i] : null, units.windspeed);
      const maxKt = toKnots(data.windspeed_max ? data.windspeed_max[i] : null, units.windspeed);
      const dirDeg = (data.winddirection && data.winddirection[i] !== undefined && data.winddirection[i] !== null) ? data.winddirection[i] : null;
      const td = document.createElement('td');
      const maxVal = maxKt !== null ? maxKt : 0;
      td.className = getWindClass(maxVal);

      const spdText = (minKt !== null && maxKt !== null)
        ? ((minKt === maxKt) ? `${minKt}` : `${minKt}-${maxKt}`)
        : (maxKt !== null ? `${maxKt}` : '-');
      td.innerHTML = `
        <div style="font-size:0.75rem; font-weight:400; white-space:nowrap;">${spdText}</div>
        ${createWindArrowSvg(dirDeg)}
      `;
      windRow.appendChild(td);
    }
    tbody.appendChild(windRow);

    // 2. Gust Row
    const gustRow = document.createElement('tr');
    gustRow.innerHTML = `<td>Gust</td>`;
    for (let i = 0; i < numDays; i++) {
      const gust = getDailyGust(data, units, i);
      const td = document.createElement('td');
      td.className = getWindClass(gust.kt);
      td.innerHTML = gustCellHtml(gust);
      gustRow.appendChild(td);
    }
    tbody.appendChild(gustRow);

    // 3. Sky Row
    const outlookRow = document.createElement('tr');
    outlookRow.innerHTML = `<td>Sky</td>`;
    for (let i = 0; i < numDays; i++) {
      const td = document.createElement('td');
      if (hasPictocode(data.pictocode, i)) {
        const code = data.pictocode[i];
        td.title = getPictocodeDescription(code, true);
        td.innerHTML = skyCellHtml(code, true, 'width:22px; height:22px; margin:0 auto; cursor:help;');
      } else {
        td.innerHTML = '<span class="no-data" title="Sky conditions unavailable">\u2013</span>';
      }
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

    // 5. Sunrise & Sunset Row (same sunset the Daily view shades with)
    const sunRow = document.createElement('tr');
    sunRow.innerHTML = `<td title="Computed for the club's location (approximate)">Sunrise<br/>Sunset</td>`;
    for (let i = 0; i < numDays; i++) {
      const sched = getClubSchedule(data.time[i].substring(0, 10));
      const td = document.createElement('td');
      td.innerHTML = `<span style="font-size:0.62rem; line-height:1.2; display:block;">${sched.sunriseTime || '--:--'}<br/>${sched.sunsetTime || '--:--'}</span>`;
      sunRow.appendChild(td);
    }
    tbody.appendChild(sunRow);

    // 6. Rain % Row
    const popRow = document.createElement('tr');
    popRow.innerHTML = `<td>Rain %</td>`;
    for (let i = 0; i < numDays; i++) {
      const td = document.createElement('td');
      const raw = data.precipitation_probability ? data.precipitation_probability[i] : null;
      td.innerHTML = popCellHtml({ pop: (raw === undefined ? null : raw), est: false });
      popRow.appendChild(td);
    }
    tbody.appendChild(popRow);
  }

  // ===========================================================================
  // 7-day gust overview / scrubber
  // ===========================================================================
  function renderWindOverview() {
    const barsContainer = $id('timelineBars');
    const labelsContainer = $id('timelineLabels');
    const peakBadge = $id('overviewPeakBadge');
    if (!barsContainer || !labelsContainer || !weatherData) return;

    barsContainer.innerHTML = '';
    labelsContainer.innerHTML = '';

    const hourly = weatherData.data_1h;
    const units = weatherData.units || {};
    if (!hourly || !hourly.time || !hourly.time.length) {
      if (peakBadge) peakBadge.textContent = 'Peak: -- kts';
      return;
    }

    const startIdx = getCurrentHourStartIndex(hourly.time);
    const totalHours = getHourlyEndIndex(hourly.time, startIdx);
    const daySpans = getHourlyDaySpans(hourly.time, startIdx, totalHours);

    daySpans.forEach((ds) => {
      const lbl = document.createElement('div');
      lbl.className = 'timeline-day-label';
      lbl.style.flex = `${ds.span}`;
      lbl.textContent = formatDayLabel(ds.dayStr, { weekday: 'short', day: 'numeric' });
      lbl.title = `Jump to ${ds.dayStr}`;
      labelsContainer.appendChild(lbl);
    });

    const gusts = [];
    for (let h = startIdx; h < totalHours; h++) {
      const g = getHourlyGust(hourly, units, h);
      gusts.push({ kt: g.kt || 0, est: g.est });
    }

    let peakGust = 10;
    let peakEst = false;
    gusts.forEach((g) => { if (g.kt > peakGust) { peakGust = g.kt; peakEst = g.est; } });
    if (peakBadge) peakBadge.textContent = `Peak: ${peakEst ? '~' : ''}${peakGust} kts`;

    for (let h = startIdx; h < totalHours; h++) {
      const g = gusts[h - startIdx];
      const bar = document.createElement('div');
      bar.className = 'timeline-bar';
      const heightPct = Math.max(12, Math.round((g.kt / (peakGust * 1.1)) * 100));
      bar.style.height = `${heightPct}%`;
      bar.style.backgroundColor = getWindHexColor(g.kt);
      bar.title = `${hourly.time[h].replace('T', ' ')}: Gust ${g.est ? '~' : ''}${g.kt} kts${g.est ? ' (estimated)' : ''}`;
      barsContainer.appendChild(bar);
    }

    const timelineWrapper = $id('timelineWrapper');
    if (timelineWrapper) {
      let isPointerDown = false;

      const handleScrub = (clientX) => {
        const scrollContainer = document.querySelector('.table-scroll-container');
        if (!timelineWrapper || !scrollContainer || !weatherData) return;
        const rect = timelineWrapper.getBoundingClientRect();
        if (rect.width <= 0) return;

        const clickX = Math.max(0, Math.min(rect.width, clientX - rect.left));

        // In the 7 Day view there is nothing to scrub, so a tap on the graph
        // opens the Daily view at that time.
        if (currentMode === 'day') {
          const times = weatherData.data_1h && weatherData.data_1h.time;
          if (!times || !times.length) return;
          const s = getCurrentHourStartIndex(times);
          const count = getHourlyEndIndex(times, s) - s;
          if (count <= 0) return;
          const idx = s + Math.min(count - 1, Math.floor((clickX / rect.width) * count));
          jumpToTimelineDay(0, idx, !prefersReducedMotion(), true);
          return;
        }

        const totalWrapperWidth = rect.width;
        const stickyWidth = getStickyWidth();
        const visibleDataWidth = Math.max(1, scrollContainer.clientWidth - stickyWidth);
        const totalDataWidth = Math.max(visibleDataWidth, scrollContainer.scrollWidth - stickyWidth);
        const maxScroll = Math.max(0, scrollContainer.scrollWidth - scrollContainer.clientWidth);

        if (maxScroll <= 0) return;

        const widthRatio = Math.min(1, Math.max(0.04, visibleDataWidth / totalDataWidth));
        const selectorWidth = Math.round(widthRatio * totalWrapperWidth);
        const maxSelectorTravel = Math.max(0, totalWrapperWidth - selectorWidth);

        // Center selector around the click/drag coordinate
        let targetSelectorLeft = clickX - (selectorWidth / 2);
        targetSelectorLeft = Math.max(0, Math.min(maxSelectorTravel, targetSelectorLeft));

        const scrollFraction = maxSelectorTravel > 0 ? (targetSelectorLeft / maxSelectorTravel) : 0;
        scrollContainer.scrollLeft = scrollFraction * maxScroll;

        syncTimelineOnTableScroll();
      };

      timelineWrapper.onpointerdown = (e) => {
        isPointerDown = true;
        try {
          timelineWrapper.setPointerCapture(e.pointerId);
        } catch (_) {}
        handleScrub(e.clientX);
      };

      timelineWrapper.onpointermove = (e) => {
        if (!isPointerDown) return;
        handleScrub(e.clientX);
      };

      const endPointer = (e) => {
        if (!isPointerDown) return;
        isPointerDown = false;
        try {
          timelineWrapper.releasePointerCapture(e.pointerId);
        } catch (_) {}
      };

      timelineWrapper.onpointerup = endPointer;
      timelineWrapper.onpointercancel = endPointer;
    }
  }

  // ===========================================================================
  // Scrolling and view switching
  // ===========================================================================
  // Index of the forecast hour that contains "now" (site time).
  function getCurrentHourIndex() {
    const times = weatherData && weatherData.data_1h && weatherData.data_1h.time;
    if (!times || !times.length) return 0;
    const nowMs = getSiteWallMs();
    let closestIdx = 0;
    let minDiff = Infinity;
    for (let i = 0; i < times.length; i++) {
      const ms = wallStringToMs(times[i]);
      if (isNaN(ms)) continue;
      if (ms <= nowMs && nowMs < ms + 3600000) return i;
      const diff = Math.abs(ms - nowMs);
      if (diff < minDiff) { minDiff = diff; closestIdx = i; }
    }
    return closestIdx;
  }

  function scrollToHour(hourIdx, smooth = true, center = false) {
    const scrollContainer = document.querySelector('.table-scroll-container');
    const targetCol = $id(`col-hour-${hourIdx}`);
    if (!scrollContainer || !targetCol) return;

    const stickyWidth = getStickyWidth();
    const visibleDataWidth = scrollContainer.clientWidth - stickyWidth;

    let targetLeft;
    if (center) {
      targetLeft = (targetCol.offsetLeft - stickyWidth) - (visibleDataWidth / 2) + (targetCol.offsetWidth / 2);
    } else {
      targetLeft = targetCol.offsetLeft - stickyWidth;
    }

    const maxScroll = Math.max(0, scrollContainer.scrollWidth - scrollContainer.clientWidth);
    targetLeft = Math.max(0, Math.min(maxScroll, targetLeft));

    if (smooth && !prefersReducedMotion()) {
      scrollContainer.scrollTo({ left: targetLeft, behavior: 'smooth' });
    } else {
      scrollContainer.scrollLeft = targetLeft;
    }

    syncTimelineOnTableScroll();

    if (programmaticScrollTimeout) clearTimeout(programmaticScrollTimeout);
    programmaticScrollTimeout = setTimeout(syncTimelineOnTableScroll, smooth ? 450 : 50);
  }

  // Remembers which hour is at the left edge so a re-render doesn't move the view.
  function captureScrollAnchor() {
    if (currentMode !== 'hour') return null;
    const scrollContainer = document.querySelector('.table-scroll-container');
    if (!scrollContainer) return null;
    const stickyWidth = getStickyWidth();
    const ths = document.querySelectorAll('#tableHead .row-hour-header th[data-time]');
    for (const th of ths) {
      if (th.offsetLeft + th.offsetWidth > scrollContainer.scrollLeft + stickyWidth + 1) {
        return { time: th.dataset.time, delta: th.offsetLeft - stickyWidth - scrollContainer.scrollLeft };
      }
    }
    return null;
  }

  function restoreScrollAnchor(anchor) {
    if (!anchor) return;
    const scrollContainer = document.querySelector('.table-scroll-container');
    if (!scrollContainer) return;
    const ths = document.querySelectorAll('#tableHead .row-hour-header th[data-time]');
    for (const th of ths) {
      if (th.dataset.time === anchor.time) {
        scrollContainer.scrollLeft = Math.max(0, th.offsetLeft - getStickyWidth() - anchor.delta);
        syncTimelineOnTableScroll();
        return;
      }
    }
    scrollContainer.scrollLeft = 0;
    syncTimelineOnTableScroll();
  }

  function rerenderPreservingScroll() {
    if (!weatherData || loadState !== 'ready') return;
    const anchor = captureScrollAnchor();
    renderForecast();
    renderWindOverview();
    updateNotice();
    restoreScrollAnchor(anchor);
  }

  function setMode(mode, options = {}) {
    currentMode = mode;
    const isHour = mode === 'hour';
    [['tabDaily', isHour], ['tab7Day', !isHour]].forEach(([id, active]) => {
      const el = $id(id);
      if (!el) return;
      el.classList.toggle('active', active);
      el.setAttribute('aria-selected', String(active));
      el.tabIndex = active ? 0 : -1;
    });
    const panel = $id('forecastPanel');
    if (panel) panel.setAttribute('aria-labelledby', isHour ? 'tabDaily' : 'tab7Day');
    const hint = $id('overviewHint');
    if (hint) hint.textContent = isHour ? 'Touch or drag anywhere to scrub' : 'Tap the graph to jump to that time in Daily view';
    if (options.render !== false) {
      renderForecast();
      updateNotice();
    }
  }

  function jumpToTimelineDay(dayIndex, hourIndex = null, smooth = true, center = false) {
    if (currentMode === 'day') {
      setMode('hour');
    }

    const startIdx = weatherData && weatherData.data_1h && weatherData.data_1h.time ? getCurrentHourStartIndex(weatherData.data_1h.time) : 0;
    let targetHourIdx = hourIndex !== null ? hourIndex : dayIndex * 24;
    if (targetHourIdx < startIdx) targetHourIdx = startIdx;

    scrollToHour(targetHourIdx, smooth, center);
  }

  function syncTimelineOnTableScroll() {
    if (!weatherData) return;
    const scrollContainer = document.querySelector('.table-scroll-container');
    const selector = $id('timelineSelector');
    const timelineWrapper = $id('timelineWrapper');
    if (!scrollContainer || !selector || !timelineWrapper) return;

    if (currentMode === 'day') {
      selector.style.display = 'none';
      return;
    }

    const totalWrapperWidth = timelineWrapper.clientWidth;
    if (!totalWrapperWidth) return;

    const stickyWidth = getStickyWidth();
    const visibleDataWidth = Math.max(1, scrollContainer.clientWidth - stickyWidth);
    const totalDataWidth = Math.max(visibleDataWidth, scrollContainer.scrollWidth - stickyWidth);
    const maxScroll = Math.max(0, scrollContainer.scrollWidth - scrollContainer.clientWidth);

    // Continuous constant width calculation prevents expanding/contracting during motion
    const widthRatio = Math.min(1, Math.max(0.04, visibleDataWidth / totalDataWidth));
    const selectorWidth = Math.round(widthRatio * totalWrapperWidth);
    const maxSelectorTravel = Math.max(0, totalWrapperWidth - selectorWidth);

    const scrollFraction = maxScroll > 0 ? Math.max(0, Math.min(1, scrollContainer.scrollLeft / maxScroll)) : 0;
    const selectorLeft = Math.round(scrollFraction * maxSelectorTravel);

    selector.style.display = 'block';
    selector.style.width = `${selectorWidth}px`;
    selector.style.left = `${selectorLeft}px`;
  }

  // ===========================================================================
  // Sample data (only shown with ?demo=1)
  // ===========================================================================
  function getFallbackMockData() {
    const nowWall = getSiteWallMs();
    const startHour = Math.floor(nowWall / 3600000) * 3600000;
    const startDay = Math.floor(nowWall / 86400000) * 86400000;
    const dailyTimes = [];
    const hourlyTimes = [];

    for (let d = 0; d < 7; d++) {
      dailyTimes.push(wallMsToString(startDay + d * 86400000).substring(0, 10));
    }
    for (let h = 0; h < 168; h++) {
      hourlyTimes.push(wallMsToString(startHour + h * 3600000));
    }
    const hourOfDay = (i) => new Date(startHour + i * 3600000).getUTCHours();
    const isoNow = new Date().toISOString().substring(0, 16).replace('T', ' ');

    return {
      units: {
        temperature: '°C',
        windspeed: 'm/s',
        precipitation: 'mm',
        precipitation_probability: '%'
      },
      metadata: {
        latitude: SITE_LAT,
        longitude: SITE_LON,
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
          const hod = hourOfDay(i);
          const cycle = (hod >= 11 && hod <= 19) ? 6.5 : 2.5;
          return cycle + (dayIdx === 3 ? 3.5 : 0) + (Math.sin(i) * 1.2);
        }),
        gust: Array.from({ length: 168 }, (_, i) => {
          const dayIdx = Math.floor(i / 24);
          const hod = hourOfDay(i);
          const base = (hod >= 11 && hod <= 19) ? 9.5 : 4.0;
          return base + (dayIdx === 3 ? 4.5 : 0) + (Math.cos(i) * 1.5);
        }),
        winddirection: Array.from({ length: 168 }, () => 220 + Math.floor(Math.random() * 30)),
        pictocode: Array.from({ length: 168 }, () => 2),
        precipitation_probability: Array.from({ length: 168 }, (_, i) => (hourOfDay(i) >= 14 && hourOfDay(i) <= 17 && Math.floor(i / 24) === 4 ? 20 : 0)),
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

  // ===========================================================================
  // Loading, refreshing and rendering
  // ===========================================================================
  async function loadWeatherData(options = {}) {
    if (isLoading) return;
    isLoading = true;
    try {
      await loadWeatherDataInner(options);
    } finally {
      isLoading = false;
    }
  }

  async function loadWeatherDataInner(options) {
    const silent = !!options.silent;
    const hadData = !!weatherData && loadState === 'ready';

    // A manual retry from the error state goes back to the loading skeleton.
    if (!silent && loadState === 'error') {
      loadState = 'loading';
      weatherData = null;
      noticeState.error = null;
      noticeState.refreshFailed = false;
      noticeState.stale = null;
      updateNotice();
      updateFooter();
      renderForecast();
    }
    if (!hadData) setStatus('updating', 'Updating...');

    let json = null;
    let failure = null;
    try {
      if (DEMO_MODE) {
        json = getFallbackMockData();
      } else {
        const resp = await fetchTextWithTimeout(METEOBLUE_CACHE_URL, { cache: 'no-store' });
        if (!resp.ok) throw new Error(`HTTP ${resp.status}`);
        json = JSON.parse(resp.text);
      }
      if (!json || !(json.data_day || json.data_1h)) throw new Error('Unexpected JSON schema from cache');
    } catch (err) {
      failure = err;
      console.warn('Forecast fetch failed:', err && err.message ? err.message : err);
    }

    if (failure) {
      if (hadData) {
        // Keep showing the last good forecast and say that it could not be refreshed.
        const d = getModelRunDate(weatherData);
        noticeState.refreshFailed = true;
        noticeState.issuedText = d ? formatIssued(d) : '';
        setStatus('stale', 'Stale');
      } else {
        loadState = 'error';
        weatherData = null;
        noticeState.error = {
          text: "The forecast couldn't be loaded, so no forecast is shown. Check your connection and try again.",
          retry: true
        };
        setStatus('error', 'Unavailable');
        updateFooter();
        renderForecast();
      }
      updateNotice();
      return;
    }

    const firstLoad = !hadData;
    weatherData = json;
    lastLoadAt = Date.now();
    noticeState.error = null;
    noticeState.refreshFailed = false;
    noticeState.stale = null;

    const modelRunDate = getModelRunDate(json);

    if (!DEMO_MODE && isForecastExpired(json)) {
      loadState = 'error';
      noticeState.error = {
        text: `The forecast data is out of date${modelRunDate ? ' (issued ' + formatIssued(modelRunDate) + ')' : ''}, so it isn't shown. Check back soon.`,
        retry: true
      };
      setStatus('error', 'Out of date');
      updateFooter();
      renderForecast();
      updateNotice();
      return;
    }

    loadState = 'ready';

    let stale = false;
    if (modelRunDate && !DEMO_MODE) {
      const ageHours = (Date.now() - modelRunDate.getTime()) / 3600000;
      if (ageHours > STALE_AFTER_HOURS) {
        stale = true;
        noticeState.stale = { ageHours };
      }
    }
    if (DEMO_MODE) setStatus('demo', 'Demo Mode');
    else if (stale) setStatus('stale', 'Stale');
    else setStatus('live', 'Meteoblue');
    updateFooter();

    // Club hours load in the background. First paint waits briefly so the usual
    // fast response doesn't flash the standard schedule, but never longer.
    const clubPromise = preloadClubHours();
    await Promise.race([clubPromise, sleep(CLUB_FIRST_PAINT_WAIT_MS)]);

    const anchor = firstLoad ? null : captureScrollAnchor();
    renderForecast();
    renderWindOverview();
    updateNotice();
    updateClubNote();
    renderedClubVersion = clubVersion;

    if (firstLoad) {
      setTimeout(() => {
        if (currentMode === 'hour') scrollToHour(getCurrentHourIndex(), false, false);
        else syncTimelineOnTableScroll();
      }, 50);
    } else {
      restoreScrollAnchor(anchor);
    }

    clubPromise.then(() => {
      updateClubNote();
      if (clubVersion !== renderedClubVersion) {
        renderedClubVersion = clubVersion;
        rerenderPreservingScroll();
      }
    });
  }

  function renderForecast() {
    const table = $id('forecastTable');
    const thead = $id('tableHead');
    const tbody = $id('tableBody');
    const card = $id('forecastCard');
    const panel = $id('forecastPanel');

    if (card) card.classList.toggle('is-error', loadState === 'error');
    if (loadState === 'error') return;

    if (!weatherData) {
      renderTableSkeleton();
      return;
    }

    if (currentMode === 'hour') {
      table.className = 'structured-forecast hourly-view';
      if (hasHourlyData()) renderHourlyTable(thead, tbody);
      else { thead.innerHTML = ''; tbody.innerHTML = ''; }
    } else {
      table.className = 'structured-forecast seven-day-view';
      if (hasDailyData()) render7DayTable(thead, tbody);
      else { thead.innerHTML = ''; tbody.innerHTML = ''; }
      const selector = $id('timelineSelector');
      if (selector) selector.style.display = 'none';
    }
    if (panel) panel.setAttribute('aria-busy', 'false');
  }

  function initForecastApp() {
    const tabDaily = $id('tabDaily');
    const tab7Day = $id('tab7Day');
    const scrollContainer = document.querySelector('.table-scroll-container');

    // Immediately render full skeleton layout so page geometry is fixed on initial paint
    renderTableSkeleton();
    setMode('hour', { render: false });

    if (scrollContainer) {
      scrollContainer.addEventListener('scroll', syncTimelineOnTableScroll, { passive: true });
    }

    if (tabDaily) {
      tabDaily.addEventListener('click', () => {
        if (currentMode === 'hour') return;
        setMode('hour');
        setTimeout(() => {
          scrollToHour(getCurrentHourIndex(), true, false);
        }, 50);
      });
    }

    if (tab7Day) {
      tab7Day.addEventListener('click', () => {
        if (currentMode === 'day') return;
        setMode('day');
        syncTimelineOnTableScroll();
      });
    }

    // Arrow-key navigation between the two tabs
    const tabs = [tabDaily, tab7Day].filter(Boolean);
    tabs.forEach((tab) => {
      tab.addEventListener('keydown', (e) => {
        const i = tabs.indexOf(e.currentTarget);
        let next = null;
        if (e.key === 'ArrowRight' || e.key === 'ArrowLeft') next = (i + 1) % tabs.length;
        else if (e.key === 'Home') next = 0;
        else if (e.key === 'End') next = tabs.length - 1;
        if (next !== null) {
          e.preventDefault();
          tabs[next].focus();
          tabs[next].click();
        }
      });
    });

    window.addEventListener('resize', () => {
      syncTimelineOnTableScroll();
    });

    // Temperature text colors depend on the theme, so redraw when it changes.
    let lastDark = isDarkTheme();
    try {
      new MutationObserver(() => {
        const dark = isDarkTheme();
        if (dark !== lastDark) {
          lastDark = dark;
          rerenderPreservingScroll();
        }
      }).observe(document.documentElement, { attributes: true, attributeFilter: ['class'] });
    } catch (_) {}

    // Keep the forecast (and the "now" column) fresh while the page stays open.
    setInterval(() => {
      if (document.visibilityState === 'visible') loadWeatherData({ silent: true });
    }, REFRESH_INTERVAL_MS);
    document.addEventListener('visibilitychange', () => {
      if (document.visibilityState === 'visible' && lastLoadAt && (Date.now() - lastLoadAt) > RESUME_REFRESH_AFTER_MS) {
        loadWeatherData({ silent: true });
      }
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

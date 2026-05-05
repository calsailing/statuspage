
<style>
    #isolated-weather-widget {
        font-family: 'Inter', sans-serif !important;
        --bg-panel: #ffffff; 
        --border-panel: #f1f5f9; 
        --text-primary: #0f172a; 
        --text-secondary: #64748b; 
        --text-muted: #94a3b8;
        --compass-text: #9ca3af;
        --map-sensor: #3b82f6;
        --hero-bg-1: #eff6ff; 
        --hero-bg-2: #f8fafc; 
        --hero-border: rgba(255, 255, 255, 0.6);
        --trend-bg: #f8fafc; 
        --trend-red: #ef4444; 
        --trend-green: #22c55e;
        --icon-indigo-bg: #eef2ff; 
        --icon-indigo: #6366f1; 
        --icon-amber-bg: #fffbeb; 
        --icon-amber: #f59e0b;
        --scale-bg: #f1f5f9; 
        --dial-tick: #cbd5e1; 
        --dial-tick-major: #94a3b8; 
        --track-bg: #f1f5f9; 
        --grey-tick: #cbd5e1; 
        --bubble-fill: #ffffff; 
        --bubble-opacity: 0.75;
        transition: color 0.3s ease;
        display: flex;
        flex-direction: column;
        gap: 1.5rem;
        padding: 0.5rem;
        width: 100%;
        position: relative;
        color: var(--text-primary);
    }

    #isolated-weather-widget.is-dark {
        --bg-panel: #363636; 
        --border-panel: #4a4a4a; 
        --text-primary: #e5e7eb; 
        --text-secondary: #9ca3af; 
        --text-muted: #6b7280;
        --compass-text: #e5e7eb;
        --map-sensor: #818cf8;
        --hero-bg-1: #2a2a2a; 
        --hero-bg-2: #363636; 
        --hero-border: #4a4a4a;
        --trend-bg: #2a2a2a;
        --trend-red: #f87171;
        --trend-green: #4ade80;
        --icon-indigo-bg: rgba(99, 102, 241, 0.15);
        --icon-indigo: #818cf8;
        --icon-amber-bg: rgba(245, 158, 11, 0.15);
        --icon-amber: #fbbf24;
        --scale-bg: #2a2a2a;
        --dial-tick: #4a4a4a;
        --dial-tick-major: #6b7280;
        --track-bg: #2a2a2a;
        --grey-tick: #4a4a4a;
        --bubble-fill: #2a2a2a;
        --bubble-opacity: 0.9;
    }

    #isolated-weather-widget, 
    #isolated-weather-widget .iw-dial-card, 
    #isolated-weather-widget .iw-card { 
        border-radius: 0 !important; 
    }

    #isolated-weather-widget * { box-sizing: border-box; }
    #isolated-weather-widget p, #isolated-weather-widget h1, #isolated-weather-widget h2 { margin: 0; padding: 0; }
    #isolated-weather-widget .hidden { display: none !important; }

    @media (min-width: 768px) { 
        #isolated-weather-widget { flex-direction: row; align-items: stretch; } 
        .iw-dial-card { flex: 0 0 auto; width: auto; max-width: none; aspect-ratio: 330 / 263; min-width: 330px; }
    }
    
    .iw-panel { position: relative; flex: 1; width: 100%; display: flex; flex-direction: column; }
    .iw-dial-card { 
        background-color: var(--bg-panel); 
        border: 1px solid var(--border-panel); 
        box-shadow: 0 1px 2px 0 rgba(0,0,0,0.05); 
        padding: 5px; 
        display: flex; 
        flex-direction: column; 
        align-items: center; 
        justify-content: center; 
        transition: background-color 0.3s ease, border-color 0.3s ease; 
    }

    .iw-map-bg {
        position: absolute;
        top: 0; left: 0; right: 0; bottom: 0;
        z-index: 0;
        overflow: hidden;
        background: var(--bg-panel);
        opacity: 0;
        transition: opacity 0.4s ease;
    }
    #isolated-weather-widget.map-mode .iw-map-bg { opacity: 1; }

    #iw-map-container {
        width: 100%;
        height: 100%;
        pointer-events: none;
        background: var(--bg-panel);
    }

    .iw-map-overlay {
        position: absolute;
        inset: 0;
        background: rgba(255, 255, 255, 0.15);
        z-index: 1;
        pointer-events: none;
    }

    #isolated-weather-widget.is-dark .leaflet-tile-pane {
        filter: brightness(85%) contrast(110%);
    }
    #isolated-weather-widget.is-dark .iw-map-overlay {
        background: rgba(54, 54, 54, 0.25);
    }

    .iw-map-toggle {
        position: absolute; top: 10px; right: 10px; z-index: 10;
        display: flex; align-items: center; gap: 6px;
        background-color: var(--bg-panel);
        padding: 6px 10px;
        border-radius: 20px;
        box-shadow: 0 2px 5px rgba(0,0,0,0.1);
        border: 1px solid var(--border-panel);
        transition: background-color 0.3s ease, border-color 0.3s ease;
    }
    .iw-toggle-label {
        font-size: 10px; font-weight: 700; text-transform: uppercase;
        color: var(--text-secondary); letter-spacing: 0.05em; user-select: none;
    }
    .iw-switch { position: relative; display: inline-block; width: 32px; height: 18px; }
    .iw-switch input { opacity: 0; width: 0; height: 0; }
    .iw-slider {
        position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0;
        background-color: var(--border-panel); border: 1px solid var(--dial-tick-major);
        transition: .3s; border-radius: 18px;
    }
    .iw-slider:before {
        position: absolute; content: ""; height: 12px; width: 12px; left: 2px; bottom: 2px;
        background-color: var(--text-secondary); transition: .3s; border-radius: 50%;
    }
    .iw-switch input:checked + .iw-slider { background-color: var(--icon-indigo-bg); border-color: var(--map-sensor); }
    .iw-switch input:checked + .iw-slider:before { transform: translateX(14px); background-color: var(--map-sensor); }

    .gauge-bg-track, .gauge-gust-track, .gauge-color-track, .gauge-tick-group, .compass-ticks, .gauge-marker {
        transition: opacity 0.4s ease;
    }
    #isolated-weather-widget.map-mode .gauge-bg-track, 
    #isolated-weather-widget.map-mode .gauge-gust-track, 
    #isolated-weather-widget.map-mode .gauge-color-track, 
    #isolated-weather-widget.map-mode .gauge-tick-group, 
    #isolated-weather-widget.map-mode .compass-ticks,
    #isolated-weather-widget.map-mode .gauge-marker {
        opacity: 0 !important;
    }

    .iw-gauge-mount { position: relative; width: 100%; height: 100%; display: flex; justify-content: center; align-items: center; z-index: 2; }
    .iw-weather-grid { display: grid; grid-template-columns: repeat(2, minmax(0, 1fr)); gap: 0.75rem; flex-grow: 1; width: 100%; height: 100%; }
    .iw-card { padding: 1rem; box-shadow: 0 1px 2px 0 rgba(0,0,0,0.05); transition: all 0.3s ease; display: flex; flex-direction: column; background-color: var(--bg-panel); border: 1px solid var(--border-panel); }
    .iw-card:hover { box-shadow: 0 4px 6px -1px rgba(0,0,0,0.1); }
    .iw-card-hero { grid-column: span 2 / span 2; background: linear-gradient(to bottom right, var(--hero-bg-1), var(--hero-bg-2)); border: 1px solid var(--hero-border); justify-content: center; }
    .iw-card-small { grid-column: span 1 / span 1; justify-content: space-between; }
    .iw-card-small:hover { transform: translateY(-4px); }
    .iw-flex-col { display: flex; flex-direction: column; }
    .iw-items-center { display: flex; align-items: center; }
    .iw-justify-between { display: flex; justify-content: space-between; }
    .iw-temp-label { display: flex; align-items: center; gap: 0.375rem; margin-bottom: 0.25rem; color: var(--text-secondary); font-size: 10px; font-weight: 600; text-transform: uppercase; letter-spacing: 0.05em; margin-top: 0.25rem; }
    .iw-temp-val-f { font-size: 2.25rem; font-weight: 700; letter-spacing: -0.05em; line-height: 1; transition: opacity 0.3s; }
    .iw-temp-val-c { color: var(--text-secondary); font-size: 0.875rem; font-weight: 500; margin-top: 0.125rem; transition: opacity 0.3s; }
    .iw-cond-text { font-size: 0.875rem; font-weight: 600; margin-top: 0.5rem; text-align: center; line-height: 1.25; transition: opacity 0.3s; }
    .iw-icon-circle { width: 28px; height: 28px; border-radius: 50%; display: flex; align-items: center; justify-content: center; }
    .iw-icon-circle.indigo { background-color: var(--icon-indigo-bg); color: var(--icon-indigo); }
    .iw-icon-circle.amber { background-color: var(--icon-amber-bg); color: var(--icon-amber); }
    .iw-data-val { font-size: 1.5rem; font-weight: 700; letter-spacing: -0.025em; line-height: 1; transition: opacity 0.3s; }
    .iw-data-label { font-size: 10px; font-weight: 600; color: var(--text-muted); text-transform: uppercase; letter-spacing: 0.05em; margin-top: 0.125rem; }
    .iw-trend-badge { margin-top: 0.5rem; display: flex; align-items: center; gap: 0.375rem; font-size: 0.75rem; font-weight: 500; color: var(--text-secondary); background-color: var(--trend-bg); padding: 0.125rem 0.5rem; width: max-content; min-height: 24px; }
    .iw-uv-bar-wrap { margin-top: 0.625rem; width: 100%; position: relative; display: flex; align-items: center; height: 0.5rem; }
    .iw-uv-bar-bg { width: 100%; height: 0.25rem; display: flex; overflow: hidden; }
    .iw-uv-green { height: 100%; background-color: #4ade80; width: 30%; }
    .iw-uv-amber { height: 100%; background-color: #fbbf24; width: 30%; }
    .iw-uv-red { height: 100%; background-color: #f87171; width: 40%; }
    .iw-uv-marker { position: absolute; top: 50%; transform: translateY(-50%); width: 0.375rem; height: 0.375rem; background-color: #ffffff; box-shadow: 0 1px 3px 0 rgba(0,0,0,0.1); border: 1px solid #64748b; transition: all 0.5s; z-index: 10; }
    
    @keyframes float { 0%, 100% { transform: translateY(0); } 50% { transform: translateY(-4px); } }
    .animate-float { width: 48px; height: 48px; filter: drop-shadow(0 1px 2px rgba(0,0,0,0.05)); animation: float 4s ease-in-out infinite; display: flex; align-items: center; justify-content: center; }
    
    @keyframes spin-slow { from { transform: rotate(0deg); } to { transform: rotate(360deg); } }
    .iw-card-small:hover .animate-spin-slow { animation: spin-slow 4s linear infinite; }

    #isolated-weather-widget text { font-family: 'Inter', sans-serif !important; fill: var(--text-primary); transition: fill 0.3s ease; }
    #isolated-weather-widget .center-speed { font-weight: 800; font-variant-numeric: tabular-nums !important; }
    #isolated-weather-widget .speed-tick { stroke: var(--dial-tick); stroke-width: 1.5; stroke-linecap: round; transition: stroke 0.3s ease; }
    #isolated-weather-widget .gauge-label { font-size: 11px !important; font-weight: 300 !important; fill: var(--compass-text) !important; opacity: 1; font-variant-numeric: tabular-nums !important; }
</style>

<div id="isolated-weather-widget">
    <div class="iw-panel iw-dial-card">
        <div class="iw-map-toggle">
            <span class="iw-toggle-label" title="Satellite Map" style="display: flex; align-items: center;">
                <svg style="width: 16px; height: 16px;" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="10"/><path d="M12 2a14.5 14.5 0 0 0 0 20 14.5 14.5 0 0 0 0-20"/><path d="M2 12h20"/></svg>
            </span>
            <label class="iw-switch">
                <input type="checkbox" id="map-mode-toggle">
                <span class="iw-slider"></span>
            </label>
        </div>
        <div class="iw-map-bg">
            <div id="iw-map-container"></div>
            <div class="iw-map-overlay"></div>
        </div>
        <div id="gauge-mount" class="iw-gauge-mount"></div>
    </div>
    <div class="iw-panel">
        <div class="iw-weather-grid">
            <div class="iw-card iw-card-hero">
                <div class="iw-justify-between iw-items-center" style="padding: 0 0.5rem;">
                    <div class="iw-flex-col">
                        <div class="iw-temp-label">
                            <svg style="width: 14px; height: 14px; color: #3b82f6;" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M14 14.76V3.5a2.5 2.5 0 0 0-5 0v11.26a4.5 4.5 0 1 0 5 0z"/></svg>
                            <span>Current</span>
                        </div>
                        <h1 id="val-temp-f" class="iw-temp-val-f">--&deg;F</h1>
                        <p id="val-temp-c" class="iw-temp-val-c">--&deg;C</p>
                    </div>
                    <div class="iw-flex-col iw-items-center" style="padding-top: 0.25rem;">
                        <div id="icon-weather" class="animate-float"></div>
                        <p id="val-conditions" class="iw-cond-text">Loading...</p>
                    </div>
                </div>
            </div>
            <div class="iw-card iw-card-small">
                <div class="iw-flex-col" style="height: 100%; justify-content: space-between;">
                    <div class="iw-icon-circle indigo">
                        <svg style="width: 14px; height: 14px;" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="m12 14 4-4"/><path d="M3.34 19a10 10 0 1 1 17.32 0"/></svg>
                    </div>
                    <div><h2 id="val-pressure" class="iw-data-val">--</h2><p class="iw-data-label">Pressure (mb)</p></div>
                    <div id="val-pressure-trend" class="iw-trend-badge"></div>
                </div>
            </div>
            <div class="iw-card iw-card-small">
                <div class="iw-flex-col" style="height: 100%; justify-content: space-between;">
                    <div class="iw-icon-circle amber">
                        <svg class="animate-spin-slow" style="width: 14px; height: 14px;" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="4"/><path d="M12 2v2"/><path d="M12 20v2"/><path d="m4.93 4.93 1.41 1.41"/><path d="m17.66 17.66 1.41 1.41"/><path d="M2 12h2"/><path d="M20 12h2"/><path d="m6.34 17.66-1.41 1.41"/><path d="m19.07 4.93-1.41 1.41"/></svg>
                    </div>
                    <div><h2 id="val-uv" class="iw-data-val">--</h2><p class="iw-data-label">UV Index</p></div>
                    <div class="iw-uv-bar-wrap">
                        <div class="iw-uv-bar-bg"><div class="iw-uv-green"></div><div class="iw-uv-amber"></div><div class="iw-uv-red"></div></div>
                        <div id="uv-marker" class="iw-uv-marker hidden"></div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>


<script>
    /* #raw */
    // 1. API Configuration
    const STATIC_TOKEN = "8535e71d-2290-4965-ad3f-ab05b9294fdf";
    const API_OBS_BASE = "https://swd.weatherflow.com/swd/rest/observations/station/127241";
    const API_FCST_BASE = "https://swd.weatherflow.com/swd/rest/better_forecast?station_id=127241&units_wind=kts";

    // 2. Persistence Logic (Using localStorage)
    const STORAGE_KEY = 'cal_sailing_wind_state';

    const saveToLocalStorage = (data) => {
        try {
            const existing = JSON.parse(localStorage.getItem(STORAGE_KEY) || '{}');
            const updated = { ...existing, ...data };
            localStorage.setItem(STORAGE_KEY, JSON.stringify(updated));
        } catch (e) { console.warn("Local storage save failed:", e); }
    };

    const loadFromLocalStorage = () => {
        try {
            const state = JSON.parse(localStorage.getItem(STORAGE_KEY) || 'null');
            if (!state) return;
            
            if (state.obs) update(state.obs, true);
            if (state.tempF) document.getElementById('val-temp-f').innerText = state.tempF;
            if (state.tempC) document.getElementById('val-temp-c').innerText = state.tempC;
            if (state.pressure) document.getElementById('val-pressure').innerText = state.pressure;
            if (state.uv) {
                document.getElementById('val-uv').innerText = state.uv;
                const marker = document.getElementById('uv-marker');
                if (marker) {
                    marker.classList.remove('hidden');
                    marker.style.left = `calc(${Math.min((state.uv / 11) * 100, 100)}% - 3px)`;
                }
            }
            if (state.fcst) {
                document.getElementById('val-conditions').innerText = state.fcst.conditions || '--';
                document.getElementById('icon-weather').innerHTML = weatherIcons[state.fcst.icon] || '';
                document.getElementById('val-pressure-trend').innerHTML = trendIcons[state.fcst.trend] || '';
            }
            if (state.mapMode) {
                document.getElementById('map-mode-toggle').checked = true;
                document.getElementById('isolated-weather-widget').classList.add('map-mode');
                setTimeout(() => map.invalidateSize(), 100);
            }
        } catch (e) { console.warn("Local storage load failed:", e); }
    };

    // 3. Fetch Helper
    const fetchWithRetry = async (url, maxRetries = 3) => {
        for (let i = 0; i < maxRetries; i++) {
            try {
                const authenticatedUrl = new URL(url);
                authenticatedUrl.searchParams.set('token', STATIC_TOKEN);
                const controller = new AbortController();
                const timeoutId = setTimeout(() => controller.abort(), 5000);
                const response = await fetch(authenticatedUrl.toString(), { signal: controller.signal });
                clearTimeout(timeoutId);
                if (response.ok) return await response.json();
                if (response.status === 429) {
                    await new Promise(res => setTimeout(res, 1000));
                    continue;
                }
                throw new Error(`HTTP ${response.status}`);
            } catch (err) {
                if (i === maxRetries - 1) throw err;
                await new Promise(res => setTimeout(res, 500)); 
            }
        }
    };

    window.obsPrefetch = fetchWithRetry(API_OBS_BASE).catch(() => null);
    window.fcstPrefetch = fetchWithRetry(API_FCST_BASE).catch(() => null);

    // 4. Map Implementation
    const SENSOR_COORD = [37.85568, -122.31445];
    const MAP_CENTER = [37.85868, -122.31445]; 
    const isMobile = window.innerWidth < 768;
    const initialZoom = isMobile ? 13.8 : 14.3;

    const map = L.map('iw-map-container', {
        center: MAP_CENTER, zoom: initialZoom, zoomSnap: 0.1, zoomControl: false, attributionControl: false,
        dragging: false, scrollWheelZoom: false, doubleClickZoom: false, boxZoom: false, touchZoom: false
    });

    L.tileLayer('https://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}', {
        maxZoom: 19, attribution: 'Tiles &copy; Esri'
    }).addTo(map);

    const weatherIcons = {
        'clear-day': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: #f59e0b;"><circle cx="12" cy="12" r="4"></circle><path d="M12 2v2"></path><path d="M12 20v2"></path><path d="m4.93 4.93 1.41 1.41"></path><path d="m17.66 17.66 1.41 1.41"></path><path d="M2 12h2"></path><path d="M20 12h2"></path><path d="m6.34 17.66-1.41 1.41"></path><path d="m19.07 4.93-1.41 1.41"></path></svg>`,
        'clear-night': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: #818cf8;"><path d="M12 3a6 6 0 0 0 9 9 9 9 0 1 1-9-9Z"></path></svg>`,
        'cloudy': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: var(--text-muted);"><path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path></svg>`,
        'partly-cloudy-day': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: #0ea5e9;"><path d="M12 2v2"></path><path d="m4.93 4.93 1.41 1.41"></path><path d="M20 12h2"></path><path d="m19.07 4.93-1.41 1.41"></path><path d="M15.94 14A5 5 0 0 0 6 12a3 3 0 0 0 0 6h9.5a3.5 3.5 0 1 0 0-7h-.5Z"></path></svg>`,
        'partly-cloudy-night': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: #a5b4fc;"><path d="M10 6.13A6 6 0 0 0 15 15h3.5a3.5 3.5 0 1 0 0-7h-.5A5 5 0 0 0 10 6.13Z"></path></svg>`,
        'rain': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: #3b82f6;"><path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path><path d="M16 23v-2"></path><path d="M8 23v-2"></path><path d="M12 23v-2"></path></svg>`,
        'snow': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: #7dd3fc;"><path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path><path d="M8 23h.01"></path><path d="M12 23h.01"></path><path d="M16 23h.01"></path></svg>`,
        'wind': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: var(--text-secondary);"><path d="M17.7 7.7a2.5 2.5 0 1 1 1.8 4.3H2"></path><path d="M9.6 4.6A2 2 0 1 1 11 8H2"></path><path d="M12.6 19.4A2 2 0 1 0 14 16H2"></path></svg>`,
        'default': `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="width: 100%; height: 100%; color: #60a5fa;"><path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path></svg>`
    };

    const trendIcons = {
        'falling': `<svg style="width: 12px; height: 12px; color: var(--trend-red);" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M12 5v14M19 12l-7 7-7-7"/></svg> <span style="color: var(--trend-red);">Falling</span>`,
        'rising': `<svg style="width: 12px; height: 12px; color: var(--trend-green);" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M12 19V5M5 12l7-7 7 7"/></svg> <span style="color: var(--trend-green);">Rising</span>`,
        'steady': `<svg style="width: 12px; height: 12px; color: var(--text-secondary);" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M5 12h14"/></svg> <span style="color: var(--text-secondary);">Steady</span>`,
    };

    function syncTheme() {
        const widget = document.getElementById('isolated-weather-widget');
        if (!widget) return;
        let isDark = document.documentElement.classList.contains('dark');
        if (!isDark) {
            try {
                if (window.self !== window.top) isDark = window.parent.document.documentElement.classList.contains('dark');
            } catch (e) {
                isDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
            }
        }
        if (isDark) widget.classList.add('is-dark');
        else widget.classList.remove('is-dark');
    }

    function getCompassPoint(degrees) {
        const val = Math.floor((degrees / 22.5) + 0.5);
        const arr = ["N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"];
        return arr[(val % 16)];
    }

    // 5. D3 Setup
    const center = { x: 165, y: 180 }; 
    const R = { speedTrack: 130, compass: 110 };
    const SWEEP_START = -0.75 * Math.PI, SWEEP_END = 0.75 * Math.PI;
    let currentMaxSpeed = 30;

    const svg = d3.select("#gauge-mount").append("svg")
        .attr("viewBox", `0 32 330 263`)
        .style("width", "100%").style("height", "auto").style("display", "block").style("overflow", "visible")
        .append("g").attr("transform", `translate(${center.x},${center.y})`);

    const colorScale = d3.scaleLinear().domain([0, 8, 10, 13, 15, 18, 20, 30, 40, 50]).range(["#1e3a8a", "#3b82f6", "#22c55e", "#84cc16", "#eab308", "#f97316", "#ef4444", "#991b1b", "#7f1d1d", "#450a0a"]).clamp(true);
    const speedScale = d3.scaleLinear().domain([0, currentMaxSpeed]).range([SWEEP_START, SWEEP_END]);
    
    svg.append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_END}).attr("d", d3.arc().innerRadius(R.speedTrack - 10).outerRadius(R.speedTrack)).attr("fill", "var(--track-bg)").attr("class", "gauge-bg-track");
    
    const d3defs = svg.append("defs");
    const speedMaskPath = d3defs.append("clipPath").attr("id", "speed-mask").append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_START});
    const gustMaskPath = d3defs.append("clipPath").attr("id", "gust-mask").append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_START});
    
    d3defs.append("mask").attr("id", "bottom-bubble-cutout").attr("maskUnits", "userSpaceOnUse").attr("x", -200).attr("y", -200).attr("width", 400).attr("height", 400).append("rect").attr("x", -200).attr("y", -200).attr("width", 400).attr("height", 400).attr("fill", "white");
    d3.select("#bottom-bubble-cutout").append("circle").attr("cx", 0).attr("cy", 0).attr("r", 33).attr("fill", "black");
    
    const gustTrackGroup = svg.append("g").attr("clip-path", "url(#gust-mask)").attr("opacity", 0.3).attr("class", "gauge-gust-track");
    const colorTrackGroup = svg.append("g").attr("clip-path", "url(#speed-mask)").attr("class", "gauge-color-track");
    const tickGroup = svg.append("g").attr("class", "gauge-tick-group");
    const arcSpeed = d3.arc().innerRadius(R.speedTrack - 10).outerRadius(R.speedTrack);
    
    const lullMarker = svg.append("line").attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 10)).attr("stroke", "#1e3a8a").attr("stroke-width", 3).attr("class", "gauge-marker");
    const speedMarker = svg.append("line").attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 10)).attr("stroke", "#22c55e").attr("stroke-width", 3).attr("class", "gauge-marker");
    const gustMarker = svg.append("line").attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 10)).attr("stroke", "#ef4444").attr("stroke-width", 3).attr("class", "gauge-marker");

    function drawSpeedTrack(maxSpeed) {
        currentMaxSpeed = maxSpeed; speedScale.domain([0, maxSpeed]);
        gustTrackGroup.selectAll("*").remove(); colorTrackGroup.selectAll("*").remove(); tickGroup.selectAll("*").remove();
        for (let i = 0; i < 120; i++) {
            const start = SWEEP_START + (i * (SWEEP_END - SWEEP_START) / 120), end = start + ((SWEEP_END - SWEEP_START) / 120), segmentSpeed = (i / 120) * maxSpeed;
            gustTrackGroup.append("path").datum({startAngle: start, endAngle: end}).attr("d", arcSpeed).attr("fill", colorScale(segmentSpeed));
            colorTrackGroup.append("path").datum({startAngle: start, endAngle: end}).attr("d", arcSpeed).attr("fill", colorScale(segmentSpeed));
        }
        for (let v = 0; v <= maxSpeed; v += 5) {
            const angle = speedScale(v);
            tickGroup.append("line").attr("x1", R.speedTrack * Math.sin(angle)).attr("y1", -R.speedTrack * Math.cos(angle)).attr("x2", (R.speedTrack - 10) * Math.sin(angle)).attr("y2", -(R.speedTrack - 10) * Math.cos(angle)).attr("class", "speed-tick");
            tickGroup.append("text").attr("x", (R.speedTrack + 12) * Math.sin(angle)).attr("y", -(R.speedTrack + 12) * Math.cos(angle)).attr("class", "gauge-label").attr("text-anchor", "middle").attr("dy", "0.35em").text(v);
        }
    }
    drawSpeedTrack(currentMaxSpeed);

    const compassTicks = svg.append("g").attr("class", "compass-ticks");
    const cardinalLabels = { 0: 'N', 90: 'E', 180: 'S', 270: 'W' };
    for (let i = 0; i < 360; i += 22.5) {
        const angle = (i * Math.PI) / 180, isMajor = i % 90 === 0;
        compassTicks.append("line").attr("x1", R.compass * Math.sin(angle)).attr("y1", -R.compass * Math.cos(angle)).attr("x2", (R.compass - (isMajor ? 10 : 7)) * Math.sin(angle)).attr("y2", -(R.compass - (isMajor ? 10 : 7)) * Math.cos(angle)).attr("stroke", "var(--grey-tick)").attr("stroke-width", 1); 
        if (isMajor) {
            compassTicks.append("text").attr("x", (R.compass - 20) * Math.sin(angle)).attr("y", -(R.compass - 20) * Math.cos(angle)).attr("text-anchor", "middle").attr("dy", "0.35em").style("font-size", "11px").style("font-weight", "300").style("fill", "var(--compass-text)").text(cardinalLabels[i]);
        }
    }

    const pointer = svg.append("g"), vane = pointer.append("path").attr("d", "M 0,115 L 65,-95 L 0,-71 L -65,-95 Z").attr("opacity", 0.7);
    const bottomBubbleWrapper = svg.append("g").attr("mask", "url(#bottom-bubble-cutout)"), bottomBubble = bottomBubbleWrapper.append("g");
    bottomBubble.append("circle").attr("cx", 0).attr("cy", -50).attr("r", 21).attr("fill", "var(--bubble-fill)").attr("fill-opacity", "var(--bubble-opacity)");
    const dirTextGroup = bottomBubble.append("g").attr("transform", "translate(0, -50)");
    const dirReadout = dirTextGroup.append("text").attr("y", -5).style("font-size", "10px").style("font-weight", "900").attr("fill", "var(--text-primary)").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("---");
    const dirAngle = dirTextGroup.append("text").attr("y", 7).style("font-size", "9px").style("font-weight", "500").attr("fill", "var(--text-primary)").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("---\xB0");
    
    function showHoverState(e) {
        if (e && e.cancelable && (e.type === 'touchstart' || e.type === 'mouseenter')) {
            if (e.type === 'touchstart') e.preventDefault();
            defaultView.transition().duration(200).attr("opacity", 0);
            hoverView.transition().duration(200).attr("opacity", 1);
        }
    }
    function hideHoverState() {
        defaultView.transition().duration(200).attr("opacity", 1);
        hoverView.transition().duration(200).attr("opacity", 0);
    }

    const topBubble = svg.append("g").style("cursor", "pointer")
        .on("mouseenter", showHoverState).on("mouseleave", hideHoverState)
        .on("touchstart", showHoverState).on("touchend", hideHoverState);
        
    topBubble.append("circle").attr("cx", 0).attr("cy", 0).attr("r", 32).attr("fill", "var(--bubble-fill)").attr("fill-opacity", "var(--bubble-opacity)");
    
    const defaultView = topBubble.append("g").attr("opacity", 1);
    const speedVal = defaultView.append("text").attr("y", -4).attr("class", "center-speed").attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "52px").attr("fill", "var(--text-primary)").text("0");
    defaultView.append("text").attr("y", 24).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "8px").style("font-weight", "400").style("letter-spacing", "0.05em").attr("fill", "var(--text-primary)").text("KNOTS");

    const hoverView = topBubble.append("g").attr("opacity", 0).style("pointer-events", "none");
    hoverView.append("text").attr("y", -18).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "8px").style("font-weight", "600").attr("fill", "var(--text-secondary)").text("LULL");
    const lullText = hoverView.append("text").attr("y", -6).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "18px").style("font-weight", "700").attr("fill", "#3b82f6").text("0");
    hoverView.append("text").attr("y", 6).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "8px").style("font-weight", "600").attr("fill", "var(--text-secondary)").text("GUST");
    const gustText = hoverView.append("text").attr("y", 18).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "18px").style("font-weight", "700").attr("fill", "var(--trend-red)").text("0");

    function update(data, skipSave = false) {
        const l = data.lull || 0, s = data.speed || 0, g = data.gust || 0, d = data.direction || 0;
        let targetMax = 30; if (g > 40 || s > 40) targetMax = 50; else if (g > 30 || s > 30) targetMax = 40; if (targetMax !== currentMaxSpeed) drawSpeedTrack(targetMax);
        const t = d3.transition().duration(2400).ease(d3.easeCubicInOut);
        speedMaskPath.transition(t).attrTween("d", dat => { const i = d3.interpolate(dat.endAngle, speedScale(s)); return time => { dat.endAngle = i(time); return d3.arc().innerRadius(115).outerRadius(135)(dat); }; });
        gustMaskPath.transition(t).attrTween("d", dat => { const i = d3.interpolate(dat.endAngle, speedScale(g)); return time => { dat.endAngle = i(time); return d3.arc().innerRadius(115).outerRadius(135)(dat); }; });
        lullMarker.transition(t).attr("transform", `rotate(${(speedScale(l) * 180) / Math.PI})`);
        speedMarker.transition(t).attr("transform", `rotate(${(speedScale(s) * 180) / Math.PI})`);
        gustMarker.transition(t).attr("transform", `rotate(${(speedScale(g) * 180) / Math.PI})`);
        pointer.transition(t).attr("transform", `rotate(${d})`);
        bottomBubble.transition(t).attr("transform", `rotate(${d})`);
        dirTextGroup.transition(t).attr("transform", `translate(0, -50) rotate(${-d})`);
        vane.transition(t).attr("fill", colorScale(s));
        dirReadout.text(getCompassPoint(d));
        dirAngle.text(Math.round(d) + "\xB0");
        speedVal.transition(t).style("font-size", Math.round(s) >= 10 ? "46px" : "52px").tween("text", function() { const i = d3.interpolateNumber(this._currentS || 0, s); return time => { this._currentS = i(time); this.textContent = Math.round(this._currentS); }; });
        lullText.transition(t).tween("text", function() { const i = d3.interpolateNumber(this._currentL || 0, l); return time => { this._currentL = i(time); this.textContent = Math.round(this._currentL); }; });
        gustText.transition(t).tween("text", function() { const i = d3.interpolateNumber(this._currentG || 0, g); return time => { this._currentG = i(time); this.textContent = Math.round(this._currentG); }; });
        
        if (!skipSave) saveToLocalStorage({ obs: { lull: l, speed: s, gust: g, direction: d } });
    }

    // 6. Data Fetching
    async function fetchWeatherData(isInitialLoad = false) {
        try {
            let obsData;
            if (isInitialLoad && window.obsPrefetch) { obsData = await window.obsPrefetch; window.obsPrefetch = null; } 
            else obsData = await fetchWithRetry(API_OBS_BASE).catch(() => null); 
            
            if (obsData && obsData.obs && obsData.obs.length > 0) {
                const o = obsData.obs[0];
                const weatherState = {
                    lull: (o.wind_lull || 0) * 1.94384, speed: (o.wind_avg || 0) * 1.94384, gust: (o.wind_gust || 0) * 1.94384, direction: o.wind_direction || 0
                };
                update(weatherState);
                if (o.air_temperature != null) {
                    const tempF = (o.air_temperature * 9/5) + 32;
                    document.getElementById('val-temp-f').innerText = `${tempF.toFixed(1)}\xB0F`;
                    document.getElementById('val-temp-c').innerText = `${o.air_temperature.toFixed(1)}\xB0C`;
                    saveToLocalStorage({ tempF: `${tempF.toFixed(1)}\xB0F`, tempC: `${o.air_temperature.toFixed(1)}\xB0C` });
                }
                const pressure = o.sea_level_pressure || o.barometric_pressure || o.station_pressure;
                if (pressure != null) {
                    document.getElementById('val-pressure').innerText = pressure.toFixed(1);
                    saveToLocalStorage({ pressure: pressure.toFixed(1) });
                }
                if (o.uv != null) {
                    document.getElementById('val-uv').innerText = o.uv.toFixed(1);
                    const marker = document.getElementById('uv-marker');
                    if(marker) { marker.classList.remove('hidden'); let uvPercentage = Math.min((o.uv / 11) * 100, 100); marker.style.left = `calc(${uvPercentage}% - 3px)`; }
                    saveToLocalStorage({ uv: o.uv.toFixed(1) });
                }
            }
        } catch (e) { console.error("Obs error:", e); }

        if (isInitialLoad) {
            try {
                let fcstData;
                if (window.fcstPrefetch) { fcstData = await window.fcstPrefetch; window.fcstPrefetch = null; } 
                else fcstData = await fetchWithRetry(API_FCST_BASE).catch(() => null);

                if (fcstData && fcstData.current_conditions) {
                    const cc = fcstData.current_conditions;
                    document.getElementById('val-conditions').innerText = cc.conditions || '--';
                    document.getElementById('icon-weather').innerHTML = weatherIcons[cc.icon] || weatherIcons['default'];
                    document.getElementById('val-pressure-trend').innerHTML = trendIcons[cc.pressure_trend] || '';
                    saveToLocalStorage({ fcst: { conditions: cc.conditions, icon: cc.icon, trend: cc.pressure_trend } });
                }
            } catch (e) { console.error("Fcst error:", e); }
        }
    }

    // 7. Initialize
    update({ lull: 0, speed: 0, gust: 0, direction: 0 }, true); 
    syncTheme();
    loadFromLocalStorage(); // Initial restore

    // Always run fresh data update
    fetchWeatherData(true); 
    setInterval(() => fetchWeatherData(false), 60000);

    document.getElementById('map-mode-toggle').addEventListener('change', (e) => {
        const widget = document.getElementById('isolated-weather-widget');
        const isChecked = e.target.checked;
        if (isChecked) {
            widget.classList.add('map-mode');
            setTimeout(() => map.invalidateSize(), 100);
        } else {
            widget.classList.remove('map-mode');
        }
        saveToLocalStorage({ mapMode: isChecked });
    });
    /* #end raw */
</script>

<link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" />
<script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
<script src="https://d3js.org/d3.v7.min.js"></script>
 
<!-- Import the Inter font so it always renders correctly on any website -->
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700;800;900&display=swap" rel="stylesheet">

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
        display: flex;
        flex-direction: column;
        gap: 24px;
        padding: 8px;
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
        --compass-text: rgba(255, 255, 255, 0.6);
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

    #isolated-weather-widget.map-mode .iw-gauge-mount {
        /* Force Dark Mode for Wind Gauge Elements */
        --bg-panel: #2a2a2a !important; 
        --text-primary: #e5e7eb !important;
        --text-secondary: #9ca3af !important;
        --track-bg: #2a2a2a !important;
        --dial-tick: #4a4a4a !important;
        --bubble-fill: #2a2a2a !important;
        --bubble-opacity: 0.9 !important;
        
        /* Force Light Mode for Compass Elements */
        --compass-text: rgba(255, 255, 255, 0.6) !important;
        --grey-tick: #9ca3af !important;
    }

    #isolated-weather-widget, 
    #isolated-weather-widget .iw-dial-card, 
    #isolated-weather-widget .iw-card { 
        border-radius: 0 !important; 
    }

    /* Aggressive CSS Reset to isolate from host site styles */
    #isolated-weather-widget * { 
        box-sizing: border-box; 
        font-family: 'Inter', sans-serif !important;
    }
    #isolated-weather-widget p, 
    #isolated-weather-widget h1, 
    #isolated-weather-widget h2, 
    #isolated-weather-widget span,
    #isolated-weather-widget text,
    #isolated-weather-widget tspan { 
        margin: 0 !important; 
        padding: 0 !important; 
        line-height: normal !important; 
        letter-spacing: normal !important;
    }
    #isolated-weather-widget .hidden { display: none !important; }

    .iw-main-row { display: flex; flex-direction: column; gap: 24px; width: 100%; }

    @media (min-width: 768px) { 
        .iw-main-row { flex-direction: row; align-items: stretch; } 
        .iw-dial-card { flex: 1.25; min-width: 350px; max-width: 550px; aspect-ratio: 330 / 284; }
    }
    
    .iw-panel { position: relative; flex: 1; width: 100%; display: flex; flex-direction: column; }
    .iw-dial-card { 
        background-color: var(--bg-panel); 
        border: 1px solid var(--border-panel); 
        box-shadow: none; 
        padding: 3px; 
        display: flex; 
        flex-direction: column; 
        align-items: center; 
        justify-content: center; 
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
        border: 1px solid var(--border-panel);
        transition: background-color 0.3s ease, border-color 0.3s ease;
    }
    #isolated-weather-widget.map-mode .iw-map-toggle {
        background-color: rgba(0, 0, 0, 0.7);
        border-color: rgba(255, 255, 255, 0.1);
    }
    .iw-toggle-label {
        font-size: 10px; font-weight: 700; text-transform: uppercase;
        color: var(--text-secondary); letter-spacing: 0.05em; user-select: none;
    }

    .iw-gauge-mount {
        position: relative;
        z-index: 5;
        width: 100%;
    }

    /* Converted all rem units to explicit px units to block external scaling */
    .iw-weather-grid { display: grid; grid-template-columns: repeat(2, 1fr); gap: 8px; flex: 1; }
    
    .iw-card { background-color: var(--bg-panel); border: 1px solid var(--border-panel); border-radius: 12px; padding: 16px; box-shadow: none; transition: transform 0.2s ease; }
    .iw-card:hover { transform: translateY(-2px); }
    .iw-card-hero { grid-column: 1 / -1; background: linear-gradient(135deg, var(--hero-bg-1) 0%, var(--hero-bg-2) 100%); border: 1px solid var(--hero-border); box-shadow: none; }
    .iw-card-small { display: flex; flex-direction: column; justify-content: center; min-height: 110px; }
    
    .iw-flex-col { display: flex; flex-direction: column; }
    .iw-justify-between { display: flex; justify-content: space-between; }
    .iw-items-center { display: flex; align-items: center; }
    
    .iw-temp-label { display: flex; align-items: center; gap: 4px; font-size: 12px !important; font-weight: 400 !important; color: var(--text-secondary); text-transform: uppercase; letter-spacing: 0.05em !important; margin-bottom: 4px; }
    .iw-temp-val-f { font-size: 48px !important; font-weight: 800 !important; line-height: 1 !important; letter-spacing: -0.025em !important; color: var(--text-primary); }
    .iw-temp-val-c { font-size: 18px !important; font-weight: 500 !important; color: var(--text-muted); margin-top: 4px; }
    
    .iw-cond-text { font-size: 16px !important; font-weight: 500 !important; color: var(--text-secondary); margin-top: 8px; text-align: center; }
    
    .iw-data-val { font-size: 24px !important; font-weight: 700 !important; color: var(--text-primary); }
    .iw-data-label { font-size: 12px !important; font-weight: 500 !important; color: var(--text-secondary); text-transform: uppercase; letter-spacing: 0.05em !important; margin-top: 4px; }
    
    .iw-icon-circle { display: flex; align-items: center; justify-content: center; width: 32px; height: 32px; border-radius: 9999px; margin-bottom: 12px; }
    .iw-icon-circle.indigo { background-color: var(--icon-indigo-bg); color: var(--icon-indigo); }
    .iw-icon-circle.amber { background-color: var(--icon-amber-bg); color: var(--icon-amber); }
    
    .iw-trend-badge { display: inline-flex; align-items: center; gap: 4px; font-size: 12px !important; font-weight: 600 !important; background-color: var(--trend-bg); padding: 4px 8px; border-radius: 9999px; margin-top: 8px; width: fit-content; }
    
    .iw-uv-bar-wrap { width: 100%; height: 6px; background-color: var(--scale-bg); border-radius: 9999px; margin-top: 12px; position: relative; }
    .iw-uv-bar-bg { display: flex; width: 100%; height: 100%; border-radius: 9999px; overflow: hidden; }
    .iw-uv-green { flex: 3; background-color: var(--trend-green); }
    .iw-uv-amber { flex: 3; background-color: var(--icon-amber); }
    .iw-uv-red { flex: 5; background-color: var(--trend-red); }
    .iw-uv-marker { position: absolute; top: 50%; transform: translateY(-50%); width: 6px; height: 12px; background-color: white; border: 1px solid #d1d5db; border-radius: 9999px; box-shadow: 0 1px 2px rgba(0,0,0,0.1); transition: left 0.5s ease; }
    #isolated-weather-widget.is-dark .iw-uv-marker { background-color: #1f2937; border-color: #4b5563; }
    
    .iw-switch { position: relative; display: inline-block; width: 36px; height: 20px; }
    .iw-switch input { opacity: 0; width: 0; height: 0; }
    .iw-slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: var(--text-muted); transition: .4s; border-radius: 20px; }
    .iw-slider:before { position: absolute; content: ""; height: 16px; width: 16px; left: 2px; bottom: 2px; background-color: white; transition: .4s; border-radius: 50%; }
    .iw-switch input:checked + .iw-slider { background-color: var(--map-sensor); }
    .iw-switch input:checked + .iw-slider:before { transform: translateX(16px); }
    
    .gauge-label { font-size: 8px !important; font-weight: 300 !important; fill: var(--text-secondary) !important; user-select: none !important; }
    .gauge-marker { stroke-linecap: round; }
    
    /* Dedicated CSS for the tick bubbles */
    .gauge-tick-bubble {
        fill: var(--bg-panel);
        stroke: var(--track-bg);
        stroke-width: 0.5px;
    }
    #isolated-weather-widget.is-dark .gauge-tick-bubble,
    #isolated-weather-widget.map-mode .gauge-tick-bubble {
        stroke: var(--track-bg) !important;
    }
    
    #icon-weather { width: 56px; height: 56px; }
    @media (min-width: 640px) { #icon-weather { width: 72px; height: 72px; } }
    
    .animate-float { animation: float 6s ease-in-out infinite; }
    @keyframes float { 0% { transform: translateY(0px); } 50% { transform: translateY(-10px); } 100% { transform: translateY(0px); } }
    .animate-spin-slow { animation: spin 8s linear infinite; }
    @keyframes spin { from { transform: rotate(0deg); } to { transform: rotate(360deg); } }
</style>

<div id="isolated-weather-widget">
    <div class="iw-main-row">
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
                    <div class="iw-justify-between iw-items-center" style="padding: 0 8px;">
                        <div class="iw-flex-col">
                            <div class="iw-temp-label">
                                <svg style="width: 14px; height: 14px; color: #3b82f6;" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M14 14.76V3.5a2.5 2.5 0 0 0-5 0v11.26a4.5 4.5 0 1 0 5 0z"/></svg>
                                <span>Current</span>
                            </div>
                            <h1 id="val-temp-f" class="iw-temp-val-f">--&deg;F</h1>
                            <p id="val-temp-c" class="iw-temp-val-c">--&deg;C</p>
                        </div>
                        <div class="iw-flex-col iw-items-center" style="padding-top: 4px;">
                            <div id="icon-weather" class="animate-float"></div>
                            <p id="val-conditions" class="iw-cond-text">--</p>
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
</div>

<script>
    /* #raw */
    // 1. API Configuration
    const STATIC_TOKEN = "8535e71d-2290-4965-ad3f-ab05b9294fdf";
    const MAPBOX_TOKEN = "TOKEN_HERE";
    const STATION_ID = "127241";
    const DEVICE_ID = "314522";
    
    let wsSocket = null;
    let obsHistory = []; // Stores rolling 10-minute history

    const API_OBS_BASE = `https://swd.weatherflow.com/swd/rest/observations/stn/${STATION_ID}`;
    const API_FCST_BASE = `https://swd.weatherflow.com/swd/rest/better_forecast?station_id=${STATION_ID}&units_wind=kts&token=${STATIC_TOKEN}`;

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
            if (!state) return false;
            
            let isRestored = false;
            if (state.obs) {
                // Pass true so update knows to make the transition 0ms
                update(state.obs, true);
                isRestored = true;
            }
            
            if (state.tempF) { const el = document.getElementById('val-temp-f'); if(el) el.innerText = state.tempF; }
            if (state.tempC) { const el = document.getElementById('val-temp-c'); if(el) el.innerText = state.tempC; }
            if (state.pressure) { const el = document.getElementById('val-pressure'); if(el) el.innerText = state.pressure; }
            if (state.uv) {
                const uvEl = document.getElementById('val-uv');
                if (uvEl) uvEl.innerText = state.uv;
                const marker = document.getElementById('uv-marker');
                if (marker) {
                    marker.classList.remove('hidden');
                    marker.style.left = `calc(${Math.min((state.uv / 11) * 100, 100)}% - 3px)`;
                }
            }
            if (state.fcst) {
                const condEl = document.getElementById('val-conditions');
                if (condEl) condEl.innerText = state.fcst.conditions || '--';
                const iconEl = document.getElementById('icon-weather');
                if (iconEl) iconEl.innerHTML = weatherIcons[state.fcst.icon] || '';
                const trendEl = document.getElementById('val-pressure-trend');
                if (trendEl) trendEl.innerHTML = trendIcons[state.fcst.trend] || '';
            }
            if (state.mapMode) {
                const toggle = document.getElementById('map-mode-toggle');
                if (toggle) toggle.checked = true;
                const widget = document.getElementById('isolated-weather-widget');
                if (widget) widget.classList.add('map-mode');
                setTimeout(() => map.invalidateSize(), 100);
            }
            
            return isRestored;
        } catch (e) { 
            console.warn("Local storage load failed:", e); 
            return false; 
        }
    };

    // 4. Map Implementation
    const SENSOR_COORD = [37.85568, -122.31445];
    const MAP_CENTER = [37.85868, -122.31445]; 
    
    // Define a bounding box matching the ideal desktop view so it scales perfectly on smaller screens
    const IDEAL_BOUNDS = L.latLngBounds(
        [37.85018, -122.32445], // South-West corner
        [37.86718, -122.30445]  // North-East corner (captures the clubhouse)
    );

    const map = L.map('iw-map-container', {
        zoomSnap: 0.01, // Allow very fine fractional zoom levels for smooth scaling
        zoomControl: false, attributionControl: false,
        dragging: false, scrollWheelZoom: false, doubleClickZoom: false, boxZoom: false, touchZoom: false
    }).fitBounds(IDEAL_BOUNDS, { animate: false, padding: [0, 0] });

    // Automatically fix Leaflet rendering issues when the responsive layout resizes the container
    new ResizeObserver(() => {
        map.invalidateSize();
        // Use fitBounds so the exact same map area stays visible, dynamically scaling down
        map.fitBounds(IDEAL_BOUNDS, { animate: false, padding: [0, 0] }); 
    }).observe(document.getElementById('iw-map-container'));

    // Custom Cached TileLayer to minimize Mapbox API calls
    L.TileLayer.Cached = L.TileLayer.extend({
        createTile: function (coords, done) {
            const tile = document.createElement('img');
            tile.crossOrigin = 'Anonymous';
            tile.alt = '';
            const url = this.getTileUrl(coords);

            if ('caches' in window) {
                caches.match(url).then(response => {
                    if (response) {
                        // Serve instantly from browser cache API
                        response.blob().then(blob => {
                            tile.onload = () => done(null, tile);
                            tile.onerror = err => done(err, tile);
                            tile.src = URL.createObjectURL(blob);
                        });
                    } else {
                        // Fetch from Mapbox API and cache it for next time
                        fetch(url).then(res => {
                            if (!res.ok) throw new Error("Network response was not ok");
                            // Clone the response BEFORE using it (e.g. before reading the blob)
                            const resClone = res.clone();
                            caches.open('mapbox-tiles').then(cache => cache.put(url, resClone));
                            return res.blob();
                        }).then(blob => {
                            tile.onload = () => done(null, tile);
                            tile.onerror = err => done(err, tile);
                            tile.src = URL.createObjectURL(blob);
                        }).catch(() => {
                            // Fallback to normal loading if fetch intercept fails
                            tile.onload = () => done(null, tile);
                            tile.onerror = err => done(err, tile);
                            tile.src = url;
                        });
                    }
                });
            } else {
                tile.onload = () => done(null, tile);
                tile.onerror = err => done(err, tile);
                tile.src = url;
            }
            return tile;
        }
    });
    L.tileLayer.cached = function (url, options) { return new L.TileLayer.Cached(url, options); };

    // Implement Mapbox using provided public access token and new cached layer
    L.tileLayer.cached(`https://api.mapbox.com/styles/v1/mapbox/satellite-v9/tiles/256/{z}/{x}/{y}@2x?access_token=${MAPBOX_TOKEN}`, {
       maxZoom: 20,
       attribution: '&copy; <a href="https://www.mapbox.com/about/maps/">Mapbox</a>'
    }).addTo(map);

    // Create a pure-code SVG replica of the clubhouse to prevent broken image links
    const cscSvg = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 100 70">
        <rect x="10" y="15" width="80" height="55" fill="#10A5A8" stroke="#0A7A7D" stroke-width="2"/>
        <rect x="8" y="10" width="84" height="5" fill="#FFFFFF" stroke="#CBD5E1" stroke-width="1"/>
        <rect x="62" y="22" width="22" height="48" fill="#FFFFFF" stroke="#CBD5E1" stroke-width="1"/>
        <rect x="65" y="25" width="16" height="45" fill="#964736" stroke="#6E3224" stroke-width="1"/>
        <rect x="67" y="27" width="12" height="18" fill="#823B2A"/>
        <rect x="67" y="47" width="12" height="20" fill="#823B2A"/>
        <circle cx="68" cy="44" r="1.5" fill="#FDE047"/>
        <rect x="15" y="25" width="40" height="25" fill="#FFFFFF" stroke="#CBD5E1" stroke-width="1"/>
        <rect x="18" y="28" width="16" height="10" fill="#FBBF24"/>
        <rect x="36" y="28" width="16" height="10" fill="#FBBF24"/>
        <rect x="18" y="39" width="16" height="8" fill="#FBBF24"/>
        <rect x="36" y="39" width="16" height="8" fill="#FBBF24"/>
        <rect x="8" y="52" width="54" height="4" fill="#BD7545" stroke="#73411E" stroke-width="1"/>
        <rect x="8" y="59" width="54" height="4" fill="#BD7545" stroke="#73411E" stroke-width="1"/>
        <rect x="12" y="63" width="4" height="7" fill="#A65317"/>
        <rect x="28" y="63" width="4" height="7" fill="#A65317"/>
        <rect x="44" y="63" width="4" height="7" fill="#A65317"/>
        <rect x="58" y="63" width="4" height="7" fill="#A65317"/>
        <ellipse cx="50" cy="10" rx="25" ry="10" fill="#2563EB" stroke="#1E40AF" stroke-width="2"/>
        <text x="50" y="14" font-family="Arial, sans-serif" font-weight="900" font-size="12" fill="white" text-anchor="middle">CSC</text>
    </svg>`;

    // Add the tiny clubhouse icon
    const clubhouseIcon = L.icon({
        iconUrl: 'data:image/svg+xml;charset=UTF-8,' + encodeURIComponent(cscSvg),
        iconSize: [40, 28], // Very small
        iconAnchor: [20, 14] // Centered on the coordinates
    });
    // Moved further North
    L.marker([37.863580, -122.313550], {icon: clubhouseIcon}).addTo(map);

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
    const R = { speedTrack: 142, compass: 129 };
    const SWEEP_START = -0.75 * Math.PI, SWEEP_END = 0.75 * Math.PI;
    let currentMaxSpeed = 30;

    const svg = d3.select("#gauge-mount").append("svg")
        .attr("viewBox", `0 25 330 284`)
        .style("width", "100%").style("height", "auto").style("display", "block").style("overflow", "visible")
        .append("g").attr("transform", `translate(${center.x},${center.y})`);

    const colorScale = d3.scaleLinear().domain([0, 8, 10, 13, 15, 18, 20, 30, 40, 50]).range(["#1e3a8a", "#3b82f6", "#22c55e", "#84cc16", "#eab308", "#f97316", "#ef4444", "#991b1b", "#7f1d1d", "#450a0a"]).clamp(true);
    const speedScale = d3.scaleLinear().domain([0, currentMaxSpeed]).range([SWEEP_START, SWEEP_END]);
    
    // Background track with 0.7 opacity
    svg.append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_END})
        .attr("d", d3.arc().innerRadius(R.speedTrack - 12).outerRadius(R.speedTrack))
        .attr("fill", "var(--track-bg)")
        .attr("class", "gauge-bg-track")
        .attr("opacity", 0.7);
    
    const d3defs = svg.append("defs");
    const speedMaskPath = d3defs.append("clipPath").attr("id", "speed-mask").append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_START});
    const gustMaskPath = d3defs.append("clipPath").attr("id", "gust-mask").append("path").datum({startAngle: SWEEP_START, endAngle: SWEEP_START});
    
    d3defs.append("mask").attr("id", "bottom-bubble-cutout").attr("maskUnits", "userSpaceOnUse").attr("x", -200).attr("y", -200).attr("width", 400).attr("height", 400).append("rect").attr("x", -200).attr("y", -200).attr("width", 400).attr("height", 400).attr("fill", "white");
    d3.select("#bottom-bubble-cutout").append("circle").attr("cx", 0).attr("cy", 0).attr("r", 33).attr("fill", "black");
    
    const gustTrackGroup = svg.append("g").attr("clip-path", "url(#gust-mask)").attr("opacity", 0.3).attr("class", "gauge-gust-track");
    const colorTrackGroup = svg.append("g").attr("clip-path", "url(#speed-mask)").attr("class", "gauge-color-track");
    const tickGroup = svg.append("g").attr("class", "gauge-tick-group");
    const arcSpeed = d3.arc().innerRadius(R.speedTrack - 12).outerRadius(R.speedTrack);
    
    const lullMarker = svg.append("line").attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 12)).attr("stroke", "#60a5fa").attr("stroke-width", 3).attr("class", "gauge-marker");
    const speedMarker = svg.append("line").attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 12)).attr("stroke", "#22c55e").attr("stroke-width", 3).attr("class", "gauge-marker");
    const gustMarker = svg.append("line").attr("x1", 0).attr("y1", -R.speedTrack).attr("x2", 0).attr("y2", -(R.speedTrack - 12)).attr("stroke", "#ef4444").attr("stroke-width", 3).attr("class", "gauge-marker");

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
            const textRadius = R.speedTrack + 7; // Place numbers tightly outside the track
            const cx = textRadius * Math.sin(angle);
            const cy = -textRadius * Math.cos(angle);
            
            // Tighter rounded rectangle (12x10) centered under the text
            tickGroup.append("rect").attr("x", cx - 6).attr("y", cy - 5).attr("width", 12).attr("height", 10).attr("rx", 1.5).attr("ry", 1.5).attr("class", "gauge-tick-bubble");
            
            // Precise dy="0.3em" for perfect optical cap-height centering
            tickGroup.append("text").attr("x", cx).attr("y", cy).attr("class", "gauge-label").attr("text-anchor", "middle").attr("dy", "0.3em").text(v);
        }
    }
    drawSpeedTrack(currentMaxSpeed);

    const compassTicks = svg.append("g").attr("class", "compass-ticks");
    const cardinalLabels = { 0: 'N', 90: 'E', 180: 'S', 270: 'W' };
    for (let i = 0; i < 360; i += 22.5) {
        const angle = (i * Math.PI) / 180, isMajor = i % 90 === 0;
        compassTicks.append("line").attr("x1", R.compass * Math.sin(angle)).attr("y1", -R.compass * Math.cos(angle)).attr("x2", (R.compass - (isMajor ? 10 : 7)) * Math.sin(angle)).attr("y2", -(R.compass - (isMajor ? 10 : 7)) * Math.cos(angle)).attr("stroke", "var(--grey-tick)").attr("stroke-width", 1); 
        if (isMajor) {
            compassTicks.append("text").attr("x", (R.compass - 19) * Math.sin(angle)).attr("y", -(R.compass - 19) * Math.cos(angle)).attr("text-anchor", "middle").attr("dy", "0.35em").style("font-size", "11px").style("font-weight", "300").attr("fill", "var(--compass-text)").text(cardinalLabels[i]);
        }
    }

    const pointer = svg.append("g"), vane = pointer.append("path").attr("d", "M 0,127 L 71.5,-105 L 0,-79 L -71.5,-105 Z").attr("opacity", 0.7);
    
    // Elevate speed labels so the directional vane doesn't obscure them (compass ticks stay behind)
    tickGroup.raise(); 

    const bottomBubbleWrapper = svg.append("g").attr("mask", "url(#bottom-bubble-cutout)"), bottomBubble = bottomBubbleWrapper.append("g");
    bottomBubble.append("circle").attr("cx", 0).attr("cy", -50).attr("r", 21).attr("fill", "var(--bubble-fill)").attr("fill-opacity", "var(--bubble-opacity)");
    const dirTextGroup = bottomBubble.append("g").attr("transform", "translate(0, -50)");
    const dirReadout = dirTextGroup.append("text").attr("y", -5).style("font-size", "10px").style("font-weight", "900").attr("fill", "var(--text-primary)").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("---");
    const dirAngle = dirTextGroup.append("text").attr("y", 7).style("font-size", "9px").style("font-weight", "500").attr("fill", "var(--text-primary)").attr("text-anchor", "middle").attr("dominant-baseline", "central").text("---\xB0");
    
    // Create new opposite bubble for Lull and Gust
    const oppBubbleWrapper = svg.append("g").attr("mask", "url(#bottom-bubble-cutout)"), oppBubble = oppBubbleWrapper.append("g");
    oppBubble.append("circle").attr("cx", 0).attr("cy", 46).attr("r", 18).attr("fill", "var(--bubble-fill)").attr("fill-opacity", "var(--bubble-opacity)");
    
    // Shift the anchor point 2px radially outward (to perfectly center it in the crescent)
    const oppTextGroup = oppBubble.append("g").attr("transform", "translate(0, 48)");
    
    // Balance the text above and below the new center anchor
    oppTextGroup.append("text").attr("y", -4.5).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "6.5px").style("font-weight", "300").attr("fill", "var(--text-secondary)").text("gusting");
    
    const oppRangeText = oppTextGroup.append("text").attr("y", 4.5).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "6.5px").style("font-weight", "300").attr("fill", "var(--text-primary)");
    const oppLullVal = oppRangeText.append("tspan").text("0");
    oppRangeText.append("tspan").text(" to ");
    const oppGustVal = oppRangeText.append("tspan").text("0");

    const topBubble = svg.append("g");
    topBubble.append("circle").attr("r", 32).attr("fill", "var(--bubble-fill)").attr("fill-opacity", "var(--bubble-opacity)");
    
    // Main wind speed readout (centered and maximized)
    const speedReadout = topBubble.append("text").attr("y", -2).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "46px").style("font-weight", "800").style("letter-spacing", "-1px").attr("fill", "var(--text-primary)").text("0");
    
    const unitsReadout = topBubble.append("text").attr("y", 24).attr("text-anchor", "middle").attr("dominant-baseline", "central").style("font-size", "11px").style("font-weight", "300").attr("fill", "var(--text-secondary)").text("kt");

    function update(data, isInstantRestore = false) {
        const l = data.lull || 0, s = data.speed || 0, g = data.gust || 0, d = data.direction || 0;
        let targetMax = 30; if (g > 40 || s > 40) targetMax = 50; else if (g > 30 || s > 30) targetMax = 40; if (targetMax !== currentMaxSpeed) drawSpeedTrack(targetMax);
        
        const duration = isInstantRestore ? 0 : 2000; 
        const t = d3.transition().duration(duration).ease(d3.easeCubicInOut);
        
        speedMaskPath.transition(t).attrTween("d", dat => { 
            const startAngle = dat.endAngle !== undefined ? dat.endAngle : (isInstantRestore ? speedScale(s) : SWEEP_START);
            const i = d3.interpolate(startAngle, speedScale(s)); 
            return time => { dat.endAngle = i(time); return d3.arc().innerRadius(R.speedTrack - 14).outerRadius(R.speedTrack + 2)(dat); }; 
        });
        gustMaskPath.transition(t).attrTween("d", dat => { 
            const startAngle = dat.endAngle !== undefined ? dat.endAngle : (isInstantRestore ? speedScale(g) : SWEEP_START);
            const i = d3.interpolate(startAngle, speedScale(g)); 
            return time => { dat.endAngle = i(time); return d3.arc().innerRadius(R.speedTrack - 14).outerRadius(R.speedTrack + 2)(dat); }; 
        });
        
        lullMarker.transition(t).attr("transform", `rotate(${(speedScale(l) * 180) / Math.PI})`);
        speedMarker.transition(t).attr("transform", `rotate(${(speedScale(s) * 180) / Math.PI})`);
        gustMarker.transition(t).attr("transform", `rotate(${(speedScale(g) * 180) / Math.PI})`);
        pointer.transition(t).attr("transform", `rotate(${d})`);
        bottomBubble.transition(t).attr("transform", `rotate(${d})`);
        dirTextGroup.transition(t).attr("transform", `translate(0, -50) rotate(${-d})`);
        oppBubble.transition(t).attr("transform", `rotate(${d})`);
        
        // Also update the animation translation so it maintains the radial shift while moving
        oppTextGroup.transition(t).attr("transform", `translate(0, 48) rotate(${-d})`);
        
        vane.transition(t).attr("fill", colorScale(s));
        dirReadout.text(getCompassPoint(d));
        dirAngle.text(Math.round(d) + "\xB0");
        
        speedReadout.transition(t).style("font-size", Math.round(s) >= 10 ? "46px" : "52px").tween("text", function() { 
            const startVal = this._currentS !== undefined ? this._currentS : (isInstantRestore ? s : 0);
            const i = d3.interpolateNumber(startVal, s); 
            return time => { 
                this._currentS = i(time); 
                this.textContent = Math.round(this._currentS); 
            }; 
        });
        oppLullVal.transition(t).tween("text", function() { 
            const startVal = this._currentL !== undefined ? this._currentL : (isInstantRestore ? l : 0);
            const i = d3.interpolateNumber(startVal, l); 
            return time => { this._currentL = i(time); this.textContent = Math.round(this._currentL); }; 
        });
        oppGustVal.transition(t).tween("text", function() { 
            const startVal = this._currentG !== undefined ? this._currentG : (isInstantRestore ? g : 0);
            const i = d3.interpolateNumber(startVal, g); 
            return time => { this._currentG = i(time); this.textContent = Math.round(this._currentG); }; 
        });
        
        // Do not re-save to local storage if we are just instantly restoring FROM it.
        if (!isInstantRestore) saveToLocalStorage({ obs: { lull: l, speed: s, gust: g, direction: d } });
    }

    // 6. WebSocket Connection and Data Logic 
    function update10MinAvg() {
        if (obsHistory.length === 0) return;
        const now = Math.floor(Date.now() / 1000);
        
        // Filter out readings older than 10 minutes (600 seconds) + a small grace period
        obsHistory = obsHistory.filter(ob => ob.time >= now - 660); 
        
        if (obsHistory.length === 0) return;

        let minLull = Infinity;
        let maxGust = -Infinity;
        let uSum = 0, vSum = 0, speedSum = 0;
        
        obsHistory.forEach(ob => {
            minLull = Math.min(minLull, ob.lull);
            maxGust = Math.max(maxGust, ob.gust);
            speedSum += ob.speed;
            
            // Calculate Vector Sum for Direction Average
            uSum += ob.speed * Math.sin(ob.dir * Math.PI / 180);
            vSum += ob.speed * Math.cos(ob.dir * Math.PI / 180);
        });
        
        const avgSpeed = speedSum / obsHistory.length;
        const avgDir = (Math.atan2(uSum, vSum) * 180 / Math.PI + 360) % 360;
        
        update({
            lull: minLull,
            speed: avgSpeed,
            gust: maxGust,
            direction: avgDir
        });
    }

    // Forecast is not available on websocket, so we still poll this occasionally
    async function fetchForecast() {
        try {
            const res = await fetch(API_FCST_BASE);
            if(res.ok) {
                const fcstData = await res.json();
                if (fcstData && fcstData.current_conditions) {
                    const cc = fcstData.current_conditions;
                    document.getElementById('val-conditions').innerText = cc.conditions || '--';
                    document.getElementById('icon-weather').innerHTML = weatherIcons[cc.icon] || weatherIcons['default'];
                    document.getElementById('val-pressure-trend').innerHTML = trendIcons[cc.pressure_trend] || '';
                    saveToLocalStorage({ fcst: { conditions: cc.conditions, icon: cc.icon, trend: cc.pressure_trend } });
                }
            }
        } catch (e) { console.error("Fcst error:", e); }
    }

    async function fetchInitialHistory() {
        const time_end = Math.floor(Date.now() / 1000);
        const time_start = time_end - 600; // Past 10 minutes
        const url = `${API_OBS_BASE}?time_start=${time_start}&time_end=${time_end}&bucket=1&token=${STATIC_TOKEN}`;
        try {
            const res = await fetch(url);
            if (res.ok) {
                const data = await res.json();
                if (data && data.obs) {
                    data.obs.forEach(ob => {
                        const time = ob[0];
                        // Ensure we don't duplicate a timestamp if WebSocket connected simultaneously
                        if (!obsHistory.some(o => o.time === time)) {
                            obsHistory.push({
                                time: time,
                                lull: ob[1] * 1.94384,
                                speed: ob[2] * 1.94384,
                                gust: ob[3] * 1.94384,
                                dir: ob[4]
                            });
                        }
                    });
                    update10MinAvg();
                }
            }
        } catch(e) { console.error("History fetch error:", e); }
    }

    async function initApp() {
        // Fetch forecast initially
        fetchForecast();
        setInterval(fetchForecast, 15 * 60 * 1000); // Update forecast every 15 mins

        // Pre-fill the array with the previous 10 minutes of REST data to 
        // make the math accurate instantly without waiting for the socket.
        await fetchInitialHistory();

        // Establish the Websocket Connection
        startWebsocket();
    }

    function startWebsocket() {
        const wsUrl = `wss://ws.weatherflow.com/swd/data?token=${STATIC_TOKEN}`;
        wsSocket = new WebSocket(wsUrl);

        wsSocket.onopen = () => {
            console.log("WebSocket connected. Listening for 60-second observation chunks.");
            // Send the standard 60-second listen payload.
            // Rapid wind (every 3 secs) was removed to provide the stable 10-min average.
            wsSocket.send(JSON.stringify({ type: "listen_start", device_id: DEVICE_ID, id: "listen_start" }));
        };

        wsSocket.onmessage = (event) => {
            const msg = JSON.parse(event.data);
            
            // obs_st updates every ~60s for standard telemetry
            if (msg.type === 'obs_st') {
                const ob = msg.obs[0];
                const time = ob[0];
                const lull = ob[1] * 1.94384; 
                const speed = ob[2] * 1.94384; 
                const gust = ob[3] * 1.94384; 
                const dir = ob[4];
                const pressure = ob[6];
                const tempC = ob[7];
                const uv = ob[10];

                // Push new data packet to history buffer and re-average the gauge
                if (!obsHistory.some(o => o.time === time)) {
                    obsHistory.push({ time, lull, speed, gust, dir });
                }
                update10MinAvg();

                // Update UI text panels
                if (tempC != null) {
                    const tempF = (tempC * 9/5) + 32;
                    document.getElementById('val-temp-f').innerText = `${tempF.toFixed(1)}\xB0F`;
                    document.getElementById('val-temp-c').innerText = `${tempC.toFixed(1)}\xB0C`;
                    saveToLocalStorage({ tempF: `${tempF.toFixed(1)}\xB0F`, tempC: `${tempC.toFixed(1)}\xB0C` });
                }
                if (pressure != null) {
                    document.getElementById('val-pressure').innerText = pressure.toFixed(1);
                    saveToLocalStorage({ pressure: pressure.toFixed(1) });
                }
                if (uv != null) {
                    document.getElementById('val-uv').innerText = uv.toFixed(1);
                    const marker = document.getElementById('uv-marker');
                    if(marker) { 
                        marker.classList.remove('hidden'); 
                        marker.style.left = `calc(${Math.min((uv / 11) * 100, 100)}% - 3px)`; 
                    }
                    saveToLocalStorage({ uv: uv.toFixed(1) });
                }
            }
        };

        wsSocket.onclose = () => {
            console.warn("WebSocket Closed. Attempting reconnect...");
            setTimeout(startWebsocket, 5000);
        };

        wsSocket.onerror = (error) => {
            console.error("WebSocket Error:", error);
            wsSocket.close(); // Force the onclose handler to fire and reconnect
        };
    }

    // 7. Initialize
    syncTheme();
    
    // Watch for theme changes dynamically (class changes on HTML tag)
    const themeObserver = new MutationObserver((mutations) => {
        mutations.forEach((mutation) => {
            if (mutation.attributeName === 'class') {
                syncTheme();
            }
        });
    });
    
    // Observe current document
    themeObserver.observe(document.documentElement, { attributes: true });
    
    // Try to observe parent document if embedded
    try {
        if (window.self !== window.top) {
            themeObserver.observe(window.parent.document.documentElement, { attributes: true });
        }
    } catch (e) { /* Ignore cross-origin errors */ }

    // Watch OS preference changes
    window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', syncTheme);
    
    // Attempt to load from cache
    const hasCachedData = loadFromLocalStorage();
    
    // ONLY init with zeros if there's no cache. Otherwise, loading from cache already painted the UI.
    if (!hasCachedData) {
        update({ lull: 0, speed: 0, gust: 0, direction: 0 }, true); 
    }

    initApp(); // Boot up the live process

    const mapToggle = document.getElementById('map-mode-toggle');
    if (mapToggle) {
        mapToggle.addEventListener('change', (e) => {
            const widget = document.getElementById('isolated-weather-widget');
            const isChecked = e.target.checked;
            if (isChecked) {
                if (widget) widget.classList.add('map-mode');
                setTimeout(() => map.invalidateSize(), 100);
            } else {
                if (widget) widget.classList.remove('map-mode');
            }
            saveToLocalStorage({ mapMode: isChecked });
        });
    }
    /* #end raw */
</script>

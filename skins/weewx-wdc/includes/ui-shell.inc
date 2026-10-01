<!--prettier-ignore-->
#encoding UTF-8
#errorCatcher Echo
#import datetime
#set $base_path = $Extras.get("base_path", "./")

<script
  type="module"
  src="https://1.www.s81c.com/common/carbon/web-components/version/v1.27.0/ui-shell.min.js"
></script>
<script
  type="module"
  src="https://1.www.s81c.com/common/carbon/web-components/version/v1.21.0/button.min.js"
></script>

<bx-header aria-label="Cal Sailing Club - $current.dateTime">
  <bx-header-menu-button
    button-label-active="Close menu"
    button-label-inactive="Open menu"
  ></bx-header-menu-button>
  <bx-header-name href="http://www.cal-sailing.org" prefix="">
    <!--prettier-ignore-->
    #if 'logo_image' in $Extras
    <img class="logo" src="https://status.cal-sailing.org/CSC-Logo.png" alt="$gettext('Logo')" />
    <!--prettier-ignore-->
    #else
      #include "includes/icons/wdc.svg"
    #end if

    <span part="prefix" class="bx--header__name--prefix"></span>
    Cal Sailing Club
  </bx-header-name>
  <bx-header-nav menu-bar-label="Cal Sailing Club Status - $current.dateTime">
    <bx-header-nav-item href="$get_base_path(path='index.html')"
      >$gettext("Today")</bx-header-nav-item
    >
    #if $show_yesterday
    <bx-header-nav-item href="$get_base_path(path='yesterday.html')"
      >$gettext("Yesterday")</bx-header-nav-item
    >
    #end if
    <bx-header-nav-item href="$get_base_path(path='week.html')"
      >$gettext("Week")</bx-header-nav-item
    >
    <bx-header-nav-item href="$get_base_path(path='month.html')"
      >$gettext("Month")</bx-header-nav-item
    >
    <bx-header-nav-item href="$get_base_path(path='year.html')"
      >$gettext("Year")</bx-header-nav-item
    >
  </bx-header-nav>
  <div id="header-global">
    <bx-btn kind="ghost" data-id="theme-toggle"
      ><svg
        class="hidden"
        data-id="theme-toggle-light-icon"
        xmlns="http://www.w3.org/2000/svg"
        width="24"
        height="24"
        viewBox="0 0 32 32"
      >
        <defs>
          <style>
            .cls-1 {
              fill: none;
            }
          </style>
        </defs>
        <rect x="15" y="2" width="2" height="5" />
        <rect
          x="21.6675"
          y="6.8536"
          width="4.958"
          height="1.9998"
          transform="translate(1.5191 19.3744) rotate(-45)"
        />
        <rect x="25" y="15" width="5" height="2" />
        <rect
          x="23.1466"
          y="21.6675"
          width="1.9998"
          height="4.958"
          transform="translate(-10.0018 24.1465) rotate(-45)"
        />
        <rect x="15" y="25" width="2" height="5" />
        <rect
          x="5.3745"
          y="23.1466"
          width="4.958"
          height="1.9998"
          transform="translate(-14.7739 12.6256) rotate(-45)"
        />
        <rect x="2" y="15" width="5" height="2" />
        <rect
          x="6.8536"
          y="5.3745"
          width="1.9998"
          height="4.958"
          transform="translate(-3.253 7.8535) rotate(-45)"
        />
        <path
          d="M16,12a4,4,0,1,1-4,4,4.0045,4.0045,0,0,1,4-4m0-2a6,6,0,1,0,6,6,6,6,0,0,0-6-6Z"
        />
        <rect
          data-name="&lt;Transparent Rectangle&gt;"
          class="cls-1"
          width="32"
          height="32"
        />
      </svg>

      <svg
        class="hidden"
        data-id="theme-toggle-dark-icon"
        xmlns="http://www.w3.org/2000/svg"
        width="24"
        height="24"
        viewBox="0 0 32 32"
      >
        <defs>
          <style>
            .cls-1 {
              fill: none;
            }
          </style>
        </defs>
        <title>asleep</title>
        <path
          d="M13.5025,5.4136A15.0755,15.0755,0,0,0,25.096,23.6082a11.1134,11.1134,0,0,1-7.9749,3.3893c-.1385,0-.2782.0051-.4178,0A11.0944,11.0944,0,0,1,13.5025,5.4136M14.98,3a1.0024,1.0024,0,0,0-.1746.0156A13.0959,13.0959,0,0,0,16.63,28.9973c.1641.006.3282,0,.4909,0a13.0724,13.0724,0,0,0,10.702-5.5556,1.0094,1.0094,0,0,0-.7833-1.5644A13.08,13.08,0,0,1,15.8892,4.38,1.0149,1.0149,0,0,0,14.98,3Z"
        />
        <rect
          data-name="&lt;Transparent Rectangle&gt;"
          class="cls-1"
          width="32"
          height="32"
        />
      </svg>
    </bx-btn>
  </div>




</bx-header>
<!-- =========================================================================
     CAL SAILING CLUB - MOBILE SUB-NAVIGATION SNIPPET
     Placement: Insert immediately below </bx-header> in your HTML/WeeWX template.
     ========================================================================= -->

<style id="csc-mobile-subnav-styles">
  /* --------------------------------------------------
     1. Design Tokens & Carbon-compatible Variables
     -------------------------------------------------- */
  :root {
    --csc-header-height: 3rem;  /* Matches Carbon <bx-header> 3rem (48px) */
    --csc-subnav-height: 44px;  /* Standard Carbon tab bar height */
    --csc-bg: #ffffff;
    --csc-border: #e0e0e0;
    --csc-text: #525252;
    --csc-text-hover: #161616;
    --csc-text-active: #0f62fe; /* Carbon Blue */
    --csc-tab-hover-bg: #f4f4f4;
    --csc-shadow: 0 2px 6px rgba(0, 0, 0, 0.08);
  }

  /* Dark mode support (System preference and Carbon g90/g100 themes) */
  @media (prefers-color-scheme: dark) {
    :root {
      --csc-bg: #161616;
      --csc-border: #393939;
      --csc-text: #c6c6c6;
      --csc-text-hover: #f4f4f4;
      --csc-text-active: #78a9ff;
      --csc-tab-hover-bg: #262626;
      --csc-shadow: 0 2px 8px rgba(0, 0, 0, 0.4);
    }
  }

  body[data-carbon-theme="g90"],
  body[data-carbon-theme="g100"],
  .bx--g90,
  .bx--g100 {
    --csc-bg: #161616;
    --csc-border: #393939;
    --csc-text: #c6c6c6;
    --csc-text-hover: #f4f4f4;
    --csc-text-active: #78a9ff;
    --csc-tab-hover-bg: #262626;
    --csc-shadow: 0 2px 8px rgba(0, 0, 0, 0.4);
  }

  /* --------------------------------------------------
     2. Strict Mobile Visibility (< 768px only)
     -------------------------------------------------- */
  #csc-mobile-subnav {
    display: none !important; /* Hidden completely on desktop & tablet */
  }

  @media (max-width: 768px) {
    #csc-mobile-subnav {
      display: block !important;
      position: fixed !important; /* Fixed at top: 3rem to lock right under bx-header */
      top: var(--csc-header-height, 3rem) !important;
      left: 0 !important;
      right: 0 !important;
      width: 100% !important;
      height: var(--csc-subnav-height) !important;
      background: var(--csc-bg) !important;
      border-bottom: 1px solid var(--csc-border) !important;
      box-shadow: var(--csc-shadow) !important;
      z-index: 7990 !important; /* Sits directly beneath Carbon <bx-header> (z-index: 8000) */
      overflow: hidden !important;
      box-sizing: border-box !important;
    }

    /* Push page content down so the fixed subnav does not cover the top card */
    .bx--content,
    main,
    #content,
    [role="main"] {
      margin-top: calc(var(--csc-header-height, 3rem) + var(--csc-subnav-height) + 12px) !important;
    }
  }

  /* --------------------------------------------------
     3. Scrollable Tab Container & Carbon Tab Styling
     -------------------------------------------------- */
  .csc-subnav-scroll {
    display: flex;
    align-items: stretch;
    height: 100%;
    padding: 0 6px;
    overflow-x: auto;
    overflow-y: hidden;
    white-space: nowrap;
    scroll-behavior: smooth;
    -webkit-overflow-scrolling: touch;
    scrollbar-width: none; /* Firefox */
    box-sizing: border-box;
  }

  .csc-subnav-scroll::-webkit-scrollbar {
    display: none; /* Safari and Chrome */
  }

  .csc-subnav-link {
    display: inline-flex;
    align-items: center;
    gap: 6px;
    padding: 0 14px;
    height: 100%;
    font-family: -apple-system, BlinkMacSystemFont, "IBM Plex Sans", "Segoe UI", Roboto, sans-serif;
    font-size: 13px;
    font-weight: 400;
    color: var(--csc-text);
    background: transparent;
    text-decoration: none;
    border: none;
    border-bottom: 2px solid transparent;
    transition: color 0.15s ease, background-color 0.15s ease, border-color 0.15s ease;
    flex-shrink: 0;
    user-select: none;
    -webkit-tap-highlight-color: transparent;
    cursor: pointer;
    box-sizing: border-box;
  }

  .csc-subnav-link svg {
    width: 14px;
    height: 14px;
    fill: currentColor;
    opacity: 0.85;
    flex-shrink: 0;
  }

  .csc-subnav-link:hover {
    background-color: var(--csc-tab-hover-bg);
    color: var(--csc-text-hover);
  }

  /* Active state matching Carbon Design System tabs */
  .csc-subnav-link.active {
    color: var(--csc-text-active);
    font-weight: 600;
    border-bottom: 2px solid var(--csc-text-active);
    background-color: transparent;
  }

  .csc-subnav-link.active svg {
    opacity: 1;
    fill: var(--csc-text-active);
  }

  /* --------------------------------------------------
     4. Scroll Margins to Prevent Sticky Header Overlap
     -------------------------------------------------- */
  #todays-conditions,
  #forecast,
  #tides-hours,
  #webcams,
  [data-csc-anchor="true"] {
    scroll-margin-top: calc(var(--csc-header-height, 3rem) + var(--csc-subnav-height) + 16px);
  }

  /* Extra mobile bottom breathing room so the last section can scroll up to the top */
  @media (max-width: 768px) {
    body {
      padding-bottom: 96px;
    }
  }
</style>

<!-- Mobile Sub-Navigation Bar -->
<nav id="csc-mobile-subnav" aria-label="Page Sections Navigation">
  <div class="csc-subnav-scroll" role="tablist">
    <!-- Today's Conditions -->
    <a href="#todays-conditions" class="csc-subnav-link active" data-target="todays-conditions" role="tab" aria-selected="true">
      <svg viewBox="0 0 16 16">
        <path d="M8 1a7 7 0 1 0 7 7A7.008 7.008 0 0 0 8 1zm0 13a6 6 0 1 1 6-6 6.007 6.007 0 0 1-6 6z"/>
        <path d="M7.5 4.5v3.25l2.25 1.5.5-.866-1.75-1.167V4.5z"/>
      </svg>
      <span>Today</span>
    </a>

    <!-- Forecast -->
    <a href="#forecast" class="csc-subnav-link" data-target="forecast" role="tab" aria-selected="false">
      <svg viewBox="0 0 16 16">
        <path d="M12 4.5a3.5 3.5 0 0 0-6.8-1.1A4.002 4.002 0 0 0 1 7.2 4 4 0 0 0 5 11h7a3 3 0 0 0 0-6z"/>
      </svg>
      <span>Forecast</span>
    </a>

    <!-- Tides & Hours -->
    <a href="#tides-hours" class="csc-subnav-link" data-target="tides-hours" role="tab" aria-selected="false">
      <svg viewBox="0 0 16 16">
        <path d="M14.5 9.5a2.5 2.5 0 0 1-2.5 2.5c-1.3 0-2-.8-3-1.8C8 9.2 7.3 8.5 6 8.5c-1.3 0-2 .8-3 1.8L2 11.2l-.7-.7.9-.9c1.2-1.2 2.2-2.1 3.8-2.1 1.3 0 2 .8 3 1.8 1 1 1.7 1.7 3 1.7 1 0 1.8-.8 1.8-1.5z"/>
        <path d="M14.5 5.5a2.5 2.5 0 0 1-2.5 2.5c-1.3 0-2-.8-3-1.8C8 5.2 7.3 4.5 6 4.5c-1.3 0-2 .8-3 1.8L2 7.2l-.7-.7.9-.9c1.2-1.2 2.2-2.1 3.8-2.1 1.3 0 2 .8 3 1.8 1 1 1.7 1.7 3 1.7 1 0 1.8-.8 1.8-1.5z"/>
      </svg>
      <span>Tides &amp; Hours</span>
    </a>

    <!-- Webcams -->
    <a href="#webcams" class="csc-subnav-link" data-target="webcams" role="tab" aria-selected="false">
      <svg viewBox="0 0 16 16">
        <path d="M14 4.5l-3 2.25V5a1 1 0 0 0-1-1H2a1 1 0 0 0-1 1v6a1 1 0 0 0 1 1h8a1 1 0 0 0 1-1V9.25l3 2.25z"/>
      </svg>
      <span>Webcams</span>
    </a>
  </div>
</nav>

<script id="csc-mobile-subnav-script">
  (function () {
    // 1. Dynamic Header Height & Content Offset
    function getHeaderHeight() {
      const header = document.querySelector('bx-header') || 
                           document.querySelector('.bx--header') || 
                           document.querySelector('[role="banner"]');
      return header ? header.offsetHeight : 48;
    }

    function syncHeaderLayout() {
      const h = getHeaderHeight();
      document.documentElement.style.setProperty('--csc-header-height', h + 'px');

      if (window.innerWidth <= 768) {
        const contentEl = document.querySelector('.bx--content') || 
                          document.querySelector('main') || 
                          document.querySelector('#content');
        if (contentEl) {
          contentEl.style.setProperty('margin-top', (h + 44 + 8) + 'px', 'important');
        }
      }
    }

    syncHeaderLayout();
    window.addEventListener('resize', syncHeaderLayout);
    window.addEventListener('orientationchange', syncHeaderLayout);

    // 2. Section Keyword Mapping & Auto-Anchoring
    // If the target elements don't already have these IDs, this automatically hooks into headings
    const sectionTargets = [
      { id: 'todays-conditions', keywords: ["today's conditions", "todays conditions", "today's", "today"] },
      { id: 'forecast', keywords: ["forecast"] },
      { id: 'tides-hours', keywords: ["club tides & hours", "tides & hours", "club tides", "tide", "hours"] },
      { id: 'webcams', keywords: ["webcam", "webcams", "webcams & radar"] }
    ];

    function resolveSectionElements() {
      sectionTargets.forEach(target => {
        let el = document.getElementById(target.id);
        if (!el) {
          const candidates = document.querySelectorAll('h1, h2, h3, h4, section, div');
          for (let node of candidates) {
            const text = (node.textContent || '').trim().toLowerCase();
            if (target.keywords.some(kw => text.startsWith(kw) || text === kw)) {
              node.id = target.id;
              node.setAttribute('data-csc-anchor', 'true');
              break;
            }
          }
        }
      });
    }

    if (document.readyState === 'loading') {
      document.addEventListener('DOMContentLoaded', resolveSectionElements);
    } else {
      resolveSectionElements();
    }

    // 3. Tab State Management & Auto-Centering
    const navBar = document.getElementById('csc-mobile-subnav');
    const navLinks = navBar.querySelectorAll('.csc-subnav-link');
    const scrollContainer = navBar.querySelector('.csc-subnav-scroll');
    let isClickScrolling = false;
    let clickTimeout = null;

    function activateTab(targetId) {
      let matchedLink = null;
      navLinks.forEach(link => {
        const matches = link.getAttribute('data-target') === targetId;
        link.classList.toggle('active', matches);
        link.setAttribute('aria-selected', matches ? 'true' : 'false');
        if (matches) matchedLink = link;
      });

      if (matchedLink && scrollContainer) {
        const linkLeft = matchedLink.offsetLeft;
        const linkWidth = matchedLink.offsetWidth;
        const containerWidth = scrollContainer.offsetWidth;
        scrollContainer.scrollTo({
          left: linkLeft - (containerWidth / 2) + (linkWidth / 2),
          behavior: 'smooth'
        });
      }
    }

    // 4. Smooth Tap-to-Scroll Handling with ScrollSpy Lock
    navLinks.forEach(link => {
      link.addEventListener('click', function (e) {
        const targetId = this.getAttribute('data-target');
        const targetElement = document.getElementById(targetId);

        if (targetElement) {
          e.preventDefault();
          isClickScrolling = true;
          clearTimeout(clickTimeout);

          activateTab(targetId);

          const headerH = getHeaderHeight();
          const subnavH = 44;
          const totalOffset = headerH + subnavH + 8;
          const targetY = targetElement.getBoundingClientRect().top + window.pageYOffset - totalOffset;

          window.scrollTo({
            top: Math.max(0, targetY),
            behavior: 'smooth'
          });

          // Re-enable scrollspy after scroll finishes
          clickTimeout = setTimeout(() => {
            isClickScrolling = false;
          }, 850);
        }
      });
    });

    // 5. ScrollSpy with Bottom-of-Page Detection
    function handleScroll() {
      if (isClickScrolling) return;

      // When user reaches near the bottom of the page, highlight the last section (Webcams)
      const scrollBottom = window.innerHeight + window.pageYOffset;
      const docHeight = document.documentElement.scrollHeight;
      if (scrollBottom >= docHeight - 45) {
        const lastTarget = sectionTargets[sectionTargets.length - 1];
        activateTab(lastTarget.id);
        return;
      }

      const headerH = getHeaderHeight();
      const subnavH = 44;
      const scrollThreshold = window.pageYOffset + headerH + subnavH + 40;

      let currentTargetId = sectionTargets[0].id;
      for (let i = 0; i < sectionTargets.length; i++) {
        const el = document.getElementById(sectionTargets[i].id);
        if (el && el.offsetTop <= scrollThreshold) {
          currentTargetId = sectionTargets[i].id;
        }
      }

      activateTab(currentTargetId);
    }

    window.addEventListener('scroll', handleScroll, { passive: true });
  })();
</script>




<bx-side-nav aria-label="Side navigation" collapse-mode="responsive">
  <bx-side-nav-items>
    <bx-side-nav-link
      class="show-small"
      href="$get_base_path(path='index.html')"
      ><span>$gettext("Today")</span></bx-side-nav-link
    >
    #if $show_yesterday
    <bx-side-nav-link
      class="show-small"
      href="$get_base_path(path='yesterday.html')"
      ><span>$gettext("Yesterday")</span></bx-side-nav-link
    >
    #end if
    <bx-side-nav-link class="show-small" href="$get_base_path(path='week.html')"
      ><span>$gettext("Week")</span></bx-side-nav-link
    >
    <bx-side-nav-link
      class="show-small"
      href="$get_base_path(path='month.html')"
      ><span>$gettext("Month")</span></bx-side-nav-link
    >
    <bx-side-nav-link class="show-small" href="$get_base_path(path='year.html')"
      ><span>$gettext("Year")</span></bx-side-nav-link
    >
    <bx-side-nav-divider class="show-small"></bx-side-nav-divider>
    <bx-side-nav-link href="$get_base_path(path='celestial.html')">
      <svg
        slot="title-icon"
        xmlns="http://www.w3.org/2000/svg"
        width="16"
        height="16"
        viewBox="0 0 32 32"
      >
        <defs>
          <style>
            .cls-1 {
              fill: none;
            }
          </style>
        </defs>
        <title>asleep</title>
        <path
          d="M13.5025,5.4136A15.0755,15.0755,0,0,0,25.096,23.6082a11.1134,11.1134,0,0,1-7.9749,3.3893c-.1385,0-.2782.0051-.4178,0A11.0944,11.0944,0,0,1,13.5025,5.4136M14.98,3a1.0024,1.0024,0,0,0-.1746.0156A13.0959,13.0959,0,0,0,16.63,28.9973c.1641.006.3282,0,.4909,0a13.0724,13.0724,0,0,0,10.702-5.5556,1.0094,1.0094,0,0,0-.7833-1.5644A13.08,13.08,0,0,1,15.8892,4.38,1.0149,1.0149,0,0,0,14.98,3Z"
        />
        <rect
          id="_Transparent_Rectangle_"
          data-name="&lt;Transparent Rectangle&gt;"
          class="cls-1"
          width="32"
          height="32"
        />
      </svg>
      <span>$gettext("Celestial")</span>
    </bx-side-nav-link>
    <bx-side-nav-link href="$get_base_path(path='statistics.html')">
      <svg
        slot="title-icon"
        width="16"
        height="16"
        xmlns="http://www.w3.org/2000/svg"
        viewBox="0 0 32 32"
      >
        <defs>
          <style>
            .cls-1 {
              fill: none;
            }
          </style>
        </defs>
        <title>analytics</title>
        <path d="M4,2H2V28a2,2,0,0,0,2,2H30V28H4Z" />
        <path
          d="M30,9H23v2h3.59L19,18.59l-4.29-4.3a1,1,0,0,0-1.42,0L6,21.59,7.41,23,14,16.41l4.29,4.3a1,1,0,0,0,1.42,0L28,12.41V16h2Z"
        />
        <rect
          id="_Transparent_Rectangle_"
          data-name="&lt;Transparent Rectangle&gt;"
          class="cls-1"
          width="32"
          height="32"
        />
      </svg>
      <span>$gettext("Statistics")</span>
    </bx-side-nav-link>

    <!--prettier-ignore-->
    #if $show_sensor_page
    <bx-side-nav-link href="$get_base_path(path='sensor-status.html')">
      <svg
        xmlns="http://www.w3.org/2000/svg"
        viewBox="0 0 32 32"
        slot="title-icon"
        width="16"
        height="16"
      >
        <defs>
          <style>
            .cls-1 {
              fill: none;
            }
          </style>
        </defs>
        <title>$gettext("Sensor Status")</title>
        <rect x="15" y="12" width="2" height="18" />
        <path d="M11.33,18.22a7,7,0,0,1,0-10.44l1.34,1.49a5,5,0,0,0,0,7.46Z" />
        <path
          d="M20.67,18.22l-1.34-1.49a5,5,0,0,0,0-7.46l1.34-1.49a7,7,0,0,1,0,10.44Z"
        />
        <path d="M8.4,21.8a11,11,0,0,1,0-17.6L9.6,5.8a9,9,0,0,0,0,14.4Z" />
        <path
          d="M23.6,21.8l-1.2-1.6a9,9,0,0,0,0-14.4l1.2-1.6a11,11,0,0,1,0,17.6Z"
        />
        <rect
          data-name="&lt;Transparent Rectangle&gt;"
          class="cls-1"
          width="32"
          height="32"
        />
      </svg>
      <span>$gettext("Sensor Status")</span>
    </bx-side-nav-link>
    #end if

    <!--prettier-ignore-->
    #if $show_cmon_page
    <bx-side-nav-link href="$get_base_path(path='computer-monitor.html')">
      <svg
        xmlns="http://www.w3.org/2000/svg"
        viewBox="0 0 32 32"
        slot="title-icon"
        width="16"
        height="16"
      >
        <defs>
          <style>
            .cls-1 {
              fill: none;
            }
          </style>
        </defs>
        <path
          d="M28,16v6H4V6h7V4H4A2,2,0,0,0,2,6V22a2,2,0,0,0,2,2h8v4H8v2H24V28H20V24h8a2,2,0,0,0,2-2V16ZM18,28H14V24h4Z"
          transform="translate(0 0)"
        />
        <path
          d="M18,18h-.01a1,1,0,0,1-.9511-.7253L15.2456,11H11V9h5a1,1,0,0,1,.9615.7252l1.0742,3.7589,3.0088-9.7783A1.0142,1.0142,0,0,1,22,3a.98.98,0,0,1,.9487.6838L24.7207,9H30v2H24a1,1,0,0,1-.9487-.6838l-1.0132-3.04L18.9556,17.2942A1,1,0,0,1,18,18Z"
          transform="translate(0 0)"
        />
        <rect
          data-name="&lt;Transparent Rectangle&gt;"
          class="cls-1"
          width="32"
          height="32"
        />
      </svg>
      <span>$gettext("Computer Monitor")</span>
    </bx-side-nav-link>
    #end if

    <!--prettier-ignore-->
    #for $static_page in $get_static_pages()
    <bx-side-nav-link href="$get_base_path(path=$static_page['link'])">
      <svg
        xmlns="http://www.w3.org/2000/svg"
        slot="title-icon"
        width="16"
        height="16"
        viewBox="0 0 32 32"
      >
        <defs>
          <style>
            .cls-1 {
              fill: none;
            }
          </style>
        </defs>
        <polygon
          points="17 22 17 14 13 14 13 16 15 16 15 22 12 22 12 24 20 24 20 22 17 22"
        />
        <path d="M16,8a1.5,1.5,0,1,0,1.5,1.5A1.5,1.5,0,0,0,16,8Z" />
        <path
          d="M16,30A14,14,0,1,1,30,16,14,14,0,0,1,16,30ZM16,4A12,12,0,1,0,28,16,12,12,0,0,0,16,4Z"
        />
        <rect class="cls-1" width="32" height="32" />
      </svg>
      <span>$gettext($static_page['title'])</span>
    </bx-side-nav-link>
    #end for

    <bx-side-nav-divider></bx-side-nav-divider>
    <bx-side-nav-link class="sidebar-heading"
      ><span>$gettext('Archive & NOAA Reports')</span></bx-side-nav-link
    >
    <!--prettier-ignore-->
    #set $archive_months = $SummaryByMonth
    #if len($SummaryByYear) == 0
    #set $SummaryByYear = $fake_get_report_years($alltime.start.format("%Y"), $latest.dateTime.format("%Y"))
    #end if
    <bx-side-nav-menu title="$gettext('Years')">
      #for $year in $SummaryByYear
      <bx-side-nav-menu-item
        href="$get_base_path(path='year-' + $str(year) + '.html')"
      >
        <b>$year</b>
      </bx-side-nav-menu-item>
      #end for
    </bx-side-nav-menu>
    <!--prettier-ignore-->
    #for $year in $SummaryByYear
    #set $months_for_year = $filter_months(archive_months, $year)
    <!--prettier-ignore-->
    <bx-side-nav-menu title="${year}">
      <!--prettier-ignore-->
      #for $month in $months_for_year
      <bx-side-nav-menu-item href="$get_base_path(path='month-' + $str(month) + '.html')">
        <span>$datetime.datetime.strptime($month, "%Y-%m").strftime("%B")</span>
      </bx-side-nav-menu-item>
      #end for
    </bx-side-nav-menu>
    <!--prettier-ignore-->
    #end for
  </bx-side-nav-items>
</bx-side-nav>

<script>
  // Add 'active' class to nav-items.
  const bxSideNavLinks = document.querySelectorAll(
    "bx-side-nav-link, bx-side-nav-menu-item"
  );

  bxSideNavLinks.forEach((element) => {
    if (
      element.getAttribute("href") &&
      window.location.pathname.includes(
        // Remove leading slash.
        element.getAttribute("href").replace(/^\/+/, "")
      )
    ) {
      element.setAttribute("active", true);
    }
  });
</script>

<script>
  var themeToggleDarkIcon = document.querySelectorAll(
    '[data-id="theme-toggle-dark-icon"]'
  );
  var themeToggleLightIcon = document.querySelectorAll(
    '[data-id="theme-toggle-light-icon"]'
  );

  // Change the icons inside the button based on previous settings
  if (
    localStorage.getItem("weewx.weewx_wdc.color-theme") === "dark" ||
    (!("weewx.weewx_wdc.color-theme" in localStorage) &&
      window.matchMedia("(prefers-color-scheme: dark)").matches)
  ) {
    document.documentElement.classList.add("dark");
    themeToggleLightIcon.forEach(function (element) {
      element.classList.remove("hidden");
    });
  } else {
    themeToggleDarkIcon.forEach(function (element) {
      element.classList.remove("hidden");
    });
  }

  var themeToggleBtn = document.querySelectorAll('[data-id="theme-toggle"]');

  themeToggleBtn.forEach(function (element) {
    element.addEventListener("click", function () {
      // toggle icons inside button
      themeToggleDarkIcon.forEach(function (element) {
        element.classList.toggle("hidden");
      });
      themeToggleLightIcon.forEach(function (element) {
        element.classList.toggle("hidden");
      });

      // if set via local storage previously
      if (localStorage.getItem("weewx.weewx_wdc.color-theme")) {
        if (localStorage.getItem("weewx.weewx_wdc.color-theme") === "light") {
          document.documentElement.classList.add("dark");
          localStorage.setItem("weewx.weewx_wdc.color-theme", "dark");
        } else {
          document.documentElement.classList.remove("dark");
          localStorage.setItem("weewx.weewx_wdc.color-theme", "light");
        }

        // if NOT set via local storage previously
      } else {
        if (document.documentElement.classList.contains("dark")) {
          document.documentElement.classList.remove("dark");
          localStorage.setItem("weewx.weewx_wdc.color-theme", "light");
        } else {
          document.documentElement.classList.add("dark");
          localStorage.setItem("weewx.weewx_wdc.color-theme", "dark");
        }
      }
    });
  });
</script>

<!--prettier-ignore-->
#if $DisplayOptions.get('layout', 'alternative') == 'classic'
<script>
  const switchSideNavCollapseMode = function () {
    if (window.matchMedia("(min-width: 672px)").matches) {
      document
        .querySelector("bx-side-nav")
        .setAttribute("collapse-mode", "rail");
    } else {
      document
        .querySelector("bx-side-nav")
        .setAttribute("collapse-mode", "responsive");
    }
  };

  switchSideNavCollapseMode();
  window.addEventListener("resize", switchSideNavCollapseMode);
</script>
#end if

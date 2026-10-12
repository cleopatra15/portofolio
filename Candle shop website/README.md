# Candle Website | E-Commerce Frontend

> A fully responsive, interactive e-commerce frontend interface for a boutique candle shop. Built entirely with pure HTML5, CSS3, and Vanilla JavaScript to demonstrate strong core web development fundamentals.

##  Overview

Candle Bliss is a multi-page web application showcasing a product catalog, dynamic shopping features, and an engaging user interface. Rather than relying on frameworks like React or Bootstrap, this project was built from scratch to demonstrate a deep understanding of DOM manipulation, CSS Grid/Flexbox architectures, browser storage, and asynchronous data fetching.

## ✨Key Features

* **Interactive Wishlist System:** Users can "heart" products across different pages. The wishlist is dynamically rendered and persists across sessions using the browser's `localStorage` API.
* **Pure CSS Animations:** Features a custom CSS-drawn candle with a continuous, keyframe-animated flickering flame (`flame-dance`), along with a fully CSS-driven image slider.
* **Dynamic Theme Switching:** Users can toggle the site's "Mood" (Original, Evening/Dark Mode, Morning), which dynamically injects CSS classes to alter the global color palette.
* **Asynchronous Data Loading:** Client reviews are fetched dynamically from a local `date.json` file using the JavaScript `Fetch API` and injected into the DOM.
* **Client-Side Authentication Mockup:** A lightweight login system that greets the user by name and persists their session via `localStorage`.
* **Responsive Architecture:** Fluid layouts built with CSS Grid and Flexbox, utilizing media queries to ensure a seamless experience across desktop, tablet, and mobile devices.

##  Technical Stack

* **HTML5:** Semantic markup, accessible forms, and multi-page routing.
* **CSS3:** 
  * Advanced layouts (`display: grid`, `display: flex`).
  * Modern styling techniques (backdrop filters, gradients, transitions).
  * Keyframe animations (`@keyframes`).
  * Responsive Design (`@media` queries, `clamp()`, relative units like `rem` and `vw`).
* **Vanilla JavaScript (ES6+):** 
  * DOM manipulation and Event Delegation.
  * Web Storage API (`localStorage.getItem()` / `setItem()`).
  * Asynchronous JavaScript (`fetch`, Promises).
  * Form validation using Regex.

##  Project Structure

* `candles.html` - The main landing page with hero animations and highlights.
* `colectii.html` & `oferte.html` - Product catalog pages categorized by collections.
* `articole.html` - A blog section with formatting for articles and reading content.
* `candles.css` - The global stylesheet governing the design system and animations.
* `candles.js` - The core logic engine for user interactions and state management.
* `date.json` - Mock database file for fetching customer reviews.

## 💻 How to Run

Because this project uses vanilla web technologies, no build steps or package managers (like npm) are required. 

1. Clone the repository.
2. Open `candles.html` directly in any modern web browser.
3. *Note: To test the "Load Reviews" (`fetch()`) functionality, you may need to run a local server (e.g., VS Code Live Server or Python's `python -m http.server`) due to browser CORS policies on local files.*

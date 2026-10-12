document.addEventListener("DOMContentLoaded", () => {

    // selectam elementele necesare dupa ID
    const loginBtn = document.getElementById("login-btn");
    const logoutBtn = document.getElementById("logout-btn");
    const usernameInput = document.getElementById("username");
    const loginControls = document.getElementById("login-controls");
    const userProfile = document.getElementById("user-profile");
    const welcomeMsg = document.getElementById("welcome-msg");
    
    const wishlistItems = document.getElementById("wishlist-items");
    const wishlistArea = document.getElementById("wishlist-area");
    const moodSelect = document.getElementById("mood-select");

    // function pentru actualizarea starii de autentificare
    function updateAuth() {
        const user = localStorage.getItem("user");
        
        if (user) {
            // daca utilizatorul este logat
            loginControls.style.display = "none";
            userProfile.style.display = "block";
            // mesaj de bun venit personalizat
            welcomeMsg.textContent = `Bun venit, ${user.charAt(0).toUpperCase() + user.slice(1)}!`;
        } else {
            // daca utilizatorul nu este logat
            loginControls.style.display = "block";
            userProfile.style.display = "none";
        }
    }

    // event listener pentru butonul de login
    loginBtn?.addEventListener("click", () => {
        // numele trebuie sa aiba cel putin 3 caractere
        const name = usernameInput.value.trim();
        if (name.length >= 3) {
            localStorage.setItem("user", name);
            updateAuth();
        } else {
            alert("Numele trebuie să aibă cel puțin 3 caractere.");
        }
    });

    // event listener pentru butonul de logout
    logoutBtn?.addEventListener("click", () => {
        localStorage.removeItem("user");
        updateAuth();
        
    });


    function verifWishlist() {
        const favs = JSON.parse(localStorage.getItem("wishlist") || "[]");
        
        //  verificăm toate inimile din pagină
        document.querySelectorAll(".wishlist-btn").forEach(btn => {
            const card = btn.closest(".collection-card");
            if (card) {
                const pName = card.querySelector("h3").textContent;
                
                if (favs.includes(pName)) {
                    btn.classList.add("active");
                } else {
                    btn.classList.remove("active");
                }
            }
        });

        if (!wishlistItems) return;
        wishlistItems.innerHTML = "";
        
        if (favs.length > 0) {
            wishlistArea.style.display = "block";
            favs.forEach((name, index) => {
                const item = document.createElement("div");
                item.className = "collection-card";
                item.innerHTML = `
                    <h4>${name}</h4>
                    <button class="btn1" onclick="removeItem(${index})">Elimină</button>
                `;
                wishlistItems.appendChild(item);
            });
        } else {
            wishlistArea.style.display = "none";
        }
    }

    
    window.removeItem = (index) => {
        let favs = JSON.parse(localStorage.getItem("wishlist") || "[]");
        favs.splice(index, 1);
        localStorage.setItem("wishlist", JSON.stringify(favs));
        verifWishlist(); // actualizeaza si inima si lista
    };

    // event listener pentru inimioare
    document.querySelectorAll(".wishlist-btn").forEach(btn => {
        btn.addEventListener("click", (e) => {
            e.stopPropagation(); // Prevenim propagarea evenimentului
            const pName = btn.closest(".collection-card").querySelector("h3").textContent;
            let favs = JSON.parse(localStorage.getItem("wishlist") || "[]");
            
            if (!favs.includes(pName)) {
                favs.push(pName);
            } else {
                favs = favs.filter(name => name !== pName);
            }
            
            localStorage.setItem("wishlist", JSON.stringify(favs));
            verifWishlist();
        });
    });

    // pt atmosfera  
    moodSelect?.addEventListener("change", (e) => {
        const mood = e.target.value;
        document.body.className = ""; // resetam clasele
        if (mood !== "original") {
            document.body.classList.add(`mood-${mood}`);
        }
        
        // afisam in consola culoarea fundalului 
        const computedBg = window.getComputedStyle(document.body).backgroundColor;
       
    });

    // efect flacara 
    setInterval(() => {
        const glow = Math.floor(Math.random() * 15) + 5; 
        const logoMark = document.querySelector(".logo-mark");
        if (logoMark) {
            logoMark.style.boxShadow = `0 0 ${glow}px rgba(255, 184, 95, 0.9)`;
        }
    }, 500);

    // recenzii
    document.getElementById("load-reviews")?.addEventListener("click", () => {
        fetch("date.json")
            .then(res => res.json())
            .then(data => {
                const container = document.getElementById("reviews-container");
                if (!container) return;
                container.innerHTML = "";
                data.recenzii.forEach(r => {
                    const rev = document.createElement("article");
                    rev.className = "article-card";
                    rev.innerHTML = `
                        <div class="article-content">
                            <h3>${r.utilizator}</h3>
                            <p>${r.comentariu}</p>
                            <span>${"⭐".repeat(r.stele)}</span>
                        </div>
                    `;
                    container.appendChild(rev);
                });
            })
            .catch(err => console.error("Eroare la încărcarea recenziilor:", err));
    });

    document.getElementById("delete-reviews")?.addEventListener("click", () => {
        const container = document.getElementById("reviews-container");
        if (container) container.innerHTML = "";
    });

  
    //validare formular
    const contactForm = document.querySelector(".contact-form");
    contactForm?.addEventListener("submit", (e) => {
        const emailInput = document.getElementById("email");
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

        if (!emailRegex.test(emailInput.value)) {
            e.preventDefault();
            emailInput.style.border = "2px solid #e74c3c";
            alert("Vă rugăm să introduceți o adresă de email validă!");
        }
    });

// data curenta 
    const footer = document.querySelector("footer");
    if (footer) {
        const acum = new Date();
        const infoFooter = document.createElement("p");
        infoFooter.textContent = `© ${acum.getFullYear()} Candle Bliss | ${acum.toLocaleDateString()}`;
        footer.appendChild(infoFooter);
    }

    document.addEventListener("keydown", (e) => {
        if (e.key === "Escape") {
            // inchidem wishlist-ul vizual daca apasam Escape
            if (wishlistArea) wishlistArea.style.display = "none";
            console.log("Acțiune anulată prin tasta Escape.");
            alert("Wishlist inchis cu Escape.");
        }
    });

   
    updateAuth();
    verifWishlist();
});
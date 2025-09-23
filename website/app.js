const PRODUCTS = [
  {id: 1, name: "Æble", price: 5.0, img: "https://upload.wikimedia.org/wikipedia/commons/1/15/Red_Apple.jpg"},
  {id: 2, name: "Banan", price: 6.0, img: "https://upload.wikimedia.org/wikipedia/commons/8/8a/Banana-Single.jpg"},
  {id: 3, name: "Gulerod", price: 2.0, img: "https://cdn.pixabay.com/photo/2016/04/15/11/18/carrot-1330216_960_720.jpg"}
];


let currentUser = null;

// ---------- Local Storage Helpers ----------
function loadUsers() { return JSON.parse(localStorage.getItem("users") || "[]"); }
function saveUsers(users) { localStorage.setItem("users", JSON.stringify(users)); }
function usernameExists(username) { return loadUsers().some(u => u.username.toLowerCase() === username.toLowerCase()); }

// ---------- Registration/Login ----------
document.getElementById("registerBtn").onclick = () => {
  const name = prompt("Enter full name:");
  if (!name) return alert("Name required!");
  let username;
  do {
    username = prompt("Choose a username:");
    if (usernameExists(username)) alert("Username already exists!");
  } while (usernameExists(username));
  const password = prompt("Set a password:");
  const coupon = parseFloat(prompt("Enter coupon % (0 if none):")) || 0;
  const users = loadUsers();
  const newUser = {name, username, password, coupon, balance: 1000, basket: []};
  users.push(newUser);
  saveUsers(users);
  alert("Registration complete!");
  loginUser(newUser);
};

document.getElementById("loginBtn").onclick = () => {
  const username = prompt("Enter username:");
  const password = prompt("Enter password:");
  const user = loadUsers().find(u => u.username.toLowerCase() === username.toLowerCase() && u.password === password);
  if (!user) return alert("Login failed!");
  loginUser(user);
};

// ---------- Shop Functions ----------
function loginUser(user) {
  currentUser = user;
  document.getElementById("login-register").classList.add("hidden");
  document.getElementById("shop").classList.remove("hidden");
  document.getElementById("welcome").innerText = `Welcome, ${currentUser.username}`;
  document.getElementById("balance").innerText = `Balance: ${currentUser.balance.toFixed(2)} DKK`;
  renderProducts();
  renderBasket();
  renderUserInfo();
}

function renderProducts() {
  const container = document.getElementById("products");
  container.innerHTML = "";
  PRODUCTS.forEach(p => {
    const div = document.createElement("div");
    div.className = "product-card";
    div.innerHTML = `
      <img src="${p.img}" alt="${p.name}">
      <strong>${p.name}</strong><br>
      ${p.price} DKK<br>
      <button onclick="addToBasket(${p.id})">Add to Basket</button>`;
    container.appendChild(div);
  });
}

function renderBasket() {
  const container = document.getElementById("basket");
  container.innerHTML = "";
  const counts = {};
  currentUser.basket.forEach(pid => counts[pid] = (counts[pid] || 0) + 1);
  let total = 0;
  for (let pid in counts) {
    const prod = PRODUCTS.find(p => p.id == pid);
    const qty = counts[pid];
    total += prod.price * qty;
    const div = document.createElement("div");
    div.innerText = `${prod.name} x${qty} - ${prod.price*qty} DKK`;
    container.appendChild(div);
  }
  total *= (1 - currentUser.coupon/100);
  const totalDiv = document.createElement("div");
  totalDiv.innerHTML = `<b>Total (with coupon ${currentUser.coupon}%): ${total.toFixed(2)} DKK</b>`;
  container.appendChild(totalDiv);
}

function addToBasket(pid) {
  currentUser.basket.push(pid);
  saveCurrentUser();
  renderBasket();
}

function saveCurrentUser() {
  const users = loadUsers();
  const index = users.findIndex(u => u.username === currentUser.username);
  if (index !== -1) users[index] = currentUser;
  saveUsers(users);
}

document.getElementById("payBtn").onclick = () => {
  let total = 0;
  const counts = {};
  currentUser.basket.forEach(pid => counts[pid] = (counts[pid] || 0) + 1);
  for (let pid in counts) total += PRODUCTS.find(p => p.id == pid).price * counts[pid];
  total *= (1 - currentUser.coupon/100);
  if (total > currentUser.balance) return alert("Insufficient balance!");
  currentUser.balance -= total;
  currentUser.basket = [];
  saveCurrentUser();
  renderBasket();
  document.getElementById("balance").innerText = `Balance: ${currentUser.balance.toFixed(2)} DKK`;
  alert("Payment successful!");
};

function renderUserInfo() {
  const container = document.getElementById("userInfo");
  container.innerHTML = `
    Name: ${currentUser.name}<br>
    Username: ${currentUser.username}<br>
    Coupon: ${currentUser.coupon}%<br>
    Balance: ${currentUser.balance.toFixed(2)} DKK
  `;
}

document.getElementById("logoutBtn").onclick = () => {
  saveCurrentUser();
  currentUser = null;
  document.getElementById("shop").classList.add("hidden");
  document.getElementById("login-register").classList.remove("hidden");
};

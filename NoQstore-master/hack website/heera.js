var config = {
    apiKey: "AIzaSyD_loh-ApuFmzl8ITjtlOe8MPdD4nWgTHg",
    authDomain: "sweetheart-934f2.firebaseapp.com",
    databaseURL: "https://sweetheart-934f2.firebaseio.com",
    projectId: "sweetheart-934f2",
    storageBucket: "sweetheart-934f2.appspot.com",
    messagingSenderId: "333811842516"
};

firebase.initializeApp(config);
user = "heera";
data = firebase.database().ref(user + "/cart/phone");
data.on("value", function (snap) {
    nu = document.getElementById("number")
    nu.innerText ="number :"+ snap.val();


});
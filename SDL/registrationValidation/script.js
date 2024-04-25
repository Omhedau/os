function validateForm(event) {
    event.preventDefault(); 

    const firstName = document.getElementById("firstName").value.trim();
    const lastName = document.getElementById("lastName").value.trim();
    const email = document.getElementById("email").value.trim();
    const password = document.getElementById("password").value;

    if (firstName === "") {
        displayErrorMessage("Please enter your first name.");
        return;
    }

    if (lastName === "") {
        displayErrorMessage("Please enter your last name.");
        return;
    }

    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailRegex.test(email)) {
        displayErrorMessage("Please enter a valid email address.");
        return;
    }

    if (password === "" || password.length > 6) {
        displayErrorMessage("Password must be at least 6 characters long.");
        return;
    }

    displaySuccessMessage("Registration successful! You can now log in.");
    document.getElementById("registrationForm").reset();
}

function displayErrorMessage(message) {
    document.getElementById("errorMessage").textContent = message;
    document.getElementById("successMessage").textContent = ""; 
}

function displaySuccessMessage(message) {
    document.getElementById("successMessage").textContent = message;
    document.getElementById("errorMessage").textContent = ""; 
}

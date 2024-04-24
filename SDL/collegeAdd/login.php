<?php
session_start(); // Start session to store logged-in user data

include 'db_connection.php'; // Include your database connection file

// Check if the form is submitted via POST method
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Retrieve form data
    $email = isset($_POST['email']) ? $_POST['email'] : '';
    $password = isset($_POST['password']) ? $_POST['password'] : '';

    // Validate input data
    if (!empty($email) && !empty($password)) {
        // Prepare SQL query to fetch student data by email
        $sql = "SELECT * FROM students WHERE email = '$email'";
        
        // Execute SQL query
        $result = $conn->query($sql);

        if ($result->num_rows > 0) {
            // Email found in the database
            $row = $result->fetch_assoc();
            $hashed_password = $row['password'];

            // Verify password
            if (password_verify($password, $hashed_password)) {
                
                $_SESSION['student_id'] = $row['id'];
                $_SESSION['student_name'] = $row['name'];

                header("Location: profile.php");
                exit();
            } else {
                // Password does not match
                echo "<div class='error-message'><h1>Password incorrect</h1></div>";
            }
        } else {
            // Email not found in the database
            echo "<div class='error-message'><h1>No student with this email</h1></div>";
        }
    } else {
        // If any required field is empty, display an error message
        echo "<div class='error-message'><h1>Email and password are required</h1></div>";
    }
} else {
    // If the request method is not POST, redirect to the login form page
    header("Location: loginForm.html");
    exit();
}
?>

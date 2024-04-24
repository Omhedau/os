<?php
session_start(); // Start session to access logged-in user data

// Check if the user is logged in
if (!isset($_SESSION['student_id'])) {
    // If not logged in, redirect to the login page
    header("Location: loginForm.html");
    exit();
}

include 'db_connection.php'; // Include your database connection file

// Retrieve logged-in user data from session
$student_id = $_SESSION['student_id'];

// Prepare SQL query to fetch student data by ID
$sql = "SELECT * FROM students WHERE id = $student_id";

// Execute SQL query
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // Student data found
    $row = $result->fetch_assoc();
    $name = $row['name'];
    $email = $row['email'];
    $mobile = $row['mobile_number'];
    $dob = $row['date_of_birth'];
    $address = $row['address'];
    $city = $row['city'];
    $state = $row['state'];
    $country = $row['country'];
    $pincode = $row['pincode'];
    $gender = $row['gender'];

    // Display student details
    echo "<h1>Welcome, $name!</h1>";
    echo "<p>Email: $email</p>";
    echo "<p>Mobile Number: $mobile</p>";
    echo "<p>Date of Birth: $dob</p>";
    echo "<p>Address: $address, $city, $state, $country - $pincode</p>";
    echo "<p>Gender: $gender</p>";

    // Add any additional details you want to display
} else {
    // Student data not found
    echo "<p>No student found with this ID</p>";
}

$conn->close(); 
?>

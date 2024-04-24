<?php
include 'db_connection.php'; // Include your database connection file

// Check if the form is submitted via POST method
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Retrieve form data
    $name = isset($_POST['name']) ? $_POST['name'] : '';
    $email = isset($_POST['email']) ? $_POST['email'] : '';
    $password = isset($_POST['password']) ? $_POST['password'] : ''; 
    $mobile = isset($_POST['mobile']) ? $_POST['mobile'] : '';
    $dob = isset($_POST['dob']) ? $_POST['dob'] : '';
    $address = isset($_POST['address']) ? $_POST['address'] : '';
    $city = isset($_POST['city']) ? $_POST['city'] : '';
    $state = isset($_POST['state']) ? $_POST['state'] : '';
    $country = isset($_POST['country']) ? $_POST['country'] : '';
    $pincode = isset($_POST['pincode']) ? $_POST['pincode'] : '';
    $gender = isset($_POST['gender']) ? $_POST['gender'] : '';

    // Validate input data
    if (!empty($name) && !empty($email) && !empty($password) && !empty($mobile) && !empty($dob) && !empty($address) && !empty($city) && !empty($state) && !empty($country) && !empty($pincode) && !empty($gender)) {
        // Additional validation can be added here (e.g., email format, mobile number format)

        // Prepare SQL query to insert data into the database
        $hashed_password = password_hash($password, PASSWORD_DEFAULT); // Hash the password
        $sql = "INSERT INTO students (name, email, password, mobile_number, date_of_birth, address, city, state, country, pincode, gender) 
                VALUES ('$name', '$email', '$hashed_password', '$mobile', '$dob', '$address', '$city', '$state', '$country', '$pincode', '$gender')";

        try {
            // Execute SQL query
            if ($conn->query($sql) === TRUE) {
                echo "<div class='success-message'><h1>New record created successfully</h1></div>";
            } else {
                throw new Exception("Error: " . $conn->error);
            }
        } catch (Exception $e) {
            echo "<div class='error-message'><h1>" . $e->getMessage() . "</h1></div>";
        }
    } else {
        // If any required field is empty, display an error message
        echo "<div class='error-message'><h1>All fields are required</h1></div>";
    }
} else {
    // If the request method is not POST, redirect to the registration form page
    header("Location: registrationForm.html");
    exit();
}
?>

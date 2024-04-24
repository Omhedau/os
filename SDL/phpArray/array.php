<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Employee Search</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
            background-color: #f4f4f4;
        }
        .container {
            max-width: 600px;
            margin: 0 auto;
            background-color: #fff;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }
        h1 {
            color: #333;
            text-align: center;
        }
        form {
            margin-bottom: 20px;
        }
        input[type="text"] {
            width: 100%;
            padding: 10px;
            margin-bottom: 10px;
            border: 1px solid #ccc;
            border-radius: 5px;
            box-sizing: border-box;
        }
        input[type="submit"] {
            background-color: #007bff;
            color: #fff;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            transition: background-color 0.3s;
            width: 100%;
        }
        input[type="submit"]:hover {
            background-color: #0056b3;
        }
        .result {
            padding: 10px;
            border-radius: 5px;
            background-color: #f0f0f0;
            margin-bottom: 10px;
        }
        .employee-list {
            list-style-type: none;
            padding: 0;
            margin: 0;
        }
        .employee-list li {
            margin-bottom: 5px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Employee Search</h1>
        <form action="" method="post">
            <input type="text" name="search_name" placeholder="Enter name to search">
            <input type="submit" value="Search">
        </form>
        <?php
        // Indexed array of employee names
        $employee_names = array(
            "John",
            "Alice",
            "Bob",
            "Emily",
            "David",
            "Sarah",
            "Michael",
            "Emma",
            "James",
            "Olivia",
            "William",
            "Sophia",
            "Alexander",
            "Ava",
            "Daniel",
            "Mia",
            "Benjamin",
            "Charlotte",
            "Ethan",
            "Amelia"
        );

        // Check if form is submitted
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $search_name = isset($_POST['search_name']) ? $_POST['search_name'] : '';
            $matching_names = array();
            // Search for the given name in the array (case-insensitive)
            foreach ($employee_names as $name) {
                if ($search_name !== '' && stripos($name, $search_name) === 0) {
                    $matching_names[] = $name;
                }
            }
            // Display search result
            echo "<div class='result'>";
            if (!empty($matching_names)) {
                echo "<p><strong>Matching Employee Names:</strong></p>";
                echo "<ul class='employee-list'>";
                foreach ($matching_names as $match) {
                    echo "<li>$match</li>";
                }
                echo "</ul>";
            } else {
                echo "<p>No employee names match the starting characters of the search query.</p>";
            }
            echo "</div>";
        }
        ?>
        <div class="result">
            <p><strong>All Employee Names:</strong></p>
            <ul class="employee-list">
                <?php
                // Display all employee names
                foreach ($employee_names as $name) {
                    echo "<li>$name</li>";
                }
                ?>
            </ul>
        </div>
    </div>
</body>
</html>

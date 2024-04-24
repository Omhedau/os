function calculate() {
    // Retrieve the values from input fields
    const years = parseInt(document.getElementById("yearsInput").value);
    const name = document.getElementById("nameInput").value;

    // Calculate average number of weeks in a human lifetime
    const weeksInYear = 52;
    const averageWeeksInLifetime = years * weeksInYear;

    // Display the calculated value
    const outputElement = document.getElementById("output");
    outputElement.textContent = `Hello, ${name}! On average, you will live approximately ${averageWeeksInLifetime} weeks.`;
}

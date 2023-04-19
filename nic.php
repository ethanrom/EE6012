<style>
table {
  border-collapse: collapse;
  width: 100%;
}

th, td {
  padding: 8px;
  text-align: left;
  border-bottom: 1px solid #ddd;
}

th {
  background-color: #4CAF50;
  color: white;
}
</style>

<?php

// Connect to the database
$dbc = mysqli_connect('localhost', 'id20091113_root', 'Esoftmeterdb@1', 'id20091113_meterdb');

// Check the connection
if (!$dbc) {
    die("Connection failed: " . mysqli_connect_error());
}

// check if user has submitted a NIC
if(isset($_POST['nic'])){
    $nic = $_POST['nic'];

    // Select all rows from the sensordata table where nic matches user input
    $sql = "SELECT * FROM esoftproject WHERE nic='$nic'";
    $result = mysqli_query($dbc, $sql);

    // Check if the query was successful
    if (mysqli_num_rows($result) > 0) {
        // If the query was successful, create a table to display the data
        echo '<h1>Sensor Data</h1>';
        echo '<table>';
        echo '<tr><th>ID</th><th>NIC</th><th>Meter Value</th><th>Reading Time</th></tr>';
        // Add alternating row colors
        $row_color = '#eee';
        // Loop through the rows and display the data
        while ($row = mysqli_fetch_assoc($result)) {
            // Toggle the row color
            $row_color = ($row_color == '#eee') ? '#fff' : '#eee';
            echo '<tr style="background-color: ' . $row_color . '">';
            echo '<td>' . $row['id'] . '</td>';
            echo '<td>' . $row['nic'] . '</td>';
            echo '<td>' . $row['meter_value'] . '</td>';
            echo '<td>' . $row['reading_time'] . '</td>';
            echo '</tr>';
        }
        echo '</table>';
    } else {
        // If the query was not successful, display an error message
        echo "No records found for NIC: " . $nic;
    }
}
else{
    // display form to enter NIC
    echo '<form method="post" action="">';
    echo 'Enter NIC: <input type="text" name="nic"><br>';
    echo '<input type="submit" value="Submit">';
    echo '</form>';
}

// Close the connection
mysqli_close($dbc);

?>





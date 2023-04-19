<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <link href="https://fonts.googleapis.com/css?family=Poppins" rel="stylesheet" />
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.1.3/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/ionicons/2.0.1/css/ionicons.min.css">
    <link href="css/main.css" rel="stylesheet" />
  </head>
  <body>

    <div class="row">
      <div class="col-md-12 ">
        <div class="header">
          <h3><a href="#">Water Meter Reading System | demo nic 941531001V</a></h3>
       </div>
      </div>
    </div>

      <div class="s130">
      <form action="" method="post">
        <div class="row">
        <div class="inner-form">
          <div class="input-field first-wrap">
            <div class="svg-wrapper">
              <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24">
                <path d="M15.5 14h-.79l-.28-.27C15.41 12.59 16 11.11 16 9.5 16 5.91 13.09 3 9.5 3S3 5.91 3 9.5 5.91 16 9.5 16c1.61 0 3.09-.59 4.23-1.57l.27.28v.79l5 4.99L20.49 19l-4.99-5zm-6 0C7.01 14 5 11.99 5 9.5S7.01 5 9.5 5 14 7.01 14 9.5 11.99 14 9.5 14z"></path>
              </svg>
            </div>
            <input id="search" type="text" placeholder="Enter your NIC number" name="search" />
          </div>
          <div class="input-field second-wrap">
            <button class="btn-search" type="submit" name="submit">SEARCH</button>
          </div>
        </div>
        <span class="info"></span>
      </div>
      <div class="row">
        <div class="table-title">
          <h3>Meter Readings for $$</h3>
        </div>

<?php
if (isset($_POST['submit'])) {
    $searchValue = $_POST['search'];
    $mysqli = new mysqli("localhost", "id20091113_root", "Esoftmeterdb@1", "id20091113_meterdb");

    // Check for database connection errors
    if ($mysqli->connect_error) {
        die("Connection failed: " . $mysqli->connect_error);
    }

    // Prepare the SQL statement
    $stmt = $mysqli->prepare("SELECT DATE_FORMAT(`reading_time`, '%Y-%m-%d') AS date, MAX(`meter_value`) - MIN(`meter_value`) AS diff
                                FROM esoftproject
                                WHERE `nic` LIKE ?
                                GROUP BY DATE_FORMAT(`reading_time`, '%Y-%m-%d')
                                ORDER BY DATE_FORMAT(`reading_time`, '%Y-%m-%d') DESC");

    // Bind the search value to the prepared statement
    $stmt->bind_param("s", $searchValue);

    // Execute the prepared statement
    $stmt->execute();

    // Get the query result
    $result = $stmt->get_result();
    
    // Check for errors in the query execution
    if (!$result) {
        die("Query failed: " . $mysqli->error);
    }

    // Output the table
?>
    <table class="table-fill">
        <thead>
            <tr>
                <th class="text-left">Daily Units Consumption</th>
                <th class="text-left">Date</th>
                <th class="text-left">Daily Bill (Rs)</th>
            </tr>
        </thead>
        <tbody class="table-hover">
            <?php while ($row = $result->fetch_assoc()) { ?>
                <tr>
                    <td class="text-left">
                        <?php
                            $dailyUnits = $row['diff'];
                            echo abs($dailyUnits);
                        ?>
                    </td>
                    <td class="text-left">
                        <a href="records.php?date=<?php echo $row['date']; ?>"><?php echo $row['date']; ?></a>
                    </td>
                    <td class="text-left">
                        <?php
                            $dailyBill = $row['diff'] * 31.75;
                            echo abs($dailyBill);
                        ?>
                    </td>
                </tr>
            <?php } ?>
        </tbody>
    </table>

    <?php
    // Close the prepared statement and database connection
    $stmt->close();
    $mysqli->close();
} 
?>


    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.1.3/js/bootstrap.bundle.min.js"></script>
    <script src="js/extention/choices.js"></script>
  </body>


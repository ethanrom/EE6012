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
          <h3><a href="#">All records | demo nic 941531001V</a></h3>
       </div>
      </div>
    </div>

      
<?php
if(isset($_GET['date'])) {
  $date = $_GET['date'];
  $con = new mysqli("localhost","id20091113_root","Esoftmeterdb@1","id20091113_meterdb");
  if ($con->connect_error) {
    echo "connection Failed: " . $con->connect_error;
  } else {
    $sql = "SELECT nic, meter_value, reading_time FROM esoftproject WHERE date(reading_time) = '$date'";
    $result = $con->query($sql);
  }
?>
  <table class="table-fill">
    <thead>
      <tr>
        <th class="text-left">NIC</th>
        <th class="text-left">Meter Value</th>
        <th class="text-left">Reading Time</th>
      </tr>
    </thead>
    <tbody class="table-hover">
      <?php while ($row = $result->fetch_assoc()) { ?>
        <tr>
          <td class="text-left"><?php echo $row['nic']; ?></td>
          <td class="text-left"><?php echo $row['meter_value']; ?></td>
          <td class="text-left"><?php echo $row['reading_time']; ?></td>
        </tr>
      <?php } ?>
    </tbody>
  </table>
<?php } ?>

    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.1.3/js/bootstrap.bundle.min.js"></script>
    <script src="js/extention/choices.js"></script>
  </body>
 <?php
$servername = "localhost";
$username = "id8513016_admin";
$password = "admin";
$dbname = "id8513016_dstat";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT status FROM data WHERE id=1";
$result = $conn->query($sql);
$row = $result->fetch_assoc();
echo $row["status"];


$sql = "UPDATE data SET status='2' WHERE id=1";

if ($conn->query($sql) === TRUE) {
    //echo "Record updated successfully";
} else {
    //echo "Error updating record: " . $conn->error;
}

$conn->close();
?> 
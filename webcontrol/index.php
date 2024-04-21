<?php
if(isset($_GET['ip'])){$address=$_GET['ip'];}


echo "<table><tr><td><iframe src='http://".$address.":8080/stream_simple.html' width='1300' height='740'></iframe></td></tr>";    
echo "<tr><td><iframe src=ff.php?ip=$address width='1300'> </iframe></td></tr>";
echo "</table>";
?>

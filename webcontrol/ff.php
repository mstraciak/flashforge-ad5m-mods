<?php
if(isset($_GET['ip'])){$address=$_GET['ip'];}
$port=8899;
$page = $_SERVER['PHP_SELF'];
$sec = "5";

?>
    <meta http-equiv="refresh" content="<?php echo $sec; ?>">

<?php


$rcm='~M601 S1\r\n';
$rim='~M115\r\n';
$rtm='~M105\r\n';
$rhm='~G28\r\n';
$progres='~M27\r\n';
$status='~M119\r\n';
$l_on='~M146 r255 g255 b255\r\n';
$cal='~M650\r\n';
$pause='~M25\r\n';
$resume='~M24\r\n';
$cancel='~M26\r\n';
$home='~G28\r\n';

$buf='';


 if (($socket=socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) and
      (socket_connect($socket, $address, $port)))
    {
      $text="Connection successful on IP $address, port $port";
      socket_send($socket,utf8_encode($rcm),strlen($rcm),0);
      socket_recv($socket, $bufi, 1024, 0);
      
      if(isset($_POST['LED']) && $_POST['LED']=='SWITCH'){ socket_send($socket,utf8_encode($l_on),strlen($l_on),0);socket_recv($socket, $buf, 1024, 0);}
      if(isset($_POST['PAUSE']) && $_POST['PAUSE']=='ON'){ socket_send($socket,utf8_encode($pause),strlen($pause),0);socket_recv($socket, $buf, 1024, 0);}
      if(isset($_POST['RESUME']) && $_POST['RESUME']=='ON'){ socket_send($socket,utf8_encode($resume),strlen($resume),0);socket_recv($socket, $buf, 1024, 0);}
      if(isset($_POST['STOP']) && $_POST['STOP']=='ON'){ socket_send($socket,utf8_encode($cancel),strlen($cancel),0);socket_recv($socket, $buf, 1024, 0);}
      if(isset($_POST['HOME']) && $_POST['HOME']=='ON'){ socket_send($socket,utf8_encode($home),strlen($home),0);socket_recv($socket, $buf, 1024, 0);}
      
      socket_send($socket,utf8_encode($rtm),strlen($rtm),0);
      socket_recv($socket, $buft, 1024, 0);
      
      socket_send($socket,utf8_encode($progres),strlen($progres),0);
      while(!socket_recv($socket, $bufp, 1024, 0));
      
      socket_send($socket,utf8_encode($status),strlen($status),0);
      while(!socket_recv($socket, $bufs, 1024, 0));
      
     
     // socket_recv($socket, $led, 1024, 0);
      
      socket_close($socket);
    //  echo "Prijate data:<br>";
  //  echo $bufs;         ///////////////////////DEBUG MESSAGE
    //Uprava informacii o teplote
      $buft=explode('T0:',$buft);
      $buft=explode('T1:',$buft[1]);
      $temp=explode('/',$buft[0]);
      $temp_he=$temp[0];
      $temp_hes=$temp[1];
      $buft=explode('B:',$buft[1]);
      $buft=explode('ok',$buft[1]);
      $temp=explode('/',$buft[0]); 
      $temp_bed=$temp[0];
      $temp_beds=$temp[1];    
     //uprava informacii o progrese. 
      $bufp=explode('byte',$bufp);
      $bufpp=explode('/',$bufp[1]);
      $hotovo=$bufpp[0];
      $layer=explode('Layer:',$bufp[1]);
      $layer=explode('ok',$layer[1]);
      $layer=$layer[0];
    //uprava informacii o subore
      $file=explode('CurrentFile:',$bufs);  
      $files=explode('ok',$file[1]);
      $file=$files[0];
    //Uprava informacii o stave
      $stav=explode('MoveMode:',$bufs);  
      $stavs=explode('Status: S:',$stav[1]);
      $stav=$stavs[0];
    }
  else
    $text="Unable to connect<pre>".socket_strerror(socket_last_error())."</pre>";
    
echo "<table border=1 style='width:100%'>";
echo "<tr><td colspan=3 style='width:33%' align=center>Temperature </td> <td colspan=2 style='width:33%' align=center>Progres</td><td style='width:33%' align=center>Control</td> </tr>";
echo "<tr><td>        </td><td> SET           </td><td> NOW          </td><td> File: </td><td>  $file    </td><td>State:  $stav        </td></tr>";    
echo "<tr><td>HOTEND  </td><td> $temp_hes °C  </td><td> $temp_he °C  </td><td> Done:  </td><td> $hotovo % </td><td>          </td></tr>";
echo "<tr><td>BED     </td><td> $temp_beds °C </td><td> $temp_bed °C </td><td> Layer: </td><td>  $layer   </td><td><form action='ff.php' method='post'>
    <button type='submit' name='LED' value='SWITCH' >LED</button><button type='submit' name='PAUSE' value='ON' >PAUSE</button><button type='submit' name='RESUME' value='ON' >RESUME</button><button type='submit' name='STOP' value='ON' >CANCEL</button><button type='submit' name='HOME' value='ON' >HOME</button>
</form></td></tr>";    
    

echo "</table>";    
echo "<br>";

//echo $text;

?>

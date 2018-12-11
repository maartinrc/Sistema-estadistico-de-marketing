<?php
	include('Conexion.php');
	$conection=conectar();
	
	if (!$conection) {
    	echo "Error: No se pudo conectar a MySQL." . PHP_EOL;
    	echo "errno de depuración: " . mysqli_connect_errno() . PHP_EOL;
    	echo "error de depuración: " . mysqli_connect_error() . PHP_EOL;
    	exit;
	}
	
	$fecha=new Date();
	$mac=$_GET['mac'];
	$tiempo=$_GET['tiempo'];
	$numP=$_GET['conteoPersonas'];
	$humedad=$_GET['humedad'];
	$temp=$_GET['temperatura'];
	
	ini_set('date.timezone','America/Mexico_City');
	   
	$time = date('d/m/Y',time());

$sql="INSERT INTO SENSOR_ULTRASONICO(FECHA,TIEMPO,MAC) VALUES('".$time."','".$tiempo."','".$mac."');";
	
$sql1="INSERT INTO SENSOR_TEMPERATURA(FECHA,HUMEDAD,TEMPERATURA,MAC) VALUES('".$time."','".$humedad."','".$temp."','".$mac."');";

$sql2="INSERT INTO SENSOR_INFRARROJO(FECHA,CANTIDAD_P,MAC) VALUES('".$time."','".$numP."','".$mac."');";
	
 mysqli_query($conection,$sql);
 mysqli_query($conection,$sql1);
 mysqli_query($conection,$sql2);

 mysqli_close($conection);  
/*	$sqlAux1="SELECT ID_ULTRA FROM ";
	$sqlAux2="";
	$sqlAux3="";

	$sql3="INSERT INTO ESTADISTICA(MAC,ID_ULTRA,ID_INFRA,ID_TEMP) VALUES('".$mac."',id,id,id);";*/


?>

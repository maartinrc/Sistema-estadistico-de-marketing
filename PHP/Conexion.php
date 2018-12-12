<?php

function conectar(){

$user="root";
$pass="";
$server="localhost";
$db="MARKETING";

$conection= mysqli_connect($server,$user,$pass,$db);

return $conection;
}
?>

<?php

function conectar(){

$user="root";
$pass="";
$server="localhost";
$db="formulario";
    
$conection= mysqli_connect($server,$user,$pass,$db) or die ("Error al conectar a la base de datos".mysqli_error());    
    
return $conection;
}
?>
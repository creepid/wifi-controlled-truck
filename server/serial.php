<?php
require_once "classes/Comm.php";
 
if (isset($_GET['comm'])){
	$comm = $_GET['comm'];
	$commObj = new Comm();
	$commObj->sendCommand($comm);	
}
?>
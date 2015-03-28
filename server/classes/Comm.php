<?php
class Comm {

     private $container = array();

     public function __construct() {
        $this->container = array(
			      "right" => 1, 
			      "left" => 2,
			      "release" => 0,

			      "forward" => 5,
			      "reverse" => 4,
			      "stop" => 3,
	);
    }

     public function sendCommand($comm) {
	     if (isset($this->container[$comm])){
			$commToSend = $this->container[$comm];
			shell_exec("echo \"".$commToSend."\" > /dev/ttyS0");
	     }
	     return;
     }

}
?>
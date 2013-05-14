<?php


function sendData($data) {
        $service_port = 1338;
        $address =  "127.0.0.1";

        /* Create a TCP/IP socket. */
        $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        if ($socket === false) {
            echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
        } else {
            echo "OK.\n";
        }

        $result = socket_connect($socket, $address, $service_port);
        if ($result === false) {
            echo "socket_connect() failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
        } else {
            echo "OK.\n";
        }
        socket_write($socket, $data, strlen($data));
        socket_close($socket);
}


if (isset($_REQUEST['turnOn'])) sendData("on");
if (isset($_REQUEST['turnOff'])) sendData("off");

sendData("on");

?>

<html>
<style>
	body {
		text-align:center;
	}
	.on {
		width:200px;
		height: 65px;
		text-align:center;
		background-color: green;
		color:white;
		display:block;
		margin: 0 auto;
		font-size: 24px;
		padding-top: 30px;
		text-decoration:none
	}
	.off {
		width:200px;
		height: 65px;
		text-align:center;
		background-color: red;
		color:white;
		display:block;
		margin: 0 auto;
		font-size: 24px;
		padding-top: 30px;
		text-decoration:none
	}
</style>
<body>
	<a class="on" href="?turnOn">Turn LED On</a><br/>
	<a class="off" href="?turnOff">Turn LED Off</a>
	

</body>
</html>

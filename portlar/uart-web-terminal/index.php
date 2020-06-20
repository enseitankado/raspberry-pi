<?php
/**
 * UART Web Terminal
 *
 * Monitors local UART (serial) ports to a web page 
 * and interact with it by ASCII commands.
 *
 * This project is licensed under the MIT License.
 *
 * @author     Ozgur Koca <ozgur.koca@linux.org.tr>
 * @version    1.0
 * @link       http://www.tankado.com/
 */
 
include('config.php');
require('auth.php');

# initialize UART(serial0) at 115200 baud and other parameters
exec("/bin/stty -F ".SERIAL_DEVICE." ".BAUD_RATE." -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -echo");
?>
<html>
	<head>
		<title>UART Web Terminal</title>
	</head>
	<body style="background-color: black;">
		<iframe src='log_window.php' width='100%' height='75%' frameborder='0'></iframe>
		<iframe src='command.php' width='100%' height='100' frameborder='0'></iframe>
	</body>
</html>
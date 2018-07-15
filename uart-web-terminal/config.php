<?php
	define('SERIAL_DEVICE', '/dev/serial0');
	define('BAUD_RATE', '115200');	
	define('MAX_LOG_LINE', 50);
	
	// Valid users
	$valid_passwords = array ("pi" => "raspberry");

	
	// ***************************************************
	// Note: Dont modify below	
	// ***************************************************
	
	// Debug mode
	/*
	ini_set('display_errors', 1);
	error_reporting(E_ALL);
	ini_set('max_execution_time', 5);
	set_time_limit(5);	
	*/
?>
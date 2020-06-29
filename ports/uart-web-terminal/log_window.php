<?php	
	include('config.php');
	require('auth.php');
	session_start();
?>
<html>
    <head>        
        <meta http-equiv="refresh" content="1" />
    </head>
    <body>
	<div style="height:5%; color:white;"><b>Monitoring:</b> <?php echo SERIAL_DEVICE.' at '.BAUD_RATE.' baud'; ?></div>
	<div style="height:95%">
	<textarea id="log_area" style="width:100%; height:100%; align: bottom; background-color: black; color: #00FFFF;">
	<?php		
		
		$ser = fopen(SERIAL_DEVICE, 'r');
		if ($ser) {
			$logs_arr = $_SESSION['logs'];		
			$buf = fgets($ser);
			fclose ($ser);
			
			if (empty(trim($buf)))
				$buf = 'Ø';
			
			$logs_arr[] = $buf;
			
		} else {
			$arr = error_get_last();
			$logs_arr[] = 'PHP Error: '.$arr['message'];
		}
		
		if (count($logs_arr) > MAX_LOG_LINE)
			$logs_arr = array_slice($logs_arr, count($logs_arr) - MAX_LOG_LINE, MAX_LOG_LINE);  			
	
		foreach ($logs_arr as $line)
			echo trim($line)."\n";
		
		$_SESSION['logs'] = $logs_arr;
	?>
	</textarea>
	</div>
	<!-- textarea dikey kaydirma cubugunu asagi yasla -->
	<script>
		var textarea = document.getElementById('log_area');
		textarea.scrollTop = textarea.scrollHeight;
	</script>
    </body>
</html>
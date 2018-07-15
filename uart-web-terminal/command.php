<?php
	include('config.php');
	require('auth.php');
?>
<html>
	<body style="color:black;">
		<?php
			if (isset($_GET['cmd']))
				$cmd = $_GET['cmd'];
			
			if (!empty($cmd))			
				exec('echo "'.strtolower($cmd).'" > '.SERIAL_DEVICE);
		?>
		<form style="display: flex;">
			<input name='cmd' placeholder="Enter ASCII Command" style="flex-grow: 1;">&nbsp;&nbsp;
			<input type='submit' value='Send ASCII'>
		</form>
		<form style="display: flex;">	
			<input type='submit' name='cmd' value='Ac'>&nbsp;
			<input type='submit' name='cmd' value='Kapat'>&nbsp;
		</form>
	</body>
</html>


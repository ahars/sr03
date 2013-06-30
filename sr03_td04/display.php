<!--
 UV : SR03 - TD04
 Auteurs : Jin Sun - Antoine Hars
 Fichier : display.php
-->

<?php 
	session_id($_GET['sessionid']);
	session_start();
	$_SESSION['adresse'] = '23 rue de Paris';
	$_SESSION['codepostal'] = 60200;
	$_SESSION['ville'] = 'Compiègne';
	print_r($_SESSION);
?>

<!doctype html>
<html>
	<head>
		<title>SR03::TD04</title>
		<meta charset = "utf-8">
	</head>
	<body>
	</body>
</html>

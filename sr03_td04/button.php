<!--
 UV : SR03 - TD04
 Auteurs : Jin Sun - Antoine Hars
 Fichier : button.php
-->

<?php session_start();
	$_SESSION['prenom'] = 'Jean';
	$_SESSION['nom'] = 'Dupont';
	$_SESSION['age'] = 24;
?>

<!doctype html>
<html>
	<head>
		<title>SR03::TD04</title>
		<meta charset = "utf-8">
		<script src = "http://code.jquery.com/jquery-1.9.1.min.js"></script>
	    	<script type = "text/javascript">
			function redirect(){
				//document.location.href = "display.php"
				document.location.href = "display.php?sessionid = <?php echo session_id(); ?>"
			}
		</script>
	</head>
	<body>
		<input type = "button" onClick = "redirect();" value = "Redirect me">
	</body>
</html>

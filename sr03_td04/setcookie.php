<!--
 UV : SR03 - TD04
 Auteurs : Jin Sun - Antoine Hars
 Fichier : setcookie.php
-->

<?php
	if (isset($_GET['cname'])&&isset($_GET['cvalue'])) {
		setcookie ( $_GET['cname'] , $_GET['cvalue']);
		echo '<h3>Deposer un nouveau cookie</h3>';
	}
	else {
		echo '<h3>Deposer un cookie</h3>';
	}
?>

<form action = "setcookie.php" method = "get">
	<input type = "text" name = "cname" placeholder = "Nom">
	<input type = "text" name = "cvalue" placeholder = "Valeur">
	<input type = "submit"> 
</form>

<?php
	echo '<h3>Liste des cookies deja presents</h3>';
	echo '<table>';
	foreach ($_COOKIE as $key => $value) {
		echo '<tr>';
		echo '<td>';
		echo $key;
		echo '</td>';
		echo '<td>';
		echo $value;
		echo '</td>';
		echo '</tr>';
	}
	echo '</table>';
?>


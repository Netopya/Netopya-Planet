<?php
	include("upper_php.php");

	$gal_id = wash($_POST["gal_id"]);
	$password = wash($_POST["pass"]);
	$name = wash($_POST["name"]);
	$suffix = wash($_POST["suffix"]);
	$description = wash($_POST["description"]);
	
	if($password != "j0hnmadden")
	{
		die("Nope");
	}
	
	$thb_url = "gallery_images/" . $gal_id . "/thb/thb_" . $suffix;
	$lrg_url = "gallery_images/" . $gal_id . "/lrg/lrg_" . $suffix;
	$full_url = "gallery_images/" . $gal_id . "/full/full_" . $suffix;
	
	if (!mysqli_query($con,"INSERT INTO  gallery_images (gallery_id, name, description, thb_url, lrg_url, full_url) VALUES ($gal_id, '$name','$description','$thb_url','$lrg_url','$full_url')"))
	{
		echo("SQL error, image not added");
	}
	else
	{
		echo("<p>Image Successfully added</p></br>");
		echo("<a href=\"gallery_test.php\">Go back</a>");
		mysqli_close($con);
	}
?>
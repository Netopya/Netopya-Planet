<?php

	
	include("upper_php.php");
	
	$tab_number = 3;

?>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Netopya Planet - Projects</title>
	
	<meta property="og:type" content="website"> 
	<meta property="og:url" content="http://www.netopyaplanet.com/"> 
	<meta property="og:title" content="Netopyaplanet.com"> 
	<meta property="og:image" content="http://www.netopyaplanet.com/site_image.png"> 
	<meta property="og:site_name" content="Netopya Planet">
	<meta property="og:description" content="Netopya's Official Blog!">
		
	<meta name="viewport" content="width=device-width, initial-scale=1">
	
    <!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="bootstrap/css/bootstrap.min.css">

	<!-- Optional theme -->
	<link rel="stylesheet" href="bootstrap/css/bootstrap-theme.min.css">
	
	<link rel="stylesheet" href="css/bootstrap.override.css">
	<link rel="stylesheet" href="css/stylesheet.css">
	
	<script src="//code.jquery.com/jquery-1.11.0.min.js"></script>
	<script src="//code.jquery.com/jquery-migrate-1.2.1.min.js"></script>
	
	<!-- Latest compiled and minified JavaScript -->
	<script src="bootstrap/js/bootstrap.min.js"></script>
	
	<script type="text/javascript" src="js/ga_script.js"></script>
  </head>
  <body>
	<?php include("php/navbar.php"); ?>
	
	<div id="smalltopnavback"></div>
  
	<div class="container marketing">
		<div class="row">
			<div class="col-lg-12">
				<ol class="breadcrumb">
				  <li><a href="index.php">Home</a></li>
				  <li>Projects</li>
				</ol>
			</div>
		</div>
		<div class="row">
			<div class="col-lg-12">
				<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
				<!-- Index Top Responsive -->
				<ins class="adsbygoogle"
					 style="display:block"
					 data-ad-client="ca-pub-8696786899578479"
					 data-ad-slot="2590288345"
					 data-ad-format="auto"></ins>
				<script>
				(adsbygoogle = window.adsbygoogle || []).push({});
				</script>
			</div>
		</div>
		<div class="row">
			<h1>Projects</h1>
		</div>
		<div class="row">
			<?php
				//http://www.phpjabbers.com/date-and-time-formatting-with-php-php28.html
			
			
				$result = mysqli_query($con,"SELECT * FROM articles WHERE tag LIKE 'PROJ' ORDER BY timestamp DESC");
				while($row = mysqli_fetch_array($result))
				{
					$author_result = mysqli_query($con,"SELECT * FROM users WHERE id=" . $row['user_id']);
					$author_row = mysqli_fetch_array($author_result);
					?>
					<div class="col-md-4 col-sm-6">
						<div class="feature_clip">
							<div class="row">
								<a href="article.php?id=<?php echo $row['id']; ?>"><h2><?php echo $row['title']; ?></h2></a>
							</div>
							
							<div class="row">
								<a href="article.php?id=<?php echo $row['id']; ?>">
									<div class="circleimage" style="background-image:url('<?php echo $row['feature_clip']; ?>');">
									</div>
								</a>
							</div>
							<div class="row">
								<a href="article.php?id=<?php echo $row['id']; ?>">
									<p class="linked_description"><?php echo $row['ogdescription']; ?></p>
								</a>
							</div>
							<div class="row">
								<a href="article.php?id=<?php echo $row['id']; ?>">Continue reading...</a>
							</div>
						</div>
					</div>
					
					
					<?php
				}
			
			?>
			
			
		</div>
	</div>
	<?php include("php/footer.php"); ?>
  </body>
</html>
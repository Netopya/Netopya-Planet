<?php

	
	include("upper_php.php");
	
	$tab_number = 0;

?>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Netopya Planet - Articles</title>
	
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
	
	<div class="row">
		<div id="smalltopnavback" class="col-lg-12"></div>
	</div>
  
	<div class="container marketing">
		<div class="col-lg-10 col-lg-offset-1">
			<div class="alert alert-danger alert-dismissible" role="alert" style="margin-top:5px;">
				<button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>
				<strong>Invalid Article!</strong> No valid article selected
			</div>
		</div>
		<div class="row">
			<?php
				//http://www.phpjabbers.com/date-and-time-formatting-with-php-php28.html
			
			
				$result = mysqli_query($con,"SELECT * FROM articles ORDER BY id DESC");
				while($row = mysqli_fetch_array($result))
				{
					$author_result = mysqli_query($con,"SELECT * FROM users WHERE id=" . $row['user_id']);
					$author_row = mysqli_fetch_array($author_result);
					
					$comment_result = mysqli_query($con,"SELECT * FROM comments WHERE enabled = 1 AND article_id=" . $row['id']);
					$num_of_comments = mysqli_num_rows($comment_result);
					?>
					<div class="col-lg-10 col-lg-offset-1 blog_post">
						<div class="row">
							<a href="article.php?id=<?php echo $row['id']; ?>"><h1><?php echo $row['title']; ?></h1></a>
						</div>
						
						
						<div class="row">
							<div class="col-lg-3 outer_circle_image col-md-3 col-sm-4">
								<a href="article.php?id=<?php echo $row['id']; ?>">
									<div class="circleimage" style="background-image:url('<?php echo $row['feature_clip']; ?>');">
									</div>
								</a>
							</div>
							<div class="col-lg-9 col-md-9 col-sm-8">
								<a href="article.php?id=<?php echo $row['id']; ?>">
									<p class="linked_description"><?php echo $row['ogdescription']; ?></p>
									<p>Comments: <span class="badge"><?php echo $num_of_comments; ?></span></p>
								</a>
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
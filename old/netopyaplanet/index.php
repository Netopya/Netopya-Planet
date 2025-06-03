<?php
	
	include("upper_php.php");

	$tab_number = 1;

?><!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Netopya Planet - Home</title>
	
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
	
	<script src="js/konami.js"></script>
	
	<script type="text/javascript" src="js/ga_script.js"></script>
	
  </head>
  <body>
  
  <div id="fb-root"></div>
	<script>(function(d, s, id) {
	  var js, fjs = d.getElementsByTagName(s)[0];
	  if (d.getElementById(id)) return;
	  js = d.createElement(s); js.id = id;
	  js.src = "//connect.facebook.net/en_US/sdk.js#xfbml=1&appId=1456409494650107&version=v2.3";
	  fjs.parentNode.insertBefore(js, fjs);
	}(document, 'script', 'facebook-jssdk'));</script>
	<?php include("php/navbar.php"); ?>
	
	
	<!-- carousel begin -->
    <div id="main-carousel" class="carousel slide" data-ride="carousel">
	  <!-- Indicators -->
	  <ol class="carousel-indicators">
		<li data-target="#main-carousel" data-slide-to="0" class="active"></li>
		<li data-target="#main-carousel" data-slide-to="1"></li>
		<li data-target="#main-carousel" data-slide-to="2"></li>
		<li data-target="#main-carousel" data-slide-to="3"></li>
		<li data-target="#main-carousel" data-slide-to="4"></li>
	  </ol>

	  <!-- Wrapper for slides -->
	  <div class="carousel-inner" role="listbox">
		<div class="item active">
		  <img src="bootimages/main-carousel/header3.jpg" alt="...">
		  <div class="carousel-caption">
			<h1>NETOPYAPLANET.COM</h1>
			<p>Welcome to netopyaplanet.com!</br>Programming, projects, and more ...</p>
		  </div>
		</div>
		<div class="item">
		  <img src="bootimages/main-carousel/ip3.jpg" alt="...">
		  <div class="carousel-caption" id="ipplanner-caption">
		  		<h1 class="media-heading">IP Planner</h1>
				<p>Track your League of Legends Influence Points rate!
					</br>
					<a href="ipplanner/"><button type="button" class="btn btn-primary">Try now <span class="glyphicon glyphicon-new-window" aria-hidden="true"></span></button></a>
				</p>
		  </div>
		</div>
		<div class="item">
		  <img src="bootimages/main-carousel/full_IMG_5841.jpg" alt="...">
		  <div class="carousel-caption">
				<h1 class="media-heading">I2C Multiplexers</h1>
				<p>Control multiple identical I2C devices with an Arduino
					</br>
					<a href="article.php?id=6"><button type="button" class="btn btn-primary">Learn more <span class="glyphicon glyphicon-new-window" aria-hidden="true"></span></button></a>
				</p>
		  </div>
		</div>
		<div class="item">
		  <img src="bootimages/main-carousel/full_IMG_6591.jpg" alt="...">
		  <div class="carousel-caption">
				<h1 class="media-heading">Raspberry Pi LCD Screen</h1>
				<p><strong>Recycle an old laptop LCD screen</strong>
					</br>
					<a href="article.php?id=9"><button type="button" class="btn btn-primary">Learn more <span class="glyphicon glyphicon-new-window" aria-hidden="true"></span></button></a>
				</p>
		  </div>
		</div>
		<div class="item">
		  <img src="bootimages/main-carousel/full_IMG_5781.jpg" alt="...">
		  <div class="carousel-caption">
				<h1 class="media-heading">The AEMD Alpha</h1>
				<p>An Arduino Entertainment Multimedia Device
					</br>
					<a href="article.php?id=3"><button type="button" class="btn btn-primary">Check out <span class="glyphicon glyphicon-new-window" aria-hidden="true"></span></button></a>
				</p>
		  </div>
		</div>
	  </div>

	  <!-- Controls -->
	  <a class="left carousel-control" href="#main-carousel" role="button" data-slide="prev">
		<span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
		<span class="sr-only">Previous</span>
	  </a>
	  <a class="right carousel-control" href="#main-carousel" role="button" data-slide="next">
		<span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
		<span class="sr-only">Next</span>
	  </a>
	</div>
	
	<!-- END CAROUSEL -->
	
	<div class="container marketing">
		<div class="row">
			<div class="col-lg-12">
				<div class="well well-sm">
					<div class="row">
						<div class="col-lg-1">
							Social:
						</div>
						<div class="col-lg-11">
							<div class="social_container" id="socialfb">
								<div class="fb-like" data-href="http://www.netopyaplanet.com/" data-layout="button_count" data-action="like" data-show-faces="false" data-share="true"></div>
							</div>
							<div class="social_container" id="socialtw">
								<a href="https://twitter.com/share" class="twitter-share-button" data-url="http://www.netopyaplanet.com" data-text="Netopya's Official Blog!" data-via="Netopya">Tweet</a>
								<script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+'://platform.twitter.com/widgets.js';fjs.parentNode.insertBefore(js,fjs);}}(document, 'script', 'twitter-wjs');</script>
							</div>
							<div class="social_container">
								<!-- Place this tag where you want the +1 button to render. -->
								<div class="g-plusone" data-size="medium" data-href="http://www.netopyaplanet.com"></div>

								<!-- Place this tag after the last +1 button tag. -->
								<script type="text/javascript">
								  (function() {
									var po = document.createElement('script'); po.type = 'text/javascript'; po.async = true;
									po.src = 'https://apis.google.com/js/plusone.js';
									var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(po, s);
								  })();
								</script>
							</div>
						</div>
					</div>
				</div>
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
			
			
			<?php
				//http://www.phpjabbers.com/date-and-time-formatting-with-php-php28.html
			
			
				$result = mysqli_query($con,"SELECT * FROM articles ORDER BY id DESC");
				while($row = mysqli_fetch_array($result))
				{
					$author_result = mysqli_query($con,"SELECT * FROM users WHERE id=" . $row['user_id']);
					$author_row = mysqli_fetch_array($author_result);
					?>
					<div class="col-lg-10 col-lg-offset-1 blog_post">
						<h2>
							<a href="article.php?id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a>
							<br/>
							<small><i>By <?php echo $author_row['pseudo_name']; ?> on <?php $timestamp = strtotime($row['timestamp']); echo date("M jS Y",$timestamp); ?></i></small>
						</h2>
						
						<?php echo $row['overfold_content']; ?>
						<a href="article.php?id=<?php echo $row['id']; ?>">Continue reading...</a>
					</div>
					
					
					<?php
				}
			
			?>
			
			
		</div>
	</div>
	<?php include("php/footer.php"); ?>	
	
  </body>
</html>
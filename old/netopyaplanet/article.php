<?php
	
	include("upper_php.php");

	$id = wash($_GET["id"]);
	/*
	$result = mysqli_query($con,"SELECT * FROM articles WHERE id=" . $article_id);
	if (!(mysqli_num_rows($result) > 0))
	{
		die("invalid article");
	}*/
	
	$stmt = $dbh->prepare("SELECT *, articles.id AS a_id, articles.timestamp AS a_timestamp FROM articles JOIN users ON articles.user_id = users.id WHERE articles.id=:id");
	$stmt->bindParam(':id', $id);
	$stmt->setFetchMode(PDO::FETCH_ASSOC); 
	$stmt->execute();
	$row = $stmt->fetch();
	if(!($row > 0))
	{
		include("invalid_article.php");
		die();
	}
	
	//$row = mysqli_fetch_array($result);
	
	//$author_result = mysqli_query($con,"SELECT * FROM users WHERE id=" . $row['user_id']);
	//$author_row = mysqli_fetch_array($author_result);
	
	//SELECT *, UNIX_TIMESTAMP(timestamp) as dt FROM `comments`
	$comment_result = mysqli_query($con,"SELECT * FROM comments WHERE enabled = 1 AND article_id=" . $row['a_id']);
	$num_of_comments = mysqli_num_rows($comment_result);
	
	$gallery_id = $row['gallery_id'];
	
	$gal_result = mysqli_query($con,"SELECT * FROM gallery_images WHERE gallery_id = " . $gallery_id);
	$num_of_images = mysqli_num_rows($gal_result);

	$tab_number = 0;
	
?><!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Netopya Planet - <?php echo $row['title']; ?></title>
	
	<meta name="viewport" content="width=device-width, initial-scale=1">
	
	<meta property="og:type"            content="website" /> 
	<meta property="og:url"             content="http://www.netopyaplanet.com/article.php?id=<?php echo $row['a_id']; ?>"/> 
	<meta property="og:title"           content="<?php echo $row['title']; ?>" /> 
	<meta property="og:image"           content="<?php echo $row['ogimage_url']; ?>" /> 
	<meta property="og:site_name"		content="Netopya Planet"/>
	<meta property="og:description" 	content="<?php echo $row['ogdescription']; ?>"/>
		
    <!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="bootstrap/css/bootstrap.min.css">

	<!-- Optional theme -->
	<link rel="stylesheet" href="bootstrap/css/bootstrap-theme.min.css">
	
	<link rel="stylesheet" href="css/bootstrap.override.css">
	<link rel="stylesheet" href="css/stylesheet.css">
	<link rel="stylesheet" href="css/article.override.css">
	
	<script src="//code.jquery.com/jquery-1.11.0.min.js"></script>
	<script src="//code.jquery.com/jquery-migrate-1.2.1.min.js"></script>
	
	<script src="js/jquery-ui-1.11.4.custom/jquery-ui.min.js"></script>
	
	<!-- Latest compiled and minified JavaScript -->
	<script src="bootstrap/js/bootstrap.min.js"></script>
		
	<script type="text/javascript" src="js/ga_script.js"></script>
			
	<script type="text/javascript">
		
		function pageReady() {
			
			//http://stackoverflow.com/questions/22639550/how-to-animate-height-change-on-bootstrap-3-carousel
			
			$('.carousel').carousel().on('slide.bs.carousel', function (e)
			{
				var nextH = $(e.relatedTarget).height();
				$(this).find('.active.item').parent().animate({ height: nextH }, 500);
			});
			
			$("#comment_form").submit(function(e){
			
				//http://stackoverflow.com/questions/24694194/jquery-ajax-submit-form-getting-response
				
				var postData = $(this).serializeArray();
				var formURL = $(this).attr("action");

				$.ajax(
				{
					url : formURL,
					type: "POST",
					crossDomain: true,
					data : postData,
					dataType : "json",
					success:function(data, textStatus, jqXHR) 
					{						
						if(data.status == "success")
						{
							$("#comment_alert_container").html('<div class="alert alert-success" role="alert">Comment Added Successfully! Please wait a few days for your comment to be reviewed.</div>');
							grecaptcha.reset();
							$("#collapsable_input").animate({height: "toggle"}, {duration: 2500, specialEasing: {height: "easeOutQuint"}});
						} 
						else
						{
							$("#comment_alert_container").html('<div class="alert alert-danger" role="alert"><strong>Error</strong> ' + data.message + '</div>');
							grecaptcha.reset();
						}
						
						
					},
					error: function(jqXHR, textStatus, errorThrown) 
					{
						$("#comment_alert_container").html('<div class="alert alert-danger" role="alert"><strong>Error</strong> No response from server</div>');
						grecaptcha.reset();
					}
				});
				e.preventDefault(); //STOP default action
				e.unbind();
			});
		}
		
		
		
		// 
	</script>
	
	<script src='https://www.google.com/recaptcha/api.js'></script>
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
	

	<div id="smalltopnavback"></div>

	
	<div class="container marketing">
		<div class="row">
			<div class="col-lg-12">
				<ol class="breadcrumb">
				  <li><a href="index.php">Home</a></li>
				  <li><?php echo $row['title']; ?></li>
				</ol>
			</div>
		</div>
		<div class="row">
			<div class="col-lg-12">
				<div class="well well-sm">
					<div class="row">
						<div class="col-lg-1">
							Social:
						</div>
						<div class="col-lg-11">
							<div class="social_container" id="socialfb">
								<div class="fb-like" data-href="http://www.netopyaplanet.com/article.php?id=<?php echo $row['a_id']; ?>" data-layout="button_count" data-action="like" data-show-faces="false" data-share="true"></div>
							</div>
							<div class="social_container" id="socialtw">
								<a href="https://twitter.com/share" class="twitter-share-button" data-url="http://www.netopyaplanet.com/article.php?id=<?php echo $row['a_id']; ?>" data-text="<?php echo $row['title']; ?> - Netopya's Official Blog!" data-via="Netopya">Tweet</a>
								<script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+'://platform.twitter.com/widgets.js';fjs.parentNode.insertBefore(js,fjs);}}(document, 'script', 'twitter-wjs');</script>
							</div>
							<div class="social_container">
								<!-- Place this tag where you want the +1 button to render. -->
								<div class="g-plusone" data-size="medium" data-href="http://www.netopyaplanet.com/article.php?id=<?php echo $row['a_id']; ?>"></div>

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
			<div class="col-lg-10 col-lg-offset-1 blog_post">
				<h1><?php echo $row['title']; ?></h1>
				<h2><small>By <?php echo $row['pseudo_name']; ?> on <?php $timestamp = strtotime($row['a_timestamp']); echo date("D M jS Y g:i A",$timestamp); ?></small></h2>
				<?php echo $row['overfold_content']; ?>
				
				
				
				<?php 
					if($gallery_id>0)
						{ 
						
							echo("<h3>Full Gallery:</h3>");
							?>
							
							<div id="main-carousel" class="carousel slide" data-ride="carousel"  data-interval="">
							  

							  <!-- Wrapper for slides -->
							  <div class="carousel-inner" role="listbox">
								<?php
									$first = true;
									while($gal_row = mysqli_fetch_array($gal_result))
									{
										?>
											
											<div class="item <?php if($first) { $first = false; echo "active"; } ?>">
											  <a href="<?php echo $gal_row['full_url']; ?>">
												<img src="<?php echo $gal_row['lrg_url']; ?>" alt="...">
											  </a>
											  <div class="carousel-caption">
												<a href="<?php echo $gal_row['full_url']; ?>">
													<p>
														<strong><?php echo $gal_row['name'];?></strong> - <?php echo $gal_row['description'];?>
													</p>
											    </a>
											  </div>
											  
											</div>
											
										<?php
									}
								
								?>
								
							  </div>
							  
							  <!-- Indicators -->
							  <ol class="carousel-indicators">
								<li data-target="#main-carousel" data-slide-to="0" class="active"></li>
								
								<?php
									for ($x = 1; $x <= $num_of_images-1; $x++) {
										?> <li data-target="#main-carousel" data-slide-to="<?php echo $x; ?>"></li> <?php
									} 
								?>
																
							  </ol>
							  
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
							
							
							<?php
							
							
							
						}
				?>
				<?php echo $row['content']; ?>
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
				<div class="col-lg-10 col-lg-offset-1 blog_post">
				<h1>Comments</h1>
				
				<?php
										
					if($num_of_comments > 0)
					{
						while($comment_row = mysqli_fetch_array($comment_result))
						{
							if($comment_row["website"])
							{
								?>
									<div class="comment">
										<h4><a href="<?php echo $comment_row["website"]; ?>"><?php echo $comment_row["username"]; ?></a> on <?php $timestamp = strtotime($comment_row["timestamp"]); echo date("D M jS g:i A",$timestamp); ?> said:</h4>
										<p><?php echo $comment_row["comment"]; ?></p>
									</div>
								<?php
							}
							else
							{
								?>
									<div class="comment">
										<h4><?php echo $comment_row["username"]; ?> on <?php $timestamp = strtotime($comment_row["timestamp"]); echo date("D M jS g:i A",$timestamp); ?> said:</h4>
										<p><?php echo $comment_row["comment"]; ?></p>
									</div>
								<?php
							}
						}
					}
					else
					{
						echo "<p>No comments</p>";
					}
				?>
				
				
				<form id="comment_form" method="post" class="form-horizontal" action="php/insert_comment_v2.php?id=<?php echo $row['a_id']; ?>">
					<div class="form-group">
						<div class="col-sm-offset-2 col-sm-10">
						  <h3>Leave a comment:</h3>
						  <div id="comment_alert_container"></div>
						</div>
					</div>
					<div id="collapsable_input">
						<div class="form-group">
							<label for="inputName3" class="col-sm-2 control-label">Name</label>
							<div class="col-sm-10">
							  <input type="text" class="form-control" id="inputName3" placeholder="Name" name="username">
							</div>
						</div>
						<div class="form-group">
							<label for="inputEmail3" class="col-sm-2 control-label">Email</label>
							<div class="col-sm-10">
							  <input type="email" class="form-control" id="inputEmail3" placeholder="Email (Optional, will not be shown)" name="e_mail">
							  <p class="help-block">Email is optional, will not be shown</p>
							</div>
						</div>
						<div class="form-group">
							<label for="inputCommenr3" class="col-sm-2 control-label">Comment</label>
							<div class="col-sm-10">
							  <textarea name="comment" class="form-control" rows="10" id="inputCommenr3" placeholder="Comment"></textarea>
							</div>
						</div>
						<div class="form-group">
							<div class="col-sm-offset-2 col-sm-10">
							  <div class="g-recaptcha" data-sitekey="6LcwShEaAAAAAGqDe_92CiNZBZsTwKo2galg4mFI"></div>
							</div>
						</div>
						<div class="form-group">
							<div class="col-sm-offset-2 col-sm-10">
							  <button type="submit" class="btn btn-default">Submit Comment</button>
							</div>
						</div>
					</div>
					<div class="form-group">
						<div class="col-sm-offset-2 col-sm-10">
						  <p class="help-block">Leaving your e-mail is optional and I will only use your e-mail to contact you if you ask for me to do so in your comment.</p>
						</div>
					</div>
					
					
				</form>				
			</div>
		</div>
	</div>
	<?php include("php/footer.php"); ?>
	<script type="text/javascript">
	   pageReady();
	</script>
  </body>
</html>
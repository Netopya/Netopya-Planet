<?php

	$tab_number = 3;
	
	include("upper_php.php");

	$gallery_id = 1;
	
	$gal_result = mysqli_query($con,"SELECT * FROM gallery_images WHERE gallery_id = " . $gallery_id);
	$num_of_images = mysqli_num_rows($gal_result);

?><html>
	<head>
		<title>Netopya Planet - Links</title>
		<LINK REL=StyleSheet HREF="stylesheet1.css" TYPE="text/css">
		<script type="text/javascript" src="ga_script.js"></script>
		<?php include("common.php");?>
	</head>
	<body onload="onpageload()">
		<div id="container_main">
			<div id="main_content_container">
				<div id="header_container">
				</div>
				<?php
					include("button_bar.php");
				?>
				<div id="output_content_container">
					<div id="site_description"><a href="links.php">Links</a></div>
					<div id="top_frame"><h1></h1></div>
					<div id="top_two_pane_layout">
						<div id="content_left_pane">
							<div class="blog_post">
								Idk how u got here, but I'm testing my own gallery code here. Enjoy!
							</div>
							<!--
							<div id="gallery_container">
								<div id="main_image_navigation">
									<div id="left_image_nav" onclick="nav_image_left()"></div>
									
									<div id="galing_outer">
										<div id="main_galimg_container"></div>
									</div>
									
									<div id="right_image_nav" onclick="nav_image_right()"></div>
								</div>
								
								<ul id="gallery_list_navigation">
									<li id="left_page_nav" onclick="nav_page_left()">
									</li>
									<li>
										<ul id="gallery_list">
									
										</ul>
									</li>
									<li id="right_page_nav" onclick="nav_page_right()">
									</li>
								</ul>
								
							</div>
							-->
							<?php include("gallery_markup.php");?>
							
							<div class="blog_post">
								<form action="insert_gal_image.php" method="post">
									<label>Pass: <input type="password" name="pass"></label><br>
									<label>gallery id: <input type="text" name="gal_id"></label></br>
									<label>Name <input type="text" name="name"></label></br>
									<label>File name <input type="text" name="suffix"></label></br>
									<label>Description:<br/><textarea name="description" rows="10" cols="80"></textarea></label></br>
									<input type="submit">
								</form>
							</div>
						</div>
						<div id="content_right_pane">
							
						</div>
					</div>
					<div id="bottom_panel">
					</div>
				</div>
				<?php include("footer.php"); ?>
			</div>
		</div>
	</body>
</html>
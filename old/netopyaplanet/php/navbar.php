<div class="navbar-wrapper">
	<div class="container">
		<nav class="navbar navbar-default">
		  <div class="container-fluid">
			<!-- Brand and toggle get grouped for better mobile display -->
			<div class="navbar-header">
			  <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
				<span class="sr-only">Toggle navigation</span>
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>
			  </button>
			  <a class="navbar-brand" href="index.php">NETOPYA</a>
			</div>

			<!-- Collect the nav links, forms, and other content for toggling -->
			<div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
			  <ul class="nav navbar-nav">
				<li <?php if($tab_number == 1){ echo 'class="active"';} ?>><a href="index.php">Home</a></li>
				<li <?php if($tab_number == -1){ echo 'class="active"';} ?>><a href="ipplanner/">IP Planner <span class="glyphicon glyphicon-new-window" aria-hidden="true"></span></a></li>
				<li <?php if($tab_number == 2){ echo 'class="active"';} ?>><a href="tutorials.php">Tutorials</a></li>
				<li <?php if($tab_number == 3){ echo 'class="active"';} ?>><a href="projects.php">Projects</a></li>
				<li <?php if($tab_number == 4){ echo 'class="active"';} ?>><a href="tools.php">Tools</a></li>
				<li <?php if($tab_number == 5){ echo 'class="active"';} ?>><a href="about.php">About</a></li>
			  </ul>
			</div><!-- /.navbar-collapse -->
		  </div><!-- /.container-fluid -->
		</nav>
	</div>
</div>
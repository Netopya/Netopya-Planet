<div id="button_bar_container">
	<ul>
		<a href="index.php"><li <?php if($tab_number == 1){ echo 'class="selected_tab"';}else{echo 'class="unselected_tab"';}?>>Home</li></a>
		<a href="/ipplanner"><li class="unselected_tab">IP Planner <img src="/images/exicon.png" height="15" width="15"/></li></a>
		<a href="about.php"><li <?php if($tab_number == 2){ echo 'class="selected_tab"';}else{echo 'class="unselected_tab"';}?>>About</li></a>
		<a href="links.php"><li <?php if($tab_number == 3){ echo 'class="selected_tab"';}else{echo 'class="unselected_tab"';}?>>Links</li></a>
	</ul>
</div>
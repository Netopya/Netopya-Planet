---
title: The AEMD Alpha
date: 2013-08-26T00:11:22.000Z
author: Netopya
category: projects
tag: PROJ
layout: post
og_image: http://www.netopyaplanet.com/gallery_images/3/full/full_IMG_5781.JPG
description: Here's my latest school project that I worked on with some friends, the Arduino Entertainment Multimedia Device. It's a completely portable Arduino powered LED matrix with a bunch of bells and whistles allowing it to live up to its name. Checkout my video above or continue on for more information and a gallery of shots.
gallery_id: 3
overfold_content: |
  <div class="row justify-content-center mb-4">
    <div class="col-lg-6 col-md-10 col-12">
      <div class="ratio ratio-4x3">
        <iframe src="https://www.youtube.com/embed/at5guVKc1LE" title="AEMD Alpha Demo Video" allowfullscreen></iframe>
      </div>
    </div>
  </div>
  <p>Here's my latest school project that I worked on with some friends, the Arduino Entertainment Multimedia Device. It's a completely portable Arduino powered LED matrix with a bunch of bells and whistles allowing it to live up to its name. Checkout my video above or continue on for more information and a gallery of shots.</p>
---

<p>Here are the AEMD's components:
<ul>
<li>Arduino UNO rev. 3</li>
<li>16x24 LED matrix (<a href="http://www.adafruit.com/products/555">Adafruit #555</a>)</li>
<li>2-axis analog joystick with select button (<a href="http://www.adafruit.com/products/512">Adafruit #512</a>)</li>
<li>DS1307 Real Time Clock breakout (<a href="http://www.adafruit.com/products/264">Adafruit #264</a>)</li>
<li>MAN6710 Red 2 Digit 7-Segment Display</li>
<li>Two 74HC595 Shift Registers</li>
<li>Project Box Enclosure</li>
<li>Panel Mounted Button</li>
<li>Panel Mounted Switch</li>
<li>Piezo Element</li>
<li>Photoresistor</li>
<li>Temperature Sensor</li>
<li>9V Battery</li>
</ul></p>
<p>The AEMD Alpha was in fact our submission for the final project of a Digital Electronics class where the criteria was to make "something useful" with an Arduino. For all of the members in our group, this was the first time we ever used the Arduino or even handled a soldering iron to make something this complex. We can all attest to the fact that we learnt a lot and that this was a great beginner project. While the Adafruit LED matrix comes nicely preassembled, we still had chance to practice our soldering skills with the assembly of the simpler RTC. On the programming side, Adafruit provides great libraries for its products, but we still learnt a lot about memory management on the Arduino and even using binary operation to simplify coding among other things.</p> 
    <p>For the conceptualization of our project, we were greatly inspired by the <a href="https://code.google.com/p/chlonos/">Chlonos Talking Clock</a>. We brainstormed many ideas and our own iterations, and limited ourselves to the functionalities that are shown in the video. In the end we have a fun, portable, entertainment device that plays our favorites games and also has some useful utilities. We would definitely recommend this project to any beginners due to its simple to use components while still requiring you to get your hands dirty.</p>
<p>Lastly here is the code for our project. I've hidden it at the end as I find that it's a bit of a mess and deserves a proper explanation, which I might get to if there's a demand. Anyway enjoy: </br><a href="http://www.netopyaplanet.com/article_code/sketch_apr25a.ino">sketch_apr25a.ino</a></p>
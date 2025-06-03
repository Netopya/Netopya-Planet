---
title: &#36;4 Computer Backlighting System
date: 2015-10-09T01:18:21.000Z
author: Netopya
category: projects
tag: Project
layout: post
og_image: http://www.netopyaplanet.com/article_images/11/full_IMG_6613.JPG
description: An awesome computer backlighting solution for only 4 dollars!
overfold_content: |
  <div class="centered_image"><a href="/article_images/11/full_IMG_6612.JPG"><img src="/article_images/11/prev_IMG_6612.JPG" class="img-thumbnail"/></a></div>
  <p>Computer monitor backlights are cool. Solutions such as Philips Ambilight are available, but many people opt to design their own system. I wanted to see just how much you can save and what you can get by making the cheapest backlighting system possible. By salvaging parts from previous projects and getting free samples, all I need to buy where some RGB LEDs for only $4.00. Join me as I experiment and create the most basic computer ambient light solution.</p>
---

<h2>Parts</h2>
<ul>
<li>Arduino Uno (or equivalent)</li>
<li>Wires and breadboard</li>
<li>10x RGB LEDs (<a href="http://www.ebay.com/itm/Diffused-10mm-RGB-Common-Anode-4Pins-LED-10pcs-FreeShipping-/251534607654">eBay</a>)</li>
<li>2x TLC5940 PWM driver (<a href="http://www.ti.com/product/tlc5940">Texas Instruments</a>)</li>
</ul>
<p>When saying that this system only costs four dollars, I am making some generous assumptions about the supplies you already have, namely an Arduino microcontroller and some wiring supplies. Nevertheless, cost can still be kept down with non-official Arduinos which are available for under $10. Wires can be obtained at low cost and the PWM driver chip used for this project, the TLC5940, has free samples available for educational use.</p>
<p>The Arduino was chosen for this project since it is easy to work with and communicates well with a computer. However, the Arduino Uno only has four PWM connections so the TLC5940 PWM driver was required in order to increase the number of PWM lines available. The TLC5940 provides an additional 16 PWM channels, however multiple chips can be chained together to increase this amount. Since I wanted to have 10 individually controlled RGB LEDs spaced out around the monitor, and each LED requires 3 PWM connections for each of the three colours, this would amount to 30 PWM channels which can be supplied by 2 TLC5940 chips. When selecting the RGB LEDs to buy, the main requirement was that they were common anode (the common connection is the voltage source) in order to work with the TLC5940 which can only sink current. Furthermore, I opted for larger 10mm and diffused LEDs to project out the light as much as possible and create more of a glowing effect.</p>
<p>With these parts I had enough LEDs to place around the back of my monitor. Since each LED is controlled by its own PWM drivers on the TLC5940, each LED can have a unique colour instead of the more basic approach where the back of the monitor is illuminated by the average colour of the entire screen. This should give a more colourful result has different colours on the edges of the monitor are projected outwards.</p>
<h2>Wiring</h2>
<figure>
<a href="/article_images/11/full_Sketch 2_bb.png">
    <img class="img-thumbnail" src="/article_images/11/prev_Sketch 2_bb.png"/>
</a>
<figcaption>Wiring diagram</figcaption>
</figure>
<p>All wiring for this project was performed on a bread board. Two TLC5940 where chained together and the first one was connected to the Arduino. The red, green, and blue components of the 10 RGB LEDs were each connected to the TLC5940s&#39; channels 0 through 29. And that&#39;s it; all power was transmitted through the USB connection.</p>
<h2>Programming</h2>
<figure>
<a href="/article_images/11/full_diagram2.jpg">
    <img class="img-thumbnail" src="/article_images/11/prev_diagram2.jpg"/>
</a>
<figcaption>Red boxes indicate the areas sampled for their average colour</figcaption>
</figure>
<p>To determine the appropriate colour for each LED, a program written in C# ran on the host computer and determined the average colour of 10 locations around the screen where the LEDs were located, as seen in the above image. The upper and lower sample locations were moved away from the edge of the screen to better match a 16:9 aspect ratio on my 16:10 monitor. This prevented the black bars of letter boxed content from interfering with the projection of the actual content to the upper and lower locations behind the screen. The program transmitted the averaged RGB values for these sample locations to the Arduino using the Serial protocol over a USB connection. The Arduino&#39;s code read this Serial information and set the appropriate PWM signal for the channel controlling the LEDs color.</p>
<h2>Conclusion</h2>
<figure>
<a href="/article_images/11/full_IMG_6613.JPG">
    <img class="img-thumbnail" src="/article_images/11/prev_IMG_6613.JPG"/>
</a>
<figcaption>The final setup</figcaption>
</figure>
<p>So what does a $4 ambient light setup give you? I have to admit that I was a tad disappointed with the result. First off I had to limit the screen sampling rate to once per second. Since this program would be running on my PC at all times I wanted to keep its CPU usage low (below 10%), and this required me to reduce how often it read colour information from the screen. Secondly having the serial library running on the Arduino seems to effect the performance of the TLC5940, resulting in noticeably inaccurate colours, especially near white colours. In the end I found the setup to be a bit of a gimmick. The coolness factor of having colours bouncing around the back of your monitor wears off pretty quickly and doesn&#39;t account for the drawbacks.</p>
<p>For someone looking for a fun, programming and electronic learning experience, you can&#39;t go wrong for only four dollars. However if you want a fully featured ambient light PC setup, I would recommend spending a bit more money and investing in more specialized hardware, such as addressable RGB LED strips. I myself am no longer using this setup, but I do plan to revisit this project in the future, perhaps with a less ambitious, single-coloured RGB LED strip.</p>
<h2>Code</h2>
<p><a href="https://github.com/Netopya/NetopyaAmbientLight">GitHub <span class="glyphicon glyphicon-new-window" aria-hidden="true"></span></a></p>
<h2>Videos</h2>
<p>A video of the system displaying a Windows Media Player music visualizer</p>
<div class="row justify-content-center mb-4">
  <div class="col-lg-8 col-md-10 col-12">
    <div class="ratio ratio-4x3">
      <iframe src="https://www.youtube.com/embed/z9RqdH6WB20" title="Computer Backlighting with Music Visualizer" allowfullscreen></iframe>
    </div>
  </div>
</div>
<p>An early video testing the TLC5940s showing a rainbow pattern on the RGB LEDs</p>
<div class="row justify-content-center mb-4">
  <div class="col-lg-8 col-md-10 col-12">
    <div class="ratio ratio-4x3">
      <iframe src="https://www.youtube.com/embed/FCKEEMjqrG0" title="TLC5940 Rainbow Pattern Test" allowfullscreen></iframe>
    </div>
  </div>
</div>
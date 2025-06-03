---
title: Controlling Multiple I2C Devices with Arduino
date: 2014-06-23T04:15:55.000Z
author: Netopya
category: tutorials
tag: TUT
layout: post
og_image: http://www.netopyaplanet.com/gallery_images/4/full/full_IMG_5841-Copy.JPG
description: A project I was working on a while ago encountered a problem when we decided to use multiple I2C color sensors. The I2C protocol relies on the fact that each device you connect as a unique address. But in the case of the sensors we were using, the address is hard wired into the device, so connecting multiple identical sensors with the same permanent address would creating a conflict. This problem was easily solved with the use of an I2C multiplexer. Not much information was available on the web regarding this solution, but after doing some research we learned that the implementation is very easy. Read on pass the break to see what we learned and how you can use multiple identical I2C devices in your Arduino projects.
gallery_id: 4
overfold_content: |
  <div class="centered_image"><img src="/gallery_images/4/lrg/lrg_IMG_5841-Copy.jpg" class="img-thumbnail"/></div>
  <p>A project I was working on a while ago encountered a problem when we decided to use multiple I2C color sensors. The I2C protocol relies on the fact that each device you connect as a unique address. But in the case of the sensors we were using, the address is hard wired into the device, so connecting multiple identical sensors with the same permanent address would creating a conflict. This problem was easily solved with the use of an I2C multiplexer. Not much information was available on the web regarding this solution, but after doing some research we learned that the implementation is very easy. Read on pass the break to see what we learned and how you can use multiple identical I2C devices in your Arduino projects.</p>
---

<h3>Introduction</h3>
<p>In our project, we used six Adafruit I2C color sensors to sort up to six ping pong balls simultaneously. As we already discussed, this is problematic since each sensor is identical with the same address. An I2C multiplexer can be used to solve this issue but only allowing one color sensor to be accessed at a time. The multiplexer we chose was the Texas Intruments TCA9548A, which can switch up to 8 I2C lines. The two I2C lines of each color sensor (SDA and SCL) were connected to unique outputs on the I2C multiplexer. The multiplexer has its own address that could be written to by the Arduino with the Wire library to connect (and disconnect) the individual I2C lines of each sensor. The rest of this tutorial will explain the proof of concept that we realized to test this setup.</p>
<h2>Components and Wiring</h2>
<ul>
    <li>6x Adafruit Color Sensor (<a href="http://www.adafruit.com/products/1334">#1334</a>)</li>
    <li>I2C multiplexer TCA9548A</li>
    <li>Adafruit SOIC breakout (<a href="http://www.adafruit.com/products/1208">#1208</a>)</li>
    <li>Breadboard/Breadboard wires</li>
    <li>Arduino</li>
</ul>
<h3>Wiring</h3>
<p>The only complication with the wiring of this project is the TCA9548A chip itself, which commonly comes in a SOIC (surface mount) package, which is difficult to solder by hand and cannot be placed on a breadboard. In our case we used the Adafruit PCB SOIC-28 breakout board so that we could place the chip on and breadboard, and later insert into female headers on a custom PCB. Note that the breakout has 28 pins while the chip only has 24 pins; the extra 4 pins just remained unused (Consider that this messes up the numbering scheme printed on the breakout). On the wiring diagram above, I used a proper SOIC-24 breakout so that there is no funny numbering scheme (These are just harder to find). Soldering the surface mount chip was quite painstaking but we patiently succeed on our first try.</p>
<figure>
    <a href="/gallery_images/4/full/full_colorsensordia1_bb.png"><img class="img-thumbnail" src="/gallery_images/4/lrg/lrg_colorsensordia1_bb.jpg"/></a>
    <figcaption>Fig. 1 - Writing diagram of this project (Click for larger image)</figcaption>
</figure>
<p>The rest of the wiring of this project is quite straight forward.  The SCL and SDA inputs of the TCA9548A (pins 22 & 23) should be connected to the I2C pins of the Arduino (analog pins A5 and A4) with some pull-up resistors.  Each of the SCL and SDA lines of the color sensors should be connected to their own SCL, SDA output on the TCA9548A.</p>
<h3>Programming</h3>
<p>To program the test bench, I based my code on the <a href="https://learn.adafruit.com/adafruit-color-sensors/overview">Adafruit example project</a> for the sensors, but made modifications for our setup. The two fundamental differences were that I changed the color sensor object into an array of color sensor objects (six of them) and I inserted the following code to switch the I2C multiplexer to the sensor I wished to communicate with before any code that communicated with the sensors.</p>
<figure>
    <code>
    Wire.beginTransmission(0x70);</br>
    Wire.write(1 << i);</br>
    Wire.endTransmission();
    </code>
    <figcaption>Fig. 2 - Example code to switch the i2c multiplexer</figcaption>
</figure>
<p>This code simply begins the communication using the Wire library to the address of the I2C multiplexer (0x70) as stated in the documentation. Then it writes a number representing the number of the color sensor we wish to access. For example if we wanted to access the third sensor (the sensor connected to SDA2 and SCL2), we would assign a value of 2 to the <code>i</code> variable. Finally the Wire library function that completes the transmission is called. To further understand necessity the bit shift operator, the data sheet tells us that it reads the values of each bit in a 8-bit word to determine the state of each output. This is quite powerful and would allow various sensors to be selected and connected simultaneously, but in our case we only want one line to be activated at a time.</p>
<p>To retrieve the data from the sensors basing of the Adafruit example, I put all of the sensing code into a for loop iterating over the six sensors, making sure to use the Wire functions to switch the I2C multiplexer to the appropriate line. I modified the serial communication code by using ":" delimiters for each RGB and clear values, and ";" delimiters to separate color sensors. I removed the gamma table code because we were not concerned about the color accuracy of the sensor, just if it would be able to distinguish between white and orange. Another final change is that the Adafruit library for the color sensor announces over serial that it is connected when you initialize the sensor, which interferes with our serial communication. So solve this, simply comment out the line in the library with the problematic code. In the <code>Adafruit_TCS34725.cpp</code> file, just note line 167.</p>
<figure>
    <a href="/gallery_images/4/full/full_notethis.PNG"><img class="img-thumbnail" src="/gallery_images/4/lrg/lrg_notethis.jpg"/></a>
    <figcaption>Fig. 3 - Comment out this line from Adafruit_TCS34725.cpp!</figcaption>
</figure>
<p>To display this information on your computer I use a Processing app that reads the serial information and displays on the screen. There are six boxes showing the color from the sensor along with a vertical bar which indicates the clear value.</p>
<figure>
    <a href="/gallery_images/4/full/full_screenshot2.JPG"><img class="img-thumbnail" src="/gallery_images/4/lrg/lrg_screenshot2.jpg"/></a>
    <figcaption>Fig. 4 - Screenshot of the processing app with an orange ball on top of the 4<sup>th</sup> color sensor</figcaption>
</figure>
<h3>Conclusion</h3>
<p>This project was one component that was used on robot for a competition I participated in called the Engineering Games. This part of the robot was used to quickly sort the ping pong balls required for the challenge. A video showcasing our team and our robot for the competition can be see below. Note at timestamp <a href="https://www.youtube.com/watch?v=_erLsbOwTc4&list=UUK0Z87bs6PvbSnr4TRXAHFw#t=83">1:23</a> where the sorting mechanism is shown in action.</p>
<div class="row"><div class="col-lg-8 col-lg-offset-2 col-sm-10 col-sm-offset-1 centered_image"><div class="embed-responsive embed-responsive-16by9">
<iframe class="embed-responsive-item" width="533" height="400" src="//www.youtube.com/embed/_erLsbOwTc4" frameborder="0" allowfullscreen></iframe>
</div></div></div>
<p>In conclusion, I hope that sharing this project with you helped you to learn how to use multiple color sensors with an Arduino. Even if multiple I2C sensors have the address, it is very simple to wire them together though an I2C multiplexer and communicate to the multiplexer with 3 lines of code. If you have any questions, feel free to email me. As always, code is below. Enjoy!</p>
<p><br/><a href="https://github.com/Netopya/Arduino-I2C-Multi-Color-Sensors">Github repo</a><br/>
<a href="article_code/6/colorviewgood1.zip">Arduino code</a><br/>
<a href="article_code/6/sketch_131121b_good1.zip">Processing code</a><br/>
<a href="https://github.com/adafruit/Adafruit_TCS34725">Color Sensor code library (Adafruit)</a></p>
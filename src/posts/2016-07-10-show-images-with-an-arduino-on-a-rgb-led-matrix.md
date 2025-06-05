---
title: Show Images with an Arduino on a RGB LED Matrix
date: 2016-07-10T19:27:10.000Z
author: Netopya
category: projects
tag: Project
layout: post
og_image: http://netopyaplanet.com/article_images/12/full_IMG_1819.JPG
description: The Adafruit 1484 is an absolutely fantastic 32x32 LED matrix. Each one of the 1024 LEDs is an individually controllable RGB LED that allow us to display beautiful pixel art. First Robotics Competition team number 296, The Northern Knights, obtained this display to spruce up our robots. As a mentor on this team, I worked with students in order to develop a system with an Arduino to read images off a MicroSD card and display them on the LED matrix. Join us to learn the system inside out.
overfold_content: |
  <div class="text-center"><a href="/article_images/12/full_IMG_1819.jpg"><img src="/article_images/12/lrg_IMG_1819.jpg" class="img-thumbnail mb-3"/></a></div>
  <p>The Adafruit 1484 is an absolutely fantastic 32x32 LED matrix. Each one of the 1024 LEDs is an individually controllable RGB LED that allow us to display beautiful pixel art. First Robotics Competition team number 296, The Northern Knights, obtained this display to spruce up our robots. As a mentor on this team, I worked with students in order to develop a system with an Arduino to read images off a MicroSD card and display them on the LED matrix. Join us to learn the system inside out.</p>
---

## Parts

Our setup consists of only four components: an Arduino Mega, an Adafruit 1484 LED Matrix, a MicroSD card reader (Adafruit model number 254), and the wiring that connects everything together. In fact the wiring was such a mess that I created a custom Arduino shield to cleanly attach everything. We chose an Arduino Mega since the LED matrix and SD card reader libraries are quite heavy and we didn't want to risk running into any memory issues with and Arduino Uno.

<figure>
    <a href="/article_images/12/full_IMG_1909.jpg"><img src="/article_images/12/lrg_IMG_1909.jpg" class="img-thumbnail"/></a>
    <figcaption>Wiring setup without shield</figcaption>
</figure>

## Custom Arduino Shield

The above images shows the wiring situation before I created the custom Arduino shield. It was a bit of a mess and I was particularly concerned that putting this setup on a jostling robot could cause issues. Therefore I designed a custom circuit board in Eagle PCB and had it manufactured through OSH Park. It routes all 16 connections from the LED matrix and all 6 connections from the SD card reader to the appropriate ports on the Arduino. Furthermore we added pin-outs for serial communication and digital IO so that we can add features in the future if we want, such as communicating with the main robot. There are also pin-outs for 12v and 5v power. The serial and power pin-outs have extra design redundancies with possibility of using standard 0.1" pitch pins or screw terminals.

<figure>
    <a href="/article_images/12/full_IMG_1913.jpg"><img src="/article_images/12/lrg_IMG_1913.jpg" class="img-thumbnail"/></a>
    <figcaption>Wiring setup with the custom Arduino shield</figcaption>
</figure>

<div class="row">
    <div class="col-md-6">
        <figure>
            <a href="/article_images/12/diagram.svg"><img src="/article_images/12/diagram.svg" class="img-thumbnail"/></a>
            <figcaption>Custom Arduino shield PCB layout</figcaption>
        </figure>
    </div>
    <div class="col-md-6">
        <figure>
            <a href="/article_images/12/wiringdiagram.svg"><img src="/article_images/12/wiringdiagram.svg" class="img-thumbnail"/></a>
            <figcaption>Custom Arduino shield wiring diagram</figcaption>
        </figure>
    </div>
</div>

## Software

The strategy I used to display images on the matrix was to store picture information in text format. Using regular image files is not straight forward due to the limit computing resources of the Arduino, so the decision to go with a custom text format that could be easily parsed was made. I created a Java application to run on a computer to process all the images and convert them into my text format. The text files would then be saved onto a MicroSD card that would be placed into a MicroSD card reader connected to the Arduino. To display the images the Arduino would read these text files and output their colour information to the LED matrix.

The text file image format takes into consideration the facts that the images are 32x32 pixels and have 12-bit colour (This colour depth is a limitation of the Arduino's power as the matrix can display more). Since each pixel is 12-bits, each of the three colours (R, G, and B) is 4-bits which can be represented by a hexadecimal number. Therefore the image format consisted of 32 lines of text (for each of the 32 rows of pixels) and each row had 32 sets of pixel information. Each set of pixel information had 3 characters for each of the tree colours. These characters were text representations of a hexadecimal digit (`0` to `9`, followed by `a` to `f`). The astute among you will note that this is a waste of space since we are representing 4-bit RGB values with an 8-bit text character. However each image is still just over 3 KB, which means we can still store over 1 million images on a regular 4 GB SD card. Furthermore working with bytes greatly simplifies coding, since on the Java side we just need to write a colour component's `toHexString` value to the text file, and on the Arduino side we can read these values by parsing the text files one byte at a time.

Another feature of this format is that we can write an additional byte at the end of the text file to specify the duration we want to show the image for. By default images are shown for 10 seconds, however if this information is included the time can be adjusted to create animations by showing image frames more quickly, or by extending the duration of more prominent images. Currently values over 10 represent how many seconds to show the images for, while value less than 10 represent how many multiples of 300 milliseconds to display the image.

<figure>
    <a href="/article_images/12/full_Picture2.png"><img src="/article_images/12/lrg_Picture2_1.jpg" class="img-thumbnail"/></a>
    <figcaption>Diagram showing how image information from the text file is converted into a colour</figcaption>
</figure>

I created a simple console Java application called RainConverter to convert a set of pictures into this text image format. Simply point the app to a folder containing a set of images already at a 32 by 32 resolution. The app uses the `javax.imageio` package so a generous amount of input formats are supported including jpeg, png, bmp, and gif. Going through each image, each pixel is passed through a gamma lookup table for the matrix that converts each colour component to 4-bits and applies a colour correction curve for the display (this table was copied directly from the Adafruit source code for the led matrix). Each colour component is then converted into a hexadecimal string so that each colour is represented by a single character (3 characters for a pixel). Timing information can now be specified and will be added to the end of the string sequence. The collection of these hex strings are packaged into text files that can be copied to the MicroSD card.

On the Arduino side of things not much needs to be done since all of the images have been processed into data that can be easily outputted to the display. The main loop iterates through each text file on the MicroSD card in alphabetical order. For each file, three bytes are read at a time which make our three R, G, and B values. Note that they do go through a character to byte conversion to convert characters such as "1" to the numeric 1 and "f" to 15 since we are working with hexadecimal values. That's it! Each line in our text file is a pixel's Y coordinate, and we can count the number of 3-byte tuples we've passed to find the X coordinate. Going through each pixel gives us a complete image on the LED matrix.

<figure>
    <a href="/article_images/12/full_IMG_1922.jpg"><img src="/article_images/12/lrg_IMG_1922.jpg" class="img-thumbnail"/></a>
    <figcaption>The LED matrix showing pictures at a robotics competition in our pit area</figcaption>
</figure>

## Conclusion

Working with the Adafruit 1484 LED matrix has been a great learning experience. Since we obtained the display for the robotics team in 2014, we've been improving the software and electrical layout to find new ways to incorporate the display into our team's projects. In 2014 we had the display on our robot showing a slideshow of images while we competed. In 2015 we moved the LED matrix into our pit area due to real estate limitations of that year's bot. Looking forward, we may be considering using different boards such as the Raspberry Pi to control the display in order to show more complex animations. As always, source code for the Arduino displayer and Java image conversion can be found on GitHub at the following links.

## Code

[Arduino image displayer "dsplyr" <span class="glyphicon glyphicon-new-window" aria-hidden="true"></span>](https://github.com/Netopya/dsplyr)

[Java image converter "RainConverter" <span class="glyphicon glyphicon-new-window" aria-hidden="true"></span>](https://github.com/Netopya/RainConverter)

## CAD

[EAGLE CAD Sketch and Board files <span class="glyphicon glyphicon-download" aria-hidden="true"></span>](/article_code/FRC296LEDmatrix2.zip)
---
title: Audio Virtual Reality
date: 2014-09-01T22:51:21.000Z
author: Netopya
category: projects
tag: Project
layout: post
og_image: http://www.netopyaplanet.com/article_images/8/Audio%20Virtual%20Reality%20(HQ).jpg
description: Here is a video demoing my latest project called Audio VR. Virtual Reality is quite a hot topic nowadays and many devices aim to augment the experience of content on your computer. My idea was to augment the experience of the computer itself by moving the computer into your actual reality. Audio VR works by measuring the head's position and adjusting the audio output channels of the computer accordingly to simulate the location of the computer with respect to the head. By modifying the channels in the left and right ears of your headphones, you get a similar experience to using speakers. Read on to learn more about this project.
overfold_content: |
  <div class="row justify-content-center mb-4">
    <div class="col-lg-8 col-md-10 col-12">
      <div class="ratio ratio-16x9">
        <iframe src="https://www.youtube.com/embed/ZT7ZVP67Y0Y" title="Audio Virtual Reality Demo" allowfullscreen></iframe>
      </div>
    </div>
  </div>
  <p>Here is a video demoing my latest project called Audio VR. Virtual Reality is quite a hot topic nowadays and many devices aim to augment the experience of content on your computer. My idea was to augment the experience of the computer itself by moving the computer into your actual reality. Audio VR works by measuring the head's position and adjusting the audio output channels of the computer accordingly to simulate the location of the computer with respect to the head. By modifying the channels in the left and right ears of your headphones, you get a similar experience to using speakers. Read on to learn more about this project.</p>
---

<h3>Planning and programming</h3>
<p>When planning out this project, I was initially looking into IMUs (Inertial Measurement Units) that I could connect to an Arduino to record the head's motion. But then I asked myself if there were any devices I had lying around that had similar motion sensing capabilities and realized that I could use any modern mobile device for testing instead of investing in new hardware. I decided to use my 4th generation iPod Touch which has the requisite motion sensor and wireless connectivity already. To program the sensing side, I chose to create a web application since I am most comfortable with this type of programming. Furthermore, the code can be used on any device by just navigating to the URL. The DeviceOrientation Event Specification allows JavaScript to retrieve the motion information from the device to be used by the web application. AJAX requests transmit the orientation of the device to a server where a PHP file writes the data to a text file. On the client side, a C# program reads the orientation information from the text file and can calculates the appropriate volumes for the right and left ears. The Windows Core Audio API (with Vannatech wrappers) is used to have access to the Windows audio mixer and modify the left and right channels.</p>
<h3>Closing Thoughts</h3>
<p>In the end, I found the effect achieved a bit disappointing. The system doesn't really augment the experience of using a computer as much as I hoped, besides the realization that I don't frequently look side to side when using my computer. For these reasons I do not believe it will be worthwhile to go on and get better hardware to improve the project. One application I thought that this application may be useful would be in a multi-monitor setup where applications running on different monitors would have their individual left and right audio channels modified to match their position with respect to the user. For example looking at the left monitor would decrease the left track volume in applications on the rightmost monitor. But such an implementation would be difficult in Windows since security reasons prevent external modifications of a program's private audio mixer.</p>
<p>In the end I really enjoyed working on this project and impressed myself with what could be accomplished by throwing together every day electronic devices and making them work in unison for something that none of them were really designed for.</p>
<p><a href="http://github.com/Netopya/Audio-Virtual-Reality">Code on GitHub</a></p>
---
title: Improving JavaScript Code Quality
date: 2016-08-27T21:14:22.000Z
author: Netopya
category: tutorials
tag: Tutorial
layout: post
og_image: http://netopyaplanet.com/article_images/13/ori_Capture_sq1.png
description: Learn from the common coding quality mistakes we made in our software engineering project as pointed out by SonarQube.
overfold_content: |
  <div class="centered_image"><a href="/article_images/13/ori_Capture_sq1.png"><img src="/article_images/13/thb_Capture_sq1.png" class="img-thumbnail"/></a></div>
  <p>Coding conventions and code quality are practices of programming that are often ignored by many of us software developers. However when working on a school project with 6 other peers, I was responsible for setting up a program called SonarQube to analyze the quality of our code. Not only did SonarQube detect multiple quality issues with our code base, it also provided many useful suggestions to improve code readability, increase robustness against bugs, and every prevent security risks. The following blog post is based off of an e-mail that I wrote to the team explaining many common software quality issues that were arising in our code along with suggestions on how we could improve. I find that many of these tips can be applied to any JavaScript project and I am personally always taking them into account when I program web applications.</p>
---

<h2>Using spaces instead of tabs</h2>
<p>Developers should be in the habit of using spaces instead of tabs to indent and indicate structure in their code. Different editors can interpret tabs differently and give the white space they represent a different width. Code that is indented one way for a developer might appear differently on another developer's computer. This is especially a problem when there is a mix of tabs and spaces leading to indentation of lines can become really out of hand. One area where we had issues was with our code review tool Review Ninja which had a wider interpretation of tabs. This caused lines of code prefixed with tabs to seem more intended that lines with spaces. Reviewing code was much harder since lines would be randomly indented and it would be more difficult to read the structure of our code.</p>
<figure>
    <a href="/article_images/13/ori_Capture_ninja2.png"><img src="/article_images/13/thb_Capture_ninja2.png" class="img-thumbnail"/></a>
    <figcaption>An example of inconsistent indenting due to the mix of tabs and spaces in Review Ninja</figcaption>
</figure>
<p>Most editors use a monospace font so spaces are always the same size as all the other characters and everything is kept in proportion. We established a convention of indenting lines with 4 spaces, which is pretty standard. Most text editors can be configured to insert tabs in the place of spaces. In Notepad++ simply navigate to <code>Settings>Preferences...>Tab Settings</code> and check <code>Replace by space</code>.</p>
<p>Another quality issue that falls into this category of whitespace management is trailing whitespaces. They are useless and could cause issues when comparing versions of code as shown in the image below. The conversion of tabs into spaces and the removal of trailing whitespaces can be easily automated. In our project, since we only had a few files, I would manually open each file and apply the "TAB to Space" and "Trim Trailing Space" under "Edit->Blank Operations" in Notepad++ at the end of each Sprint to remove any whitespace problems that managed to sneak their way into our code.</p>
<figure>
    <a href="/article_images/13/ori_Capture_meld1.png"><img src="/article_images/13/thb_Capture_meld1.png" class="img-thumbnail"/></a>
    <figcaption>Notice this comparison in Meld that a line edit is being indicated. In reality the programmer added some lines, but the trailing whitespace results in the action being classified differently. This slows down code checking since we need to more closely analyze what the programmer did.</figcaption>
</figure>
<h2>Triple Equals</h2>
<p>A common confusion in JavaScript is the difference between using double equals (<code>==</code>) and triple equals (<code>===</code>). Programmers are often familiar with writing <code>==</code> from other programming languages and end up using the same <code>==</code> when programming in JavaScript. However, it is JavaScript's <code>===</code> that exhibits equality checking behaviour closest to the <code>==</code> of languages such as Java and C#. In Javascript <code>===</code> checks if two variables are of the same type and the same value. When <code>==</code> is used, if the variables are not of the same type, it will attempt to cast them to the same type so that their values can be compared. This casting operation may produce unexpected results and not cast our variable to a value that is appropriate for comparisons.</p>
<figure>
    <blockquote><p>Double equals is described as triple equals' evil brother, so due to the team's political alignments we should stick with the good guys.</p></blockquote>
    <figcaption>A quote from the e-mail sent to the team regarding code quality</figcaption>
</figure>
<p>For programmers unfamiliar with JavaScript, it is best to use <code>===</code> since this will behave like they are used to from other programming languages. If using a <code>===</code> doesn't work while using <code>==</code> does work, there is probably something wrong with your code where you end up comparing variables of different types. An example from our project was a case where we were checking the equality between two variables storing an id number. The variables where never equal when using <code>===</code>, but switching it to <code>==</code> worked as expected. The issue originated from an id value that was extracted from a string but never converted to an integer. Therefore, the equality check was comparing an id number with another id number but encoded as a string. Although this section of the code worked when using <code>==</code>, using <code>===</code> allowed us to notice our oversight, program the code to execute as we expected it too, and also to avoid further errors later in the code.</p>
<h2>Semicolons after functions</h2>
<p>In JavaScript there is a distinction between  <i>Function Declarations</i> and <i>Function Expressions</i>. Function Declarations are free hanging functions that can be accessed within their scope. Function Expressions are defined functions that are passed to a variable. Function Expressions should have a semicolon at the end of their statements, Function Declarations should not.</p>
<h3>Some examples:</h3>
<div class="table-responsive">
    <table class="table table-bordered">
        <thead>
            <th>Function type</th>
            <th class="success">Good</th>
            <th class="danger">Bad</th>
        </thead>
        <tbody>
            <tr>
                <th scope="row">Function Declaration</th>
                <td>
                    <code>
                        function nodesInEdges(a,b) {</br>
                        //...</br>
                        } //Good :)
                    </code>
                </td>
                <td>
                    <code>
                        function LanguageText() {</br>
                        //...</br>
                        }; //Bad :(
                    </code>
                </td>
            </tr>
            <tr>
                <th scope="row">Function Expression</th>
                <td>
                    <code>
                        this.toJSON = function() {</br>
                        //...</br>
                        }? //Good :)
                    </code>
                </td>
                <td>
                    <code>
                        this.addPair = function(lang, value){</br>
                        //...</br>
                        } //Bad :(
                    </code>
                </td>
            </tr>
        </tbody>
    </table>
</div>
<p>Often, this is usually not an issue since JavaScript is able to implicitly add a semicolon at the end of the statements where they were missing, but this may not always be the case. Basically if there's an equal sign, there should be a semicolon.</p>
<h2>Foreach loops require var declaration</h2>
<p>When using foreach loops, one should make sure to add var to the variable declaration, else JavaScript will create a global instance of the variable which can produce unpredictable results.</p>
<div class="table-responsive">
    <table class="table table-bordered">
        <tbody>
            <tr>
                <td>
                    <code>
                        for(val in POIList){</br>
                        // Bad :(</br>
                        }
                    </code>
                </td>
                <td>
                    <code>
                        for(var val in POIList){</br>
                        // Good :)</br>
                        }
                    </code>
                </td>
            </tr>
        </tbody>
    </table>
</div>
<h2>Commented out code</h2>
<p>A pretty big pet peeve of mine is to leave commended out code trailing around. I always recommend to use Git for even small projects which allows referencing previous versions of one's software. If you wish to archive something, commit what you have, then remove the commented code or any code you don't need in the foreseeable future, then commit your clean and shiny non-commented out code :)</p>
<figure>
    <a href="/article_images/13/ori_Capture_commented_code.png"><img src="/article_images/13/thb_Capture_commented_code.png" class="img-thumbnail"/></a>
    <figcaption>A git commit where commented code is replaced with the completed implementation</figcaption>
</figure>
<h2>TODO comments</h2>
<p>Programmers sometimes like to leave comments prefixed with TODO to indicate work that needs to be done inside the actual code itself. This is a very messy way of keeping track of what needs to be done and you should consider using a task or project management system. If something still needs to be done submit a ticket in your management software and. For our project in particular using TODO comments ways particularly gnarly since we were already using JIRA for task management. My compromise to the team was to resolve any TODO comments they generated by the end of the Sprint to avoid the technical debt created from combing through the code and evaluating TODO comments against tasks in JIRA.</p>
<figure>
    <a href="/article_images/13/ori_Capture_todo2.png"><img src="/article_images/13/thb_Capture_todo2.png" class="img-thumbnail"/></a>
    <figcaption>An example warning message from SonarQube of a lingering TODO comment</figcaption>
</figure>
<h2>Alerts</h2>
<p>Using JavaScript alerts is a security issue since they are mainly used for debugging purposes and their presence could indicate forgotten development code. Anything that is interacting with the user should provide a better user experience then native JavaScript alerts anyway. There are JavaScript libraries (such as <a href=” http://bootboxjs.com/”>Bootbox.js</a>) that accomplish this, or you can create your own custom notification system with better custom styling.</p>
<figure>
    <a href="/article_images/13/ori_Capture_alert1.png"><img src="/article_images/13/thb_Capture_alert1.png" class="img-thumbnail"/></a>
    <figcaption>SonarQube's rule regarding regular JavaScript alerts</figcaption>
</figure>
<p>Happy coding!</p>
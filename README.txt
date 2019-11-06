Program: Lab 01 Phase 02
Created by: Aidan Roth
Date: Fall 2019

What works: All the requirements for phase 1 are met. TagParser class organizes and pairs matching tags and stores them in a map. Malformed tags are caught and appropriate error messages are shown. PrintMap function outputs the well-formed tags in an organized manner. Requirements for phase 2 are met.

What doesn't work: TagParser will infinitely loop if the input file ends with an open tag like <br . This can be tested by using the included file infLoopTest.html as input for the program.
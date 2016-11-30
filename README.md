# Rat-Races

About: Rat Races was my first serious school project way back for my associates degree at Front Range (Like 4 or 5 years ago now).  At it's heart, Rat Race is just a fun experimental pac-man style video game. Although I'm not currently doing anything more with it, I highly encourage anybody who downloads this repository to try recoding things and come up with something new and awesome! 

*However, my apologies for the "bloatiness" of this repository because with it has some irrelevant things such as practice files and duplicate files (so I wouldn't have to go in and edit all the path locations again through visual studio) when I made the .exe file.  As a courtesy I did add a git ignore file post upload so it shouldn't index the larger files if you do start a repository for this.*

*Furthermore, if you are a potential employer checking out my repositories for clean code, this is NOT a demonstration of that! Better repositories would be either the FreeBillingProgram, the Sudoku andrioid app, or

Languages: This was created in Visual Studio using C++ and the SDL library.  It's probably best to recreate this setup if you want to work on it. Good idea to contact me too.

Purpose: This project was my first attempt to be a "master of all trades". By this I mean: I drew the mouse and animation frames, made the sound effects, wrote the music using Finale, played some of the soundbytes on the piano (such as the fox logo theme for the victory screen soundbyte, and a annoying crashing piano soundbyte for the losing screen), while coding it all FROM SCRATCH to put it all together (no copy and pasting or handtyping what someone else wrote verbatim!).  Took A LOT of time needless to say.

Features: Although there is only 1 executeable file, there is code for two versions of the game.  Both demonstrate a very twisted humor I have. The first game is just pretty much straight-forward pacman with some code to randomize the wall locations (two different ways, randomized customed positions, and randomization using some design algorithms) as well as some Evil Cat AI I never quite finished.  This would be a great thing for a code experimenter to work on and make more complete. 

The second version of the game (Was going to title it Mouse Trap) came to be because I came across a weird bug by matching up goofy variables which caused the walls to grow and shrink dynamically depending on how the user was moving.  Thus, I naturally made a game around this. The goal was to get to the endpoint by screwing around with bouncing collisions to navigate this metamorphic level before the timer ran out.  Since I'm incredibly evil, I added a little joke trap where if you land in it, you are stuck with no option to escape (but it eludes you into thinking you might be able to escape since the walls are moving with you, but I made sure this was impossible). This basically forces the user to stay thinking they can figure it out until a long timer runs out only to bring a very annoying and ridiculing losing screen as well as a fatal error to make the program crash.  To add further insult to injury I disabled the close button on the microsoft window frame too (the X at the top right of the screen) to prevent the user from exitting the game so they would be forced to wait for the very long timer, bwahahahahaha!!!! (Just remember to ctrl+alt+delete if you really want out)

However, if the user does succeed, then the reward is the exit button is re-enabled and they can leave the game without it crashing! Yippie!

How To Run: To run this game, simply download the master folder, go inside it and look for the Rat Races.exe and double click it.  I added a screenshot in case you have trouble finding it.

How To Play: Use the arrow keys on the lower right of the keyboard to navigate the mouse to reach the cheeses until you collect 20. Hit 'm' to toggle the original music I wrote for this game with the same title (Rat Race). If you read up above, the normal Windows 'X' button is disabled until you finish the game and is re-enabled if you win, or the game crashes if you lose.  Also notice that the background does move dynamically with the mouse for a cool visual effect.  Have fun and don't take any of my jokes too seriously!!!! 

And please feel free to pull and push some on your own branch if you have some awesome changes to make!

Happy Rat Racing!
- Anthony Walter (NetDoodler)

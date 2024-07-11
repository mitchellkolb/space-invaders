-----------------------------------------------------------------------------

This README is for PA6 in Nadra Guizani's CPTS 122 Summer Course.

-----------------------------------------------------------------------------

The group members that worked on this project were:

	Sebastian Cordero
	Jonathan Qiaoshun Sun
	Dewan Salehin
	Mitchell Kolb

-----------------------------------------------------------------------------

If you are on an Apple device these are the command I used to run the game.

1.) Your terminal should be opened to the game folder
2.) Enter "g++ -c main.cpp points.cpp"
3.) Enter "g++ main.o points.o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system"
4.) Enter "./sfml-app" to run the game. 

-----------------------------------------------------------------------------

					Overview of our project:

We built a working version of the 1978 classic game "Space Invaders".
This version includes customized sprites and music for the players' 
ship, missile, alien ships, background, sound effects, background 
music. In this game the goal is to shoot the alien ships down with 
your missile and to see how long you can stay alive before the alien 
ships get past you. As the player you are able to move left and 
right with the 'A' and 'D' keys on your keyboard and shoot missiles
by pressing the space key. The players ship can move off the left
and right sides of the screen and return on the other side. This is
a new feature we implememted that isn't in the original game. The 
alien ships will move left and right down the map and try to get past
the player. If one ship manages to do that the game will end. Once
the game ends and the player has pressed the 'S' key to close the
game window the score of how many alien ships the player shot will 
show.

-----------------------------------------------------------------------------

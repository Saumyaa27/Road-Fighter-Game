# Road-Fighter-Game 
Road Fighter Game using OpenGL
Computer Graphics mini project

**INTRODUCTION:**

The game is a single-player type in the racing genre. The game loads with a start screen. The start screen mentions the controls used to play the game. To start the game, the user would have to press the spacebar key. When the game starts we see a forest scene wherein there is a road with lots of cars. There is a player (main car) that has to race forward while saving itself from colliding with other vehicles which act as obstacles. These vehicles(obstacles) move in the opposite direction to that of the main car (player). To save itself from colliding the player car can move in the left and right direction. The game has 2 levels. The first level has a forest scene. When the score becomes higher than 500 points, level 2 automatically starts. In level 2, the view changes to the city scene, and the obstacle cars change to more powerful racer cars. The lives and the real-time score are continuously displayed on the screen. The player car has 3 lives i.e. it can collide a maximum of 3 times with the obstacle cars, after which the game would end. When the game gets over, the score for the current game along with the highest score of all the consecutive games is displayed on the screen. The user can replay the game by pressing the spacebar key.

**CONTROLS-**<br>
SPACEBAR_KEY: to start the game/ restart the game

LEFT_ARROW_KEY: to move left

RIGHT_ARROW_KEY: to move right

**FUNCTIONS IMPLEMENTED:**<br>
Move(): <BR>
It is used to do smooth transitioning of the vehicle, as instead of directly translating the vehicle from one lane to another, it will translate in small gaps, which gives a smooth transition effect.

OtherV_pos(): <BR>
This function is used to initialize the other vehicle's position. It uses random numbers to decide in which lane the car should be and stores these values in an array which can then be used for displaying cars.

Initialize(): <BR>
It is used to reset the game after the collision, as after the collision, life is decreased by 1 and the other vehicles are sent back to their starting position. And the Main vehicle is also brought back to its original place.

drawRoad(): <BR>
It is used to draw the road, as it makes a rectangle of grey colour, which will function as the road.

drawDivider():  <BR>
It is used to draw the white lines on the road, which signifies the lanes of the road. The moving effect is given by translating the divider of the road.

SpecialKey(): <BR>
It is used to move the car left and right, it detects the keypress and accordingly it decides if the car is to be translated to left or right.

NormalKey():  <BR>
It is used to start the game. If the user presses the space key on the start or end screen then it will detect that and start the game, also if the user presses ESC key it quits the game.

Game_end():  <BR>It is used to display the end game screen. This screen shows the current score, the highest score of the current session. Also, the player can restart the game by pressing the space key.

startGame():  <BR>It displays the first level of the game. In this, we are using other functions to display the car, other vehicles, and the trees and road. This function checks if a collision has occurred and if so, then it decrements the lives and displays the end screen if lives are 0.

drawTree(): <BR> It is used to draw trees at the x and y coordinates given as argument. It draws three triangles to construct the bottom and top parts of the tree.

positionTrees():  <BR>It is used to specify the coordinates of the trees to be drawn on either side of the lane and thereafter, calling the drawTree() function.

drawBuilding():  <BR>It is used to draw the buildings which appear on either side of the lane using the x and y coordinates passed as an argument to this function. It draws a black-colored rectangle and subsequently calls the drawWindow() function.
drawWindow: It is used to draw the windows of the buildings using the x and y coordinates provided as an argument. It draws a white-colored square corresponding to each window.

secondDesign():  <BR>It is used to initialize the setting of level 2 which is a scene of a city, thus calling drawBuilding, drawRoad, drawDivider, drawVehicle, and drawotherV_ functions to draw the objects that appear in this scene. Apart from this, it helps in the translation of the divider by updating the value of the ‘divider’ variable which specifies the amount to be moved in the y-direction. This function also checks whether our vehicle collides with other vehicles or not. If it is so then it reduces the number of lives. It also gives calls to Text and Num functions to display the current score and the number of lives the player has.

drawVehicle():  <BR>It is used to draw the main car i.e. the player car. A car is drawn using GL_QUADS and GL_POINTS.

drawother_V():  <BR>It is used to draw the cars that move in the opposite direction. Cars are drawn using GL_QUADS and GL_POINTS. It also keeps a track of the distance between the main car and the opponent car. If the y-coordinate is less than 90 units then the cars are in close proximity. If the x-coordinate is less than 50 units means that the cars have collided. If the y-coordinate is less than -25 then it means that the car is not visible on the screen. In that case, random coordinates are chosen for displaying the next car.


firstDesign():  <BR>It is used to load the start screen. It calls the functions drawRoad, drawDivider,  positionTrees(), and drawVehicle(). It also displays the name of the game, along with the rules by calling the function Text().

Text(): <BR> It is used to display the text on the screen. We first load the identity matrix thereby replacing the current projection matrix and then specify the raster position with respect to the origin. This specifies a 3D position in the window which forms the lowermost corner of the text we need to write.

Num():  <BR>It is used to display numeric data such as score, lives, etc on the screen. We first load the identity matrix thereby replacing the current projection matrix and then specify the raster position with respect to the origin. This specifies a 3D position in the window which forms the lowermost corner of the text we need to write.



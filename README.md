# OBJECT AVOIDING OBSTACLES

<a name="br2"></a>**Introduction:**

Our project is Object Avoiding Obstacles in 3-D. In this project we have basically made a spaceship (our object) that
is avoiding the multiple incoming asteroids (our obstacles) in space. The asteroids are coming from random
directions in space and the user will have to control the spaceship using the predefined keys to make it avoid the
asteroids. We have made this project as a game that the user can play. If the spaceship goes on without colliding with
the asteroids the score of the player will increase. If the spaceship collides with the asteroid then the game is over
and we display the final score. Our HOME window is shown below:

The game is made such that the asteroids are placed at a fixed position in space and the spaceship is moving in their
direction to avoid the collision. Our spaceship and asteroid are all made as models in a software called ‘Blender’, this
software allows us to make different models and then use them in our OpenGL project. Then we have imported these
models from Blender in OpenGL as .obj file extensions. Basically the .obj of each model contains the coordinates
and colors of that model that we have to use in our project. Moreover the user can also select the spaceship of his
choice to play the game. There are two modes to play the game namely Day and Night mode which we are
implementing using the Lighting Effect. Yo u can also listen to some nice tunes while playing the game making it fun
to play.

**Libraries Required:**

**1) #include "\.\./Library/main\.h"** :- This library is used to load and render the \.obj files and \.mtl files into OpenGL. This library contains following libraries:

> &nbsp;&nbsp;&nbsp;&nbsp;**a) #include "../Library/loadpng.h"**

> &nbsp;&nbsp;&nbsp;&nbsp;**b) #include "../Library/process\_image.h"**

> &nbsp;&nbsp;&nbsp;&nbsp;**c) #include "../Library/gl\_texture.h"**

**2) #include "\.\./Library/soil/SOIL\.h"** :- This library is used to render images into OpenGL\.

**3) #include <bits/stdc++\.h>** :- This library contains basic C++ in-built functions for calculations, using string,vectors, etc.

**4) #include <cstdlib>** :- This library contains system calls and we are using it for the play() system call\.

**Steps to run the project:**

\- Install OpenGL by following the instructions using the below link:

> [https://www.cyberithub.com/how-to-install-opengl-library-on-ubuntu-20-04-lts-focal-fossa](https://www.cyberithub.com/how-to-install-opengl-library-on-ubuntu-20-04-lts-focal-fossa/)[/](https://www.cyberithub.com/how-to-install-opengl-library-on-ubuntu-20-04-lts-focal-fossa/)

\- Install below libraries from linux terminal for sound functionality:
> sudo apt-get install sox

> sudo apt-get install libsox-fmt-mp3

\- When we unzip the file, open the ‘Space Game’ folder, inside that folder open the ‘Game’ folder. Open the
 linux terminal in that folder and execute the below two commands.

\- To **Compile** the program use below command in terminal:

> g++ main.cpp -lglut -lGLU -lGL -lSOIL

\- To **Run** the program use below command in terminal:

> ./a.out

**Instructions to play the game:**

To start the game run the above command. A HOME window will appear where we have 3 options:

 1. PLAY : to play the game

 2. INSTRUCTIONS : to go to instruction window

 3. QUIT : to quit the game

If we click on the ‘PLAY’ button then we go to our next window in which we have to select the spaceship with which we have to play the game. There are 3 options for spacecraft:

 1. X-WING

 2. U.F.O

 3. SKY BLADE

We can select among the 3 spaceships using 2 buttons:
 
 1. The ‘>’ button goes to the next spaceship.
 
 2. The ‘<’ button goes to the previous spaceship.




<a name="br4"></a>Between these two buttons we have our sample model of each spaceship. Then below this model we have 2 buttons:

 1. ‘SELECT’ - to select the current spaceship and start the game,

 2. ‘HOME’ - to go back to the home window.

When we press on the ‘SELECT’ button our game starts. There are basically 4 keys using which the user can control the spaceship’s movement in four directions in the space. These keys are:

 1. ‘UP arrow’ key: used to move the spaceship in the upward direction.

 2. ‘DOWN arrow’ key: used to move the spaceship in the downward direction.

 3. ‘LEFT arrow’ key: used to move the spaceship in the left direction.

 4. ‘RIGHT arrow’ key: used to move the spaceship in the right direction.

Moreover we can also rotate the spaceship in all 3 dimensions using the mouse scroller (or touchpad) to avoid the
asteroids.

We also have two modes in our game namely DAY and NIGHT mode. Default mode is the Day mode. We have to
press the ‘N’ key to Enable (or Disable) the night mode. Then in the night mode we can also increase the shininess
property of our materials. Pressing ‘+’ key increases the shininess and pressing ‘-’ key decreases the shininess of the
materials.

When we are playing the game we can pause the game using the ‘SPACEBAR’ key. To PLAY the game again after
PAUSE we press ‘SPACEBAR’ again. When we press that ‘SPACEBAR’ key to PAUSE a window appears with a
HOME button in the top left corner to go to the HOME window.

We can play the game using these above instructions, but if we crash into some asteroid then the game is over and a
window appears that displays our ‘SCORE’ and the ‘DISTANCE COVERED’. Then again we have 3 options:
 1. ‘HOME’ - go to home window

 2. ‘PLAY AGAIN’ - to restart the game and go to the spacecraft selecting window

 3. ‘QUIT’ - quit the game

Following is the list of instructions to play the game:




<a name="br5"></a>**Functionalities Implemented:**

**DAY and NIGHT Mode:**

Using the Lighting Effect we have implemented two modes in our game, Day and Night mode. In day

mode we can see all the default colors of our object like spaceship, asteroids and rendered images. In night

mode we are reducing the intensity of the light. Also in night mode we can control the shininess of the

reflecting surface of the materials. In the below code GL\_AMBIENT is used to change between Day and

Night modes and GL\_SPECULAR is used to control the shininess of the materials.

**Multiple Spaceships:**

In our game the user has the choice to select the spaceship with which he wants to play the game. There are

3 spaceship models available for the user to choose from and play the game. There is a special window in

which users can select the spaceship to play. From that window the user can proceed to play the game or

can return to the home window. Below is the code to represent our selected spaceship in the space:




<a name="br6"></a>**Image Rendering:**

Another small thing that we have implemented in our project is that we have rendered an image of a galaxy

in the background of almost every window. It makes the game look attractive to the user. In the below

galaxy() function we Enable the texture then bind the image with that texture. Then we make a quadrilateral

to fit that image into.

**Collision Detection:**

One of the most important features of our game is the collision detection of the spaceship with the

asteroids, the whole idea of our project is based on this. For detecting the collision we have considered

every model (spaceship and asteroids) as a 3-D sphere. Then if the coordinates of the spaceship sphere

matches with the coordinates of the asteroid sphere during playing then we assume that the collision is

taking place. We have to adjust the sphere around every asteroid so that it collides accurately with the

sphere of the spaceship. Below is the code of collision detection for spacecraft 1 where we are defining its

thresholds of the sphere around it.



<a name="br7"></a>**Increasing Levels:**

When we are playing the game the level of the game is increasing after crossing every 9 asteroids. When

the level is increased the speed of the incoming asteroids and the movement speed of the spaceship is also

increased. Below is the code for the same:

**Score Calculation:**

When we start our game the Score starts from 0 and keeps on increasing as our spaceship moves in the

space without collison. After every 15 milliseconds our Distance increases by 10 meters and whenever

(distance % 9 == 8) our Score increases by 1. When the asteroid and the spaceship collide with each other

we display the score and the distance covered on another window.

**Sound:**

We have also implemented sound features in our game. When the user plays the game he can hear some

nice tunes which stop when he quits the game.

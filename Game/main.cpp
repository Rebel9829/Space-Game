// Including libraries
#include "../Library/main.h"
#include "../Library/soil/SOIL.h"
#include <bits/stdc++.h>
#include <cstdlib>

// ob models relative addresses
std::string spacecraft1_str = "Models/X-WING1.obj";
std::string spacecraft2_str = "Models/spacecraft2.obj";
std::string spacecraft3_str = "Models/spacecraft3.obj";
std::string satellite_str = "Models/satellite.obj";
std::string asteroid4_str = "Models/as4.obj";
std::string asteroid5_str = "Models/as5.obj";
std::string asteroid6_str = "Models/as6.obj";
std::string asteroid7_str = "Models/as7.obj";
std::string asteroid8_str = "Models/as8.obj";
std::string asteroid9_str = "Models/as9.obj";
std::string asteroid10_str = "Models/as10.obj";

// Coordinates of centres of obj models would be stored in these
// float spacecraft_x, spacecraft_y, spacecraft_z;
float spacecraft1_x, spacecraft1_y, spacecraft1_z, trans_y, ast_y;
float spacecraft2_x, spacecraft2_y, spacecraft2_z;
float spacecraft3_x, spacecraft3_y, spacecraft3_z;
float spacecraft1_x_old, spacecraft1_y_old, spacecraft1_z_old;
float spacecraft2_x_old, spacecraft2_y_old, spacecraft2_z_old;
float spacecraft3_x_old, spacecraft3_y_old, spacecraft3_z_old;
float satellite_x, satellite_y, satellite_z;
float asteroid4_x, asteroid4_y, asteroid4_z;
float asteroid5_x, asteroid5_y, asteroid5_z;
float asteroid6_x, asteroid6_y, asteroid6_z;
float asteroid7_x, asteroid7_y, asteroid7_z;
float asteroid8_x, asteroid8_y, asteroid8_z;
float asteroid9_x, asteroid9_y, asteroid9_z;
float asteroid10_x, asteroid10_y, asteroid10_z;
// float particle_x, particle_y, particle_z;

float angle_x = -45.0f, angle_y = 90.0f;
float angle_satellite_x = 0.0f, angle_satellite_y = 45.0f;
float ast_pos = 1000.0;

int x_old = 0, y_old = 0, x_satellite_old = 0, y_satellite_old = 0;
int level = 1;
float level_speed = 0.08;
int current_scroll = 5;
float distance_covered = 0;
int score = 0;
float zoom_per_scroll = 0;

bool closed = false;           // Indicates that the window has been closed (Quit) so that we can stop background music
bool is_holding_mouse = false; // would be made true if user is holding mouse
bool is_updated = false;
bool start = false; // indicates whether to start the game and start calculating scores
bool change_mode = true;
bool space_pressed = false; // indicates whether space is pressed (indicates to pause or not)

// following flags indicate if to show various menu
bool show_menu = true;
bool info_menu = false;
bool collision_menu = false;
bool spacecraft_menu = false;

// indicates which model is selected by user
bool craft1 = true, craft2 = false, craft3 = false;

// rotation angles for different aircrafts
float hor_speed = 0.2, ver_speed = 0.15;
float angle_craft1_x = 0.0f, angle_craft1_y = 90.0f;
float angle_craft2_x = 0.0f, angle_craft2_y = 90.0f;
float angle_craft3_x = 0.0f, angle_craft3_y = 90.0f;
GLfloat b_x = 0.0, b_y = 0.0, b_z = 0.0;
GLfloat a_x = 0.25, a_y = 0.25, a_z = 0.25;
int craft1_x = 0, craft1_y = 0;
int craft2_x = 0, craft2_y = 0;
int craft3_x = 0, craft3_y = 0;

// Model class has been defined in main.h header file
Model spacecraft1_model;
Model spacecraft2_model;
Model spacecraft3_model;
Model satellite_model;
Model asteroid4_model;
Model asteroid5_model;
Model asteroid6_model;
Model asteroid7_model;
Model asteroid8_model;
Model asteroid9_model;
Model asteroid10_model;
Model particle_model;

GLuint texture[5];

void LoadGLTextures()
{
    // texture
    texture[1] = SOIL_load_OGL_texture("./Images/1.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);                           // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);                           // Enable Smooth Shading
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);              // Black Background
    glClearDepth(1.0f);                                // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                           // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                            // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
}

// Returns square of the euclidean distance
float distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float dist = 0;
    dist += (x1 - x2) * (x1 - x2);
    dist += (y2 - y1) * (y2 - y1);
    dist += (z1 - z2) * (z1 - z2);
    return dist;
}

// This function checks whether collison has happened or not , would be called each time redisplay is called
bool check()
{
    if (!start)
    {
        return true;
    }
    bool ans = true;

    if (craft1)
    {
        ans = ans and (distance(asteroid6_x, asteroid6_y + 10 + ast_y, asteroid6_z - 10, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 35);
        ans = ans and (distance(asteroid9_x + 5, asteroid9_y + 20 + ast_y, asteroid9_z - 4, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 35);
        ans = ans and (distance(asteroid4_x - 10, asteroid4_y + 30 + ast_y, asteroid4_z - 14, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 28);
        ans = ans and (distance(asteroid5_x - 5, asteroid5_y + 40 + ast_y, asteroid5_z - 10, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 25);
        ans = ans and (distance(asteroid6_x + 9, asteroid6_y + 50 + ast_y, asteroid6_z - 10, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 25);
        ans = ans and (distance(asteroid10_x - 5, asteroid10_y + 60 + ast_y, asteroid10_z - 4, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 25);
        ans = ans and (distance(asteroid8_x - 8, asteroid8_y + 70 + ast_y, asteroid8_z - 12, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 25);
        ans = ans and (distance(asteroid5_x + 5, asteroid5_y + 80 + ast_y, asteroid5_z - 10, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 25);
        ans = ans and (distance(asteroid7_x - 5, asteroid7_y + 90 + ast_y, asteroid7_z - 15, spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3) > 25);
    }
    else if (craft2)
    {
        ans = ans and (distance(asteroid6_x, asteroid6_y + 10 + ast_y, asteroid6_z - 10, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
        ans = ans and (distance(asteroid9_x + 5, asteroid9_y + 20 + ast_y, asteroid9_z - 4, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
        ans = ans and (distance(asteroid4_x - 10, asteroid4_y + 30 + ast_y, asteroid4_z - 14, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
        ans = ans and (distance(asteroid5_x - 5, asteroid5_y + 40 + ast_y, asteroid5_z - 10, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
        ans = ans and (distance(asteroid6_x + 9, asteroid6_y + 50 + ast_y, asteroid6_z - 10, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
        ans = ans and (distance(asteroid10_x - 5, asteroid10_y + 60 + ast_y, asteroid10_z - 4, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
        ans = ans and (distance(asteroid8_x - 8, asteroid8_y + 70 + ast_y, asteroid8_z - 12, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
        ans = ans and (distance(asteroid5_x + 5, asteroid5_y + 80 + ast_y, asteroid5_z - 10, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
        ans = ans and (distance(asteroid7_x - 5, asteroid7_y + 90 + ast_y, asteroid7_z - 15, spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10) > 16);
    }
    else if (craft3)
    {
        ans = ans and (distance(asteroid6_x, asteroid6_y + 10 + ast_y, asteroid6_z - 10, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 35);
        ans = ans and (distance(asteroid9_x + 5, asteroid9_y + 20 + ast_y, asteroid9_z - 4, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 35);
        ans = ans and (distance(asteroid4_x - 10, asteroid4_y + 30 + ast_y, asteroid4_z - 14, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 28);
        ans = ans and (distance(asteroid5_x - 5, asteroid5_y + 40 + ast_y, asteroid5_z - 10, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 25);
        ans = ans and (distance(asteroid6_x + 9, asteroid6_y + 50 + ast_y, asteroid6_z - 10, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 25);
        ans = ans and (distance(asteroid10_x - 5, asteroid10_y + 60 + ast_y, asteroid10_z - 4, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 25);
        ans = ans and (distance(asteroid8_x - 8, asteroid8_y + 70 + ast_y, asteroid8_z - 12, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 25);
        ans = ans and (distance(asteroid5_x + 5, asteroid5_y + 80 + ast_y, asteroid5_z - 10, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 25);
        ans = ans and (distance(asteroid7_x - 5, asteroid7_y + 90 + ast_y, asteroid7_z - 15, spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z + 3) > 25);
    }

    return ans;
}

// returns random float numbers , this function helps in drawing of background stars
float randomFloat()
{
    // srand(1);
    return -20.0f + 40.0f * ((float)(rand()) / RAND_MAX);
}
// background() function makes the background filled of stars
void background()
{
    glColor3f(1, 1, 1);

    srand(1);
    // generate 5000 random coordinates
    for (int i = 0; i < 5000; i++)
    {
        int s = ((int)rand()) % 3 + 1;
        glPointSize(s);
        glBegin(GL_POINTS);
        float a = randomFloat();
        float b = randomFloat();
        float c = randomFloat();
        glVertex3f(a, b, c);
        glEnd();
    }
}

GLfloat white[] = {1., 1., 1., 1.};
GLfloat mat_shininess[] = {10};
GLfloat light_pos[] = {0.0f, 0.0f, 10.0f, 10.0f};
GLfloat amb[] = {1, 1, 1, 1};

void init()
{
    LoadGLTextures();
    glEnable(GL_LIGHT0);                             // Enables a light source.
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);    // Sets the position of a light source.
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enables two-sided lighting.

    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);   // Sets the ambient color of a light source.
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white); // Sets the diffuse color of a light source.

    // Sets the clear color of the framebuffer.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Sets the current matrix mode to projection.
    glMatrixMode(GL_PROJECTION);

    // Replaces the current matrix with the identity matrix.
    glLoadIdentity();

    // Sets the material shininess of front and back faces.
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    // Defines a perspective projection matrix.
    gluPerspective(45.0, 1.0, 1.0, 2000.0);

    // Sets the current matrix mode to modelview.
    glMatrixMode(GL_MODELVIEW);

    // Specifies the pixel arithmetic for blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enables anti-aliasing for lines.
    glEnable(GL_LINE_SMOOTH);

    // Sets the wrap parameter for texture coordinate S to repeat.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    // Sets the wrap parameter for texture coordinate T to repeat.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Sets the texture minifying function to linear interpolation.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Sets the texture magnifying function to linear interpolation.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Enables 2D texturing.
    glEnable(GL_TEXTURE_2D);

    // Enables depth testing.
    glEnable(GL_DEPTH_TEST);

    // Loads the 3D models for spacecrafts, satellites, and asteroids
    spacecraft1_model.load(spacecraft1_str.c_str());
    spacecraft2_model.load(spacecraft2_str.c_str());
    spacecraft3_model.load(spacecraft3_str.c_str());
    satellite_model.load(satellite_str.c_str());
    asteroid4_model.load(asteroid4_str.c_str());
    asteroid5_model.load(asteroid5_str.c_str());
    asteroid6_model.load(asteroid6_str.c_str());
    asteroid7_model.load(asteroid7_str.c_str());
    asteroid8_model.load(asteroid8_str.c_str());
    asteroid9_model.load(asteroid9_str.c_str());
    asteroid10_model.load(asteroid10_str.c_str());

    // Sets the initial position of spacecraft1
    spacecraft1_x = spacecraft1_model.pos_x;
    spacecraft1_y = spacecraft1_model.pos_y;
    spacecraft1_z = spacecraft1_model.pos_z - 1.0f;

    // Sets the initial position of spacecraft2
    spacecraft2_x = spacecraft2_model.pos_x;
    spacecraft2_y = spacecraft2_model.pos_y;
    spacecraft2_z = spacecraft2_model.pos_z - 1.0f;

    // Sets the initial position of spacecraft3
    spacecraft3_x = spacecraft3_model.pos_x;
    spacecraft3_y = spacecraft3_model.pos_y;
    spacecraft3_z = spacecraft3_model.pos_z - 1.0f;

    // These lines of code are assigning initial values to various variables, such as positions and zoom level, based on the initial positions and properties of various models such as spacecrafts, satellites, and asteroids.
    spacecraft1_x_old = spacecraft1_x;
    spacecraft1_y_old = spacecraft1_y;
    spacecraft1_z_old = spacecraft1_z;

    spacecraft2_x_old = spacecraft2_x;
    spacecraft2_y_old = spacecraft2_y;
    spacecraft2_z_old = spacecraft2_z;

    spacecraft3_x_old = spacecraft3_x;
    spacecraft3_y_old = spacecraft3_y;
    spacecraft3_z_old = spacecraft3_z;

    satellite_x = satellite_model.pos_x;
    satellite_y = satellite_model.pos_y;
    satellite_z = satellite_model.pos_z - 1.0f;

    asteroid4_x = asteroid4_model.pos_x;
    asteroid4_y = asteroid4_model.pos_y;
    asteroid4_z = asteroid4_model.pos_z - 1.0f;

    asteroid5_x = asteroid5_model.pos_x;
    asteroid5_y = asteroid5_model.pos_y;
    asteroid5_z = asteroid5_model.pos_z - 1.0f;

    asteroid6_x = asteroid6_model.pos_x;
    asteroid6_y = asteroid6_model.pos_y;
    asteroid6_z = asteroid6_model.pos_z - 1.0f;

    asteroid7_x = asteroid7_model.pos_x;
    asteroid7_y = asteroid7_model.pos_y;
    asteroid7_z = asteroid7_model.pos_z - 1.0f;

    asteroid8_x = asteroid8_model.pos_x;
    asteroid8_y = asteroid8_model.pos_y;
    asteroid8_z = asteroid8_model.pos_z - 1.0f;

    asteroid9_x = asteroid9_model.pos_x;
    asteroid9_y = asteroid9_model.pos_y;
    asteroid9_z = asteroid9_model.pos_z - 1.0f;

    asteroid10_x = asteroid10_model.pos_x;
    asteroid10_y = asteroid10_model.pos_y;
    asteroid10_z = asteroid10_model.pos_z - 1.0f;

    zoom_per_scroll = -spacecraft1_model.pos_z / 10.0f;
}

void galaxy()
{
    // Code for changing day and night mode and changing shininess property of materials
    GLfloat white8[] = {a_x, a_y, a_z, 1.0};
    GLfloat white2[] = {b_x, b_y, b_z, 1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white8);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white2);

    glPushMatrix();
    if (change_mode)
    {
        glDisable(GL_LIGHTING);
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]); // Binding image to texture
    glTranslatef(0, 0, -30);
    glBegin(GL_QUADS); // Creating Quad/Polygon and putting texture on it so that image is rendered on this polygon
    glTexCoord2f(0.0f, 0.0f);
    float xmin = -20, xmax = 20, ymin = -20, ymax = 20;
    glVertex3f(xmin, ymin, -20.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(xmin, ymax, -20.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xmax, ymax, -20.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(xmax, ymin, -20.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (!show_menu && !collision_menu && !spacecraft_menu && !info_menu) // Playing screen
    {
        galaxy();     // Creating galaxy
        if (!check()) // Checking for collision
        {
            // std::cout<<"yayy\n";
            system("play -q collison.wav &");
            sleep(1);
            collision_menu = true;
            start = false;
            goto jump; // If collision then no need to render things written down
        }
        glPushMatrix();
        glDepthMask(GL_FALSE); // disable depth writes

        glDisable(GL_LIGHTING);

        glTranslatef(0, trans_y, 0);
        background();

        glEnable(GL_LIGHTING);
        glDepthMask(GL_TRUE); // enable depth writes
        glPopMatrix();

        glPushMatrix();

        // Translate Asteroids downwards
        glTranslatef(0, ast_y, 0);

        // Create asteroids
        glPushMatrix();
        glTranslatef(asteroid6_x, asteroid6_y + 10, asteroid6_z - 10);
        asteroid6_model.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(asteroid9_x + 5, asteroid9_y + 20, asteroid9_z - 4);
        asteroid9_model.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(asteroid4_x - 10, asteroid4_y + 30, asteroid4_z - 14);
        asteroid4_model.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(asteroid5_x - 5, asteroid5_y + 40, asteroid5_z - 10);
        asteroid5_model.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(asteroid6_x + 9, asteroid6_y + 50, asteroid6_z - 10);
        asteroid6_model.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(asteroid10_x - 5, asteroid10_y + 60, asteroid10_z - 4);
        asteroid7_model.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(asteroid8_x - 8, asteroid8_y + 70, asteroid8_z - 12);
        asteroid8_model.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(asteroid5_x + 5, asteroid5_y + 80, asteroid5_z - 10);
        asteroid5_model.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(asteroid7_x - 5, asteroid7_y + 90, asteroid7_z - 15);
        asteroid10_model.draw();
        glPopMatrix();

        glPopMatrix();

        glPushMatrix();

        // Draw corresponding spacecraft
        if (craft1)
        {
            glTranslatef(spacecraft1_x, spacecraft1_y - 8.0, spacecraft1_z + 3);
            glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
            glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
            glRotatef(90, 0, 0, 1);
            spacecraft1_model.draw();
        }
        else if (craft2)
        {
            glTranslatef(spacecraft2_x, spacecraft2_y - 8.15, spacecraft2_z - 10);
            glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
            glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
            glRotatef(90, 0, 0, 1);
            spacecraft2_model.draw();
        }
        else if (craft3)
        {
            glTranslatef(spacecraft3_x, spacecraft3_y - 8.0, spacecraft3_z);
            glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
            glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
            glRotatef(90, 0, 0, 1);
            glRotatef(90, 0, 1, 0);
            spacecraft3_model.draw();
        }

        glPopMatrix();

        if (space_pressed) // Space pressed, giving home button
        {
            glPushMatrix();
            glDisable(GL_LIGHTING);
            glDepthMask(GL_FALSE); // disable depth writes

            glPushMatrix();

            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos3f(-0.28, 0.4, -2.0);
            std::string text = "PRESS SPACE TO CONTINUE";
            for (int i = 0; i < text.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
            }

            glPopMatrix();

            // Display the BACK Button
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_QUADS);
            glVertex3f(-1.0f, 0.85f, -2.0);
            glVertex3f(-0.65f, 0.85f, -2.0);
            glVertex3f(-0.65f, 0.75f, -2.0);
            glVertex3f(-1.0f, 0.75f, -2.0);
            glEnd();

            glColor3f(1.0f, 0.0f, 0.0f);
            glRasterPos3f(-0.8, 0.78, -2.0);
            text = "HOME";
            for (int i = 0; i < text.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
            }

            glDepthMask(GL_TRUE); // enable depth writes
            glEnable(GL_LIGHTING);
            glPopMatrix();
        }

        glPushMatrix();
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE); // disable depth writes

        // Display the SCORE
        glColor3f(1.0f, 0.0f, 1.0f);
        glRasterPos3f(0.5, 0.78, -2.0);
        std::string text = "SCORE : " + std::to_string(score);
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Display the level
        glColor3f(1.0f, 0.0f, 1.0f);
        glRasterPos3f(-0.1, 0.78, -2.0);
        text = "LEVEL : " + std::to_string(level);
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glDepthMask(GL_TRUE); // enable depth writes
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    else if (show_menu && !collision_menu && !spacecraft_menu && !info_menu) // Home menu
    {
        galaxy();
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE); // disable depth writes

        glPushMatrix();
        // Draw the title
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.33, 0.6, -2.0);
        std::string text = "SPACE-CRAFT AVOIDING OBSTACLES";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glPopMatrix();

        glTranslatef(0, trans_y, 0);
        background();

        glDepthMask(GL_TRUE); // enable depth writes
        glEnable(GL_LIGHTING);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(satellite_x + 1, satellite_y + 3, satellite_z + 10);
        glRotatef(angle_satellite_x, 1.0f, 0.0f, 0.0f);
        glRotatef(angle_satellite_y, 0.0f, 1.0f, 0.0f);
        satellite_model.draw();
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_LIGHTING);

        // Draw the play button
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(-0.2, -0.25, -2.0);
        glVertex3f(0.2, -0.25, -2.0);
        glVertex3f(0.2, -0.35, -2.0);
        glVertex3f(-0.2, -0.35, -2.0);
        glEnd();

        // Text for play button
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos3f(-0.025, -0.156, -1.0);
        text = "PLAY";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw the info button
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex3f(-0.2, -0.4, -2.0);
        glVertex3f(0.2, -0.4, -2.0);
        glVertex3f(0.2, -0.5, -2.0);
        glVertex3f(-0.2, -0.5, -2.0);
        glEnd();

        // Text for info button
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos3f(-0.07, -0.23, -1.0);
        text = "INSTRUCTIONS";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw the quit button
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(-0.2, -0.55, -2.0);
        glVertex3f(0.2, -0.55, -2.0);
        glVertex3f(0.2, -0.65, -2.0);
        glVertex3f(-0.2, -0.65, -2.0);
        glEnd();

        // Text for quit button
        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos3f(-0.025, -0.307, -1.0);
        text = "QUIT";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    else if (collision_menu && !spacecraft_menu && !info_menu) // Collision Menu
    {
        galaxy();
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE); // disable depth writes

        glPushMatrix();
        // Draw the title
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.3, 0.6, -2.0);
        std::string text = "OOPS!!! SPACECRAFT CRASHED";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glPopMatrix();

        glTranslatef(0, trans_y, 0);
        background();

        glDepthMask(GL_TRUE); // enable depth writes
        glEnable(GL_LIGHTING);
        glPopMatrix();

        glPushMatrix();
        glDepthMask(GL_FALSE); // disable depth writes
        glDisable(GL_LIGHTING);

        // Draw the Dialog box
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex3f(-0.5, 0.45, -2.0);
        glVertex3f(0.5, 0.45, -2.0);
        glVertex3f(0.5, 0.05, -2.0);
        glVertex3f(-0.5, 0.05, -2.0);
        glEnd();

        // Text1
        glColor3f(1.0f, 0.2f, 0.8f);
        glRasterPos3f(-0.12, 0.18, -1.0);
        text = "BETTER LUCK NEXT TIME";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glColor3f(0.0, 0.0, 0.0);
        glRasterPos3f(-0.115, 0.12, -1.0); // Print Distance covered
        text = "Total Distance Covered: " + std::to_string(int(distance_covered)) + "m";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glRasterPos3f(-0.05, 0.06, -1.0); // Print current score
        text = "Total Score: " + std::to_string(score);
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw the Home button
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glVertex3f(-0.2, -0.1, -2.0);
        glVertex3f(0.2, -0.1, -2.0);
        glVertex3f(0.2, -0.2, -2.0);
        glVertex3f(-0.2, -0.2, -2.0);
        glEnd();

        // Text the Home button
        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos3f(-0.031, -0.08, -1.0);
        text = "HOME";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw the play button
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(-0.2, -0.3, -2.0);
        glVertex3f(0.2, -0.3, -2.0);
        glVertex3f(0.2, -0.4, -2.0);
        glVertex3f(-0.2, -0.4, -2.0);
        glEnd();

        // Draw the play button
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos3f(-0.055, -0.18, -1.0);
        text = "PLAY AGAIN";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw the quit button
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(-0.2, -0.5, -2.0);
        glVertex3f(0.2, -0.5, -2.0);
        glVertex3f(0.2, -0.6, -2.0);
        glVertex3f(-0.2, -0.6, -2.0);
        glEnd();

        // Text for quit button
        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos3f(-0.025, -0.28, -1.0);
        text = "QUIT";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glDepthMask(GL_TRUE); // enable depth writes
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    else if (spacecraft_menu && !info_menu) // Select spacecraft menu
    {
        galaxy();
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE); // disable depth writes

        glPushMatrix();
        // Write the title
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.2, 0.6, -2.0);
        std::string text = "SELECT THE SPACECRAFT";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glPopMatrix();

        glTranslatef(0, trans_y, 0);
        background();

        glDepthMask(GL_TRUE); // enable depth writes
        glEnable(GL_LIGHTING);
        glPopMatrix();

        // Draw spacecraft
        if (craft1)
        {
            glPushMatrix();

            glTranslatef(spacecraft1_x + 0.8, spacecraft1_y + 0.5, spacecraft1_z + 12);
            glRotatef(angle_craft1_x, 1.0f, 0.0f, 0.0f);
            glRotatef(angle_craft1_y, 0.0f, 1.0f, 0.0f);
            glRotatef(90, 0, 0, 1);
            spacecraft1_model.draw();
            glPopMatrix();
        }
        else if (craft2)
        {
            glPushMatrix();

            glTranslatef(spacecraft2_x + 0.5, spacecraft2_y + 2, spacecraft2_z + 2);
            glRotatef(angle_craft2_x, 1.0f, 0.0f, 0.0f);
            glRotatef(angle_craft2_y, 0.0f, 1.0f, 0.0f);
            glRotatef(45, 0, 0, 1);
            // glRotatef(45,1,0,0);
            spacecraft2_model.draw();
            glPopMatrix();
        }
        else if (craft3)
        {
            glPushMatrix();

            glTranslatef(spacecraft3_x + 0.5, spacecraft3_y + 1.5, spacecraft3_z + 12);
            glRotatef(angle_craft3_x, 1.0f, 0.0f, 0.0f);
            glRotatef(angle_craft3_y, 0.0f, 1.0f, 0.0f);
            glRotatef(90, 0, 0, 1);
            glRotatef(90, 0, 1, 0);
            spacecraft3_model.draw();
            glPopMatrix();
        }

        glPushMatrix();
        glDisable(GL_LIGHTING);

        // Draw the Next button
        glColor3f(0.137, 0.51, 0.631);
        glBegin(GL_QUADS);
        glVertex3f(0.6, 0.38, -2.0);
        glVertex3f(0.66, 0.38, -2.0);
        glVertex3f(0.66, 0.0, -2.0);
        glVertex3f(0.6, 0.0, -2.0);
        glEnd();

        // Text the Next button
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(0.31, 0.097, -1.0);
        text = ">";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw the Prev button
        glColor3f(0.137, 0.51, 0.631);
        glBegin(GL_QUADS);
        glVertex3f(-0.6, 0.38, -2.0);
        glVertex3f(-0.66, 0.38, -2.0);
        glVertex3f(-0.66, 0.0, -2.0);
        glVertex3f(-0.6, 0.0, -2.0);
        glEnd();

        // Text the Prev button
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.32, 0.097, -1.0);
        text = "<";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Spaceship Name
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.04, -0.27, -2.0);

        if (craft1)
        {
            text = "X-WING";
        }
        else if (craft2)
        {
            text = "UFO";
        }
        else if (craft3)
        {
            text = "SKY-BLADE";
        }

        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw Home button
        glColor3f(0.137, 0.51, 0.631);
        glBegin(GL_QUADS);
        glVertex3f(-0.45, -0.5, -2.0);
        glVertex3f(-0.15, -0.5, -2.0);
        glVertex3f(-0.15, -0.6, -2.0);
        glVertex3f(-0.45, -0.6, -2.0);
        glEnd();

        // Text for Home button
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.18, -0.28, -1.0);
        text = "HOME";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw Select button
        glColor3f(0.137, 0.51, 0.631);
        glBegin(GL_QUADS);
        glVertex3f(0.45, -0.5, -2.0);
        glVertex3f(0.15, -0.5, -2.0);
        glVertex3f(0.15, -0.6, -2.0);
        glVertex3f(0.45, -0.6, -2.0);
        glEnd();

        // Text for select button
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(0.115, -0.28, -1.0);
        text = "SELECT";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    else if (info_menu) // Instructions Panel
    {
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE); // disable depth writes

        glPushMatrix();
        // Draw the title
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.19, 0.6, -2.0);
        std::string text = "INSTRUCTIONS";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glPopMatrix();

        glTranslatef(0, trans_y, 0);
        background();

        glDepthMask(GL_TRUE); // enable depth writes
        glEnable(GL_LIGHTING);
        glPopMatrix();

        glPushMatrix();
        glDepthMask(GL_FALSE); // disable depth writes
        glDisable(GL_LIGHTING);

        glRasterPos3f(-0.29, 0.2, -1.0);
        text = "'UP arrow' key           :      MOVE SPACESHIP UP";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glRasterPos3f(-0.29, 0.17, -1.0);
        text = "'DOWN arrow' key    :      MOVE SPACESHIP DOWN";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, 0.14, -1.0);
        text = "'LEFT arrow' key       :      MOVE SPACESHIP LEFT";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, 0.11, -1.0);
        text = "'RIGHT arrow' key    :      MOVE RIGHT";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, 0.08, -1.0);
        text = "'N' KEY                      :      ENABLE/DISABLE NIGHT MODE";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, 0.05, -1.0);
        text = "'+' KEY                       :      INCREASE SHININESS";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, 0.02, -1.0);
        text = "'-' KEY                       :      DECREASE SHININESS";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, -0.01, -1.0);
        text = "'ENTER' key              :      MOVE TO NEXT MENU";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, -0.04, -1.0);
        text = "'ESC' key                    :      MOVE TO PREVIOUS MENU";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, -0.07, -1.0);
        text = "'SPACE' KEY            :      PAUSE/START";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
        glRasterPos3f(-0.29, -0.1, -1.0);
        text = "HOLD LEFT-MB      :      ROTATE SPACESHIPS";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        // Draw the Home button
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(-0.2, -0.5, -2.0);
        glVertex3f(0.2, -0.5, -2.0);
        glVertex3f(0.2, -0.6, -2.0);
        glVertex3f(-0.2, -0.6, -2.0);
        glEnd();

        // Text for Home button
        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos3f(-0.03, -0.28, -1.0);
        text = "HOME";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glDepthMask(GL_TRUE); // enable depth writes
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
jump:
    glColor3f(1.0, 1.0, 1.0);
    glFlush();
    glutSwapBuffers();
}

// Timer function is called after every 15 millisecond
void timer(int value)
{
    // Translating background stars
    trans_y -= 0.01;

    if (trans_y < -8)
        trans_y += 20;

    if (start)
    {
        // Increase distance
        distance_covered += 10.0;
        // Increase socre
        if (int(distance_covered) % 9 == 8)
        {
            score += 1;
        }

        // Increase level along with increasing speed for asteroids and spacecraft
        ast_y -= (level_speed);
        if (ast_y < -100)
        {
            ast_y = 0;
            level_speed += 0.04;
            hor_speed += 0.02;
            ver_speed += 0.015;
            level++;
        }
    }

    if (is_updated)
    {
        is_updated = false;
        glutPostRedisplay();
    }
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, timer, 0); // Recursive after every 15ms
}

void specialKeyFunc(int key, int x, int y)
{
    if (!show_menu && !space_pressed && !collision_menu && !spacecraft_menu) // While playing with spacecraft
    {
        if (craft1)
        {
            if (key == GLUT_KEY_DOWN)
            {
                if (spacecraft1_y > -1.737)
                    spacecraft1_y -= ver_speed;
            }
            else if (key == GLUT_KEY_UP)
            {
                if (spacecraft1_y < 16.2629)
                    spacecraft1_y += ver_speed;
            }
            else if (key == GLUT_KEY_RIGHT)
            {
                if (spacecraft1_x < 8.71)
                    spacecraft1_x += hor_speed;
            }
            else if (key == GLUT_KEY_LEFT)
            {
                if (spacecraft1_x > -9.79)
                    spacecraft1_x -= hor_speed;
            }
        }
        else if (craft2)
        {
            if (key == GLUT_KEY_DOWN)
            {
                if (spacecraft2_y > -1.6)
                    spacecraft2_y -= ver_speed;
            }
            else if (key == GLUT_KEY_UP)
            {
                if (spacecraft2_y < 17.38)
                    spacecraft2_y += ver_speed;
            }
            else if (key == GLUT_KEY_RIGHT)
            {
                if (spacecraft2_x < 8.71)
                    spacecraft2_x += hor_speed;
            }
            else if (key == GLUT_KEY_LEFT)
            {
                if (spacecraft2_x > -9.79)
                    spacecraft2_x -= hor_speed;
            }
        }
        else if (craft3)
        {
            if (key == GLUT_KEY_DOWN)
            {
                if (spacecraft3_y > -1.737)
                    spacecraft3_y -= ver_speed;
            }
            else if (key == GLUT_KEY_UP)
            {
                if (spacecraft3_y < 16.2629)
                    spacecraft3_y += ver_speed;
            }
            else if (key == GLUT_KEY_RIGHT)
            {
                if (spacecraft3_x < 8.71)
                    spacecraft3_x += hor_speed;
            }
            else if (key == GLUT_KEY_LEFT)
            {
                if (spacecraft3_x > -9.79)
                    spacecraft3_x -= hor_speed;
            }
        }

        glutPostRedisplay();
    }
    else if (spacecraft_menu) // Moving next and prev spacecrafts
    {
        if (key == GLUT_KEY_RIGHT)
        {
            if (craft1)
            {
                craft1 = false;
                craft2 = true;
                angle_craft1_x = 0;
                angle_craft1_y = 90;
                angle_craft2_x = 0;
                angle_craft2_y = 90;
                angle_craft3_x = 0;
                angle_craft3_y = 90;
            }
            else if (craft2)
            {
                craft2 = false;
                craft3 = true;
                angle_craft1_x = 0;
                angle_craft1_y = 90;
                angle_craft2_x = 0;
                angle_craft2_y = 90;
                angle_craft3_x = 0;
                angle_craft3_y = 90;
            }
            else if (craft3)
            {
                craft3 = false;
                craft1 = true;
                angle_craft1_x = 0;
                angle_craft1_y = 90;
                angle_craft2_x = 0;
                angle_craft2_y = 90;
                angle_craft3_x = 0;
                angle_craft3_y = 90;
            }
        }
        else if (key == GLUT_KEY_LEFT)
        {
            if (craft1)
            {
                craft1 = false;
                craft3 = true;
                angle_craft1_x = 0;
                angle_craft1_y = 90;
                angle_craft2_x = 0;
                angle_craft2_y = 90;
                angle_craft3_x = 0;
                angle_craft3_y = 90;
            }
            else if (craft2)
            {
                craft2 = false;
                craft1 = true;
                angle_craft1_x = 0;
                angle_craft1_y = 90;
                angle_craft2_x = 0;
                angle_craft2_y = 90;
                angle_craft3_x = 0;
                angle_craft3_y = 90;
            }
            else if (craft3)
            {
                craft3 = false;
                craft2 = true;
                angle_craft1_x = 0;
                angle_craft1_y = 90;
                angle_craft2_x = 0;
                angle_craft2_y = 90;
                angle_craft3_x = 0;
                angle_craft3_y = 90;
            }
        }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'n') // Changing day and night modes
    {
        change_mode = !change_mode;
        if (change_mode)
        {
            a_x = 0.25;
            a_y = 0.25;
            a_z = 0.25;
            b_x = 0.0;
            b_y = 0.0;
            b_z = 0.0;
        }
        else
        {
            a_x = 0.05;
            a_y = 0.05;
            a_z = 0.05;
        }
    }
    if (!change_mode) // Changing shininess property of materials
    {
        if (key == 43) // + key
        {
            b_x += 0.2;
            b_y += 0.2;
            b_z += 0.2;
            if (b_x > 4 || b_y > 4 || b_z > 4)
            {
                b_x = 4;
                b_y = 4;
                b_z = 4;
            }
        }
        else if (key == 45) // - key
        {
            b_x -= 0.2;
            b_y -= 0.2;
            b_z -= 0.2;
            if (b_x < 0 || b_y < 0 || b_z < 0)
            {
                b_x = 0;
                b_y = 0;
                b_z = 0;
            }
        }
    }
    if (!show_menu && !collision_menu && !spacecraft_menu) // While playing with spacecraft
    {
        switch (key)
        {
        case ' ':
            start = !start;
            space_pressed = !space_pressed;
            break;
        }
    }
    else if (spacecraft_menu && !show_menu && !collision_menu) // Spacecraft Menu
    {
        if (key == 13) // Enter key
        {
            spacecraft_menu = false;
            trans_y = 0;
            distance_covered = 0;
            start = true;
            ast_y = 0;
            level_speed = 0.08;
            level = 1;
            score = 0;

            angle_craft1_x = 0;
            angle_craft1_y = 90;
            angle_craft2_x = 0;
            angle_craft2_y = 90;
            angle_craft3_x = 0;
            angle_craft3_y = 90;
            craft1_x = 0;
            craft1_y = 0;
            craft2_x = 0;
            craft2_y = 0;
            craft3_x = 0;
            craft3_y = 0;

            if (craft1)
            {
                spacecraft1_x = spacecraft1_x_old;
                spacecraft1_y = spacecraft1_y_old;
            }
            else if (craft2)
            {
                spacecraft2_x = spacecraft2_x_old;
                spacecraft2_y = spacecraft2_y_old;
            }
            else if (craft3)
            {
                spacecraft3_x = spacecraft3_x_old;
                spacecraft3_y = spacecraft3_y_old;
            }
        }
        else if (key == 27) // ESC key
        {
            spacecraft_menu = false;
            show_menu = true;
            angle_craft1_x = 0;
            angle_craft1_y = 90;
            angle_craft2_x = 0;
            angle_craft2_y = 90;
            angle_craft3_x = 0;
            angle_craft3_y = 90;

            craft1_x = 0;
            craft1_y = 0;
            craft2_x = 0;
            craft2_y = 0;
            craft3_x = 0;
            craft3_y = 0;
            craft1 = true;
            craft2 = false;
            craft3 = false;

            angle_satellite_x = 0.0f;
            angle_satellite_y = 45.0f;
        }
    }
    else if (show_menu && !collision_menu && !spacecraft_menu) // Show Menu
    {
        if (key == 13) // ENTER key
        {
            show_menu = false;
            spacecraft_menu = true;
        }
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (show_menu && !collision_menu && !spacecraft_menu && !info_menu) // Buttons in show menu
    {
        is_updated = true;

        // Check if the left mouse button was pressed and released
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            // Check if the mouse cursor is within the bounds of the play button

            if (x >= 381 && x <= 622 && y >= 652 && y <= 712) // Play
            {
                // Call a function to start the game
                system("play -q click.wav &");
                show_menu = false;
                spacecraft_menu = true;
            }
            else if (x >= 381 && x <= 622 && y >= 743 && y <= 801) // Information menu
            {
                system("play -q click.wav &");
                show_menu = false;
                info_menu = true;
            }
            // Check if the mouse cursor is within the bounds of the quit button
            else if (x >= 381 && x <= 622 && y >= 831 && y <= 893) // Exit
            {
                // Call a function to exit the program
                system("play -q click.wav &");
                exit(0);
            }
        }
        if (button == GLUT_LEFT_BUTTON)
        {
            if (state == GLUT_DOWN)
            {
                x_satellite_old = x;
                y_satellite_old = y;
                is_holding_mouse = true;
            }
            else
                is_holding_mouse = false;
        }
    }
    else if (collision_menu && !spacecraft_menu && !info_menu) // Collision menu
    {
        is_updated = true;

        // Check if the left mouse button was pressed and released
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            if (x >= 379 && x <= 622 && y >= 560 && y <= 625) // Home
            {
                system("play -q click.wav &");
                show_menu = true;
                collision_menu = false;
                if (craft1)
                {
                    spacecraft1_x = spacecraft1_x_old;
                    spacecraft1_y = spacecraft1_y_old;
                }
                else if (craft2)
                {
                    spacecraft2_x = spacecraft2_x_old;
                    spacecraft2_y = spacecraft2_y_old;
                }
                else if (craft3)
                {
                    spacecraft3_x = spacecraft3_x_old;
                    spacecraft3_y = spacecraft3_y_old;
                }
                angle_x = -45.0f;
                angle_y = 90.0f;
                angle_satellite_x = 0.0f;
                angle_satellite_y = 45.0f;
            }

            // Check if the mouse cursor is within the bounds of the play button
            else if (x >= 380 && x <= 620 && y >= 680 && y <= 745) // Play again
            {
                // Call a function to start the game
                collision_menu = false;
                spacecraft_menu = true;
                if (craft1)
                {
                    spacecraft1_x = spacecraft1_x_old;
                    spacecraft1_y = spacecraft1_y_old;
                }
                else if (craft2)
                {
                    spacecraft2_x = spacecraft2_x_old;
                    spacecraft2_y = spacecraft2_y_old;
                }
                else if (craft3)
                {
                    spacecraft3_x = spacecraft3_x_old;
                    spacecraft3_y = spacecraft3_y_old;
                }
                angle_x = -45.0f;
                angle_y = 90.0f;
            }
            // Check if the mouse cursor is within the bounds of the quit button
            else if (x >= 380 && x <= 620 && y >= 800 && y <= 865) // quit
            {
                // Call a function to exit the program
                exit(0);
            }
            // glutPostRedisplay();
        }
    }
    else if (!spacecraft_menu && !info_menu) // While playing with spacecraft
    {
        is_updated = true;
        if (space_pressed) // If space is pressed stop every motion
        {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
            {
                // Check if the mouse cursor is within the bounds of the play button

                if (x >= 0 && x <= 110 && y >= 0 && y <= 45) // Home
                {
                    // Call a function to start the game
                    system("play -q click.wav &");
                    angle_x = -45.0f;
                    angle_y = 90.0f;
                    angle_satellite_x = 0.0f;
                    angle_satellite_y = 45.0f;
                    ast_pos = 1000.0;

                    x_old = 0, y_old = 0;
                    x_satellite_old = 0;
                    y_satellite_old = 0;
                    current_scroll = 5;
                    zoom_per_scroll = 0;

                    is_holding_mouse = false;
                    is_updated = false;
                    start = true;
                    space_pressed = false;
                    show_menu = true;
                    trans_y = 0;
                    distance_covered = 0;
                    score = 0;
                    angle_craft1_x = 0;
                    angle_craft1_y = 90;
                    angle_craft2_x = 0;
                    angle_craft2_y = 90;
                    angle_craft3_x = 0;
                    angle_craft3_y = 90;

                    craft1_x = 0;
                    craft1_y = 0;
                    craft2_x = 0;
                    craft2_y = 0;
                    craft3_x = 0;
                    craft3_y = 0;
                    craft1 = true;
                    craft2 = false;
                    craft3 = false;

                    b_x = 0.0;
                    b_y = 0.0;
                    b_z = 0.0;

                    // change_mode = false;

                    if (craft1)
                    {
                        spacecraft1_x = spacecraft1_x_old;
                        spacecraft1_y = spacecraft1_y_old;
                    }
                    else if (craft2)
                    {
                        spacecraft2_x = spacecraft2_x_old;
                        spacecraft2_y = spacecraft2_y_old;
                    }
                    else if (craft3)
                    {
                        spacecraft3_x = spacecraft3_x_old;
                        spacecraft3_y = spacecraft3_y_old;
                    }
                }
            }
        }
        else
        {
            if (button == GLUT_LEFT_BUTTON)
            {
                if (state == GLUT_DOWN)
                {
                    x_old = x;
                    y_old = y;
                    is_holding_mouse = true;
                }
                else
                    is_holding_mouse = false;
            }
        }
    }
    else if (spacecraft_menu && !info_menu) // Spacecraft menu
    {
        is_updated = true;

        // Check if the left mouse button was pressed and released
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            // std::cout<<x<<" "<<y<<"\n";

            if (x >= 863 && x <= 901 && y >= 272 && y <= 500) // Next spacecraft
            {
                system("play -q click.wav &");
                if (craft1)
                {
                    craft1 = false;
                    craft2 = true;
                    angle_craft1_x = 0;
                    angle_craft1_y = 90;
                    angle_craft2_x = 0;
                    angle_craft2_y = 90;
                    angle_craft3_x = 0;
                    angle_craft3_y = 90;
                }
                else if (craft2)
                {
                    craft2 = false;
                    craft3 = true;
                    angle_craft1_x = 0;
                    angle_craft1_y = 90;
                    angle_craft2_x = 0;
                    angle_craft2_y = 90;
                    angle_craft3_x = 0;
                    angle_craft3_y = 90;
                }
                else if (craft3)
                {
                    craft3 = false;
                    craft1 = true;
                    angle_craft1_x = 0;
                    angle_craft1_y = 90;
                    angle_craft2_x = 0;
                    angle_craft2_y = 90;
                    angle_craft3_x = 0;
                    angle_craft3_y = 90;
                }
            }
            else if (x >= 103 && x <= 138 && y >= 271 && y <= 501) // Prev Spacecraft
            {
                system("play -q click.wav &");
                if (craft1)
                {
                    craft1 = false;
                    craft3 = true;
                    angle_craft1_x = 0;
                    angle_craft1_y = 90;
                    angle_craft2_x = 0;
                    angle_craft2_y = 90;
                    angle_craft3_x = 0;
                    angle_craft3_y = 90;
                }
                else if (craft2)
                {
                    craft2 = false;
                    craft1 = true;
                    angle_craft1_x = 0;
                    angle_craft1_y = 90;
                    angle_craft2_x = 0;
                    angle_craft2_y = 90;
                    angle_craft3_x = 0;
                    angle_craft3_y = 90;
                }
                else if (craft3)
                {
                    craft3 = false;
                    craft2 = true;
                    angle_craft1_x = 0;
                    angle_craft1_y = 90;
                    angle_craft2_x = 0;
                    angle_craft2_y = 90;
                    angle_craft3_x = 0;
                    angle_craft3_y = 90;
                }
            }
            else if (x >= 229 && x <= 409 && y >= 804 && y <= 862) // Home
            {
                system("play -q click.wav &");
                spacecraft_menu = false;
                show_menu = true;
                angle_craft1_x = 0;
                angle_craft1_y = 90;
                angle_craft2_x = 0;
                angle_craft2_y = 90;
                angle_craft3_x = 0;
                angle_craft3_y = 90;

                craft1_x = 0;
                craft1_y = 0;
                craft2_x = 0;
                craft2_y = 0;
                craft3_x = 0;
                craft3_y = 0;
                craft1 = true;
                craft2 = false;
                craft3 = false;

                angle_satellite_x = 0.0f;
                angle_satellite_y = 45.0f;
            }
            // Check if the mouse cursor is within the bounds of the select button
            else if (x >= 591 && x <= 772 && y >= 804 && y <= 864) // Select
            {
                system("play -q click.wav &");
                spacecraft_menu = false;
                trans_y = 0;
                distance_covered = 0;
                start = true;
                ast_y = 0;
                level_speed = 0.08;
                level = 1;
                score = 0;

                angle_craft1_x = 0;
                angle_craft1_y = 90;
                angle_craft2_x = 0;
                angle_craft2_y = 90;
                angle_craft3_x = 0;
                angle_craft3_y = 90;
                craft1_x = 0;
                craft1_y = 0;
                craft2_x = 0;
                craft2_y = 0;
                craft3_x = 0;
                craft3_y = 0;

                if (craft1)
                {
                    spacecraft1_x = spacecraft1_x_old;
                    spacecraft1_y = spacecraft1_y_old;
                }
                else if (craft2)
                {
                    spacecraft2_x = spacecraft2_x_old;
                    spacecraft2_y = spacecraft2_y_old;
                }
                else if (craft3)
                {
                    spacecraft3_x = spacecraft3_x_old;
                    spacecraft3_y = spacecraft3_y_old;
                }
            }
        }
        if (button == GLUT_LEFT_BUTTON)
        {
            if (state == GLUT_DOWN)
            {
                if (craft1)
                {
                    craft1_x = x;
                    craft1_y = y;
                }
                else if (craft2)
                {
                    craft2_x = x;
                    craft2_y = y;
                }
                else if (craft3)
                {
                    craft3_x = x;
                    craft3_y = y;
                }

                is_holding_mouse = true;
            }
            else
                is_holding_mouse = false;
        }
    }
    else if (info_menu) // Information menu
    {
        if (x >= 379 && x <= 622 && y >= 803 && y <= 865) // Home
        {
            system("play -q click.wav &");
            show_menu = true;
            info_menu = false;
        }
    }
    glutPostRedisplay();
}

void motion(int x, int y)
{
    if (!show_menu && !space_pressed && !collision_menu && !spacecraft_menu) // While playing with spacecraft
    {
        if (is_holding_mouse)
        {
            is_updated = true;

            angle_y += (x - x_old);
            x_old = x;
            if (angle_y > 360.0f)
                angle_y -= 360.0f;
            else if (angle_y < 0.0f)
                angle_y += 360.0f;

            angle_x += (y - y_old);
            y_old = y;
            if (angle_x > 90.0f)
                angle_x = 90.0f;
            else if (angle_x < -90.0f)
                angle_x = -90.0f;
        }
    }
    else if (show_menu && !spacecraft_menu) // While rotating staellite in Home menu
    {
        if (is_holding_mouse)
        {
            is_updated = true;

            angle_satellite_y += (x - x_satellite_old);
            x_satellite_old = x;
            if (angle_satellite_y > 360.0f)
                angle_satellite_y -= 360.0f;
            else if (angle_satellite_y < 0.0f)
                angle_satellite_y += 360.0f;

            angle_satellite_x += (y - y_satellite_old);
            y_satellite_old = y;
            if (angle_satellite_x > 90.0f)
                angle_satellite_x = 90.0f;
            else if (angle_satellite_x < -90.0f)
                angle_satellite_x = -90.0f;
        }
    }
    else if (spacecraft_menu) // Now rotate spacecrafts in spacecraft menu
    {
        if (is_holding_mouse)
        {
            is_updated = true;

            if (craft1)
            {
                angle_craft1_y += (x - craft1_x);
                craft1_x = x;
                if (angle_craft1_y > 360.0f)
                    angle_craft1_y -= 360.0f;
                else if (angle_craft1_y < 0.0f)
                    angle_craft1_y += 360.0f;

                angle_craft1_x += (y - craft1_y);
                craft1_y = y;
                if (angle_craft1_x > 90.0f)
                    angle_craft1_x = 90.0f;
                else if (angle_craft1_x < -90.0f)
                    angle_craft1_x = -90.0f;
            }
            else if (craft2)
            {
                angle_craft2_y += (x - craft2_x);
                craft2_x = x;
                if (angle_craft2_y > 360.0f)
                    angle_craft2_y -= 360.0f;
                else if (angle_craft2_y < 0.0f)
                    angle_craft2_y += 360.0f;

                angle_craft2_x += (y - craft2_y);
                craft2_y = y;
                if (angle_craft2_x > 90.0f)
                    angle_craft2_x = 90.0f;
                else if (angle_craft2_x < -90.0f)
                    angle_craft2_x = -90.0f;
            }
            else if (craft3)
            {
                angle_craft3_y += (x - craft3_x);
                craft3_x = x;
                if (angle_craft3_y > 360.0f)
                    angle_craft3_y -= 360.0f;
                else if (angle_craft3_y < 0.0f)
                    angle_craft3_y += 360.0f;

                angle_craft3_x += (y - craft3_y);
                craft3_y = y;
                if (angle_craft3_x > 90.0f)
                    angle_craft3_x = 90.0f;
                else if (angle_craft3_x < -90.0f)
                    angle_craft3_x = -90.0f;
            }
        }
    }
}
// this function plays the background music and abrupts it on closing of window
void play_sound()
{
    while (!closed)
    {
        system("play -q music.mp3 &");
        for (int i = 0; i < 28; i++)
        {
            sleep(1);
            if (closed)
            {
                int pid = system("pgrep play");
                pid = atoi(std::to_string(pid).c_str());
                kill(pid, SIGINT);
                break;
            }
        }
    }
}

// thread pointer for playing background music
std::thread *t1;

// callback function to stop playing of sound on closing of window
void window_close_callback()
{
    closed = true;

    t1->join();
}
int main(int argc, char **argv)
{
    t1 = new std::thread(play_sound);
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(50, 50);       // window Position
    glutInitWindowSize(1000, 1000);       // Window Size
    glutCreateWindow("Space Game");       // Window name
    glutCloseFunc(window_close_callback); // This function would be called when the window would be closed
    init();
    glutDisplayFunc(display);        // Sets the display finction to be called
    glutMouseFunc(mouse);            // Set mouse callback function
    glutMotionFunc(motion);          // Set motion callback function
    glutKeyboardFunc(keyboard);      // Set keyboard callback function
    glutSpecialFunc(specialKeyFunc); // Set special key callback function
    glutTimerFunc(0, timer, 0);      // Set timer callback function
    glutMainLoop();                  // Enter the GLUT event processing loop.
    return 0;
}

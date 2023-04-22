#include "../Library/main.h"
#include "../Library/soil/SOIL.h"
#include <bits/stdc++.h>

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

GLfloat light_pos[] = {0.0f, 0.0f, 0.0f, 10.0f};

float spacecraft_x, spacecraft_y, spacecraft_z;
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
float particle_x, particle_y, particle_z;
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

bool is_holding_mouse = false;
bool is_updated = false;
bool start = false;
bool space_pressed = false;
bool show_menu = true;
bool collision_menu = false;
bool spacecraft_menu = false;
bool craft1 = true, craft2 = false, craft3 = false;
float angle_craft1_x = 0.0f, angle_craft1_y = 90.0f;
float angle_craft2_x = 0.0f, angle_craft2_y = 90.0f;
float angle_craft3_x = 0.0f, angle_craft3_y = 90.0f;
int craft1_x = 0, craft1_y = 0;
int craft2_x = 0, craft2_y = 0;
int craft3_x = 0, craft3_y = 0;

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

GLuint texture;

void LoadGLTextures()
{
    // texture
    texture = SOIL_load_OGL_texture("spacecraft.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Typical Texture Generation Using Data From The Bitmap
    // glBindTexture(GL_TEXTURE_2D, texture[0]);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glEnable(GL_TEXTURE_2D);                           // Enable Texture Mapping ( NEW )
    // glShadeModel(GL_SMOOTH);                           // Enable Smooth Shading
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);              // Black Background
    // glClearDepth(1.0f);                                // Depth Buffer Setup
    // glEnable(GL_DEPTH_TEST);                           // Enables Depth Testing
    // glDepthFunc(GL_LEQUAL);                            // The Type Of Depth Testing To Do
    // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
}

float distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float dist = 0;
    dist += (x1 - x2) * (x1 - x2);
    dist += (y2 - y1) * (y2 - y1);
    dist += (z1 - z2) * (z1 - z2);
    return dist;
}
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
        ans = ans and (distance(asteroid6_x, asteroid6_y + 10 + ast_y, asteroid6_z - 10, spacecraft2_x, spacecraft2_y - 8.0, spacecraft2_z + 3) > 40);
        ans = ans and (distance(asteroid9_x + 5, asteroid9_y + 20 + ast_y, asteroid9_z - 4, spacecraft2_x, spacecraft2_y - 8.0, spacecraft2_z + 3) > 35);
        ans = ans and (distance(asteroid4_x - 10, asteroid4_y + 30 + ast_y, asteroid4_z - 14, spacecraft2_x-9.4, spacecraft2_y - 11.0, spacecraft2_z -9) > 28);
        ans = ans and (distance(asteroid5_x - 5, asteroid5_y + 40 + ast_y, asteroid5_z - 10, spacecraft2_x, spacecraft2_y - 8.0, spacecraft2_z + 3) > 25);
        ans = ans and (distance(asteroid6_x + 9, asteroid6_y + 50 + ast_y, asteroid6_z - 10, spacecraft2_x, spacecraft2_y - 8.0, spacecraft2_z + 3) > 25);
        ans = ans and (distance(asteroid10_x - 5, asteroid10_y + 60 + ast_y, asteroid10_z - 4, spacecraft2_x, spacecraft2_y - 8.0, spacecraft2_z + 3) > 25);
        ans = ans and (distance(asteroid8_x - 8, asteroid8_y + 70 + ast_y, asteroid8_z - 12, spacecraft2_x, spacecraft2_y - 8.0, spacecraft2_z + 3) > 25);
        ans = ans and (distance(asteroid5_x + 5, asteroid5_y + 80 + ast_y, asteroid5_z - 10, spacecraft2_x, spacecraft2_y - 8.0, spacecraft2_z + 3) > 25);
        ans = ans and (distance(asteroid7_x - 5, asteroid7_y + 90 + ast_y, asteroid7_z - 15, spacecraft2_x, spacecraft2_y - 8.0, spacecraft2_z + 3) > 25);
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

float randomFloat()
{
    // srand(1);
    return -20.0f + 40.0f * ((float)(rand()) / RAND_MAX);
}

void background()
{
    glColor3f(1, 1, 1);

    srand(1);

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

void init()
{
    LoadGLTextures();
    // glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

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

    spacecraft1_x = spacecraft1_model.pos_x;
    spacecraft1_y = spacecraft1_model.pos_y;
    spacecraft1_z = spacecraft1_model.pos_z - 1.0f;

    spacecraft2_x = spacecraft2_model.pos_x;
    spacecraft2_y = spacecraft2_model.pos_y;
    spacecraft2_z = spacecraft2_model.pos_z - 1.0f;

    // std::cout<<spacecraft3_x<<" "<<spacecraft3_y<<" "<<spacecraft3_z<<"\n";

    spacecraft3_x = spacecraft3_model.pos_x;
    spacecraft3_y = spacecraft3_model.pos_y;
    spacecraft3_z = spacecraft3_model.pos_z - 1.0f;

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

    // std::cout << asteroid4_x << " " << asteroid4_y << " " << asteroid4_z << "\n";
    // std::cout << spacecraft2_x << " " << spacecraft2_y << " " << spacecraft2_z << "\n";
}

// Function for menuBackground
void menuBack()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTranslatef(0, 0, -30);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    float xmin = 5.5, xmax = 10.5, ymin = 0.0, ymax = 5.5;
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

    if (!show_menu && !collision_menu && !spacecraft_menu)
    {
        if (!check())
        {
            // std::cout<<"yayy\n";
            collision_menu = true;
            start = false;
            goto jump;
        }
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE); // disable depth writes

        glTranslatef(0, trans_y, 0);
        background();

        glDepthMask(GL_TRUE); // enable depth writes
        glEnable(GL_LIGHTING);
        glPopMatrix();

        glPushMatrix();

        glTranslatef(0, ast_y, 0);

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

        if (space_pressed)
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
    else if (show_menu && !collision_menu && !spacecraft_menu)
    {
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
        glVertex3f(-0.2, -0.3, -2.0);
        glVertex3f(0.2, -0.3, -2.0);
        glVertex3f(0.2, -0.4, -2.0);
        glVertex3f(-0.2, -0.4, -2.0);
        glEnd();

        // Draw the quit button
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos3f(-0.025, -0.18, -1.0);
        text = "PLAY";
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

        // Draw the quit button
        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos3f(-0.025, -0.28, -1.0);
        text = "QUIT";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glEnable(GL_LIGHTING);
        menuBack();
        glPopMatrix();
    }
    else if (collision_menu && !spacecraft_menu)
    {
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
        glRasterPos3f(-0.115, 0.12, -1.0);
        text = "Total Distance Covered: " + std::to_string(int(distance_covered)) + "m";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glRasterPos3f(-0.05, 0.06, -1.0);
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

        // Draw the quit button
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
    else
    {
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE); // disable depth writes

        glPushMatrix();
        // Draw the title
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

        // Text the Name
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.04, -0.27, -2.0);

        if(craft1){
            text = "X-WING";
        } else if(craft2){
            text = "UFO";
        } else if(craft3){
            text = "SKY-BLADE";
        }
        
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glColor3f(0.137, 0.51, 0.631);
        glBegin(GL_QUADS);
        glVertex3f(-0.45, -0.5, -2.0);
        glVertex3f(-0.15, -0.5, -2.0);
        glVertex3f(-0.15, -0.6, -2.0);
        glVertex3f(-0.45, -0.6, -2.0);
        glEnd();

        // Draw the quit button
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(-0.18, -0.28, -1.0);
        text = "HOME";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glColor3f(0.137, 0.51, 0.631);
        glBegin(GL_QUADS);
        glVertex3f(0.45, -0.5, -2.0);
        glVertex3f(0.15, -0.5, -2.0);
        glVertex3f(0.15, -0.6, -2.0);
        glVertex3f(0.45, -0.6, -2.0);
        glEnd();

        // Draw the quit button
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
jump:
    glFlush();
    glutSwapBuffers();
}

void timer(int value)
{
    trans_y -= 0.01;

    if (trans_y < -8)
        trans_y += 20;

    if (start)
    {
        distance_covered += 10.0;
        if (int(distance_covered) % 9 == 8)
        {
            score += 1;
        }

        ast_y -= (level_speed);
        if (ast_y < -100)
        {
            ast_y = 0;
            level_speed += 0.04;
            level++;
        }
    }

    if (is_updated)
    {
        is_updated = false;
        glutPostRedisplay();
    }
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, timer, 0);
}

void specialKeyFunc(int key, int x, int y)
{
    if (!show_menu && !space_pressed && !collision_menu && !spacecraft_menu)
    {
        if (craft1)
        {
            if (key == GLUT_KEY_DOWN)
            {
                if (spacecraft1_y > -1.737)
                    spacecraft1_y -= 0.1;
            }
            else if (key == GLUT_KEY_UP)
            {
                if (spacecraft1_y < 16.2629)
                    spacecraft1_y += 0.1;
            }
            else if (key == GLUT_KEY_RIGHT)
            {
                if (spacecraft1_x < 8.71)
                    spacecraft1_x += 0.15;
            }
            else if (key == GLUT_KEY_LEFT)
            {
                if (spacecraft1_x > -9.79)
                    spacecraft1_x -= 0.15;
            }
        }
        else if (craft2)
        {
            if (key == GLUT_KEY_DOWN)
            {
                if (spacecraft2_y > -1.6)
                    spacecraft2_y -= 0.1;
            }
            else if (key == GLUT_KEY_UP)
            {
                if (spacecraft2_y < 17.38)
                    spacecraft2_y += 0.1;
            }
            else if (key == GLUT_KEY_RIGHT)
            {
                if (spacecraft2_x < 8.71)
                    spacecraft2_x += 0.15;
            }
            else if (key == GLUT_KEY_LEFT)
            {
                if (spacecraft2_x > -9.79)
                    spacecraft2_x -= 0.15;
            }
        }
        else if (craft3)
        {
            if (key == GLUT_KEY_DOWN)
            {
                if (spacecraft3_y > -1.737)
                    spacecraft3_y -= 0.1;
            }
            else if (key == GLUT_KEY_UP)
            {
                if (spacecraft3_y < 16.2629)
                    spacecraft3_y += 0.1;
            }
            else if (key == GLUT_KEY_RIGHT)
            {
                if (spacecraft3_x < 8.71)
                    spacecraft3_x += 0.15;
            }
            else if (key == GLUT_KEY_LEFT)
            {
                if (spacecraft3_x > -9.79)
                    spacecraft3_x -= 0.15;
            }
        }

        glutPostRedisplay();
    }
    else if (spacecraft_menu)
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
    if (!show_menu && !collision_menu && !spacecraft_menu)
    {
        switch (key)
        {
        case ' ':
            start = !start;
            space_pressed = !space_pressed;
            break;
        }
    }
    else if (spacecraft_menu && !show_menu && !collision_menu)
    {
        if (key == 13)
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
        else if (key == 27)
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
        }
    }
    else if (show_menu && !collision_menu && !spacecraft_menu)
    {
        if (key == 13)
        {
            show_menu = false;
            spacecraft_menu = true;
        }
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (show_menu && !collision_menu && !spacecraft_menu)
    {
        is_updated = true;

        // Check if the left mouse button was pressed and released
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            // Check if the mouse cursor is within the bounds of the play button
            if (x >= 380 && x <= 620 && y >= 680 && y <= 745)
            {
                // Call a function to start the game
                show_menu = false;
                spacecraft_menu = true;
            }
            // Check if the mouse cursor is within the bounds of the quit button
            else if (x >= 380 && x <= 620 && y >= 800 && y <= 865)
            {
                // Call a function to exit the program
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
    else if (collision_menu && !spacecraft_menu)
    {
        is_updated = true;

        // Check if the left mouse button was pressed and released
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            if (x >= 379 && x <= 622 && y >= 560 && y <= 625)
            {
                show_menu = true;
                collision_menu = false;
            }

            // Check if the mouse cursor is within the bounds of the play button
            else if (x >= 380 && x <= 620 && y >= 680 && y <= 745)
            {
                // Call a function to start the game
                collision_menu = false;
                spacecraft_menu = true;
                if (craft1)
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
            else if (x >= 380 && x <= 620 && y >= 800 && y <= 865)
            {
                // Call a function to exit the program
                exit(0);
            }
            // glutPostRedisplay();
        }
    }
    else if (!spacecraft_menu)
    {
        is_updated = true;
        if (space_pressed)
        {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
            {
                // Check if the mouse cursor is within the bounds of the play button
                if (x >= 0 && x <= 110 && y >= 0 && y <= 45)
                {
                    // Call a function to start the game
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
    else
    {
        is_updated = true;

        // Check if the left mouse button was pressed and released
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            // std::cout<<x<<" "<<y<<"\n";
            if (x >= 863 && x <= 901 && y >= 272 && y <= 500)
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
            else if (x >= 103 && x <= 138 && y >= 271 && y <= 501)
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
            else if (x >= 229 && x <= 409 && y >= 804 && y <= 862)
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

            }
            // Check if the mouse cursor is within the bounds of the quit button
            else if (x >= 591 && x <= 772 && y >= 804 && y <= 864)
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
    glutPostRedisplay();
}

void motion(int x, int y)
{
    if (!show_menu && !space_pressed && !collision_menu && !spacecraft_menu)
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
    else if (show_menu && !spacecraft_menu)
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
    else if (spacecraft_menu)
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    // glEnable(GL_MULTISAMPLE);
    // glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    // glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Space Game");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyFunc);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

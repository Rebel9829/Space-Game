#include "main.h"
#include <bits/stdc++.h>

int POS_X, POS_Y;

std::string spacecraft_str = "Models/X-WING1.obj";
std::string satellite_str = "Models/satellite.obj";
std::string asteroid1_str = "Models/as1.obj";
std::string asteroid2_str = "Models/as2.obj";
std::string asteroid3_str = "Models/as3.obj";
std::string asteroid4_str = "Models/as4.obj";
std::string asteroid5_str = "Models/as5.obj";
std::string asteroid6_str = "Models/as6.obj";
std::string asteroid7_str = "Models/as7.obj";
std::string asteroid8_str = "Models/as8.obj";
std::string asteroid9_str = "Models/as9.obj";
std::string asteroid10_str = "Models/as10.obj";

GLfloat light_pos[] = {-10.0f, 10.0f, 100.00f, 1.0f};

float spacecraft_x, spacecraft_y, spacecraft_z, trans_y, ast_y;
float spacecraft_x_old, spacecraft_y_old, spacecraft_z_old;
float satellite_x, satellite_y, satellite_z;
float asteroid1_x, asteroid1_y, asteroid1_z;
float asteroid2_x, asteroid2_y, asteroid2_z;
float asteroid3_x, asteroid3_y, asteroid3_z;
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
float level_speed = 0.02;
int current_scroll = 5;
float distance_covered = 0;
int score = 0;
float zoom_per_scroll = 0;

bool is_holding_mouse = false;
bool is_updated = false;
bool start = false;
bool space_pressed = false;
bool show_menu = false;
bool collision_menu = true;
bool display_level = true;

Model spacecraft_model;
Model satellite_model;
Model asteroid1_model;
Model asteroid2_model;
Model asteroid3_model;
Model asteroid4_model;
Model asteroid5_model;
Model asteroid6_model;
Model asteroid7_model;
Model asteroid8_model;
Model asteroid9_model;
Model asteroid10_model;
Model particle_model;

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
        // std::cout<<a<<" "<<b<<" "<<c<<"\n";
    }
}

void init()
{
    // glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
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

    spacecraft_model.load(spacecraft_str.c_str());
    satellite_model.load(satellite_str.c_str());
    asteroid1_model.load(asteroid1_str.c_str());
    asteroid2_model.load(asteroid2_str.c_str());
    asteroid3_model.load(asteroid3_str.c_str());
    asteroid4_model.load(asteroid4_str.c_str());
    asteroid5_model.load(asteroid5_str.c_str());
    asteroid6_model.load(asteroid6_str.c_str());
    asteroid7_model.load(asteroid7_str.c_str());
    asteroid8_model.load(asteroid8_str.c_str());
    asteroid9_model.load(asteroid9_str.c_str());
    asteroid10_model.load(asteroid10_str.c_str());

    spacecraft_x = spacecraft_model.pos_x;
    spacecraft_y = spacecraft_model.pos_y;
    spacecraft_z = spacecraft_model.pos_z - 1.0f;

    spacecraft_x_old = spacecraft_x;
    spacecraft_y_old = spacecraft_y;
    spacecraft_z_old = spacecraft_z;

    satellite_x = satellite_model.pos_x;
    satellite_y = satellite_model.pos_y;
    satellite_z = satellite_model.pos_z - 1.0f;

    asteroid1_x = asteroid1_model.pos_x;
    asteroid1_y = asteroid1_model.pos_y;
    asteroid1_z = asteroid1_model.pos_z - 1.0f;

    asteroid2_x = asteroid2_model.pos_x;
    asteroid2_y = asteroid2_model.pos_y;
    asteroid2_z = asteroid2_model.pos_z - 1.0f;

    asteroid3_x = asteroid3_model.pos_x;
    asteroid3_y = asteroid3_model.pos_y;
    asteroid3_z = asteroid3_model.pos_z - 1.0f;

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

    zoom_per_scroll = -spacecraft_model.pos_z / 10.0f;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (!show_menu && !collision_menu)
    {
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
        glTranslatef(asteroid6_x, asteroid6_y+10, asteroid6_z - 10);
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

        // glDisable(GL_LIGHTING);
        // // glColor3f(0.0,1.0,0.0);
        // // glBegin(GL_QUADS);
        // // glVertex3f(0.03, -0.68f, -2.0);
        // // glVertex3f(-0.06, -0.68f, -2.0);
        // // glVertex3f(-0.06, -0.78f, -2.0);
        // // glVertex3f(0.03, -0.78f, -2.0);
        // // glEnd();
        // glColor3f(1,0,0);
        // for(int i=0;i<100;i++){
        //     glBegin(GL_POINTS);
        //         float a = -0.04f - 0.03f * ((float)(rand()) / RAND_MAX);
        //         float b = -0.775f + 0.1f * ((float)(rand()) / RAND_MAX);
        //         // float c = -2.0f - 1.0f * ((float)(rand()) / RAND_MAX);
        //         glVertex3f(a,b,-2.0f);
        //     glEnd();
        // }
        // glColor3f(1,1,0);
        // for(int i=0;i<100;i++){
        //     glBegin(GL_POINTS);
        //         float a = -0.04f - 0.03f * ((float)(rand()) / RAND_MAX);
        //         float b = -0.775f + 0.1f * ((float)(rand()) / RAND_MAX);
        //         // float c = -2.0f - 1.0f * ((float)(rand()) / RAND_MAX);
        //         glVertex3f(a,b,-2.0f);
        //     glEnd();
        // }
        // glEnable(GL_LIGHTING);

        // std::cout<<spacecraft_x<<" "<<spacecraft_y<<" "<<spacecraft_z<<" \n";
        glTranslatef(spacecraft_x, spacecraft_y - 8.0, spacecraft_z + 3);
        glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
        glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
        glRotatef(90, 0, 0, 1);
        spacecraft_model.draw();
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
    else if (show_menu && !collision_menu)
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

        // Draw the quit button
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

    glFlush();
    glutSwapBuffers();
}

void timer(int value)
{
    if (start)
    {
        distance_covered += 10.0;
        if (int(distance_covered) % 9 == 8)
        {
            score += 1;
        }

        trans_y -= 0.01;

        if (trans_y < -8)
            trans_y += 20;

        ast_y -= (level_speed);
        if (ast_y < -100)
        {
            ast_y = 0;
            level_speed += 0.005;
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
    if (!show_menu && !space_pressed && !collision_menu)
    {
        if (key == GLUT_KEY_DOWN)
        {
            spacecraft_y -= 0.1;
            if (spacecraft_y < -10.5)
                spacecraft_y = -8.5;
        }
        else if (key == GLUT_KEY_UP)
        {
            spacecraft_y += 0.1;
            // if (pos_y > 0.9)
            //     pos_y = -0.9;
        }
        else if (key == GLUT_KEY_RIGHT)
        {
            spacecraft_x += 0.1;
            // if (pos_x > 0.4)
            //     pos_x = 0.3;
        }
        else if (key == GLUT_KEY_LEFT)
        {
            spacecraft_x -= 0.1;
            // if (pos_x < -1.4)
            //     pos_x = 0.3;
        }

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (!show_menu && !collision_menu)
    {
        switch (key)
        {
        case ' ':
            start = !start;
            space_pressed = !space_pressed;
            break;
            glutPostRedisplay();
        }
    }
}

void mouse(int button, int state, int x, int y)
{
    if (show_menu && !collision_menu)
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
                trans_y = 0;
                distance_covered = 0;
                start = true;
                ast_y = 0;
                level_speed = 0.02;
                level = 1;

                glutPostRedisplay();
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
        else if (state == GLUT_UP)
        {
            switch (button)
            {
            case 3:
                if (current_scroll > 0)
                {
                    current_scroll--;
                    satellite_z += zoom_per_scroll;
                }
                break;
            case 4:
                if (current_scroll < 15)
                {
                    current_scroll++;
                    satellite_z -= zoom_per_scroll;
                }
                break;
            }
        }
    }
    else if (collision_menu)
    {
        is_updated = true;

        // Check if the left mouse button was pressed and released
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            if (x >= 380 && x <= 620 && y >= 580 && y <= 625)
            {
                show_menu = true;
                collision_menu = false;
            }

            // Check if the mouse cursor is within the bounds of the play button
            else if (x >= 380 && x <= 620 && y >= 680 && y <= 745)
            {
                // Call a function to start the game
                collision_menu = false;
                trans_y = 0;
                score = 0;
                distance_covered = 0;
                start = true;
                ast_y = 0;
                level_speed = 0.02;
                level = 1;
            }
            // Check if the mouse cursor is within the bounds of the quit button
            else if (x >= 380 && x <= 620 && y >= 800 && y <= 865)
            {
                // Call a function to exit the program
                exit(0);
            }
            glutPostRedisplay();
        }
    }
    else
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

                    spacecraft_x = spacecraft_x_old;
                    spacecraft_y = spacecraft_y_old;
                    spacecraft_z = spacecraft_z_old;

                    glutPostRedisplay();
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
            else if (state == GLUT_UP)
            {
                switch (button)
                {
                case 3:
                    if (current_scroll > 0)
                    {
                        current_scroll--;
                        spacecraft_z += zoom_per_scroll;
                    }
                    break;
                case 4:
                    if (current_scroll < 15)
                    {
                        current_scroll++;
                        spacecraft_z -= zoom_per_scroll;
                    }
                    break;
                }
            }
        }
    }
}

void motion(int x, int y)
{
    if (!show_menu && !space_pressed && !collision_menu)
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
    else
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
    glutCreateWindow("Load Model");
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

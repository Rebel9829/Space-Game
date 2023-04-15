#include "main.h"
#include <bits/stdc++.h>

int POS_X, POS_Y;

std::string spacecraft_str = "Models/X-WING1.obj";
std::string satellite_str = "Models/satellite.obj";
std::string asteroid_str = "Models/as1.obj";

GLfloat light_pos[] = {-10.0f, 10.0f, 100.00f, 1.0f};

float spacecraft_x, spacecraft_y, spacecraft_z, trans_y;
float satellite_x, satellite_y, satellite_z;
float asteroid_x, asteroid_y, asteroid_z;
float angle_x = -45.0f, angle_y = 90.0f;
float ast_pos = 1000.0;

int x_old = 0, y_old = 0;
int current_scroll = 5;
float zoom_per_scroll;

bool is_holding_mouse = false;
bool is_updated = false;
bool start = true;

Model spacecraft_model;
Model satellite_model;
Model asteroid_model;

float initial = 0.0;

float randomFloat()
{
    // srand(1);
    return -10.0f + 20.0f * ((float)(rand()) / RAND_MAX);
}

void background()
{
    glColor3f(1, 1, 1);

    srand(1);

    for (int i = 0; i < 1000; i++)
    {
        int s = ((int)rand()) % 3 + 1;
        glPointSize(s);
        glBegin(GL_POINTS);
        float a = randomFloat();
        float b = randomFloat();
        float c = randomFloat();
        glVertex3f(a, initial + b, c);
        glEnd();
        // std::cout<<a<<" "<<b<<" "<<c<<"\n";
    }
}

void init()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    asteroid_model.load(asteroid_str.c_str());

    spacecraft_x = spacecraft_model.pos_x;
    spacecraft_y = spacecraft_model.pos_y;
    spacecraft_z = spacecraft_model.pos_z - 1.0f;

    satellite_x = satellite_model.pos_x;
    satellite_y = satellite_model.pos_y;
    satellite_z = satellite_model.pos_z - 1.0f;

    asteroid_x = asteroid_model.pos_x;
    asteroid_y = asteroid_model.pos_y;
    asteroid_z = asteroid_model.pos_z - 1.0f;

    zoom_per_scroll = -spacecraft_model.pos_z / 10.0f;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE); // disable depth writes
    glTranslatef(0, trans_y, 0);
    background();
    glDepthMask(GL_TRUE); // enable depth writes
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(asteroid_x, asteroid_y, asteroid_z-5);
    asteroid_model.draw();
    glPopMatrix();
    glPopMatrix();
    // std::cout<<asteroid_z<<" "<<spacecraft_z;
    glPushMatrix();
    glTranslatef(spacecraft_x, spacecraft_y - 8.0, spacecraft_z + 3);
    glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    glRotatef(90, 0, 0, 1);
    spacecraft_model.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(satellite_x+15, satellite_y, satellite_z-50);
    // glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
    // glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    satellite_model.draw();
    glPopMatrix();

    // glPushMatrix();
    // glTranslatef(asteroid_x - 10, asteroid_y + 20, asteroid_z - ast_pos);
    // glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
    // glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    // asteroid_model.draw();
    // glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void timer(int value)
{
    if (start)
    {
        trans_y -= 0.01;
        if(trans_y < -8) trans_y+=20;
        // initial+=0.01;
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

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        start = !start;
        break;
    glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{
    is_updated = true;

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

void motion(int x, int y)
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glutSetOption(GLUT_MULTISAMPLE, 8);
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

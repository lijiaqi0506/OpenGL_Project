//  ====================================================================
//  COSC363: Assignment 1
//  Date:07/04/2021
//  Author: LI JIAQI
//  ID: 75766881
//  ====================================================================

#include <iostream>
#include <fstream>
#include <climits>
#include <math.h>
#include <GL/freeglut.h>
#include "loadBMP.h"
#include "loadTGA.h"
#include <cmath>
using namespace std;

//--Globals ---------------------------------------------------------------
const int N = 2;
float vx_init[N] = {0,10};
float vy_init[N] = {0};
float vz_init[N] = { 0,10 };

float theta = 10;
float radian = theta * (M_PI/180);
bool new_flag = false;
float *x, *y, *z;       //vertex coordinate arrays
int *t1, *t2, *t3;      //triangles
int nvrt, ntri;         //total number of vertices and triangles
float sphere_x = -62;
float cam_angle=0;
int step = 0;
float  cam_x = 0,  cam_y = 50,  cam_z = 300;    //Initial camera position
float look_x = 0, look_y = 50, look_z = -400;    //"Look-at" point along -z direction
float sec=1;
float d=20;
float rotate = 90.0;
float ro_ammo = 0.0;
bool flag = true;
float shadowMat[16] = { 100.,0,0,0, -100.,0,-100.,-1,0,0,100.,0, 0,0,0,100. };
GLuint txId[8];
float timet = 0;
float blue_x = 290.0;
float blue_y = 154.0;
void loadTexture()
{
    glGenTextures(8, txId);                // Create a Texture object
    glBindTexture(GL_TEXTURE_2D, txId[0]);     //Use this texture
    loadBMP("down.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("up.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
    loadTGA("back.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture
    loadTGA("front.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[4]);  //Use this texture
    loadTGA("left.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[5]);  //Use this texture
    loadTGA("right.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[6]);  //Use this texture
    loadBMP("Wall.bmp");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[7]);     //Use this texture
    loadBMP("Road.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

void skybox() {
    glEnable(GL_BLEND);
    glColor4f(1.0, 1.0, 1.0, 0.9);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);

        // Back
        glBindTexture(GL_TEXTURE_2D, txId[2]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);     glVertex3f(-400.0, -0.1, -400.0);
            glTexCoord2f(1.0, 0.0);     glVertex3f( 400.0, -0.1, -400.0);
            glTexCoord2f(1.0, 1.0);     glVertex3f( 400.0,  399.9, -400.0);
            glTexCoord2f(0.0, 1.0);     glVertex3f(-400.0,  399.9, -400.0);
        glEnd();
        // Front
        glBindTexture(GL_TEXTURE_2D, txId[3]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);     glVertex3f( 400.0, -0.1, 400.0);
            glTexCoord2f(1.0, 0.0);     glVertex3f(-400.0, -0.1, 400.0);
            glTexCoord2f(1.0, 1.0);     glVertex3f(-400.0,  399.9, 400.0);
            glTexCoord2f(0.0, 1.0);     glVertex3f( 400.0,  399.9, 400.0);
        glEnd();

        // Left
        glBindTexture(GL_TEXTURE_2D, txId[4]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);     glVertex3f(-400.0, -0.1,  400.0);
            glTexCoord2f(1.0, 0.0);     glVertex3f(-400.0, -0.1, -400.0);
            glTexCoord2f(1.0, 1.0);     glVertex3f(-400.0,  399.9, -400.0);
            glTexCoord2f(0.0, 1.0);     glVertex3f(-400.0,  399.9,  400.0);
        glEnd();
        // Right
        glBindTexture(GL_TEXTURE_2D, txId[5]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);     glVertex3f(400.0, -0.1, -400.0);
            glTexCoord2f(1.0, 0.0);     glVertex3f(400.0, -0.1,  400.0);
            glTexCoord2f(1.0, 1.0);     glVertex3f(400.0,  399.9,  400.0);
            glTexCoord2f(0.0, 1.0);     glVertex3f(400.0,  399.9, -400.0);
        glEnd();

         // Top
        glBindTexture(GL_TEXTURE_2D, txId[1]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);     glVertex3f( 400.0,  399.9, -400.0);
            glTexCoord2f(1.0, 0.0);     glVertex3f( 400.0,  399.9,  400.0);
            glTexCoord2f(1.0, 1.0);     glVertex3f(-400.0,  399.9,  400.0);
            glTexCoord2f(0.0, 1.0);     glVertex3f(-400.0,  399.9, -400.0);
        glEnd();



    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glDisable(GL_BLEND);

}
//-- Loads mesh data in OFF format    -------------------------------------
void loadMeshFile(const char* fname)
{
    ifstream fp_in;
    int num, ne;

    fp_in.open(fname, ios::in);
    if(!fp_in.is_open())
    {
        cout << "Error opening mesh file" << endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');                //ignore first line
    fp_in >> nvrt >> ntri >> ne;                // read number of vertices, polygons, edges

    x = new float[nvrt];                        //create arrays
    y = new float[nvrt];
    z = new float[nvrt];

    t1 = new int[ntri];
    t2 = new int[ntri];
    t3 = new int[ntri];

    for(int i=0; i < nvrt; i++)                         //read vertex list
        fp_in >> x[i] >> y[i] >> z[i];

    for(int i=0; i < ntri; i++)                         //read polygon list
    {
        fp_in >> num >> t1[i] >> t2[i] >> t3[i];
        if(num != 3)
        {
            cout << "ERROR: Polygon with index " << i  << " is not a triangle." << endl;  //not a triangle!!
            exit(1);
        }
    }

    fp_in.close();
    cout << " File successfully read." << endl;
}

//--Function to compute the normal vector of a triangle with index tindx ----------
void normal(int tindx)
{
    float x1 = x[t1[tindx]], x2 = x[t2[tindx]], x3 = x[t3[tindx]];
    float y1 = y[t1[tindx]], y2 = y[t2[tindx]], y3 = y[t3[tindx]];
    float z1 = z[t1[tindx]], z2 = z[t2[tindx]], z3 = z[t3[tindx]];
    float nx, ny, nz;
    nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

//--------draws the mesh model of the cannon----------------------------
void drawCannon()
{
    glColor3f(0.4, 0.5, 0.4);

    //Construct the object model here using triangles read from OFF file
    glBegin(GL_TRIANGLES);
        for(int tindx = 0; tindx < ntri; tindx++)
        {
           normal(tindx);
           glVertex3d(x[t1[tindx]], y[t1[tindx]], z[t1[tindx]]);
           glVertex3d(x[t2[tindx]], y[t2[tindx]], z[t2[tindx]]);
           glVertex3d(x[t3[tindx]], y[t3[tindx]], z[t3[tindx]]);
        }
    glEnd();
}

//----------draw a floor plane-------------------
void drawFloor()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[0]);

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    for(int x = -400; x <= 400; x += 20)
    {
        for(int z = -400; z <= 400; z += 20)
        {
            glTexCoord2f(0., 0.); glVertex3f(x, -0.1, z);
            glTexCoord2f(1., 0.); glVertex3f(x, -0.1, z+20);
            glTexCoord2f(1.,1. ); glVertex3f(x+20, -0.1, z+20);
            glTexCoord2f(0.,1. ); glVertex3f(x+20, -0.1, z);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

}


void drawWall()
{
    glBegin(GL_QUADS);
      glNormal3f(-1.0, 0.0, 0.0);
      glTexCoord2f(0., 0.);  glVertex3f(290, 0.0, -75.0);
      glTexCoord2f(1., 0.);  glVertex3f(290, 0.0, 75.0);
      glTexCoord2f(1.,1 ); glVertex3f(290, 150, 75.0);
      glTexCoord2f(0.,1 ); glVertex3f(290, 150, -75.0);

      glNormal3f(1.0, 0.0, 0.0);
      glTexCoord2f(0., 0.);  glVertex3f(320, 0.0, -75.0);
      glTexCoord2f(1., 0.);  glVertex3f(320, 0.0, 75.0);
      glTexCoord2f(1.,1 ); glVertex3f(320, 150, 75.0);
      glTexCoord2f(0.,1 ); glVertex3f(320, 150, -75.0);

      glNormal3f(0.0, 0.0, 1.0);
      glTexCoord2f(0., 0.);  glVertex3f(290, 0.0, 75.0);
      glTexCoord2f(0.5, 0.);  glVertex3f(320, 0.0, 75.0);
      glTexCoord2f(0.5,1 ); glVertex3f(320, 150, 75.0);
      glTexCoord2f(0.,1 ); glVertex3f(290, 150, 75.0);

      glNormal3f(0.0, 0.0, -1.0);
      glTexCoord2f(0., 0.);  glVertex3f(290, 0.0, -75.0);
      glTexCoord2f(0.5, 0.);  glVertex3f(320, 0.0, -75.0);
      glTexCoord2f(0.5,1 ); glVertex3f(320, 150, -75.0);
      glTexCoord2f(0.,1 ); glVertex3f(290, 150, -75.0);
    glEnd();

}
void drawModel()
{
    glPushMatrix();
        glColor3f(1, 0.4, 0);
        glTranslatef(-10, 5, 17);
        glScalef(80, 10, 6);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20, 25, 17);
        glScalef(40, 30, 6);
        glColor3f(1, 0.4, 0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 0.4, 0);
        glTranslatef(-10, 5, -17);
        glScalef(80, 10, 6);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20, 25, -17);
        glScalef(40, 30, 6);
        glColor3f(1, 0.4, 0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        drawCannon();
    glPopMatrix();


}
void drawYi()
{
    glPushMatrix();
      glTranslatef(-28,30,0);
      glScalef(3,7,0.7);
      glRotatef(90, 0, 1, 0);
      glutSolidCube(1);
    glPopMatrix();
}
void drawAmmo()
{   glPushMatrix();
    glPushMatrix();
      glScalef(3,1,1);
      glTranslatef(0,30,0);
      glRotatef(90, 0, 1, 0);
      glutSolidCone(2, 2, 60, 60);
    glPopMatrix();

    glPushMatrix();
      glScalef(3,1,1);
      glTranslatef(-3,30,0);
      glRotatef(90, 0, 1, 0);
      GLUquadric *q;
      q = gluNewQuadric();
      gluCylinder(q, 2, 2, 3, 60, 60);
      gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();

    glPushMatrix();
      glScalef(4,1,1);
      glTranslatef(-4,30,0);
      glRotatef(90, 0, 1, 0);
      GLUquadric *qq;
      qq = gluNewQuadric();
      gluCylinder(qq, 1, 2, 2, 60, 60);
      gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-13,30,0);
      glScalef(3,7,0.7);
      glRotatef(90, 0, 1, 0);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(15,30,-30);
      glRotatef(90,1,0,0);
      drawYi();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-13,30,0);
      glutSolidSphere(1,100,100);
    glPopMatrix();

    glPopMatrix();


}
void drawbai()
{
    glPushMatrix();
        glTranslatef(150,145,0);
        glScalef(1, 200, 1);
        glutSolidCube(1);


    glPopMatrix();


    glPushMatrix();

        glTranslatef(150,30,0);
        glRotatef(90, 0, 1, 0);
        glutSolidTorus(4, 20,20, 20);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(150,245,0);
        glutSolidSphere(2, 50,50);

    glPopMatrix();
}
void drawRoad()
{
    glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, txId[7]);
      drawWall();


    glBegin(GL_QUADS);
      glNormal3f(0.0, 1.0, 0.0);
      glTexCoord2f(0., 0.);  glVertex3f(-400, -0.05, 75.0);
      glTexCoord2f(1., 0.);  glVertex3f(400, -0.05, 75.0);
      glTexCoord2f(1.,1 ); glVertex3f(400, -0.05, -75.0);
      glTexCoord2f(0.,1 ); glVertex3f(-400, -0.05, -75.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

void normal2(float x1, float y1, float z1,
            float x2, float y2, float z2,
              float x3, float y3, float z3 )
{
      float nx, ny, nz;
      nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
      ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
      nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);

      glNormal3f(nx, ny, nz);
}
void drawWormhole()
{
    float vx[N], vy[N], vz[N];
    float wx[N], wy[N], wz[N];

    for (int i = 0; i < N; i++) {
        vx[i] = vx_init[i];
        vy[i] = vy_init[i];
        vz[i] = vz_init[i];
    }
    for(int j = 0; j < 36; j++) {

        for(int i = 0; i < N; i++) {
            wx[i] =  vx[i]* cos(radian) + vz[i] * sin(radian);
            wy[i] =  vy[i];
            wz[i] = -vx[i]*sin(radian) + vz[i] * cos(radian);
        }

        glBegin((GL_TRIANGLE_STRIP));
        for (int i = 0; i<N; i++) {
            if(i > 0) normal2(vx[i-1], vy[i-1], vz[i-1],
                     wx[i-1], wy[i-1], wz[i-1],
                     vx[i], vy[i], vz[i]);

            glVertex3f(vx[i], vy[i], vz[i]);

            if(i > 0) normal2(wx[i-1], wy[i-1], wz[i-1],wx[i], wy[i], wz[i],vx[i], vy[i], vz[i]);

            glVertex3f(wx[i], wy[i], wz[i]);
        }

        glEnd();

        for(int i = 0; i < N; i++) {
            vx[i] = wx[i];
            vy[i] = wy[i];
            vz[i] = wz[i];
        }
    }
}
//--Display: ----------------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
    float lpos[4] = {100., 100., 100., 1.0};  //light's position


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    cam_x += step * sec * -sin(cam_angle);
    cam_z += step * sec * -cos(cam_angle);
    step = 0;

    if (cam_x >=330){
        cam_x = 330;
    }
    else if(cam_x <=-330){
        cam_x = -330;
    }
    if (cam_z >= 330){
        cam_z = 330;
    }
    else if (cam_z <=-330){
        cam_z = -330;
    }

    look_x = cam_x+d*-sin(cam_angle);
    look_y = cam_y;
    look_z = cam_z+d*-cos(cam_angle);


    gluLookAt(cam_x, cam_y, cam_z,  look_x, look_y, look_z, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //set light position


    glPushMatrix();
        glTranslatef(0,-0.1,0);
        drawFloor();
    glPopMatrix();


    //--start here

    glDisable(GL_LIGHTING);
    glPushMatrix(); //Draw Shadow Object
      glMultMatrixf(shadowMat);
      glTranslatef(-150,245,0);
      glRotatef(rotate, 1, 0, 0);
      glTranslatef(150,-245,0);/* Object Transformations */
      glColor4f(0.2, 0.2, 0.2, 1.0);
      drawbai();
    glPopMatrix();
    glEnable(GL_LIGHTING);



    glPushMatrix();
        glTranslatef(-150,245,0);
        glRotatef(rotate, 1, 0, 0);
        glTranslatef(150,-245,0);
        glColor3f(1, 0, 0);
        drawbai();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-100,0,0);

        drawModel();
    glPopMatrix();


    glDisable(GL_LIGHTING);
    glPushMatrix(); //Draw Shadow Object
      glMultMatrixf(shadowMat);
      glTranslatef(sphere_x, 30, 0);
        glRotatef(ro_ammo,1,0,0);
      glTranslatef(0, -30, 0);/* Object Transformations */
      glColor4f(0.2, 0.2, 0.2, 1.0);
      drawAmmo();
    glPopMatrix();
    glEnable(GL_LIGHTING);





    glPushMatrix();
        glTranslatef(sphere_x, 30, 0);
        glRotatef(ro_ammo,1,0,0);
        glTranslatef(0, -30, 0);
        glColor3f(1, 1, 1);
        drawAmmo();
    glPopMatrix();

    glPushMatrix();
      skybox();
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glPushMatrix(); //Draw Shadow Object
      glMultMatrixf(shadowMat);
      glColor4f(0.2, 0.2, 0.2, 1.0);
      drawWall();
    glPopMatrix();
    glEnable(GL_LIGHTING);


    glPushMatrix();
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, txId[6]);
      drawWall();
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(blue_x-20*timet,blue_y-0.5*9.8*timet*timet,0);
      glColor4f(0.3, 0.7, 1,1);
      glutSolidSphere(5, 100, 100);
    glPopMatrix();

    glPushMatrix();
      drawRoad();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(177,0,0);
      glColor4f(0.0, 0.0, 0.0,1);
      drawWormhole();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(300,170,0);
      glRotatef(90,0,0,1);
      drawWormhole();
    glPopMatrix();







    glutSwapBuffers();
}

//------------TIMER FUNCTION----------------------------------------------
void myTimer(int value)
{

    if (sphere_x <= 290)
        sphere_x += 1.21;
    if (rotate == 90 || rotate == -90)
        sphere_x = -62;
    if (rotate == 90) flag = true;
    if (rotate == -90) flag = false;
    if(flag == true) rotate-=0.5;
    if (flag == false) rotate+=0.5;
    ro_ammo+=50;
    if (290 <= sphere_x) {
        new_flag = true;
    }
    if (new_flag == true) {
        timet+=0.05;
    }
    if (blue_y-0.5*9.8*timet*timet <= 0) {
        timet = 0;
        new_flag = false;
    }
    printf("%f\n",blue_x-20*timet);
    glutPostRedisplay();
    glutTimerFunc(30, myTimer, value);
}
//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
    loadTexture();
    loadMeshFile("Cannon.off");             //Specify mesh file name here
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //Background colour

    glEnable(GL_LIGHTING);                  //Enable OpenGL states
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 50, 1000);  //The camera view volume
}


void special(int key, int x, int y)
{
    step = 0;
    if(key == GLUT_KEY_LEFT){
        cam_angle += 0.1;   //in radians
    }else if(key == GLUT_KEY_RIGHT){
         cam_angle -= 0.1;
    }else if(key == GLUT_KEY_DOWN){
        step = -5;
        printf("%f %f\n",look_x,look_z);
    }else if(key == GLUT_KEY_UP){
        step = 5;
        printf("%f %f\n",look_x,look_z);
    }

    glutPostRedisplay();
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE |GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (1024, 768);
   glutInitWindowPosition (4, 3);
   glutCreateWindow ("The Shy");
   initialize();

   glutDisplayFunc(display);
   glutTimerFunc(30, myTimer, 0);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}

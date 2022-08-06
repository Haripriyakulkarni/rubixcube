#include <string.h>
#include<GL/glut.h>
#include<stdio.h>
void *font = GLUT_BITMAP_TIMES_ROMAN_24;
char defaultMessage[] = "Rotation Speed:";
char *message = defaultMessage;
void
output(int x, int y, char *string)
{
int len, i;
glRasterPos2f(x, y);
len = (int) strlen(string);
for (i = 0; i < len; i++) {
glutBitmapCharacter(font, string[i]);
}
}
static float speed=0.0;
static int top[3][3]={{0,0,0},{0,0,0},{0,0,0}},
right[3][3]={{1,1,1},{1,1,1},{1,1,1}},
front[3][3]={{2,2,2},{2,2,2},{2,2,2}},
back[3][3]={{3,3,3},{3,3,3},{3,3,3}},
bottom[3][3]={{4,4,4},{4,4,4},{4,4,4}},
left[3][3]={{5,5,5},{5,5,5},{5,5,5}},
temp[3][3];
int solve[300];
int count=0;
int solve1=0;
static int rotation=0;
int rotationcomplete=0;
static GLfloat theta=0.0;
static GLint axis=0;
static GLfloat p=0.0,q=0.0,r=0.0;
static GLint inverse=0;
static GLfloat angle=0.0;
int beginx=0,beginy=0;
int moving=0;
static int speedmetercolor[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static int speedmetercount=-1;
GLfloat vertices[][3]={{-1.0,-1.0,-1.0},
{1.0,-1.0,-1.0},
{1.0,1.0,-1.0},
{-1.0,1.0,-1.0}, //center
{-1.0,-1.0,1.0},
{1.0,-1.0,1.0},
{1.0,1.0,1.0},
{-1.0,1.0,1.0},
{-1.0,-3.0,-1.0},
{1.0,-3.0,-1.0},
{1.0,-1.0,-1.0},
{-1.0,-1.0,-1.0}, //bottom center
{-1.0,-3.0,1.0},
{1.0,-3.0,1.0},
{1.0,-1.0,1.0},
{-1.0,-1.0,1.0},
{-3.0,-1.0,-1.0},
{-1.0,-1.0,-1.0},
{-1.0,1.0,-1.0},
{-3.0,1.0,-1.0}, //left center
{-3.0,-1.0,1.0},
{-1.0,-1.0,1.0},
{-1.0,1.0,1.0},
{-3.0,1.0,1.0},
{1.0,-1.0,-1.0},
{3.0,-1.0,-1.0},
{3.0,1.0,-1.0},
{1.0,1.0,-1.0}, // right center
{1.0,-1.0,1.0},
{3.0,-1.0,1.0},
{3.0,1.0,1.0},
{1.0,1.0,1.0},
{-1.0,1.0,-1.0},
{1.0,1.0,-1.0},
{1.0,3.0,-1.0},
{-1.0,3.0,-1.0}, // top center
{-1.0,1.0,1.0},
{1.0,1.0,1.0},
{1.0,3.0,1.0},
{-1.0,3.0,1.0},
{-1.0,-1.0,1.0},
{1.0,-1.0,1.0},
{1.0,1.0,1.0},
{-1.0,1.0,1.0}, //front center
{-1.0,-1.0,3.0},
{1.0,-1.0,3.0},
{1.0,1.0,3.0},
{-1.0,1.0,3.0},
{-1.0,-1.0,-3.0},
{1.0,-1.0,-3.0},
{1.0,1.0,-3.0},
{-1.0,1.0,-3.0}, //back center
{-1.0,-1.0,-1.0},
{1.0,-1.0,-1.0},
{1.0,1.0,-1.0},
{-1.0,1.0,-1.0},
{-3.0,1.0,-1.0},
{-1.0,1.0,-1.0},
{-1.0,3.0,-1.0},
{-3.0,3.0,-1.0}, // top left center
{-3.0,1.0,1.0},
{-1.0,1.0,1.0},
{-1.0,3.0,1.0},
{-3.0,3.0,1.0},
{1.0,1.0,-1.0},
{3.0,1.0,-1.0},
{3.0,3.0,-1.0},
{1.0,3.0,-1.0}, // top right center
{1.0,1.0,1.0},
{3.0,1.0,1.0},
{3.0,3.0,1.0},
{1.0,3.0,1.0},
{-1.0,1.0,1.0},
{1.0,1.0,1.0},
{1.0,3.0,1.0},
{-1.0,3.0,1.0}, // top front center
{-1.0,1.0,3.0},
{1.0,1.0,3.0},
{1.0,3.0,3.0},
{-1.0,3.0,3.0},
{-1.0,1.0,-3.0},
{1.0,1.0,-3.0},
{1.0,3.0,-3.0},
{-1.0,3.0,-3.0}, // top back center
{-1.0,1.0,-1.0},
{1.0,1.0,-1.0},
{1.0,3.0,-1.0},
{-1.0,3.0,-1.0},
{-3.0,-3.0,-1.0},
{-1.0,-3.0,-1.0},
{-1.0,-1.0,-1.0},
{-3.0,-1.0,-1.0}, //bottom left center
{-3.0,-3.0,1.0},
{-1.0,-3.0,1.0},
{-1.0,-1.0,1.0},
{-3.0,-1.0,1.0},
{1.0,-3.0,-1.0},
{3.0,-3.0,-1.0},
{3.0,-1.0,-1.0},
{1.0,-1.0,-1.0}, //bottom right center
{1.0,-3.0,1.0},
{3.0,-3.0,1.0},
{3.0,-1.0,1.0},
{1.0,-1.0,1.0},
{-1.0,-3.0,1.0},
{1.0,-3.0,1.0},
{1.0,-1.0,1.0},
{-1.0,-1.0,1.0}, //bottom front center
{-1.0,-3.0,3.0},
{1.0,-3.0,3.0},
{1.0,-1.0,3.0},
{-1.0,-1.0,3.0},
{-1.0,-3.0,-3.0},
{1.0,-3.0,-3.0},
{1.0,-1.0,-3.0},
{-1.0,-1.0,-3.0}, //bottom back center
{-1.0,-3.0,-1.0},
{1.0,-3.0,-1.0},
{1.0,-1.0,-1.0},
{-1.0,-1.0,-1.0},
{-3.0,1.0,-3.0},
{-1.0,1.0,-3.0},
{-1.0,3.0,-3.0},
{-3.0,3.0,-3.0}, // top left back
{-3.0,1.0,-1.0},
{-1.0,1.0,-1.0},
{-1.0,3.0,-1.0},
{-3.0,3.0,-1.0},
{-3.0,1.0,1.0},
{-1.0,1.0,1.0},
{-1.0,3.0,1.0},
{-3.0,3.0,1.0}, // top left front
{-3.0,1.0,3.0},
{-1.0,1.0,3.0},
{-1.0,3.0,3.0},
{-3.0,3.0,3.0},
{1.0,1.0,-3.0},
{3.0,1.0,-3.0},
{3.0,3.0,-3.0},
{1.0,3.0,-3.0}, // top right back
{1.0,1.0,-1.0},
{3.0,1.0,-1.0},
{3.0,3.0,-1.0},
{1.0,3.0,-1.0},
{1.0,1.0,1.0},
{3.0,1.0,1.0},
{3.0,3.0,1.0},
{1.0,3.0,1.0}, // top right front
{1.0,1.0,3.0},
{3.0,1.0,3.0},
{3.0,3.0,3.0},
{1.0,3.0,3.0},
{-3.0,-1.0,-3.0},
{-1.0,-1.0,-3.0},
{-1.0,1.0,-3.0},
{-3.0,1.0,-3.0}, //ceneter left back
{-3.0,-1.0,-1.0},
{-1.0,-1.0,-1.0},
glVertex3fv(vertices[e]);
glEnd();
}
void colorcube1()
{
polygon(6,0,3,2,1);
polygon(6,2,3,7,6);
polygon(6,0,4,7,3); // center piece
polygon(6,1,2,6,5);
polygon(6,4,5,6,7);
polygon(6,0,1,5,4);
}
void colorcube2()
{
polygon(6,8,11,10,9);
polygon(6,10,11,15,14);
polygon(6,8,12,15,11); // bottom center
polygon(6,9,10,14,13);
polygon(6,12,13,14,15);
polygon(bottom[1][1],8,9,13,12);
}
void colorcube3()
{
polygon(6,16,19,18,17);
polygon(6,18,19,23,22);
polygon(left[1][1],16,20,23,19); // left center
polygon(6,17,18,22,21);
glPopMatrix();
colorcube9();
colorcube10();
colorcube11();
colorcube16();
colorcube17();
colorcube18();
colorcube19();
colorcube20();
colorcube21();
colorcube22();
colorcube23();
if(inverse==0)
{glPushMatrix();
glColor3fv(color[0]);
output(-11,6,"Bottom");
glPopMatrix();
glRotatef(theta,0.0,1.0,0.0);
}
else
{glPushMatrix();
glColor3fv(color[0]);
output(-11,6,"BottomInverted");
glPopMatrix();
glRotatef(-theta,0.0,1.0,0.0);
}
colorcube2();
colorcube12();
colorcube13();
colorcube14();
colorcube15();
colorcube24();
colorcube25();
colorcube26();
colorcube27();
}
glPopMatrix();
/*glPushMatrix();
glTranslatef(-.5,-4,0);
glScalef(speed/4.5,1.0,1.0);
glTranslatef(0.5,4,0);
polygon(5,216,217,218,219);
glPopMatrix();
*/
glFlush();
glutSwapBuffers();
}
void transpose(char a)
{
if(a=='r')
{
int temp;
temp=right[0][0];
right[0][0]=right[2][0];
right[2][0]=right[2][2];
right[2][2]=right[0][2];
right[0][2]=temp;
temp=right[1][0];
right[1][0]=right[2][1];
right[2][1]=right[1][2];
right[1][2]=right[0][1];
right[0][1]=temp;
}
if(a=='t')
{
int temp;
temp=top[0][0];
top[0][0]=top[2][0];
top[2][0]=top[2][2];
top[2][2]=top[0][2];
top[0][2]=temp;
temp=top[1][0];
top[1][0]=top[2][1];
top[2][1]=top[1][2];
top[1][2]=top[0][1];
top[0][1]=temp;
}
if(a=='f')
{
int temp;
temp=front[0][0];
front[0][0]=front[2][0];
front[2][0]=front[2][2];
front[2][2]=front[0][2];
front[0][2]=temp;
temp=front[1][0];
front[1][0]=front[2][1];
front[2][1]=front[1][2];
front[1][2]=front[0][1];
front[0][1]=temp;
}
if(a=='l')
{
int temp;
temp=left[0][0];
left[0][0]=left[2][0];
left[2][0]=left[2][2];
left[2][2]=left[0][2];
left[0][2]=temp;
temp=left[1][0];
left[1][0]=left[2][1];
left[2][1]=left[1][2];
left[1][2]=left[0][1];
left[0][1]=temp;
}
if(a=='k')
{
int temp;
temp=back[0][0];
back[0][0]=back[2][0];
back[2][0]=back[2][2];
back[2][2]=back[0][2];
back[0][2]=temp;
temp=back[1][0];
back[1][0]=back[2][1];
back[2][1]=back[1][2];
back[1][2]=back[0][1];
back[0][1]=temp;
}
if(a=='b')
{
int temp;
temp=bottom[0][0];
bottom[0][0]=bottom[2][0];
bottom[2][0]=bottom[2][2];
bottom[2][2]=bottom[0][2];
bottom[0][2]=temp;
temp=bottom[1][0];
bottom[1][0]=bottom[2][1];
bottom[2][1]=bottom[1][2];
bottom[1][2]=bottom[0][1];
bottom[0][1]=temp;
}
}
void topc()
{
transpose('t');
int temp1=front[0][0];
int temp2=front[0][1];
}
if(key=='t'&&rotationcomplete==1)
{rotationcomplete=0;
rotation=5;
inverse=1;
solve[++count]=-5;
glutIdleFunc(spincube);
}
if(key=='h'&&rotationcomplete==1)
{rotationcomplete=0;
rotation=6;
inverse=0;
solve[++count]=6;
glutIdleFunc(spincube);
}
if(key=='y'&&rotationcomplete==1)
{rotationcomplete=0;
rotation=6;
inverse=1;
solve[++count]=-6;
glutIdleFunc(spincube);
}
if(key=='2'&&rotationcomplete==1)
{
p=p+2.0;
glutIdleFunc(spincube);
}
if(key=='8'&&rotationcomplete==1)
{
p=p-2.0;
glutIdleFunc(spincube);
}
if(key=='6'&&rotationcomplete==1)
{
q=q+2.0;
glutIdleFunc(spincube);
}
if(key=='4'&&rotationcomplete==1)
{
q=q-2.0;
glutIdleFunc(spincube);
}
if(key=='9'&&rotationcomplete==1)
{
r=r+2.0;
glutIdleFunc(spincube);
}
if(key=='1'&&rotationcomplete==1)
{
r=r-2.0;
glutIdleFunc(spincube);
}
if(key=='5'&&rotationcomplete==1)
{
p=0.0;
q=0.0;
r=0.0;
glutIdleFunc(spincube);
}
if(key=='m'&&rotationcomplete==1)
{
if(speed<=1.3)
{
//for(speed=0;speed<1.3;speed++)
speed=speed+0.3;
speedmetercolor[++speedmetercount]=3;
}
glutPostRedisplay();
}
if(key=='m'&&rotationcomplete==1)
{
if(speed>1.3)
{ if(speed<=2.9)
{
//for(speed=0;speed<1.3;speed++)
speed=speed+0.3;
speedmetercolor[++speedmetercount]=4;
}
}
glutPostRedisplay();
}
if(key=='m'&&rotationcomplete==1)
{
if(speed>2.9)
{
if(speed<=4.2)
{
//r(speed=0;speed<=4.3;speed+=0.1)
//{
speed=speed+0.3;
speedmetercolor[++speedmetercount]=5;
}
}
glutPostRedisplay();
}
if(key=='n'&&rotationcomplete==1)
{
if(speed>=0.3)
{
speed=speed-0.3;
speedmetercolor[speedmetercount--]=0;
}
glutPostRedisplay();
}
if(key=='o'&&rotationcomplete==1)
{
rotationcomplete=0;
if(count>=0)
{
if(solve[count]<0)
{
rotation=-1*solve[count];
inverse=0;
glutIdleFunc(spincube);
}
if(solve[count]>0)
{
rotation=solve[count];
inverse=1;
glutIdleFunc(spincube);
}
count--;
}
glutIdleFunc(spincube);
}
}
void myreshape(int w,int h)
{
glViewport(0,0,w,h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if (w <= h)
glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w, 10.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
else
glOrtho(-10.0*(GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-10.0,10.0);
glMatrixMode(GL_MODELVIEW);
}
void mymenu(int id)
{
if(rotationcomplete==1)
{rotationcomplete=0;
switch(id)
{
case 1:
rotation=1;
inverse=0;
solve[++count]=1;
glutIdleFunc(spincube);
break;
case 2:
rotation=1;
inverse=1;
solve[++count]=-1;
glutIdleFunc(spincube);
break;
case 3:
rotation=2;
inverse=0;
solve[++count]=2;
glutIdleFunc(spincube);
break;
case 4:
rotation=2;
inverse=1;
solve[++count]=-2;
glutIdleFunc(spincube);
break;
case 5:
rotation=3;
inverse=0;
solve[++count]=3;
glutIdleFunc(spincube);
break;
case 6:
rotation=3;
inverse=1;
solve[++count]=-3;
glutIdleFunc(spincube);
break;
case 7:
rotation=4;
inverse=0;
solve[++count]=4;
glutIdleFunc(spincube);
break;
case 8:
rotation=4;
inverse=1;
solve[++count]=-4;
glutIdleFunc(spincube);
break;
case 9:
rotation=5;
inverse=0;
solve[++count]=5;
glutIdleFunc(spincube);
break;
case 10:
rotation=5;
inverse=1;
solve[++count]=-5;
glutIdleFunc(spincube);
break;
case 11:
rotation=6;
inverse=0;
solve[++count]=6;
glutIdleFunc(spincube);
break;
case 12:
rotation=6;
inverse=1;
solve[++count]=-6;
glutIdleFunc(spincube);
break;
case 13:
exit(0);
break;
}
}
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (500, 500);
glutCreateWindow ("RUBIK'S CUBE");
glutReshapeFunc (myreshape);
glutIdleFunc(spincube);
glutMouseFunc(mouse);
glutMotionFunc(motion);
glutCreateMenu(mymenu);
glutAddMenuEntry("Top :a",1);
glutAddMenuEntry("Top Inverted :q",2);
glutAddMenuEntry("Right :s",3);
glutAddMenuEntry("Right Inverted :w",4);
glutAddMenuEntry("Front :d",5);
glutAddMenuEntry("Front Inverted :e",6);
glutAddMenuEntry("Left :f",7);
glutAddMenuEntry("Left Inverted :r",8);
glutAddMenuEntry("Back :g",9);
glutAddMenuEntry("Back Inverted :t",10);
glutAddMenuEntry("Bottom :h",11);
glutAddMenuEntry("Bottom Inverted :y",12);
glutAddMenuEntry("Exit",13);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutKeyboardFunc(keyboard);
glutDisplayFunc (display);
glEnable(GL_DEPTH_TEST);
glutMainLoop();
//return 0;
}


#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

GLfloat xRotated,yRotated,zRotated;

GLdouble radius=0.2;
GLdouble fallOverX = -2.5;
GLdouble fallOverY = 1.0;

GLdouble nextFallOverX = 0;
GLdouble nextFallOverY = -1.5;
GLdouble leftEndX = -3.5;
GLdouble rightEndX = 0;
GLdouble topY = 1;
GLdouble bottomY = -2.0;
GLdouble circleX = 0;
GLdouble circleY = 0;
GLdouble circleZ = -6.0;
double sin45 = 0.85090352453;

int fallOver = 0;
int hitBottom = 0;
int keyPressed = 0;
int bounceTimer = 0;
int theEnd = 0;

void display(void);
void reshape(int x,int y);
void keypressfunction();
void drawCircle();
void update(int value);
void idleFunc(void)
{
    zRotated -=1.8;
    yRotated +=2.8;
    xRotated +=2.8;
    display();
}
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}



void init() {
    
    //initailize ball position
    circleX =  fallOverX - radius;
    circleY = fallOverY + radius;
    
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    
    glEnable(GL_LIGHTING);                // so the renderer considers light
    glEnable(GL_LIGHT0);                  // turn LIGHT0 on
    glEnable(GL_DEPTH_TEST);              // so the renderer considers depth
}


int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1240, 780);
    
    glutCreateWindow("solid sphere");
    initGL();
    //initLighting();
    init();
    xRotated=yRotated=zRotated=0.0;
    glutIdleFunc(idleFunc);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keypressfunction);
    //    glutTimerFunc(100,update,0);
    glutMainLoop();
    return 0;
}

void drawCircle(){
    
    glPushMatrix();
    
    glTranslatef(circleX,circleY,circleZ);
    if(keyPressed == 1 && theEnd == 0){
        glRotatef(zRotated,0.0,0.0,2.0);
    }
    glScalef(1.0,1.0,1.0);
    glutSolidSphere(radius, 30, 30);
    
    glPopMatrix();
    
}

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //glColor3d(1,0,0);
    drawCircle();
    
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.8, 1.0, 1.0);
    glTranslated(0.0,0.0,0);
    glBegin(GL_POLYGON);
    
    glVertex3f(leftEndX, bottomY,-6.0);
    glVertex3f(nextFallOverX, bottomY,-6.0);
    glVertex3f(nextFallOverX, nextFallOverY,-6.0);
    glVertex3f(fallOverX, fallOverY,-6.0);
    glVertex3f(leftEndX, topY,-6.0);
    
    glEnd();
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void keypressfunction(void){
    keyPressed = 1;
    glutTimerFunc(15,update,0);
}
double maximumHeight = 0;
int direction = 1;

void update(int value)
{
    if(bounceTimer < 4    ){
        if(hitBottom == 0  && (circleY-radius) > bottomY){
            if( (circleX+radius) <= fallOverX){
                circleX += radius+(sin45/10) ;
                circleY = circleY;
            }
            else{
                fallOver = 1;
                circleX += (radius*(sin45));
                circleY -= (radius*(sin45));
            }
            
        }else{
            if(hitBottom == 0){
                circleY = bottomY+radius;
                hitBottom = 1;
            }else{
                
                
                circleY += direction * (0.3/(bounceTimer+1));
                circleX +=  0.03;
                if ((circleY+radius) > maximumHeight) {
                    circleY = maximumHeight-radius;
                    direction = -1;
                    bounceTimer += 1;

                    
                } else if ((circleY-radius) < bottomY) {
                    direction = 1;
                    maximumHeight -= radius;
                }
            }
        }
    }else{
        circleY = bottomY+radius;
        theEnd = 1;
    }
    glutPostRedisplay();
    glLoadIdentity();
    glutTimerFunc(15,update,0);
}

void reshape(int x,int y)
{
    if(y == 0||x == 0)
        return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}



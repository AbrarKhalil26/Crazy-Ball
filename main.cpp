#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include<cmath>

using namespace std;

ofstream ofile;
ifstream ifile;

int moveBallX = 100,moveBallY = 190;
float score = 0.0;
float moveEnemy = 0.2;

void bg(int x1,int y1,int z1,int x2,int y2,int z2);
void ball(float x,float y,float z);
void Lines(float b1);
void basket(float x1,float y1,float z1);
void enemy();
void Lose();void Win();


float EnemyX1 = 10,EnemyY1 = 155;
float EnemyX2 = 192,EnemyY2 = 95;
float LineOne_part1 = 40,LineOne_part3 = 70,LineOne_part2 = 55;
float LineTwo_part1 = 80,LineTwo_part3 = 110,LineTwo_part2 = 95;
float LineThree_part1 = 20,LineThree_part3 = 50,LineThree_part2 = 35;
float LineFour_part1 = 120,LineFour_part3 = 150,LineFour_part2 = 135;
float LineFive_part1 = 150,LineFive_part3 = 180,LineFive_part2 = 165;

bool status_LineOne = true;
bool status_LineTwo = false;
bool status_LineThree = true;
bool status_LineFour = false;
bool status_LineFive = true;
bool status_Enemy1 = false;
bool status_Enemy2 = false;

bool lose = false,win = false;
bool level1 = true,level2 = false, level3 = false;
//================================================================
//              Level 1
//================================================================

void Level1(){
    glClear(GL_COLOR_BUFFER_BIT);

    float b1 = 0.1;
    bg(105, 185, 199,181, 112,35);
    ball(0.6 , 0.0 , 0.0);
    //Lines(b1);
    basket(0.6 , 0.0 , 0.0);
    Lose();
    Win();

    if (lose){
        ofile.open("score.dat",ios::trunc);
        ofile<<score<<endl;
        ofile.close();
        ifile.open("score.dat",ios::in);
        char a[4];
        ifile>>a;
        cout<<a;
        char text[50]= "Your score : ";
        strcat(text,a);
        MessageBox(NULL,text,"Game Over",0);
        exit(0);
    }
    if(win){
        level1 = false;
        level2 = true;
        level3 = false;
        win = false;
        moveBallX = 100,moveBallY = 190;
    }
    else{
        Lines(b1);
    }
    glFlush();
    glutSwapBuffers();


}
//================================================================
//              Level 2
//================================================================

void Level2(){
    glClear(GL_COLOR_BUFFER_BIT);

    float b1 = 0.2;
    bg(255, 178, 102,255, 255,153);
    ball(0.6 , 0.6 , 0.0);
    Lines(b1);
    basket(0.6 , 0.6 , 0.0);
    Lose();
    Win();

    if (lose){
        ofile.open("score.dat",ios::trunc);
        ofile<<score<<endl;
        ofile.close();
        ifile.open("score.dat",ios::in);
        char a[4];
        ifile>>a;
        cout<<a;
        char text[50]= "Your score : ";
        strcat(text,a);
        MessageBox(NULL,text,"Game Over",0);
        exit(0);
    }
    if(win){
        win = false;
        level2 = false;
        level3 = true;
        moveBallX = 100,moveBallY = 190;
    }
    glFlush();
    glutSwapBuffers();

}
//================================================================
//              Level 3
//================================================================

void Level3(){
    glClear(GL_COLOR_BUFFER_BIT);


    EnemyX1 = 10,EnemyY1 = 155;
    EnemyX2 = 192,EnemyY2 = 95;

    float b1 = 0.3;
    bg(255, 255, 204,204, 255,255);
    ball(0.0 , 0.0 , 0.8);
    Lines(b1);
    basket(0.0 , 0.0 , 0.8);
    enemy();

    Lose();
    Win();

    if (lose){
        ofile.open("score.dat",ios::trunc);
        ofile<<score<<endl;
        ofile.close();
        ifile.open("score.dat",ios::in);
        char a[4];
        ifile>>a;
        cout<<a;
        char text[50]= "Your score : ";
        strcat(text,a);
        MessageBox(NULL,text,"Game Over",0);
        exit(0);
    }
    if(win){
        win = false;
        level2 = false;
        level3 = false;
        ofile.open("score.dat",ios::trunc);
        ofile<<score<<endl;
        ofile.close();
        ifile.open("score.dat",ios::in);
        char a[10];
        ifile>>a;
        cout<<a;
        char text[50]= "Your score : ";
        strcat(text,a);
        MessageBox(NULL,text,"You Win",0);
    }
    glFlush();
    glutSwapBuffers();

}

//================================================================
//              Background
//================================================================

void bg(int x1,int y1,int z1,int x2,int y2,int z2){

    glBegin(GL_QUADS);
    glColor3f(1, 1,1);

        glVertex2f(0, 25);
        glColor3ub(x1, y1, z1);//blue sky
        glVertex2f(0, 200);
        glVertex2f(200, 200);
        glColor3f(1, 1,1);
        glVertex2f(200, 25);
        glClear( GL_COLOR_BUFFER_BIT);
        glColor3ub(x2, y2,z2);// floor
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(200, 0);
        glColor3f(1, 1,1);
        glVertex2f(200, 25);
        glColor3f(1, 1,1);
        glVertex2f(0, 25);

    glEnd();

}

//================================================================
//              Ball
//================================================================

void ball(float x,float y,float z){

    glColor3f(0.0 , 0.0 , 0.0);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(45);
    glBegin(GL_POINTS);
    glVertex2f(moveBallX,moveBallY);
    glEnd();


    glEnable(GL_POINT_SMOOTH);
    glPointSize(40);
    glBegin(GL_POINTS);
    glColor3f(x ,y, z);
    glVertex2f(moveBallX,moveBallY);
    glEnd();
}

//================================================================
//              Enemy
//================================================================

void enemy(){
    // Enemy 1
    if(EnemyX1 + 8 < 200){
        EnemyX1 += moveEnemy;
    }
    else if(EnemyX1 + 8 > 200){
        EnemyX1 = 8;
    }
    glColor3f(0.0 , 0.0 , 0.0);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(45);
    glBegin(GL_POINTS);
    glVertex2f(EnemyX1,EnemyY1);
    glEnd();
    //------------------------------------------
    // Enemy 2
    if(EnemyX2 + 8 > 0){
        EnemyX2 -= moveEnemy;
    }
    else if(EnemyX2 + 8 < 200){
        EnemyX2 = 192;
    }
    glColor3f(0.0 , 0.0 , 0.0);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(45);
    glBegin(GL_POINTS);
    glVertex2f(EnemyX2,EnemyY2);
    glEnd();

    //cout << "Ball x = " << int(moveBallX) << endl;
    //cout << "Ball y = " << int(moveBallY) << endl;
    //cout << "enemy x = " << int(EnemyX) << endl;
    //cout << "enemy y = " << int(EnemyY) << endl;

}

//================================================================
//              LineFun
//================================================================

void LineFun(int x1,int y1,int x2,int y2){
    glLineWidth(5);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
}
//================================================================
//              OvalFun
//================================================================
void OvalFun(float x,float y){
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glColor3f (0.0 , 0.0 , 0.0);

    float r = 5;
    double pi = 22/7.0;

    for(float i=0;i<=2*pi;i+=pi/360)
        glVertex2f(x+sin(i)*(3.2*r),y+cos(i)*r);

    glEnd();
}
//================================================================
//              Lines
//================================================================
void lineOne(float b1){
    if(int( LineOne_part2 + 17.0) == 200) status_LineOne = true;
    else if(int (LineOne_part2 - 17.0) == 0) status_LineOne = false;

    if(!status_LineOne){
        LineOne_part1 += b1;
        LineOne_part2 += b1;
        LineOne_part3 += b1;
    }
     else{
        LineOne_part1 -= b1;
        LineOne_part2 -= b1;
        LineOne_part3 -= b1;
    }

    LineFun(0,170,LineOne_part1,170);
    OvalFun(LineOne_part2,170);
    LineFun(LineOne_part3,170,200,170);
}

//================================================================
void lineTwo(float b1){

    if(int( LineTwo_part2 + 17.0) == 200) status_LineTwo = true;
    else if(int (LineTwo_part2 - 17.0) == 0) status_LineTwo = false;

    if(!status_LineTwo){
        LineTwo_part1 += b1;
        LineTwo_part2 += b1;
        LineTwo_part3 += b1;
    }
     else{
        LineTwo_part1 -= b1;
        LineTwo_part2 -= b1;
        LineTwo_part3 -= b1;
    }

    LineFun(0,140,LineTwo_part1,140);
    OvalFun(LineTwo_part2,140);
    LineFun(LineTwo_part3,140,200,140);
}
//================================================================
void lineThree(float b1){
    if(int( LineThree_part2 + 17.0) == 200) status_LineThree = true;
    else if(int (LineThree_part2 - 17.0) == 0) status_LineThree = false;

    if(!status_LineThree){
        LineThree_part1 += b1;
        LineThree_part2 += b1;
        LineThree_part3 += b1;
    }
     else{
        LineThree_part1 -= b1;
        LineThree_part2 -= b1;
        LineThree_part3 -= b1;
    }


    LineFun(0,110,LineThree_part1,110);
    OvalFun(LineThree_part2,110);
    LineFun(LineThree_part3,110,200,110);
}
//================================================================
void lineFour(float b1){
    if(int( LineFour_part2 + 17.0) == 200) status_LineFour = true;
    else if(int (LineFour_part2 - 17.0) == 0) status_LineFour = false;

    if(!status_LineFour){
        LineFour_part1 += b1;
        LineFour_part2 += b1;
        LineFour_part3 += b1;
    }
     else{
        LineFour_part1 -= b1;
        LineFour_part2 -= b1;
        LineFour_part3 -= b1;
    }

    LineFun(0,80,LineFour_part1,80);
    OvalFun(LineFour_part2,80);
    LineFun(LineFour_part3,80,200,80);
}
//================================================================
void lineFive(float b1){
    if(int( LineFive_part2 + 17.0) == 200) status_LineFive = true;
    else if(int (LineFive_part2 - 17.0) == 0) status_LineFive = false;

    if(!status_LineFive){
        LineFive_part1 += b1;
        LineFive_part2 += b1;
        LineFive_part3 += b1;
    }
     else{
        LineFive_part1 -= b1;
        LineFive_part2 -= b1;
        LineFive_part3 -= b1;
    }

    LineFun(0,50,LineFive_part1,50);
    OvalFun(LineFive_part2,50);
    LineFun(LineFive_part3,50,200,50);
}
//================================================================
//              Five Lines Funs
//================================================================
void Lines(float b1){
    lineOne(b1);
    lineTwo(b1);
    lineThree(b1);
    lineFour(b1);
    lineFive(b1);
    //glutPostRedisplay();
}

//================================================================
//              Basket
//================================================================
void basket(float x1,float y1,float z1){
    // Left side
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(10,25);
        glVertex2f(5,20);
        glVertex2f(5,5);
        glVertex2f(10,10);
    glEnd();

    // behind
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(45,10);
        glVertex2f(45,25);
        glVertex2f(10,25);
        glVertex2f(10,10);
    glEnd();

    // Right Side
    glColor3f(x1,y1,z1);
    glBegin(GL_POLYGON);
        glVertex2f(40,5);
        glVertex2f(45,10);
        glVertex2f(45,25);
        glVertex2f(40,20);
    glEnd();

    // Front
    glColor3f(x1,y1,z1);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(40,5);
        glVertex2f(40,20);
        glVertex2f(5,20);
        glVertex2f(5,5);
    glEnd();

}
//================================================================
//              Loss
//================================================================

void Lose(){

    switch(moveBallY){
        case 177:
            if((moveBallX >= 0 && moveBallX <= LineOne_part1) ||
               (moveBallX >= LineOne_part3 && moveBallX <= 200)){
                lose = true;
                cout << "LOSE Line 1\n";
            }
            break;
        case 147:
            if((moveBallX >= 0 && moveBallX <= LineTwo_part1) ||
               (moveBallX >= LineTwo_part3 && moveBallX <= 200)){
                lose = true;
                cout << "LOSE Line 2\n";
            }
            break;
        case 117:
            if((moveBallX >= 0 && moveBallX <= LineThree_part1) ||
               (moveBallX >= LineThree_part3 && moveBallX <= 200)){
                lose = true;
                cout << "LOSE Line 3\n";
            }
            break;
        case 87:
            if((moveBallX >= 0 && moveBallX <= LineFour_part1) ||
               (moveBallX >= LineFour_part3 && moveBallX <= 200)){
                lose = true;
                cout << "LOSE Line 4\n";
            }
            break;
        case 57:
            if((moveBallX >= 0 && moveBallX <= LineFive_part1) ||
               (moveBallX >= LineFive_part3 && moveBallX <= 200)){
                lose = true;
                cout << "LOSE Line 5\n";
            }
            break;
        case 14:
            if((moveBallX >= 50 && moveBallX <= 200)){
                lose = true;
                cout << "LOSE END\n";
            }
            break;

    }
    // Enemy 1
    if(moveBallY <= 169 && moveBallY >= 141){
        if((int(EnemyX1) + 7 == int (moveBallX) - 7) || (int(EnemyX1) - 7 == int(moveBallX) + 7)){
            lose = true;
            cout << "LOSE Enemy\n" << endl;
        }
    }
    // Enemy 2
    if(moveBallY <= 109 && moveBallY >= 81){
        if((int(EnemyX1) + 7 == int (moveBallX) - 7) || (int(EnemyX1) - 7 == int(moveBallX) + 7)){
            lose = true;
            cout << "LOSE Enemy\n" << endl;
        }
    }

}
//================================================================
//              Win
//================================================================

void Win(){
    if(moveBallY >= 10 && moveBallY <= 20){
        if (moveBallX >= 7 && moveBallX <= 35)
            win = true;
    }
}

//================================================================
//              Animation
//================================================================
void Special_Keys(int key, int x, int y)
{
	switch (key)
	{
        case GLUT_KEY_LEFT:
            if(moveBallX > 8.0) --moveBallX;
            break;
        case GLUT_KEY_RIGHT:
            if(moveBallX < 192.0) ++moveBallX;
            break;
        case GLUT_KEY_DOWN:
            if(moveBallY > 15.0) --moveBallY,score += 0.5;
            break;
        case GLUT_KEY_UP:
            if(moveBallY < 192.0) ++moveBallY;
            break;
	}
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (btn == GLUT_LEFT_BUTTON)
			cout << "Click\n";
		else
			cout << "not Click\n";

	}
}
//================================================================
//              General
//================================================================
void Draw(){
    if(level1){
        Level1();
        cout << "Level 1\n";
    }
    if(level2){
        Level2();
        cout << "Level 2\n";
    }
    if(level3){
        Level3();
        cout << "Level 3\n";
    }
    //glutIdleFunc(Lines);
}

void intinlize(){
  glClearColor(0 , 0 , 0 , 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0 , 200 , 0 , 200);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(600 , 600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("project");
    glutMouseFunc(mouse);
    glutSpecialFunc(Special_Keys);
    intinlize();
    glutDisplayFunc(Draw);
    //glutIdleFunc(Draw);
    glutMainLoop();

    return EXIT_SUCCESS;
}

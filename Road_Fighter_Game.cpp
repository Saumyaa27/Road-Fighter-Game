#include<GL/glut.h>
#include<iostream>//for strlen
#include<stdlib.h>
#include<cstring>
#include<windows.h>
#include <stdio.h>
using namespace std;

int i, q;
int score = 0;//for score counting
static int highest_score = 0;
int screen = 0;
bool collide = false;//check if car collide to make game over
char buffer[10];
int start = 0;
int gv = 0;
int vehicleX = 400, vehicleY = 70;
int x_opposition[4], y_opposition[4];
int y_divider = 4, divider;
bool game_over = false;
int x_divider[2] = { 325,475 };
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

bool left_check = 0, right_check = 0;

int max_count = 9, offset = 15;
int count_check = max_count;
int lives = 3;

void move() {
	if (left_check == 1 && count_check != 0) {
		vehicleX -= offset;
		count_check--;
		if (count_check == 0) {
			left_check = 0;
			count_check = max_count;
		}
	}
	else if (right_check == 1 && count_check != 0) {
		vehicleX += offset;
		count_check--;
		if (count_check == 0) {
			right_check = 0;
			count_check = max_count;
		}
	}
}



void Text(char ch[], int xpos, int ypos)//draw the text for score and game over
{
	int numofchar = strlen(ch);
	glLoadIdentity();
	glRasterPos2f(xpos, ypos);
	for (i = 0; i <= numofchar - 1; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
	}
}


void Num(char ch[], int numtext, int xpos, int ypos)//counting the score
{
	int len;
	int k;
	k = 0;
	len = numtext - strlen(ch);
	glLoadIdentity();
	glRasterPos2f(xpos, ypos);
	for (i = 0; i <= numtext - 1; i++)
	{
		if (i < len)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
			k++;
		}

	}
}


void otherV_pos()
{
	//glClearColor(0, 0, 1, 0);
	for (i = 0; i < 4; i++)
	{
		if (rand() % 3 == 0)
		{
			x_opposition[i] = 250;
		}
		else if (rand() % 3 == 1)
		{
			x_opposition[i] = 400;
		}
		else
		{
			x_opposition[i] = 550;
		}
		y_opposition[i] = 1000 - i * 200;
	}
}

void initialize(int life, int s) {
	vehicleX = 400;
	vehicleY = 70;
	left_check = 0;
	right_check = 0;
	count_check = max_count;
	lives = life;
	score = s;
	otherV_pos();
}

void drawTree(int x, int y)
{
	int newx = x;
	int newy = y;
	//Bottom
	glColor3f(0.871, 0.722, 0.529);
	glBegin(GL_POLYGON);
	glVertex2f(newx - 5, newy);
	glVertex2f(newx - 5, newy + 55);
	glVertex2f(newx + 5, newy + 55);
	glVertex2f(newx + 5, newy);
	glEnd();
	//Top-Bottom
	glColor3f(0.133, 0.545, 0.133);
	glBegin(GL_TRIANGLES);
	glVertex2f(newx - 35, newy + 55 - 5);
	glVertex2f(newx, newy + 55 + 35);
	glVertex2f(newx + 35, newy + 55 - 5);
	glEnd();
	//Top
	glColor3f(0.133, 0.545, 0.133);
	glBegin(GL_TRIANGLES);
	glVertex2f(newx - 25, newy + 55 + 25);
	glVertex2f(newx, newy + 55 + 50);
	glVertex2f(newx + 25, newy + 55 + 25);
	glEnd();
}

void positionTrees() {
	//Left side
	drawTree(95, 15);
	drawTree(135, 35);
	drawTree(45, 200);
	drawTree(65, 140);
	drawTree(100, 160);
	drawTree(135, 300);
	drawTree(50, 340);
	drawTree(100, 380);

	//Right side
	drawTree(705, 15);
	drawTree(665, 35);
	drawTree(725, 200);
	drawTree(735, 140);
	drawTree(700, 160);
	drawTree(665, 300);
	drawTree(750, 340);
	drawTree(700, 380);
}


void drawRoad()
{
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(400 - 225, 500);
	glVertex2f(400 - 225, 0);
	glVertex2f(400 + 225, 0);
	glVertex2f(400 + 225, 500);
	glEnd();
}


void drawDivider()//white patch drawn in middle of road
{
	glLoadIdentity();
	glTranslatef(0, divider, 0);
	for (int k = 0; k < 2; k++) {
		for (i = 1; i <= 10; i++)
		{
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			glVertex2f(x_divider[k] - 5, y_divider * 15 * i + 18);
			glVertex2f(x_divider[k] - 5, y_divider * 15 * i - 18);
			glVertex2f(x_divider[k] + 5, y_divider * 15 * i - 18);
			glVertex2f(x_divider[k] + 5, y_divider * 15 * i + 18);
			glEnd();
		}
	}

	glLoadIdentity();
}


void drawWindow(int x, int y) {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + 20, y);
	glVertex2f(x + 20, y + 20);
	glVertex2f(x, y + 20);
	glEnd();
}

void drawBuilding(int x, int y) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + 50, y);
	glVertex2f(x + 50, y + 150);
	glVertex2f(x, y + 150);
	glEnd();

	drawWindow(x, y + 30);
	drawWindow(x + 20, y + 70);
	drawWindow(x, y + 110);
}

void drawVehicle()//car for racing
{
	glPointSize(10.0);
	glBegin(GL_POINTS);//tire
	glColor3f(0, 0, 0);
	glVertex2f(vehicleX - 20, vehicleY + 16);
	glVertex2f(vehicleX + 20, vehicleY + 16);
	glVertex2f(vehicleX - 20, vehicleY - 16);
	glVertex2f(vehicleX + 20, vehicleY - 16);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);//middle body
	glVertex2f(vehicleX - 20, vehicleY + 35);
	glVertex2f(vehicleX - 20, vehicleY - 35);
	glVertex2f(vehicleX + 20, vehicleY - 35);
	glVertex2f(vehicleX + 20, vehicleY + 35);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);//sunroof
	glVertex2f(vehicleX - 12, vehicleY + 10);
	glVertex2f(vehicleX - 12, vehicleY - 10);
	glVertex2f(vehicleX + 12, vehicleY - 10);
	glVertex2f(vehicleX + 12, vehicleY + 10);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);//down body
	glVertex2f(vehicleX - 20, vehicleY - 35);
	glVertex2f(vehicleX - 10, vehicleY - 45);
	glVertex2f(vehicleX + 10, vehicleY - 45);
	glVertex2f(vehicleX + 20, vehicleY - 35);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);//up body
	glVertex2f(vehicleX - 20, vehicleY + 35);
	glVertex2f(vehicleX - 10, vehicleY + 45);
	glVertex2f(vehicleX + 10, vehicleY + 45);
	glVertex2f(vehicleX + 20, vehicleY + 35);
	glEnd();

}

void drawotherV_(float cr1, float cg1, float cb1, float cr2, float cg2, float cb2)//other cars
{

	for (i = 0; i < 4; i++)
	{
		glPointSize(10.0);
		glBegin(GL_POINTS);//tire
		glColor3f(0, 0, 0);
		glVertex2f(x_opposition[i] - 20, y_opposition[i] + 16);
		glVertex2f(x_opposition[i] + 20, y_opposition[i] + 16);
		glVertex2f(x_opposition[i] - 20, y_opposition[i] - 16);
		glVertex2f(x_opposition[i] + 20, y_opposition[i] - 16);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(cr1, cg1, cb1);//middle body
		glVertex2f(x_opposition[i] - 20, y_opposition[i] + 35);
		glVertex2f(x_opposition[i] - 20, y_opposition[i] - 35);
		glVertex2f(x_opposition[i] + 20, y_opposition[i] - 35);
		glVertex2f(x_opposition[i] + 20, y_opposition[i] + 35);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(cr2, cg2, cb2);//sunroof
		glVertex2f(x_opposition[i] - 12, y_opposition[i] + 10);
		glVertex2f(x_opposition[i] - 12, y_opposition[i] - 10);
		glVertex2f(x_opposition[i] + 12, y_opposition[i] - 10);
		glVertex2f(x_opposition[i] + 12, y_opposition[i] + 10);
		glEnd();

		glBegin(GL_QUADS);//up body
		glColor3f(cr2, cg2, cb2);
		glVertex2f(x_opposition[i] - 20, y_opposition[i] + 35);
		glVertex2f(x_opposition[i] - 10, y_opposition[i] + 45);
		glVertex2f(x_opposition[i] + 10, y_opposition[i] + 45);
		glVertex2f(x_opposition[i] + 20, y_opposition[i] + 35);
		glEnd();

		glBegin(GL_QUADS);//down body
		glColor3f(cr2, cg2, cb2);
		glVertex2f(x_opposition[i] - 20, y_opposition[i] - 35);
		glVertex2f(x_opposition[i] - 10, y_opposition[i] - 45);
		glVertex2f(x_opposition[i] + 10, y_opposition[i] - 45);
		glVertex2f(x_opposition[i] + 20, y_opposition[i] - 35);
		glEnd();

		y_opposition[i] = y_opposition[i] - 8;

		if (abs(y_opposition[i] - vehicleY) < 90)
		{
			if (abs(x_opposition[i] - vehicleX) < 50)
				collide = true;
		}

		if (y_opposition[i] < -25)
		{
			if (rand() % 3 == 0)
			{
				x_opposition[i] = 250;
			}
			else if (rand() % 3 == 1)
			{
				x_opposition[i] = 400;
			}
			else
			{
				x_opposition[i] = 550;
			}
			y_opposition[i] = 700;
		}
	}
}

void Specialkey(int key, int x, int y)//allow to use navigation key for movement of car
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (vehicleX != 250 && left_check == 0 && right_check == 0) {
			vehicleX -= offset;
			left_check = true;
		}

		break;
	case GLUT_KEY_RIGHT:
		if (vehicleX != 550 && left_check == 0 && right_check == 0) {
			vehicleX += offset;
			right_check = true;
		}
		break;
	}
	glutPostRedisplay();
}

void Normalkey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		if (game_over == 1) {
			game_over = 0;
			otherV_pos();
		}
		else if (start == 0) {
			start = 1;
		}
		break;
	case 27:exit(0);
	}
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}


void first_design() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1);
	positionTrees();
	drawRoad();
	drawDivider();
	drawVehicle();

	glColor3f(1.000, 1.000, 0.000);
	char heading[] = "Road Fighter Game ";
	Text(heading, 300, 400);

	glColor3f(0.000, 1.000, 0.000);
	char st[] = "Press SPACE to START";
	Text(st, 300, 310);

	glColor3f(1.000, 0.000, 0.000);
	char Rule[] = "RULES:";
	Text(Rule, 300, 260);

	glColor3f(0.000, 1.000, 1.000);
	char Rule2[] = "LEFT_ARROW_KEY  : to move left";
	char Rule3[] = "RIGHT_ARROW_KEY : to move right";

	Text(Rule2, 300, 210);
	Text(Rule3, 300, 190);
	glutSwapBuffers();
}

void game_end() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1);
	vehicleX = 400, vehicleY = 70;
	glColor3f(1.000, 1.000, 0.000);
	if (score > highest_score)
		highest_score = score;
	char over[] = " GAME OVER ";
	Text(over, 300, 400);
	char st[] = "Press SPACE to START";
	Text(st, 250, 250);
	char hs[] = "Your highest score is: ";
	Text(hs, 250, 350);
	_itoa_s(highest_score, buffer, 10);
	Num(buffer, 6, 480, 350);
	char sc[] = "Your score is: ";
	Text(sc, 250, 300);
	_itoa_s(score, buffer, 10);
	Num(buffer, 6, 420, 300);
	glutSwapBuffers();
}

void secondDesign() {
	move();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1);
	//Road BackGround
	glColor3f(0.4314, 0.1725, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(800, 0);
	glColor3f(0.9216, 0.5961, 0.3059);
	glVertex2f(800, 300);
	glVertex2f(0, 300);
	glEnd();

	//Road Sky
	glColor3f(0.000, 0.60, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(800, 500);
	glVertex2f(0, 500);
	glColor3f(0.933, 0.933, 0.933);
	glVertex2f(0, 300);
	glVertex2f(800, 300);
	glEnd();

	//Left side
	drawBuilding(0, 250);
	drawBuilding(55, 280);
	drawBuilding(110, 250);

	//Right side
	drawBuilding(750, 250);
	drawBuilding(695, 280);
	drawBuilding(640, 250);

	drawRoad();
	drawDivider();
	drawVehicle();
	drawotherV_(0.5, 0, 0.5, 0, 0, 0);
	divider = divider - 16;
	if (divider < -60)
	{
		divider = 0;
	}
	score = score + 1;
	glColor3f(1, 1, 1);
	char score_text[] = "Score: ";
	Text(score_text, 660, 455);
	_itoa_s(score, buffer, 10);
	Num(buffer, 6, 720, 455);

	char lives_ch[] = { lives + '0','\n' };
	char live_text[] = "Lives: ";
	Text(live_text, 660, 485);
	Num(lives_ch, 6, 720, 485);
	glutSwapBuffers();
	for (q = 0; q <= 10000000; q++) { ; }
	if (collide == true)
	{
		lives--;
		if (lives == 0) {
			start = 0;
			game_over = true;
			glutSwapBuffers();
		}
		initialize(lives, score);
		collide = 0;
	}
}

void startGame()
{
	move();
	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	//Road BackGround
	glColor3f(0.4314, 0.1725, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(800, 0);
	glColor3f(0.9216, 0.5961, 0.3059);
	glVertex2f(800, 500);
	glVertex2f(0, 500);
	glEnd();
	positionTrees();
	drawRoad();
	drawDivider();
	drawVehicle();
	drawotherV_(0, 0, 1, 0, 1, 1);
	divider = divider - 16;
	if (divider < -60)
	{
		divider = 0;
	}
	score = score + 1;
	glColor3f(1, 1, 1);
	char score_text[] = "Score: ";
	Text(score_text, 660, 455);
	_itoa_s(score, buffer, 10);
	Num(buffer, 6, 720, 455);

	char live_text[] = "Lives: ";
	char lives_ch[] = { lives + '0','\n' };
	Text(live_text, 660, 485);
	Num(lives_ch, 6, 720, 485);

	glutSwapBuffers();
	for (q = 0; q <= 10000000; q++) { ; }
	if (collide == true)
	{
		lives--;
		if (lives == 0) {
			start = 0;
			game_over = true;
			glutSwapBuffers();
		}
		initialize(lives, score);
		collide = 0;

	}
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (start == 1 && score <= 500) {
		glClearColor(0.000, 0.392, 0.000, 1);
		startGame();
	}
	else if (start == 1 && score > 500) {
		secondDesign();
	}
	else if (start == 0 && game_over == 1) {
		game_end();
	}
	else {
		initialize(3, 0);
		first_design();
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Road Fighter game");
	otherV_pos();
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(Specialkey);
	glutKeyboardFunc(Normalkey);
	glutIdleFunc(display);
	glutMainLoop();
}

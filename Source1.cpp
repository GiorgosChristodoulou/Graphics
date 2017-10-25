#include <GL/gl.h>     // openGL header
#include <GL/glu.h>   // glut header
#include <GL/glut.h>   // glut header
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string>






unsigned char r[1600], p[1600], s[1600],b[1600]; 
int FillGrid[12][15];
int Bombs[12][15];
int Btrue = 0;
int click = 1;
int bonusclick = 1;
int moves;
int innermoves = 0;
int second = 0;
int play = 0;
int showbombs = 0;


class scrPt {
public:
	GLint x, y;
};




//scale φαση
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          
static int g_Height = 520;

//scale φαση



int score = 0;

void changeSize(GLint width, GLint height) {

	g_Width = width;
	g_Height = height;
	
	glViewport(0, 0, g_Width, g_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective((float)g_Width / g_Height, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
	glMatrixMode(GL_MODELVIEW);
}






void FillInTheGrid() {
	srand(time(NULL));
	int randi, i, j;


//init and check for 3,4.. of the same kind before start.
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 15; j++) {
			randi = rand() % 5;
			
			FillGrid[i][j] = randi;
			if(j>=2){
				while ((FillGrid[i][j]== FillGrid[i][j-1])&& (FillGrid[i][j] == FillGrid[i][j - 2]) ){
					FillGrid[i][j] = rand() % 5;
				}
			}
			if (i >= 2) {
				while ((FillGrid[i][j] == FillGrid[i-1][j]) && (FillGrid[i][j] == FillGrid[i-2][j])) {
					FillGrid[i][j] = rand() % 5;
				}
				if (j >= 2) {
					while ((FillGrid[i][j] == FillGrid[i][j - 1]) && (FillGrid[i][j] == FillGrid[i][j - 2])) {
						FillGrid[i][j] = rand() % 5;
					}
				}
			}
		}
	}

//init and check for 3,4.. of the same kind before start.

//init the bomb table
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 15; j++) {
			randi = rand() % 10;
			if(randi>5){
				Bombs[i][j] =1;
				
			}
			else {
				Bombs[i][j] = 0;
			}
		}
	}
	
}


void renderBitmapString() {
	char c[50];
	char points[50];
	glRasterPos2i(-590, -500);
	glColor3i(1, 1, 1);

	if (play == 0) {
		sprintf(c, "press ESC for exit or b for restart.YOUR SCORE WAS:%d",score);
		const char* p = c;
		do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p); while (*(++p));
	}
	if(play==1){
		sprintf(points, "SCORE: %d" , score);
		const char* k = points;
		do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *k); while (*(++k));
	}
	
}

void display(void) {
		
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (Btrue == 0) {
			FillInTheGrid();
			
			
			
		}
		int i, j, k;
		



		glLineWidth(1);
		glColor3f(1.0, 1.0, 1.0);
	
		for (i = -480; i <= 0; i += 40) {
			glBegin(GL_LINES);
			glVertex3f(-600, i, 0);
			glVertex3f(0, i, 0);
			glEnd();
		}

	
		for (j = -600; j <= 0; j += 40) {
			glBegin(GL_LINES);
			glVertex3f(j, -480, 0);
			glVertex3f(j, 0, 0);
			glEnd();
		}
		glFlush(); 

		if (second == 1) {
			play = 0;
			renderBitmapString();
			second = 0;
		}
		if(play==1) {
			
			renderBitmapString();
		}
		if(Btrue==1){
			for (i = 0; i < 12; i++) {
				for (j = 0; j < 15; j++) {
					//			if blue
					if (FillGrid[i][j] == 0) {
						glColor3f(0.5,0.5,1);
						glBegin(GL_QUADS);
						glVertex2f(-40 * j, -40 * i);
						glVertex2f(-40 * j - 40, -40 * i);
						glVertex2f(-40 * j - 40, -40 * i - 40);
						glVertex2f(-40 * j, -40 * i - 40);

						glEnd();
					
					}
					//			if red
					if (FillGrid[i][j] == 1) {
						glColor3f(1, 1, 0);
						glBegin(GL_QUADS);
						glVertex2f(-40 * j, -40 * i);
						glVertex2f(-40 * j - 40, -40 * i);
						glVertex2f(-40 * j - 40, -40 * i - 40);
						glVertex2f(-40 * j, -40 * i - 40);

						glEnd();
					
					}
					//          if paper
					if (FillGrid[i][j] == 2) {
					
						glRasterPos2i(j * (-40) -40, i * (-40) -40);
					
						glDrawPixels(40, 40, GL_BLUE, GL_UNSIGNED_BYTE, p);
					

					}
					//          if scissors
					if (FillGrid[i][j] == 3) {
						glRasterPos2i(j * (-40) - 40, i * (-40) - 40);
						glDrawPixels(40, 40, GL_GREEN, GL_UNSIGNED_BYTE, s);

					}
					//			if rock
					if (FillGrid[i][j] == 4) {
						glRasterPos2i(j * (-40) - 40, i * (-40) - 40);
						glDrawPixels(40, 40, GL_RED, GL_UNSIGNED_BYTE, r);
					

					}
					if (FillGrid[i][j] == 5) {
						glColor3f(0, 0, 0);
						glBegin(GL_QUADS);
						glVertex2f(-40 * j, -40 * i);
						glVertex2f(-40 * j - 40, -40 * i);
						glVertex2f(-40 * j - 40, -40 * i - 40);
						glVertex2f(-40 * j, -40 * i - 40);

						glEnd();
						
					}

					if (showbombs == 1) {
						if (Bombs[i][j] == 0) {
							glColor3f(1, 1, 1);
							glBegin(GL_QUADS);
							glVertex2f(-40 * j, -40 * i);
							glVertex2f(-40 * j - 40, -40 * i);
							glVertex2f(-40 * j - 40, -40 * i - 40);
							glVertex2f(-40 * j, -40 * i - 40);

							glEnd();

						}

						if (Bombs[i][j] == 1) {
							glRasterPos2i(j * (-40) - 40, i * (-40) - 40);
							glDrawPixels(40, 40, GL_RED, GL_UNSIGNED_BYTE, b);

						}
					}
				}

			
			}

			glLineWidth(1);
			if (showbombs == 1){
				glColor3f(0, 0, 0);
			}
			else {
				glColor3f(0, 0, 0);
			}
			for (i = -480; i <= 0; i += 40) {
				glBegin(GL_LINES);
				glVertex3f(-600, i, 0);
				glVertex3f(0, i, 0);
				glEnd();
			}
			


			//glLineWidth(1);
			//glColor3f(0, 0, 0);
			for (j = -600; j <= 0; j += 40) {
				glBegin(GL_LINES);
				glVertex3f(j, -480, 0);
				glVertex3f(j, 0, 0);
				glEnd();
			}

		
			glFlush(); //Draw everything to the screen*/
		
		}
		
	
	
	
		
		glutSwapBuffers();
	

}





void slide() {
	int i,j,k,swap;
	for (i = 0; i < 12;i++) {
		for (j = 0; j < 15; j++) {
			if (FillGrid[i][j] == 5) {
				for (k = i; k > 0; k--) {
					
					swap = FillGrid[k][j];
					FillGrid[k][j] = FillGrid[k - 1][j];
					FillGrid[k - 1][j] = swap;
				}
			}
		}

	}
	glutPostRedisplay();
}

void ReFill() {
	srand(time(NULL));
	int randi, i, j;


	
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 15; j++) {

			randi = rand() % 5;

			
			if (FillGrid[i][j] == 5) {
				FillGrid[i][j] = randi;
			}
			
		}
	}
	glutPostRedisplay();

	
}

void aftermove() {
	int i,j,k;
	int spotter=1;
	int isTrue = 1;
	
	while(isTrue==1){
		isTrue = 0;
		for (i = 0; i < 12;i++){
			for (k = 1; k < 15; k++) {
				if (FillGrid[i][k] == FillGrid[i][k - 1]) {
					spotter += 1;


				}
				else {
					spotter = 1;
				}

				if (spotter == 3) {

			
					FillGrid[i][k] = 5;
					FillGrid[i][k - 1] = 5;
					FillGrid[i][k - 2] = 5;
					score += 6;
					isTrue =1;

					spotter = 1;
			
				}
			}
		}

		spotter = 1;
		for (j = 0; j < 15;j++){
			for (k = 1; k < 12; k++) {
				if (FillGrid[k][j] == FillGrid[k - 1][j]) {
					spotter += 1;


				}
				else {
					spotter = 1;
				}

				if (spotter == 3) {
		
					FillGrid[k][j] = 5;
					FillGrid[k - 1][j] = 5;
					FillGrid[k - 2][j] = 5;
					isTrue = 1;
					score += 6;
				
					spotter = 1;
			
			
				}
			}
		}
	
		slide();
		ReFill();
	}
}

void findWeakLines(int i, int j,int kind) {
	int beginI, endI, beginJ, endJ,k,m;
	score -= 6;
	
	if (i >= 3) {
		beginI = i - 3;
			if (i < 9) {
				endI = i + 3;
			
			}else if (i < 10) {
				endI = i + 2;
				
			}else if (i < 11) {
				endI = i + 1;
				
			}else if(i==11){
				endI = i;
				
			}
	}
	else if (i = 2) {
		beginI = i - 2;
		endI = i + 3;

	}else if (i = 1) {
		beginI = i - 1;
		endI = i + 3;

	}else if (i = 0) {
		beginI = i;
		endI = i + 3;
	}


	if (j >= 5) {
		beginJ = j - 5;
		if (j <= 11) {
			endJ = j + 3;
		}else if (j == 12) {
			endJ = j + 2;
		}else if (j == 13) {
			endJ = j + 1;
		}else if(j==14){
			endJ = j;
		}
	}else if(j==4){ 
		beginJ = j - 4;
		endJ = j + 3;
	}else if (j==3) {
		beginJ = j - 3;
		endJ = j + 3;
	}else if (j == 2) {
		beginJ = j - 2;
		endJ = j + 3;
	}
	
	
	
	for (k = beginI; k <= endI; k++) {
		for (m = beginJ; m <= endJ; m++) {
			
				
			if(kind!=2){    //if not paper
				if (FillGrid[k][m] == kind-1) {
					FillGrid[k][m] = 5;
					score += 2;
					
				}
			}
			else {       //if paper check for rock
				if (FillGrid[k][m] == kind +2) {
					FillGrid[k][m] = 5;
					score += 2;
				}
			}
		}
	}
	glutPostRedisplay();

	slide();
	ReFill();

}



void findWeakColumns(int i, int j, int kind) {
	int beginI, endI, beginJ, endJ, k, m;
	score -= 6;
	
	if (j >= 3) {
		beginJ = j - 3;
		if (j < 12) {
			endJ = j + 3;
			
		}
		else if (j < 13) {
			endJ = j + 2;
			
		}
		else if (j < 14) {
			endJ = j + 1;
			
		}
		else if (j == 14) {
			endJ = j;
			
		}
	}
	else if (j = 2) {
		beginJ =j - 2;
		endJ =j + 3;

	}
	else if (j = 1) {
		beginJ = j - 1;
		endJ = j + 3;

	}
	else if (j = 0) {
		beginI = j;
		endI =j + 3;
	}


	if (i >= 5) {
		beginI = i - 5;
		if (i <= 8) {
			endI= i + 3;
		}
		else if (i == 9) {
			endI = i + 2;
		}
		else if (i ==10) {
			endI = i + 1;
		}
		else if (i == 11) {
			endI = i;
		}
	}
	else if (i == 4) {
		beginI = i - 4;
		endI = i + 3;
	}
	else if (i == 3) {
		beginI = i - 3;
		endI = i + 3;
	}
	else if (i == 2) {
		beginI = i- 2;
		endI = i + 3;
	}


	
	for (k = beginI; k <= endI; k++) {
		for (m = beginJ; m <= endJ; m++) {


			if (kind != 2) {    //if not paper
				if (FillGrid[k][m] == kind - 1) {
					FillGrid[k][m] = 5;
					score += 2;
					if (Bombs[i][j] == 1) {
						score -= 30;
					}
				}
			}
			else {       //if paper check for rock
				if (FillGrid[k][m] == kind + 2) {
					FillGrid[k][m] = 5;
					score += 2;
					if (Bombs[i][j] == 1) {
						score -= 30;
					}
				}
			}
		}
	}
	glutPostRedisplay();

	slide();
	ReFill();
	
}



void move(int i,int j) {
	int spotter=1;
	int k;
	int kind;

	
	for (k = 1; k < 15; k++) {
		
			if (FillGrid[i][k] == FillGrid[i][k - 1]) {
				spotter += 1;
				

			}
			else {
				spotter = 1;
			}
			
			if(spotter==3){
				
				kind = FillGrid[i][k];
				FillGrid[i][k] = 5;
				FillGrid[i][k-1] =5;
				FillGrid[i][k-2] =5;
				score += 10;
				
				glutPostRedisplay();
				spotter = 1;
				
				if ((kind!=1)&&(kind!=0)&&(kind!=5)){
					findWeakLines(i,k,kind);
				}
			}
			
		
		
		
		
	}

	spotter = 1;
	for (k =1; k < 12; k++) {
		
			if (FillGrid[k][j] == FillGrid[k-1][j]) {
				spotter += 1;


			}
			else {
				spotter = 1;
			}

			if (spotter == 3) {
				kind = FillGrid[k][j];
				FillGrid[k][j] = 5;
				FillGrid[k-1][j] = 5;
				FillGrid[k-2][j] = 5;

				score += 10;
				glutPostRedisplay();
				spotter = 1;
				
				if ((kind != 1) && (kind != 0) && (kind != 5)) {
					findWeakColumns(k, j, kind);
				}
			}

		
		
			

	}

	
		aftermove();
}



void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) //<esc>
		exit(0);

	if (key == 98) { //<b>
		
		printf("give number of moves");
		scanf("%d", &moves);
		
		Btrue =1;
		glutPostRedisplay();
		
	}
}



void ChangeColour(scrPt endPt1, scrPt endPt2){
	int temp1, temp2, temp3, temp4,swap;
	



		temp1 = -(endPt2.y / 40);
		temp2 = -(endPt2.x / 40);
		temp3 = -(endPt1.y / 40);
		temp4 = -(endPt1.x / 40);

	if(temp1<12 && temp3 <12){	//check if player is out of bounds
		if ((temp1 == temp3 + 1 || temp1 == temp3 - 1)&& (temp2 == temp4)) {
			swap = FillGrid[temp1][temp2];
			FillGrid[temp1][temp2] = FillGrid[temp3][temp4];
			FillGrid[temp3][temp4] = swap;
		}

		if ((temp2 == temp4 + 1 || temp2 == temp4 - 1) && (temp1 == temp3)) {
			swap = FillGrid[temp1][temp2];
			FillGrid[temp1][temp2] = FillGrid[temp3][temp4];
			FillGrid[temp3][temp4] = swap;
		}

		
		
	}

	
	

	

	glutPostRedisplay();
	move(temp1, temp2);
	move(temp3, temp4);

	
	
	
}



void decide(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	static scrPt endPt1, endPt2;

	if (innermoves == moves) {
		Btrue = 0;
		innermoves = 0;
		second = 1;
		

	}
	
		if (click == 1) {
			if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
				endPt1.x = xMouse - 600;
				endPt1.y = -yMouse;
				click = 2;
				innermoves++;
				play = 1;
			}


		}
		else if (click == 2) {
			if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
				endPt2.x = xMouse - 600;
				endPt2.y = -yMouse;
				ChangeColour(endPt1, endPt2);
				click = 1;

			}

		}

		//bonus
		if (bonusclick == 1) {
			if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
				
				showbombs = 1;
				glutPostRedisplay();
				bonusclick = 2;
				
			}


		}
		else if (bonusclick == 2) {
			if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
				showbombs = 2;
				glutPostRedisplay();
				bonusclick = 1;
				
			}

		}
	
}


void init()
{
	glClearColor(0.0,0.0, 0.0, 0); //Define our background color
	gluOrtho2D(-600, 0, -520, 0); //(NEW) Define our viewing area
	
}



void ReadThePgms(){
	FILE *pgm1, *pgm2, *pgm3, *pgm4;
	int i,j;
	char str[100];   //για την fgets
				 //read the pgms
	pgm1 = fopen("rock.pgm", "r");
	pgm2 = fopen("paper.pgm", "r");
	pgm3 = fopen("scissors.pgm", "r");
	pgm4 = fopen("bomb.pgm", "r");
	if (pgm1 == NULL || pgm2 == NULL || pgm3 == NULL || pgm4 == NULL) {
		printf("reading ERROR");
		exit(0);
	}
	//after the 4th line
	for (i = 0; i < 4; i++) {
		fgets(str, 100, pgm1);
		fgets(str, 100, pgm2);
		fgets(str, 100, pgm3);
		fgets(str, 100, pgm4);
	}

	for (i = 0; i < 1600; i++) {
		fscanf(pgm1, "%d", &j);
		r[i] = (unsigned char)j;

		fscanf(pgm2, "%d", &j);
		p[i] = (unsigned char)j;

		fscanf(pgm3, "%d", &j);
		s[i] = (unsigned char)j;

		fscanf(pgm4, "%d", &j);
		b[i] = (unsigned char)j;
	}

	fclose(pgm1);
	fclose(pgm2);
	fclose(pgm3);
	fclose(pgm4);
}

int main(int argc, char **argv) {
	
	


	glutInit(&argc, argv);

	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(600, 520);
	glutCreateWindow("ΒραΧαΨα II");

	
	init();
	ReadThePgms();
	
	glutDisplayFunc(display);
	//glutReshapeFunc(changeSize);
		
	glutKeyboardFunc(processNormalKeys);
	
	
	glutMouseFunc(decide);
	


	glutMainLoop();

	return 1;
}

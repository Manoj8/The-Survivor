#include<GL/freeglut.h>
#include<stdio.h>
#include<math.h>
int u=0,i1,v=0,q=-50,r=0;
int u1=0,v1=-300,u3=0,vv1=0;
int x1=0,x2=0,x3=0;
int u4=0,z=-250,vv=0,uu=0;
float xx,yy;

void coverpage();
void disp1();
void takeoff();
void crashing();
void shark();
void terrain();
void car();
void background();
void pathgen(int);
void delay();
void drawString(float , float , float ,const char *);

void display();
void delay1();

#define INFINITY 100
#define MAX(a, b) ((a > b) ? (a) : (b))

int n = 5;
long dist[10][10];
long d[10];
int prev[10];
int path1[10];
int path[10];
int getPath[10];
long getDistance[10][10];
float x = 0, y = 0;
float m[10][10] = {
	{
		0,
		1.33,
		0.56,
		-1.33,
		-0.55
	},
	{
		1.33,
		0,
		0,
		-10.6,
		-1.76
	},
	{
		0.56,
		-0.25,
		0,
		1.76,
		-10.6
	},
{ -1.33,
-10.6,
1.76,
0,
0
},
{ -0.55,
-1.76,
-10.6,
0.15,
0
}
};

int i = 0, j = 0, k = 0;
int a, b, flag = 0;

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}



void destpath(int g) {
	int i, j, w;
	i = 0;
	j = n;
	w = g;
	while (j != 0) {

		if (prev[w] != -1) {
			path1[i] = prev[w];
			w = path1[i];
			i++;
		}
		j--;
	}
	j = 0;
	i--;
	while (i != -1) {
		path[j] = path1[i];
		i--;
		j++;
	}
	path[j] = g;
}

void dijkstra(int s)
{
	int i, k, mini;
	int visited[10];

	for (i = 1; i <= n; ++i) {
		d[i] = INFINITY;
		prev[i] = -1;
		visited[i] = 0;
		path1[i] = -1;
	}

	d[s] = 0;

	for (k = 1; k <= n; ++k) {
		mini = -1;
		for (i = 1; i <= n; ++i)
			if (!visited[i] && ((mini == -1) || (d[i] < d[mini])))
				mini = i;

		visited[mini] = 1;

		for (i = 1; i <= n; ++i)
			if (dist[mini][i]) {
				if (d[mini] + dist[mini][i] < d[i]) {
					d[i] = d[mini] + dist[mini][i];
					prev[i] = mini;
				}
			}
	}
}
void callPath(int a, int b) {
	int i, j, k;
	int u, v, w, dest, src;

	src = a;
	dest = b;

	dijkstra(src);

	destpath(dest);

	k = 0;
	while (path[k] != '\0') {
		getPath[k] = path[k];
		k++;
	}

}
void distanceMatrix() {
	int i, j;
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j)
			dist[i][j] = 0;

	n = 5;
	
	dist[1][2] = 10;
	dist[1][4] = 5;
	dist[2][3] = 1;
	dist[2][4] = 3;
	dist[3][5] = 6;
	dist[4][2] = 2;
	dist[4][3] = 9;
	dist[4][5] = 2;
	dist[5][1] = 7;
	dist[5][3] = 4;	

	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j)
			getDistance[i][j] = dist[i][j];
}


void drawString(float x, float y, float z,const char * string) {
	const char * c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}
void drawString1(float x, float y, float z,const char * string) {
	const char * c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}
void drawString2(float x, float y, float z,const char * string) {
	const char * c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}


/*void specialkey(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:yy=yy+5;
			glutPostRedisplay(); break;
		case GLUT_KEY_DOWN:yy=yy-5; glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:    //glutPostRedisplay();
			uu=uu+5; glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			xx=xx+5; glutPostRedisplay();
		break;
		

	}
}*/


void delay() 
{
	unsigned int i;
	for (i = 0;i < 6500000;i++);
	glutPostRedisplay();
	glutSwapBuffers();
}


void coverpage()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.7, 0.0, 0.0);

	drawString(180.0, 475.0, 1.0, "    RNS INSTITUTE OF TECHNOLOGY  ");
	glColor3f(0.0, 0.2, 1.0);
	
	drawString(175.0, 440.0, 1.0, "DEPARTMENT OF COMPUTER SCIENCE");
	glColor3f(0.7, 0.5, 0.06);
	drawString(200.0, 390.0, 1.0, "A MINI PROJECT ON");
	glColor3f(0.3, 0.8, 0.4);
	drawString(205.0, 350.0, 1.0, "THE SURVIVOR");
	glColor3f(0.7, 0.5, 0.06);
	drawString(80.0, 150.0, 1.0, "BY");
	glColor3f(0.7, 0.5, 0.06);
	drawString(380.0, 150.0, 1.0, "GUIDED BY");
	glColor3f(0.79, 0.37, 1.0);
	drawString(45.0, 120.0, 1.0, "A MANOJ KUMAR               1RN15CS002");
	glColor3f(0.79, 0.37, 1.0);
	drawString(40.0, 100.0, 1.0, "AMITH R KORADAKERI         1RN15CS019");
	glColor3f(0.79, 0.37, 1.0);
	drawString(370.0, 120.0, 1.0, "Mrs.MAMATHA JAJUR");
	glColor3f(0.79, 0.37, 1.0);
	drawString(370.0, 100.0, 1.0, "Mrs.SAMPADA K S");
	glColor3f(0.15, 0.6, 0.25);
	
	drawString(215.0, 50.0, 1.0, "Press S to start");
	glFlush();


	//for(i=0;i<10000;i++)
	//glutDisplayFunc(takeoff);

}

void disp1()
{
	int i;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glColor3f(1,0,0);
	 drawString1(225, 250, 0, " THE END ");
	
	glFlush();
	
}

void disp2()
{
	int i;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glColor3f(1,0,0);
	drawString1(225, 250, 0, " Man was Killed ");
	

	
}

void takeoff()
{
	int nn;
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(500,0);
	glVertex2f(500,200);
	glVertex2f(0,200);
	glEnd();
	if(u1<500)u1++;
	if(v1<0)v1++;
	for(i1=0;i1<u1;i1++)
	{
		glColor3f(0.8,.5,.3);
		glBegin(GL_POLYGON); //main body
		glVertex2f(10+u1,400+v1);
		glVertex2f(80+u1,400+v1);
		glVertex2f(80+u1,430+v1);
		glVertex2f(10+u1,430+v1);
		glVertex2f(10+u1,400+v1);
		glEnd();
				
		glColor3f(.7,0.2,0);     //back
		glBegin(GL_POLYGON);
		glVertex2f(10+u1,430+v1);
		glVertex2f(10+u1,450+v1);
		glVertex2f(25+u1,450+v1);
		glVertex2f(30+u1,430+v1);
		glVertex2f(10+u1,430+v1);
		glEnd();
				
		glColor3f(.7,0.2,0);    //up wing
		glBegin(GL_POLYGON);
		glVertex2f(50+u1,430+v1);
		glVertex2f(40+u1,450+v1);
		glVertex2f(60+u1,450+v1);
		glVertex2f(70+u1,430+v1);
		glVertex2f(50+u1,430+v1);
		glEnd();
				
		glColor3f(.7,0.2,0);   //down wing 
		glBegin(GL_POLYGON);
		glVertex2f(50+u1,410+v1);
		glVertex2f(40+u1,380+v1);
		glVertex2f(60+u1,380+v1);
		glVertex2f(70+u1,410+v1);
		glVertex2f(50+u1,410+v1);
		glEnd();
				
		glColor3f(.7,0.2,0);	//front 1
		glBegin(GL_POLYGON);
		glVertex2f(80+u1,430+v1);
		glVertex2f(100+u1,416+v1);
		glVertex2f(100+u1,414+v1);
		glVertex2f(80+u1,400+v1);
		glEnd();
	}
	glColor3f(0.8,0.8,0.1);
	
	for(nn=0;nn<500;nn+=73)//road strips
	{
		glBegin(GL_LINE_STRIP);	
		glVertex2f(10+nn,100);
		glVertex2f(50+nn,100);
		glEnd();
	}
	glLineWidth(8);
	glFlush();
	glutSwapBuffers();
	glFlush();
	if(u1==499)
	{
		glutDisplayFunc(crashing);
	}	
}

void crashing() 
{
	float theta;
	int j;
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(u<358)u++;
	if(v<=0)v--;
		
	if(u<354)
	{
		glColor3f(0.8,.5,.3);
		glBegin(GL_POLYGON); //main body
		glVertex2f(10+u,400);
		glVertex2f(80+u,400);
		glVertex2f(80+u,430);
		glVertex2f(10+u,430);
		glVertex2f(10+u,400);
		glEnd();
				
		glColor3f(.7,0.2,0);     //back
		glBegin(GL_POLYGON);
		glVertex2f(10+u,430);
		glVertex2f(10+u,450);
		glVertex2f(25+u,450);
		glVertex2f(30+u,430);
		glVertex2f(10+u,430);
		glEnd();
				
		glColor3f(.7,0.2,0);     //up wing
		glBegin(GL_POLYGON);
		glVertex2f(50+u,430);
		glVertex2f(40+u,450);
		glVertex2f(60+u,450);
		glVertex2f(70+u,430);
		glVertex2f(50+u,430);
		glEnd();
				
		glColor3f(.7,0.2,0);    //down wing 
		glBegin(GL_POLYGON);
		glVertex2f(50+u,410);
		glVertex2f(40+u,380);
		glVertex2f(60+u,380);
		glVertex2f(70+u,410);
		glVertex2f(50+u,410);
		glEnd();
				
		glColor3f(.7,0.2,0); 	//front 1
		glBegin(GL_POLYGON);
		glVertex2f(80+u,430);
		glVertex2f(100+u,416);
		glVertex2f(100+u,414);
		glVertex2f(80+u,400);
		glEnd();	
	}
	if(u<600)u++;

	if(u>350&&u<399)	
	{
	
		glColor3f(1.0,0.0,0.0);		//blast
		glBegin(GL_POLYGON); 
		glVertex2f(405,320); 
		glVertex2f(385,285); 
		glVertex2f(365,345); 
		glVertex2f(345,355); 
		glVertex2f(345,415); 
		glVertex2f(330,440); 
		glVertex2f(345,475); 
		glVertex2f(352,530); 
		glVertex2f(380,520); 
		glVertex2f(395,565); 
		glVertex2f(415,530); 
		glVertex2f(440,547); 
		glVertex2f(450,510); 
		glVertex2f(470,510); 
		glVertex2f(475,470); 
		glVertex2f(490,442); 
		glVertex2f(490,405);  
		glVertex2f(470,370); 
		glVertex2f(475,335); 
		glVertex2f(465,305); 
		glVertex2f(445,320); 
		glVertex2f(425,285); 
		glVertex2f(404,320); 
		glEnd(); 	
	}

	if(v>-185){
	glColor3f(0,0,1);	//man
	glBegin(GL_LINES);
	glVertex2f(50+u,360+v);  //body
	glVertex2f(50+u,340+v);
	glVertex2f(50+u,340+v);  //Rleg
	glVertex2f(44+u,325+v);
	glVertex2f(50+u,340+v);  //Lleg
	glVertex2f(56+u,325+v);
	glVertex2f(50+u,350+v);  //Rhand
	glVertex2f(40+u,360+v);
	glVertex2f(50+u,350+v);  //Lhand
	glVertex2f(60+u,360+v);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2f(40+u,360+v);
	glVertex2f(20+u,391+v);
	glVertex2f(60+u,360+v);
	glVertex2f(80+u,391+v);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);	//head
	for(j=0;j<360;j++)
	{
		theta=j*3.14/180;
		glVertex2f(50+7*cos(theta)+u,367+7*sin(theta)+v);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);  //parachute
	for(j=0;j<180;j++)
	{
		theta=j*3.14/180;
		glVertex2f(50+30*cos(theta)+u,390+20*sin(theta)+v);
	}
	glEnd();
	}

	glColor3f(0.0,0.5,1.0);   //water
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(500,0);
	glVertex2f(500,200);
	glVertex2f(0,200);
	glVertex2f(0,0);
	glEnd();	
	glColor3f(0.4f,0.15f,0.0f); //boat
	glBegin(GL_POLYGON);
	glVertex2f(30+u,185);
	glVertex2f(75+u,185);
	glVertex2f(95+u,225);
	glVertex2f(10+u,225);
	glVertex2f(30+u,190);
	glEnd();

	if(u>390){
	glColor3f(0,0,1);   //man inside boat
	glBegin(GL_LINES);
	glVertex2f(50+u,225);
	glVertex2f(50+u,240);
	glVertex2f(50+u,230);
	glVertex2f(60+u,210);
	glEnd();
	
	
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
	for(j=0;j<360;j++)
	{
		theta=j*3.14/180;
		glVertex2f(50+7*cos(theta)+u,245+7*sin(theta));
	}
	glEnd();
	}
	glLineWidth(8);
	glFlush();
	if(u==599)
	{
		glutDisplayFunc(shark);
	}
}

void shark()
{
	float theta;
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor3d(0.0,0.5,1);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);	//water
	glVertex2f(500,0);
	glVertex2f(500,200);
	glVertex2f(0,200);
	glVertex2f(0,0);
	glEnd();
	glLineWidth(8);
	if(uu<100)uu++;
	for(i=0;i<uu;i+=10)
	{
		glColor3f(0.4f,0.15f,0.0f); //boat
		glBegin(GL_POLYGON);
		glVertex2f(30+uu,190);
		glVertex2f(70+uu,190);
		glVertex2f(90+uu,225);
		glVertex2f(10+uu,225);
		glVertex2f(30+uu,190);
		glEnd();
		
		glColor3f(0,0,1);   //man
		glBegin(GL_LINES);
		
		glVertex2f(50+uu,225);
		glVertex2f(50+uu,240);
		glVertex2f(50+uu,230);
		glVertex2f(60+uu,210);
		glEnd();
	
		glColor3f(0,0,1);
		glBegin(GL_POLYGON);
		for(j=0;j<360;j++)
		{
			theta=j*3.14/180;
			glVertex2f(50+8*cos(theta)+uu,245+8*sin(theta));
		}
		glEnd();
		
		
	}
	if(uu>50&&vv1<500)vv1++;
	if(uu>50){	
		for(i=0;i<vv1;i++)		//shark
		{
		glColor3f(0.2,0.2,0.2);
		glBegin(GL_TRIANGLES);
		glVertex2f(10+vv1,200);
		glVertex2f(5+vv1,230);
		glVertex2f(32+vv1,200);
		glEnd();
		if(vv1==(uu-8))
		{
			glutDisplayFunc(disp2);
		}
	}}
	glLineWidth(8);
	glColor3f(1,0,0);
	drawString(50.0, 380.0, 1.0, "Press D to move the boat ");
	glFlush();
	if(uu>490)glutDisplayFunc(terrain);
}

void terrain()
{
	float theta;
	int j;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glLineWidth(8);
	glColor3f(0.0,0.5,1);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);    //water
	glVertex2f(250,0);
	glVertex2f(250,200);
	glVertex2f(0,200);
	glVertex2f(0,0);
	glEnd();
	
	glColor3f(0,0.5,0);   //grass
	glBegin(GL_POLYGON);
	glVertex2f(250,0);
	glVertex2f(500,0);
	glVertex2f(500,200);
	glVertex2f(300,200);
	glVertex2f(250,200);
	glVertex2f(250,0);
	glEnd();
	if(x1<173)x1++;
	if(x2<600)x2++;
	for(i=0;i<x1;i++)
	{
	glColor3f(0.4f,0.15f,0.0f);//boat
	glBegin(GL_POLYGON);
	glVertex2f(30+x1,190);
	glVertex2f(70+x1,190);
	glVertex2f(90+x1,225);
	glVertex2f(10+x1,225);
	glVertex2f(30+x1,190);
	glEnd();
	
	}
	glLineWidth(8);
	if(x2<250)
	{
		glColor3f(0,0,1);
	glBegin(GL_LINES);
	glVertex2f(50+x1,225);
	glVertex2f(50+x1,240);
	glVertex2f(50+x1,230);
	glVertex2f(60+x1,210);
	glEnd();

		glBegin(GL_POLYGON);
		for(j=0;j<360;j++)
		{
			theta=j*3.14/180;
			glVertex2f(50+8*cos(theta)+x1,245+8*sin(theta));
		}
		glEnd();
	}
	glLineWidth(8);
	if(x2>300)x3++;

	if(x2>300)
	{
		glColor3f(0,0,1);
		glLineWidth(8);
		glBegin(GL_LINES);
		glVertex2f(268+x3,220);
		glVertex2f(268+x3,240);
		glVertex2f(268+x3,220);  //Rleg
		glVertex2f(273+x3,200);
		glVertex2f(268+x3,220);  //Lleg
		glVertex2f(263+x3,200);
		glVertex2f(268+x3,233);  //Rhand
		glVertex2f(275+x3,215);
		glVertex2f(268+x3,233);  //Lhand
		glVertex2f(261+x3,215);
		glEnd();
		glBegin(GL_POLYGON);
		for(j=0;j<360;j++)
		{
			theta=j*3.14/180;
			glVertex2f(268+7*cos(theta)+x3,245+7*sin(theta));
		}
		glEnd();
	}
	glLineWidth(8);
	glFlush();
	
	if(x2==599)
	glutDisplayFunc(display);
}


void car()
{
	float theta;
	int j,k,y,kk;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2, 0.2, 0.2, 0);
	glColor3f(0,0.5,0);//Bottom Grass
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(500,0);
	glVertex2f(500,150);
	glVertex2f(0,150);
	glVertex2f(0,0);
	glEnd();
	glColor3f(0,0.5,0);
	glBegin(GL_POLYGON);   //Up Grass
	glVertex2f(0,350);
	glVertex2f(500,350);
	glVertex2f(500,500);
	glVertex2f(0,500);
	glVertex2f(0,350);
	glEnd();
	glColor3f(0.8,0.8,0.1);
	for(kk=0;kk<550;kk+=73)
	{
		glBegin(GL_LINE_STRIP);	//road strips
		glVertex2f(10+kk,250);
		glVertex2f(50+kk,250);
		glEnd();
	}
	glLineWidth(8);
	if(z<-50)z++;r++;
	if(r<250){
		glColor3f(0,0,1);   //man
		glBegin(GL_LINES);
		glVertex2f(75,370);
		glVertex2f(75,390);
		glVertex2f(75,370);  //Rleg
		glVertex2f(80,350);
		glVertex2f(75,370);  //Lleg
		glVertex2f(70,350);
		glVertex2f(75,383);  //Rhand
		glVertex2f(82,365);
		glVertex2f(75,383);  //Lhand
		glVertex2f(68,365);
		glEnd();
		glBegin(GL_POLYGON);
		for(j=0;j<360;j++)
		{
			theta=j*3.14/180;
			glVertex2f(75+7*cos(theta),396+7*sin(theta));
		}
		glEnd();
	}
	if(r<250){
	for(i=-300;i<z;i+=5)
	{	
		
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);	//car bottom
		glVertex2f(40+z,280);
		glVertex2f(190+z,280);
		glVertex2f(190+z,330);
		glVertex2f(40+z,330);
		glVertex2f(40+z,280);
		glEnd();
		
		glColor3f(1,1,1);    //car top
		glBegin(GL_POLYGON);
		glVertex2f(60+z,330);
		glVertex2f(80+z,380);
		glVertex2f(150+z,380);
		glVertex2f(170+z,330);
		glVertex2f(70+z,330);
		glEnd();
		
		glColor3f(.1,.1,.1);	//windows 1
		glBegin(GL_POLYGON);
		glVertex2f(82+z,330);
		glVertex2f(82+z,360);
		glVertex2f(112+z,360);
		glVertex2f(112+z,330);
		glVertex2f(82+z,330);
		glEnd();
		
		glColor3f(.1,.1,.1);  //window 2
		glBegin(GL_POLYGON);
		glVertex2f(119+z,330);
		glVertex2f(119+z,360);
		glVertex2f(149+z,360);
		glVertex2f(149+z,330);
		glVertex2f(119+z,330);
		glEnd();
		
		glColor3f(.1,.1,.1);  //window 3
		glBegin(GL_TRIANGLES);
		glVertex2f(158+z,360);
		glVertex2f(158+z,330);
		glVertex2f(170+z,330);
		glEnd();
		
		glColor3f(.1,.1,.1);  //window 0
		glBegin(GL_TRIANGLES);
		glVertex2f(60+z,330);
		glVertex2f(72+z,360);
		glVertex2f(72+z,330);
		glEnd();
		
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);	//car front
		glVertex2f(170+z,330);
		glVertex2f(190+z,330);
		glVertex2f(177+z,360);
		glVertex2f(158+z,360);
		glVertex2f(170+z,330);
		glEnd();
		
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);	//car back
		glVertex2f(40+z,330);
		glVertex2f(53+z,360);
		glVertex2f(72+z,360);
		glVertex2f(60+z,330);
		glVertex2f(40+z,330);
		glEnd();
		
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
		glVertex2f(190+z,320);
		glVertex2f(190+z,305);
		glVertex2f(191+z,305);
		glVertex2f(191+z,320);
		glVertex2f(190,320);
		glEnd();
		
		glColor3f(0.7,0.7,0.2);
		glBegin(GL_POLYGON);
		glVertex2f(191+z,320);
		glVertex2f(191+z,305);
		glVertex2f(240+z,280);
		glVertex2f(240+z,345);
		glVertex2f(191+z,320);
		glEnd();
		
		glColor3f(0.05,0.05,0.05); //wheels
		glBegin(GL_POLYGON);
		for(j=0;j<360;j++)
		{
			theta=j*3.14/180;
			glVertex2f(70+15*cos(theta)+z,275+15*sin(theta));
		}
		glEnd();
		
		glColor3f(0.05,0.05,0.05);
		glBegin(GL_POLYGON);
		for(k=0;k<360;k++)
		{
			theta=k*3.14/180;
			glVertex2f(160+15*cos(theta)+z,275+15*sin(theta));
		}
		glEnd();
	}
	}
	if(r>270&&r<1300){r++;q++;}
	if(r>248){
	for(y=-300;y<z;y+=5)
	{	
		
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);	//car bottom
		glVertex2f(40+q,280);
		glVertex2f(190+q,280);
		glVertex2f(190+q,330);
		glVertex2f(40+q,330);
		glVertex2f(40+q,280);
		glEnd();
		
		glColor3f(1,1,1);  //car top
		glBegin(GL_POLYGON);
		glVertex2f(60+q,330);
		glVertex2f(80+q,380);
		glVertex2f(150+q,380);
		glVertex2f(170+q,330);
		glVertex2f(70+q,330);
		glEnd();
		
		glColor3f(.1,.1,.1);	//windows 1
		glBegin(GL_POLYGON);
		glVertex2f(82+q,330);
		glVertex2f(82+q,360);
		glVertex2f(112+q,360);
		glVertex2f(112+q,330);
		glVertex2f(82+q,330);
		glEnd();
		
		glColor3f(.1,.1,.1);  //window 2
		glBegin(GL_POLYGON);
		glVertex2f(119+q,330);
		glVertex2f(119+q,360);
		glVertex2f(149+q,360);
		glVertex2f(149+q,330);
		glVertex2f(119+q,330);
		glEnd();
		
		glColor3f(.1,.1,.1);  //window 3
		glBegin(GL_TRIANGLES);
		glVertex2f(158+q,360);
		glVertex2f(158+q,330);
		glVertex2f(170+q,330);
		glEnd();
		
		glColor3f(.1,.1,.1);  //window 0
		glBegin(GL_TRIANGLES);
		glVertex2f(60+q,330);
		glVertex2f(72+q,360);
		glVertex2f(72+q,330);
		glEnd();
		
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);	//car front
		glVertex2f(170+q,330);
		glVertex2f(190+q,330);
		glVertex2f(177+q,360);
		glVertex2f(158+q,360);
		glVertex2f(170+q,330);
		glEnd();
		
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);	//car back
		glVertex2f(40+q,330);
		glVertex2f(53+q,360);
		glVertex2f(72+q,360);
		glVertex2f(60+q,330);
		glVertex2f(40+q,330);
		glEnd();
		
		glColor3f(1,1,1);	//headlight
		glBegin(GL_POLYGON);
		glVertex2f(190+q,320);
		glVertex2f(190+q,305);
		glVertex2f(191+q,305);
		glVertex2f(191+q,320);
		glVertex2f(190+q,320);
		glEnd();
		
		glColor3f(0.7,0.7,0.2);	//light
		glBegin(GL_POLYGON);
		glVertex2f(191+q,320);
		glVertex2f(191+q,305);
		glVertex2f(240+q,280);
		glVertex2f(240+q,345);
		glVertex2f(191+q,320);
		glEnd();
		
		glColor3f(0.05,0.05,0.05); //wheels
		glBegin(GL_POLYGON);
		for(j=0;j<360;j++)
		{
			theta=j*3.14/180;
			glVertex2f(70+15*cos(theta)+q,275+15*sin(theta));
		}
		glEnd();
		
		glColor3f(0.05,0.05,0.05);
		glBegin(GL_POLYGON);
		for(k=0;k<360;k++)
		{
			theta=k*3.14/180;
			glVertex2f(160+15*cos(theta)+q,275+15*sin(theta));
		}
		glEnd();
	}
	}
	glLineWidth(8);
	glutSwapBuffers();
	glFlush();

	if(q>460)glutDisplayFunc(disp1);

}


void delay1()
{
	int bx, ax;
	bx = 100;
label1: ax = 2000;
label2: ax--;
	if (ax != 0) {
		goto label2;
	}
	bx--;
	if (bx != 0) {
		goto label1;
	}
}
void sources()
{
	float theta = 0;
	int ii, ij,t=-70,t1=-30,q=-80;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	drawString(40.0, 215.0, 1.0, "  Forest  ");
	drawString(125.0, 365.0, 1.0, "  Desert  ");
	drawString(360.0, 380.0, 1.0, "  Mountain  ");
	drawString(135.0, 25.0, 1.0, "  City  ");
	drawString(350.0, 50.0, 1.0, "  River  ");
	glColor3f(0, 0.15, 0.0);
	glBegin(GL_POLYGON);   //ground
	for (ii = 0; ii<360; ii++)
	{
		theta = 3.14*ii / 180;
		glVertex2f(t1+80 + 40 * cos(theta), 260 + 15 * sin(theta));
	}
	glEnd();
	glColor3f(0, 0.7, 0);      //leaves
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(50+t1, 310);
	glVertex2f(55+t1, 325);
	glVertex2f(65+t1, 340);
	glVertex2f(80+t1, 370);
	glVertex2f(95+t1, 360);
	glVertex2f(108+t1, 335);
	glVertex2f(110+t1, 310);
	glEnd();
	glColor3f(0.5, 0.0, 0.0);    //branch
	glBegin(GL_POLYGON);
	glVertex2f(78+t1, 310);
	glVertex2f(86+t1, 310);
	glVertex2f(86+t1, 260);
	glVertex2f(78+t1, 260);
	glVertex2f(78+t1, 310);
	glEnd();

	glColor3f(0.0, 0.5, 0);
	glBegin(GL_POLYGON);   //ground
	for (ii = 0; ii<360; ii++)
	{
		theta = 3.14*ii / 180;
		glVertex2f(145 + 30 * cos(theta), 55 + 15 * sin(theta));
	}
	glEnd();



	glColor3f(1, 0, 1);		//building1

	glBegin(GL_POLYGON);
	glVertex2f(125, 115);
	glVertex2f(135, 115);
	glVertex2f(135, 50);
	glVertex2f(125, 50);
	glEnd();

	glColor3f(1, 0, 0.5);	//building2
	glBegin(GL_POLYGON);
	glVertex2f(135, 135);
	glVertex2f(155, 135);
	glVertex2f(155, 50);
	glVertex2f(135, 50);
	glEnd();

	glColor3f(1, 0, 1);

	glBegin(GL_POLYGON);	//building3
	glVertex2f(155, 115);
	glVertex2f(165, 115);
	glVertex2f(165, 50);
	glVertex2f(155, 50);
	glEnd();

	for (ij = 0; ij<40; ij += 10)
	{
		glColor3f(1, 1, 0);	//window1
		glBegin(GL_POLYGON);
		glVertex2f(127 + ij, 105);
		glVertex2f(132 + ij, 105);
		glVertex2f(132 + ij, 95);
		glVertex2f(127 + ij, 95);
		glEnd();
	}

	for(ij = 0;ij < 40;ij += 10)
	{
		glColor3f(1, 1, 0);	//window2
		glBegin(GL_POLYGON);
		glVertex2f(127 + ij, 80);
		glVertex2f(132 + ij, 80);
		glVertex2f(132 + ij, 70);
		glVertex2f(127 + ij, 70);
		glEnd();
	}


	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	for (ii = 0; ii<360; ii++)
	{
		theta = 3.14*ii / 180;
		glVertex2f(350 + 45 * cos(theta), 100 + 25 * sin(theta));
	}
	glEnd();
	glColor3f(0.3, 0, 0);  //boat
	glBegin(GL_POLYGON);
	glVertex2f(335, 120);
	glVertex2f(370, 120);
	glVertex2f(360, 95);
	glVertex2f(345, 95);
	glEnd();


	glColor3f(0.7, 0.4, 0);
	glBegin(GL_POLYGON);   //ground
	for (ii = 0; ii<360; ii++)
	{
		theta = 3.14*ii / 180;
		glVertex2f(t+208 + 30 * cos(theta), 400 + 15 * sin(theta));
	}
	glEnd();
	
	
	glColor3f(0, 0.5, 0);		//1cac
	glBegin(GL_POLYGON);
	glVertex2f(202+t, 400);
	glVertex2f(213+t, 400);
	glVertex2f(213+t, 420);
	glVertex2f(202+t, 420);
	glEnd();

	glBegin(GL_POLYGON);    //cac2
	glVertex2f(228+t, 430);
	glVertex2f(228+t, 445);
	glVertex2f(218+t, 445);
	glVertex2f(218+t, 430);
	glEnd();

	glBegin(GL_POLYGON);    //cac3
	glVertex2f(213+t, 430);
	glVertex2f(213+t, 465);
	glVertex2f(202+t, 465);
	glVertex2f(202+t, 430);
	glEnd();

	glBegin(GL_POLYGON);    //cac4
	glVertex2f(197+t, 430);
	glVertex2f(197+t, 445);
	glVertex2f(187+t, 445);
	glVertex2f(187+t, 430);
	glEnd();
	
	glBegin(GL_POLYGON);    //cac5
	glVertex2f(187+t, 430);
	glVertex2f(187+t, 420);
	glVertex2f(228+t, 420);
	glVertex2f(228+t, 430);
	glEnd();
	
	glColor3f(0.75, 0.75, 0.75);  //mountain
	glBegin(GL_TRIANGLES);
	glVertex2f(375+q, 410);
	glVertex2f(400+q, 445);
	glVertex2f(425+q, 410);
	glVertex2f(350+q, 410);
	glVertex2f(375+q, 435);
	glVertex2f(400+q, 410);
	glVertex2f(400+q, 410);
	glVertex2f(425+q, 435);
	glVertex2f(450+q, 410);
	glEnd();
	
	glBegin(GL_POLYGON);	
	glColor3f(1,1,1);
	for (j = 360; j >=180 ; j--)
	{
		theta = j * 3.14 / 180;
		glVertex2f(440 + 6 * cos(theta) + xx, 450+ 6 * sin(theta) + yy);
	}
	glEnd();

	glBegin(GL_POINTS);   //snow
	glVertex2f(365+q, 465);
	glVertex2f(375+q, 460);
	glVertex2f(385+q, 455);
	glVertex2f(382+q, 450);
	glVertex2f(355+q, 453);
	glVertex2f(360+q, 445);
	glVertex2f(367+q, 455);
	glVertex2f(415+q, 470);
	glVertex2f(405+q, 460);
	glVertex2f(395+q, 455);
	glVertex2f(422+q, 460);
	glVertex2f(445+q, 440);
	glVertex2f(450+q, 455);
	glVertex2f(432+q, 460);
	glVertex2f(435+q, 440);
	glVertex2f(440+q, 455);
	glEnd();
	glPointSize(3);
	
	glColor3f(1,0,0);
	drawString(10, 315, 0, "1");
	drawString(110, 470, 0, "2");
	drawString(325, 480, 0, "3");
	drawString(100, 60, 0, "4");
	drawString(385, 160, 0, "5");
	glFlush();

}


void display2() 
{
	
	int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	sources();
	
	glColor3f(0.0, 0.0, 1.0);
	drawString2(385, 235, 0, "Press P to find the path");
	glutPostRedisplay();
	
	glFlush();
}

void pathgen() 
{

	float theta = 0, xx = 0, yy = 0,y=25,x=18,ik;
	int t=-65;
	glLineWidth(7);
	if (a == b) 
	{
		if (a == 1) 
		{
			glColor3f(0.0, 0.0, 1.0);
			drawString(10, 295, 0, "Source");
			drawString(10, 210, 0, "Destination");
			glFlush();
		}
		else if (a == 2) 
		{
			glColor3f(0.0, 0.0, 1.0);
			drawString(110, 460, 0, "Source");
			drawString(110, 375, 0, "Destination");
			glFlush();
		}
		else if (a == 3) {
			glColor3f(0.0, 0.0, 1.0);
			drawString(285, 460, 0, "Source");
			drawString(285, 375, 0, "Destination");
			glFlush();
		}
		else if (a == 4) {
			glColor3f(0.0, 0.0, 1.0);
			drawString(110, 130, 0, "Source");
			drawString(110, 45, 0, "Destination");
			glFlush();
		}
		else {
			glColor3f(0.0, 0.0, 1.0);
			drawString(285, 130, 0, "Source");
			drawString(285, 45, 0, "Destination");
			glFlush();
		}
		glFlush();
	}
	else {
		glColor3f(1, 0,0);
		if (a == 1)
		{
			drawString(10, 295, 0, "Source");
			glColor3f(0, 0, 1);

			glBegin(GL_LINES);
			glVertex2f(70 + xx, 280 + yy);  //body
			glVertex2f(70 + xx, 260 + yy);
			glVertex2f(70 + xx, 260 + yy);  //Rleg
			glVertex2f(65 + xx, 250 + yy);
			glVertex2f(70 + xx, 260 + yy);  //Lleg
			glVertex2f(75 + xx, 250 + yy);
			glVertex2f(70 + xx, 275 + yy);  //Rhand
			glVertex2f(63 + xx, 265 + yy);
			glVertex2f(70 + xx, 275 + yy);  //Lhand
			glVertex2f(77 + xx, 265 + yy);
			glEnd();

			glBegin(GL_POLYGON);	//head
			for (j = 0; j < 360; j++)
			{
				theta = j * 3.14 / 180;
				glVertex2f(70 + 6 * cos(theta) + xx, 285 + 6 * sin(theta) + yy);
			}
			glEnd();


		}
		else if (a == 2)
		{	
			glColor3f(1, 0, 0);
			drawString(110, 460, 0, "Source");
			glColor3f(0, 0, 1);
			glBegin(GL_LINES);
			glVertex2f(t+200 + xx, 430 + yy);  //body
			glVertex2f(t+200 + xx, 410 + yy);
			glVertex2f(t+200 + xx, 410 + yy);  //Rleg
			glVertex2f(t+195 + xx, 400 + yy);
			glVertex2f(t+200 + xx, 410 + yy);  //Lleg
			glVertex2f(t+205 + xx, 400 + yy);
			glVertex2f(t+200 + xx, 425 + yy);  //Rhand
			glVertex2f(t+193 + xx, 415 + yy);
			glVertex2f(t+200 + xx, 425 + yy);  //Lhand
			glVertex2f(t+207 + xx, 415 + yy);
			glEnd();

			
			glBegin(GL_POLYGON);	//head
			for (j = 0; j < 360; j++)
			{
				theta = j * 3.14 / 180;
				glVertex2f(t+200 + 6 * cos(theta) + xx, 435 + 6 * sin(theta) + yy);
			}
			glEnd();

		}
		else if (a == 3)
		{
			drawString(285, 480, 0, "Source");

			glColor3f(0, 0, 1);
			glBegin(GL_LINES);
			glVertex2f(370 + xx+t, 420 + yy);  //body
			glVertex2f(370 + xx+t, 400 + yy);
			glVertex2f(370 + xx+t, 400 + yy);  //Rleg
			glVertex2f(365 + xx+t, 390 + yy);
			glVertex2f(370 + xx+t, 400 + yy);  //Lleg
			glVertex2f(375 + xx+t, 390 + yy);
			glVertex2f(370 + xx+t, 415 + yy);  //Rhand
			glVertex2f(363 + xx+t, 405 + yy);
			glVertex2f(370 + xx+t, 415 + yy);  //Lhand
			glVertex2f(377 + xx+t, 405 + yy);
			glEnd();

			glBegin(GL_POLYGON);	//head
			for (j = 0; j < 360; j++)
			{
				theta = j * 3.14 / 180;
				glVertex2f(t+370 + 6 * cos(theta) + xx, 425 + 6 * sin(theta) + yy);
			}
			glEnd();
		}
		else if (a == 4)
			drawString(110, 130, 0, "Source");
		else if (a == 5)
		{
			drawString(285, 150, 0, "Source");
			glColor3f(0, 0, 1 );
			glBegin(GL_LINES);
			glVertex2f(x+300 + xx, y+130 + yy);  //body
			glVertex2f(x+300 + xx, y+110 + yy);
			glVertex2f(x+300 + xx, y+110 + yy);  //Rleg
			glVertex2f(x+295 + xx, y+100 + yy);
			glVertex2f(x+300 + xx, y+110 + yy);  //Lleg
			glVertex2f(x+305 + xx, y+100 + yy);
			glVertex2f(x+300 + xx, y+125 + yy);  //Rhand
			glVertex2f(x+293 + xx, y+115 + yy);
			glVertex2f(x+300 + xx, y+125 + yy);  //Lhand
			glVertex2f(x+307 + xx, y+115 + yy);
			glEnd();


			glBegin(GL_POLYGON);	//head
			for (j = 0; j < 360; j++)
			{
				theta = j * 3.14 / 180;
				glVertex2f(x+300 + 6 * cos(theta) + xx, y+135 + 6 * sin(theta) + yy);
			}
			glEnd();
		}

		if (b == 1)
			drawString(10, 210, 0, "Destination");
		else if (b == 2)
			drawString(110, 375, 0, "Destination");
		else if (b == 3)
			drawString(285, 375, 0, "Destination");
		else if (b == 4){
			glColor3f(1,0,0);
			drawString(125, 28, 0, "Destination");}
		else if (b == 5)
			drawString(285, 45, 0, "Destination");

		i = 0;
		while (getPath[i + 1] != '\0') {
			if (getPath[i] == 1) {
				glFlush();
				if (getPath[i + 1] == 2) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 60) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(110 + x, 290 + y, 0);
						glVertex3f(125 + x, 307.5 + y, 0);
						glVertex3f(130 + x, 302.5 + y, 0);
						glVertex3f(115 + x, 285 + y, 0);
						glVertex3f(110 + x, 290 + y, 0);
						y = y + 33;
						x = x + 25;

						glFlush();
						glEnd();
						for (k = 0; k <= 100; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else if (getPath[i + 1] == 3) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 31) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(112.5 + x, 250 + y, 0);
						glVertex3f(135 + x, 265 + y, 0);
						glVertex3f(137.5 + x, 260 + y, 0);
						glVertex3f(115 + x, 245 + y, 0);
						glVertex3f(112.5 + x, 250 + y, 0);
						y = y + 25;
						x = x + 48;

						glFlush();
						glEnd();
						for (k = 0; k <= 100; k++) {
							delay1();
						}
						glFlush();
					}

					glFlush();
				}
				else if (getPath[i + 1] == 4) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 60) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(65 + x, 220 + y, 0);
						glVertex3f(80 + x, 200 + y, 0);
						glVertex3f(75 + x, 195 + y, 0);
						glVertex3f(60 + x, 215 + y, 0);
						glVertex3f(65 + x, 220 + y, 0);
						y = y - 33;
						x = x + 25;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 40) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(95 + x, 210 + y, 0);
						glVertex3f(117.5 + x, 197.5 + y, 0);
						glVertex3f(115 + x, 192.5 + y, 0);
						glVertex3f(92.5 + x, 205 + y, 0);
						glVertex3f(95 + x, 210 + y, 0);
						y = y - 32;
						x = x + 56;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}

					glFlush();
				}
				glFlush();
			}
			else if (getPath[i] == 2) {
				glFlush();
				if (getPath[i + 1] == 1) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 60) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(120 + x, 375 + y, 0);
						glVertex3f(125 + x, 370 + y, 0);
						glVertex3f(110 + x, 350 + y, 0);
						glVertex3f(105 + x, 355 + y, 0);
						glVertex3f(120 + x, 375 + y, 0);
						y = y - 25;
						x = x - 18;

						glFlush();
						glEnd();
						for (k = 0; k <= 100; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else if (getPath[i + 1] == 3) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 50) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(212.5 + x, 445 + y, 0);
						glVertex3f(237.5 + x, 445 + y, 0);
						glVertex3f(237.5 + x, 438 + y, 0);
						glVertex3f(212.5 + x, 438 + y, 0);
						glVertex3f(212.5 + x, 445 + y, 0);
						y = y;
						x = x + 30;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else if (getPath[i + 1] == 4) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 35) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(135 + x, 380 + y, 0);
						glVertex3f(137.5 + x, 355 + y, 0);
						glVertex3f(142.5 + x, 359 + y, 0);
						glVertex3f(140 + x, 383.5 + y, 0);
						glVertex3f(135 + x, 380 + y, 0);
						y = y - 70;
						x = x + 5;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}

					glFlush();
					
				}
				else {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 31) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(182.5 + x, 367.5 + y, 0);
						glVertex3f(195 + x, 345 + y, 0);
						glVertex3f(190 + x, 342.5 + y, 0);
						glVertex3f(177.5 + x, 365 + y, 0);
						glVertex3f(182.5 + x, 367.5 + y, 0);
						y = y - 66;
						x = x + 37;

						glFlush();
						glEnd();
						for (k = 0; k <= 100; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				glFlush();
			}
			else if (getPath[i] == 3) {
				glFlush();
				if (getPath[i + 1] == 1) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 31) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(297.5 + x, 382.5 + y, 0);
						glVertex3f(275 + x, 372.5 + y, 0);
						glVertex3f(277.5 + x, 367.5 + y, 0);
						glVertex3f(300 + x, 377.5 + y, 0);
						glVertex3f(297.5 + x, 382.5 + y, 0);
						y = y - 25;
						x = x - 50;

						glFlush();
						glEnd();
						for (k = 0; k <= 100; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else if (getPath[i + 1] == 2) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 60) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(290 + x, 385 + y, 0);
						glVertex3f(287.5 + x, 380 + y, 0);
						glVertex3f(265 + x, 387.5 + y, 0);
						glVertex3f(267.5 + x, 392.5 + y, 0);
						glVertex3f(290 + x, 385 + y, 0);
						y = y + 6.25;
						x = x - 30;

						glFlush();
						glEnd();
						for (k = 0; k <= 100; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else if (getPath[i + 1] == 4) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 31) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(295 + x, 372.5 + y, 0);
						glVertex3f(282.5 + x, 350 + y, 0);
						glVertex3f(287.5 + x, 347.5 + y, 0);
						glVertex3f(300 + x, 370 + y, 0);
						glVertex3f(295 + x, 372.5 + y, 0);
						y = y - 66.25;
						x = x - 37.5;

						glFlush();
						glEnd();
						for (k = 0; k <= 100; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 35) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(310 + x, 385 + y, 0);
						glVertex3f(313 + x, 360 + y, 0);
						glVertex3f(317.5 + x, 362.5 + y, 0);
						glVertex3f(315 + x, 387.5 + y, 0);
						glVertex3f(310 + x, 385 + y, 0);
						y = y - 70;
						x = x + 5;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}

					glFlush();
				}
				glFlush();
			}
			else if (getPath[i] == 4) {
				glFlush();
				if (getPath[i + 1] == 1) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 45) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(127.5 + x, 115 + y, 0);
						glVertex3f(112.5 + x, 135 + y, 0);
						glVertex3f(107.5 + x, 132.5 + y, 0);
						glVertex3f(122.5 + x, 112.5 + y, 0);
						glVertex3f(127.5 + x, 115 + y, 0);
						y = y + 31.25;
						x = x - 25;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else if (getPath[i + 1] == 2) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 35) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(210 + x, 125 + y, 0);
						glVertex3f(207.5 + x, 155 + y, 0);
						glVertex3f(212.5 + x, 157.5 + y, 0);
						glVertex3f(215 + x, 127.5 + y, 0);
						glVertex3f(210 + x, 125 + y, 0);
						y = y + 70;
						x = x - 5;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else if (getPath[i + 1] == 3) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 22) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(210 + x, 125 + y, 0);
						glVertex3f(222.5 + x, 145 + y, 0);
						glVertex3f(226 + x, 138 + y, 0);
						glVertex3f(215 + x, 120 + y, 0);
						glVertex3f(210 + x, 125 + y, 0);
						y = y + 45;
						x = x + 25;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}

					glFlush();
				}
				else {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 50) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(180 + x, 50 + y, 0);
						glVertex3f(205 + x, 50 + y, 0);
						glVertex3f(205 + x, 42.5 + y, 0);
						glVertex3f(180 + x, 42.5 + y, 0);
						glVertex3f(180 + x, 50 + y, 0);
						y = y;
						x = x + 40;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				glFlush();
			}
			else {
				glFlush();
				if (getPath[i + 1] == 1) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 30) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(315 + x, 120 + y, 0);
						glVertex3f(287.5 + x, 132.5 + y, 0);
						glVertex3f(282.5 + x, 127.5 + y, 0);
						glVertex3f(310 + x, 115 + y, 0);
						glVertex3f(315 + x, 120 + y, 0);
						y = y + 25;
						x = x - 45;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}

					glFlush();
				}
				else if (getPath[i + 1] == 2) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 30) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(362.5 + x, 130 + y, 0);
						glVertex3f(350 + x, 150 + y, 0);
						glVertex3f(345 + x, 147.5 + y, 0);
						glVertex3f(357.5 + x, 127.5 + y, 0);
						glVertex3f(362.5 + x, 130 + y, 0);
						y = y + 60;
						x = x - 35;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}

					glFlush();
				}
				else if (getPath[i + 1] == 3) {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 35) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(385 + x, 125 + y, 0);
						glVertex3f(382.5 + x, 155 + y, 0);
						glVertex3f(387.5 + x, 157.5 + y, 0);
						glVertex3f(390 + x, 127.5 + y, 0);
						glVertex3f(385 + x, 125 + y, 0);
						y = y + 70;
						x = x - 5;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}
					glFlush();
				}
				else {
					x = 0;
					y = 0;
					x = m[i][i + 1] * y;
					for (j = 0; j < 125; j = j + 60) {
						glBegin(GL_POLYGON);
						glColor3f(1.0, 0.0, 0.0);
						glVertex3f(295 + x, 95 + y, 0);
						glVertex3f(270 + x, 90 + y, 0);
						glVertex3f(272.5 + x, 85 + y, 0);
						glVertex3f(297.5 + x, 90 + y, 0);
						glVertex3f(295 + x, 95 + y, 0);
						y = y - 5;
						x = x - 35;

						glFlush();
						glEnd();
						for (k = 0; k <= 300; k++) {
							delay1();
						}
						glFlush();
					}

					glFlush();
				}
				glFlush();
			}
			i++;
			glFlush();
		}
	}
	for(ik=0;ik<1000;ik++)
	glFlush();
	
	
}

void display3() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	drawString1(135, 200, 0, " CALCULATING BEST PATH ");
	glLineWidth(3);

	for (i = 0; i < 300; i = i + 25) {
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(125 + i, 190, 0);
		glVertex3f(150 + i, 190, 0);
		glEnd();
		for (j = 0; j <= 100; j++) {
			delay1();
		}
		glFlush();
	}
	glFlush();
	for (i = 0; i <= 100; i++) {
		delay1();
	}
	for (i = 0; i <= 100; i++) {
		delay1();
	}
	for (i = 0; i <= 100; i++) {
		delay1();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	callPath(a, b);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	sources();
	
	pathgen();

}
void mykey(unsigned char key, int x, int y)
{
	if(key=='d')
	{
		uu=uu+5;
	}



	if(key=='R' || key == 'r')
	{
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(4096, 4096);
								
		glutCreateWindow("Plane");
		init();
	
		glutDisplayFunc(takeoff);
		glutIdleFunc(delay);
		glutFullScreen();
		glutMainLoop();
	}



	if(key=='s' || key == 'S')
	{
		glutDisplayFunc(takeoff);

		glutPostRedisplay();
	}

	if(key == 'N' || key == 'n')
	{

	
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(4096, 4096);
								
		glutCreateWindow("Plane");
		init();
	
		glutDisplayFunc(car);
		glutIdleFunc(delay);
		glutMainLoop();

	}
	if ((key == 'P' || key == 'p')) 
	{
		flag = 1;
		glFlush();
		glClearColor(0.0, 0.0, 0.0, 0.0);
		sources();
		
		glColor3f(0.0, 0.0, 1.0);
		drawString2(385, 235, 0, " Enter the number for Source Node");
		drawString2(385, 225, 0, " 1, 2, 3, 5");
		
		glFlush();
	}
	else if (key == '1' || key == '2' || key == '3'  || key == '4' || key == '5') {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		sources();
		
		glColor3f(0.0, 0.0, 1.0);

		if (flag == 1) {
			flag = 2;
			drawString2(385, 235, 0, " Enter the number for Destination Node");
			drawString2(385, 225, 0, "	4 ");

			if (key == '1') {
				a = 1;
			}
			else if (key == '2') {
				a = 2;
			}
			else if (key == '3') {
				a = 3;
			}
			else if (key == '4') {
				a = 4;
			}
			else {
				a = 5;
			}

		}
		else if (flag == 2) {
			if (key == '1') {
				b = 4;
			}
			else if (key == '2') {
				b = 4;
			}
			else if (key == '3') {
				b = 4;
			}
			else if (key == '4') {
				b = 4;
			}
			else {
				b = 4;
			}

			display3();
		}
		else {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glFlush();
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glFlush();
			glColor3f(0.0, 0.0, 1.0);
			drawString1(100, 400, 0, " Invalid Key Pressed ");
			glFlush();
			for (i = 0; i <= 500; i++) 
			{
				delay1();
			}
			for (i = 0; i <= 500; i++) 
			{
				delay1();
			}
			
		}
		glFlush();
	}
}

void display() {
	distanceMatrix();
	display2();
}


int main(int argc,char *argv[]) 
{
	int i,j;
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(4096, 4096);
			

	glutCreateWindow("The Survivor");
	init();
	

	glutDisplayFunc(coverpage);
	glutIdleFunc(delay);
	
	glutKeyboardFunc(mykey);
	//glutSpecialFunc(specialkey);
	
	glutMainLoop();
	
}
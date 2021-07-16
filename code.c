#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#define MAX 8

struct horse
{
		int startx,starty,height, width, no, col;
		int x[6], y[6];
};
typedef struct horse horse;

horse stable[MAX+1];
int mx, my, finish, winner;


void setvalues(horse *h, int a, int b, int n, int c, int hh,int w);
void erase(horse *h);
void move(horse *h, int dx, int dy);
void draw(horse *h);
void RaceInit();
void drawCourse();

main()
{
	int gd=DETECT, gm, dig, sgn,oldcol;

	char stop='y', str[25];
	char *w;

        initgraph(&gd, &gm, "c:\\tcpp");


	oldcol=getcolor();
        mx = getmaxx();
        my = getmaxy();

	do
	{
		cleardevice();

		settextstyle(SANS_SERIF_FONT, 0, 0);
		setusercharsize(1,3,1,3);
		settextjustify(RIGHT_TEXT, CENTER_TEXT);
		outtextxy(mx-20,my-20, "Developed by xxxxx");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setusercharsize(2,3,2,3);

		setfillstyle(SOLID_FILL,RED);
		setcolor(RED);
		pieslice(mx/2-200, 20, 0, 360, 15);
		pieslice(mx/2+200, 20, 0, 360, 15);
		bar(mx/2-200,5, mx/2+200, 35);
		setcolor(WHITE);

		outtextxy(mx/2,17, "Casino Royale");
		settextjustify(0,0);

		strcpy(str,"WINNER IS ");


	        RaceInit();
	        drawCourse();

		settextstyle(3,0,0);
		setusercharsize(1,3,1,3);

		outtextxy(20, my-45, "Press a key to start");
		getch();
		winner = play();
		w =fcvt(winner, 0, &dig, &sgn);
		strcat(str, w);

		setfillstyle(SOLID_FILL,RED);
		setcolor(RED);
		pieslice(mx/2-200, my-80, 0, 360, 20);
		pieslice(mx/2+200, my-80, 0, 360, 20);
		bar(mx/2-200,my-100, mx/2+200, my-60);
		settextstyle(1,0,0);
		setusercharsize(3,2,3,2);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		setcolor(WHITE);
		outtextxy(mx/2,my-90, str);
		settextstyle(3,0,0);
		setcolor(oldcol);
		setusercharsize(1,3,1,3);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		outtextxy(20, my-30, "press 'y' to continue");
		stop = getch();
	}while(stop=='y' || stop=='Y');

	closegraph();
}


void RaceInit()
{
        int x1=10, y1=50,i;
	winner=0;

	finish = mx - 20;



	for(i=1; i<=MAX; i++)
	{
		if(i==8)
			setvalues(&stable[i],x1,y1,i, 14,25,60);
		else if(i==1)
			setvalues(&stable[i],x1,y1,i, 13,25,60);
		else if(i==4)
			setvalues(&stable[i],x1,y1,i, LIGHTBLUE,25,60);

		else if(i==7)
			setvalues(&stable[i],x1,y1,i, LIGHTGRAY,25,60);

		else
			setvalues(&stable[i],x1,y1,i, i,25,60);
		y1 += 40;
	}
}

void drawCourse()
{
	int i, laney;
	for(i=1; i<=MAX; i++)
		erase(&stable[i]);

	rectangle(0,0,mx,my);
	line(finish,0, finish,my-50);
	line(0,my-50, mx,my-50);

	settextstyle(3,0,0);
	setusercharsize(1,1,1,1);
	settextjustify(0,0);

	for(i=1; i<=MAX; i++)
	{
		draw(&stable[i]);
	}
	laney = 40;
	setlinestyle(DASHED_LINE, 0, 1);
	for(i=1; i<=MAX+1; i++)
	{
		line(0, laney, finish, laney);
		laney+=40;
	}
	line(70,40, 70,360);
	setlinestyle(SOLID_LINE, 0, 1);
}

int play()
{
	int next;
	unsigned freq=20;
	randomize();
	winner=0;

	while(1)
	{
		next = random(MAX+1);
		if(next==0)
			continue;

		sound(freq);
		freq += 10;
		delay(30);
		if(freq>=300)
		{
			freq = 20;
		}
		move(&stable[next], 5, 0);
		if( endpoint(&stable[next]) >= finish)
		{
			nosound();
			return(next);
		}

	}
	nosound();
	return(0);
}


void setvalues(horse *h, int a, int b, int n, int c, int hh,int w)
{
	int i,w2,h2;
	h->startx=a;
	h->starty=b;
	h->height=hh;
	h->width = w;
	h->no = n;
	h->col = c;
	w2=h->width/2;
	h2=h->height/2;

	h->x[0]=h->startx; 		h->y[0]=h->starty;
	h->x[1]=h->startx+w2;	        h->y[1]=h->starty;
	h->x[2]=h->startx+h->width;	h->y[2]=h->starty+h2;
	h->x[3]=h->startx+w2; 		h->y[3]=h->starty+h->height;
	h->x[4]=h->startx;		h->y[4]=h->starty+h->height;

}

void transpose(horse *h, int dx, int dy)
{
	int i;
	h->startx += dx;
	h->starty += dy;
	for(i=0; i<5; i++)
	{
		h->x[i] += dx;
		h->y[i] += dy;
	}
}

void erase(horse *h)
{
	int savecol = h->col;
	int bkcolor = getbkcolor();
	h->col = bkcolor;
	draw(h);
	h->col = savecol;
}

void move(horse *h, int dx, int dy)
{
	erase(h);
	transpose(h,dx,dy);
	draw(h);
}

int endpoint(horse *h)
{
	return h->x[2];
}


void draw(horse *h)
{
	char *str;
	struct linesettingstype old;
	int oc,w2,h2;
	int dx[12];
        int dig, sgn, cx,cy;

	oc = getcolor();
	setcolor(h->col);

	w2=h->width/2;
	h2=h->height/2;

	dx[0]=h->startx; 		dx[1]=h->starty;
	dx[2]=h->x[0]+w2;		dx[3]=h->y[0];
	dx[4]=h->x[0]+h->width;		dx[5]=h->y[0]+h2;
	dx[6]=h->x[0]+w2; 		dx[7]=h->y[0]+h->height;
	dx[8]=h->x[0];			dx[9]=h->y[0]+h->height;
	dx[10]=h->x[0];			dx[11]=h->y[0];

	setfillstyle(SOLID_FILL, h->col);
	drawpoly(6, dx);
	fillpoly(6, dx);

	cx = h->startx + (h->width/2);
	cy = h->starty+ (h->height/2);

	str = fcvt(h->no, 0,&dig,&sgn);
	settextstyle(3,0,0);
	setusercharsize(2,3,2,3);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(BLACK);
	outtextxy(cx,cy, str);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(oc);
	settextstyle(3,0,0);
	setusercharsize(1,1,1,1);
}

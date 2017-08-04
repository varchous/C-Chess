#include<iostream.h>
#include<math.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<fstream.h>
#include<iomanip.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct mousestate{
	   int x,y;
	   int b;
};

void mouseoff()
{
    _asm{
	 mov ax,0
	 int 0x33
	}
}

void mouseon()
{
	_asm{
	 mov ax,1
	 int 0x33
	}
}

void MoveMouseCursor(int x,int y){
	_asm{
	 mov ax,4
	 mov cx,x
	 mov dx,y
	 int 0x33
	}
}

void getmousestate(mousestate &s){
	_asm{
	 mov ax,3
	 int 0x33
	}
	#if defined(_COMPACT_) || defined (_LARGE_) || defined (_HUGE_)
	_asm{
	 push es
	 push di
	 les di,dword ptr s
	 mov es:[di],cx
	 mov es:[di+2],dx
	 mov es:[di+4],bx  //knopka
	 pop di
	 pop es
	}
	#else
	_asm{
	 push di
	 mov di,word ptr s
	 mov [di],cx
	 mov [di+2],dx
	 mov[di+4],bx
	 pop di
	}
	#endif
}

class Figura;

struct Kletka
{
 int x;
 int y;
 int i1;
 int j1;
 int cvet;
 int cvetf;
 int f;
};

class Pole
{
 private:
 enum {n=8};
 Kletka pole[n][n];
 public:
 void Draw();
 Pole();
 void Vivod();
 Kletka& getxy(int, int);
 int getcolor(int,int);
 int Search();
};

class Figura
{
 public:
 void Destroy(Kletka&);
};
void Figura::Destroy(Kletka& k)
{
 k.cvetf=2;
 k.f=0;
 int x1=k.x,y1=k.y;
 int x2=k.x+50,y2=k.y+50;
 setlinestyle(0,0,1);
 if(k.cvet==0)setfillstyle(1,15);
 else  setfillstyle(1,4);
 bar(x1,y1,x2,y2);
}

class Slon : public Figura
{
 private:
 int cvet;
 public:
 Slon(int);
 void Drawslon(Kletka&);
 void Hod(Kletka&,int,int,Pole&);
};

void Slon::Hod(Kletka&k,int x, int y,Pole&p)
{
 if( p.getcolor(x,y)==cvet) return;
 if(abs(k.i1-x)==abs(k.j1-y))
 {
  int s1,s2;
  if(k.i1>x) {s1=k.i1-1; s2=k.j1-1;}
  else {s1=x-1; s2=y-1;}
  for(int kol=abs(x-k.i1)-1;kol>0;kol--)
  {
   if(p.getcolor(s1,s2)==1||p.getcolor(s1,s2)==0) return;
   s1--;
   s2--;
  }
 delay(500);
 Destroy(p.getxy(k.i1,k.j1));
 delay(500);
 Destroy(p.getxy(x,y));
 delay(500);
 Drawslon(p.getxy(x,y));
 }
}

Slon::Slon(int  x)
{
 if (x>1||x<0) return;
 cvet=x;
}

void Slon::Drawslon(Kletka& k)
{
 k.cvetf=cvet;
 k.f=4;
 int x1=k.x+17, x2=k.x+33;
 int y1=k.y+42,y2=k.y+42;
 if(cvet==1)  setcolor(1);
 else setcolor(7);
 setlinestyle(0,0,1);
 line(x1,y1,x2,y2);
 line(x1,y2,x1,y1-7);
 line(x2,y2,x2,y2-7);
 line(x1,y1-7,x1-2,y1-15);
 line(x2,y2-7,x2+2,y2-15);
 ellipse(x1+8,y1-15,1,180,10,21);
  putpixel(x1+15,y1-10,2);
	if(cvet==1){
		  setfillstyle(1,1);
		  floodfill(x1+15,y1-10,1);
		 }
  else
  {
   setfillstyle(1,7);
   floodfill(x1+15,y1-10,7);
  }
  setcolor(14);
   setlinestyle(0,0,1);
  line(x1+5,y1-25,x1+11,y1-25);
  line(x1+8,y1-30,x1+8,y1-20);
}

class King : public Figura
 {
 private:
 int cvet;
 public:
 King(int);
 void Drawking(Kletka&);
 void Hod(Kletka&,int,int,Pole&);
};

void King::Hod(Kletka& k,int x, int y,Pole&p)
{
 if( p.getcolor(x,y)==cvet) return;
  if(k.i1==x&&abs(k.j1-y)==1 ||k.j1==y&&abs(k.i1-x)==1 || abs(k.i1-x)==1&&abs(k.j1-y)==1)
 {
 delay(500);
 Destroy(p.getxy(k.i1,k.j1
 ));
 delay(500);
 Destroy(p.getxy(x,y));
 delay(500);
 Drawking(p.getxy(x,y));
 }
}

King::King(int x)
{
  if (x>1||x<0) return;
 cvet=x;
}

void King::Drawking(Kletka& k)
{
 k.cvetf=cvet;
 k.f=6;
 int x1=k.x+10, x2=k.x+40;
 int y1=k.y+42,y2=k.y+42;
 if(cvet==1)  setcolor(1);
 else setcolor(7);
 line(x1,y1,x2,y2);
 line(x1,y2,x1,y1-15);
 line(x2,y2,x2,y2-15);
 ellipse(x1+7,y1-8,20,160,8,21);
 ellipse(x2-7,y2-8,20,160,8,21);
 setlinestyle(0,0,3);
 line(x1+15,y1-15,x1+15,y1-35);
 line(x1+12,y1-31,x1+18,y1-31);
 putpixel(x1+15,y1-10,2);
	if(cvet==1){
		  setfillstyle(1,1);
		  floodfill(x1+15,y1-10,1);
		 }
  else
  {
   setfillstyle(1,7);
   floodfill(x1+15,y1-10,7);
  }
}

class Ferz : public Figura
{
 private:
 int cvet;
 public:
 Ferz(int);
 void Drawferz(Kletka&);
 void Hod(Kletka&,int,int,Pole&);
};

void Ferz::Hod(Kletka& k,int x, int y,Pole&p)
{
 if( p.getcolor(x,y)==cvet) return;
 if(k.i1==x||k.j1==y||abs(k.i1-x)==abs(k.j1-y))
 {
  if(abs(k.i1-x)==abs(k.j1-y))
 {
  int s1,s2;
  if(k.i1>x) {s1=k.i1-1; s2=k.j1-1;}
  else {s1=x-1; s2=y-1;}
  for(int kol=(x-k.i1)-1;kol>0;kol--)
  {
   if(p.getcolor(s1,s2)==1||p.getcolor(s1,s2)==0) return;
   s1--;
   s2--;
  }
 }
  if(k.j1==y)
  { int s=0;
	if(k.i1>x) s=k.i1-1;
	else s=x-1;
	for(int kol=(abs(x-k.i1)-1);kol>0;kol--)
	{
	 if(p.getcolor(s,k.j1)==1||p.getcolor(s,k.j1)==0) return;
	 s--;
	}
  }

  if(k.i1==x)
  { int s=0;
  if(k.j1>y) s=k.j1-1;
  else s=y-1;
  for(int kol=(abs(y-k.j1)-1);kol>0;kol--)
  {
  if(p.getcolor(k.i1,s)==1||p.getcolor(k.i1,s)==0) return;
   s--;
  }
 }
 delay(500);
 Destroy(p.getxy(k.i1,k.j1));
 delay(500);
 Destroy(p.getxy(x,y));
 delay(500);
 Drawferz(p.getxy(x,y));
 }
}

Ferz::Ferz(int x)
{

 if (x>1||x<0) return;
 cvet=x;
}

void Ferz::Drawferz(Kletka& k)
{
  k.cvetf=cvet;
  k.f=5;
  int x1=k.x+5, x2=k.x+42;
  int y1=k.y+40,y2=k.y+40;
  if(cvet==1)  setcolor(1);
  else setcolor(7);
  setlinestyle(0,0,1);
  line(x1+3,y1,x2-3,y2);
  line(x1+3,y1,x1+3,y1-10);
  line(x2-3,y2,x2-3,y2-10);
  line(x1+3,y1-10,x1,y1-25);
  setfillstyle(1,14);
  ellipse(x1+3,y1-25,10,180,2,4);
  line(x1+6,y1-25,x1+7,y1-15);
  line(x1+7,y1-15,x1+10,y1-25);
  ellipse(x1+12,y1-25,10,180,2,4);
  line(x1+14,y1-25,x1+16,y1-15);
  line(x1+16,y1-15,x1+19,y1-25);
  ellipse(x1+21,y1-25,10,180,2,4);
  line(x1+23,y1-25,x1+25,y1-15);
  line(x1+25,y1-15,x1+29,y1-25);
  ellipse(x1+32,y1-25,10,180,2,4);
  line(x1+34,y1-25,x1+33,y1-10);
  putpixel(x1+15,y1-10,2);
	if(cvet==1){
		  setfillstyle(1,1);
		  floodfill(x1+15,y1-10,1);
		 }
  else
  {
   setfillstyle(1,7);
   floodfill(x1+15,y1-10,7);
  }
}

class Ladia : public Figura
{
 private:
 int cvet;
 public:
 Ladia(int);
 void Drawladia(Kletka&);
 void Hod(Kletka&,int,int,Pole&);
};

void Ladia::Hod(Kletka& k,int x, int y,Pole&p)
{
 if(p.getcolor(x,y)==cvet) return;
  int s;
 if(k.i1==x||k.j1==y)
 {
  if(k.j1==y)
  {  s=0;
	if(k.i1>x) s=k.i1-1;
	else s=x-1;
	for(int kol=(abs(k.i1-x)-1);kol>0;kol--)
	{
	 if(p.getcolor(s,k.j1)==1||p.getcolor(s,k.j1)==0) return;
	 s--;
	}
  }
  if(k.i1==x)
  {  s=0;
	if(k.j1>y) s=k.j1-1;
  else s=y-1;
  for(int kol=(abs(k.j1-y)-1);kol>0;kol--)
  {
   if(p.getcolor(k.i1,s)==1||p.getcolor(k.i1,s)==0) return;
   s--;
  }
 }
 delay(500);
 Destroy(p.getxy(k.i1,k.j1));
 if (k.i1==x)Destroy(p.getxy(k.i1,k.j1));
 delay(500);
 Destroy(p.getxy(x,y));
 delay(500);
 Drawladia(p.getxy(x,y));
 }
}

Ladia::Ladia(int x)
{
  if (x>1||x<0) return;
  cvet=x;
}

void Ladia::Drawladia(Kletka& k)
{
  k.cvetf=cvet;
  k.f=2;
  int x1=k.x+10, x2=k.x+40;
  int y1=k.y+40,y2=k.y+40;
  if(cvet==1)  setcolor(1);
  else setcolor(7);
  setlinestyle(0,0,1);
  line(x1+7,y1,x2-7,y2);
  line(x2-7,y2,x2-7,y2-15);
  line(x1+7,y1,x1+7,y1-15);
  line(x2-7,y2-15,x2-3,y2-22);
  line(x1+7,y1-15,x1+3,y1-22);
  line(x2-3,y2-22,x2-3,y2-30);
  line(x2-3,y2-30,x2-8,y2-30);
  line(x2-8,y2-30,x2-8,y2-23);
  line(x2-8,y2-23,x2-12,y2-23);
  line(x2-12,y2-23,x2-12,y2-30);
  line(x2-12,y2-30,x2-17,y2-30);
  line(x2-17,y2-30,x2-17,y2-23);
  line(x2-17,y2-23,x2-21,y2-23);
  line(x2-21,y2-23,x2-21,y2-30);
  line(x2-21,y2-30,x1+3,y2-30);
  line(x1+3,y2-30,x1+3,y1-22);
  putpixel(x1+15,y1-10,3);
	if(cvet==1){
		  setfillstyle(1,1);
		  floodfill(x1+15,y1-10,1);
		 }
  else
  {
   setfillstyle(1,7);
	 floodfill(x1+15,y1-10,7);
  }
}
class Kon  : public Figura
{
 private:
 int cvet;
 public:
 Kon(int );
 void Drawkon(Kletka&);
 void Hod(Kletka&,int,int,Pole&);
};
void Kon::Hod(Kletka& k,int x, int y,Pole&p)
{
 if( p.getcolor(x,y)==cvet) return;
 if(abs(k.i1-x)==1&&abs(k.j1-y)==2||abs(k.i1-x)==2&&abs(k.j1-y)==1)
 {
 delay(500);
 Destroy(p.getxy(k.i1,k.j1));
 delay(500);
 Destroy(p.getxy(x,y));
 delay(500);
 Drawkon(p.getxy(x,y));
 }
}
Kon::Kon(int x)
{
 if (x>1||x<0) return;
  cvet=x;
}
void Kon::Drawkon(Kletka& k)
{
  k.cvetf=cvet;
  k.f=3;
  int x1=k.x+10, x2=k.x+40;
  int y1=k.y+40,y2=k.y+40;
  if(cvet==1)  setcolor(1);
  else setcolor(7);
  line(x1,y1,x2,y2);
  line(x1,y1,x1+5,y1-20);
  line(x2,y2,x2-13,y2-15);
  line(x1+5,y1-20,x1+10,y1-25);
  line(x1+10,y1-25,x1+27,y1-25);
  line(x2-13,y2-15,x2-3,y2-15);
  line(x1+27,y1-25,x2-3,y2-15);
  putpixel(x1+10,y1-10,3);
	if(cvet==1){
		  setfillstyle(1,1);
		  floodfill(x1+10,y1-10,1);
		 }
  else
  {
   setfillstyle(1,7);
   floodfill(x1+10,y1-10,7);
  }
  setcolor(14);
  line(x1+15,y1-23,x1+17,y1-23);
  putpixel(x1+16,y1-23,1);
  setlinestyle(0,0,1);
  line(x1+27,y1-17,x1+20,y1-17);
}

class Peshka : public Figura
{ private:
  int cvet;
  public:
  void Vivod();
  Peshka(int);
  void Drawpeshka(Kletka&);
  void Hod(Kletka&,int,int,Pole&);
};
void Peshka::Hod(Kletka& k,int x, int y,Pole&p)
{
 if( p.getcolor(x,y)==cvet) return ;
 if(k.j1==y&&abs(k.i1-x)==1&&cvet==0&&k.i1>x&&p.getxy(x,y).cvetf==2 || k.j1==y&&k.i1==6&&cvet==0&&abs(k.i1-x)==2&&k.i1>x&&p.getxy(x,y).cvetf==2||
    k.j1==y&&abs(k.i1-x)==1&&cvet==1&&x>k.i1&&p.getxy(x,y).cvetf==2 || k.j1==y&&k.i1==1&&cvet==1&&abs(k.i1-x)==2&&x>k.i1&&p.getxy(x,y).cvetf==2  )
 {
 delay(500);
 Destroy(p.getxy(k.i1,k.j1));
 delay(500);
 Destroy(p.getxy(x,y));
 delay(500);
 Drawpeshka(p.getxy(x,y));
 }
 if(p.getcolor(x,y)==1&&cvet==0&&abs(k.i1-x)==1&&abs(k.j1-y)==1&&k.i1>x || p.getcolor(x,y)==0&&cvet==1&&abs(k.i1-x)==1&&abs(k.j1-y)==1&&x>k.i1)
 {
  delay(500);
 Destroy(p.getxy(k.i1,k.j1));
 delay(500);
 Destroy(p.getxy(x,y));
 delay(500);
 Drawpeshka(p.getxy(x,y));
 }
}
Peshka::Peshka(int x)
{
  if (x>1||x<0) return;
  cvet=x;
}
void Peshka::Drawpeshka(Kletka& k)
{
  k.cvetf=cvet;
  k.f=1;
  int x1=k.x+10, x2=k.x+40;
  int y1=k.y+40,y2=k.y+40;
  if(cvet==1)  setcolor(1);
  else setcolor(7);
  line(x1,y1,x2,y2);
  line(x1,y1,x1+10,y1-20);
  line(x2,y2,x2-10,y2-20);
  arc(x1+15,y1-25,325,220,8);
   putpixel(x1+15,y2-15,14);
  if(cvet==1){
		  setfillstyle(1,1);
		  floodfill(x1+15,y2-15,1);
		 }
  else
  {
   setfillstyle(1,7);
   floodfill(x1+15,y2-15,7);
  }
}

int Pole::Search()
{
 const int n=7;
 int king0=0,king1=0;
 for(int i=0;i<=n;i++)
 {
 for(int j=0;j<=n;j++)
 {
  if(pole[i][j].cvetf==1&&pole[i][j].f==6) king1=1;
  if(pole[i][j].cvetf==0&&pole[i][j].f==6) king0=1;
 }
 }
 if(king1==0) {settextstyle(0,0,5); setcolor(2);outtextxy(40,160,"White win"); return  0;}
 if(king0==0) {settextstyle(0,0,5); setcolor(2);outtextxy(40,160,"Black win"); return  0;}
 return 1;
}
void Pole::Draw()
{
 settextstyle(0,0,0);
 int x1=10,x2=421,x3=20,x4=411;
 int y1=20,y2=30,y3=431,y4=421;
  do
  {
   setcolor(7);
   setlinestyle(0,0,3);

   line(x1,y1,x1,y2);
   line(x1,y3,x1,y4);

   line(x2,y1,x2,y2);
   line(x2,y3,x2,y4);

   line(x1,y1,x3,y1);
   line(x2,y1,x4,y1);

   line(x1,y3,x3,y3);
   line(x2,y3,x4,y3);

   y2+=1;
   y4-=1;
   x3+=1;
   x4-=1;
  }
  while(y2<=230);

  x1=12; x2=62; x3=369; x4=419;
  y1=22; y2=72; y3=379; y4=429;

  for(int i=1;i<=4;i++)
  {
   if(i%2==1) {  x1=12;
		 x2=62;
		 x3=369;
			 x4=419;
		  }
   else       { x1=369;
			x2=419;
		x3=12;
		x4=62;
		  }
	for(int j=1;j<=8;j++)
	{

	if(i%2==0){
		   if(j%2==1) setfillstyle(1,15);
		   else  setfillstyle(1,4);
		  }

	if(i%2==1){
		   if(j%2==1) setfillstyle(1,15);
		   else  setfillstyle(1,4);
			 }
	bar(x1,y1,x2,y2);
	bar(x3,y3,x4,y4);

	if(i%2==1) { x1+=51;
		 x2+=51;
		 x3-=51;
		 x4-=51;
		   }
	else       { x1-=51;
		 x2-=51;
		 x3+=51;
		 x4+=51;
		   }

   }
   y1+=51;
   y2+=51;
   y3-=51;
   y4-=51;
  }
  setcolor(15);
  char  b[2];
  int a=8;
  char c[2]="";

  x1=1;  x2=35;
  y1=45; y2=9;
  char ch='A';
  for(i=1;i<=8;i++,ch++)
  {

   b[0]=ch;b[1]=0;
   outtextxy(x1,y1,itoa(a,c,10));
   outtextxy(x2,y2,b);
   a--;
   y1+=51;
   x2+=51;
  }
}
Kletka& Pole::getxy(int i, int j)
{
 Kletka *temp=&pole[i][j];
 return *temp;
}

int Pole::getcolor(int i,int j)
{
 return pole[i][j].cvetf;
}
void Pole::Vivod()
{
 const int n=7;
 for(int i=0;i<=n;i++)
 {
 for(int j=0;j<=n;j++)
 {
 cout<<pole[i][j].cvetf<<" ";
 }
 cout<<endl;
 }
}
Pole::Pole()
{
 const int n=7;
 int x1=12,y1=22;
 for(int i=0;i<=n;i++)
 {
  for(int j=0;j<=n;j++)
  {
   pole[i][j].x=x1;
   pole[i][j].y=y1;
   x1+=51;
   if((i+j)%2==0) pole[i][j].cvet=0;
   else pole[i][j].cvet=1;
   pole[i][j].cvetf=2;
   pole[i][j].i1=i;
   pole[i][j].j1=j;
  }
  y1+=51;
  x1=12;
  }
}

void Zastavka();
void Game();
void Returnmouse(int&,int&);
void Returnmouse(int& x1,int& y1)
{
  mouseon();
  int flag1=1;
  while(flag1==1)
  {
  mousestate m;
  getmousestate(m);
  if(m.b==1){
  flag1=0; m.b=0; x1=m.x; y1=m.y;}
  }
  x1=(x1-12)/51;
  y1=(y1-22)/51;
}

void main()
{ clrscr();
  int gdrive=DETECT,gmode;
  initgraph(&gdrive,&gmode,"C:\\BorlandC\\BGI");
  setbkcolor(8);
  Zastavka();
  Game();
  getch();
  closegraph();
}

void Zastavka()
{
 int x1=10,x2=421,x3=20,x4=411;
 int y1=20,y2=30,y3=431,y4=421;
  do
  {
   setcolor(7);
   setlinestyle(0,0,3);

   line(x1,y1,x1,y2);
   line(x1,y3,x1,y4);

   line(x2,y1,x2,y2);
   line(x2,y3,x2,y4);

   line(x1,y1,x3,y1);
   line(x2,y1,x4,y1);

   line(x1,y3,x3,y3);
   line(x2,y3,x4,y3);

   delay(10);
   y2+=1;
   y4-=1;
   x3+=1;
   x4-=1;
  }
  while(y2<=230);

  x1=12; x2=62; x3=369; x4=419;
  y1=22; y2=72; y3=379; y4=429;

  for(int i=1;i<=4;i++)
  {
   if(i%2==1) {  x1=12;
		 x2=62;
		 x3=369;
		 x4=419;
		  }
   else       { x1=369;
		x2=419;
		x3=12;
		x4=62;
		  }
	for(int j=1;j<=8;j++)
	{
	 delay(150);
	if(i%2==0){
		   if(j%2==1) setfillstyle(1,15);
		   else  setfillstyle(1,4);
		  }

	if(i%2==1){
		   if(j%2==1) setfillstyle(1,15);
		   else  setfillstyle(1,4);
		  }

	bar(x1,y1,x2,y2);
	bar(x3,y3,x4,y4);

	if(i%2==1) { x1+=51;
		 x2+=51;
		 x3-=51;
		 x4-=51;
		   }
	else       { x1-=51;
		 x2-=51;
		 x3+=51;
		 x4+=51;
		   }

   }
   y1+=51;
   y2+=51;
   y3-=51;
   y4-=51;
  }
  setcolor(15);
  char  b[2];
  int a=8;
  char c[2]="";

  x1=1;  x2=35;
  y1=45; y2=9;
  char ch='A';
  for(i=1;i<=8;i++,ch++)
  {
	 delay(200);
   b[0]=ch;b[1]=0;
   outtextxy(x1,y1,itoa(a,c,10));
   outtextxy(x2,y2,b);
   a--;
   y1+=51;
   x2+=51;
  }

  Pole p1;
  Ladia l1(1),l2(0); int l=0;
  Kon ko1(1),ko2(0); int ko=1;
  Slon s1(1),s2(0);  int s=2;
  Ferz f1(1),f2(0);  int f=3;
  King k1(1),k2(0);  int k=4;
   for( i=1;i<=2;i++)
   {
   l1.Drawladia(p1.getxy(0,l));
   l2.Drawladia(p1.getxy(7,l));
   l+=7;
   delay(250);
   }

	for( i=1;i<=2;i++)
   {
   ko1.Drawkon(p1.getxy(0,ko));
   ko2.Drawkon(p1.getxy(7,ko));
   ko+=5;
   delay(250);
   }

	for(i=1;i<=2;i++)
   {
   s1.Drawslon(p1.getxy(0,s));
   s2.Drawslon(p1.getxy(7,s));
   s+=3;
   delay(250);
   }
   f1.Drawferz(p1.getxy(0,f));
   f2.Drawferz(p1.getxy(7,f));
   delay(350);
   k1.Drawking(p1.getxy(0,k));
   k2.Drawking(p1.getxy(7,k));
   Peshka pe1(1),pe2(0);
  int j=7;
  for(i=0;i<=3;i++,j--)
  {
  delay(250);
  pe1.Drawpeshka(p1.getxy(1,i));
  pe2.Drawpeshka(p1.getxy(6,i));
  pe1.Drawpeshka(p1.getxy(1,j));
  pe2.Drawpeshka(p1.getxy(6,j));
  }
  delay(500);
  setcolor(2);
  settextstyle(0,0,4);
  outtextxy(40,160,"Start Game?");
  delay(500);
  settextstyle(0,0,3);
  outtextxy(40,240,"Yes(Y)");
  outtextxy(250,240,"No(N)");
  char ch2[2];
  int flag=0;
  do
  {
  cin.getline(ch2,2);
  switch (ch2[0])
  {
   case 'n':exit(1);
   case 'N':exit(1);
   case 'Y':flag=1;break;
   case 'y':flag=1;break;
  }
  }
  while(flag!=1);
  cleardevice();
}
void Game()
{
  Pole p;
  p.Draw();
  Ladia l1(1),l2(0),l3(1),l4(0); int l=0;
  l1.Drawladia(p.getxy(0,l));
  l2.Drawladia(p.getxy(7,l));
  l+=7;
  l3.Drawladia(p.getxy(0,l));
  l4.Drawladia(p.getxy(7,l));

  Kon ko1(1),ko2(0),ko3(1),ko4(0); int ko=1;
  ko1.Drawkon(p.getxy(0,ko));
  ko2.Drawkon(p.getxy(7,ko));
  ko+=5;
  ko3.Drawkon(p.getxy(0,ko));
  ko4.Drawkon(p.getxy(7,ko));


  Slon s1(1),s2(0),s3(1),s4(0);  int s=2;
  s1.Drawslon(p.getxy(0,s));
  s2.Drawslon(p.getxy(7,s));
  s+=3;
  s3.Drawslon(p.getxy(0,s));
  s4.Drawslon(p.getxy(7,s));

  Ferz f1(1),f2(0);  int f=3;
  f1.Drawferz(p.getxy(0,f));
  f2.Drawferz(p.getxy(7,f));

  King k1(1),k2(0);  int k=4;
  k1.Drawking(p.getxy(0,k));
  k2.Drawking(p.getxy(7,k));
  Peshka pe1(1),pe2(0); int pe=0;
  pe1.Drawpeshka(p.getxy(1,pe));
  pe2.Drawpeshka(p.getxy(6,pe));
  pe++;
  pe1.Drawpeshka(p.getxy(1,pe));
  pe2.Drawpeshka(p.getxy(6,pe));
  pe++;
  pe1.Drawpeshka(p.getxy(1,pe));
  pe2.Drawpeshka(p.getxy(6,pe));
  pe++;
  pe1.Drawpeshka(p.getxy(1,pe));
  pe2.Drawpeshka(p.getxy(6,pe));
  pe++;
  pe1.Drawpeshka(p.getxy(1,pe));
  pe2.Drawpeshka(p.getxy(6,pe));
  pe++;
  pe1.Drawpeshka(p.getxy(1,pe));
  pe2.Drawpeshka(p.getxy(6,pe));
  pe++;
  pe1.Drawpeshka(p.getxy(1,pe));
  pe2.Drawpeshka(p.getxy(6,pe));
  pe++;
  pe1.Drawpeshka(p.getxy(1,pe));
  pe2.Drawpeshka(p.getxy(6,pe));
  mouseon();
  int flag=0;
 while(p.Search()!=0||!kbhit())
 {
  if(flag==0) {settextstyle(0,0,1); setcolor(15); outtextxy(500,10,"Turn");}
  if(flag==1) {settextstyle(0,0,1); setcolor(1); outtextxy(500,10,"Turn");}
  int cv=2,ch=-1;
  mouseon();
  int x1,y1;
  Returnmouse(x1,y1);
  int x2,y2;
  delay(500);
  Returnmouse(x2,y2);
  if( p.getxy(y1,x1).f==0) ch=0;
  else {ch=p.getxy(y1,x1).f; cv=p.getxy(y1,x1).cvetf; }
  if(cv==0&&flag==0&&p.getxy(y2,x2).cvetf!=0||cv==1&&flag==1&&p.getxy(y2,x2).cvetf!=1)
  {
  if (cv==0) flag=1;
  if (cv==1) flag=0;
  switch(ch)
  {
  case 1:{if(cv==0) pe2.Hod(p.getxy(y1,x1),y2,x2,p);
	  if(cv==1) pe1.Hod(p.getxy(y1,x1),y2,x2,p); }break;

  case 2:{if(cv==0) l2.Hod(p.getxy(y1,x1),y2,x2,p) ;
	 if(cv==1) l1.Hod(p.getxy(y1,x1),y2,x2,p) ;}break;

  case 3:{if(cv==0) ko2.Hod(p.getxy(y1,x1),y2,x2,p) ;
	  if(cv==1) ko1.Hod(p.getxy(y1,x1),y2,x2,p) ;}break;

  case 4:{if(cv==0) s2.Hod(p.getxy(y1,x1),y2,x2,p) ;
	  if(cv==1) s1.Hod(p.getxy(y1,x1),y2,x2,p) ;}break;

  case 5:{if(cv==0) f2.Hod(p.getxy(y1,x1),y2,x2,p) ;
	  if(cv==1) f1.Hod(p.getxy(y1,x1),y2,x2,p) ;}break;

  case 6:{if(cv==0) k2.Hod(p.getxy(y1,x1),y2,x2,p) ;
	  if(cv==1) k1.Hod(p.getxy(y1,x1),y2,x2,p) ;}break;
  default:break;
  }
  }
  }
}
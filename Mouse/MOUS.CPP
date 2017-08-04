#include<fstream.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
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
void main(){
	 int a=0;
	 initgraph (&a,&a,"..\\bgi");
         mouseoff();
	 mouseon();
	  while (!kbhit()){
		 mousestate s;
		 mouseon();
		 getmousestate(s);
		 if (s.x>10&&s.x<40&&s.y>30&&s.y<60){
		setcolor(s.b+3);
		/*setfillstyle(1,s.b+3);*/
		rectangle(10,30,40,60);
		delay(500);
		bar(10,30,40,60);
		if(s.b) cout<<s.x<<" "<<s.y;
		 }


	  }
}



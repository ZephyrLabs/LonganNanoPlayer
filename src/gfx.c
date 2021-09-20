#include "gfx.h"
#include "lcd.h"

void gfx_draw_line(int x1,int y1,int x2,int y2,unsigned short int color)
{
	unsigned short int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; 
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1;
	else if (delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x;
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		lcd_setpixel(uRow,uCol,color);
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

void gfx_draw_circle(unsigned short int x, unsigned short int y, unsigned short int r, unsigned short int color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		lcd_setpixel(x-b,y-a,color);             //3           
		lcd_setpixel(x+b,y-a,color);             //0           
		lcd_setpixel(x-a,y+b,color);             //1                
		lcd_setpixel(x-a,y-b,color);             //2             
		lcd_setpixel(x+b,y+a,color);             //4               
		lcd_setpixel(x+a,y-b,color);             //5
		lcd_setpixel(x+a,y+b,color);             //6 
		lcd_setpixel(x-b,y+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))                      //Determine whether the points to be drawn are too far away
		{
			b--;
		}
	}
}

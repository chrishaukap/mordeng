#include "stdafx.h"
#include <stdarg.h>                         /* var arg stuff */
#include <stdio.h>                          /* vsprintf */
#include <stdlib.h>                         /* exit */
#include <assert.h>

#include "window.h"
#include "clipping.h"

using namespace mord;

extern int main(int n,char **o);            /* real main (well...) */

int screen_x_size;                       /* screen dimensions */
int screen_y_size;
int image_size;                          /* number of pixels */
int pixel_size;                          /* in bytes */

int red_size;                            /* how many bits is there */
int green_size;                          /* occupied by each color */
int blue_size;
int red_mask;                            /* which bits are occupied */
int green_mask;                          /* by color */
int blue_mask;
int red_shift;                           /* how colors are packed into */
int green_shift;                         /* the bitmap */
int blue_shift;

HDC mem;                                 /* memory device context */
HBITMAP bmp;                             /* bitmap header */
RECT rect;                               /* "client" area dimensions */
HWND wnd;                                /* window */
HINSTANCE instance;   
int cmd_show;                            /* not sure why, but needed */
pixel_ptr c_buffer;
const char g_szClassName[] = "3Dgpl3";

void (*frame_function)(void)=NULL;
void (*handler_function)(int key_code)=NULL;
void (*idle_function)(void)=NULL;

void line(int *vertex1,int *vertex2,int red,int green,int blue);

#pragma region CALLBACKS
void handler(int key)                       
{
   switch(key)
   {
   case KEY_ENTER: 
      close_event_loop(); break;

   case KEY_ARROW_RIGHT: break;
   case KEY_ARROW_LEFT:  break;
   case KEY_ARROW_UP:    break;
   case KEY_ARROW_DOWN:  break;
   }
}

void frame(void)                            
{
   int v1[3]={0,0,0};
   int v2[3]={0,0,0};

   v1[0]=rand()%screen_x_size;             /* coordinates for a random */
   v1[1]=rand()%screen_y_size;             /* point */
   v2[0]=rand()%screen_x_size;             /* coordinates for a random */
   v2[1]=rand()%screen_y_size;             /* point */

   line(v1,v2,rand()%255,rand()%255,rand()%255);

   blit();                                
}

void idle(void)
{
   frame();
}
#pragma endregion 


#pragma region ENGINE FUNCTIONS


void init_graphics(void)
{
   c_buffer=(pixel_ptr)malloc(image_size*pixel_size);
   if(c_buffer==NULL) 
      error("(Graphics) Not enough memory.\n");
}

void init_screen(char *window_title,int size_x,int size_y)
{
   PAINTSTRUCT ps;
   int i,remap;
   COLORREF cr,cr2;                           /* for determining */
   BYTE r,g,b;                                /* bits for each color */

   screen_x_size=size_x;                   /* screen size */
   screen_y_size=size_y;
   image_size=screen_x_size*screen_y_size;
   
   ClippingUtils::init_clipping(0,0,screen_x_size-1,screen_y_size-1);
   
   static char szAppName[] = "Environ";
   wnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                        g_szClassName,
                        "The title of my window",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, size_x, size_y,
                        NULL, NULL, instance, NULL);
   if(wnd == NULL)   {
      DWORD error = GetLastError();
      assert(wnd != NULL);
   }

   mem = CreateCompatibleDC( BeginPaint( wnd,&ps ) );
   if(( GetDeviceCaps( ps.hdc, PLANES )) !=1 )
      error( "(Hardware) Direct RGB color expected." );

   pixel_size = GetDeviceCaps( ps.hdc,BITSPIXEL ) / 8;
   if(( pixel_size != 2 ) && ( pixel_size != 3 ) && (pixel_size != 4))
      error( "(Hardware) 16bpp, 24bpp or 32bpp expected." );

   
   init_graphics();
   
   bmp = CreateCompatibleBitmap( ps.hdc, screen_x_size, screen_y_size );
   SelectObject( mem, bmp );

   cr2 = 0;                                     /* ugly way of doing something */
   red_mask = green_mask = blue_mask = 0;  /* trivial. Windows don't */
   for (i=1; i<256; i++)                        /* have any service to report */
   {                                          /* pixel bit layout */
      cr = SetPixel( mem,0,0, RGB(i,i,i) );
      if( GetRValue(cr) != GetRValue(cr2)) red_mask++;
      if( GetGValue(cr) != GetGValue(cr2)) green_mask++;
      if( GetBValue(cr) != GetBValue(cr2)) blue_mask++;       
      cr2 = cr;                                   /* masks - which bits are masked */
   }                                          /* by every color */
   red_size = green_size = blue_size = 0;  
   for(i=0; i<8; i++)                           /* finding how many bits */
   {
      if( red_mask >> i ) red_size++;
      if( green_mask >> i ) green_size++;
      if( blue_mask >> i ) blue_size++;
   }
   red_shift = green_size + blue_size;   /* finding how to pack colors */
   green_shift = blue_size;               /* into a pixel */
   blue_shift = 0;

   EndPaint(wnd,&ps);

   rect.left = rect.top = 0;
   rect.right = screen_x_size;
   rect.bottom = screen_y_size;

   ShowWindow(wnd,cmd_show);            /* generate messages */
   UpdateWindow(wnd);
}

/**********************************************************\
 * Packing a pixel into a bitmap.                         *
\**********************************************************/

void pixel(char* buf_address,int red,int green,int blue)
{                                           
   /* adjust and clamp */
   if(( red >>= (8-red_size) ) > red_mask) red = red_mask;
   if(( green >>= (8-green_size) ) > green_mask) green = green_mask; 
   if(( blue >>= (8-blue_size) ) > blue_mask) blue = blue_mask; 

   switch(pixel_size)                      /* depending on screen depth */ 
   {                                          /* pack and store */
   case 2:                                   /* 16bpp */
      (*(short*)buf_address) = (red << red_shift) | 
                               (green << green_shift) | 
                               (blue << blue_shift); 
      break;
   case 3:                                   /* 24bpp */
      *buf_address = blue; 
      *(buf_address+1) = green;
      *(buf_address+2) = red;
      break;
   case 4:                                   /* 32bpp */
      (*(int*)buf_address) = (red << red_shift) | 
                             (green << green_shift) | 
                             (blue << blue_shift);
      break;
   }
}


void clear(int red,int green,int blue)
{
   int i;
   for(i=0;i<image_size*pixel_size;i+=pixel_size)
      pixel(c_buffer+i,red,green,blue);
}

void line(int *vertex1,int *vertex2,int red,int green,int blue)
{
   int inc_ah,inc_al;
   int i;
   int *v1,*v2,pos;
   int dx,dy,long_d,short_d;
   int d,add_dh,add_dl;
   int inc_xh,inc_yh,inc_xl,inc_yl;
   pixel_ptr adr_c=c_buffer;
   v1=(int*)vertex1;
   v2=(int*)vertex2;

   if(ClippingUtils::line_x_clipping(&v1,&v2,2))           /* horizontal clipping */
   {
      if(ClippingUtils::line_y_clipping(&v1,&v2,2))          /* vertical clipping */
      {
         dx=v2[0]-v1[0]; dy=v2[1]-v1[1];          /* ranges */

         if(dx<0){
            dx=-dx; inc_xh=-1; inc_xl=-1;/* making sure dx and dy >0 */
         }  
         else    {       
            inc_xh=1;  inc_xl=1; /* adjusting increments */
         }  

         if(dy<0){
            dy=-dy;inc_yh=-screen_x_size;
            inc_yl=-screen_x_size;                    /* to get to the neighboring */
         }                                
         else    {       
            inc_yh= screen_x_size;
            inc_yl= screen_x_size;
         }
         if(dx>dy){
            long_d=dx;short_d=dy;inc_yl=0;
         }/* long range,&make sure either */
         else     {
            long_d=dy;short_d=dx;inc_xl=0;
         }/* x or y is changed in L case */

         inc_ah=inc_xh+inc_yh;
         inc_al=inc_xl+inc_yl;                    /* increments for point address */

         d=2*short_d-long_d;                      /* initial value of d */
         add_dl=2*short_d;                        /* d adjustment for H case */
         add_dh=2*(short_d-long_d);               /* d adjustment for L case */
         pos=v1[1]*screen_x_size+v1[0];
         adr_c+=pos*pixel_size;                /* address of first point */
         
         for(i=0;i<=long_d;i++)                   /* for all points in long range */
         {
            pixel(adr_c,red,green,blue);         /* ploting a pixel */

            if(d>=0)
            {
               d+=add_dh;
               adr_c+=inc_ah*pixel_size;           /* new in the color-buffer */
            }                                       /* previous point was H type */
            else
            {
               d+=add_dl;
               adr_c+=inc_al*pixel_size;           /* new in the color-buffer */
            }                                       /* previous point was L type */
         }
      }
   }
}

void init_event_loop(void (*frame)(void),
                     void (*handler)(int key_code),
                     void (*idle)(void))
{ 
   MSG msg;

   frame_function = frame;                   /* remebering which functions */
   handler_function = handler;               /* to call */
   idle_function = idle;

   frame_function();                       /* draw first frame */
   InvalidateRect(wnd,&rect,TRUE);
   UpdateWindow(wnd);

   while(1)                                   /* event loop */
   {
      if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))  /* get a message, don't block */
      {
         if(msg.message==WM_QUIT) 
            break;          /* exit event received */
         TranslateMessage(&msg);
         DispatchMessage(&msg);                   /* message forwarded */
      }
      else
      {
         InvalidateRect(wnd,&rect,TRUE);    /* erase following by paint */
         UpdateWindow(wnd);                    /* will be generated */
      }
   }
}

void error(char *s,...)
{
   char str[256];
   va_list lst;

   va_start(lst,s);
   vsprintf_s(str,s,lst);                       /* forming the message */
   va_end(lst);

   MessageBox(NULL, (LPCSTR)str, (LPCSTR)"3Dgpl",MB_OK|MB_ICONSTOP|MB_SYSTEMMODAL);

   close_event_loop();
   exit(0);                                   /* above might not be enough */
}

void close_event_loop(void)
{
   PostMessage(wnd,WM_CLOSE,0,0L);         
}



int main(int argc, char *argv[])                
{

   init_screen("3Dgpl3 - Texture", 300, 300);
   
   clear(0,0,0); 
   init_event_loop(frame,handler,idle);    
   close_screen();

   return(1);
}
#pragma endregion


#pragma region WINDOWS FUNCTIONS
long FAR PASCAL WndProc(HWND hWnd,UINT message,
			WPARAM wParam,LPARAM lParam)
{
   switch(message)
   {
   case WM_PAINT:      
      if(frame_function!=NULL) idle_function();
      break;
   case WM_ERASEBKGND:
      return(1L);           /* don't erase background */
   case WM_DESTROY:  
      PostQuitMessage(0);
      break;
   case WM_KEYDOWN:  
      if(handler_function!=NULL) 
         handler_function(wParam);
      if(frame_function!=NULL) 
      {
         frame_function();
         InvalidateRect(wnd,&rect,TRUE);
         UpdateWindow(wnd);
      }
      break;
   default:            
      return(DefWindowProc(hWnd,message,wParam,lParam));
   }
   return(0L);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpszCmdLine,int nCmdShow)
{
   WNDCLASS w;
   int n;
   char *start,*end;                          /* to get parametrs */
   char *o[32];                               /* to pass parameters */

   instance = hInstance;
   cmd_show=nCmdShow;
   if((instance=hPrevInstance)==NULL)
   {
      w.style = CS_HREDRAW | CS_VREDRAW;
      w.lpfnWndProc = WndProc;
      w.cbClsExtra = 0;
      w.cbWndExtra = 0;
      w.hInstance = hInstance;
      w.hIcon = NULL;
      w.hCursor = NULL;
      w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
      w.lpszMenuName = NULL;
      w.lpszClassName = (LPCSTR)g_szClassName;

      if(! RegisterClass(&w))
         return FALSE;
   }

   n=0;
   o[n++]="";
   start=lpszCmdLine;                         /* starting from here */
   while((end=strchr(start,' '))!=NULL)
   {
      if(n>=32) 
         error("(Hardware) Way too many command line options.\n");
      if(end!=start) 
         o[n++]=start;              /* ignore empty ones */
      *end=0;                                   /* end of line */
      start=end+1;
   }
   if(strlen(start)>0) 
      o[n++]=start;          /* the very last one */

   return(main(n,o));                         /* here, humane way to start */
}
void close_screen(void)
{
   DeleteDC(mem);                          
   DeleteObject(bmp);
}


void blit(void)
{
   PAINTSTRUCT ps;

   BeginPaint(wnd,&ps);                    /* store into a bitmap */
   SetMapMode(ps.hdc,MM_TEXT);                /* blit a bitmap */
   SetBitmapBits(bmp,image_size*pixel_size,(void*)c_buffer);
   BitBlt(ps.hdc,0,0,screen_x_size,screen_y_size,mem,0,0,SRCCOPY);
   EndPaint(wnd,&ps);
}

#pragma endregion

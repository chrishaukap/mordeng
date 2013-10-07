#if !defined(WINDOW_H)
#define WINDOW_H

#include <windows.h>                        

#define main _main                          /* to accomodate windows */

#define KEY_ARROW_LEFT  VK_LEFT
#define KEY_ARROW_RIGHT VK_RIGHT
#define KEY_ARROW_UP    VK_UP
#define KEY_ARROW_DOWN  VK_DOWN
#define KEY_PLUS        VK_ADD
#define KEY_MINUS       VK_SUBTRACT
#define KEY_ENTER       VK_RETURN
#define KEY_SPACE       VK_SPACE
#define KEY_TAB         VK_TAB           /* ids of some keys */

#define MAX_SCREEN_SIZE 1024

extern int screen_x_size;                /* screen dimensions */
extern int screen_y_size;
extern int image_size;                   /* number of pixels */
extern int pixel_size;                   /* in bytes */

typedef char* pixel_ptr;                 /* may not fit a char though */

/**********************************************************/

void init_screen(char *window_title,int size_x,int size_y);
void pixel(pixel_ptr buf_address,int r,int g,int b);
void blit(void);
void close_screen(void);

void init_event_loop(void (*frame)(void),
                        void (*handler)(int key_code),
                        void (*idle)(void));
void error(char *s,...);
void close_event_loop(void);

/**********************************************************/

#endif

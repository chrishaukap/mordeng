#include "clipping.h"
#include <assert.h>
#include <memory.h>

using namespace mord;


int ClippingUtils::minx = 0;                       
int ClippingUtils::maxx = 0;                       
int ClippingUtils::miny = 0;
int ClippingUtils::maxy = 0;
int ClippingUtils::clipping_2D = 0;    

void ClippingUtils::init_clipping(int _minx, int _miny, 
                                  int _maxx, int _maxy)
{
   minx=_minx;                     /* no error checking... */
   miny=_miny;
   maxx=_maxx;
   maxy=_maxy;
}

/**********************************************************\
 * Line clipping using binary search technique.           *
 *                                                        *
 * RETUNRNS: 0 when line is compleately outside;          *
 * --------- 1 otherwise.                                 *
 *                                                        *
 * SETS:  clipping_2D to 1 when first or both points    *
 * -----  were changed, 0 otherwise.                      *
\**********************************************************/

#define C_MAX_DIMENSIONS               8    /* X Y Z R G B Tx Ty */

                    /* type of performed clipping */
int ClippingUtils::line_x_clipping(int **vertex1, int **vertex2, int dimension)
{
   int i;
   int whereto;
   int *l,*r,*m,*t;                           /* left right midle and tmp */
   static int g_store0[C_MAX_DIMENSIONS];     /* static stores for clipped vxes */
   static int g_store1[C_MAX_DIMENSIONS];
   static int g_store2[C_MAX_DIMENSIONS];
   static int g_store3[C_MAX_DIMENSIONS];
   static int g_store4[C_MAX_DIMENSIONS];
   static int g_store5[C_MAX_DIMENSIONS];
   int **vmn,**vmx;                           /* so that *vmn[0] < *vmx[0] */
   int swap;                                  /* were coordinates swaped? */

   clipping_2D=0;                           /* default no clipping yet */

   if((*vertex1)[0]<(*vertex2)[0])
   { 
      swap=0; vmn=vertex1; vmx=vertex2; /* so that *vmn[0] < *vmx[0] */
   }      
   else
   { 
      swap=1; vmn=vertex2; vmx=vertex1; 
   }

   if( ( (*vmn)[0] >= maxx ) ||
       ( (*vmx)[0] <= minx ) ) 
      return(0);
   else
   {
      if( (*vmn)[0] <= minx )           /* clipping */
      {
         memcpy(m=g_store0,*vmn,dimension*sizeof(int));
         memcpy(r=g_store1,*vmx,dimension*sizeof(int));
         l=g_store2;

         whereto=1;
         while(m[0] != minx)
         {
            if(whereto==1) 
            { 
               t=l; l=m; m=t; 
            }
            else       
            { 
               t=r; r=m; m=t; 
            }
            for( i=0; i<dimension; i++) 
               m[i] = (l[i] + r[i]) >> 1;

            whereto = m[0] < minx;
         }
         *vmn = m;                                  /* that is why m[] is static */
         clipping_2D = swap^1;
      }

      if( (*vmx)[0] >= maxx )           /* clipping */
      {
         memcpy(l=g_store3,*vmn,dimension*sizeof(int));
         memcpy(m=g_store4,*vmx,dimension*sizeof(int));
         r=g_store5;

         whereto=0;
         while(m[0] != maxx)
         {
            if(whereto==1) 
            {
               t=l; l=m; m=t; 
            }
            else           
            { 
               t=r; r=m; m=t; 
            }
            for(i=0; i<dimension; i++) 
               m[i] = (l[i]+r[i]) >> 1;
         
            whereto = m[0] < maxx;
         }
      
         *vmx = m;                                 /* that is why m[] is static */
         clipping_2D |= swap & 1;
      }
   }
   return(1);                                 /* partialy or not clipped */
}

/**********************************************************\
 * Line clipping using binary search technique.           *
 *                                                        *
 * RETUNRNS: 0 when line is compleately outside;          *
 * --------- 1 otherwise.                                 *
 *                                                        *
 * SETS:  clipping_2D to 1 when first or both points    *
 * -----  were changed, 0 otherwise.                      *
\**********************************************************/

int ClippingUtils::line_y_clipping(int **vertex1, int **vertex2, int dimension)
{
   int i;
   int whereto;
   int *l,*r,*m,*t;                           /* left right midle and tmp */
   static int g_store0[C_MAX_DIMENSIONS];     /* static stores for clipped vxes */
   static int g_store1[C_MAX_DIMENSIONS];
   static int g_store2[C_MAX_DIMENSIONS];
   static int g_store3[C_MAX_DIMENSIONS];
   static int g_store4[C_MAX_DIMENSIONS];
   static int g_store5[C_MAX_DIMENSIONS];
   int **vmn,**vmx;                           /* so that *vmn[1] < *vmx[1] */
   int swap;                                  /* were coordinates swaped? */

   clipping_2D=0;                           /* default no clipping yet */

   if((*vertex1)[1]<(*vertex2)[1])
   { 
      swap=0; vmn=vertex1; vmx=vertex2; /* so that *vmn[1] < *vmx[1] */
   }      
   else
   { 
      swap=1; vmn=vertex2; vmx=vertex1; 
   }

   if(((*vmn)[1] >= maxy) ||
      ((*vmx)[1] <= miny)) 
      return(0);
   else
   {
      if((*vmn)[1]<=miny)           /* clipping */
      {
         memcpy(m=g_store0,*vmn,dimension*sizeof(int));
         memcpy(r=g_store1,*vmx,dimension*sizeof(int));
         l=g_store2;

         whereto=1;
         while(m[1]!=miny)
         {
            if(whereto==1) 
            { 
               t=l; l=m; m=t; 
            }
            else           
            { 
               t=r; r=m; m=t; 
            }
            for(i=0;i<dimension;i++)
               m[i] = (l[i] + r[i]) >> 1;

            whereto = m[1] < miny;
         }
         *vmn=m;                                  /* that is why m[] is static */
         clipping_2D=swap^1;
      }

      if((*vmx)[1]>=maxy)           /* clipping */
      {
         memcpy(l=g_store3,*vmn,dimension*sizeof(int));
         memcpy(m=g_store4,*vmx,dimension*sizeof(int));
         r=g_store5;

         whereto=0;
         while(m[1]!=maxy)
         {
            if(whereto==1) 
            { 
               t=l; l=m; m=t; 
            }
            else           
            {
               t=r; r=m; m=t; 
            }
            for(i=0; i<dimension; i++) 
               m[i] = (l[i] + r[i]) >> 1;
            whereto = m[1] < maxy;
         }
         *vmx=m;                                  /* that is why m[] is static */
         clipping_2D|=swap&1;
      }
   }
   return(1);                                 /* partialy or not clipped */
}

#if !defined(CLIPPING_H)
#define CLIPPING_H

namespace mord {
   class ClippingUtils{
   public:
      static void init_clipping(int minx,int miny,int maxx,int maxy);
      static int line_x_clipping(int **vertex1, int **vertex2, int dimension);
      static int line_y_clipping(int **vertex1, int **vertex2, int dimension);
   private:   
      static int minx;                       
      static int maxx;                       
      static int miny;
      static int maxy;
      static int clipping_2D;      
   };
}



#endif

#ifndef MATRIX4_H
#define MATRIX4_H

namespace mord{
   class Vector4;
   class Matrix4{
      
   private:
      // used for double subscript overloading
      // access row-first.
      // ie. use [2][1] to get the middle column of the last row
      class Proxy { 
      public:
           Proxy(float* _array) : _array(_array) { }

           float& operator[](int index) {
               return _array[index];
           }
       private:
           float* _array;
       };

   public:
      Matrix4();
      Matrix4(float a1, float b1, float c1, float d1,
              float a2, float b2, float c2, float d2,
              float a3, float b3, float c3, float d3,
           float a4, float b4, float c4, float d4); 

      Matrix4(const Matrix4& m);
      ~Matrix4();
                 
     bool isZeroed() const;
      Proxy operator[] (int idx){
         return Proxy(values[idx]);
      }
      Proxy operator[] (int idx) const{
         return Proxy(values[idx]);
      }
      Matrix4& operator= (const Matrix4& rhs);

      Matrix4 operator* (const Matrix4& rhs);
      static void mult(Matrix4& ret, const Matrix4& lhs, const Matrix4& rhs);

      Matrix4& operator*= (const Matrix4& rhs);
      
      bool operator==(const Matrix4& rhs);
      bool operator!=(const Matrix4& rhs);
 
      void print() const;
   private:

      void allocateMatrix();
      void deleteMatrix();
      float** values;
   };
}

#endif //MATRIX4_H
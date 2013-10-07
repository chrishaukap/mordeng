#ifndef MATRIX_H
#define MATRIX_H

namespace mord{
   class Vector3D;
   class Matrix3D{
      
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
      Matrix3D();
      Matrix3D(float x1, float y1, float z1,
               float x2, float y2, float z2,
               float x3, float y3, float z3);
      Matrix3D(const Vector3D& row1,
               const Vector3D& row2,
               const Vector3D& row3);
      
      Matrix3D(const Matrix3D& m);
      ~Matrix3D();
                 
      Proxy operator[] (int idx){
         return Proxy(values[idx]);
      }
      Proxy operator[] (int idx) const{
         return Proxy(values[idx]);
      }
      Matrix3D& operator= (const Matrix3D& rhs);

      Matrix3D operator* (const Matrix3D& rhs);
      static void mult(Matrix3D& ret, const Matrix3D& lhs, const Matrix3D& rhs);

      Matrix3D& operator*= (const Matrix3D& rhs);
      
      bool operator==(const Matrix3D& rhs);
      bool operator!=(const Matrix3D& rhs);
 
      void print() const;
   private:

      void allocateMatrix();
      void deleteMatrix();
      float** values;
   };
}

#endif //MATRIX_H
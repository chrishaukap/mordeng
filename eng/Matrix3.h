#ifndef MATRIX3_H
#define MATRIX3_H

namespace mord{
   class Vector3;
   class Matrix3{
      
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
      Matrix3();
      Matrix3(float x1, float y1, float z1,
              float x2, float y2, float z2,
              float x3, float y3, float z3);
      Matrix3(const Vector3& row1,
              const Vector3& row2,
              const Vector3& row3);
      
      Matrix3(const Matrix3& m);
      ~Matrix3();
                 
      Proxy operator[] (int idx){
         return Proxy(values[idx]);
      }
      Proxy operator[] (int idx) const{
         return Proxy(values[idx]);
      }
      Matrix3& operator= (const Matrix3& rhs);

      Matrix3 operator* (const Matrix3& rhs);
      static void mult(Matrix3& ret, const Matrix3& lhs, const Matrix3& rhs);

      Matrix3& operator*= (const Matrix3& rhs);
      
      bool operator==(const Matrix3& rhs);
      bool operator!=(const Matrix3& rhs);
 
      void print() const;
   private:

      void allocateMatrix();
      void deleteMatrix();
      float** values;
   };
}

#endif //MATRIX3_H
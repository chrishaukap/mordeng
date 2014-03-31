#include "Matrix3.h"

#include "Vector3.h"
#include <assert.h>
#include <cstdlib>
#include <stdio.h>

using namespace mord;

const int size = 3;

Matrix3::Matrix3() : values(NULL) {
   allocateMatrix();
   
   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         values[i][j] = 0;
}

Matrix3::Matrix3(float x1, float y1, float z1,
                   float x2, float y2, float z2,
                   float x3, float y3, float z3) : values(NULL) {  
   allocateMatrix();
   
   values[0][0] = x1; values[0][1] = y1; values[0][2] = z1;
   values[1][0] = x2; values[1][1] = y2; values[1][2] = z2;
   values[2][0] = x3; values[2][1] = y3; values[2][2] = z3;
}

Matrix3::Matrix3(const Vector3& row1,
                 const Vector3& row2,
                 const Vector3& row3) : values(NULL) {
   Matrix3(row1.getX(), row1.getY(), row1.getZ(),
            row2.getX(), row2.getY(), row2.getZ(),
            row3.getX(), row3.getY(), row3.getZ());
}
      
Matrix3::Matrix3(const Matrix3& m) : values(NULL) {
   *this = m;
}

Matrix3::~Matrix3(){
   deleteMatrix();
}

Matrix3& Matrix3::operator= (const Matrix3& rhs)
{
   deleteMatrix();
   allocateMatrix();

   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         values[j][i] = rhs[j][i];

   return *this;
}

void Matrix3::allocateMatrix(){              
   values = new float*[size];
   for(int i = 0; i < size; ++i)
      values[i] = new float[size];
}

void Matrix3::deleteMatrix(){
         
   if(values != NULL){
      for(int i = 0; i < size; ++i)
         delete [] values[i];
      delete [] values;
   }
}

bool Matrix3::operator==(const Matrix3& rhs){   
   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         if(values[j][i] != rhs[j][i])
            return false;
   return true;
}

bool Matrix3::operator!=(const Matrix3& rhs){
   return !operator==(rhs);
}

Matrix3 Matrix3::operator* (const Matrix3& rhs){
   Matrix3 ret;
   Matrix3::mult(ret, *this, rhs);
   return ret;
}

void Matrix3::mult(Matrix3 &ret, const Matrix3& lhs, const Matrix3& rhs){
   
   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j) {
         float total = 0;
         for(int k=0; k<size; ++k) { // TODO - assuming square matrices
            total += lhs[i][k] * rhs[k][j];
            int blah=0;
         }
         ret[i][j] = total;
      }
}

Matrix3& Matrix3::operator*= (const Matrix3& rhs){
   Matrix3 tmp;
   Matrix3::mult(tmp, *this, rhs);
   *this = tmp;
   return *this;
}

void Matrix3::print() const
{
   for(int i=0; i<size; ++i) {
      for(int j=0; j<size; ++j) 
         fprintf(stderr, "%f ", values[i][j]);
      fprintf(stderr, "\n");
   }
   fprintf(stderr, "\n");
}
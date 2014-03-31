#include "Matrix4.h"

#include "Vector4.h"
#include <assert.h>
#include <cstdlib>
#include <stdio.h>

// TODO: write a generic Matrix class that can handle N dimension so we're not duplicating code

using namespace mord;

const int size = 4;

Matrix4::Matrix4() : values(NULL) {
   allocateMatrix();
   
   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         values[i][j] = 0;
}

Matrix4::Matrix4(float a1, float b1, float c1, float d1,
                 float a2, float b2, float c2, float d2,
                 float a3, float b3, float c3, float d3,
                 float a4, float b4, float c4, float d4)  : values(NULL) {  
   allocateMatrix();
   
   values[0][0] = a1; values[0][1] = b1; values[0][2] = c1; values[0][3] = d1;
   values[1][0] = a2; values[1][1] = b2; values[1][2] = c2; values[1][3] = d2;
   values[2][0] = a3; values[2][1] = b3; values[2][2] = c3; values[2][3] = d3;
   values[3][0] = a4; values[3][1] = b4; values[3][2] = c4; values[3][3] = d4;
}
      
Matrix4::Matrix4(const Matrix4& m) : values(NULL) {
   *this = m;
}

Matrix4::~Matrix4(){
   deleteMatrix();
}

bool Matrix4::isZeroed() const
{
   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         if( values[i][j] != 0 )
          return false;
   return true;
}

Matrix4& Matrix4::operator= (const Matrix4& rhs)
{
   deleteMatrix();
   allocateMatrix();

   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         values[j][i] = rhs[j][i];

   return *this;
}

void Matrix4::allocateMatrix(){              
   values = new float*[size];
   for(int i = 0; i < size; ++i)
      values[i] = new float[size];
}

void Matrix4::deleteMatrix(){
         
   if(values != NULL){
      for(int i = 0; i < size; ++i)
         delete [] values[i];
      delete [] values;
   }
}

bool Matrix4::operator==(const Matrix4& rhs){   
#define ERROR 0.00001
   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         if(values[j][i]  - rhs[j][i] > ERROR)
       {
         float val1 = values[j][i];
         float val2 = rhs[j][i];
            return false;
       }
   return true;
}

bool Matrix4::operator!=(const Matrix4& rhs){
   return !operator==(rhs);
}

Matrix4 Matrix4::operator* (const Matrix4& rhs){
   Matrix4 ret;
   Matrix4::mult(ret, *this, rhs);
   return ret;
}

void Matrix4::mult(Matrix4 &ret, const Matrix4& lhs, const Matrix4& rhs){
   
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

Matrix4& Matrix4::operator*= (const Matrix4& rhs){
   Matrix4 tmp;
   Matrix4::mult(tmp, *this, rhs);
   *this = tmp;
   return *this;
}

void Matrix4::print() const
{
   for(int i=0; i<size; ++i) {
      for(int j=0; j<size; ++j) 
         fprintf(stderr, "%f ", values[i][j]);
      fprintf(stderr, "\n");
   }
   fprintf(stderr, "\n");
}
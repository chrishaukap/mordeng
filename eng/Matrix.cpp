#include "Matrix.h"

#include "Vector3D.h"
#include <assert.h>
#include <cstdlib>
#include <stdio.h>

using namespace mord;

const int size = 3;

Matrix3D::Matrix3D() : values(NULL) {
   allocateMatrix();
   
   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         values[i][j] = 0;
}

Matrix3D::Matrix3D(float x1, float y1, float z1,
                   float x2, float y2, float z2,
                   float x3, float y3, float z3) : values(NULL) {  
   allocateMatrix();
   
   values[0][0] = x1; values[0][1] = y1; values[0][2] = z1;
   values[1][0] = x2; values[1][1] = y2; values[1][2] = z2;
   values[2][0] = x3; values[2][1] = y3; values[2][2] = z3;
}

Matrix3D::Matrix3D(const Vector3D& row1,
                   const Vector3D& row2,
                   const Vector3D& row3) : values(NULL) {
   Matrix3D(row1.getX(), row1.getY(), row1.getZ(),
            row2.getX(), row2.getY(), row2.getZ(),
            row3.getX(), row3.getY(), row3.getZ());
}
      
Matrix3D::Matrix3D(const Matrix3D& m) : values(NULL) {
   *this = m;
}

Matrix3D::~Matrix3D(){
   deleteMatrix();
}

Matrix3D& Matrix3D::operator= (const Matrix3D& rhs)
{
   deleteMatrix();
   allocateMatrix();

   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         values[j][i] = rhs[j][i];

   return *this;
}

void Matrix3D::allocateMatrix(){              
   values = new float*[size];
   for(int i = 0; i < size; ++i)
      values[i] = new float[size];
}

void Matrix3D::deleteMatrix(){
         
   if(values != NULL){
      for(int i = 0; i < size; ++i)
         delete [] values[i];
      delete [] values;
   }
}

bool Matrix3D::operator==(const Matrix3D& rhs){   
   for(int i=0; i<size; ++i)
      for(int j=0; j<size; ++j)
         if(values[j][i] != rhs[j][i])
            return false;
   return true;
}

bool Matrix3D::operator!=(const Matrix3D& rhs){
   return !operator==(rhs);
}

Matrix3D Matrix3D::operator* (const Matrix3D& rhs){
   Matrix3D ret;
   Matrix3D::mult(ret, *this, rhs);
   return ret;
}

void Matrix3D::mult(Matrix3D &ret, const Matrix3D& lhs, const Matrix3D& rhs){
   
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

Matrix3D& Matrix3D::operator*= (const Matrix3D& rhs){
   Matrix3D tmp;
   Matrix3D::mult(tmp, *this, rhs);
   *this = tmp;
   return *this;
}

void Matrix3D::print() const
{
   for(int i=0; i<size; ++i) {
      for(int j=0; j<size; ++j) 
         fprintf(stderr, "%f ", values[i][j]);
      fprintf(stderr, "\n");
   }
   fprintf(stderr, "\n");
}
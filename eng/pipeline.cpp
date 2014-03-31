#include "pipeline.h"
#include "Matrix4.h"
#include "Vector3.h"
#include <assert.h>
#include <math.h>

namespace mord
{

void genTransMatrixFromEmptyMatrix(Matrix4& matrix, const Vector3& translationVector)
{
   assert(matrix.isZeroed());
   matrix[0][0] = 1; matrix[1][1] = 1; matrix[2][2] = 1;   matrix[3][3] = 1;
   matrix[0][3] = translationVector.getX();
   matrix[1][3] = translationVector.getY();
   matrix[2][3] = translationVector.getZ();
}

void genRotMatrixAboutX(Matrix4& emptyMatrix, float alpha)
{
   assert(emptyMatrix.isZeroed());
   if(alpha != 0.0f)
   {
      emptyMatrix[0][0] = 1; emptyMatrix[3][3] = 1;
      emptyMatrix[1][1] = cos(alpha);
      emptyMatrix[2][1] = sin(alpha);
      emptyMatrix[1][2] = -sin(alpha);
      emptyMatrix[2][2] = cos(alpha);
   }
}
void genRotMatrixAboutY(Matrix4& emptyMatrix, float beta)
{
   assert(emptyMatrix.isZeroed());
   if(beta != 0.0f)
   {
      emptyMatrix[1][1] = 1; emptyMatrix[3][3] = 1;
      emptyMatrix[0][0] = cos(beta);
      emptyMatrix[0][2] = sin(beta);
      emptyMatrix[2][0] = -sin(beta);
      emptyMatrix[2][2] = cos(beta);
   }
}
void genRotMatrixAboutZ(Matrix4& emptyMatrix, float gamma)
{
   assert(emptyMatrix.isZeroed());
   if(gamma != 0.0f)
   {
      emptyMatrix[2][2] = 1; emptyMatrix[3][3] = 1;
      emptyMatrix[0][0] = cos(gamma);
      emptyMatrix[0][1] = -sin(gamma);
      emptyMatrix[1][0] = sin(gamma);
      emptyMatrix[1][1] = cos(gamma);
   }   
}

void genRotMatrixFromTranslationMatrix(Matrix4& transMatrix, float alpha, float beta, float gamma)
{
   assert(!"NOT IMPLEMENTED");
}

}
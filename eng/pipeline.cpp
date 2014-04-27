#include "pipeline.h"
#include "Matrix4.h"
#include "Vector3.h"
#include <assert.h>
#include <math.h>

namespace mord
{
  
void genLookAtMatrix(Matrix4& lookAt, const Camera& cam)
{
  assert(lookAt.isZeroed());

  Vector3 eye(cam.x, cam.y, cam.z);
  Vector3 up(cam.up_x, cam.up_y, cam.up_z);
  Vector3 target(cam.target_x, cam.target_y, cam.target_z);

  // 'forward' vector
  Vector3 zaxis( Vector3::normalize(eye - target));

  // 'right' vector
  Vector3 xaxis = Vector3::normalize(Vector3::cross(up, zaxis));
  
  // 'up' vector
  Vector3 yaxis = Vector3::cross(zaxis, xaxis);
 
  // Create a 4x4 view matrix from the right, up, forward and eye position vectors
  lookAt[0][0] = xaxis.getX(); 
  lookAt[0][1] = xaxis.getY(); 
  lookAt[0][2] = xaxis.getZ(); 
  lookAt[0][3] = -Vector3::dot( xaxis, eye );
  lookAt[1][0] = yaxis.getX(); 
  lookAt[1][1] = zaxis.getY(); 
  lookAt[1][2] = yaxis.getZ(); 
  lookAt[1][3] = -Vector3::dot( yaxis, eye );
  lookAt[2][0] = zaxis.getX(); 
  lookAt[2][1] = yaxis.getY(); 
  lookAt[2][2] = zaxis.getZ(); 
  lookAt[2][3] = -Vector3::dot( zaxis, eye );
  lookAt[3][0] = 0; 
  lookAt[3][1] = 0; 
  lookAt[3][2] = 0; 
  lookAt[3][3] = 1;
}

void genTranslationMatrixFromEmptyMatrix(Matrix4& matrix, const Vector3& translationVector)
{
   assert(matrix.isZeroed());
   matrix[0][0] = 1; matrix[1][1] = 1; matrix[2][2] = 1;   matrix[3][3] = 1;
   matrix[0][3] = translationVector.getX();
   matrix[1][3] = translationVector.getY();
   matrix[2][3] = translationVector.getZ();
}

void genRotationMatrixAboutX(Matrix4& emptyMatrix, float alpha)
{
   assert(emptyMatrix.isZeroed());
   float cosAlpha = cos(alpha);
   float sinAlpha = sin(alpha);
   if(alpha != 0.0f)
   {
      emptyMatrix[0][0] = 1; emptyMatrix[3][3] = 1;
      emptyMatrix[1][1] = cosAlpha;
      emptyMatrix[2][1] = sinAlpha;
      emptyMatrix[1][2] = -sinAlpha;
      emptyMatrix[2][2] = cosAlpha;
   }
}
void genRotationMatrixAboutY(Matrix4& emptyMatrix, float beta)
{
   assert(emptyMatrix.isZeroed());
   float cosBeta = cos(beta);
   float sinBeta = sin(beta);
   if(beta != 0.0f)
   {
      emptyMatrix[1][1] = 1; emptyMatrix[3][3] = 1;
      emptyMatrix[0][0] = cosBeta;
      emptyMatrix[0][2] = sinBeta;
      emptyMatrix[2][0] = -sinBeta;
      emptyMatrix[2][2] = cosBeta;
   }
}
void genRotationMatrixAboutZ(Matrix4& emptyMatrix, float gamma)
{
   assert(emptyMatrix.isZeroed());
   float cosGamma = cos(gamma);
   float sinGamma = sin(gamma);
   if(gamma != 0.0f)
   {
      emptyMatrix[2][2] = 1; emptyMatrix[3][3] = 1;
      emptyMatrix[0][0] = cosGamma;
      emptyMatrix[0][1] = -sinGamma;
      emptyMatrix[1][0] = sinGamma;
      emptyMatrix[1][1] = cosGamma;
   }   
}

void genRotationMatrixFromTranslationMatrix(Matrix4& transMatrix, float alpha, float beta, float gamma)
{
   assert(!"NOT IMPLEMENTED");
}

}
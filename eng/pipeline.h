#ifndef PIPELINE_H
#define PIPELINE_H

namespace mord{
   class Matrix4;
   class Vector3;

   class Camera{
   public:
     Camera(float _x, float _y, float _z,
            float _alpha, float _beta, float _gamma) : 
       x(_x), y(_y), z(_z), alpha(_alpha), beta(_beta), gamma(_gamma)
     {
       target_x = target_y = target_z = 0;
       up_x = up_y = up_z = 0;
     }
     ~Camera(){}
     float x,y,z;
     float alpha,beta,gamma;

     float up_x, up_y, up_z;
     float target_x,target_y,target_z;
   };
   
   void genWorldTransformMatrixForCamera(Matrix4& out_matrix, const Camera& cam);
   void genTranslationMatrixFromEmptyMatrix(Matrix4& matrix, const Vector3& translationVector);

   // caller must pass in translation Matrix
   void genRotationMatrixFromTranslationMatrix(Matrix4& translationMatrix, float alpha, float beta, float gamma);
   
   void genRotationMatrixAboutX(Matrix4& emptyMatrix, float alpha);
   void genRotationMatrixAboutY(Matrix4& emptyMatrix, float beta);
   void genRotationMatrixAboutZ(Matrix4& emptyMatrix, float gamma);

}

#endif
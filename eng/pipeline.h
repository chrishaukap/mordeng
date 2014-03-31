#ifndef PIPELINE_H
#define PIPELINE_H

namespace mord{
   class Matrix4;
   class Vector3;
   

   void genTransMatrixFromEmptyMatrix(Matrix4& matrix, const Vector3& translationVector);

   // caller must pass in translation Matrix
   void genRotMatrixFromTranslationMatrix(Matrix4& translationMatrix, float alpha, float beta, float gamma);
   
   void genRotMatrixAboutX(Matrix4& emptyMatrix, float alpha);
   void genRotMatrixAboutY(Matrix4& emptyMatrix, float beta);
   void genRotMatrixAboutZ(Matrix4& emptyMatrix, float gamma);

}

#endif
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "pipeline.h"
#include <math.h>
#include <iostream>
#include <assert.h>

using namespace mord;
using namespace std;

int testVectors()
{
   {
      Vector3 a(10,0,0);
      a.normalize();

      Vector3 b(1,0,0);
      
      if(a != b)
         return -1;
   }
   {
      Vector3 a(5,0,0);
      Vector3 b(0,5,0);
      Vector3 c(5,5,0);

      a = a+b;
      if(a != c)
         return -1;
      a = a-b;
      if(a == c)
         return -1;

      Vector3 d(15,0,0);
      a = a*3;
      if(a != d)
         return -1;
   }
   {
      Vector3 a(5,0,0);
      Vector3 b(0,5,0);
      Vector3 c(5,5,0);

      a += b;
      if(a != c)
         return -1;
      a -= b;
      if(a == c)
         return -1;

      Vector3 d(15,0,0);
      a *= 3;
      if(a != d)
         return -1;
   }

   {
      Vector3 a(10,0,0);
      Vector3 b(5,5,0);
      
      float dot1 = a * b;
      if( dot1 != 50 )
         return -1;

      a.normalize();
      b.normalize();

      float angle = abs(0.7854f - a.angleBetweenNormalized(b));
      if( 0.0001 <= angle)
         return -1;
   }

   {
      Vector3 a(1,0,0);
      Vector3 b(0,1,0);
      Vector3 c(0,0,1);

      Vector3 d = Vector3::cross(a,b);
      if(c != d)
         return -1;
   }
   return 0;
}

#define PI 3.14159f
#define DEG2RAD(deg) ((deg) * PI / 180.0f)

static void printVec(const Vector4& v)
{
   cout << v.getX() << " " << v.getY() << " " 
        << v.getZ() << " " << v.getW();
}

int testMatrices()
{
#pragma region basic_tests
   {
      Vector3 r1(1,2,3);
      Vector3 r2(4,5,6);
      Vector3 r3(7,8,9);

      Matrix3 m(r1.getX(), r1.getY(), r1.getZ(),
                 r2.getX(), r2.getY(), r2.getZ(),
                 r3.getX(), r3.getY(), r3.getZ());      
      Vector3 row1(m[0][0], m[0][1], m[0][2]);
      Vector3 row2(m[1][0], m[1][1], m[1][2]);
      Vector3 row3(m[2][0], m[2][1], m[2][2]);

      m.print();
      if(r1 != row1)
         return -1;
      if(r2 != row2)
         return -1;
      if(r3 != row3)
         return -1;

      Matrix3 m2(m);
      if(m != m2)
         return -1;

   }
   {
      Matrix3 m1(1,1,1,
                 2,2,2,
                 3,3,3);
      fprintf(stderr,"m1:\n");
      m1.print();
      Matrix3 m2(4,5,6,
                 4,5,6,
                 4,5,6);
      fprintf(stderr,"m2:\n");
      m2.print();
      
      Matrix3 m3;
      Matrix3::mult(m3, m1, m2);
      fprintf(stderr,"m3:\n");
      m3.print();

      Matrix3 m4(12, 15, 18,
                 24, 30, 36,
                 36, 45, 54);
      assert(m3 == m4);
   }
   {
      Matrix4 m1(1,1,1,1,
                 2,2,2,2,
                 3,3,3,3,
             4,4,4,4);
      fprintf(stderr,"m1:\n");
      m1.print();
      Matrix4 m2(4,5,6,7,
                 4,5,6,7,
                 4,5,6,7,
             4,5,6,7);
      fprintf(stderr,"m2:\n");
      m2.print();
      
      Matrix4 m3;
      Matrix4::mult(m3, m1, m2);
      fprintf(stderr,"m3:\n");
      m3.print();

      Matrix4 m4(16,20,24,28,
               32,40,48,56,
             48,60,72,84,
             64,80,96,112);
      assert(m3 == m4);
   }
#pragma endregion
   
#pragma region pipeline_tests
   {
      Matrix4 mT;
      {
         Vector3 transVec(1.5,1.0,1.5);
         genTranslationMatrixFromEmptyMatrix(mT, transVec);
         Matrix4 mTVal (1,0,0,1.5,
                        0,1,0,1,
                        0,0,1,1.5,
                        0,0,0,1);
         assert(mTVal == mT);
      }        

      Matrix4 mRotY;
      {
         genRotationMatrixAboutY(mRotY, DEG2RAD(90));
         Matrix4 mRotYVal (cos(DEG2RAD(90)), 0, sin(DEG2RAD(90)),0,
                           0,1,0,0,
                           -sin(DEG2RAD(90)),0, cos(DEG2RAD(90)),0,
                           0,0,0,1);
         assert(mRotY == mRotYVal);
      }

      Matrix4 mRotX;
      {
         genRotationMatrixAboutX(mRotX, DEG2RAD(180));
     
         Matrix4 mRotXVal (1,0,0,0,
                           0,cos(DEG2RAD(180)), -sin(DEG2RAD(180)),0,
                           0,sin(DEG2RAD(180)), cos(DEG2RAD(180)),0,
                           0,0,0,1);
         assert(mRotX == mRotXVal);
      }

      Matrix4 resultMatrix;
      {
         resultMatrix = mT * mRotX * mRotY;
         Matrix4 resultMatrixVal ( 0,0,1,1.5,
                                   0,-1,0,1.0,
                                   1,0,0,1.5,
                                   0,0,0,1);
         assert(resultMatrix == resultMatrixVal);
         resultMatrix.print();
      }

      {
         Vector4 pVal(1.5,0,1.5,1);

         Vector4 pOriginal(0,1,0,1);
         Vector4 p = resultMatrix * pOriginal;
         printVec(p);
         assert(p == pVal);
      }

   }
#pragma endregion 
   return 0;
}

int main()
{
   if(testVectors() < 0) {
      cout << "vectors failed" << endl;
      return -1;
   }

   if(testMatrices() < 0) {
      cout << "matrices failed" << endl;
      return -1;
   }

   cout << "all tests succeeded" << endl;
}
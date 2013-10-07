#include "Vector3D.h"
#include "Matrix.h"
#include <math.h>
#include <iostream>
#include <assert.h>

using namespace mord;
using namespace std;

int testVectors()
{
   {
      Vector3D a(10,0,0);
      a.normalize();

      Vector3D b(1,0,0);
      
      if(a != b)
         return -1;
   }
   {
      Vector3D a(5,0,0);
      Vector3D b(0,5,0);
      Vector3D c(5,5,0);

      a = a+b;
      if(a != c)
         return -1;
      a = a-b;
      if(a == c)
         return -1;

      Vector3D d(15,0,0);
      a = a*3;
      if(a != d)
         return -1;
   }
   {
      Vector3D a(5,0,0);
      Vector3D b(0,5,0);
      Vector3D c(5,5,0);

      a += b;
      if(a != c)
         return -1;
      a -= b;
      if(a == c)
         return -1;

      Vector3D d(15,0,0);
      a *= 3;
      if(a != d)
         return -1;
   }

   {
      Vector3D a(10,0,0);
      Vector3D b(5,5,0);
      
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
      Vector3D a(1,0,0);
      Vector3D b(0,1,0);
      Vector3D c(0,0,1);

      Vector3D d = Vector3D::cross(a,b);
      if(c != d)
         return -1;
   }
   return 0;
}

int testMatrices()
{
   {
      Vector3D r1(1,2,3);
      Vector3D r2(4,5,6);
      Vector3D r3(7,8,9);

      Matrix3D m(r1.getX(), r1.getY(), r1.getZ(),
                 r2.getX(), r2.getY(), r2.getZ(),
                 r3.getX(), r3.getY(), r3.getZ());      
      Vector3D row1(m[0][0], m[0][1], m[0][2]);
      Vector3D row2(m[1][0], m[1][1], m[1][2]);
      Vector3D row3(m[2][0], m[2][1], m[2][2]);

      m.print();
      if(r1 != row1)
         return -1;
      if(r2 != row2)
         return -1;
      if(r3 != row3)
         return -1;

      Matrix3D m2(m);
      if(m != m2)
         return -1;

   }
   {
      Matrix3D m1(1,1,1,
                  2,2,2,
                  3,3,3);
      fprintf(stderr,"m1:\n");
      m1.print();
      Matrix3D m2(4,5,6,
                  4,5,6,
                  4,5,6);
      fprintf(stderr,"m2:\n");
      m2.print();
      
      Matrix3D m3;
      Matrix3D::mult(m3, m1, m2);
      fprintf(stderr,"m3:\n");
      m3.print();

      Matrix3D m4(12, 15, 18,
                  24, 30, 36,
                  36, 45, 54);
      assert(m3 == m4);
   }
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
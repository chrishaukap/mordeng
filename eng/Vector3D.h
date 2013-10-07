#ifndef VECTOR3D_H
#define VECTOR3D_H

namespace mord {

   class Vector3D {
   public:
      Vector3D(float x, float y, float z);
      Vector3D(const Vector3D&);

      void normalize();
      static Vector3D normalize(const Vector3D& rhs);

      float dot(const Vector3D& rhs);
      static float dot(const Vector3D& lhs, const Vector3D& rhs);
      Vector3D cross(const Vector3D& rhs);
      static Vector3D cross(const Vector3D& lhs, const Vector3D& rhs);
      
      // Vectors must be normalized before calling
      float angleBetweenNormalized(const Vector3D& other) const;
      static float angleBetweenNormalized(const Vector3D& lhs, const Vector3D& rhs);
      
      Vector3D operator+(const Vector3D& rhs);
      Vector3D& operator+=(const Vector3D& rhs);
      Vector3D operator-(const Vector3D& rhs);
      Vector3D& operator-=(const Vector3D& rhs);
      Vector3D operator*(float scalar);
      Vector3D& operator*=(float scalar);
      float operator*(const Vector3D& rhs);
      float operator*(const Vector3D& rhs) const;

      void operator=(const Vector3D& rhs);
      bool operator==(const Vector3D& rhs);
      bool operator!=(const Vector3D& rhs);

      float getX() const {return x;}
      float getY() const {return y;}
      float getZ() const {return z;}
      float getMagnitude() const {return magnitude;}
   private:
      void computeMagnitude();
      float x,y,z;
      float magnitude;
   };
}
#endif
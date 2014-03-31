#ifndef VECTOR3_H
#define VECTOR3_H

namespace mord {

   class Vector3 {
   public:
      Vector3(float x, float y, float z);
      Vector3(const Vector3&);

      void normalize();
      static Vector3 normalize(const Vector3& rhs);

      float dot(const Vector3& rhs);
      static float dot(const Vector3& lhs, const Vector3& rhs);
      Vector3 cross(const Vector3& rhs);
      static Vector3 cross(const Vector3& lhs, const Vector3& rhs);
      
      // Vectors must be normalized before calling
      float angleBetweenNormalized(const Vector3& other) const;
      static float angleBetweenNormalized(const Vector3& lhs, const Vector3& rhs);
      
      Vector3 operator+(const Vector3& rhs);
      Vector3& operator+=(const Vector3& rhs);
      Vector3 operator-(const Vector3& rhs);
      Vector3& operator-=(const Vector3& rhs);
      Vector3 operator*(float scalar);
      Vector3& operator*=(float scalar);
      float operator*(const Vector3& rhs);
      float operator*(const Vector3& rhs) const;

      void operator=(const Vector3& rhs);
      bool operator==(const Vector3& rhs);
      bool operator!=(const Vector3& rhs);

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
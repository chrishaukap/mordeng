#ifndef VECTOR4_H
#define VECTOR4_H

namespace mord {

   class Vector4 {
   public:
      Vector4(float x, float y, float z, float w=0);
      Vector4(const Vector4&);

      void normalize();
      static Vector4 normalize(const Vector4& rhs);

      float dot(const Vector4& rhs);
      static float dot(const Vector4& lhs, const Vector4& rhs);
      Vector4 cross(const Vector4& rhs);
      static Vector4 cross(const Vector4& lhs, const Vector4& rhs);
      
      // Vectors must be normalized before calling
      float angleBetweenNormalized(const Vector4& other) const;
      static float angleBetweenNormalized(const Vector4& lhs, const Vector4& rhs);
      
      Vector4 operator+(const Vector4& rhs);
      Vector4& operator+=(const Vector4& rhs);
      Vector4 operator-(const Vector4& rhs);
      Vector4& operator-=(const Vector4& rhs);
      Vector4 operator*(float scalar);
      Vector4& operator*=(float scalar);
      float operator*(const Vector4& rhs);
      float operator*(const Vector4& rhs) const;

      void operator=(const Vector4& rhs);
      bool operator==(const Vector4& rhs);
      bool operator!=(const Vector4& rhs);

      float getX() const {return x;}
      float getY() const {return y;}
      float getZ() const {return z;}
      float getW() const {return w;}
      float getMagnitude() const {return magnitude;}
   private:
      void computeMagnitude();
      float x,y,z,w;
      float magnitude;
   };
}
#endif
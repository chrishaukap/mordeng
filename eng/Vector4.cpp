#include "Vector4.h"
#include "math.h"
#include <assert.h>

// TODO: write a generic Vector class that can handle N dimension so we're not duplicating code

using namespace mord;

Vector4::Vector4(float _x, float _y, float _z) : 
   x(_x), y(_y), z(_z)
{
   computeMagnitude();
}

Vector4::Vector4(const Vector4& orig){
   *this = orig;
}

void Vector4::normalize(){
   x /= magnitude;
   y /= magnitude;
   z /= magnitude;
   magnitude = 1;
}
Vector4 Vector4::normalize(const Vector4& rhs){
   Vector4 ret(rhs);
   ret.normalize();
   return ret;
}

float Vector4::dot(const Vector4& rhs){
   return dot(*this, rhs);
}

float Vector4::dot(const Vector4& lhs, const Vector4& rhs){
   return lhs.getX() * rhs.getX() +
          lhs.getY() * rhs.getY() +
          lhs.getZ() * rhs.getZ();
}

Vector4 Vector4::cross(const Vector4& rhs){
   
   return Vector4(getY() * rhs.getZ() - getZ() * rhs.getY(),
                   getZ() * rhs.getX() - getX() * rhs.getZ(),
                   getX() * rhs.getY() - getY() * rhs.getX());
}

Vector4 Vector4::cross(const Vector4& lhs, const Vector4& rhs){
   return Vector4(lhs.getY() * rhs.getZ() - lhs.getZ() * rhs.getY(),
                   lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ(),
                   lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX());
}

float Vector4::angleBetweenNormalized(const Vector4& other) const{
   return angleBetweenNormalized(*this, other);
}

float Vector4::angleBetweenNormalized(const Vector4& lhs, const Vector4& rhs){
   assert(lhs.getMagnitude() == 1.0 && rhs.getMagnitude() == 1.0);

   return acos( lhs * rhs );
}


Vector4 Vector4::operator+(const Vector4& rhs){
   return Vector4(getX() + rhs.getX(), 
                   getY() + rhs.getY(),
                   getZ() + rhs.getZ());
}

Vector4& Vector4::operator+=(const Vector4& rhs){
   x += rhs.getX();
   y += rhs.getY();
   z += rhs.getZ();
   computeMagnitude();
   return *this;
}


Vector4 Vector4::operator-(const Vector4& rhs){
   return Vector4(getX() - rhs.getX(), 
                   getY() - rhs.getY(),
                   getZ() - rhs.getZ());
}

Vector4& Vector4::operator-=(const Vector4& rhs){
   x -= rhs.getX();
   y -= rhs.getY();
   z -= rhs.getZ();
   computeMagnitude();
   return *this;
}

Vector4 Vector4::operator*(float scalar){
   return Vector4(getX() * scalar, 
                   getY() * scalar,
                   getZ() * scalar);
}

Vector4& Vector4::operator*=(float scalar){
   x *= scalar;
   y *= scalar;
   z *= scalar;
   magnitude *= scalar;
   return *this;
}

float Vector4::operator*(const Vector4& rhs){
   return dot(*this, rhs);
}

float Vector4::operator*(const Vector4& rhs) const{
   return dot(*this, rhs);
}

void Vector4::operator=(const Vector4& rhs){
   x = rhs.getX();
   y = rhs.getY();
   z = rhs.getZ();
   magnitude = rhs.getMagnitude();
}

bool Vector4::operator==(const Vector4& rhs){
   return ( x == rhs.getX() &&
            y == rhs.getY() &&
            z == rhs.getZ() &&
            magnitude == rhs.getMagnitude());
}

bool Vector4::operator!=(const Vector4& rhs){
   return !operator==(rhs);
}

void Vector4::computeMagnitude()
{
   magnitude = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}
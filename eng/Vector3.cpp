#include "Vector3.h"
#include "math.h"
#include <assert.h>


using namespace mord;

Vector3::Vector3(float _x, float _y, float _z) : 
   x(_x), y(_y), z(_z)
{
   computeMagnitude();
}

Vector3::Vector3(const Vector3& orig){
   *this = orig;
}

void Vector3::normalize(){
   x /= magnitude;
   y /= magnitude;
   z /= magnitude;
   magnitude = 1;
}
Vector3 Vector3::normalize(const Vector3& rhs){
   Vector3 ret(rhs);
   ret.normalize();
   return ret;
}

float Vector3::dot(const Vector3& rhs){
   return dot(*this, rhs);
}

float Vector3::dot(const Vector3& lhs, const Vector3& rhs){
   return lhs.getX() * rhs.getX() +
          lhs.getY() * rhs.getY() +
          lhs.getZ() * rhs.getZ();
}

Vector3 Vector3::cross(const Vector3& rhs){
   
   return Vector3(getY() * rhs.getZ() - getZ() * rhs.getY(),
                   getZ() * rhs.getX() - getX() * rhs.getZ(),
                   getX() * rhs.getY() - getY() * rhs.getX());
}

Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs){
   return Vector3(lhs.getY() * rhs.getZ() - lhs.getZ() * rhs.getY(),
                   lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ(),
                   lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX());
}

float Vector3::angleBetweenNormalized(const Vector3& other) const{
   return angleBetweenNormalized(*this, other);
}

float Vector3::angleBetweenNormalized(const Vector3& lhs, const Vector3& rhs){
   assert(lhs.getMagnitude() == 1.0 && rhs.getMagnitude() == 1.0);

   return acos( lhs * rhs );
}


Vector3 Vector3::operator+(const Vector3& rhs){
   return Vector3(getX() + rhs.getX(), 
                   getY() + rhs.getY(),
                   getZ() + rhs.getZ());
}

Vector3& Vector3::operator+=(const Vector3& rhs){
   x += rhs.getX();
   y += rhs.getY();
   z += rhs.getZ();
   computeMagnitude();
   return *this;
}


Vector3 Vector3::operator-(const Vector3& rhs){
   return Vector3(getX() - rhs.getX(), 
                   getY() - rhs.getY(),
                   getZ() - rhs.getZ());
}

Vector3& Vector3::operator-=(const Vector3& rhs){
   x -= rhs.getX();
   y -= rhs.getY();
   z -= rhs.getZ();
   computeMagnitude();
   return *this;
}

Vector3 Vector3::operator*(float scalar){
   return Vector3(getX() * scalar, 
                   getY() * scalar,
                   getZ() * scalar);
}

Vector3& Vector3::operator*=(float scalar){
   x *= scalar;
   y *= scalar;
   z *= scalar;
   magnitude *= scalar;
   return *this;
}

float Vector3::operator*(const Vector3& rhs){
   return dot(*this, rhs);
}

float Vector3::operator*(const Vector3& rhs) const{
   return dot(*this, rhs);
}

void Vector3::operator=(const Vector3& rhs){
   x = rhs.getX();
   y = rhs.getY();
   z = rhs.getZ();
   magnitude = rhs.getMagnitude();
}

bool Vector3::operator==(const Vector3& rhs){
   return ( x == rhs.getX() &&
            y == rhs.getY() &&
            z == rhs.getZ() &&
            magnitude == rhs.getMagnitude());
}

bool Vector3::operator!=(const Vector3& rhs){
   return !operator==(rhs);
}

void Vector3::computeMagnitude()
{
   magnitude = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}
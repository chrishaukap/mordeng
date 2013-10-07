#include "Vector3D.h"
#include "math.h"
#include <assert.h>


using namespace mord;

Vector3D::Vector3D(float _x, float _y, float _z) : 
   x(_x), y(_y), z(_z)
{
   computeMagnitude();
}

Vector3D::Vector3D(const Vector3D& orig){
   *this = orig;
}

void Vector3D::normalize(){
   x /= magnitude;
   y /= magnitude;
   z /= magnitude;
   magnitude = 1;
}
Vector3D Vector3D::normalize(const Vector3D& rhs){
   Vector3D ret(rhs);
   ret.normalize();
   return ret;
}

float Vector3D::dot(const Vector3D& rhs){
   return dot(*this, rhs);
}

float Vector3D::dot(const Vector3D& lhs, const Vector3D& rhs){
   return lhs.getX() * rhs.getX() +
          lhs.getY() * rhs.getY() +
          lhs.getZ() * rhs.getZ();
}

Vector3D Vector3D::cross(const Vector3D& rhs){
   
   return Vector3D(getY() * rhs.getZ() - getZ() * rhs.getY(),
                   getZ() * rhs.getX() - getX() * rhs.getZ(),
                   getX() * rhs.getY() - getY() * rhs.getX());
}

Vector3D Vector3D::cross(const Vector3D& lhs, const Vector3D& rhs){
   return Vector3D(lhs.getY() * rhs.getZ() - lhs.getZ() * rhs.getY(),
                   lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ(),
                   lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX());
}

float Vector3D::angleBetweenNormalized(const Vector3D& other) const{
   return angleBetweenNormalized(*this, other);
}

float Vector3D::angleBetweenNormalized(const Vector3D& lhs, const Vector3D& rhs){
   assert(lhs.getMagnitude() == 1.0 && rhs.getMagnitude() == 1.0);

   return acos( lhs * rhs );
}


Vector3D Vector3D::operator+(const Vector3D& rhs){
   return Vector3D(getX() + rhs.getX(), 
                   getY() + rhs.getY(),
                   getZ() + rhs.getZ());
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs){
   x += rhs.getX();
   y += rhs.getY();
   z += rhs.getZ();
   computeMagnitude();
   return *this;
}


Vector3D Vector3D::operator-(const Vector3D& rhs){
   return Vector3D(getX() - rhs.getX(), 
                   getY() - rhs.getY(),
                   getZ() - rhs.getZ());
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs){
   x -= rhs.getX();
   y -= rhs.getY();
   z -= rhs.getZ();
   computeMagnitude();
   return *this;
}

Vector3D Vector3D::operator*(float scalar){
   return Vector3D(getX() * scalar, 
                   getY() * scalar,
                   getZ() * scalar);
}

Vector3D& Vector3D::operator*=(float scalar){
   x *= scalar;
   y *= scalar;
   z *= scalar;
   magnitude *= scalar;
   return *this;
}

float Vector3D::operator*(const Vector3D& rhs){
   return dot(*this, rhs);
}

float Vector3D::operator*(const Vector3D& rhs) const{
   return dot(*this, rhs);
}

void Vector3D::operator=(const Vector3D& rhs){
   x = rhs.getX();
   y = rhs.getY();
   z = rhs.getZ();
   magnitude = rhs.getMagnitude();
}

bool Vector3D::operator==(const Vector3D& rhs){
   return ( x == rhs.getX() &&
            y == rhs.getY() &&
            z == rhs.getZ() &&
            magnitude == rhs.getMagnitude());
}

bool Vector3D::operator!=(const Vector3D& rhs){
   return !operator==(rhs);
}

void Vector3D::computeMagnitude()
{
   magnitude = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}
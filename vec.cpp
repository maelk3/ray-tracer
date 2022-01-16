#include "vec.h"
#include <cmath>
#include <stdlib.h>

vec3::vec3(){}

vec3::vec3(float x, float y, float z){
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

float vec3::x() const { return data[0]; }
float vec3::y() const { return data[1]; }
float vec3::z() const { return data[2]; }

float vec3::r() const { return data[0]; }
float vec3::g() const { return data[1]; }
float vec3::b() const { return data[2]; }


vec3& vec3::operator+=(const vec3& other){
  data[0] += other.x();
  data[1] += other.y();
  data[2] += other.z();
  return *this;
}

vec3& vec3::operator-=(const vec3& other){
  data[0] -= other.x();
  data[1] -= other.y();
  data[2] -= other.z();
  return *this;
}
vec3& vec3::operator*=(float scalar){
  data[0] *= scalar;
  data[1] *= scalar;
  data[2] *= scalar;
  return *this;
}

float vec3::operator[](int i) const {
  return data[i];
}
float& vec3::operator[](int i){
  return data[i];
}

float vec3::norm() const {
  return sqrt(this->norm_squared());
}

float vec3::norm_squared() const {
  return dot(*this, *this);
}

vec3& vec3::normalize(){
  *this *= 1/this->norm();
  return *this;
}

vec3 operator+(const vec3& a, const vec3& b){
  return {a.x()+b.x(), a.y()+b.y(), a.z()+b.z()};
}

vec3 operator-(const vec3& a, const vec3& b){
  return {a.x()-b.x(), a.y()-b.y(), a.z()-b.z()};
}

vec3 operator*(float scalar, const vec3& vec){
  return {scalar*vec.x(), scalar*vec.y(), scalar*vec.z()};
}

vec3 operator*(const vec3& a, const vec3& b){
  return {a.x()*b.x(), a.y()*b.y(), a.z()*b.z()};
}

vec3 operator-(const vec3& vec){
  return {-vec.x(), -vec.y(), -vec.z()};
}
vec3 operator+(const vec3& vec){
  return vec;
}

vec3 operator+(const vec3& a, vec3&& b){
  return b+=a;
}

vec3 operator+(vec3&& a, const vec3& b){
  return a+=b;
}

vec3 operator+(vec3&& a, vec3&& b){
  return a+=b;
}

vec3 operator-(const vec3& a, vec3&& b){
  b[0] = a[0]-b[0];
  b[1] = a[1]-b[1];
  b[2] = a[2]-b[2];   
  return b;
}

vec3 operator-(vec3&& a, const vec3& b){
  return a-=b;
}

vec3 operator-(vec3&& a, vec3&& b){
  return a-=b;
}

vec3 cross(const vec3& a, const vec3& b){
  return {a.y()*b.z()-a.z()*b.y(),
          a.z()*b.x()-a.x()*b.z(),
          a.x()*b.y()-a.y()*b.x()};
}

float dot(const vec3& a, const vec3& b){
  return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

vec3 unit_vector(vec3 vec){
  return vec.normalize();
}

std::ostream& operator<<(std::ostream& stream, const vec3& vec){
  return  stream << "vec3(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
}

float random_uniform(){
  return (float)rand()/((float)RAND_MAX);
}

vec3 get_random_unit(){
  return vec3(2.0*random_uniform()-1.0, 2.0*random_uniform()-1.0, 2.0*random_uniform()-1.0).normalize();
}

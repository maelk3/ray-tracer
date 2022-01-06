#pragma once
#include <iostream>

class vec3 {
  float data[3];
 public:
  vec3(float x, float y, float z);

  // position getters
  float x() const;
  float y() const;
  float z() const;

  // colors getters
  float r() const;
  float g() const;
  float b() const;

  vec3& operator+=(const vec3& other);
  vec3& operator-=(const vec3& other);
  vec3& operator*=(float scalar);

  float operator[](int i) const;
  float& operator[](int i);
  
  float norm() const;
  float norm_squared() const;
  vec3& normalize();
};

// vector operations
vec3 operator+(const vec3& a, const vec3& b);
vec3 operator-(const vec3& a, const vec3& b);
vec3 operator*(float scalar, const vec3& vec);

vec3 operator-(const vec3& vec);
vec3 operator+(const vec3& vec);

vec3 operator+(const vec3& a, vec3&& b);
vec3 operator+(vec3&& a, const vec3& b);

vec3 operator-(const vec3& a, vec3&& b);
vec3 operator-(vec3&& a, const vec3& b);

float dot(const vec3& a, const vec3& b);

vec3 cross(const vec3& a, const vec3& b);

std::ostream& operator<<(std::ostream& stream, const vec3& vec);

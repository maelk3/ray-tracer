#include <iostream>
#include "vec.h"
#include "ray.h"

int main(){

  vec3 a {1, 2, 3};
  
  Ray ray(vec3(2, 4, 2), a + a);

  std::cout << ray << "\n";
  
  return 0;
}

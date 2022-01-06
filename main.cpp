#include <iostream>
#include "vec.h"

int main(){

  vec3 a(1, 2, 3);

  vec3 b = (a + a) + a;

  std::cout << b << "\n";
  std::cout << b.norm() << "\n";
  
  return 0;
}

#include <iostream>
#include "image.h"

int main(){

  Image test(256, 256);

  for(int i=0; i<256; i++)
    for(int j=0; j<256; j++)
      test(i, j) = {255, (unsigned char)j, (unsigned char)i};

  test.save_as("test.bmp");

  return 0;
}

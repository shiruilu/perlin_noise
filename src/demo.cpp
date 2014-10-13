#include "PerlinNoise.h"
#include "ppm.hpp"

#include <assert.h>
#include <cmath>
#include <iostream>
#include <cstring>

unsigned int width = 600, height = 450;
// Create an empty PPM image
PPM image(width, height);
// Init with seed
PerlinNoise pn(22);

void clearCanvas() {
  // White canvas
  for (int i=0; i < height; i++) {
    for (int j =0; j < width; j++) {
      image.r[i*width+j] = 255;
      image.g[i*width+j] = 255;
      image.b[i*width+j] = 255;
    }
  }
}

void drawLine(int x1, int x2, int y1, int y2, bool noise) {

  const unsigned int stroke = 2;
  const unsigned int variance=5;
  if (y1 == y2) {
    for (unsigned int j=x1; j < x2; j++) {
      unsigned int i = y1; //Start at y of the canvas
      if (noise) {
        //assert( pn.noise(10.0*j/width, 0.8, 0.8) <=1 && pn.noise(10.0*j/width, 0.8, 0.8) >= 0);
        std::cout << pn.noise(10.0*j/width, 0.8, 0.8) << std::endl;
        i += variance * (pn.noise(10.0*j/width, 0.8, 0.8) - 0.5) ;
      }
      for (unsigned int k=0; k<stroke; ++k) {
        assert((i+k)*width+j < width*height);
        image.r[(i+k)*width+j] = 0;
        image.g[(i+k)*width+j] = 0;
        image.b[(i+k)*width+j] = 0;
      }
    }
  }
  else if (x1 == x2) {
    for (unsigned int i=y1; i < y2; i++) {
      unsigned int j = x1; //Start at x of the canvas
      if (noise) {
        j += variance * (pn.noise(0.8, 20.0*i/height, 0.8) - 0.5) ;
      }
      for (unsigned int k=0; k<stroke; ++k) {
        assert(i*width+j+k < width*height);
        image.r[i*width+j+k] = 0;
        image.g[i*width+j+k] = 0;
        image.b[i*width+j+k] = 0;
      }
    }
  }
}

void drawSquare(int dis, bool noise) {
  drawLine(dis, width-dis, dis, dis, noise);
  drawLine(width-dis, width-dis, dis, height-dis, noise);
  drawLine(dis, width-dis, height-dis, height-dis, noise);
  drawLine(dis, dis, dis, height-dis, noise);
}

void wood() {

  for (unsigned int i=0; i < height; i++) {
    for (unsigned int j =0; j < width; j++) {
      double n = pn.noise( 1.0*i/width, 1.0*j/height, 1.0*(i+j)/width );
      n = 20*n - floor(20*n);
      image.r[i*width+j] = floor(255 * n);
      image.g[i*width+j] = floor(255 * n);
      image.b[i*width+j] = floor(255 * n);
    }
  }
}

void default_noise() {
  for (unsigned int i=0; i < height; i++) {
    for (unsigned int j =0; j < width; j++) {
      double n = pn.noise( 1.0*i/width, 1.0*j/height, 1.0*(i+j)/width );
      //n = 20*n - floor(20*n);
      image.r[i*width+j] = floor(255 * n);
      image.g[i*width+j] = floor(255 * n);
      image.b[i*width+j] = floor(255 * n);
    }
  }
}

void drawCircle() {
  const unsigned int R=100;
  const unsigned int RR=110;
  const unsigned int CX=width/2;
  const unsigned int CY=height/2;
  for (int i=0; i < height; i++) {
    for (int j =0; j < width; j++) {
      if((i-CY)*(i-CY) + (j-CX)*(j-CX) <=RR*RR && (i-CY)*(i-CY) + (j-CX)*(j-CX) >=R*R) {
        image.r[i*width+j] = 0;
        image.g[i*width+j] = 0;
        image.b[i*width+j] = 0;
      }
      else {
        image.r[i*width+j] = 255;
        image.g[i*width+j] = 255;
        image.b[i*width+j] = 255;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  clearCanvas();
  if ( !strcmp(argv[1], "-d")) { //default noise
    default_noise();
  }
  else if ( !strcmp(argv[1], "-w")) { // wood structure
    wood();
  }
  else if ( !strcmp(argv[1], "-c")) { // common square
    drawSquare(40, false);
  }
  else if ( !strcmp(argv[1], "-n")) { // square with noise
    drawSquare(40, true);
  }

  image.writeFile("demo.ppm");

  return 0;
}

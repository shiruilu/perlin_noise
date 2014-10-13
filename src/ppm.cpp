#include <iostream>
#include <fstream>
#include <sstream>

#include "ppm.hpp"

PPM::PPM() : _width(0), _height(0), _max_color_value(255)
{
  unsigned int size = _width * _height;
  r.resize(size);
  g.resize(size);
  b.resize(size);
}

PPM::PPM(const unsigned int width, const unsigned int height)
  : _max_color_value(255) {
  _width = width;
  _height = height;

  unsigned int size = _width * _height;
  r.resize(size);
  g.resize(size);
  b.resize(size);
}

//write the PPM image in fileName
void PPM::writeFile(const std::string &fileName) {
  std::ofstream ofp(fileName.c_str(), std::ios::out | std::ios::binary);
  if (ofp.is_open()) {
    ofp << "P6" << std::endl;
    ofp << _width << " " << _height << std::endl;
    ofp << _max_color_value << std::endl;

    char aux;
    for (int i = 0; i < _width * _height; ++i) {
      aux = (char) r[i];
      ofp.write(&aux, 1);
      aux = (char) g[i];
      ofp.write(&aux, 1);
      aux = (char) b[i];
      ofp.write(&aux, 1);
    }
  } else {
    std::cerr << "Error, Unable to open " << fileName << std::endl;
  }
  ofp.close();
}

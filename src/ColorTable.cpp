#include "ColorTable.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

ColorTable::ColorTable(const std::string &fileName) : rgb(MAX_COLOR_VALUE, std::vector<int>(3))
{
  std::ifstream ifp(fileName.c_str(), std::ios::in);
  if (ifp.is_open()) {
    double r=0, g=0, b=0;
    for (int i = 0; i < MAX_COLOR_VALUE; ++i) {
      ifp >> r >> g >> b;
      // std::cout << r << g << b;
      rgb[i][0] = floor(r * (MAX_COLOR_VALUE-1) );
      rgb[i][1] = floor(g * (MAX_COLOR_VALUE) );
      rgb[i][2] = floor(b * (MAX_COLOR_VALUE) );
      // std::cout << r << g << b << std::endl;
      
      // std::cout << rgb[i][0] << "," << rgb[i][1] << "," << rgb[i][2]%2 << std::endl;
    }
  } else {
    std::cerr << "Error, Unable to open file: " << fileName << std::endl;
  }
  ifp.close();
}
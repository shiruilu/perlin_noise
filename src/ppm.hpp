#ifndef _PPM_H_
#define _PPM_H_

#include <vector>
#include <string>

class PPM {
  unsigned int _width;
  unsigned int _height;
  unsigned int _max_color_value;
  
public:
  //R,G,B value
  std::vector<unsigned char> r;
  std::vector<unsigned char> g;
  std::vector<unsigned char> b;

public:
  PPM();
  PPM(const unsigned int width, const unsigned int height);
  void writeFile(const std::string &fileName);
};

#endif
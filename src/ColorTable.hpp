#ifndef COLORTABLE_H
#define COLORTABLE_H

#include <vector>
#include <string>

#define MAX_COLOR_VALUE 256

class ColorTable
{
public:
  // typedef double (*vec3)[3];
  std::vector< std::vector<int> > rgb;
  ColorTable(const std::string &fileName);
  virtual ~ColorTable() {}
};


#endif /* COLORTABLE_H */
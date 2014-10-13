#ifndef _PERLIN_NOISE_H_
#define _PERLIN_NOISE_H_

#include <vector>

class PerlinNoise {
  std::vector<int> p;
  inline double fade(double t) const { return t * t * t * (t * (t * 6 - 15) + 10); }
  inline double lerp(double a, double b, double t) const { return a * (1 - t) + b * t; }
  double grad(int hash, double x, double y, double z) const;
public:
  PerlinNoise(unsigned int seed);
  double noise(double x, double y, double z) const;
};

#endif
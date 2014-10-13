#include "PerlinNoise.h"
#include <assert.h>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

PerlinNoise::PerlinNoise(unsigned int seed)
{
  p.resize(256);
  std::iota(p.begin(), p.end(), 0);
  std::default_random_engine engine(seed);
  std::shuffle(p.begin(), p.end(), engine);
  p.insert(p.end(), p.begin(), p.end());
  p.insert(p.end(), p.begin(), p.end());
}

double PerlinNoise::grad(int hash, double x, double y, double z) const
{
  switch(hash & 0xF)
  {
    case 0x0: return  x + y;
    case 0x1: return -x + y;
    case 0x2: return  x - y;
    case 0x3: return -x - y;
    case 0x4: return  x + z;
    case 0x5: return -x + z;
    case 0x6: return  x - z;
    case 0x7: return -x - z;
    case 0x8: return  y + z;
    case 0x9: return -y + z;
    case 0xA: return  y - z;
    case 0xB: return -y - z;
    case 0xC: return  y + x;
    case 0xD: return -y + z;
    case 0xE: return  y - x;
    case 0xF: return -y - z;
    default: return 0; // never happens
  }
}

double PerlinNoise::noise(double x, double y, double z) const
{
  // Find the unit cube that contains the point
  int xi = (int) floor(x) & 255;
  int yi = (int) floor(y) & 255;
  int zi = (int) floor(z) & 255;
  assert( xi<256 && yi<256 && zi<256 );

  // Find relative x, y,z of point in cube
  double xf = x - floor(x);
  double yf = y - floor(y);
  double zf = z - floor(z);

  // Compute fade curves for each of x, y, z
  double u = fade(xf);
  double v = fade(yf);
  double w = fade(zf);

  // Hash coordinates of the 8 cube corners
  int aaa, aba, aab, abb, baa, bba, bab, bbb;
  aaa = p[p[p[ xi   ]+ yi   ]+ zi   ];
  aba = p[p[p[ xi   ]+ yi+1 ]+ zi   ];
  aab = p[p[p[ xi   ]+ yi   ]+ zi+1 ];
  abb = p[p[p[ xi   ]+ yi+1 ]+ zi+1 ];
  baa = p[p[p[ xi+1 ]+ yi   ]+ zi   ];
  bba = p[p[p[ xi+1 ]+ yi+1 ]+ zi   ];
  bab = p[p[p[ xi+1 ]+ yi   ]+ zi+1 ];
  bbb = p[p[p[ xi+1 ]+ yi+1 ]+ zi+1 ];
  assert( aaa<256 && aba<256 && aab<256 && abb<256 && baa<256 && bba<256 && bab<256 && bbb<256);
  // Add blended results from 8 corners of cube
  double x1, x2, y1, y2;
  x1 = lerp(  grad (aaa, xf  , yf  , zf),
              grad (baa, xf-1, yf  , zf),
              u);
  x2 = lerp(  grad (aba, xf  , yf-1, zf),
              grad (bba, xf-1, yf-1, zf),
              u);
  y1 = lerp(x1, x2, v);

  x1 = lerp(  grad (aab, xf  , yf  , zf-1),
              grad (bab, xf-1, yf  , zf-1),
              u);
  x2 = lerp(  grad (abb, xf  , yf-1, zf-1),
              grad (bbb, xf-1, yf-1, zf-1),
              u);
  y2 = lerp(x1, x2, v);

  // assert( -1.1<=y1 && y1<=1.1 && -1.1<=y2 && y2<=1.1 );
  return (lerp (y1, y2, w)+1.0)/2.0; // Bind to [0, 1]
}
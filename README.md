# Implementation and Application of Perlin Noise.

The result writes to a ppm file `demo.ppm`.

## Features
- Wood-like texture.
- Handwritten style square.

## To Build
```
cd build
cmake ../src/.
make
```

## To Run
- default noise example:
```
./perlin_noise -d
```
- wood like structure:
```
./perlin_noise -w
```
- normal square:
```
./perlin_noise -c
```
- handwritten style square (with noise):
```
./perlin_noise -n
```
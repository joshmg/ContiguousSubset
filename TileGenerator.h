// File: TileGenerator.h
// Written by Joshua Green

#ifndef TILE_GENERATOR_H
#define TILE_GENERATOR_H

#include "Vect2f.h"
#include <cmath>

template <typename T>
class TileGenerator {
  private:

  public:
  	TileGenerator() { }
  	~TileGenerator() { }

  	T* GetAt(const Vect2f& position, int size) {
      T* data = new T[size*size];
      for(int i=0;i<size*size;i++) {
        data[i] = 'a' + mod(i, 26);
      }

      return data;
  	}

  T* GetStripFrom(const Vect2f& p0, const Vect2f& p1) const {
    T* data;
    if (p0.x == p1.x) { // column
      int size = fabs(p0.y - p1.y);
      data = new T[size];

      for (int i=0;i<size;i++) { data[i] = '0' + mod(i, 10); }
    }
    else if (p0.y == p1.y) { // row
      int size = fabs(p0.y - p1.y);
      data = new T[size];

      for (int i=0;i<size;i++) { data[i] = '0' + mod(i, 10); }
    }
    else { // diagnal strip
      int x = (p1.x - p0.x), y = (p1.y - p0.y);
      int size = sqrt((float)(x*x + y*y));
      data = new T[size];

      for (int i=0;i<size;i++) { data[i] = '0' + mod(i, 10); }
    }

    return data;
  }
};

#endif

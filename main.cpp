// File: main.cpp
// Written by Joshua Green

#include <iostream>
#include "Contiguous.h"
using namespace std;


template <typename T, int S>
void print(const ContiguousSubset<T, S>& subset) {
  int tile_size = subset.GetTileWidth();

  Vect2f origin = subset.GetOrigin();
  Vect2f tile_offset = subset.GetOffset();
  cout << "Origin = (" << origin.x << ", " << origin.y << ")" << endl;
  cout << "Offset = (" << tile_offset.x << ", " << tile_offset.y << ")" << endl;

  tile_offset.y = tile_size - tile_offset.y - 1;

  const T* data = subset.GetTileData();
  cout << "data = " << endl;

  cout << " -";
  for(int j=0;j<tile_size+1;j++) cout << "--";
  cout << endl;

  for(int i=0;i<tile_size;i++) {
    cout << " |";
    if (i != tile_offset.y || 0 != tile_offset.x) cout << " ";
    for(int j=0;j<tile_size;j++) {
      if (i == tile_offset.y && j == tile_offset.x) cout << "[";
      cout << data[i*tile_size + j];
      if (i == tile_offset.y && j == tile_offset.x) cout << "]";
      else if (!(i == tile_offset.y && j == tile_offset.x-1)) cout << " ";
    }
    cout << "|" << endl;
  }

  cout << " -";
  for(int j=0;j<tile_size+1;j++) cout << "--";
  cout << endl << endl;
}

int main() {
  TileGenerator<char> tilegen;
  ContiguousSubset<char, 9> testle;

  testle.SetDataSource(&tilegen);

  testle.SetOrigin(Vect2f(10, 0));
  print(testle);

  testle.SetOrigin(Vect2f(12, 0));
  print(testle);

  testle.SetOrigin(Vect2f(0, 0));
  print(testle);

  return 0;
}

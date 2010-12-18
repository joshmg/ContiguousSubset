// File: Contiguous.h
// Written by Joshua Green

#ifndef CONTIGUOUS_H
#define CONTIGUOUS_H


#include "iContiguous.h"
#include "Vect2f.h"
#include "TileGenerator.h"

//#define TILE_SIZE 10

#include <iostream>
using namespace std;

// *** Begin Declarations *** //

template <typename T, int TILE_SIZE>
class ContiguousSubset : public iContiguousSubset<T> {
  private:
    TileGenerator<T>* _tile_generator;
    T* _data;
    
    Vect2f _origin, // the tile's position in world space
           _offset; // the origin's offset within the tile (the toroid marker)

    bool _initialized; // initially false, set to true once a tile source is given

    void _set_row(int offset);
    void _set_column(int offset);

  public:
    ContiguousSubset();
    ~ContiguousSubset();

    void SetDataSource(TileGenerator<T>*);

    void SetOrigin(const Vect2f&);
    Vect2f GetOrigin() const;

    Vect2f GetOffset() const;

    const T* GetTileData() const;
    int GetTileWidth() const;
};



// *** Begin Definitions *** //



template <typename T, int TILE_SIZE>
void ContiguousSubset<T, TILE_SIZE>::_set_row(int row) {
  // procedure takes a row id ("int row") (identified from 0 being lower row, TILE_SIZE-1 being top row),
  //   requests the row from the left most part of the tile, to the right most part of the tile
  //   and copies the row from left to right

  T* new_row_data = _tile_generator->GetStripFrom(Vect2f(_origin.x, _origin.y+row), Vect2f(_origin.x+TILE_SIZE, _origin.y+row));
  int index = (TILE_SIZE-row)*TILE_SIZE;

  for (int i=0;i<TILE_SIZE;i++) {
    _data[index] = new_row_data[i];
    index++; // advance a column
  }

  delete[] new_row_data;
}

template <typename T, int TILE_SIZE>
void ContiguousSubset<T, TILE_SIZE>::_set_column(int column) {
  // procedure takes a column id ("int column") (identified from 0 being left column, TILE_SIZE-1 being right col),
  //   requests the column from the bottom most part of the tile, to the top most part of the tile
  //   and copies the column from bottom to top

  T* new_col_data = _tile_generator->GetStripFrom(Vect2f(_origin.x+column, _origin.y), Vect2f(_origin.x+column, _origin.y+TILE_SIZE));
  int index = TILE_SIZE*TILE_SIZE - (TILE_SIZE-column); // (0,0) corresponds to bottom left corner

  for (int i=0;i<TILE_SIZE;i++) {
    _data[index] = new_col_data[i];
    index -= TILE_SIZE; // retreat a row
  }

  delete[] new_col_data;
}

template <typename T, int TILE_SIZE>
ContiguousSubset<T, TILE_SIZE>::ContiguousSubset() : _data(new T[TILE_SIZE*TILE_SIZE]), _initialized(false) { }

template <typename T, int TILE_SIZE>
ContiguousSubset<T, TILE_SIZE>::~ContiguousSubset() { delete[] _data; }

template <typename T, int TILE_SIZE>
void ContiguousSubset<T, TILE_SIZE>::SetDataSource(TileGenerator<T>* tgen) {
  _tile_generator = tgen;

  _origin.x = 0, _origin.y = 0;
  _data = _tile_generator->GetAt(_origin, TILE_SIZE);
  _initialized = true;
}

template <typename T, int TILE_SIZE>
void ContiguousSubset<T, TILE_SIZE>::SetOrigin(const Vect2f& new_origin) {
  if (!_initialized) return;

  Vect2f dist(new_origin.x - _origin.x, new_origin.y - _origin.y);

  if (abs(dist.x) > TILE_SIZE || abs(dist.y) > TILE_SIZE) {
    cout << "Refreshing entire tile.." << endl;
    delete[] _data;
    _data = _tile_generator->GetAt(_origin, TILE_SIZE);
    _origin = new_origin;

    _offset.x = 0, _offset.y = 0;
  }
  else {
    // acquire rows:
    cout << "Changed: ";
    for (int i=0;i<abs(dist.y);i++) {
      int step = ((i)*dist.y)/(float)(abs(dist.y));
      int row = mod(_offset.y + step, TILE_SIZE);
      _set_row( row );
      cout << "(Row: " << row << ") ";
    }

    // acquire columns:
    for (int i=0;i<abs(dist.x);i++) {
      int step = ((i)*dist.x)/(float)(abs(dist.x));
      int col = mod(_offset.x + step, TILE_SIZE);
      _set_column( col );
      cout << "(Col: " << col << ") ";
    }
    cout << endl;

    _offset.x = mod(_offset.x + dist.x, TILE_SIZE);
    _offset.y = mod(_offset.y + dist.y, TILE_SIZE);
  }
}

template <typename T, int TILE_SIZE>
Vect2f ContiguousSubset<T, TILE_SIZE>::GetOrigin() const { return _origin; }

template <typename T, int TILE_SIZE>
Vect2f ContiguousSubset<T, TILE_SIZE>::GetOffset() const { return _offset; }

template <typename T, int TILE_SIZE>
const T* ContiguousSubset<T, TILE_SIZE>::GetTileData() const { return _data; }

template <typename T, int TILE_SIZE>
int ContiguousSubset<T, TILE_SIZE>::GetTileWidth() const { return TILE_SIZE; }

#endif

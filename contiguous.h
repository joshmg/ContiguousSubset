// File: contiguous.h
// Written by Joshua Green

#ifndef CONTIGUOUS_H
#define CONTIGUOUS_H


#include "contiguous_interface.h"
#include "tile_generator.h"
#include "vectXf.h"

//#define TILE_SIZE 10

#include <iostream>
using namespace std;

// *** Begin Declarations *** //

template <typename T, int TILE_SIZE>
class ContiguousSubset : public IContiguousSubset<T> {
  private:
    TileGenerator<T>* _tile_generator;
    T* _data;
    int _data_size;
    vectf* _origin;
    vectf* _world_origin;
    vectf* _tile_size;

    int _dimension;

    bool _initialized;

    void _copy_row(int offset);
    void _copy_column(int offset);

  public:
    ContiguousSubset(int=2);
    ~ContiguousSubset();

    void SetDataSource(const char*);

    bool Init();

    void SetTileOrigin(const vectf* const);
    vectf* GetTileOrigin() const;

    vectf* GetOriginOffset() const;

    vectf* GetTileSize() const;

    const T* GetTileData() const;

    const T* Test();
};



// *** Begin Definitions *** //



template <typename T, int TILE_SIZE>
void ContiguousSubset<T, TILE_SIZE>::_copy_row(int offset) { // this function uses _world_origin and _origin
  // offset = +/-, for up or down "movement"

  if (_data_size == 0) return; // _data was not correctly initialized...

  vectf* world_position = _world_origin->clone();
  // (this always works assuming the GetWorldData wraps data upon reaching bounds)
  (*world_position)[0] -= TILE_SIZE/2; // offset the x-position so GetWorldData returns a strip centered at the origin
  (*world_position)[1] += offset; // modify row to point to the offset row

  T* world_data_strip = _tile_generator->GetWorldData_Row(world_position, TILE_SIZE); // get a strip of data centered at _origin with a width of TILE_SIZE

  /*cout << "strip = ";
  for (int i=0;i<TILE_SIZE;i++) cout << world_data_strip[i];
  cout << endl;*/

  // copy the data
  int row = mod((*_origin)[1]+offset-TILE_SIZE/2, TILE_SIZE); // "translate" origin to top, then calculate proper row index
  for (int i=0;i<TILE_SIZE;i++) {
    int column = mod(i + ((*_origin)[0]-TILE_SIZE/2), TILE_SIZE); // "translate" origin to the left, then calculate proper column index
    int index = column + row*TILE_SIZE; // pointer arithmetic...
    _data[index] = '0';//world_data_strip[i];
  }

  delete world_position;
  delete[] world_data_strip;
}

template <typename T, int TILE_SIZE>
void ContiguousSubset<T, TILE_SIZE>::_copy_column(int offset) { // this function uses _world_origin and _origin
  // offset = +/-, for left or right "movement"

  if (_data_size == 0) return; // _data was not correctly initialized...

  vectf* world_position = _world_origin->clone();
  // (this always works assuming the GetWorldData wraps data upon reaching bounds)
  (*world_position)[1] -= TILE_SIZE/2; // offset the y-position so GetWorldData returns a vertical strip centered at the origin
  (*world_position)[0] += offset; // modify row to point to the offset row

  T* world_data_strip = _tile_generator->GetWorldData_Column(world_position, TILE_SIZE); // get a strip of data centered at _origin with a height of TILE_SIZE

  // copy the data
  int column = mod(((*_origin)[0]+offset-TILE_SIZE/2), TILE_SIZE); // "translate" origin to the left, then calculate proper column index
  for (int i=0;i<TILE_SIZE;i++) {
    int row = mod(i+(*_origin)[1]-TILE_SIZE/2, TILE_SIZE); // "translate" origin to top, then calculate proper row index
    int index = column + row*TILE_SIZE; // pointer arithmetic...
    _data[index] = '0';//world_data_strip[i];
  }

  delete world_position;
  delete[] world_data_strip;
}

template <typename T, int TILE_SIZE>
ContiguousSubset<T, TILE_SIZE>::ContiguousSubset(int dimension) : _dimension(dimension), _initialized(false), _data_size(0) {
  if (_dimension > 4) _dimension = 4; // cap dimension

  _tile_generator = new TileGenerator<T>(TILE_SIZE, _dimension);
  _origin = new vect4f;
  _world_origin = new vect4f;
  _tile_size = new vect4f;

  // set tile size:
  for (int i=0;i<_dimension;i++) (*_tile_size)[i] = TILE_SIZE;
}

template <typename T, int TILE_SIZE>
ContiguousSubset<T, TILE_SIZE>::~ContiguousSubset() {
  delete _tile_generator;
  if (_initialized) delete[] _data;
  delete _origin;
  delete _tile_size;
}

template <typename T, int TILE_SIZE>
void ContiguousSubset<T, TILE_SIZE>::SetDataSource(const char* src) {
  _tile_generator->Init(src);
}

template <typename T, int TILE_SIZE>
bool ContiguousSubset<T, TILE_SIZE>::Init() {
  if (!_initialized) {
    _data = (*_tile_generator).LoadTileCenteredAt(_origin, &_data_size);
  }

  return _initialized;
}

template <typename T, int TILE_SIZE>
void ContiguousSubset<T, TILE_SIZE>::SetTileOrigin(const vectf* const new_origin) {
  // RESUME HERE:

  // re-align data:
  vect4f distance, tile_area;
  for (int i=0;i<_dimension;i++) {
    distance[i] = (*new_origin)[i]-(*_origin)[i]; // calculate delta-origin
    tile_area[i] = TILE_SIZE;
  }

  // at what point is it better to simply reload the tile?
  bool load_new = false;
  for (int i=0;i<_dimension;i++) {
    if (distance[i] >= tile_area[i]) {
      load_new = true;
      break;
    }
  }
  if (load_new) { // easy refresh of the tile...
    // reload new tile centered as origin
    if (_initialized) {
      delete _data;
      _data = (*_tile_generator).LoadTileCenteredAt(new_origin, &_data_size);
    }
  }
  else { // calculate tile modifications, offsets, etc...
    for (int i=0;i<_dimension;i++) {
      for (int j=0;j<abs(distance[i]);j++) {
        if (i == 0) { // calculating x-value variants :. reloading columns
          _copy_column(j-j*j/distance[i]);
        }
        else if (i == 1) { // calculating y-value variants :. reloading rows
          _copy_row(j-j*j/distance[i]);
        }
      }
    }
  }

  for (int i=0;i<_dimension;i++) (*_origin)[i] = (*new_origin)[i]; // reassign incoming value to private data member
}

template <typename T, int TILE_SIZE>
vectf* ContiguousSubset<T, TILE_SIZE>::GetTileOrigin() const { return _origin->clone(); }

template <typename T, int TILE_SIZE>
vectf* ContiguousSubset<T, TILE_SIZE>::GetOriginOffset() const { return new vect4f; }

template <typename T, int TILE_SIZE>
vectf* ContiguousSubset<T, TILE_SIZE>::GetTileSize() const { return _tile_size->clone(); }

template <typename T, int TILE_SIZE>
const T* ContiguousSubset<T, TILE_SIZE>::GetTileData() const { return _data; }

template <typename T, int TILE_SIZE>
const T* ContiguousSubset<T, TILE_SIZE>::Test() {
  _copy_column(0);
  _copy_row(-1);
  _copy_row(0);
  _copy_row(1);
  return _data;
}

#endif

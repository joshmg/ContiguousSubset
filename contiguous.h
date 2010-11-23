// File: contiguous.h
// Written by Joshua Green

#ifndef CONTIGUOUS_H
#define CONTIGUOUS_H


#include "contiguous_interface.h"
#include "tile_generator.h"
#include "vectXf.h"

#define TILE_SIZE 100000

// *** Begin Declarations *** //

template <typename T>
class ContiguousSubset : public IContiguousSubset<T> {
  private:
    TileGenerator<T>* _tile_generator;
    T* _data;
    vectf* _origin;
    vectf* _tile_size;

    int _dimension;

  public:
    ContiguousSubset(int=2);
    ~ContiguousSubset();

    void SetDataSource(const char*);

    void SetTileOrigin(const vectf* const);
    vectf* GetTileOrigin() const;

    vectf* GetOriginOffset() const;

    vectf* GetTileSize() const;

    const T* GetTileData(const vectf* const) const;
    const T* GetWorldData(const vectf* const) const;
};



// *** Begin Definitions *** //



template <typename T>
ContiguousSubset<T>::ContiguousSubset(int dimension) : _dimension(dimension) {
  if (_dimension > 4) _dimension = 4; // cap dimension

  _tile_generator = new TileGenerator<T>();
  _data = new T[TILE_SIZE*_dimension];
  _origin = new vect4f;
  _tile_size = new vect4f;

  // set tile size:
  for (int i=0;i<_dimension;i++) (*_tile_size)[i] = TILE_SIZE;
}

template <typename T>
ContiguousSubset<T>::~ContiguousSubset() {
  delete _tile_generator;
  delete[] _data;
  delete _origin;
  delete _tile_size;
}

template <typename T>
void ContiguousSubset<T>::SetDataSource(const char* src) {
  _tile_generator->Init(src);
}

template <typename T>
void ContiguousSubset<T>::SetTileOrigin(const vectf* const new_origin) {
  for (int i=0;i<_dimension;i++) (*_origin)[i] = (*new_origin)[i];
}

template <typename T>
vectf* ContiguousSubset<T>::GetTileOrigin() const { return _origin->clone(); }

template <typename T>
vectf* ContiguousSubset<T>::GetOriginOffset() const { return new vect4f; }

template <typename T>
vectf* ContiguousSubset<T>::GetTileSize() const { return _tile_size->clone(); }

template <typename T>
const T* ContiguousSubset<T>::GetTileData(const vectf* const) const { return _data; }

template <typename T>
const T* ContiguousSubset<T>::GetWorldData(const vectf* const) const { return _data; }

#endif

// File: iContiguous.h
// Written by Joshua Green

#ifndef ICONTIGUOUS_H
#define ICONTIGUOUS_H

#include "Vect2f.h"
#include "TileGenerator.h"

template <typename T>
class iContiguousSubset {
  public:
    virtual void SetDataSource(TileGenerator<T>*) = 0;

    virtual void SetOrigin(const Vect2f&) = 0;
    virtual Vect2f GetOrigin() const = 0;

    virtual Vect2f GetOffset() const = 0;

    virtual const T* GetTileData() const = 0;
    virtual int GetTileWidth() const = 0;
};

#endif

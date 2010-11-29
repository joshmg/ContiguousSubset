// File: contiguous_interface.h
// Written by Joshua Green

#ifndef ICONTIGUOUS_H
#define ICONTIGUOUS_H

#include "vectXf.h"

template <typename T>
class IContiguousSubset {
  public:
    virtual void SetDataSource(const char*) = 0;

    virtual void SetTileOrigin(const vectf* const) = 0;
    virtual vectf* GetTileOrigin() const = 0;

    virtual vectf* GetOriginOffset() const = 0;

    virtual vectf* GetTileSize() const = 0;

    virtual const T* GetTileData() const = 0;
};

#endif

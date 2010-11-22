// File: contiguous.h
// Written by Joshua Green

#ifndef CONTIGUOUS_H
#define CONTIGUOUS_H


#include "contiguous_interface.h"

template <typename DataType, class Utilty>
class ContiguousSubset : public IContiguousSubset<DataType, Utility> {
  private:
    typedef Utility::Point Point;
    ITileFactory* _tile_factory;

  public:
    ContiguousSubset();
    ~ContiguousSubset();

    void set_tile_origin(Utility::Point);
    Utility::Point get_tile_origin() const;

    int get_origin_offset() const;

    int get_tile_size() const; // assuming square/cube/etc tiles

    DataType get_tile_data(Utility::Point) const;
    DataType get_world_data(Utility::Point) const;
};

#endif

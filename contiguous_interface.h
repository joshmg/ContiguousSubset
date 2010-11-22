// File: contiguous_interface.h
// Written by Joshua Green

#ifndef ICONTIGUOUS_H
#define ICONTIGUOUS_H


template <typename DataType, class Utilty>
class IContiguousSubset {
  public:
    virtual void set_tile_origin(Utility::Point) = 0;
    virtual Utility::Point get_tile_origin() const = 0;

    // these functions could easily be calculated with get_tile_size()...
    //virtual void set_tile_center(Utility::Point) = 0;
    //virtual Utility::Point get_tile_center() const = 0;

    virtual int get_origin_offset() const = 0;

    virtual int get_tile_size() const = 0; // assuming square/cube/etc tiles
    //virtual void GetTileSize(Utility::Point) const = 0;

    virtual DataType get_tile_data(Utility::Point) const = 0;
    virtual DataType get_world_data(Utility::Point) const = 0;
};

#endif

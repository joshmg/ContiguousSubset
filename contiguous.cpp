// File: contiguous.cpp
// Written by Joshua Green

#include "contiguous.h"

ContiguousSubset::ContiguousSubset() {
  _tile_factory = new TileFactory();
}

ContiguousSubset::~ContiguousSubset() {
  delete _tile_factory;
}

void ContiguousSubset::set_tile_origin(Utility::Point) {
  
}

Utility::Point ContiguousSubset::get_tile_origin() const {
  
}

int ContiguousSubset::get_origin_offset() const {
  
}

int ContiguousSubset::get_tile_size() const {
  
}

DataType ContiguousSubset::get_tile_data(Utility::Point) const {
  
}

DataType ContiguousSubset::get_world_data(Utility::Point) const {
  
}

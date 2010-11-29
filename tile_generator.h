// File: tile_generator.h
// Written by Joshua Green

#ifndef TILE_GEN_H
#define TILE_GEN_H

#include <cstring>
#include <iostream>

template <typename T>
class TileGenerator {
  private:
  	int _tile_size, _dimension;
  	char* _source;

  	bool _initialized;

    T* _data;
    int _data_width; // the width of data moreso than its size. ie: |_data| = _data_width^_dimension

  public:

  	TileGenerator(int tile_size, int dimension) : _tile_size(tile_size), _dimension(dimension), _initialized(false), _data_width(0) { }

  	~TileGenerator() {
      if (_initialized) delete _source;
  	}

    void Init(const char* source) {
      if (_initialized) {
        delete _source;
        delete _data;
      }

      int len = strlen(source);
      _source = new char[len+1];
      int c=0;
      while (c<len+1) _source[c] = source[c++];

      std::cout << "source file = " << _source << std::endl;

      // assign bogus data _data
      _data_width = 20;
      int size = pow((double)_data_width, _dimension);
      _data = new T[size];

      bool caps = true;
      for (int i=0;i<size;i++) {
        char letter;
        if (mod(i, _data_width) == 0) caps = !caps;

        if (caps) letter = 'A';
        else letter = 'a';

        _data[i] = letter + mod(i, 20);
      }
      _initialized = true;

      cout << " ";
      for (int j=0;j<_data_width+1;j++) cout << "--";
      cout << endl;

      for (int i=0;i<_data_width;i++) {
        cout << " |";
        for (int j=0;j<_data_width;j++) {
          cout << _data[i*_data_width + j] << " ";
        }
        cout << "|" << endl;
      }

      cout << " ";
      for (int j=0;j<_data_width+1;j++) cout << "--";
      cout << endl << endl;

    }

    T* LoadTileCenteredAt(const vectf* const origin, int* tile_data_size=0) const {
      int temp;
      if (tile_data_size == 0) tile_data_size = &temp; // if no data_size was given

      *tile_data_size = (int)pow((double)_tile_size, _dimension);
      int _data_size = (int)pow((double)_data_width, _dimension);

      if (_initialized) {
        T* tile_data = new T[*tile_data_size];
        //for (int i=0;i<*tile_data_size;i++) tile_data[i] = '0';

        for (int d=0;d<_dimension-1;d++) { // does this accomplish row-major 3d to linear storage? 2d yes, but 3d?
          for (int i=0;i<_tile_size;i++) {
            for (int j=0;j<_tile_size;j++) {
              int row = mod((i+(*origin)[d+1]), _data_width);
              int column = mod(j + (*origin)[d+0], _data_width);

              tile_data[i*_tile_size + j] = _data[row*_data_width + column];
            }
          }
        }
        return tile_data;
      }
      else {
        *tile_data_size = 0;
        return 0;
      }
    }

    T* GetWorldData_Row(const vectf* const position, int size) {
      T* data = new T[size];

      int _data_size = pow((double)_data_width, _dimension);

      int row = mod((*position)[1], _data_width);
      for (int i=0;i<size;i++) {
        int column = mod((*position)[0] + i, _data_width);
        int index = column + row*_data_width;
        data[i] = _data[mod(index, _data_size)];
      }

      return data;
    }

    T* GetWorldData_Column(const vectf* const position, int size) {
      T* data = new T[size];

      int _data_size = pow((double)_data_width, _dimension);

      int column = mod((*position)[0], _data_width);
      for (int i=0;i<size;i++) {
        int row = mod((*position)[1] + i, _data_width);
        int index = column + row*_data_width;
        data[i] = _data[mod(index, _data_size)];
      }

      return data;
    }
};

#endif

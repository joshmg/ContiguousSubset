// File: main.cpp
// Written by Joshua Green

#include "contiguous_interface.h"
#include "contiguous.h"
#include "vectXf.h"
#include <iostream>
using namespace std;

int main() {
  ContiguousSubset<char, 10> test(2);
  test.SetDataSource("dat/1.JPG");

  test.SetTileOrigin(&vectf(0, 0));
  test.Init();


  // move the origin:
  test.SetTileOrigin(&vectf(2, 2));
  vectf* origin = test.GetTileOrigin();
  cout << "(" << (*origin)[0] << ", " << (*origin)[1] << ")" << endl;

  const char* data = test.GetTileData();
  cout << "data = " << endl;

  cout << " ";
  for(int j=0;j<10+1;j++) cout << "--";
  cout << endl;

  for(int i=0;i<10;i++) {
    cout << " |";
    for(int j=0;j<10;j++) {
      if (i == (*origin)[1] && j == (*origin)[0]) cout << "[";
      cout << data[i*10 + j];
      if (i == (*origin)[1] && j == (*origin)[0]) cout << "]";
      else if (!(i == (*origin)[1] && j == (*origin)[0]-1)) cout << " ";
    }
    cout << "|" << endl;
  }

  cout << " ";
  for(int j=0;j<10+1;j++) cout << "--";
  cout << endl;

  delete data;
  delete origin;

  return 0;
}

// File: main.cpp
// Written by Joshua Green

#include "contiguous_interface.h"
#include "contiguous.h"
#include "vectXf.h"
#include <iostream>
using namespace std;

int main() {
  cout << "This program effectively allocates 300kb of memory, prints stuff, and then quits." << endl;

  ContiguousSubset<unsigned char> test(3);
  test.SetDataSource("data.dat");

  test.SetTileOrigin(&vect3f(0, 0, 0));
  vectf* origin = test.GetTileOrigin();
  cout << origin->to_string() << endl;
  delete origin;

  char c;
  cin >> c;

  return 0;
}

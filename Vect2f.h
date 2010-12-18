// File: Vect2f.h
// Written by Joshua Green

#ifndef VECT2F_H
#define VECT2F_H

int mod(int a, int b) { return a%b < 0 ? a%b+b : a%b; }

struct Vect2f {
  float x, y;
  Vect2f() : x(0), y(0) {};
  Vect2f(float _x, float _y) : x(_x), y(_y) {};
};

#endif

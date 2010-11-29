// File: vectXf.h
// Written by Joshua Green

#ifndef vectXf_H
#define vectXf_H

//#include "str/str.h"
//#include <string>
//#include <vector>

int mod(int a, int b);

struct vectf {
  int x, y;
  int _out_of_bounds;

  vectf();
  vectf(int _x, int _y);

  virtual vectf* clone() const { return new vectf(*this); }

  virtual int& operator[](int);
  virtual const int& operator[](int) const;

  virtual bool operator==(const vectf& p) const;
  virtual bool operator!=(const vectf& p) const;
  vectf operator*(int c) const;
  vectf operator/(int c) const;
  vectf operator+(const vectf& p) const;
  vectf operator-(const vectf& p) const;
  virtual void operator+=(const vectf& p);
  virtual void operator-=(const vectf& p);
  virtual void normalize();
  virtual int magnitude() const;

  vectf cross() const;
  virtual int dot(const vectf&) const;

  //virtual std::string to_string() const;
  //virtual vectf& from_string(std::string data);

  virtual void clear();
};

struct vect3f : public vectf {
  int z;

  vect3f();
  vect3f(int _x, int _y, int _z);
  virtual vectf* clone() const { return new vect3f(*this); }

  virtual int& operator[](int);
  virtual const int& operator[](int) const;

  virtual bool operator==(const vect3f& p) const;
  virtual bool operator!=(const vect3f& p) const;
  vect3f operator*(int c) const;
  vect3f operator/(int c) const;
  vect3f operator+(const vect3f& p) const;
  vect3f operator-(const vect3f& p) const;
  virtual void operator*=(int);
  virtual void operator/=(int);
  virtual void operator+=(const vect3f& p);
  virtual void operator-=(const vect3f& p);
  virtual void normalize();
  virtual int magnitude() const;

  vect3f cross(const vect3f& p) const;
  virtual int dot(const vect3f&) const;

  //virtual std::string to_string() const;
  //virtual vect3f& from_string(std::string data);

  virtual void clear();
};

struct vect4f : public vectf {
  int z, a;
  mutable int temp[4];

  vect4f();
  vect4f(int _x, int _y, int _z, int _a);

  virtual vectf* clone() const { return new vect4f(*this); }

  virtual operator const int* () const;

  virtual int& operator[](int);
  virtual const int& operator[](int) const;

  virtual bool operator==(const vect4f& p) const;
  virtual bool operator!=(const vect4f& p) const;
  vect4f operator*(int c) const;
  vect4f operator/(int c) const;
  vect4f operator+(const vect4f& p) const;
  vect4f operator-(const vect4f& p) const;
  virtual void operator*=(int);
  virtual void operator/=(int);
  virtual void operator+=(const vect4f& p);
  virtual void operator-=(const vect4f& p);
  virtual void normalize();
  virtual int magnitude() const;

  virtual int dot(const vect4f&) const;

  //virtual std::string to_string() const;
  //virtual vect4f& from_string(std::string data);

  virtual void clear();
};

#endif

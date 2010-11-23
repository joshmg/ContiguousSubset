// File: vectXf.h
// Written by Joshua Green

#ifndef vectXf_H
#define vectXf_H

#include "str/str.h"
#include <string>
#include <vector>

int mod(int a, int b);

struct vectf {
  float x, y;
  float _out_of_bounds;

  vectf();
  vectf(float _x, float _y);

  virtual vectf* clone() const { return new vectf(*this); }

  virtual float& operator[](int);
  virtual const float& operator[](int) const;

  virtual bool operator==(const vectf& p) const;
  virtual bool operator!=(const vectf& p) const;
  vectf operator*(float c) const;
  vectf operator/(float c) const;
  vectf operator+(const vectf& p) const;
  vectf operator-(const vectf& p) const;
  virtual void operator+=(const vectf& p);
  virtual void operator-=(const vectf& p);
  virtual void normalize();

  vectf cross() const;
  virtual float dot(const vectf&) const;

  virtual std::string to_string() const;
  virtual vectf& from_string(std::string data);

  virtual void clear();
};

struct vect3f : public vectf {
  float z;

  vect3f();
  vect3f(float _x, float _y, float _z);
  virtual vectf* clone() const { return new vect3f(*this); }

  virtual float& operator[](int);
  virtual const float& operator[](int) const;

  virtual bool operator==(const vect3f& p) const;
  virtual bool operator!=(const vect3f& p) const;
  vect3f operator*(float c) const;
  vect3f operator/(float c) const;
  vect3f operator+(const vect3f& p) const;
  vect3f operator-(const vect3f& p) const;
  virtual void operator*=(float);
  virtual void operator/=(float);
  virtual void operator+=(const vect3f& p);
  virtual void operator-=(const vect3f& p);
  virtual void normalize();

  vect3f cross(const vect3f& p) const;
  virtual float dot(const vect3f&) const;

  virtual std::string to_string() const;
  virtual vect3f& from_string(std::string data);

  virtual void clear();
};

struct vect4f : public vectf {
  float z, a;
  mutable float temp[4];

  vect4f();
  vect4f(float _x, float _y, float _z, float _a);

  virtual vectf* clone() const { return new vect4f(*this); }

  virtual operator const float* () const;

  virtual float& operator[](int);
  virtual const float& operator[](int) const;

  virtual bool operator==(const vect4f& p) const;
  virtual bool operator!=(const vect4f& p) const;
  vect4f operator*(float c) const;
  vect4f operator/(float c) const;
  vect4f operator+(const vect4f& p) const;
  vect4f operator-(const vect4f& p) const;
  virtual void operator*=(float);
  virtual void operator/=(float);
  virtual void operator+=(const vect4f& p);
  virtual void operator-=(const vect4f& p);
  virtual void normalize();

  virtual float dot(const vect4f&) const;

  virtual std::string to_string() const;
  virtual vect4f& from_string(std::string data);

  virtual void clear();
};

#endif

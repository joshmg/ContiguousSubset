// File: vectXf.cpp
// Written by Joshua Green

#include "vectXf.h"
#include <cmath>
//#include "str/str.h"
//#include <string>
//#include <vector>
using namespace std;

int mod(int a, int b) { return a%b < 0 ? a%b+b : a%b; }



// **** begin class vectf definitions **** //
vectf::vectf() : x(0.0f), y(0.0f) { }
vectf::vectf(int _x, int _y) : x(_x), y(_y) { }

int& vectf::operator[](int index) {
  switch(index) {
    case 0: { return x; } break;
    case 1: { return y; } break;
    default: { return _out_of_bounds; } break;
  }
}
const int& vectf::operator[](int index) const {
  switch(index) {
    case 0: { return x; } break;
    case 1: { return y; } break;
    default: { return _out_of_bounds; } break;
  }
}

bool vectf::operator==(const vectf& p) const { return ((x == p.x) && (y == p.x)); }
bool vectf::operator!=(const vectf& p) const { return ((x != p.x) || (y != p.x)); }
vectf vectf::operator+(const vectf& p) const { return vectf(x+p.x, y+p.y); }
vectf vectf::operator-(const vectf& p) const { return vectf(x-p.x, y-p.y); }
void vectf::operator+=(const vectf& p) { x += p.x; y += p.y; }
void vectf::operator-=(const vectf& p) { x -= p.x; y -= p.y; }

void vectf::normalize() {
  int mag(sqrt((float)(x*x + y*y)));
  if (mag != 0.0000f) {
    x /= mag;
    y /= mag;
  }
}

int vectf::magnitude() const { return sqrt((float)(x*x + y*y)); }

vectf vectf::cross() const { return vectf(y, -x); }

int vectf::dot(const vectf& p) const { return (x*p.x + y*p.y); }

/*std::string vectf::to_string() const {
  std::string value = "("; 
  value += itos(x);
  value += ", ";
  value += itos(y);
  value += ")";
  return value;
}

vectf& vectf::from_string(string data) {
  if (data.length() < 3) {
    clear();
    return (*this);
  }

  data.erase(data.begin()); // remove '('
  data.erase(data.end()--); // remove ')'
  std::vector<std::string> coordinate_strings(explode(data, ", ", -1));

  if (coordinate_strings.size() < 2) clear();
  else {
    x = atof(coordinate_strings[0].c_str());
    y = atof(coordinate_strings[1].c_str());
  }

  return (*this);
}*/

void vectf::clear() {
  x = 0.0f;
  y = 0.0f;
}




// *** begin class vect3f defintions *** //
vect3f::vect3f() : z(0.0f) { }
vect3f::vect3f(int _x, int _y, int _z) : vectf(_x, _y), z(_z) { }

int& vect3f::operator[](int index) {
  switch(index) {
    case 0: { return x; } break;
    case 1: { return y; } break;
    case 2: { return z; } break;
    default: { return _out_of_bounds; } break;
  }
}
const int& vect3f::operator[](int index) const {
  switch(index) {
    case 0: { return x; } break;
    case 1: { return y; } break;
    case 2: { return z; } break;
    default: { return _out_of_bounds; } break;
  }
}

bool vect3f::operator==(const vect3f& p) const { return (x==p.x && y==p.y && z==p.z); }
bool vect3f::operator!=(const vect3f& p) const { return (x!=p.x || y!=p.y || z==p.z); }
vect3f vect3f::operator*(int c) const { return vect3f(x*c, y*c, z*c); }
vect3f vect3f::operator/(int c) const { return vect3f(x/c, y/c, z/c); }
vect3f vect3f::operator+(const vect3f& p) const { return vect3f(x+p.x, y+p.y, z+p.z); }
vect3f vect3f::operator-(const vect3f& p) const { return vect3f(x-p.x, y-p.y, z-p.z); }
void vect3f::operator*=(int c) { x*=c; y*=c; z*=c; }
void vect3f::operator/=(int c) { x/=c; y/=c; z/=c; }
void vect3f::operator+=(const vect3f& p) { x+=p.x; y+=p.y; z+=p.z; }
void vect3f::operator-=(const vect3f& p) { x-=p.x; y-=p.y; z-=p.z; }

void vect3f::normalize() {
  int mag = sqrt((float)(x*x + y*y + z*z));
  if (mag != 0.0000f) {
    x /= mag;
    y /= mag;
    z /= mag;
  }
}

int vect3f::magnitude() const { return sqrt((float)(x*x + y*y + z*z)); }

vect3f vect3f::cross(const vect3f& p) const {
  return vect3f(  (y*p.z - z*p.y),
                  (z*p.x - x*p.z),
                  (x*p.y - y*p.x)
               );
}

int vect3f::dot(const vect3f& p) const { return (x*p.x + y*p.y + z*p.z); }

/*string vect3f::to_string() const {
  std::string value = "("; 
  value += ftos(x);
  value += ", ";
  value += ftos(y);
  value += ", ";
  value += ftos(z);
  value += ")";
  return value;
}

vect3f& vect3f::from_string(string data) {
  if (data.length() < 4) {
    clear();
    return (*this);
  }

  data.erase(data.begin()); // remove '('
  data.erase(data.end()--); // remove ')'
  std::vector<std::string> coordinate_strings(explode(data, ", ", -1));

  if (coordinate_strings.size() < 3) return (*this);

  x = atof(coordinate_strings[0].c_str());
  y = atof(coordinate_strings[1].c_str());
  z = atof(coordinate_strings[2].c_str());
  return (*this);
}*/

void vect3f::clear() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}




// **** begin class glvect4f definitions ****
vect4f::vect4f() : a(0.0) { }
vect4f::vect4f(int _x, int _y, int _z, int _a) : vectf(_x, _y), z(_z), a(_a) { }

vect4f::operator const int* () const {
  temp[0] = x;
  temp[1] = y;
  temp[2] = z;
  temp[3] = a;

  return temp;
}

int& vect4f::operator[](int index) {
  switch(index) {
    case 0: { return x; } break;
    case 1: { return y; } break;
    case 2: { return z; } break;
    case 3: { return a; } break;
    default: { return _out_of_bounds; } break;
  }
}
const int& vect4f::operator[](int index) const {
  switch(index) {
    case 0: { return x; } break;
    case 1: { return y; } break;
    case 2: { return z; } break;
    case 3: { return a; } break;
    default: { return _out_of_bounds; } break;
  }
}

bool vect4f::operator==(const vect4f& p) const { return (x==p.x && y==p.y && z==p.z && a==p.a); }
bool vect4f::operator!=(const vect4f& p) const { return (x!=p.x || y!=p.y || z!=p.z || a!=p.a); }
vect4f vect4f::operator*(int c) const { return vect4f(x*c, y*c, z*c, a*c); }
vect4f vect4f::operator/(int c) const { return vect4f(x/c, y/c, z/c, a/c); }
vect4f vect4f::operator+(const vect4f& p) const { return vect4f(x+p.x, y+p.y, z+p.z, a+p.a); }
vect4f vect4f::operator-(const vect4f& p) const { return vect4f(x-p.x, y-p.y, z-p.z, a-p.a); }
void vect4f::operator*=(int c) { x*=c; y*=c; z*=c; a*=c; }
void vect4f::operator/=(int c) { x/=c; y/=c; z/=c; a/=c; }
void vect4f::operator+=(const vect4f& p) { x+=p.x; y+=p.y; z+=p.z; a+=p.a;}
void vect4f::operator-=(const vect4f& p) { x-=p.x; y-=p.y; z-=p.z; a-=p.a;}

void vect4f::normalize() {
  int mag = sqrt((float)(x*x + y*y + z*z + a*a));
  if (mag != 0.0000f) {
    x /= mag;
    y /= mag;
    z /= mag;
    a /= mag;
  }
}

int vect4f::magnitude() const { return sqrt((float)(x*x + y*y + z*z + a*a)); }

int vect4f::dot(const vect4f& p) const { return (x*p.x + y*p.y + z*p.z + a*p.a); }

/*string vect4f::to_string() const {
  std::string value = "("; 
  value += ftos(x);
  value += ", ";
  value += ftos(y);
  value += ", ";
  value += ftos(z);
  value += ", ";
  value += ftos(a);
  value += ")";
  return value;
}

vect4f& vect4f::from_string(string data) {
  if (data.length() < 5) {
    clear();
    return (*this);
  }
  data.erase(data.begin()); // remove '('
  data.erase(data.end()--); // remove ')'
  vector<string> coordinate_strings(explode(data, ", ", -1));

  if (coordinate_strings.size() < 4) return (*this);

  x = atof(coordinate_strings[0].c_str());
  y = atof(coordinate_strings[1].c_str());
  z = atof(coordinate_strings[2].c_str());
  a = atof(coordinate_strings[3].c_str());
  return (*this);
}*/


void vect4f::clear() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
  a = 0.0f;
}

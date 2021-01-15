#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "utilities.h"
using namespace std;

class Polygon {
public:
  Polygon(const string& name, const vector<Point>& points);
  virtual ~Polygon() {}
  int NumVerts() { return points.size(); }
  virtual bool anglesEqual();
  virtual bool edgesEqual();
  virtual bool HasRightAngle();

protected:
  string name_;
  vector<Point> points_;
  vector<double> edges_;
  vector<double> angles_;
};

class Triangle : public Polygon {
public:
  Triangle(const string& name, const vector<Point>& points);
  virtual bool anglesEqual() { return false; }
  virtual bool edgesEqual() { return false; }
};

class Quadrilateral : public Polygon {
public:
  Quadrilateral(const string& name, const vector<Point>& points);
  virtual bool anglesEqual() { return false; }
  virtual bool edgesEqual() { return false; }
};

class IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle(const string& name, const vector<Point>& points);
  bool anglesEqual() { return false; }
  bool edgesEqual() { return false; }
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
  EquilateralTriangle(const string& name, const vector<Point>& points);
  bool anglesEqual() { return true; }
  bool edgesEqual() { return true; }
};

class Rectangle : public Parallelogram {
public:
  Rectangle(const string& name, const vector<Point>& points);
  bool anglesEqual() { return true; }
  bool edgesEqual() { return false; }
  bool HasRightAngle() { return true; }
};

class Square : public Rectangle, public Rhombus {
public:
  Square(const string& name, const vector<Point>& points);
  bool anglesEqual() { return true; }
  bool edgesEqual() { return true; }
  bool HasRightAngle() { return true; }
};

class RightTriangle : public Triangle {
public:
  RightTriangle(const string& name, const vector<Point>& points);
  bool anglesEqual() { return false; }
  bool edgesEqual() { return false; }
  bool HasRightAngle() { return true; }
};

class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle {
public:
  IsoscelesRightTriangle(const string& name, const vector<Point>& points);
  bool anglesEqual() { return false; }
  bool edgesEqual() { return false; }
  bool HasRightAngle() { return true; }
};

class Trpaezoid : public Quadrilateral {
public:
  Trapezoid(const string& name, const vector<Point>& points);
  bool anglesEqual() { return false; }
  bool edgesEqual() { return false; }
};

class Kite : public Quadrilateral {
public:
  Kite(const string& name, const vector<Point>& points);
  bool anglesEqual() { return false; }
  bool edgesEqual() { return false; }
};

class Parallelogram : public Trapezoid {
public:
  Parallelogram(const string& name, const vector<Point>& points);
  virtual bool anglesEqual() { return false; }
  virtual bool edgesEqual() { return false; }
  virtual bool HasRightAngle() { return false; }
};

class Rhombus : public Parallelogram, public Kite {
public:
  Rhombus(const string& name, const vector<Point>& points);
  bool anglesEqual() { return false; }
  bool edgesEqual() { return true; }
}
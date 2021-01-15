#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "utilities.h"
#include "polygons.h"
using namespace std;

Polygon::Polygon(const string& name, const vector<Point>& points) {
  for (int i = 0; i < points.size()-1; ++i) {
    double e1 = DistanceBetween(points[0], points[1]);
  	edges_.push_back(e1);
  }
  for (int i = 1; i < points.size()-1; ++i) {
    double a1 = Angle(points[i-1], points[i], points[i+1]);
  	angles_.push_back(a1);
  }
  name_ = name;
  points_ = points;
}

bool Polygon::anglesEqual() {
  for (int i = 0; i < angles_.size()-1; ++i) {
    if (EqualSides(angles_[i], angles_[i+1]) == false) {
      return false;
    }
  }
  return true;
}

bool Polygon::edgesEqual() {
  for (int i = 0; i < edges_.size()-1; ++i) {
    if (EqualSides(edges_[i], edges_[i+1]) == false) {
      return false;
    }
  }
  return true;
}

bool Polygon::HasRightAngle() {
  for (int i = 0; i < angles_.size()-1; ++i) {
    if (RightAngle(angles_[i]) == false) {
      return false;
    }
  }
  return true;
}

Triangle::Triangle(const string& name, const vector<Point>& points) : Polygon(name, points) {
  if (points.size() != 3) {
  	throw -1;
  }
  else {
  	name_ = name;
    points_ = points;
  }
}

Quadrilateral::Quadrilateral(const string& name, const vector<Point>& points) : Polygon(name, points) {
  if (points.size() != 4) {
  	throw -1;
  }
  else {
  	name_ = name;
    points_ = points;
  }
}

IsoscelesTriangle::IsoscelesTriangle(const string& name, const vector<Point>& points) : Triangle(name, points) {
  if (points.size() != 3) {
  	throw -1;
  }
  if (EqualSides(edges_[0], edges_[1]) == false && EqualSides(edges_[0], edges_[2]) == false
      && EqualSides(edges_[1], edges_[2]) == false) {
  	throw -2;
  }
  name_ = name;
  points_ = points;
}

EquilateralTriangle::EquilateralTriangle(const string& name, const vector<Point>& points) : IsoscelesTriangle(name, points) {
  if (points.size() != 3) {
  	throw -1;
  }
  if (!(EqualSides(edges_[0], edges_[1]) == true && EqualSides(edges_[0], edges_[2]) == true
      && EqualSides(edges_[1], edges_[2]) == true)) {
  	throw -2;
  }
  name_ = name;
  points_ = points;
}

Rectangle::Rectangle(const string& name, const vector<Point>& points) : Parallelogram(name, points) {
  if (points.size() != 4) {
  	throw -1;
  }
  if (!((EqualSides(edges_[0], edges_[1]) == true && EqualSides(edges_[2], edges_[3]) == true) ||
  	    (EqualSides(edges_[0], edges_[2]) == true && EqualSides(edges_[1], edges_[3]) == true) ||
  	    (EqualSides(edges_[0], edges_[3]) == true && EqualSides(edges_[1], edges_[2]) == true))) {
  	throw -2;
  }
  if (!((EqualAngles(angles_[0], angles_[1]) == true && EqualSides(angles_[2], angles_[3]) == true) ||
  	    (EqualAngles(angles_[0], angles_[2]) == true && EqualSides(angles_[1], angles_[3]) == true) ||
  	    (EqualAngles(angles_[0], angles_[3]) == true && EqualSides(angles_[1], angles_[2]) == true))) {
  	throw -3;
  }
  if (!(RightAngle(angles_[0]) == true && RightAngle(angles_[1]) == true && 
  	    RightAngle(angles_[2]) == true && RightAngle(angles_[3]) == true &&)) {
  	throw -3;
  }
  name_ = name;
  points_ = points;
}

Sqare::Sqare(const string& name, const vector<Point>& points) : Rectangle(name, points), Rhombus(name, points) {
  if (points.size() != 4) {
  	throw -1;
  }
  if (!(EqualSides(edges_[0], edges_[1]) == true && EqualSides(edges_[0], edges_[2]) == true &&
  	    EqualSides(edges_[0], edges_[3]) == true)) {
  	throw -2;
  }
  if (!(RightAngle(angles_[0]) == true && RightAngle(angles_[1]) == true && 
  	    RightAngle(angles_[2]) == true && RightAngle(angles_[3]) == true &&)) {
  	throw -3;
  }
  name_ = name;
  points_ = points;
}

RightTriangle::RightTriangle(const string& name, const vector<Point>& points) : Triangle(name, points) {
  if (points.size() != 3) {
    throw -1;
  }
  if (!(RightAngle(angles_[0]) == true || (RightAngle(angles_[1]) == true || (RightAngle(angles_[2]) == true)) {
    throw -2;
  }
  name_ = name;
  points_ = points;
}

IsoscelesRightTriangle::IsoscelesRightTriangle(const string& name, const vector<Point>& points) : IsoscelesTriangle(name, points), RightAngle(name, points) {
  if (points.size() != 3) {
    throw -1;
  }
  if (!(RightAngle(angles_[0]) == true || (RightAngle(angles_[1]) == true || (RightAngle(angles_[2]) == true)) {
    throw -2;
  }
  if (EqualSides(edges_[0], edges_[1]) == false && EqualSides(edges_[0], edges_[2]) == false
      && EqualSides(edges_[1], edges_[2]) == false) {
    throw -3;
  }
  name_ = name;
  points_ = points;
}

Trpaezoid::Trapezoid(const string& name, const vector<Point>& points) : Quadrilateral(name, points) {
  if (points.size() != 4) {
    throw -1;
  }
  if (!(Parallel(Vector(points[0], points[1]), Vector(points[2], points[3])) == true || 
        Parallel(Vector(points[0], points[3]), Vector(points[1], points[2])) == true)) {
    throw -2;
  }
  name_ = name;
  points_ = points;
}

Kite::Kite(const string& name, const vector<Point>& points) : Quadrilateral(name, points) {
  if (points.size() != 4) {
    throw -1;
  }
  if (!((EqualSides(edges_[0], edges_[1]) == true && EqualSides(edges_[2], edges_[3]) == true) ||
        (EqualSides(edges_[0], edges_[3]) == true && EqualSides(edges_[1], edges_[2]) == true))) {
    throw -1;
  }
  name_ = name;
  points_ = points;
}

Parallelogram::Parallelogram(const string& name, const vector<Point>& points) : Trapezoid(name, points) {
  if (points.size() != 4) {
    throw -1;
  }
  if (!((Parallel(Vector(points[0], points[1]), Vector(points[2], points[3])) == true && EqualSides(edges_[0], edges_[2])) ||
        (Parallel(Vector(points[0], points[3]), Vector(points[1], points[2])) == true && EqualSides(edges_[1], edges_[3])))) {
    throw -2;
  }
  name_ = name;
  points_ = points;
}

Rhombus::Rhombus(const string& name, const vector<Point>& points) : Parallelogram(name, points), Kite(name, points) {
  if (points.size() != 4) {
    throw -1;
  }
  if (!(EqualSides(edges_[0], edges_[1]) == true && EqualSides(edges_[0], edges_[2]) == true &&
        EqualSides(edges_[0], edges_[3]) == true)) {
    throw -2;
  }
  if (!((Parallel(Vector(points[0], points[1]), Vector(points[2], points[3])) == true && EqualSides(edges_[0], edges_[2])) ||
        (Parallel(Vector(points[0], points[3]), Vector(points[1], points[2])) == true && EqualSides(edges_[1], edges_[3])))) {
    throw -3;
  }
  name_ = name;
  points_ = points;
}
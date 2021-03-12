/*                                                              */
/* tri.h - Header file for Triangle class                       */
/*                                                              */
/* Copyright (C) ARM Limited, 1999. All rights reserved.        */
/*                                                              */

#ifndef _TRI_H_ 
#define _TRI_H_

enum TriangleType { EQUILATERAL, ISOSCELES, SCALENE };

class Triangle {

public:

  Triangle();                 // default constructor
  TriangleType type() const;  // returns type of triangle
  double perimeter() const;   // returns perimeter of triangle
  void display() const;       // displays private attributes of triangle        
  ~Triangle();                // destructor, returns allocated memory

private:

  double x1, y1;              // coordinates of first vertex
  double x2, y2;              // coordinates of second vertex
  double x3, y3;              // coordinates of third vertex
  char*  title;               // attribute to show dynamic memory allocation 
};

#endif  // _TRI_H_


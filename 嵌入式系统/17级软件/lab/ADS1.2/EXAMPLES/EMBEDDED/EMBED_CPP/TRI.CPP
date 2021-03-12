/*                                                              */
/* tri.cpp - Implementation file for Triangle class             */
/*                                                              */
/* Copyright (C) ARM Limited, 1999. All rights reserved.        */
/*                                                              */

#include <stdio.h>
#include <math.h>        
#include <string.h>
#include "tri.h"


const double EPSILON = 0.00001; // Tolerance for testing equality.
const char*  TEST = "   This is an instance of class Triangle. ";

// Default constructor. Instantiates a Triangle with some simple coordinates.

Triangle::Triangle()    // default constructor
{
  x1 = 0;               // coordinates of 
  y1 = 0;               // first vertex
  x2 = 1;               // coordinates of
  y2 = 2;               // second vertex
  x3 = 2;               // coordinates of
  y3 = 0;               // third vertex
  title = strcpy(new char[strlen(TEST)+1], TEST);

  printf("\nDefault constructor for Triangle called.\n\n"); 
}



// Compute the Euclidean distance between two points.

inline double distance(double x1, double y1, double x2, double y2)
{
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


// Test whether two real numbers are equal to within EPSILON.

inline bool equal(double a, double b)
{
  return (fabs(a-b) < EPSILON);
}


// Test an instance of Triangle and return a TriangleType value.

TriangleType Triangle::type() const 
{
  double a = distance(x1, y1, x2, y2),
         b = distance(x2, y2, x3, y3),
         c = distance(x3, y3, x1, y1);

  if (equal(a, b) && equal(a, c) && equal(b, c))
    return EQUILATERAL;
  else if (equal(a, b) || equal(b, c) || equal(a, c))
    return ISOSCELES;
  else
    return SCALENE;
}


// Compute the perimeter of an instance of Triangle.

double Triangle::perimeter() const 
{
  double a = distance(x1, y1, x2, y2),
         b = distance(x2, y2, x3, y3),
         c = distance(x3, y3, x1, y1);
  return (a+b+c); 
}


// Display standard details of an instance of Triangle.

void Triangle::display() const
{
  printf (title);
  printf ("\n\n   Its vertices are ");
  printf ("(%2.2f,%2.2f)"  , x1, y1 );
  printf (" (%2.2f,%2.2f) ", x2, y2 );
  printf ("(%2.2f,%2.2f)\n", x3, y3 );
}


// Destructor, returns memory allocated to title.

Triangle::~Triangle()
{
  delete [] title;

  printf("Destructor called for Triangle.\n\n");
}


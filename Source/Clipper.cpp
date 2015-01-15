/*
  ==============================================================================

    Clipper.cpp
    Created: 15 Jan 2015 9:23:05pm
    Author:  user

  ==============================================================================
*/

#include <math.h>
#include "Clipper.h"
Clipper::Clipper(){
	x1=x2=0.0f;
}
Clipper::~Clipper(){
}
float Clipper::max (float x, float a)
{
   x -= a;
   x += fabs (x);
   x *= 0.5;
   x += a;
   return (x);
}

float Clipper::min (float x, float b)
{
   x = b - x;
   x += fabs (x);
   x *= 0.5;
   x = b - x;
   return (x);
}

float Clipper::clip (float x, float a, float b)
{
   x1 = fabs (x-a);
   x2 = fabs (x-b);
   x = x1 + (a+b);
   x -= x2;
   x *= 0.5;
   return (x);
}
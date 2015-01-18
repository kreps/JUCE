/*
==============================================================================

OnePoleFilter.cpp
Created: 18 Jan 2015 7:46:13pm
Author:  user

==============================================================================
*/

#include "OnePoleFilter.h"
OnePoleFilter::OnePoleFilter() { a = 0.99; b = 1. - a; z = 0.; };
OnePoleFilter::~OnePoleFilter() {};
double OnePoleFilter::Process(double in) { z = (in * b) + (z * a); return z; }

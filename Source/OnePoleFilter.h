/*
  ==============================================================================

    OnePoleFilter.h
    Created: 18 Jan 2015 7:38:44pm
    Author:  user

  ==============================================================================
*/

#ifndef ONEPOLEFILTER_H_INCLUDED
#define ONEPOLEFILTER_H_INCLUDED

class OnePoleFilter
{
public:
  OnePoleFilter(); 
  ~OnePoleFilter(); 
  double Process(double in);
private:
  double a, b, z;
};



#endif  // ONEPOLEFILTER_H_INCLUDED

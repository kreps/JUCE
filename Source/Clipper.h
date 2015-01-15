/*
  ==============================================================================

    Clipper.h
    Created: 15 Jan 2015 9:23:05pm
    Author:  user

  ==============================================================================
*/

#ifndef CLIPPER_H_INCLUDED
#define CLIPPER_H_INCLUDED
class Clipper
{
	public:
		Clipper();
		~Clipper();
		float clip(float x, float a, float b);
	private:
		float max(float x, float a);
		float min(float x, float b);
		float x1,x2;
};




#endif  // CLIPPER_H_INCLUDED

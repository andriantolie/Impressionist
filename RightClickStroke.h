//
// RightClickStroke.h
//
// The header file for RightClickStroke. 
//

#ifndef POINTBRUSH_H
#define POINTBRUSH_H

#include "ImpBrush.h"

class RightClickStroke : public ImpBrush
{
public:
	RightClickStroke(ImpressionistDoc* pDoc = NULL, char* name = NULL);
	Point* brushStartCoord;
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif
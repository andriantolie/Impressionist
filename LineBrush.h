//
// LineBrush.h
//
// The header file for Line Brush. 
//

#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include "ImpBrush.h"
#include <math.h>

class LineBrush : public ImpBrush
{
public:
	Point* brushStartCoord;
	Point* brushEndCoord;
	LineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void drawLine(const Point source, const Point target, const int lineSize, const int lineAngle);
	int getBrushDirection();
	int calculateAngle(const int startX, const int startY, const int endX, const int endY);
	int getGradientX(const Point source);
	int getGradientY(const Point source);
	double getPixelIntensity(const int x, const int y);
	char* BrushName(void);
};

#endif
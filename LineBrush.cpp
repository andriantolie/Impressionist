//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Linebrush.h"
#include <iostream>
using namespace std;

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int lineWidth = pDoc->getLineWidth();

	glLineWidth(lineWidth);
	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int lineSize = pDoc->getSize();
	int lineAngle = pDoc->getLineAngle();


	int startX = target.x - (lineSize / 2) * cos(lineAngle * M_PI / 180);
	int startY = target.y - (lineSize / 2) * sin(lineAngle * M_PI / 180);
	int endX = target.x + (lineSize / 2) * cos(lineAngle * M_PI / 180);
	int endY = target.y + (lineSize / 2) * sin(lineAngle * M_PI / 180);

	glBegin(GL_LINES);

	SetColor(source);

	glVertex2d(startX, startY);
	glVertex2d(endX, endY);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


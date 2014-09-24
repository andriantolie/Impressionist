//
// RightClickStroke.cpp
//
// The implementation of RightClickStroke Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "RightClickStroke.h"

extern float frand();

RightClickStroke::RightClickStroke(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
	brushStartCoord = NULL;
}

void RightClickStroke::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	brushStartCoord = new Point(target.x, target.y);
	glPointSize(1);
	glColor3f(1.0, 0.0, 0.0);

	BrushMove(source, target);
}

void RightClickStroke::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("RightClickStroke::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINES);
	glVertex2d(brushStartCoord->x, brushStartCoord->y);
	glVertex2d(target.x, target.y);

	glEnd();
}

void RightClickStroke::BrushEnd(const Point source, const Point target)
{
	delete brushStartCoord;
	brushStartCoord = NULL;
}


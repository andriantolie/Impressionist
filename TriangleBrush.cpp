//
// TriangleBrush.cpp
//
// The implementation of Triangle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "TriangleBrush.h"

extern float frand();

TriangleBrush::TriangleBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void TriangleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	glBegin(GL_POLYGON);
	SetColor(source);

	glVertex2d(target.x - size*cos(M_PI/3), target.y + size*cos(M_PI/3));
	glVertex2d(target.x + size*cos(M_PI / 3), target.y + size*cos(M_PI / 3));
	glVertex2d(target.x, target.y - size*cos(M_PI / 3));

	glEnd();
}

void TriangleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);
}


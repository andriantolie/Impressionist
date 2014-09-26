// ScatteredCircleBrush.cpp
//
// The implementation of Scattered Circle Brush

#include "ImpressionistUI.h"
#include "ImpressionistDOC.h"
#include "ScatteredCircleBrush.h"

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
CircleBrush(pDoc, name) {
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();


	glPointSize( float (size) );

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	BrushMove(source, target);

}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	//set random target coordinates
	//srand(time(NULL));
	int numOfPoints = rand() % 4 + 1;

	for (int i = 0; i < numOfPoints; i++){
		int xDisplacement = rand() % (size/2) + 1;
		int yDisplacement = rand() % (size/2) + 1;
		Point newSource(source.x + xDisplacement, source.y + yDisplacement);
		Point newTarget(target.x + xDisplacement, target.y + yDisplacement);
		CircleBrush::BrushMove(newSource, newTarget);

	}

}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);
}

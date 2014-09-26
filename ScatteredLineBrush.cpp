//
// ScatteredLineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"
#include <time.h>

extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
LineBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int lineWidth = pDoc->getLineWidth();
	glLineWidth(lineWidth);
	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	//set random target coordinates
	//srand(time(NULL));
	int numOfLines = rand() % 10 + 1;
	for (int i = 0; i < numOfLines; i++){
		int xDisplacement = rand() % size;
		int yDisplacement = rand() % size;
		Point newSource(source.x + xDisplacement, source.y + yDisplacement);
		Point newTarget(target.x + xDisplacement, target.y + yDisplacement);

		LineBrush::BrushMove(newSource, newTarget);
	}
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}



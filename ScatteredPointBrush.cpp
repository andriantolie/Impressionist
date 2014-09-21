//
// ScatteredPointBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"
#include <time.h>

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
PointBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize(1);

	BrushMove(source, target);


}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	//set random target coordinates
	srand(time(NULL));
	int numOfPoints = rand() % (size/2)*(size/2) + 1;
	for (int i = 0; i < numOfPoints; i++){
		int xDisplacement = rand() % size;
		int yDisplacement = rand() % size;
		Point newSource(source.x + xDisplacement, source.y + yDisplacement);
		Point newTarget(target.x + xDisplacement, target.y + yDisplacement);

		PointBrush::BrushMove(newSource, newTarget);
	}

}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


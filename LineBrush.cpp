//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Linebrush.h"

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
	brushStartCoord = NULL;
	brushEndCoord = NULL;
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int lineWidth = pDoc->getLineWidth();

	glLineWidth(lineWidth);

	//set brush start coordinate - for brush direction
	brushStartCoord = new Point(target.x, target.y);
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

	//set line angle according to brush direction
	if (dlg->m_StrokeDirectionChoice->value() == BRUSH_DIRECTION){
		//set up brush end coodinate - for brush direction
		brushEndCoord = new Point(target.x, target.y);
		int brushDirection = getBrushDirection();
		pDoc->setLineAngle(brushDirection);
		//setup new value for brush start
		delete brushStartCoord;
		brushStartCoord = brushEndCoord;
	}

	int lineSize = pDoc->getSize();
	int lineAngle = pDoc->getLineAngle();

	if(lineAngle != - 1) drawLine(source, target, lineSize, lineAngle);
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	//// remove brush start and end coordinate from the heap
	delete brushStartCoord;
	brushStartCoord = NULL;
	brushEndCoord = NULL; //brushStart Coord and brushEndCoord previously pointed to the same value so we only need to delete brushStartCoord
}

void LineBrush::drawLine(const Point source, const Point target, const int lineSize, const int lineAngle){
	if (lineAngle >= 0 && lineAngle < 360){
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
}
int LineBrush::getBrushDirection(){

	if (!(brushStartCoord == NULL || brushEndCoord == NULL)){

		int normalizedX = brushEndCoord->x - brushStartCoord->x;
		int normalizedY = (brushEndCoord->y - brushStartCoord->y);

		int angle = atan2((float)normalizedY, (float)normalizedX) * 180 / M_PI;
		if (angle >= 0){
			return angle;
		}
		else{
			return angle + 360;
		}
	}
	else{
		return -1; //denotes invalid value
	}
}


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
		if (brushEndCoord == NULL){
			brushEndCoord = new Point(target.x, target.y);
		}
		else{
			//set up brush end coodinate - for brush direction
			brushEndCoord = new Point(target.x, target.y);
			int brushDirection = calculateAngle(brushStartCoord->x, brushStartCoord->y, brushEndCoord->x, brushEndCoord->y);
			pDoc->setLineAngle(brushDirection);
			//setup new value for brush start
			delete brushStartCoord;
			brushStartCoord = brushEndCoord;
		}

	}
	else if (dlg->m_StrokeDirectionChoice->value() == GRADIENT){
		int gradientX = getGradientX(source);
		int gradientY = getGradientY(source);
		int gradientAngle = calculateAngle(0, 0, gradientX, gradientY);
		int perpendicularToGradient = gradientAngle + 90;
		if (perpendicularToGradient >= 360) perpendicularToGradient -= 180;
		pDoc->setLineAngle(perpendicularToGradient);
	}


	int lineAngle = pDoc->getLineAngle();
	int lineSize = pDoc->getSize();

	drawLine(source, target, lineSize, lineAngle);
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// remove brush start and end coordinate from the heap
	//brushStart Coord and brushEndCoord previously pointed to the same value so we only need to delete brushStartCoord
	delete brushStartCoord;
	brushStartCoord = NULL;
	brushEndCoord = NULL; 
}

//draw line using opengl
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

//get direction of the brush stroke
int LineBrush::getBrushDirection(){
	if (!(brushStartCoord == NULL || brushEndCoord == NULL)){
		ImpressionistDoc* pDoc = GetDocument();
		int height = pDoc->m_nHeight;
		return calculateAngle(brushStartCoord->x, height - brushStartCoord->y, brushEndCoord->x, height - brushEndCoord->y);
	}
	else{
		return -1; //denotes invalid value
	}
}

//calculate angle given two points
int LineBrush::calculateAngle(const int startX, const int startY, const int endX, const int endY){
	int normalizedX = endX - startX;
	int normalizedY = endY - startY;

	int angle = atan2((float)normalizedY, (float)normalizedX) * 180 / M_PI;
	if (angle >= 0){
		return angle;
	}
	else{
		return angle + 360;
	}
}

//Calculate gradient in X direction
int LineBrush::getGradientX(const Point source){
	ImpressionistDoc* pDoc = GetDocument();
	int sobelX[3][3] = 
	{
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};
	double gradientX = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			gradientX += sobelX[i][j] * getPixelIntensity(source.x + j - 1, source.y - i + 1 );
		}
	}
	return (int)gradientX;

}

//Calculate gradient in Y direction
int LineBrush::getGradientY(const Point source){
	ImpressionistDoc* pDoc = GetDocument();
	int sobelY[3][3] =
	{
		{ 1, 2, 1 },
		{ 0, 0, 0 },
		{ -1, -2, -1 }
	};
	double gradientY = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			gradientY += sobelY[i][j] * getPixelIntensity(source.x + j - 1, source.y - i + 1);
		}
	}
	return (int)gradientY;

}

//get intensity of a pixel
//we define intensity as relative luminance, i.e. Y = 0.2126 R + 0.7152 G + 0.0722 B
double LineBrush::getPixelIntensity(int x, int y){
	ImpressionistDoc* pDoc = GetDocument();
	unsigned char color[3];
	memcpy(color, pDoc->GetOriginalPixel(x, y), 3);
	return (0.2126*color[0] + 0.7152*color[1] + 0.0722*color[2]);

}


/*
 * The implementation of circle brush.
 *
*/

#include "ImpressionistUI.h"
#include "ImpressionistDoc.h"
#include "CircleBrush.h"

extern float frand();

CircleBrush::CircleBrush (ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void CircleBrush::BrushBegin (const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize((float) size);

	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_NOTEQUAL, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	BrushMove(source, target);
}

void CircleBrush::BrushMove (const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "Circlerush::BrushMove document is NULL\n" );
		return;
	}
	int size = pDoc->getSize();
	int radius = size / 2;
	glBegin( GL_TRIANGLE_FAN );
		SetColor( source );

		for (double i = 0; i < 2*M_PI; i+=0.1){
			glVertex2d(target.x + radius*cos(i), target.y + radius*sin(i));
		}

	glEnd();
}

void CircleBrush::BrushEnd (const Point source, const Point target) {
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);

}
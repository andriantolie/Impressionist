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

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	BrushMove(source, target);
}

void CircleBrush::BrushMove (const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove document is NULL\n" );
		return;
	}

	glBegin( GL_POINTS );
		SetColor( source );

		glVertex2d( target.x, target.y );

	glEnd();
}

void CircleBrush::BrushEnd (const Point source, const Point target) {
	// Do nothing for now
	glDisable(GL_POINT_SMOOTH);
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);
}
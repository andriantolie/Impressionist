/*
 * The header file for scattered circle brush
 *
*/

#ifndef SCATTEREDCIRCLEBRUSH_H
#define SCATTEREDCIRCLEBURSH_H

 #include "ImpBrush.h"
 #include "CircleBrush.h"

 class ScatteredCircleBrush : public ImpBrush {
 public:
 	ScatteredCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
 };

 #endif
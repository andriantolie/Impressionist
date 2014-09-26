//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include "RightClickStroke.h"
#include <math.h>

#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6
#define MOUSE_MOVE			7

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;
static int      index = 0;


PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA
	if(!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{
		RestoreContent();

	}
	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{
		if (coord.x <= m_nDrawWidth && coord.y <= m_nDrawHeight){
			// Clear it after processing.
			isAnEvent = 0;

			Point source(coord.x + m_nStartCol, m_nEndRow - coord.y);
			Point target(coord.x, m_nWindowHeight - coord.y);

			// This is the event handler
			switch (eventToDo)
			{
			case LEFT_MOUSE_DOWN:
				m_pDoc->m_pCurrentBrush->BrushBegin(source, target);
				break;
			case LEFT_MOUSE_DRAG:
				m_pDoc->m_pCurrentBrush->BrushMove(source, target);
				break;
			case LEFT_MOUSE_UP:
				m_pDoc->m_pCurrentBrush->BrushEnd(source, target);

				SaveCurrentContent();
				RestoreContent();
				break;
			case RIGHT_MOUSE_DOWN:
				SaveCurrentContent();
				rightClickStroke = new RightClickStroke(m_pDoc, "Right Click Stroke");
				rightClickStroke->BrushBegin(source, target);
				break;
			case RIGHT_MOUSE_DRAG:
				RestoreContent();
				rightClickStroke->BrushMove(source, target);
				break;
			case RIGHT_MOUSE_UP:
				rightClickStroke->BrushEnd(source, target);
				delete rightClickStroke;
				rightClickStroke = NULL;
				RestoreContent();
				break;
			default:
				printf("Unknown event!!\n");
				break;
			}
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	ImpressionistUI* ui = m_pDoc->m_pUI;

	switch (event)
	{
	case FL_ENTER:
		redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button() > 1){
			eventToDo = RIGHT_MOUSE_DOWN;
		}
		else{
			eventToDo = LEFT_MOUSE_DOWN;
		}
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button() > 1){
			eventToDo = RIGHT_MOUSE_DRAG;
		}
		else{
			eventToDo = LEFT_MOUSE_DRAG;
		}
		ui->m_origView->isMoving = true;
		ui->m_origView->cursor.x = coord.x;
		ui->m_origView->cursor.y = m_pDoc->m_nPaintHeight - coord.y;
		ui->m_origView->redraw();
		isAnEvent=1;
		redraw();
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button() > 1){
			eventToDo = RIGHT_MOUSE_UP;
		}
		else{
			eventToDo = LEFT_MOUSE_UP;
		}
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		ui->m_origView->isMoving = true;
		ui->m_origView->cursor.x = coord.x;
		ui->m_origView->cursor.y = m_pDoc->m_nPaintHeight - coord.y;
		ui->m_origView->redraw();
		break;
	default:
		return 0;
		break;

	}



	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB,
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}

void PaintView::automaticDraw(){
	//clear the background first
	glClear(GL_COLOR_BUFFER_BIT);
#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
#endif // !MESA
	if (!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable(GL_DEPTH_TEST);

		ortho();

		glClear(GL_COLOR_BUFFER_BIT);
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y = 0;

	m_nWindowWidth = w();
	m_nWindowHeight = h();

	int drawWidth, drawHeight;
	drawWidth = min(m_nWindowWidth, m_pDoc->m_nPaintWidth);
	drawHeight = min(m_nWindowHeight, m_pDoc->m_nPaintHeight);

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if (startrow < 0) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting +
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth = drawWidth;
	m_nDrawHeight = drawHeight;

	m_nStartRow = startrow;
	m_nEndRow = startrow + drawHeight;
	m_nStartCol = scrollpos.x;
	m_nEndCol = m_nStartCol + drawWidth;
	
	int origSize = m_pDoc->getSize();
	int numOfPoints = (drawWidth / 2) * (drawHeight / 2);
	for (int i = 0; i < numOfPoints; i++){
		int x = rand() % drawWidth ;
		int y = rand() % drawHeight ;
		int modifiedSize = (origSize + (-1 * rand() % 2) * (rand() % (origSize / 4))) % 40 + 1;
		m_pDoc->setSize(modifiedSize);
		Point source(x + m_nStartCol, m_nEndRow - y);
		Point target(x, m_nWindowHeight - y);

		if (i == 0){
			m_pDoc->m_pCurrentBrush->BrushBegin(source, target);
		}
		else if (x == numOfPoints - 1){
			m_pDoc->m_pCurrentBrush->BrushEnd(source, target);
		}
		else {
			m_pDoc->m_pCurrentBrush->BrushMove(source, target);
		}
		m_pDoc->setSize(origSize);
	}

	glFlush();
	SaveCurrentContent();

#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
#endif // !MESA

}

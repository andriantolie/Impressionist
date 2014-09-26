//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//TODO
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v)
{
	whoami(o)->m_colorDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}

//TODO
// Turn the original view into original image
void ImpressionistUI::cb_original_image(Fl_Menu_* o, void* v) {
	
}

//TODO
// Turn the original view into edge image
void ImpressionistUI::cb_edge_image(Fl_Menu_* o, void* v) {

}

//TODO
void ImpressionistUI::cb_another_image(Fl_Menu_* o, void* v) {

}


//TODO
void ImpressionistUI::cb_faster(Fl_Menu_* o, void* v) {
	
}

//TODO
void ImpressionistUI::cb_safer(Fl_Menu_* o, void* v) {

}
	
//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for COMP4411, Fall 2014");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;


	pDoc->setBrushType(type);
}

void ImpressionistUI::cb_strokeDirection(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	//pDoc->setMyType(type);
}	
//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

// Updates the line width
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{ 
		((ImpressionistUI*)(o->user_data()))->m_nLineWidth=int( ((Fl_Slider *)o)->value() ) ;
}

// Updates the line angle
void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
		((ImpressionistUI*)(o->user_data()))->m_nLineAngle=int( ((Fl_Slider *)o)->value() ) ;
}

// Updates the alpha
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
		((ImpressionistUI*)(o->user_data()))->m_nAlpha=float( ((Fl_Slider *)o)->value() ) ;
}

// Updates the edge clipping button
void ImpressionistUI::cb_edgeClippingButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->IsEdgeClipping==TRUE) pUI->IsEdgeClipping=FALSE;
		else pUI->IsEdgeClipping=TRUE;
	}
		
// Updates the another gradient button
void ImpressionistUI::cb_anotherGradientButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->IsAnotherGradient==TRUE) pUI->IsAnotherGradient=FALSE;
		else pUI->IsAnotherGradient=TRUE;
	}

// Updates the spacing slider
void ImpressionistUI::cb_spacingSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nSpacing=int( ((Fl_Slider *)o)->value() ) ;
}

// Updates the size random light button
void ImpressionistUI::cb_sizeRandomButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->IsSizeRandom==TRUE) pUI->IsSizeRandom=FALSE;
		else pUI->IsSizeRandom=TRUE;
	}


//TODO
void ImpressionistUI::cb_paintButton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_paintView->automaticDraw();
}

// Updates the edge threshold slider
void ImpressionistUI::cb_edgeThresholdSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nEdgeThreshold=int( ((Fl_Slider *)o)->value() ) ;
}

//TODO
void ImpressionistUI::cb_doItButton(Fl_Widget* o, void* v)
{
	return;
}

// Change the color blend value
void ImpressionistUI::cb_colorSelector(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_colorBlend[0] = float(((Fl_Color_Chooser *)o)->r());
	pUI->m_colorBlend[1] = float(((Fl_Color_Chooser *)o)->g());
	pUI->m_colorBlend[2] = float(((Fl_Color_Chooser *)o)->b());
}



//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

//------------------------------------------------
// Return the line width
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}

//-------------------------------------------------
// Set the line width
//-------------------------------------------------
void ImpressionistUI::setLineWidth(int lineWidth)
{
	m_nLineWidth = lineWidth;

	if (lineWidth <= 40)
		m_LineWidthSlider->value(m_nLineWidth);
}
//------------------------------------------------
// Return the line angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;
}

//-------------------------------------------------
// Set the line angle
//-------------------------------------------------
void ImpressionistUI::setLineAngle(int lineAngle)
{
    m_nLineAngle = lineAngle;

    if (lineAngle <= 359 && m_StrokeDirectionChoice->value() == SLIDER)
        m_LineAngleSlider->value(m_nLineAngle);
	
}

//------------------------------------------------
// Return the alpha value
//------------------------------------------------
float ImpressionistUI::getAlpha() {
	return m_nAlpha;
}

//------------------------------------------------
// Return the color blend value
//------------------------------------------------
float* ImpressionistUI::getColorBlend(){
	return m_colorBlend;
}
//------------------------------------------------
// Return the spacing
//------------------------------------------------

int	ImpressionistUI::getSpacing(){
	return m_nSpacing;
}
//------------------------------------------------
// Return the randomness of size
//------------------------------------------------
bool ImpressionistUI::getSizeRandomness(){
	return IsSizeRandom;
}
// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Colors...", FL_ALT + 'r', (Fl_Callback *)ImpressionistUI::cb_colors },
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },
	{ "&Display", 0, 0, 0, FL_SUBMENU },
		{ "&Original Image", FL_ALT + 'o', (Fl_Callback *) ImpressionistUI::cb_original_image },
		{ "&Edge image", FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_edge_image },
		{ "&Another image", FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_another_image },
		{ 0 },
	{ "&Options", 0, 0, 0, FL_SUBMENU },
		{ "&Faster", FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_faster },
		{ "&Safer", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_safer },
		{ 0 },
	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  { "Triangles", FL_ALT + 't', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_TRIANGLES },
  {0}
};


// Stroke direction choice menu definition
Fl_Menu_Item ImpressionistUI::m_StrokeDirectionChoiceMenu[NUM_STROKE_DIRECTION_TYPE + 1] = {
	{ "Slider/Right Mouse", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_strokeDirection, (void *)SLIDER },
	{ "Gradient", FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirection, (void *)GRADIENT },
	{ "Brush Direction", FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirection, (void *)BRUSH_DIRECTION },
	{ 0 }
};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_nAlpha = 1.00;
	IsEdgeClipping = TRUE;
	m_nSpacing = 4;
	IsSizeRandom = TRUE;
	m_nEdgeThreshold = 200;
	m_colorBlend[0] = 1.0;
	m_colorBlend[1] = 1.0;
	m_colorBlend[2] = 1.0;

	// brush dialog definition
	m_brushDialog = new Fl_Window(410, 335, "Brush Dialog");
	// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add a stroke direction choice to the dialog
		m_StrokeDirectionChoice = new Fl_Choice(115,45,150,25,"&Stroke Direction");
		m_StrokeDirectionChoice->user_data((void*)(this));	 // record self to be used by static callback functions
		m_StrokeDirectionChoice->menu(m_StrokeDirectionChoiceMenu);
		m_StrokeDirectionChoice->callback(cb_strokeDirection);
		m_StrokeDirectionChoice->deactivate();


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add line width slider to the dialog
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
	    m_LineWidthSlider->labelfont(FL_COURIER);
	    m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_lineWidthSlides);
		//if (m_pDoc->m_pCurrentBrush != ImpBrush::c_pBrushes[BRUSH_LINES] || m_pDoc->m_pCurrentBrush != ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES])
			m_LineWidthSlider->deactivate();

		// Add line angle slider to the dialog
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
	    m_LineAngleSlider->labelfont(FL_COURIER);
	    m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLineAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_lineAngleSlides);
		m_LineAngleSlider->deactivate();

		// Add alpha slider to the dialog
		m_AlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
	    m_AlphaSlider->labelfont(FL_COURIER);
	    m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.0);
		m_AlphaSlider->maximum(1.00);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nAlpha);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_alphaSlides);



		// Add a light button for edge clipping
		m_EdgeClippingButton = new Fl_Light_Button(10,200,130,25,"&Edge Clipping");
		m_EdgeClippingButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_EdgeClippingButton->value(IsEdgeClipping);
		m_EdgeClippingButton->callback(cb_edgeClippingButton);
		m_EdgeClippingButton->deactivate();

		// Add a light button for another gradient
		m_AnotherGradientButton = new Fl_Light_Button(240,200,150,25,"&Another Gradient");
		m_AnotherGradientButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_AnotherGradientButton->callback(cb_anotherGradientButton);
		m_AnotherGradientButton->deactivate();

		m_SpacingSlider = new Fl_Value_Slider(20, 240, 140, 20, "Spacing");
		m_SpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_SpacingSlider->type(FL_HOR_NICE_SLIDER);
	    m_SpacingSlider->labelfont(FL_COURIER);
	    m_SpacingSlider->labelsize(12);
		m_SpacingSlider->minimum(1);
		m_SpacingSlider->maximum(16);
		m_SpacingSlider->step(1);
		m_SpacingSlider->value(m_nSpacing);
		m_SpacingSlider->align(FL_ALIGN_RIGHT);
		m_SpacingSlider->callback(cb_spacingSlides);

		m_SizeRandomButton = new Fl_Light_Button(220,240,100,20,"&Size Rand.");
		m_SizeRandomButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_SizeRandomButton->value(IsSizeRandom);
		m_SizeRandomButton->callback(cb_sizeRandomButton);

		m_PaintButton = new Fl_Button(330,240,50,20,"&Paint");
		m_PaintButton->user_data((void*)(this));
		m_PaintButton->callback(cb_paintButton);

		m_PaintGroupBox = new Fl_Box(FL_THIN_UP_BOX, 10,230,380,40,"");
		m_PaintGroup = new Fl_Group(10, 230, 380, 40, "");
		m_PaintGroup->user_data((void*)this);
		m_PaintGroup->resizable(m_PaintGroupBox);
		m_PaintGroup->add(m_SpacingSlider);
		m_PaintGroup->add(m_SizeRandomButton);
		m_PaintGroup->add(m_PaintButton);

		m_EdgeThresholdSlider = new Fl_Value_Slider(20, 285, 200, 20, "Edge Threshold");
		m_EdgeThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_EdgeThresholdSlider->type(FL_HOR_NICE_SLIDER);
	    m_EdgeThresholdSlider->labelfont(FL_COURIER);
	    m_EdgeThresholdSlider->labelsize(12);
		m_EdgeThresholdSlider->minimum(0);
		m_EdgeThresholdSlider->maximum(500);
		m_EdgeThresholdSlider->step(1);
		m_EdgeThresholdSlider->value(m_nEdgeThreshold);
		m_EdgeThresholdSlider->align(FL_ALIGN_RIGHT);
		m_EdgeThresholdSlider->callback(cb_edgeThresholdSlides);

		m_DoItButton = new Fl_Button(330,285,50,20,"&Do it");
		m_DoItButton->user_data((void*)(this));
		m_DoItButton->callback(cb_doItButton);

		m_DoItGroupBox = new Fl_Box(FL_THIN_UP_BOX, 10,275,380,40,"");
		m_DoItGroup = new Fl_Group(10, 275, 380, 40, "");
		m_DoItGroup->user_data((void*)this);
		m_DoItGroup->resizable(m_DoItGroupBox);
		m_DoItGroup->add(m_EdgeThresholdSlider);
		m_DoItGroup->add(m_DoItButton);


    m_brushDialog->end();	

	//set color dialog
	m_colorDialog = new Fl_Window(200, 250, "Color Selector");
	    m_ColorSelector = new Fl_Color_Chooser(0, 0, 200, 250, "Color Selector");
		m_ColorSelector->user_data((void*)this);
		m_ColorSelector->rgb(1.0, 1.0, 1.0);
		m_ColorSelector->callback(cb_colorSelector);
	m_colorDialog->end();



}


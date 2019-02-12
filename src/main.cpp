
#include "constParameter.h"
#include "ofApp.h"
#include "ofViewerApp.h"
#include "ofDisplayerApp.h"

//========================================================================
int main( ){

#ifdef PROJECTION_MODE
	ofGLFWWindowSettings settings_;
	//Projection Window
	settings_.width = cProjectionWindowWidth;
	settings_.height = cProjectionWindowHeight;
	settings_.setPosition(ofVec2f(1920, 0));
	settings_.resizable = false;
	shared_ptr<ofAppBaseWindow> displaerWindow = ofCreateWindow(settings_);

	//View Window
	settings_.width = cViewWindowWidth;
	settings_.height = cViewWindowHeight;
	settings_.setPosition(ofVec2f(0, 0));
	settings_.shareContextWith = displaerWindow;
	shared_ptr<ofAppBaseWindow> viewWindow = ofCreateWindow(settings_);

	shared_ptr<ofDisplayerApp> displayerApp(new ofDisplayerApp);
	shared_ptr<ofViewerApp> viewApp(new ofViewerApp);

	ofRunApp(viewWindow, viewApp);
	ofRunApp(displaerWindow, displayerApp);

	ofRunMainLoop();
#else //PROJECTION_MODE
	ofSetupOpenGL(cViewWidth, cViewHeight, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofViewerApp());
#endif //PROJECTION_MODE
	

}

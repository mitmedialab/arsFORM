#include "ofAppGlutWindow.h"
#include "ReliefApplication.h"
#include "UITriggers.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    
//    // hide the cursor
    CGDisplayHideCursor(kCGDirectMainDisplay);
    
    ofSetupOpenGL(&window, 2*1920, 1080, OF_FULLSCREEN);
    //ofSetupOpenGL(&window, 2*1920, 1080, OF_FULLSCREEN);
	
    ReliefApplication *relief = new ReliefApplication();    
    
    // this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(relief);

}

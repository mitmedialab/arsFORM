//
//  ShapeObject.h
//  basicExample
//
//  Created by Daniel Leithinger on 3/20/14.
//
//

#ifndef __basicExample__ShapeObject__
#define __basicExample__ShapeObject__

#include "ofMain.h"
#include "ShapeIOManager.h"
#include <iostream>

class ShapeObject {
public:
    // If required, change table values best fit for this shape object
    virtual void setTableValuesForShape(ShapeIOManager *pIOManager){};
    
    // Update the current shape object
    virtual void update(){};
    
    // draw the depth map for given shape
    // region will be from (0,0) to (w,h)
    virtual void renderTangibleShape(int w, int h){};
    
    // draw the graphics for the UI
    virtual void renderTouchscreenGraphics(int w, int h){};
    
    // draw the graphics for the projector
    virtual void renderProjectorOverlay(int w, int h){};
    
    // draw the graphics for the left margin on the touch screen
    virtual void renderMarginGraphics(int x, int y){};
    
    // mouse events from the touch screen
    virtual void mouseMoved(int x, int y){};
    virtual void mousePressed(int x, int y, int button){};

};

#endif /* defined(__basicExample__ShapeObject__) */

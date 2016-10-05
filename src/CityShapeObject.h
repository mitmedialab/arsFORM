//
//  CityShapeObject.h
//  cooperFORM
//
//  Created by ken_tmg on 11/7/14.
//
//

#ifndef __cooperFORM__CityShapeObject__
#define __cooperFORM__CityShapeObject__

#include <stdio.h>


#include "ShapeObject.h"
#include "ofxAnimatableOfPoint.h"

class CityShapeObject : public ShapeObject {
    
public:
    CityShapeObject();
    void update();
    void renderProjectorOverlay(int w, int h);
    void renderTangibleShape(int w, int h);
    void renderTouchscreenGraphics(int w, int h);
    void keyReleased(int key);
    void setMouseDragInfo(int x, int y, int button);
    void setMousePressedInfo(int x, int y);
    void setMouseReleasedInfo();
    
    float getMovPosition();
    void setMovPosition(float t);
    void chooseCity(int num);
    
    void reset();
    
    int currentCity;
    int previousCity;
    
    
    //int posX, posY;
    
    int rectLength;
    int length;
    
    
    ofVec2f pos;
    ofVec2f oldMouse;
    
    string get_shape_name() {return shape_name; };
    //void setTableValuesForShape(ShapeIOManager *pIOManager);
    
    ofImage mapShadow;
    ofImage loupe;
    
    bool loupeDragged;
    bool sliderGrabbed;
    
    ofxAnimatableOfPoint loupeTargetPostion;
    
    float time;
    
private:
    string shape_name = "city";
    
    ofFbo touchscreenImage; //FBO where we render graphics for pins
    ofFbo pinHeightMapImage; //FBO where we render height map
    ofFbo projectorImage; //FBO that will be displayed from the projector
    
    
    const int cityNum = 4;
    ofVideoPlayer cityMov[4][2];
    
    ofTexture trimmedMov[2];
    
    ofImage realMap;
    ofImage cityImages[4][2];
    
    unsigned char * trimMov;
    
    const int heightMapMovieSize = 300;
    //const int imageSize = 2894;
    
};


#endif /* defined(__cooperFORM__CityShapeObject__) */

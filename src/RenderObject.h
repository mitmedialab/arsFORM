//
//  RenderObject.h
//  cooperFORM
//
//  Created by Philipp Schoessler on 10/19/14.
//
//

#ifndef cooperFORM_RenderObject_h
#define cooperFORM_RenderObject_h

#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"
#include "Constants.h"

class RenderObject {
public:
    ofShader heightMapShader;
    ofxAnimatableOfPoint position;
    ofxAnimatableOfPoint size;
    ofColor color;
    
    bool useColor = false;
    bool render = false;
    bool isTouched = false;
    bool isHovered = false;
    bool containsObject = false;
    
    virtual void update(float dt) {};
    virtual void drawHeightMap(){};
    virtual void drawGraphics(){};
    
    virtual void touchTest(vector<ofPoint> & touchPoints){};
    virtual void objectTest(vector<ofPoint> & objectCentroids){};
    
    
    void loadShader() {heightMapShader.load("shaders/heightMapShader");}
    
    void setSize(ofPoint size) {this->size.setPosition(size);};
    void setPosition(ofPoint position) {this->position.setPosition(position);};
    void setColor(ofColor color) {this->color = color; useColor = true;};
};


#endif

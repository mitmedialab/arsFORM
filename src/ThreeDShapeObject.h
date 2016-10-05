//
//  ThreeDShapeObject.h
//  cooperFORM
//
//  Created by Philipp Schoessler on 10/17/14.
//
//

#ifndef __cooperFORM__ThreeDShapeObject__
#define __cooperFORM__ThreeDShapeObject__

#include "ofxAssimpModelLoader.h"
#include "ofx3DModelLoader.h"
#include "ShapeObject.h"
#include <iostream>

class ThreeDShapeObject : public ShapeObject {
    
    struct threeDModel
    {
        ofxAssimpModelLoader model;
        string name;
        float z;
    };
    
public:
    ThreeDShapeObject();
    void update();
    void renderProjectorOverlay(int w, int h);
    void renderTangibleShape(int w, int h);
    void renderTouchscreenGraphics(int w, int h);
    void renderMarginGraphics(int x, int y);
    
    void setMouseDragInfo(int x, int y, int button);
    void setMousePressedInfo(int x, int y);
    void setScale(float uniformScaleVal);
    
    string getCurrentModelName();
    
    void changeModel(int idx);
    void changeModel(string direction);
    void reset();
    
    vector<threeDModel*> models;
    ofCamera cam;
    ofLight	light;
    ofFbo pinHeightMapImage;
    ofFbo pinHeightMapImageSmall;
    ofFbo marginImage;
    ofFbo projectorImage;
    ofFbo projectorImageSmall;
    
    ofPixels projectorMaskedPixels;
    ofPixels pinHeightMapPixels;
    ofColor c;
    ofColor p;
    
    ofImage maskedResult;
    
    string get_shape_name() {return shape_name; };
    void setTableValuesForShape(ShapeIOManager *pIOManager) {};
    
    ofImage bgImg;
    ofShader shader;
    
    
    //arcball
    ofQuaternion    quat;
    ofVec2f         oldMouse;
    float           dampen;
    ofVec3f axis;
    float angle;
    
    int marginX;
    int marginY;
    
private:
    string shape_name = "3D";
    string currentModelName = "empty";
    float scale;
    int numLoadedModels;
    int idx;
    int maskThresh;
};

#endif /* defined(__cooperFORM__ThreeDShapeObject__) */

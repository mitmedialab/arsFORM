//
//  WavyShapeObject.h
//  basicExample
//
//  Created by Tangible Media Group on 3/21/14.
//
//

#ifndef __basicExample__WavyShapeObject__
#define __basicExample__WavyShapeObject__

#include "ShapeObject.h"
#include "KinectTracker.h"
#include "ofxOpenCv.h"
#include <iostream>

class WavyShapeObject : public ShapeObject {

public:
    void setKinectTracker(KinectTracker * pKinectTracker){ mKinectTracker = pKinectTracker; };
    
    int solveCount = 1;
    
    float friction;
    float speed;
    
    int cols, rows;
    
    int getCols();
    int getRows();
    
    ofImage depthImageInput;
    ofPixels depthMap;
    ofFbo depthData;
    ofFbo depthOutputFBO;
    
    WavyShapeObject();
    WavyShapeObject(float width, float height, float cellSize);
    //WavyShapeObject(float width, float height, float cellSize);
    WavyShapeObject(int numCols, int numRows);
    
    
    void renderProjectorOverlay(int w, int h);
    void renderTangibleShape(int w, int h);
    void renderTouchscreenGraphics(int w, int h);
    
    void update();
    
    void updateDepthMapFromPixels(unsigned char * pixels, int w, int h, ofImageType imageType);
    
    void solveFluid();
    float getAdjacentDensitySum(int x, int y);
    void getDepthMapKinect();
    


    string get_shape_name() {return shape_name; };
    void setTableValuesForShape(ShapeIOManager *pIOManager);
    
    ofFbo editor;
    void beginEdit();
    void endEdit();
    unsigned char* getPixels();
    
    float seaLevel; // Resting height for the liquid. 0 - 255
    float getSeaLevel();
    void  setSeaLevel(float level);
    
    float waveAmplitude; // The wave powers
    float getWaveAmplitude();
    void  setWaveAmplitude(float amplitude);
    
    // Scales both sea level and wave amplitude 0 - 1 inclusive
    float waveScalar;
    float destWaveScalar;
    
    float idleWaveAmplitude = 75;
    float idleWaveFrequency = 10;
    
    long waveScalarSetTime;
    void setWaveScalar(float scalar);
    float getWaveScalar();
    
    float idleWaveScalar;
    void setIdleWaveScalar(float scalar);

    void reset();
private:
    
    void init(int numCols, int numRows);
    
    ofImage surface;
    float **velocity;
    float **density;
    
    long previousMS;
    long currentMS; // in ms
    int fixedDeltaMS;
    int leftOverMS;
    
    long lastInterpolatedMS = 0;
    
    // array of velocity derivatives
    // allows for nth order approximation of the velocity field
    float ***taylorSeries;
    int interpolate;
    long lastInterp;
    void interpolateSurface();

    KinectTracker * mKinectTracker;

    void idleWaves();
    
    string shape_name = "Wavy";
    
    //tracking closest blob and map to heartbeat
    float dist;
    //float time;
    unsigned char* allPixels;
    
    int minX, minY, maxX, maxY;
};

#endif /* defined(__basicExample__WavyShapeObject__) */

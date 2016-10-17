#pragma once

#include "ofMain.h"
#include "UIHandler.h"
#include "ShapeIOManager.h"
#include "ShapeObject.h"
#include "CameraTracker.h"
#include "KinectShapeObject.h"
#include "WavyShapeObject.h"
#include "MoveBallShapeObject.h"
#include "ThreeDShapeObject.h"
#include "CityShapeObject.h"
#include "MathShapeObject.h"
#include "KinectTracker.h"
#include "OSCInterface.h"
#include "Function.h"

class ReliefApplication : public ofBaseApp {
public:
    UIHandler       * uiHandler;

    // the table mode we're on
    // "telepresence", "wavy", "3D", and "math"
    string          currentMode;
    
    // manages communication with the pin display
    ShapeIOManager   * mIOManager;

    // table config variables
    float            gain_P;
    float            gain_I;
    int              max_I;
    int              deadZone;
    int              maxSpeed;
    
    //  camera calibration variables:
    ofRectangle kinectDepthcamCropDims;
    ofRectangle kinectRGBcamCropDims;
    ofRectangle kinectRGBcamProjDims;
    ofRectangle vertRGBcamDims;
    ofRectangle mathModeProjectionDims;
    int calibrationMode = 0; // 0=none, 1=kinectDepthcam; 2=kinectRGBcam; 3=mathDim;

    // heightmap data for the pins 
    ofFbo            pinHeightMapImage;
    // the heightmap data for the pins
    ofFbo            pinHeightMapImageSmall;
    // image to be projected on top of the pins
    ofFbo            projectorOverlayImage;
    // image to be displayed on the touch screen
    ofFbo            touchScreenDisplayImage;
    // image to be displayed on the left margin of the touch screen (only for 3D Mode)
    ofFbo            marginTouchDisplayImage;
    ofFbo            transitionImage;

    ShapeObject      * currentShape;
    ShapeObject      * currentTransitionFromShape;
    ShapeObject      * currentTransitionToShape;
    ShapeObject      * overlayShape;
    long             transitionLengthMS;
    long             transitionStart = 0;
    
    // our interface for the cameras
    CameraTracker    cameraTracker;

    // Shape objects
    KinectShapeObject   * kinectShapeObject;
    WavyShapeObject     * wavyShapeObject;
    MoveBallShapeObject * ballMoverShapeObject;
    ThreeDShapeObject   * threeDShapeObject;
    CityShapeObject     * cityShapeObject;
    MathShapeObject     * mathShapeObject;

    // our interface for the Kinect
    KinectTracker    kinectTracker;
    
    // our interface for communicating with the computer for the vertical display
    OSCInterface    * backDisplayComputer;
    
    // whether or not we're on the info screen
    bool showInfo = true;
    
    bool motorsEnabled = true;
    bool renderDebuggingInfo = true;
    
    void setup();
    void update();
    void draw();
    void exit();
    
    // initialize all the UI elements
    void setupUI();
    void drawDebugScreen();
    
    void setMode(string newMode);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void loadCalibrationParams(string fileName);
    void saveCalibrationParams(string fileName);
    void changeCalibrationParams(int key);
};

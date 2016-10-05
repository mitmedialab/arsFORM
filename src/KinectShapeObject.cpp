//
//  KinectShapeObject.cpp
//  basicExample
//
//  Created by Daniel Leithinger on 3/20/14.
//
//

#include "KinectShapeObject.h"

KinectShapeObject::KinectShapeObject() {
    mKinectHeightImage.allocate(KINECT_X, KINECT_Y);
    mOutputShapeImage.allocate(KINECT_X, KINECT_Y);
};

void KinectShapeObject::update(){

    mKinectHeightImage.begin();
    mKinectTracker->drawDepthThreshedImage(0,0, mKinectHeightImage.getWidth(), mKinectHeightImage.getHeight());
    mKinectHeightImage.end();

    mOutputShapeImage.begin();
    mKinectTracker->drawColorThresholdImage(0,0, mOutputShapeImage.getWidth(), mOutputShapeImage.getHeight());
    mOutputShapeImage.end();

};

void KinectShapeObject::renderTouchscreenGraphics(int w, int h){
    //mKinectHeightImage.draw(0,0, w, h);
    ofSetColor(255);
    //cameraTracker->drawCameraFeed(0, -194, -26, 1502, 1120);
    cameraTracker->drawCameraFeed(0, 0, 0, 1920, 1080);
};
void KinectShapeObject::renderTangibleShape(int w, int h){
    mKinectHeightImage.draw(0,0, w, h);
};
void KinectShapeObject::renderProjectorOverlay(int w, int h){
    
    // latest for cooper hewitt: mOutputShapeImage.draw(510, 242, 1065, 814);
    ofSetColor(255);
    mOutputShapeImage.draw(0,0, w, h);
};

void KinectShapeObject::mouseMoved(int x, int y){

};
void KinectShapeObject::mousePressed(int x, int y, int button){

};

void KinectShapeObject::setTableValuesForShape(ShapeIOManager *pIOManager) {
    pIOManager->set_max_speed(200);
    pIOManager->set_gain_p(1.5f);
    pIOManager->set_gain_i(0.045f);
    pIOManager->set_max_i(25);
    pIOManager->set_deadzone(2);
};
//
//  KinectTracker.h
//  basicExample
//
//  Created by Tangible Media Group on 2/16/14.
//
//

#ifndef __basicExample__KinectTracker__
#define __basicExample__KinectTracker__

#include <iostream>

#include "ofxOpenCv.h"
#include "ofxKinect.h"

class KinectTracker {
private:
    int cropX, cropY, cropWidth, cropHeight;
    
	ofxKinect               kinect;
	
	
	ofxCvGrayscaleImage     depthImg; // grayscale depth image
	ofxCvGrayscaleImage     activityDepthImg; // grayscale depth image to track activity level around the kiosk
    ofxCvGrayscaleImage     grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage     grayThreshFar; // the far thresholded image
    
    ofxCvGrayscaleImage     depthThreshed; // grayscale depth image
    ofxCvGrayscaleImage     erodedDepthThreshed;
    ofxCvGrayscaleImage     lastDepthThreshed;
    ofxCvGrayscaleImage     depthThreshedDiff;
    
    ofxCvColorImage         colorImg;
    ofxCvColorImage         colorImgThreshed;
    
    ofxCvColorImage         colorImgCropped;
    ofxCvGrayscaleImage     depthImgCropped;
	
	ofxCvContourFinder      contourFinder;
    
    void updateImagesFromKinect();
    void flagImagesAsChanged();
    void cropImages();
    void calculateThresholdsAndModifyImages();
    void loadAlphaMaskAndPrepForCvProcessing();
    
    void trackActivityAroundTable();
    bool enableTimeOut = true;
    
public:
    
    
    int mNearThreshold; // the far threshold, closest possible value is 255, farthest possible value 0
	int mFarThreshold; // the far threshold, closest possible value is 255, farthest possible value 0
    int mContourMinimumSize; // the minimum size of a contour in pixels
    bool useMask = true;
    
    ofImage mask, colorMask;
    ofxCvColorImage maskColorCv;
    ofxCvGrayscaleImage maskCv;
    
    void setup(int pNearThreshold = 80, int pFarThreshold = 70, int pContourMinimumSize = 20);
    void update();
    void updateCurrentFrame(unsigned char * pixels, int w, int h);
    
    // draw various images coordinates and size
    void drawColorImage(int x, int y, int width, int height);
    void drawColorThresholdImage(int x, int y, int width, int height);
    void drawDepthImage(int x, int y, int width, int height);
    void drawActivityDepthImage(int x, int y, int width, int height);
    
    void drawThresholdImage(int x, int y, int width, int height);
    
    void drawDepthThreshedImage(int x, int y, int width, int height);
    void drawDepthThreshedDiff(int x, int y, int width, int height);
    
    // generate video pixels for recording kinect input
    unsigned char * getRecordingPixels();
    
    // get images as pixels
    unsigned char *  getColorPixels();
    unsigned char *  getDepthPixels();
    unsigned char *  grayImagePixels();

    unsigned char *  depthThreshedPixels();
    ofPixels depthThresholdOFPixels();
    
    // get contour finder
    ofxCvContourFinder * getContourFinder();
    
    // getter pass through methods
    int     numAvailableDevices();
    bool    isFrameNew();
    bool    isConnected();

    void setCrop(int x, int y, int width, int height);
    
    unsigned char * returnPixels;
    ofPixels ofPixels;
    ofImage recordingImage, playingImage;
    ofImage imageLeft;
    ofImage imageRight;
    
    // return the time elapsed since last activity in the depth map
    // in seconds
    long lastActiveTime = 0;
    double timeSinceLastActive();
};


#endif /* defined(__basicExample__KinectTracker__) */

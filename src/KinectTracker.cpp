//
//  KinectTracker.cpp
//  basicExample
//
//  Created by Tangible Media Group on 2/16/14.
//
//


#include "KinectTracker.h"
#include "Constants.h"

void KinectTracker::setup(int pNearThreshold, int pFarThreshold, int pContourMinimumSize) {
	
    if(kinect.numAvailableDevices() > 0) {
        kinect.setRegistration(true); // enable depth->video image calibration
        kinect.init(false, true, true);
        kinect.open();
    }
    
	// print the intrinsic IR sensor values
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
	}
	
	colorImg.allocate(kinect.width, kinect.height);
    depthImg.allocate(kinect.width, kinect.height);
    activityDepthImg.allocate(kinect.width, kinect.height);
    
    colorImgCropped.allocate(kinect.width, kinect.height);
    depthImgCropped.allocate(kinect.width, kinect.height);
    
//	grayThreshNear.allocate(kinect.width, kinect.height);
//	grayThreshFar.allocate(kinect.width, kinect.height);
	depthThreshed.allocate(kinect.width, kinect.height);
    erodedDepthThreshed.allocate(kinect.width, kinect.height);
    lastDepthThreshed.allocate(kinect.width, kinect.height);
    depthThreshedDiff.allocate(kinect.width, kinect.height);
    recordingImage.allocate(kinect.width*2, kinect.height, OF_IMAGE_COLOR);
    playingImage.allocate(kinect.width*2, kinect.height, OF_IMAGE_COLOR);
    
	mNearThreshold = pNearThreshold;
	mFarThreshold = pFarThreshold;
    mContourMinimumSize = pContourMinimumSize;
    
    //loadAlphaMaskAndPrepForCvProcessing();
    
    cropX = 0;
    cropY = 0;
    cropWidth = kinect.width;
    cropHeight = kinect.height;
}

//--------------------------------------------------------------
//
// Update
//
// If playing from a recording, we set
// the colorImg and depthImg from the video
// and the rest of the class continues to reference
// colorImg and depthImg, rather then needing to
// reference different images depending on the input.
//
//--------------------------------------------------------------

void KinectTracker::update() {
    
    //if(kinect.numAvailableDevices() == 0)
    //    return;
    
    kinect.update();
	
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
		
        // update from kinect
        updateImagesFromKinect();
        
        // activity tracking around the installation
        // subtract mask which is png alpha image called "mask.png"
        //if(useMask) subtractMask();\

        trackActivityAroundTable();
        
        depthImg.dilate_3x3();
        depthImg.erode_3x3();
        
        cropImages();
        
        lastDepthThreshed.setFromPixels(depthThreshed.getPixels(), depthThreshed.getWidth(), depthThreshed.getHeight());
        // always update the depth image
        depthThreshed.setFromPixels(depthImgCropped.getPixels(), depthImgCropped.getWidth(), depthImgCropped.getHeight());
        colorImgThreshed.setFromPixels(colorImgCropped.getPixels(), colorImgCropped.getWidth(), colorImgCropped.getHeight());
                
        // threshold calcutations convery depth map into black and white images
		calculateThresholdsAndModifyImages();
        
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// if find holes is set to true, we will get interior contours as well.
		//contourFinder.findContours(depthImg, mContourMinimumSize, (kinect.width*kinect.height)/2, 10, false);
        
        depthThreshedDiff.absDiff(lastDepthThreshed, depthThreshed);
	}
}

// we are using kinect
void KinectTracker::updateImagesFromKinect() {
    colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
    colorImg.mirror(true,true);
    colorImg.flagImageChanged();
    
    depthImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
    depthImg.mirror(true,true);
    depthImg.flagImageChanged();
    
    activityDepthImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
    activityDepthImg.flagImageChanged();
    
}

// used by the player class to set the current frame from now playing movie
void KinectTracker::updateCurrentFrame(unsigned char * pixels, int w, int h) {
    playingImage.setFromPixels(pixels, w, h, OF_IMAGE_COLOR);
}

void KinectTracker::flagImagesAsChanged() {
    colorImg.flagImageChanged();
    depthImg.flagImageChanged();
    depthThreshed.flagImageChanged();
}

void KinectTracker::cropImages() {
//    if (cropX == 0 && cropY == 0 && cropWidth == colorImg.getWidth() && cropHeight == colorImg.getHeight())
//        return;
    
    ofImage fullColor;
    fullColor.allocate(colorImg.getWidth(), colorImg.getHeight(), OF_IMAGE_COLOR);
    fullColor.setFromPixels(colorImg.getPixels(), colorImg.getWidth(), colorImg.getHeight(), OF_IMAGE_COLOR);
    fullColor.crop(cropX, cropY, cropWidth, cropHeight);
    colorImgCropped.setFromPixels(fullColor.getPixels(), fullColor.getWidth(), fullColor.getHeight());

    ofImage fullDepth;
    fullDepth.allocate(depthImg.getWidth(), depthImg.getHeight(), OF_IMAGE_GRAYSCALE);
    fullDepth.setFromPixels(depthImg.getPixels(), fullDepth.getWidth(), fullDepth.getHeight(), OF_IMAGE_GRAYSCALE);
    fullDepth.crop(cropX, cropY, cropWidth, cropHeight);
    depthImgCropped.setFromPixels(fullDepth.getPixels(), fullDepth.getWidth(), fullDepth.getHeight());
}

// loads png mask and converts to cv grayscale which we need to cvAnd method
void KinectTracker::loadAlphaMaskAndPrepForCvProcessing() {
    
    // type is OF_IMAGE_COLOR_ALPHA
    mask.loadImage("mask.png");
    
    // simple way to convert to differe image type,
    // changing the transparent areas to white
    ofImage image;
    image.setFromPixels(mask.getPixelsRef());
    image.setImageType(OF_IMAGE_COLOR);
    maskColorCv.setFromPixels(image.getPixels(), mask.getWidth(), mask.getHeight());
    maskCv = maskColorCv;
    
}

void KinectTracker::trackActivityAroundTable() {
    activityDepthImg.threshold(KINECT_FAR_CUTOFF_PLANE + KINECT_ACTIVITY_PLANE_DISTANCE);
    //cvAnd(activityDepthImg.getCvImage(), maskCv.getCvImage(), activityDepthImg.getCvImage(), NULL);
    activityDepthImg.flagImageChanged();
    
    int numActivePixels = 0;
    for (int x = KINECT_ACTIVITY_CROP_X; x < KINECT_ACTIVITY_CROP_X + KINECT_ACTIVITY_CROP_WIDTH; x++) {
        for (int y = KINECT_ACTIVITY_CROP_Y; y < KINECT_ACTIVITY_CROP_Y + KINECT_ACTIVITY_CROP_HEIGHT; y++) {
            if (activityDepthImg.getPixelsRef().getColor(x,y).getBrightness() > 0) {
                numActivePixels++;
            }
        }
    }
    
    if (numActivePixels > KINECT_ACTIVITY_CROP_NUM_PIXELS || !enableTimeOut)
        lastActiveTime = ofGetElapsedTimeMillis();
}

void KinectTracker::calculateThresholdsAndModifyImages() {

    ofPixelsRef depthPixels = depthThreshed.getPixelsRef();

    for (int x = 0; x < depthPixels.getWidth(); x++) {
        for (int y = 0; y < depthPixels.getHeight(); y++) {
            float shade = ofClamp((depthPixels.getColor(x,y).getBrightness() - mFarThreshold) * 144.f / (mNearThreshold - mFarThreshold), 0, 144);

            if (shade > 0) {
                depthPixels.setColor(x,y, shade + DEPTH_HANDS_MINIMUM_HEIGHT);
            }
            else {
                depthPixels.setColor(x,y, 0);
            }
        }
    }
    
    depthThreshed.flagImageChanged();
    
    erodedDepthThreshed.setFromPixels(depthThreshed.getPixels(), depthThreshed.getWidth(), depthThreshed.getHeight());
    //erodedDepthThreshed.erode_3x3();
    erodedDepthThreshed.erode_3x3();
    
    
    // threshold the color image to be black underneath the depth image -
    // this function is disabled for the Ars Electronica exhibit, where we only use a black pedestal,
    // instead of a touch screen display
    /*ofPixelsRef colorPixels = colorImgThreshed.getPixelsRef();
    ofPixelsRef erodedDepthPixels = erodedDepthThreshed.getPixelsRef();
    for (int x = 1; x < erodedDepthPixels.getWidth()-1; x++) {
        for (int y = 1; y < erodedDepthPixels.getHeight()-1; y++) {
            if (erodedDepthPixels.getColor(x, y).getBrightness() <=0)
                colorPixels.setColor(x,y, 0);
        }
    }*/
    
    colorImgThreshed.flagImageChanged();
}

//--------------------------------------------------------------
//
// Draw various images
//
//--------------------------------------------------------------

// color image
void KinectTracker::drawColorImage(int x, int y, int width, int height) {
    ofSetColor(255);
    colorImg.draw(x, y, width, height);
}

// color image
void KinectTracker::drawColorThresholdImage(int x, int y, int width, int height) {
    ofSetColor(255);
    colorImgThreshed.draw(x, y, width, height);
}

// gray image with contour blobs drawn on top
void KinectTracker::drawThresholdImage(int x, int y, int width, int height){
    ofSetColor(255);
    depthThreshed.draw(x,y,width,height);
    //depthImg.draw(x, y, width, height);
    //contourFinder.draw(x, y, width, height);
}

// draw from the live kinect
void KinectTracker::drawDepthImage(int x, int y, int width, int height){
    ofSetColor(255);
    depthImg.draw(x, y, width, height);
}

void KinectTracker::drawActivityDepthImage(int x, int y, int width, int height) {
    ofSetColor(255);
    activityDepthImg.draw(x, y, width, height);
    ofNoFill();
    ofSetColor(255);
    ofRect(KINECT_ACTIVITY_CROP_X, KINECT_ACTIVITY_CROP_Y,
           KINECT_ACTIVITY_CROP_WIDTH, KINECT_ACTIVITY_CROP_HEIGHT);
    ofFill();
}

// black and white image from within threshold range
void KinectTracker::drawDepthThreshedImage(int x, int y, int width, int height) {
    ofSetColor(255);
    depthThreshed.draw(x, y, width, height);
}

// black and white difference image from within threshold range
// (only data from movements)
void KinectTracker::drawDepthThreshedDiff(int x, int y, int width, int height) {
    ofSetColor(255);
    depthThreshedDiff.draw(x,y, width, height);
}


//--------------------------------------------------------------
//
// Get various kinect images as pixels
//
//--------------------------------------------------------------

// standard color image from kinect video camera
unsigned char * KinectTracker::getColorPixels() {
    return colorImg.getPixels();
}

// kinect depth map
// grayscale image where white = near, black = far
unsigned char * KinectTracker::getDepthPixels() {
    return kinect.getDepthPixels();
}

// kinect depth map WHERE
// areas outside near and far threshold range are black.
// This is currently used by the wave animation
unsigned char * KinectTracker::depthThreshedPixels() {
    return depthThreshed.getPixels();
}

// kinect depth map WHERE
// areas outside near and far threshold range are black.
// This is currently used by the wave animation
ofPixels KinectTracker::depthThresholdOFPixels() {
    return depthThreshed.getPixelsRef();
}


// kinect depth map WHERE
// only black OR white (0 OR 255) is used.
// calculated using using pContourMinimumSize
unsigned char * KinectTracker::grayImagePixels() {
    return depthImg.getPixels();
}

// returns pixels
// color image is on left and depth is on right
unsigned char * KinectTracker::getRecordingPixels() {
    return recordingImage.getPixels();
}


// get a reference to the contour finder
ofxCvContourFinder * KinectTracker::getContourFinder() {
    return &contourFinder;
}


//--------------------------------------------------------------
//
// Kinect pass through getters
//
// Since we wrap the kinect class we no longer have access to
// its methods unless we add them to KinectTracker too.
//
//--------------------------------------------------------------
int KinectTracker::numAvailableDevices(){
    return kinect.numAvailableDevices();
}

bool KinectTracker::isFrameNew() {
    return kinect.isFrameNew();
}

bool KinectTracker::isConnected() {
    return kinect.isConnected();
}

void KinectTracker::setCrop(int x, int y, int width, int height) {
    cropX = x;
    cropY = y;
    cropWidth = width;
    cropHeight = height;
    
    colorImgCropped.allocate(cropWidth, cropHeight);
    depthImgCropped.allocate(cropWidth, cropHeight);
    depthThreshed.allocate(cropWidth, cropHeight);
    lastDepthThreshed.allocate(cropWidth, cropHeight);
    depthThreshedDiff.allocate(cropWidth, cropHeight);
}


double KinectTracker::timeSinceLastActive() {
    return (ofGetElapsedTimeMillis() - lastActiveTime) / 1000.0;
}

void KinectTracker::resetTimeSinceLastActive() {
    lastActiveTime = ofGetElapsedTimeMillis();
}
//
//  UISlider.cpp
//  cooperFORM
//
//  Created by Tangible Media Group on 9/26/14.
//
//

#include "UISlider.h"
#include "UITriggers.h"

UISlider::UISlider() { }
UISlider::UISlider(string name, bool horizontal, int trackX, int trackY, int trackLength, int handleWidth, int handleHeight) {
    this->name = name;
    
    this->horizontal = horizontal;
    
    this->trackX = trackX;
    this->trackY = trackY;
    imageTrackX = trackX;
    imageTrackY = trackY;
    
    handlePos = 0.0;
    
    this->trackLength = trackLength;
    
    this->handleWidth = handleWidth;
    this->handleHeight = handleHeight;
    
    trackImage = new ofImage();
    handleImageIdle = new ofImage();
    handleImageActive = new ofImage();
    
    lockToPoses = vector<float>();
}

string UISlider::getName() {
    return name;
}

void UISlider::draw() {
    if (!visible)
        return;
    
    
    ofPushStyle();
    
    int endTrackX = 0;
    int endTrackY = 0;
    if (horizontal) {
        endTrackX = trackX + trackLength;
        endTrackY = trackY;
    }
    else {
        endTrackX = trackX;
        endTrackY = trackY + trackLength;
    }
    
    if (trackImage->isAllocated()) {
        int trackImageDrawX = imageTrackX;
        int trackImageDrawY = imageTrackY;
        
        if (horizontal) {
            trackImageDrawY += imageTrackOffset;
        }
        else {
            trackImageDrawX += imageTrackOffset;
        }
        trackImage->draw(trackImageDrawX, trackImageDrawY);
    }
    else {
        ofSetLineWidth(5);
        ofSetColor(200);
        ofLine(trackX, trackY, endTrackX, endTrackY);
    }
    
    
    if (handleImageIdle->isAllocated() and handleImageActive->isAllocated()) {
        if (isGrabbed())
            handleImageActive->draw(getHandleX(), getHandleY(), handleWidth, handleHeight);
        else
            handleImageIdle->draw(getHandleX(), getHandleY(), handleWidth, handleHeight);
    }
    else {
        if (isGrabbed())
            ofSetColor(ofColor(255,0,0));
        else
            ofSetColor(ofColor(0,0,255));
        ofRect(getHandleX(), getHandleY(), handleWidth, handleHeight);
    }
    ofPopStyle();
}
void UISlider::enable() {
    enabled = true;
}
void UISlider::disable() {
    enabled = false;
}

void UISlider::show() {
    visible = true;
}
void UISlider::hide() {
    visible = false;
}


void UISlider::setImageTrack(string imageName) {
    trackImage->loadImage(imageName);
    if (horizontal) {
        imageTrackX = trackX + trackLength/2 - trackImage->getWidth()/2 + handleWidth/2;
        imageTrackY = trackY - trackImage->getHeight()/2;
    }
    else {
        imageTrackX = trackX - trackImage->getWidth()/2;
        imageTrackY = trackY + trackLength/2 - trackImage->getHeight()/2 + handleHeight/2;
    }
}
void UISlider::setImageHandleIdle(string imageName) {
    handleImageIdle->loadImage(imageName);
}
void UISlider::setImageHandleActive(string imageName) {
    handleImageActive->loadImage(imageName);
}
void UISlider::setImageTrackOffset(int amount) {
    imageTrackOffset = amount;
}

void UISlider::setHandlePos(float val){
    handlePos = ofClamp(val, 0, 1);
}
void UISlider::setLockToPosThresh(float threshold) {
    lockToPosThreshold = threshold;
}
void UISlider::addLockToPos(float pos) {
    lockToPoses.push_back(pos);
}


int UISlider::getHandleX() {
    if (horizontal)
        return (int)(trackX + trackLength * handlePos);
    else
        return (int)(trackX - handleWidth/2);
}
int UISlider::getHandleY() {
    if (horizontal)
        return (int)(trackY - handleHeight/2);
    else
        return (int)(trackY + trackLength * handlePos);
}
double UISlider::getVal() { // get value (from 0 to 1)
    return handlePos;
}
double UISlider::getVal(double min, double max) { // get mapped values
    return ofMap(getVal(), 0, 1, min, max);
}

bool UISlider::overHandle(int xPos, int yPos) {
    if (!enabled)
        return false;
    
    float handleX = getHandleX();
    float handleY = getHandleY();
    
    if (xPos < handleX || xPos > handleX + handleWidth)
        return false;
    
    if (yPos < handleY || yPos > handleY + handleHeight)
        return false;
    
    return true;
}

void UISlider::mousePressed(int x, int y) {
    if (!enabled)
        return;
    
    grabbed = true;
    
    mouseOffsetX = x - getHandleX();
    mouseOffsetY = y - getHandleY();
}

void UISlider::mouseDragged(int x, int y) {
    if (!enabled) {
        grabbed = false;
        return;
    }
    
    if (!grabbed)
        return;
    
    if (horizontal) {
        int newHandleX = x - mouseOffsetX;
        
        // constrain handle x within the track
        newHandleX = ofClamp(newHandleX, trackX, trackX + trackLength - handleWidth/2);
        
        handlePos = (double)(newHandleX - trackX) / trackLength;
    }
    else { // vertical track
        int newHandleY = y - mouseOffsetY;
        
        // constrain handle y within the track
        newHandleY = ofClamp(newHandleY, trackY, trackY + trackLength - handleHeight/2);
        
        handlePos = (double)(newHandleY - trackY) / trackLength;
    }
    
    for (float lockToPos : lockToPoses) {
        if (abs(handlePos - lockToPos) < lockToPosThreshold)
            handlePos = lockToPos;
    }
    UITriggers::sliderTrigger(this);
}


void UISlider::mouseReleased() {
    grabbed = false;
}

bool UISlider::isGrabbed() {
    return grabbed;
}

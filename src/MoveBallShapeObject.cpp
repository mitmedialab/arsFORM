//
//  MoveBallShapeObject.cpp
//  cooperFORM
//
//  Created by Tangible Media Group on 10/13/14.
//
//

#include "MoveBallShapeObject.h"


MoveBallShapeObject::MoveBallShapeObject() {
    depthBuffer.allocate(100,100);
}

void MoveBallShapeObject::update() {
    float maxHeightOfEdge = 170;
    float minRadius = 5;
    float time = 2;
    if (toCenter)
        time = (float)(ofGetElapsedTimeMillis() - startAnimationTime) / toCenterAnimationTime;
    else
        time = (float)(ofGetElapsedTimeMillis() - startAnimationTime) / toCornerAnimationTime;
    
    int w = depthBuffer.getWidth();
    int h = depthBuffer.getHeight();
    
    if (time > 1) {
        maxHeightOfEdge = min(210 - (float)time*0.001, 255.0 * 3/4);
        
        if (!toCenter && !ballInCorner)
            ballInCorner = true;
        
        depthBuffer.begin();
        if (!ballInCorner)
            ofBackground(0,0);
        else {
            int x = cornerX;
            int y = cornerY;
            
            depthBuffer.begin();
            ofBackground(0,0);
            
            ofFill();
            ofSetColor(maxHeightOfEdge);
            ofCircle(x, y, minRadius+8, minRadius+8);
            
            ofSetColor((maxHeightOfEdge*3)/4);
            ofCircle(x, y, minRadius+6, minRadius+6);
            
            ofSetColor((maxHeightOfEdge*2)/4);
            ofCircle(x, y, minRadius+4, minRadius+4);
            
            ofSetColor(maxHeightOfEdge/4);
            ofCircle(x, y, minRadius+2, minRadius+2);
            
            ofSetColor(0);
            ofCircle(x, y, minRadius, minRadius);
            
            depthBuffer.end();
        }
        depthBuffer.end();
        return;
    }
    
    float toCenterTimeFraction;
    if (toCenter) {
        toCenterTimeFraction = 0;
        time = 1.0 - time; // reverse time
    }
    else
        toCenterTimeFraction = 0.6;
    
    if (time < toCenterTimeFraction) {
        float toCenterTime = 1.0 - time / toCenterTimeFraction;
        float tScaled = (1.0 - cos(pi * toCenterTime)) / 2;
        float baseRadius = minRadius + tScaled * depthBuffer.getWidth()*0.3;
        
        int w = depthBuffer.getWidth();
        int h = depthBuffer.getHeight();
        
        int toX = w/2;
        int toY = h/2;
        
        depthBuffer.begin();
        ofBackground(0,0);
        ofPushStyle();
        
        ofFill();
        
        ofSetColor(maxHeightOfEdge);
        ofCircle(toX, toY, baseRadius+8, baseRadius+8);
        
        ofSetColor((maxHeightOfEdge*3)/4);
        ofCircle(toX, toY, baseRadius+6, baseRadius+6);
        
        ofSetColor((maxHeightOfEdge*2)/4);
        ofCircle(toX, toY, baseRadius+4, baseRadius+4);
        
        ofSetColor(maxHeightOfEdge/4);
        ofCircle(toX, toY, baseRadius+2, baseRadius+2);
        
        ofSetColor(0);
        ofCircle(toX, toY, baseRadius, baseRadius);
        
        
        ofPopStyle();
        depthBuffer.end();
    }
    else {
        float toCornerTime = (time - toCenterTimeFraction) / (1.0 - toCenterTimeFraction);
        float tScaled = (1.0 - cos(pi * toCornerTime)) / 2;
        
        float baseRadius = minRadius;
        
        depthBuffer.begin();
        ofBackground(0,0);
        ofPushStyle();
        
        int w = depthBuffer.getWidth();
        int h = depthBuffer.getHeight();
        
        int fromX = w/2;
        int fromY = h/2;
        
        int toX = cornerX;
        int toY = cornerY;
        
        float x = fromX + (toX - fromX) * tScaled;
        float y = fromY + (toY - fromY) * tScaled;
        
        ofFill();
        
        ofSetColor(maxHeightOfEdge);
        ofCircle(x, y, baseRadius+8, baseRadius+8);
        
        ofSetColor((maxHeightOfEdge*3)/4);
        ofCircle(x, y, baseRadius+6, baseRadius+6);
        
        ofSetColor((maxHeightOfEdge*2)/4);
        ofCircle(x, y, baseRadius+4, baseRadius+4);
        
        ofSetColor(maxHeightOfEdge/4);
        ofCircle(x, y, baseRadius+2, baseRadius+2);
        
        ofSetColor(0);
        ofCircle(x, y, baseRadius, baseRadius);
        
        
        ofPopStyle();
        depthBuffer.end();
    }
}

void MoveBallShapeObject::renderTangibleShape(int w, int h) {
    depthBuffer.draw(0,0, w,h);
}
void MoveBallShapeObject::renderTouchscreenGraphics(int w, int h) {
    depthBuffer.draw(0,0, w,h);
}

void MoveBallShapeObject::moveBallToCorner() {
    if (ballInCorner)
        return;
    startAnimationTime = ofGetElapsedTimeMillis();
    ballInCorner = true;
    toCenter = false;
}
void MoveBallShapeObject::moveBallToCenter() {
    if (!ballInCorner)
        return;
    if (!toCenter && ofGetElapsedTimeMillis() - startAnimationTime < toCornerAnimationTime) {
        ballInCorner = false;
        toCenter = true;
        startAnimationTime = ofGetElapsedTimeMillis() - toCenterAnimationTime;
        return;
    }
    
    startAnimationTime = ofGetElapsedTimeMillis();
    ballInCorner = false;
    toCenter = true;
}
bool MoveBallShapeObject::isBallInCorner() {
    return ballInCorner;
}
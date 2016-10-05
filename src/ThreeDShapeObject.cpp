//
//  ThreeDShapeObject.cpp
//  cooperFORM
//
//  Created by Philipp Schoessler on 10/17/14.
//
//

#include "ThreeDShapeObject.h"


ThreeDShapeObject::ThreeDShapeObject() {
    
    angle = 0;
    maskThresh = 20;
    dampen = 1.3;
    idx = 0;
    numLoadedModels = 4;
    for (int i = 0; i < numLoadedModels; i++)
    {
        models.push_back(new threeDModel());
    }
    //models.at(0)->model.loadModel("models/beetle3.3ds");
    models.at(0)->model.loadModel("models/banana_01.3DS");
    models.at(0)->name = "Banana";
    models.at(0)->z = -180;
    models.at(1)->model.loadModel("models/plane_04.3DS");
    models.at(1)->name = "Plane";
    models.at(1)->z = 0;
    models.at(2)->model.loadModel("models/shark_01.3DS");
    models.at(2)->name = "Shark";
    models.at(2)->z = -100;
    models.at(3)->model.loadModel("models/teddy_03.3DS");
    models.at(3)->name = "Teddy";
    models.at(3)->z = -150;
    
    //model.loadModel("models/beetle3.3ds");
    bgImg.loadImage("test.jpg");
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    pinHeightMapImage.allocate(TOUCHSCREEN_VISIBLE_SIZE_X, TOUCHSCREEN_SIZE_Y, GL_RGBA);
    marginImage.allocate(MARGIN_X, MARGIN_X, GL_RGBA);
    projectorImage.allocate(TOUCHSCREEN_VISIBLE_SIZE_X, TOUCHSCREEN_SIZE_Y, GL_RGBA);
    
    maskedResult.allocate(RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_Y, OF_IMAGE_COLOR);
    pinHeightMapImageSmall.allocate(RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_Y, GL_RGBA);
    projectorImageSmall.allocate(RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_Y, GL_RGBA);
    
    pinHeightMapPixels.allocate(RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_Y, OF_IMAGE_COLOR);
    projectorMaskedPixels.allocate(RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_Y, OF_IMAGE_COLOR);
        
    shader.load("shaders/heightMapShader.vert", "shaders/heightMapShader.frag");
 
    currentModelName = models.at(idx)->name;
}

//--------------------------------------------------------------

void ThreeDShapeObject::update() {
    
    pinHeightMapImage.begin();
    ofPushMatrix();
    ofPushStyle();
    ofBackground(0);
    
    //GL stuff
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, TOUCHSCREEN_VISIBLE_SIZE_X, TOUCHSCREEN_SIZE_Y);
    glOrtho(0.0, TOUCHSCREEN_VISIBLE_SIZE_X, 0, TOUCHSCREEN_SIZE_Y, -1000, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    
    shader.begin();
    models.at(idx)->model.setPosition((1920 - 840) / 2, (1080)/2, models.at(idx)->z);
    models.at(idx)->model.setRotation(1, angle, axis.x, axis.y, axis.z);
    models.at(idx)->model.setScale(.3 + (.5 * scale), .3 + (.5 * scale), .3 + (.5 * scale));
    models.at(idx)->model.drawFaces();
    shader.end();
    
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    ofPopStyle();
    pinHeightMapImage.end();
    
    
    
    quat.getRotate(angle, axis);
    
    //DRAW MARGIN GRAPHIC
    marginImage.begin();    
    ofPushStyle();
    
    //draw background
    ofBackground(255);
    //draw th 3D model's wireframe
    ofPushMatrix();
    glEnable(GL_DEPTH_TEST);
    models.at(idx)->model.setPosition( MARGIN_X/2, MARGIN_X/2, 0);
    models.at(idx)->model.setRotation(1, angle, axis.x, axis.y, axis.z);
    models.at(idx)->model.setScale(0.1, 0.1, 0.1);
    //models.at(idx)->model.setScale(0.2, 0.2, 0.2);
    
    //draw wireframe in black
    ofSetColor(200);
    //glPolygonMode( GL_FRONT, GL_LINE );
    models.at(idx)->model.drawFaces();
    models.at(idx)->model.setScale(0.101, 0.101, 0.101);
    //models.at(idx)->model.setScale(0.201, 0.201, 0.201);
    ofSetColor(0);
    models.at(idx)->model.drawWireframe();
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
    ofPopStyle();
    marginImage.end();
    
    
    
    //DRAW PROJECTOR IMAGE
    projectorImage.begin();
    ofPushMatrix();
    ofPushStyle();
    ofBackground(0);
    
    //GL stuff
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, TOUCHSCREEN_VISIBLE_SIZE_X, TOUCHSCREEN_SIZE_Y);
    glOrtho(0.0, TOUCHSCREEN_VISIBLE_SIZE_X, 0, TOUCHSCREEN_SIZE_Y, -1000, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    
    //shader.begin();
    models.at(idx)->model.setPosition((1920 - 840) / 2, (1080)/2, 0);
    models.at(idx)->model.setRotation(1, angle, axis.x, axis.y, axis.z);
    models.at(idx)->model.setScale(.3 + (.5 * scale), .3 + (.5 * scale), .3 + (.5 * scale));
    models.at(idx)->model.drawFaces();
    //shader.end();
    
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    ofPopStyle();
    projectorImage.end();
    
    projectorImageSmall.begin();
    projectorImage.draw(0, 0, RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_Y);
    projectorImageSmall.end();
    
    pinHeightMapImageSmall.begin();
    pinHeightMapImage.draw(0, 0, RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_Y);
    pinHeightMapImageSmall.end();
    
    //MASK FOR PROJECTION IMAGE (so far very costly calculation)
    pinHeightMapImageSmall.readToPixels(pinHeightMapPixels);
    projectorImageSmall.readToPixels(projectorMaskedPixels);
    
    for (int i =0; i < RELIEF_PROJECTOR_SIZE_X; i++) {
        for (int j = 0; j < RELIEF_PROJECTOR_SIZE_Y; j++) {
    
                c = pinHeightMapPixels.getColor(i, j);
                p = projectorMaskedPixels.getColor(i, j);
    
                if(c.r == c.g && c.r == c.g)
                {
                    int greyVal = (c.r + c.g + c.b) / 3;
                    if ((greyVal < maskThresh))
                    {
                        projectorMaskedPixels.setColor(i, j, ofColor(0)); // if grey is smaller than treshold draw a black pixel
                    }
                }
            }
        }
    
    maskedResult.setFromPixels(projectorMaskedPixels);
    //cout<<ofGetFrameRate()<< endl;
}

//--------------------------------------------------------------

void ThreeDShapeObject::renderProjectorOverlay(int w, int h) {
    //TEXTURE RENDERING TODO
    //maskedResult.draw(310, RELIEF_PROJECTOR_SIZE_Y/2 - 10, RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_Y); //TODO find proper x y vals
    maskedResult.draw(510, 242, 1065, 814); //TODO find proper x y vals
    
    
}

//--------------------------------------------------------------

void ThreeDShapeObject::renderTangibleShape(int w, int h) {
    pinHeightMapImage.draw(0, 0, w, h);
}

//--------------------------------------------------------------

void ThreeDShapeObject::renderTouchscreenGraphics(int w, int h) {
    pinHeightMapImage.draw(0, 0, w, h);
    //projectorImage.draw(0, 0, RELIEF_PROJECTOR_SIZE_X/ 2, RELIEF_PROJECTOR_SIZE_Y/2);
    //maskedProjectorImage.draw(0, 0, RELIEF_PROJECTOR_SIZE_X/ 2, RELIEF_PROJECTOR_SIZE_Y/2);
    
}

//--------------------------------------------------------------

void ThreeDShapeObject::renderMarginGraphics(int x, int y)
{
    marginX = x;
    marginY = y;
    marginImage.draw(x, y);
}

//--------------------------------------------------------------

void ThreeDShapeObject::changeModel(int idx)
{
    if(idx > numLoadedModels)
    {
        cout << "can't change Model: only " << numLoadedModels << "are available" << endl;
        return;
    }
    this->idx = idx;
    currentModelName = models.at(idx)->name;
}

//--------------------------------------------------------------

void ThreeDShapeObject::changeModel(string direction)
{
    if(direction != "left" && direction != "right")
    {
        cout << "changeModel command unknow" << endl;
        return;
    }
    else if(direction == "left")
    {
        idx--;
        if (idx < 0)
            idx = numLoadedModels - 1;
    }
    else
    {
        idx++;
        if (idx >= numLoadedModels) {
            idx = 0;
        }
    }
    currentModelName = models.at(idx)->name;
}

//--------------------------------------------------------------

void ThreeDShapeObject::reset() {
    //cout << "reset" << endl;
    angle = 0;
    scale = 0.5;
    idx = 0;
}

//--------------------------------------------------------------

void ThreeDShapeObject::setMouseDragInfo(int x, int y, int button)
{
    if(ofDist(x, y, marginX + MARGIN_X/2, marginY +MARGIN_X/2) < MARGIN_X/2)
    {
        ofVec2f mouse(x, y);
        ofQuaternion yRot((x - oldMouse.x) * dampen, ofVec3f(0, -1, 0));
        ofQuaternion xRot((y - oldMouse.y) * dampen, ofVec3f(1, 0, 0));
        quat *= yRot*xRot;
        oldMouse = mouse;
    }
    else if(ofDist(x, y, TOUCHSCREEN_SIZE_X/2, TOUCHSCREEN_SIZE_Y/2) < 1080/2) //arcball in middle of touchscreen
    {
        ofVec2f mouse(x, y);
        ofQuaternion yRot((x - oldMouse.x) * dampen, ofVec3f(0, -1, 0));
        ofQuaternion xRot((y - oldMouse.y) * dampen, ofVec3f(1, 0, 0));
        quat *= yRot*xRot;
        oldMouse = mouse;
    }
}

//--------------------------------------------------------------

void ThreeDShapeObject::setMousePressedInfo(int x, int y)
{
    oldMouse = ofVec2f(x,y); //prevents popping
}

//--------------------------------------------------------------

void ThreeDShapeObject::setScale(float uniformScaleVal)
{
    scale = uniformScaleVal;
}

//--------------------------------------------------------------

string ThreeDShapeObject::getCurrentModelName()
{
    return currentModelName;
}

//--------------------------------------------------------------


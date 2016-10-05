//
//  UIButton.cpp
//  cooperFORM
//
//  Created by Tangible Media Group on 9/23/14.
//
//

#include "UIButton.h"
#include "UITriggers.h"
//#include "ofMain.h"


// temporary constructor
UIButton::UIButton() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    name = "";
    buttonImageIdle = new ofImage();
    buttonImageActive = new ofImage();
    buttonImageSelected = new ofImage();
}

UIButton::UIButton(string name, int xPos, int yPos, int w, int h) {
    this->name = name;
    x = xPos;
    y = yPos;
    width = w;
    height = h;
    buttonImageIdle = new ofImage();
    buttonImageActive = new ofImage();
    buttonImageSelected = new ofImage();
}

string UIButton::getName() {
    return name;
}

void UIButton::draw() {
    if (!visible)
        return;
    
    if (buttonImageActive->isAllocated()) {
        if (isSelected())
            buttonImageSelected->draw(x,y, width,height);
        else if (isPressed())
            buttonImageActive->draw(x,y, width,height);
        else
            buttonImageIdle->draw(x,y, width,height);
    }
    else {
        ofPushStyle();
        if (isSelected())
            ofSetColor(ofColor(0,255,0));
        else if (isPressed())
            ofSetColor(ofColor(255,0,0));
        else
            ofSetColor(ofColor(0,0,255));
        
        ofRect(x,y, width, height);
        ofPopStyle();
    }
}

void UIButton::enable() {
    enabled = true;
}
void UIButton::disable() {
    enabled = false;
}
void UIButton::show() {
    visible = true;
}
void UIButton::hide() {
    visible = false;
}

void UIButton::setImageIdle(string imageName) {
    buttonImageIdle->loadImage(imageName);
}
void UIButton::setImageActive(string imageName) {
    buttonImageActive->loadImage(imageName);
}
void UIButton::setImageSelected(string imageName) {
    buttonImageSelected->loadImage(imageName);
}

void UIButton::setX(int x) {
    this->x = x;
}
void UIButton::setY(int y) {
    this->y = y;
}

// given x and y coordinates
// return whether it is within this button
bool UIButton::overButton(int xPos, int yPos) {
    if (!enabled)
        return false;
    
    if (xPos < x || xPos > x+width)
        return false;
    if (yPos < y || yPos > y+height)
        return false;
    
    return true;
}

void UIButton::mousePressed() {
    if (!enabled)
        return;
    
    pressed = true;
}
void UIButton::mouseReleased() {
    pressed = false;
    
    if (!enabled)
        return;
    
    if (!selected)
        UITriggers::buttonTrigger(this);
    else
        UITriggers::buttonUnselect(this);
}

// triggered when the mouse has left the button,
// but didn't release
void UIButton::mouseLeft() {
    pressed = false;
}
void UIButton::select() {
    selected = true;
}
void UIButton::unselect() {
    selected = false;
}
bool UIButton::isPressed() {
    return pressed;
}
bool UIButton::isSelected() {
    return selected;
}
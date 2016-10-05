//
//  UIText.cpp
//  cooperFORM
//
//  Created by Tangible Media Group on 10/9/14.
//
//

#include "UINum.h"

UINum::UINum(string text, string name, int size, int xPos, int yPos) {
    this->text = text;
    
    this->name = name;
    
    this->color = ofColor(255,0,0);
    
    
    //layout.loadFont("helvetica-neue-medium-1361522099.ttf", size);
    layout.loadFont("Math/assets/ExcelsiorLTStd-Italic.otf", size);
    layout.setLineSpacing(1.2);
    
    x = xPos;
    y = yPos;
}

void UINum::draw() {
    ofPushStyle();
    ofSetColor(color);
    if (visible)
        layout.drawString(text, x,y);
    ofPopStyle();
}

string UINum::getName() {
    return name;
}

void UINum::setWidth(int width) {
    layout.setLineLength(width);
}

void UINum::setAlignment(string alignment) {
    if (alignment == "left")
        layout.setAlignment(FTGL_ALIGN_LEFT);
    else if (alignment == "right")
        layout.setAlignment(FTGL_ALIGN_RIGHT);
    else if (alignment == "center")
        layout.setAlignment(FTGL_ALIGN_CENTER);
    else if (alignment == "justify")
        layout.setAlignment(FTGL_ALIGN_JUSTIFY);
}

void UINum::setColor(ofColor color) {
    this->color = color;
}

void UINum::setNum(string text) {
    this->text = text;
}

void UINum::setX(float x) {
    this->x = x;
}

void UINum::setY(float y) {
    this->y = y;
}

void UINum::setSize(int size) {
    //layout.setSize(size);
    ofxFTGLTextAlignment align = layout.getAlignment();
    float lineLength = layout.getLineLength();
    layout.loadFont("Math/assets/ExcelsiorLTStd-Italic.otf", size);
    layout.setAlignment(align);
    layout.setLineSpacing(1.2);
    layout.setLineLength(lineLength);
}

void UINum::show() {
    visible = true;
}
void UINum::hide() {
    visible = false;
}

bool UINum::showing() {
    return visible;
}

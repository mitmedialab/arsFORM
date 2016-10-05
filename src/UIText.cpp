//
//  UIText.cpp
//  cooperFORM
//
//  Created by Tangible Media Group on 10/9/14.
//
//

#include "UIText.h"

UIText::UIText(string text, string name, int size, int xPos, int yPos) {
    this->text = text;
    
    this->name = name;
    
    this->color = ofColor(0);
    
    layout.loadFont("helvetica-neue-medium-1361522099.ttf", size);
    layout.setLineSpacing(1.2);
    
    x = xPos;
    y = yPos;
}

void UIText::draw() {
    ofPushStyle();
    ofSetColor(color);
    if (visible)
        layout.drawString(text, x,y);
    ofPopStyle();
}

string UIText::getName() {
    return name;
}

void UIText::setWidth(int width) {
    layout.setLineLength(width);
}

void UIText::setAlignment(string alignment) {
    if (alignment == "left")
        layout.setAlignment(FTGL_ALIGN_LEFT);
    else if (alignment == "right")
        layout.setAlignment(FTGL_ALIGN_RIGHT);
    else if (alignment == "center")
        layout.setAlignment(FTGL_ALIGN_CENTER);
    else if (alignment == "justify")
        layout.setAlignment(FTGL_ALIGN_JUSTIFY);
}

void UIText::setColor(ofColor color) {
    this->color = color;
}

void UIText::setText(string text) {
   this->text = text;
}

float UIText::getStrWidth(string text) {
    return layout.getStringBoundingBox(text,0,0).getWidth();
}

void UIText::setX(int x) {
    this->x = x;
}
void UIText::setY(int y) {
    this->y = y;
}

int UIText::getX() {
    return x;
}

void UIText::show() {
    visible = true;
}
void UIText::hide() {
    visible = false;
}

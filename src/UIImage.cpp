//
//  UIImage.cpp
//  cooperFORM
//
//  Created by Tangible Media Group on 9/29/14.
//
//

#include "UIImage.h"

UIImage::UIImage(string imagePath, int x, int y) {
    image = new ofImage();
    image->loadImage(imagePath);
    this->x = x;
    this->y = y;
}
UIImage::UIImage(ofImage *image, int x, int y) {
    this->image = image;
    this->x = x;
    this->y = y;
}

UIImage::UIImage(ofImage *image, string name, int x, int y) {
    this->image = image;
    this->name=name;
    this->x = x;
    this->y = y;
}

void UIImage::draw() {
    if (visible) {
        image->draw(x,y, image->getWidth(), image->getHeight());
        if (hasCaption)
            captionText->draw();
    }
}
void UIImage::setName(string name) {
    this->name = name;
}
string UIImage::getName() {
    return name;
}

int UIImage::getX() {
    return x;
}
int UIImage::getY() {
    return y;
}

void UIImage::setX(int x) {
    this->x = x;
}
void UIImage::setY(int y) {
    this->y = y;
}

void UIImage::show() {
    visible = true;
}
void UIImage::hide() {
    visible = false;
}

void UIImage::setCaption(string text, int size, int width) {
    captionText = new UIText(text, text, size, x + image->getWidth()/2 - width/2, y + image->getHeight() + 25);
    captionText->setWidth(width);
    captionText->setAlignment("center");
    hasCaption = true;
}

UIText* UIImage::getCaption() {
    return captionText;
}

void UIImage::setImage(ofImage *image) {
    this->image = image;
}
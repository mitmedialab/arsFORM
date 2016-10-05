//
//  UIButton.h
//  cooperFORM
//
//  Created by Tangible Media Group on 9/23/14.
//
//

#ifndef __cooperFORM__UIButton__
#define __cooperFORM__UIButton__

#include "UIElement.h"
#include "ofImage.h"

using namespace std;

class UIButton : public UIElement {
public:
    UIButton();
    UIButton(string name, int xPos, int yPos, int w, int h);
    
    string getName();
    void draw();
    
    void enable();
    void disable();
    
    void show();
    void hide();
    
    void setImageIdle(string imageName);
    void setImageActive(string imageName);
    void setImageSelected(string imageName);
    
    void setX(int x);
    void setY(int y);
    
    // will tell you whether
    // an x,y coordinate is inside the button
    bool overButton(int xPos, int yPos);
    
    void mousePressed();
    void mouseReleased();
    
    // triggered when the mouse has left the button,
    // but didn't release
    void mouseLeft();
    
    void select();
    void unselect();
    
    
    // whether or not mouse is pressed on this button
    bool isPressed();
    bool isSelected();
    
private:
    string name;
    
    bool enabled = true;
    
    int x, y, width, height;
    
    bool pressed = false;
    bool selected = false;
    
    ofImage *buttonImageActive;
    ofImage *buttonImageIdle;
    ofImage *buttonImageSelected;
    
    bool visible = true;
};

#endif /* defined(__cooperFORM__UIButton__) */

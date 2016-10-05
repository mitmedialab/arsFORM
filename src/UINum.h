//
//  UIText.h
//  cooperFORM
//
//  Created by Tangible Media Group on 10/9/14.
//
//

#ifndef __cooperFORM__UINum__
#define __cooperFORM__UINum__

#include "Constants.h"
#include "UIElement.h"
#include "ofMain.h"
#include "ofxFTGL.h"

using namespace std;

class UINum  : public UIElement {
public:
    UINum() { };
    UINum(string text, string name, int size, int xPos, int yPos);
    
    void draw();
    
    string getName();
    
    void setWidth(int width);
    void setAlignment(string alignment);
    void setColor(ofColor color);
    void setNum(string text);
    void setX(float x);
    void setY(float y);
    void setSize(int size);
    
    void enable() { };
    void disable() { };
    
    void show();
    void hide();
    
    bool showing();
    
private:
    string text;
    string name;
    ofxFTGLSimpleLayout layout;
    int x, y;
    ofColor color;
    bool visible = true;
};

#endif /* defined(__cooperFORM__UIText__) */

//
//  UIImage.h
//  cooperFORM
//
//  Created by Tangible Media Group on 9/29/14.
//
//

#ifndef __cooperFORM__UIImage__
#define __cooperFORM__UIImage__

#include "UIElement.h"
#include "ofMain.h"
#include "UIText.h"

class UIImage : public UIElement {
public:
    UIImage(string imagePath, int x, int y);
    UIImage(ofImage *image, int x, int y);
    UIImage(ofImage *image, string name, int x, int y);
    
    void draw();
    string getName();
    void setName(string name);
    
    int getX();
    int getY();
    
    void setX(int x);
    void setY(int y);
    
    // inherited from UIElement
    // does nothing since UIImage is not interactive
    void enable() { };
    void disable() { };
    
    void show();
    void hide();
    
    void setCaption(string text, int size, int width);
    
    UIText* getCaption();
    
    void setImage(ofImage* image);
private:
    string name;
    ofImage *image;
    UIText *captionText;
    int x, y;
    bool visible = true;
    bool hasCaption = false;
};

#endif /* defined(__cooperFORM__UIImage__) */

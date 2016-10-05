//
//  UISlider.h
//  cooperFORM
//
//  Created by Tangible Media Group on 9/26/14.
//
//

#ifndef __cooperFORM__UISlider__
#define __cooperFORM__UISlider__

#include "UIElement.h"
#include "ofMain.h"

using namespace std;

//        handle
//     track |
//       |   v
//       v  ___
// ---------| |--
//          ---

class UISlider : public UIElement {
public:
    UISlider();
    UISlider(string name, bool horizontal, int trackX, int trackY, int trackLength, int handleWidth, int handleHeight);
    
    string getName();
    void draw();
    
    void enable();
    void disable();
    
    void show();
    void hide();
    
    void setImageTrack(string imageName);
    void setImageHandleIdle(string imageName);
    void setImageHandleActive(string imageName);
    void setImageTrackOffset(int amount);
    void setHandlePos(float val); //should be between 0 and 1
    
    // closest handle will get to a "lock to pos" before getting snapped there
    // threshold should be between 0 and 1
    void setLockToPosThresh(float threshold);
    // add a position along the track at which the handle will get snapped to when it's close
    // between 0 and 1
    void addLockToPos(float pos);
    
    int getHandleX();
    int getHandleY();
    double getVal();
    double getVal(double min, double max);

    // will tell you whether
    // an x,y coordinate is inside the button
    bool overHandle(int xPos, int yPos);
    
    void mousePressed(int x, int y);
    void mouseDragged(int x, int y);
    void mouseReleased();

    bool isGrabbed();
    
private:
    string name;
    
    ofImage *trackImage;
    ofImage *handleImageIdle;
    ofImage *handleImageActive;
    
    bool enabled = true;
    
    int trackX, trackY;
    int imageTrackX, imageTrackY;
    int imageTrackOffset = 0;
    
    // how far along the track the handle is
    // value is from 0 to 1
    double handlePos;
    
    int trackLength;
    int handleWidth, handleHeight;
    
    // true for horizontal
    // false for vertical
    bool horizontal;
    
    bool grabbed = false;
    int mouseOffsetX, mouseOffsetY;
    
    bool visible = true;
    
    vector<float> lockToPoses;
    float lockToPosThreshold = 0.1;
};

#endif /* defined(__cooperFORM__UISlider__) */

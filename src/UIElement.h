//
//  UIElement.h
//  cooperFORM
//
//  Created by Jared Counts on 10/3/14.
//
//

#ifndef cooperFORM_UIElement_h
#define cooperFORM_UIElement_h
#include <iostream>

using namespace std;

class UIElement {
public:
    virtual void draw() = 0;
    
    virtual string getName() = 0;
    
    virtual void enable() = 0;
    virtual void disable() = 0;
    
    virtual void show() = 0;
    virtual void hide() = 0;
};

#endif

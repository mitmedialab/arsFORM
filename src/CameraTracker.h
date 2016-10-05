//
//  CameraTracker.h
//  cooperFORM
//
//  Created by Jared Counts on 9/22/14.
//
//

#ifndef __cooperFORM__CameraTracker__
#define __cooperFORM__CameraTracker__

#include <iostream>
#include "ofMain.h"


class CameraTracker {
    
public:
    ~CameraTracker();
    void setup();
    void drawCameraFeed(int id, int x, int y, int w, int h);
    
private:
    vector<ofVideoGrabber> grabbers;
};

#endif /* defined(__cooperFORM__CameraTracker__) */

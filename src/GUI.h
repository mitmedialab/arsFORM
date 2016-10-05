//
//  GUI.h
//  cooperFORM
//
//  Created by Tangible Media Group on 10/10/14.
//
//

#ifndef __cooperFORM__GUI__
#define __cooperFORM__GUI__

#include "ReliefApplication.h"
#include "UIHandler.h"
#include "UITriggers.h"

class GUI {
public:
    static void setupUI(UIHandler* uiHandler);
private:
    static void setupRightSidebar(UIHandler* uiHandler,  const int rightSidebarWidth);
    static void setupLeftSidebar(UIHandler* uiHandler, const int leftSidebarWidth);
    static void setupInfoBar(UIHandler* uiHandler, const int leftSidebarWidth);
    static void setupTeleBar(UIHandler* uiHandler, const int leftSidebarWidth);
    static void setupWaveBar(UIHandler* uiHandler, const int leftSidebarWidth);
    static void setupCityBar(UIHandler* uiHandler, const int leftSidebarWidth);
    static void setupThreeDBar(UIHandler* uiHandler, const int leftSidebarWidth);
    static void setupMathBar(UIHandler* uiHandler, const int leftSidebarWidth);
};

#endif /* defined(__cooperFORM__GUI__) */
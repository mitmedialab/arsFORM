//
//  UITriggers.h
//  cooperFORM
//
//  Created by Tangible Media Group on 9/24/14.
//
//

#ifndef __cooperFORM__UITriggers__
#define __cooperFORM__UITriggers__

#include "UIHandler.h"
#include "UIButton.h"
#include "ReliefApplication.h"

class UITriggers {
public:

    
    // the button trigger event
    static void buttonTrigger(UIButton *button);
    
    // the button trigger event for unselecting a button
    static void buttonUnselect(UIButton *button);
    
    // slider trigger event
    // triggered when the slider handle changes position
    static void sliderTrigger(UISlider *slider);
    
    static void setIdle();
    
    // be sure to register relief application
    // so we can do stuff with it after events are triggered
    static void registerReliefApplication(ReliefApplication* relief);
    
private:
    // reference to the relief application
    // so we can actually do stuff when triggered
    static ReliefApplication *reliefApplication;
    
    // reference to UI handler for UI-wide operations
    static UIHandler *uiHandler;
    
    // mode switching can be done at this much time apart
    // (to prevent rapid mode switching);
    static int modeSwitchTimeLimit;
    
    static long lastModeSwitched;
};

#endif /* defined(__cooperFORM__UITriggers__) */

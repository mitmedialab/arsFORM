//
//  UITriggers.cpp
//  cooperFORM
//
//  Created by Jared Counts on 9/24/14.
//
//

// All of the table-specific functions triggered by UI events


#include "UITriggers.h"

void UITriggers::buttonTrigger(UIButton *button) {
    UIHandler *ui = uiHandler;
    string name = button->getName();
    if (ofGetElapsedTimeMillis() - UITriggers::lastModeSwitched > UITriggers::modeSwitchTimeLimit) {
        if (name == "telepresence") {
            reliefApplication->setMode("telepresence");
            uiHandler->select(button);
            uiHandler->showUIGroup("telepresence");
            uiHandler->hideUIGroup("wavy");
            uiHandler->hideUIGroup("3D");
            uiHandler->hideUIGroup("city");
            uiHandler->hideUIGroup("math");
            uiHandler->hideUIGroup("info");
            UITriggers::lastModeSwitched = ofGetElapsedTimeMillis();
            reliefApplication->showInfo = false;
        }
        else if (name == "wavy") {
            reliefApplication->setMode("wavy");
            uiHandler->select(button);
            uiHandler->hideUIGroup("telepresence");
            uiHandler->showUIGroup("wavy");
            uiHandler->hideUIGroup("3D");
            uiHandler->hideUIGroup("city");
            uiHandler->hideUIGroup("math");
            uiHandler->hideUIGroup("info");
            UITriggers::lastModeSwitched = ofGetElapsedTimeMillis();
            reliefApplication->showInfo = false;
        }
        else if (name == "3D") {
            reliefApplication->setMode("3D");
            uiHandler->select(button);
            uiHandler->hideUIGroup("telepresence");
            uiHandler->hideUIGroup("wavy");
            uiHandler->showUIGroup("3D");
            uiHandler->hideUIGroup("city");
            uiHandler->hideUIGroup("math");
            uiHandler->hideUIGroup("info");
            UITriggers::lastModeSwitched = ofGetElapsedTimeMillis();
            reliefApplication->showInfo = false;
        }
        else if (name == "city") {
            reliefApplication->setMode("city");
            uiHandler->select(button);
            uiHandler->hideUIGroup("telepresence");
            uiHandler->hideUIGroup("wavy");
            uiHandler->showUIGroup("city");
            uiHandler->hideUIGroup("math");
            uiHandler->hideUIGroup("info");
            UITriggers::lastModeSwitched = ofGetElapsedTimeMillis();
            reliefApplication->showInfo = false;
        }
        else if (name == "math") {
            reliefApplication->setMode("math");
            uiHandler->select(button);
            uiHandler->hideUIGroup("telepresence");
            uiHandler->hideUIGroup("wavy");
            uiHandler->hideUIGroup("3D");
            uiHandler->hideUIGroup("city");
            uiHandler->showUIGroup("math");
            uiHandler->hideUIGroup("info");
            UITriggers::lastModeSwitched = ofGetElapsedTimeMillis();
            reliefApplication->showInfo = false;
        }
    }
    if (name == "modelSelectLeft")
    {
        reliefApplication->threeDShapeObject->changeModel("left");
        //cout << "modelSelectLeft" <<endl;
    }
    else if (name == "modelSelectRight")
    {
        reliefApplication->threeDShapeObject->changeModel("right");
        //cout << "modelSelectRight" <<endl;
    }
    else if (name == "equationSelectButton1")
    {
        reliefApplication->mathShapeObject->chooseFunction(0);
        uiHandler->select(button);
        
    }
    else if (name == "equationSelectButton2")
    {
        reliefApplication->mathShapeObject->chooseFunction(1);
        uiHandler->select(button);
    }
    else if (name == "equationSelectButton3")
    {
        reliefApplication->mathShapeObject->chooseFunction(2);
        uiHandler->select(button);
    }
    else if (name == "equationSelectButton4")
    {
        reliefApplication->mathShapeObject->chooseFunction(3);
        uiHandler->select(button);
    }
    else if (name == "equationSelectButton5")
    {
        reliefApplication->mathShapeObject->chooseFunction(4);
        uiHandler->select(button);
    }
    else if (name == "modifyVal1Up")
    {
        reliefApplication->mathShapeObject->modifyVal1Up();
    }
    else if (name == "modifyVal1Down")
    {
        reliefApplication->mathShapeObject->modifyVal1Down();
    }
    else if (name == "modifyVal2Up")
    {
        reliefApplication->mathShapeObject->modifyVal2Up();
    }
    else if (name == "modifyVal2Down")
    {
        reliefApplication->mathShapeObject->modifyVal2Down();
    }
    else if (name == "citySelectButton1")
    {
        reliefApplication->cityShapeObject->chooseCity(0);
        uiHandler->select(button);
        
    }
    else if (name == "citySelectButton2")
    {
        reliefApplication->cityShapeObject->chooseCity(1);
        uiHandler->select(button);
    }
    else if (name == "citySelectButton3")
    {
        reliefApplication->cityShapeObject->chooseCity(2);
        uiHandler->select(button);
    }
    else if (name == "citySelectButton4")
    {
        reliefApplication->cityShapeObject->chooseCity(3);
        uiHandler->select(button);
    }
}
void UITriggers::buttonUnselect(UIButton *button) {
    string name = button->getName();
    if (name == "telepresence"  || name == "wavy" || name == "city" || name == "3D" || name == "math") {
//      // disabled info screen
//        uiHandler->unselect(button);
//        uiHandler->hideUIGroup(name);
//        uiHandler->showUIGroup("info");
    }
}

void UITriggers::setIdle() {
    string currentMode = reliefApplication->currentMode;
    cout << currentMode << endl;
    UIButton *currentButton = uiHandler->getButton(currentMode);
    uiHandler->unselect(currentButton);
    
    uiHandler->hideUIGroup(currentMode);
    uiHandler->showUIGroup("info");
}

void UITriggers::sliderTrigger(UISlider *slider) {
    string name = slider->getName();
    if (name == "sliderScale") {
        reliefApplication->threeDShapeObject->setScale(slider->getVal());
    }
    if (name == "sliderPosition") {
        reliefApplication->cityShapeObject->setMovPosition(slider->getVal());
    }
    
}

// initialize relevant static variables
ReliefApplication* UITriggers::reliefApplication;
UIHandler* UITriggers::uiHandler;
int UITriggers::modeSwitchTimeLimit;
long UITriggers::lastModeSwitched;

void UITriggers::registerReliefApplication(ReliefApplication* relief) {
    UITriggers::reliefApplication = relief;
    UITriggers::uiHandler = relief->uiHandler;
    
    // initialize these too
    // since C++ spec won't let us initialize static members in-line the .h file
    UITriggers::modeSwitchTimeLimit = 300;
    UITriggers::lastModeSwitched = 0;
}
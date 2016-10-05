//
//  UIHandler.cpp
//  cooperFORM
//
//  Created by Jared Counts on 9/23/14.
//
//

#include "UIHandler.h"

UIHandler::UIHandler() {
    buttons = vector<UIButton*>();
    sliders = vector<UISlider*>();
    texts = vector<UIText*>();
    images = vector<UIImage*>();
    nums = vector<UINum*>();
    buttonGroups = vector< vector<UIButton*>* >();
}

void UIHandler::draw() {
    for (UIButton *button : buttons)
        button->draw();
    for (UISlider * slider : sliders)
        slider->draw();
    for (UIImage *image : images)
        image->draw();
    for (UIText *text : texts)
        text->draw();
    for (UINum *num : nums)
        num->draw();
    
    ofSetColor(ofColor(255));
}

void UIHandler::addButton(UIButton *button) {
    buttons.push_back(button);
}

void UIHandler::addButtonGroup(vector<UIButton*>* group) {
    buttonGroups.push_back(group);
}

void UIHandler::addSlider(UISlider *slider) {
    sliders.push_back(slider);
}

void UIHandler::addImage(UIImage* image) {
    images.push_back(image);
}

void UIHandler::addText(UIText* text) {
    texts.push_back(text);
}

void UIHandler::addNum(UINum* num) {
    nums.push_back(num);
}


void UIHandler::addUIGroup(vector<UIElement*> uiGroup, string name) {
    uiGroups[name] = uiGroup;
}

void UIHandler::showUIGroup(string groupName) {
    map< string, vector<UIElement*> >::iterator groupIt = uiGroups.find(groupName);
    if (groupIt == uiGroups.end())
        return;
    
    vector<UIElement*> group = groupIt->second;
    for (UIElement* element : group) {
        element->enable();
        element->show();
    }
}
void UIHandler::hideUIGroup(string groupName) {
    map< string, vector<UIElement*> >::iterator groupIt = uiGroups.find(groupName);
    if (groupIt == uiGroups.end())
        return;
    
    vector<UIElement*> group = groupIt->second;
    for (UIElement* element : group) {
        element->disable();
        element->hide();
    }
}

void UIHandler::mousePressed(int x, int y) {
    // look for buttons under this mouse position
    for (UIButton *button : buttons) {
        if (button->overButton(x, y))
            button->mousePressed();
    }
    for (UISlider *slider : sliders) {
        if (slider->overHandle(x, y)) {
            slider->mousePressed(x,y);
        }
    }
}

void UIHandler::mouseReleased(int x, int y) {
    // look for buttons under this mouse position
    for (UIButton *button : buttons) {
        if (button->isPressed()) {
            // check first if the mouse is still over the button
            // to see which event trigger to use
            if (button->overButton(x,y))
                button->mouseReleased();
            else
                button->mouseLeft();
        }
    }
    for (UISlider *slider : sliders) {
        if (slider->isGrabbed())
            slider->mouseReleased();
    }
}

void UIHandler::mouseDragged(int x, int y) {
    for (UIButton *button : buttons) {
        if (button->isPressed()) {
            // check to see if the mouse pressed a button but left
            if (!button->overButton(x,y))
                button->mouseLeft();
        }
    }
    for (UISlider *slider : sliders) {
        if (slider->isGrabbed()) {
            slider->mouseDragged(x,y);
        }
    }
}

void UIHandler::unselect(UIButton *button) {
    // unselect the button
    button->unselect();
}

void UIHandler::select(UIButton *button) {
    // find out which groups it's in
    for (vector<UIButton*>* buttonGroup : buttonGroups) {
        
        std::vector<UIButton*>::iterator it;
        it = find(buttonGroup->begin(), buttonGroup->end(), button);
        if (it != buttonGroup->end()) {
            
            // found the button!
            // now deselect every other button in this group
            for (UIButton *other : *buttonGroup) {
                if (other != button)
                    other->unselect();
            }
            
        }
        // look for more groups this button might belong in
    }
    
    // finally select the button
    button->select();
}

UIButton* UIHandler::getButton(string name) {
    for (UIButton *button : buttons) {
        if (button->getName() == name)
            return button;
    }
    return NULL;
}

UISlider* UIHandler::getSlider(string name) {
    for (UISlider *slider : sliders) {
        if (slider->getName() == name)
            return slider;
    }
    return NULL;
}

UIText* UIHandler::getText(string name) {
    for (UIText *text : texts) {
        if (text->getName() == name)
            return text;
    }
    return NULL;
}

UINum* UIHandler::getNum(string name) {
    for (UINum *num : nums) {
        if (num->getName() == name)
            return num;
    }
    return NULL;
}

UIImage* UIHandler::getImage(string name) {
    for (UIImage *image : images) {
        if (image->getName() == name)
            return image;
    }
    return NULL;
}
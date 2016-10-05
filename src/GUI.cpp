//
//  GUI.cpp
//  cooperFORM
//
//  Created by Tangible Media Group on 10/10/14.
//
//

// Constructs the GUI

#include "GUI.h"
void GUI::setupRightSidebar(UIHandler *uiHandler, const int rightSidebarWidth) {
    // Right sidebar stuff:
    
    const int modeButtonWidth  = 372;
    const int modeButtonHeight = 222;
    
    const int modeButtonX = 1920 - rightSidebarWidth + rightSidebarWidth/2 - modeButtonWidth/2;
    const int modeButtonVertSpaceBetween = 50;
    const int modeButtonsTotalHeight = 4 * modeButtonHeight + 3 * modeButtonVertSpaceBetween;
    const int modeButtonStartY = 1080 / 2 - modeButtonsTotalHeight / 2;
    
    ofImage* divider = new ofImage();
    divider->loadImage("divider.png");
    
    const int dividerWidth = divider->getWidth();
    const int dividerHeight = divider->getHeight();
    const int dividerX = 1920 - rightSidebarWidth + rightSidebarWidth/2 - dividerWidth/2;
    
    
    // initialize the new buttons
    // UIButton name = UIButton("name", x,y, w,h)
    UIButton* telepresenceModeButton
    = new UIButton("telepresence",
                   modeButtonX, modeButtonStartY,
                   modeButtonWidth,modeButtonHeight);
    telepresenceModeButton->setImageIdle("teleo.png");
    telepresenceModeButton->setImageActive("teleo-active.png");
    telepresenceModeButton->setImageSelected("teleo-selected.png");
    
    UIImage* divider1 = new UIImage(divider,
                                    dividerX, modeButtonStartY + modeButtonHeight + 0.5*modeButtonVertSpaceBetween - dividerHeight/2);
    
    UIButton* wavyModeButton
    = new UIButton("wavy",
                   modeButtonX, modeButtonStartY + modeButtonVertSpaceBetween + modeButtonHeight,
                   modeButtonWidth,modeButtonHeight);
    wavyModeButton->setImageIdle("wave.png");
    wavyModeButton->setImageActive("wave-active.png");
    wavyModeButton->setImageSelected("wave-selected.png");
    UIImage* divider2 = new UIImage(divider,
                                    dividerX, modeButtonStartY + 2*modeButtonHeight + 1.5*modeButtonVertSpaceBetween - dividerHeight/2);
    
    UIButton* cityModeButton
    = new UIButton("city",
                   modeButtonX, modeButtonStartY + 2*modeButtonVertSpaceBetween + 2*modeButtonHeight,
                   modeButtonWidth,modeButtonHeight);
    cityModeButton->setImageIdle("city.png");
    cityModeButton->setImageActive("city-active.png");
    cityModeButton->setImageSelected("city-selected.png");
    UIImage* divider3 = new UIImage(divider,
                                    dividerX, modeButtonStartY + 3*modeButtonHeight + 2.5*modeButtonVertSpaceBetween - dividerHeight/2);
//    UIButton* threeDModeButton
//    = new UIButton("3D",
//                   modeButtonX, modeButtonStartY + 2*modeButtonVertSpaceBetween + 2*modeButtonHeight,
//                   modeButtonWidth,modeButtonHeight);
//    threeDModeButton->setImageIdle("3dm.png");
//    threeDModeButton->setImageActive("3dm-active.png");
//    threeDModeButton->setImageSelected("3dm-selected.png");
//    UIImage* divider3 = new UIImage(divider,
//                                    dividerX, modeButtonStartY + 3*modeButtonHeight + 2.5*modeButtonVertSpaceBetween - dividerHeight/2);
    
    
    UIButton* mathModeButton
    = new UIButton("math",
                   modeButtonX, modeButtonStartY + 3*modeButtonVertSpaceBetween + 3*modeButtonHeight,
                   modeButtonWidth,modeButtonHeight);
    mathModeButton->setImageIdle("math.png");
    mathModeButton->setImageActive("math-active.png");
    mathModeButton->setImageSelected("math-selected.png");
    
    // add buttons to the handler
    uiHandler->addButton(telepresenceModeButton);
    uiHandler->addImage(divider1);
    uiHandler->addButton(wavyModeButton);
    uiHandler->addImage(divider2);
    uiHandler->addButton(cityModeButton);
    uiHandler->addImage(divider3);
    uiHandler->addButton(mathModeButton);
    
    // add these buttons to a group
    // for the "select" and "unselect" functionality
    vector<UIButton*>* mainButtonGroup = new vector<UIButton*>();
    mainButtonGroup->push_back(telepresenceModeButton);
    mainButtonGroup->push_back(wavyModeButton);
    mainButtonGroup->push_back(cityModeButton);
    mainButtonGroup->push_back(mathModeButton);
    uiHandler->addButtonGroup(mainButtonGroup);
    
    UITriggers::buttonTrigger(telepresenceModeButton);
}

//--------------------------------------------------------------

void GUI::setupLeftSidebar(UIHandler *uiHandler, const int leftSidebarWidth) {
    setupInfoBar(uiHandler, leftSidebarWidth);
    setupTeleBar(uiHandler, leftSidebarWidth);
    setupCityBar(uiHandler, leftSidebarWidth);
    //setupThreeDBar(uiHandler, leftSidebarWidth);
    setupWaveBar(uiHandler, leftSidebarWidth);
    setupMathBar(uiHandler, leftSidebarWidth);
}

//--------------------------------------------------------------

void GUI::setupInfoBar(UIHandler *uiHandler, const int leftSidebarWidth) {
    // left sidebar stuff:
    // info screen
    // inFORM logo
    
    ofImage* inFORMLogoImg = new ofImage();
    inFORMLogoImg->loadImage("inform-logo.png");
    
    const int informLogoWidth = inFORMLogoImg->getWidth();
    const int informLogoHeight = inFORMLogoImg->getHeight();
    const int informLogoX = leftSidebarWidth/2 - informLogoWidth/2;
    const int informLogoY = informLogoX;
    
    UIImage *inFORMLogo = new UIImage(inFORMLogoImg, informLogoX, informLogoY);
    
    
    // creator text
    const int creatorTextWidth = 270;
    const int creatorTextX = leftSidebarWidth/2 - creatorTextWidth/2;
    const int creatorTextY = informLogoY + informLogoHeight + 25;
    const int creatorTextSize = 9;
    const string creatorTextStr = "Daniel Leithinger, Sean Follmer, Alex Olwal, Akimitsu Hogge, Hiroshi Ishii";
    
    UIText* creatorText = new UIText(creatorTextStr, "creators", creatorTextSize, creatorTextX, creatorTextY);
    creatorText->setAlignment("left");
    creatorText->setWidth(creatorTextWidth);
    creatorText->setColor(ofColor(175,175,175));
    
    // inFORM description
    const int descTextWidth = 300;
    const int descTextX = leftSidebarWidth/2 - descTextWidth/2;
    const int descTextY = creatorTextY + 100;
    const int descTextSize = 10;
    const string descTextStr = "The inFORM is a Dynamic Shape Display that can render 3D content physically, so users can interact with digital information in a tangible way while also interacting with the physical world around it.";
    
    UIText* inFORMText = new UIText(descTextStr, "inFORM description", descTextSize, descTextX, descTextY);
    inFORMText->setAlignment("left");
    inFORMText->setWidth(descTextWidth);
    inFORMText->setColor(ofColor(35,35,35));
    
    // divider
    ofImage* dividerImg = new ofImage();
    dividerImg->loadImage("divider.png");
    
    const int dividerWidth = dividerImg->getWidth();
    const int dividerHeight = dividerImg->getHeight();
    const int dividerX = leftSidebarWidth/2 - dividerWidth/2;
    const int dividerY = descTextY + 210;
    
    UIImage* divider = new UIImage(dividerImg, dividerX, dividerY);
    
    // tmg logo
    ofImage* tmgLogImg = new ofImage();
    tmgLogImg->loadImage("tmg-logo.png");
    
    const int tmgLogoWidth = tmgLogImg->getWidth();
    const int tmgLogoHeight = tmgLogImg->getHeight();
    const int tmgLogoX = leftSidebarWidth/2 - tmgLogoWidth/2;
    const int tmgLogoY = dividerY + 50 + dividerHeight;
    
    UIImage *tmgLogo = new UIImage(tmgLogImg, tmgLogoX, tmgLogoY);
    
    // tmg description
    const int tmgTextWidth = 300;
    const int tmgTextX = leftSidebarWidth/2 - descTextWidth/2;
    const int tmgTextY = tmgLogoY + tmgLogoHeight + 50;
    const int tmgTextSize = 10;
    const string tmgTextStr = "The Tangible Media Group, led by Professor Hiroshi Ishii, seeks to seamlessly couple the dual world of bits and atoms by giving dynamic physical form to digital information and computation.";
    UIText* tmgText = new UIText(tmgTextStr, "TMG description", tmgTextSize, tmgTextX, tmgTextY);
    tmgText->setAlignment("left");
    tmgText->setWidth(tmgTextWidth);
    tmgText->setColor(ofColor(35,35,35));
    
    uiHandler->addImage(inFORMLogo);
    uiHandler->addText(creatorText);
    uiHandler->addText(inFORMText);
    uiHandler->addImage(divider);
    uiHandler->addImage(tmgLogo);
    uiHandler->addText(tmgText);
    
    
    vector<UIElement*> infoScreenGroup = vector<UIElement*>();
    infoScreenGroup.push_back(inFORMLogo);
    infoScreenGroup.push_back(creatorText);
    infoScreenGroup.push_back(inFORMText);
    infoScreenGroup.push_back(divider);
    infoScreenGroup.push_back(tmgLogo);
    infoScreenGroup.push_back(tmgText);
    uiHandler->addUIGroup(infoScreenGroup, "info");
}

//--------------------------------------------------------------

void GUI::setupTeleBar(UIHandler *uiHandler, const int leftSidebarWidth) {
    
    // divider
    ofImage* dividerImg = new ofImage();
    dividerImg->loadImage("divider.png");
    
    const int dividerWidth = dividerImg->getWidth();
    const int dividerHeight = dividerImg->getHeight();
    const int dividerX = leftSidebarWidth/2 - dividerWidth/2;
    
    // headline text
    const int textWidth = 300;
    const int textX = leftSidebarWidth/2 - textWidth/2;
    const int headlineY = 60;
    const int descY = 105;
    
    const int headlineSize = 16;
    const int textSize = 10;
    
    const string headlineStr = "Teleoperation Tips";
    const string teleDescStr = "inFORM virtually mirrors your hands to directly control and play with the red ball. Here are some fun things to try out:";
    
    UIText* headline = new UIText(headlineStr, "tele headline", headlineSize, textX, headlineY);
    headline->setWidth(textWidth);
    headline->setColor(ofColor(35,35,35));
    UIText* teleDesc =new UIText(teleDescStr, "tele description", textSize, textX, descY);
    teleDesc->setWidth(textWidth);
    teleDesc->setColor(ofColor(35,35,35));
    
    const int divider1Y = descY + 125;
    UIImage* divider1 = new UIImage(dividerImg,
                                    dividerX, divider1Y);
    
    // telepresence stuff
    ofImage* teleBatImage = new ofImage();
    teleBatImage->loadImage("Teleoperation/assets/bat.png");
    
    const int teleBatHeight = teleBatImage->getHeight();
    const int teleBatWidth = teleBatImage->getWidth();
    const int teleBatX = leftSidebarWidth/2 - teleBatWidth/2;
    const int teleBatY = divider1Y + 25;
    const int teleSpacing = 60;
    const int captionTextHeight = 30;
    
    UIImage *teleBat = new UIImage(teleBatImage, teleBatX, teleBatY);
    teleBat->setCaption("Bat the ball left and right", 10, 300);
    teleBat->getCaption()->setColor(ofColor(35,35,35));
    
    const int divider2Y = teleBatY + teleBatHeight + captionTextHeight + teleSpacing/2;
    UIImage* divider2 = new UIImage(dividerImg,
                                    dividerX, divider2Y);
    
    const int telePushY = teleBatY + teleBatHeight + captionTextHeight + teleSpacing;
    ofImage* telePushImage = new ofImage();
    telePushImage->loadImage("Teleoperation/assets/push.png");
    
    UIImage *telePush = new UIImage(telePushImage, teleBatX, telePushY);
    telePush->setCaption("Cup your hand and push", 10, 300);
    telePush->getCaption()->setColor(ofColor(35,35,35));
    
    const int divider3Y = telePushY + teleBatHeight + captionTextHeight + teleSpacing/2;
    UIImage* divider3 = new UIImage(dividerImg,
                                    dividerX, divider3Y);
    
    ofImage* teleScoopImage = new ofImage();
    teleScoopImage->loadImage("Teleoperation/assets/scoop.png");
    
    const int teleScoopY = telePushY + teleBatHeight + captionTextHeight + teleSpacing;
    UIImage *teleScoop = new UIImage(teleScoopImage, teleBatX, teleScoopY);
    teleScoop->setCaption("Start low and scoop it", 10, 300);
    teleScoop->getCaption()->setColor(ofColor(35,35,35));
    
    uiHandler->addText(headline);
    uiHandler->addText(teleDesc);
    uiHandler->addImage(divider1);
    uiHandler->addImage(teleBat);
    uiHandler->addImage(divider2);
    uiHandler->addImage(telePush);
    uiHandler->addImage(divider3);
    uiHandler->addImage(teleScoop);
    
    
    vector<UIElement*> telepresenceGroup = vector<UIElement*>();
    telepresenceGroup.push_back(headline);
    telepresenceGroup.push_back(teleDesc);
    telepresenceGroup.push_back(divider1);
    telepresenceGroup.push_back(teleBat);
    telepresenceGroup.push_back(divider2);
    telepresenceGroup.push_back(telePush);
    telepresenceGroup.push_back(divider3);
    telepresenceGroup.push_back(teleScoop);
    uiHandler->addUIGroup(telepresenceGroup, "telepresence");
}

//--------------------------------------------------------------

void GUI::setupWaveBar(UIHandler *uiHandler, const int leftSidebarWidth) {
    
    // divider
    ofImage* dividerImg = new ofImage();
    dividerImg->loadImage("divider.png");
    
    const int dividerWidth = dividerImg->getWidth();
    const int dividerHeight = dividerImg->getHeight();
    const int dividerX = leftSidebarWidth/2 - dividerWidth/2;
    
    // headline text
    const int textWidth = 300;
    const int textX = leftSidebarWidth/2 - textWidth/2;
    const int headlineY = 60;
    const int descY = 105;
    
    const int headlineSize = 16;
    const int textSize = 10;
    
    const string headlineStr = "Wave Tips";
    const string waveDescStr = "Wave your hands over the table on the right to create various water ripples across the remote tabletop.";
    
    UIText* headline = new UIText(headlineStr, "wave headline", headlineSize, textX, headlineY);
    headline->setWidth(textWidth);
    headline->setColor(ofColor(35,35,35));
    UIText* waveDesc =new UIText(waveDescStr, "wave description", textSize, textX, descY);
    waveDesc->setWidth(textWidth);
    waveDesc->setColor(ofColor(35,35,35));
    
    const int divider1Y = descY + 125;
    UIImage* divider1 = new UIImage(dividerImg,
                                    dividerX, divider1Y);
    
    
    
    // wavepresence stuff
    ofImage* waveSideImage = new ofImage();
    waveSideImage->loadImage("Wave/assets/side.png");
    
    const int waveSideHeight = waveSideImage->getHeight();
    const int waveSideWidth = waveSideImage->getWidth();
    const int waveSideX = leftSidebarWidth/2 - waveSideWidth/2;
    const int waveSideY = divider1Y + 25;
    const int waveSpacing = 60;
    const int captionTextHeight = 30;
    
    UIImage *waveSide = new UIImage(waveSideImage, waveSideX, waveSideY);
    waveSide->setCaption("Move your hand side to side", 10, 300);
    waveSide->getCaption()->setColor(ofColor(35,35,35));
    
    const int divider2Y = waveSideY + waveSideHeight + captionTextHeight + waveSpacing/2;
    UIImage* divider2 = new UIImage(dividerImg,
                                    dividerX, divider2Y);
    
    const int waveVerticalY = waveSideY + waveSideHeight + captionTextHeight + waveSpacing;
    ofImage* waveVerticalImage = new ofImage();
    waveVerticalImage->loadImage("Wave/assets/height.png");
    
    UIImage *waveVertical = new UIImage(waveVerticalImage, waveSideX, waveVerticalY);
    waveVertical->setCaption("Up & down for stronger waves", 10, 300);
    waveVertical->getCaption()->setColor(ofColor(35,35,35));
    
    const int divider3Y = waveVerticalY + waveSideHeight + captionTextHeight + waveSpacing/2;
    UIImage* divider3 = new UIImage(dividerImg,
                                    dividerX, divider3Y);
    
    ofImage* waveBothImage = new ofImage();
    waveBothImage->loadImage("Wave/assets/both.png");
    
    const int waveBothY = waveVerticalY + waveSideHeight + captionTextHeight + waveSpacing;
    UIImage *waveBoth = new UIImage(waveBothImage, waveSideX, waveBothY);
    waveBoth->setCaption("Try both hands at once", 10, 300);
    waveBoth->getCaption()->setColor(ofColor(35,35,35));
    
    uiHandler->addText(headline);
    uiHandler->addText(waveDesc);
    uiHandler->addImage(divider1);
    uiHandler->addImage(waveSide);
    uiHandler->addImage(divider2);
    uiHandler->addImage(waveVertical);
    uiHandler->addImage(divider3);
    uiHandler->addImage(waveBoth);
    
    
    vector<UIElement*> wavepresenceGroup = vector<UIElement*>();
    wavepresenceGroup.push_back(headline);
    wavepresenceGroup.push_back(waveDesc);
    wavepresenceGroup.push_back(divider1);
    wavepresenceGroup.push_back(waveSide);
    wavepresenceGroup.push_back(divider2);
    wavepresenceGroup.push_back(waveVertical);
    wavepresenceGroup.push_back(divider3);
    wavepresenceGroup.push_back(waveBoth);
    uiHandler->addUIGroup(wavepresenceGroup, "wavy");
}

//--------------------------------------------------------------

void GUI::setupCityBar(UIHandler* uiHandler, const int leftSidebarWidth)
{
    //TEXT
    const int textWidth = 300;
    const int textX = 60;
    const int textY = 155;
    const int headlineY = 60;
    const int captionX = 88;
    const int caption1Y = 483+10;
    const int caption2Y = 577+10;
    
    const int headlineSize = 16;
    const int textSize = 10;
    
    const string headlineStr = "City Scape Controls and Tips";
    const string textStr = "Use the touch screen controls below and on the right to pan the map and change filters.";
    const string caption1Str = "drag the loupe with your finger";
    const string caption2Str = "Choose a filter to explore";
    //string modelNameStr = ((ReliefApplication*)ofGetAppPtr())->threeDShapeObject->getCurrentModelName(); // could be nicer
    const string timeStr = " "; //will be changed dynamically
    const int timeX = 960;
    
    ofImage* timeT = new ofImage();
    timeT->loadImage("City/assets/timetip.png");
    
    UIText* text = new UIText(textStr, "city description", textSize, textX, textY);
    UIText* headline = new UIText(headlineStr, "city headline", headlineSize, textX, headlineY);
    UIText* caption1 = new UIText(caption1Str, "caption1", textSize, captionX, caption1Y);
    UIText* caption2 = new UIText(caption2Str, "caption2", textSize, captionX, caption2Y);
    UIText* time = new UIText(timeStr, "time", 6, timeX-28, 938);
    UIImage* timeTip = new UIImage(timeT, "timeTip", timeX-42, 920);
    
    headline->setAlignment("left");
    headline->setWidth(textWidth);
    headline->setColor(ofColor(35,35,35));
    text->setAlignment("left");
    text->setWidth(textWidth);
    text->setColor(ofColor(35,35,35));
    caption1->setAlignment("left");
    caption1->setWidth(textWidth);
    caption1->setColor(ofColor(35,35,35));
    caption2->setAlignment("left");
    caption2->setWidth(textWidth);
    caption2->setColor(ofColor(35,35,35));
    
    time->setAlignment("center");
    time->setWidth(50);
    time->setColor(ofColor(35,35,35));
    
    
    
    
    // DIVIDERS
    ofImage* dividerImg = new ofImage();
    dividerImg->loadImage("divider.png");
    
    const int dividerWidth = dividerImg->getWidth();
    const int dividerHeight = dividerImg->getHeight();
    const int dividerX = leftSidebarWidth/2 - dividerWidth/2;
    const int dividerY = 270;
    const int dividerSpacerY = 270;
    
    UIImage* divider1 = new UIImage(dividerImg, dividerX, 270);
    UIImage* divider2 = new UIImage(dividerImg, dividerX, 540);
    
    
    
    //IMAGE
    ofImage* dragImg = new ofImage();
    dragImg->loadImage("City/assets/dragloupe.png");
    
    const int dragImgWidth = dragImg->getWidth();
    const int dragImgHeight = dragImg->getHeight();
    const int dragImgX = leftSidebarWidth/2 - dragImgWidth/2;
    const int dragImgY = 300;
    
    UIImage *DragImg = new UIImage(dragImg, dragImgX, dragImgY);
    
    
    //BUTTONS
    // UIButton name = UIButton("name", x,y, w,h)
    const int citySelectButtonWidth  = 307;
    const int citySelectButtonHeight = 89;
    
    const int citySelectButtonX = 60;
    const int citySelectButtonY = 625;
    
    const int spacer = 106;
    
    UIButton* citySelectButton1
    = new UIButton("citySelectButton1",
                   citySelectButtonX, citySelectButtonY,
                   citySelectButtonWidth,citySelectButtonHeight);
    citySelectButton1->setImageIdle("City/assets/shadow.png");
    citySelectButton1->setImageActive("City/assets/shadow-active.png");
    citySelectButton1->setImageSelected("City/assets/shadow-selected.png");
    
    UIButton* citySelectButton2
    = new UIButton("citySelectButton2",
                   citySelectButtonX, citySelectButtonY + spacer,
                   citySelectButtonWidth,citySelectButtonHeight);
    citySelectButton2->setImageIdle("City/assets/traffic.png");
    citySelectButton2->setImageActive("City/assets/traffic-active.png");
    citySelectButton2->setImageSelected("City/assets/traffic-selected.png");
    
    UIButton* citySelectButton3
    = new UIButton("citySelectButton3",
                   citySelectButtonX, citySelectButtonY + spacer*2,
                   citySelectButtonWidth,citySelectButtonHeight);
    citySelectButton3->setImageIdle("City/assets/energy.png");
    citySelectButton3->setImageActive("City/assets/energy-active.png");
    citySelectButton3->setImageSelected("City/assets/energy-selected.png");
    
    UIButton* citySelectButton4
    = new UIButton("citySelectButton4",
                   citySelectButtonX, citySelectButtonY + spacer*3,
                   citySelectButtonWidth,citySelectButtonHeight);
    citySelectButton4->setImageIdle("City/assets/population.png");
    citySelectButton4->setImageActive("City/assets/population-active.png");
    citySelectButton4->setImageSelected("City/assets/population-selected.png");
    
    
    // SLIDERS
    const int sliderWidth = 955-50;//1006;
    const int sliderX = 960-sliderWidth/2-22;
    const int sliderY = 985;
    // name, bool horizontal, int trackX, int trackY, int trackLength, int handleWidth, int handleHeight
    //3D SLIDER
    /*UISlider *sliderScale = new UISlider("sliderPosition", true, sliderX, sliderY, sliderWidth, 46, 50);
    sliderScale->setImageHandleActive("City/assets/cityknob.png");
    sliderScale->setImageHandleIdle("City/assets/cityknob.png");
    sliderScale->setImageTrack("City/assets/timeline.png");
    sliderScale->setImageTrackOffset(-3);
    sliderScale->setHandlePos(0.5);*/
    
    
    
    //SETUP
    uiHandler->addButton(citySelectButton1);
    uiHandler->addButton(citySelectButton2);
    uiHandler->addButton(citySelectButton3);
    uiHandler->addButton(citySelectButton4);
    //uiHandler->addSlider(sliderScale);
    uiHandler->addImage(divider1);
    uiHandler->addImage(divider2);
    uiHandler->addImage(DragImg);
    uiHandler->addText(headline);
    uiHandler->addText(text);
    uiHandler->addText(caption1);
    uiHandler->addText(caption2);
    uiHandler->addText(time);
    uiHandler->addImage(timeTip);
    
    vector<UIElement*> cityGroup = vector<UIElement*>();
    cityGroup.push_back(citySelectButton1);
    cityGroup.push_back(citySelectButton2);
    cityGroup.push_back(citySelectButton3);
    cityGroup.push_back(citySelectButton4);
    //cityGroup.push_back(sliderScale);
    cityGroup.push_back(divider1);
    cityGroup.push_back(divider2);
    cityGroup.push_back(DragImg);
    cityGroup.push_back(headline);
    cityGroup.push_back(text);
    cityGroup.push_back(caption1);
    cityGroup.push_back(caption2);
    cityGroup.push_back(time);
    cityGroup.push_back(timeTip);
    
    uiHandler->addUIGroup(cityGroup, "city");
    
    
    // add these buttons to a group
    // for the "select" and "unselect" functionality
    vector<UIButton*>* citySelectButtonGroup = new vector<UIButton*>();
    citySelectButtonGroup->push_back(citySelectButton1);
    citySelectButtonGroup->push_back(citySelectButton2);
    citySelectButtonGroup->push_back(citySelectButton3);
    citySelectButtonGroup->push_back(citySelectButton4);
    uiHandler->addButtonGroup(citySelectButtonGroup);
    
//    UITriggers::buttonTrigger(citySelectButton1);
}

//--------------------------------------------------------------

void GUI::setupThreeDBar(UIHandler* uiHandler, const int leftSidebarWidth)
{
    //TEXT
    const int textWidth = 300;
    const int textX = 60;
    const int textY = 105;
    const int headlineY = 60;
    const int captionX = 88;
    const int caption1Y = 300;
    const int caption2Y = 570;
    const int caption3Y = 840;
    const int modelNameY = 380;
    
    const int headlineSize = 16;
    const int textSize = 10;
    const int modelNameSize = 20;
    
    const string headlineStr = "3d Model Controls";
    const string textStr = "Use the touch screen controls located below to load a new 3d model, rotate it around, and/or scale it to different sizes.";
    const string caption1Str = "Select between 3d models";
    const string caption2Str = "Slide Finger below to rotate";
    const string caption3Str = "Drag slider to resize model";
    //string modelNameStr = ((ReliefApplication*)ofGetAppPtr())->threeDShapeObject->getCurrentModelName(); // could be nicer
    const string modelNameStr = " "; //will be changed dynamically
    
    UIText* text = new UIText(textStr, "3D description", textSize, textX, textY);
    UIText* headline = new UIText(headlineStr, "3d headline", headlineSize, textX, headlineY);
    UIText* caption1 = new UIText(caption1Str, "caption1", textSize, captionX, caption1Y);
    UIText* caption2 = new UIText(caption2Str, "caption2", textSize, captionX, caption2Y);
    UIText* caption3 = new UIText(caption3Str, "caption3", textSize, captionX, caption3Y);
    UIText* modelName = new UIText(modelNameStr, "modelName", modelNameSize, textX, modelNameY);
    
    headline->setAlignment("left");
    headline->setWidth(textWidth);
    headline->setColor(ofColor(35,35,35));
    text->setAlignment("left");
    text->setWidth(textWidth);
    text->setColor(ofColor(35,35,35));
    caption1->setAlignment("left");
    caption1->setWidth(textWidth);
    caption1->setColor(ofColor(35,35,35));
    caption2->setAlignment("left");
    caption2->setWidth(textWidth);
    caption2->setColor(ofColor(35,35,35));
    caption3->setAlignment("left");
    caption3->setWidth(textWidth);
    caption3->setColor(ofColor(35,35,35));
    modelName->setAlignment("center");
    modelName->setWidth(textWidth);
    modelName->setColor(ofColor(35,35,35));
    
    
    // DIVIDERS
    ofImage* dividerImg = new ofImage();
    dividerImg->loadImage("divider.png");
    
    const int dividerWidth = dividerImg->getWidth();
    const int dividerHeight = dividerImg->getHeight();
    const int dividerX = leftSidebarWidth/2 - dividerWidth/2;
    const int dividerY = 270;
    const int dividerSpacerY = 270;
    
    UIImage* divider1 = new UIImage(dividerImg, dividerX, dividerY);
    UIImage* divider2 = new UIImage(dividerImg, dividerX, dividerY + 1 * dividerSpacerY);
    UIImage* divider3 = new UIImage(dividerImg, dividerX, dividerY + 2 * dividerSpacerY);
    
    
    //BUTTONS
    // UIButton name = UIButton("name", x,y, w,h)
    const int modelSelectButtonWidth  = 142;
    const int modelSelectButtonHeight = 70;
    
    const int modelSelectButtonX = 60;
    const int modelSelectButtonY = 440;
    const int spacer = 160;
    
    UIButton* modelSelectButtonLeft
    = new UIButton("modelSelectLeft",
                   modelSelectButtonX, modelSelectButtonY,
                   modelSelectButtonWidth,modelSelectButtonHeight);
    modelSelectButtonLeft->setImageIdle("3D Models/assets/larrow.png");
    modelSelectButtonLeft->setImageActive("3D Models/assets/larrow.png");
    modelSelectButtonLeft->setImageSelected("3D Models/assets/larrow.png");
    
    UIButton* modelSelectButtonRight
    = new UIButton("modelSelectRight",
                   modelSelectButtonX + spacer, modelSelectButtonY,
                   modelSelectButtonWidth,modelSelectButtonHeight);
    modelSelectButtonRight->setImageIdle("3D Models/assets/rarrow.png");
    modelSelectButtonRight->setImageActive("3D Models/assets/rarrow.png");
    modelSelectButtonRight->setImageSelected("3D Models/assets/rarrow.png");
    
    
    // SLIDERS
    const int sliderWidth = 280;
    const int sliderX = MARGIN_X/2 - sliderWidth/2;
    const int sliderY = 940;
    
    // name, bool horizontal, int trackX, int trackY, int trackLength, int handleWidth, int handleHeight
    //3D SLIDER
    UISlider *sliderScale = new UISlider("sliderScale", true, sliderX, sliderY, sliderWidth, 46, 50);
    sliderScale->setImageHandleActive("3D Models/assets/knob.png");
    sliderScale->setImageHandleIdle("3D Models/assets/knob.png");
    sliderScale->setImageTrack("3D Models/assets/slider.png");
    sliderScale->setImageTrackOffset(-10);
    sliderScale->setHandlePos(0.5);
    
    sliderScale->setLockToPosThresh(0.05);
    sliderScale->addLockToPos(0.5);
    sliderScale->addLockToPos(0);
    sliderScale->addLockToPos(1);
    
    //SETUP
    uiHandler->addButton(modelSelectButtonLeft);
    uiHandler->addButton(modelSelectButtonRight);
    //uiHandler->addSlider(sliderScale);
    uiHandler->addImage(divider1);
    uiHandler->addImage(divider2);
    uiHandler->addImage(divider3);
    uiHandler->addText(headline);
    uiHandler->addText(text);
    uiHandler->addText(caption1);
    uiHandler->addText(caption2);
    uiHandler->addText(caption3);
    uiHandler->addText(modelName);
    
    vector<UIElement*> threeDGroup = vector<UIElement*>();
    threeDGroup.push_back(modelSelectButtonLeft);
    threeDGroup.push_back(modelSelectButtonRight);
    //threeDGroup.push_back(sliderScale);
    threeDGroup.push_back(divider1);
    threeDGroup.push_back(divider2);
    threeDGroup.push_back(divider3);
    threeDGroup.push_back(headline);
    threeDGroup.push_back(text);
    threeDGroup.push_back(caption1);
    threeDGroup.push_back(caption2);
    threeDGroup.push_back(caption3);
    threeDGroup.push_back(modelName);
    
    uiHandler->addUIGroup(threeDGroup, "3D");
}

//--------------------------------------------------------------

void GUI::setupMathBar(UIHandler* uiHandler, const int leftSidebarWidth)
{
    //TEXT
    const int textWidth = 300;
    const int textX = 60;
    const int textY = 155;
    const int headlineY = 60;
    const int captionX = 88;
    const int caption2Y = 570;
    const int modelNameY = 380;
    
    const int headlineSize = 16;
    const int textSize = 10;
    const int modelNameSize = 26;
    
    const string headlineStr = "Math Controls and Tips";
    const string textStr = "Use the touch screen controls below and on the right to load and modify new equations.";
    const string caption2Str = "Choose  a new equation";
    const string equationStr = ""; //will be changed dynamically
    const string eqVal1Str = ""; //will be changed dynamically
    const string eqVal2Str = ""; //will be changed dynamically
    
    
    UIText* text = new UIText(textStr, "Math description", textSize, textX, textY);
    UIText* headline = new UIText(headlineStr, "Math headline", headlineSize, textX, headlineY);
    UIText* caption2 = new UIText(caption2Str, "caption2", textSize, captionX, caption2Y);
    
    
    headline->setAlignment("left");
    headline->setWidth(textWidth-50);
    headline->setColor(ofColor(35,35,35));
    text->setAlignment("left");
    text->setWidth(textWidth);
    text->setColor(ofColor(35,35,35));
    caption2->setAlignment("left");
    caption2->setWidth(textWidth);
    caption2->setColor(ofColor(35,35,35));
    
    
    // DIVIDERS
    ofImage* dividerImg = new ofImage();
    dividerImg->loadImage("divider.png");
    //  int val = function.eq_val1;
    
    const int dividerWidth = dividerImg->getWidth();
    const int dividerHeight = dividerImg->getHeight();
    const int dividerX = leftSidebarWidth/2 - dividerWidth/2;
    const int dividerY = 250;
    const int dividerSpacerY = 270;
    
    UIImage* divider1 = new UIImage(dividerImg, dividerX, dividerY);
    UIImage* divider2 = new UIImage(dividerImg, dividerX, dividerY + 1 * dividerSpacerY);
    
    
    ofImage* tapArrowsImage = new ofImage();
    tapArrowsImage->loadImage("Math/assets/taparrows.png");
    const int tapArrowsWidth = tapArrowsImage->getWidth();
    const int tapArrowsX = leftSidebarWidth/2 - tapArrowsWidth/2;
    const int tapArrowsY = dividerY + 25;
    
    UIImage *tapArrows = new UIImage(tapArrowsImage, tapArrowsX, tapArrowsY);
    tapArrows->setCaption("Tapping the arrows on the right changes the numbers", 10, 300);
    tapArrows->getCaption()->setColor(ofColor(35,35,35));

    
    //MODIFY BUTTONS
    // UIButton name = UIButton("name", x,y, w,h)
    const int modifyButtonWidth  = 48;
    const int modifyButtonHeight = 60;
    const int spacerX = 300;
    const int spacerY = 150;
    const int modifyButtonX = TOUCHSCREEN_SIZE_X/2 - spacerX/2 - modifyButtonWidth;
    const int modifyButtonY = 100;
    
    UIButton* modifyVal1Up
    = new UIButton("modifyVal1Up",
                   modifyButtonX, modifyButtonY,
                   modifyButtonWidth,modifyButtonHeight);
    modifyVal1Up->setImageIdle("Math/assets/uarrow.png");
    modifyVal1Up->setImageActive("Math/assets/uarrow-selected.png");
    modifyVal1Up->setImageSelected("Math/assets/uarrow.png");
    
    UIButton* modifyVal1Down
    = new UIButton("modifyVal1Down",
                   modifyButtonX, modifyButtonY+modifyButtonHeight+spacerY,
                   modifyButtonWidth,modifyButtonHeight);
    modifyVal1Down->setImageIdle("Math/assets/darrow.png");
    modifyVal1Down->setImageActive("Math/assets/darrow-selected.png");
    modifyVal1Down->setImageSelected("Math/assets/darrow.png");
    
    UIButton* modifyVal2Up
    = new UIButton("modifyVal2Up",
                   modifyButtonX+spacerX, modifyButtonY,
                   modifyButtonWidth,modifyButtonHeight);
    modifyVal2Up->setImageIdle("Math/assets/uarrow.png");
    modifyVal2Up->setImageActive("Math/assets/uarrow-selected.png");
    modifyVal2Up->setImageSelected("Math/assets/uarrow.png");
    
    UIButton* modifyVal2Down
    = new UIButton("modifyVal2Down",
                   modifyButtonX+spacerX, modifyButtonY + modifyButtonHeight + spacerY,
                   modifyButtonWidth,modifyButtonHeight);
    modifyVal2Down->setImageIdle("Math/assets/darrow.png");
    modifyVal2Down->setImageActive("Math/assets/darrow-selected.png");
    modifyVal2Down->setImageSelected("Math/assets/darrow.png");
    
    const int eqVal1X = modifyButtonX;
    const int eqVal2X = modifyButtonX + spacerX;
    const int eqValY  = modifyButtonY + modifyButtonHeight + spacerY/2 + 20;
    UINum* eqVal1 = new UINum(eqVal1Str, "eqVal1", modelNameSize, eqVal1X, eqValY);
    UINum* eqVal2 = new UINum(eqVal1Str, "eqVal2", modelNameSize, eqVal2X, eqValY);
    eqVal1->setAlignment("center");
    eqVal1->setWidth(modifyButtonWidth);
    eqVal1->setColor(ofColor(230,0,0));
    eqVal2->setAlignment("center");
    eqVal2->setWidth(modifyButtonWidth);
    eqVal2->setColor(ofColor(230,0,0));
    
    const int eqValSec1X = modifyButtonX;
    const int eqValSec2X = modifyButtonX + spacerX;
    const int eqValSecY  = modifyButtonY + modifyButtonHeight + spacerY/2 + 20;
    UINum* eqValSec1 = new UINum(eqVal1Str, "eqValSecond1", modelNameSize, eqVal1X, eqValY);
    UINum* eqValSec2 = new UINum(eqVal1Str, "eqValSecond2", modelNameSize, eqVal2X, eqValY);
    eqValSec1->setAlignment("center");
    eqValSec1->setWidth(modifyButtonWidth);
    eqValSec1->setColor(ofColor(35,35,35));
    eqValSec2->setAlignment("center");
    eqValSec2->setWidth(modifyButtonWidth);
    eqValSec2->setColor(ofColor(35,35,35));
    eqValSec1->hide();
    eqValSec2->hide();
    
    
    ofImage* equationImg = new ofImage();
    equationImg->loadImage("Math/assets/eq/equation-01.png");
    const int equationWidth = equationImg->getWidth();
    const int equationHeight = equationImg->getHeight();
    const int equationX = TOUCHSCREEN_SIZE_X/2 - equationWidth/2;
    const int equationY = modifyButtonY + modifyButtonHeight + spacerY/2 - equationHeight/2;
    
    UIImage* equation = new UIImage(equationImg, equationX, equationY);
    equation->setName("equation");
    
    //EQUATION BUTTONS
    // UIButton name = UIButton("name", x,y, w,h)
    const int equationSelectButtonWidth  = 307;
    const int equationSelectButtonHeight = 63;
    
    const int equationSelectButtonX = 60;
    const int equationSelectButtonY = 610;
    const int spacer = 90;
    
    UIButton* equationSelectButton1
    = new UIButton("equationSelectButton1",
                   equationSelectButtonX, equationSelectButtonY,
                   equationSelectButtonWidth,equationSelectButtonHeight);
    equationSelectButton1->setImageIdle("Math/assets/equation1.png");
    equationSelectButton1->setImageActive("Math/assets/equation1-active.png");
    equationSelectButton1->setImageSelected("Math/assets/equation1-selected.png");
    
    UIButton* equationSelectButton2
    = new UIButton("equationSelectButton2",
                   equationSelectButtonX, equationSelectButtonY+spacer,
                   equationSelectButtonWidth,equationSelectButtonHeight);
    equationSelectButton2->setImageIdle("Math/assets/equation2.png");
    equationSelectButton2->setImageActive("Math/assets/equation2-active.png");
    equationSelectButton2->setImageSelected("Math/assets/equation2-selected.png");
    
    UIButton* equationSelectButton3
    = new UIButton("equationSelectButton3",
                   equationSelectButtonX, equationSelectButtonY + spacer*2,
                   equationSelectButtonWidth,equationSelectButtonHeight);
    equationSelectButton3->setImageIdle("Math/assets/equation3.png");
    equationSelectButton3->setImageActive("Math/assets/equation3-active.png");
    equationSelectButton3->setImageSelected("Math/assets/equation3-selected.png");
    
    UIButton* equationSelectButton4
    = new UIButton("equationSelectButton4",
                   equationSelectButtonX, equationSelectButtonY + spacer*3,
                   equationSelectButtonWidth,equationSelectButtonHeight);
    equationSelectButton4->setImageIdle("Math/assets/equation4.png");
    equationSelectButton4->setImageActive("Math/assets/equation4-active.png");
    equationSelectButton4->setImageSelected("Math/assets/equation4-selected.png");
    
    UIButton* equationSelectButton5
    = new UIButton("equationSelectButton5",
                   equationSelectButtonX, equationSelectButtonY + spacer*4,
                   equationSelectButtonWidth,equationSelectButtonHeight);
    equationSelectButton5->setImageIdle("Math/assets/equation5.png");
    equationSelectButton5->setImageActive("Math/assets/equation5-active.png");
    equationSelectButton5->setImageSelected("Math/assets/equation5-selected.png");
    
    
    //SETUP
    uiHandler->addButton(modifyVal1Up);
    uiHandler->addButton(modifyVal1Down);
    uiHandler->addButton(modifyVal2Up);
    uiHandler->addButton(modifyVal2Down);
    uiHandler->addButton(equationSelectButton1);
    uiHandler->addButton(equationSelectButton2);
    uiHandler->addButton(equationSelectButton3);
    uiHandler->addButton(equationSelectButton4);
    uiHandler->addButton(equationSelectButton5);
    uiHandler->addImage(divider1);
    uiHandler->addImage(divider2);
    uiHandler->addImage(tapArrows);
    uiHandler->addText(headline);
    uiHandler->addText(text);
    uiHandler->addText(caption2);
    uiHandler->addImage(equation);
    uiHandler->addNum(eqVal1);
    uiHandler->addNum(eqVal2);
    uiHandler->addNum(eqValSec1);
    uiHandler->addNum(eqValSec2);
    
    vector<UIElement*> mathGroup = vector<UIElement*>();
    mathGroup.push_back(modifyVal1Up);
    mathGroup.push_back(modifyVal1Down);
    mathGroup.push_back(modifyVal2Up);
    mathGroup.push_back(modifyVal2Down);
    mathGroup.push_back(equationSelectButton1);
    mathGroup.push_back(equationSelectButton2);
    mathGroup.push_back(equationSelectButton3);
    mathGroup.push_back(equationSelectButton4);
    mathGroup.push_back(equationSelectButton5);
    mathGroup.push_back(divider1);
    mathGroup.push_back(divider2);
    mathGroup.push_back(tapArrows);
    mathGroup.push_back(headline);
    mathGroup.push_back(text);
    mathGroup.push_back(caption2);
    mathGroup.push_back(eqVal1);
    mathGroup.push_back(eqVal2);
    mathGroup.push_back(eqValSec1);
    mathGroup.push_back(eqValSec2);
    mathGroup.push_back(equation);
    
    uiHandler->addUIGroup(mathGroup, "math");
    
    vector<UIButton*>* equationButtonGroup = new vector<UIButton*>();
    equationButtonGroup->push_back(equationSelectButton1);
    equationButtonGroup->push_back(equationSelectButton2);
    equationButtonGroup->push_back(equationSelectButton3);
    equationButtonGroup->push_back(equationSelectButton4);
    equationButtonGroup->push_back(equationSelectButton5);
    uiHandler->addButtonGroup(equationButtonGroup);
    
//    UITriggers::buttonTrigger(equationSelectButton1);
}

//--------------------------------------------------------------

void GUI::setupUI(UIHandler* uiHandler) {
    const int leftSidebarWidth = 420;
    const int rightSidebarWidth = 420;
    
    setupRightSidebar(uiHandler, rightSidebarWidth);
    
    setupLeftSidebar(uiHandler, leftSidebarWidth);
    
    // drop shadow for middle region
    ofImage* centerDropShadowImg = new ofImage();
    centerDropShadowImg->loadImage("pin-shadow.png");
    
    const int dropShadowX = leftSidebarWidth + 1;
    const int dropShadowY = 1;
    
    UIImage *centerDropShadow = new UIImage(centerDropShadowImg, dropShadowX, dropShadowY);
    
    uiHandler->addImage(centerDropShadow);
}

//--------------------------------------------------------------


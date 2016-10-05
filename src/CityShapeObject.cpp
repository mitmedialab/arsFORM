//
//  CityShapeObject.cpp
//  cooperFORM
//
//  Created by ken_tmg on 11/7/14.
//
//

#include "CityShapeObject.h"
#include "Constants.h"

// heightMapMovieSize
// colorMovieSize

CityShapeObject::CityShapeObject() {
    touchscreenImage.allocate(TOUCHSCREEN_VISIBLE_SIZE_X, TOUCHSCREEN_SIZE_Y, GL_RGBA);
    pinHeightMapImage.allocate(TOUCHSCREEN_VISIBLE_SIZE_X, TOUCHSCREEN_SIZE_Y, GL_RGBA);
    projectorImage.allocate(PROJECTOR_RAW_RESOLUTION_X, PROJECTOR_RAW_RESOLUTION_Y, GL_RGBA);
    
    //pos = ofVec2f(TOUCHSCREEN_SIZE_Y/2, TOUCHSCREEN_SIZE_Y/2);
    length = 200;
    rectLength = 200 * heightMapMovieSize /TOUCHSCREEN_SIZE_Y;
    
    loupeTargetPostion.setPosition(ofPoint(TOUCHSCREEN_SIZE_Y/2, TOUCHSCREEN_SIZE_Y/2));
    loupeTargetPostion.setDuration( 4.0f );
    loupeTargetPostion.setRepeatType(PLAY_ONCE);
    loupeTargetPostion.setCurve(LINEAR);
    
    cityMov[0][0].loadMovie("City/mov/Shadow.mov");
    cityMov[0][1].loadMovie("City/mov/Shadow_bw.mov");
    cityMov[1][0].loadMovie("City/mov/Traffic.mov");
    cityMov[1][1].loadMovie("City/mov/Traffic_bw.mov");
    cityMov[2][0].loadMovie("City/mov/Energy.mov");
    cityMov[2][1].loadMovie("City/mov/Energy_bw.mov");
    cityMov[3][0].loadMovie("City/mov/Sequence.mov");
    cityMov[3][1].loadMovie("City/mov/Sequence_bw.mov");
    
    realMap.loadImage("City/map.jpg");
    
    /*cityImages[0][0].loadImage("City/map.jpg");
    cityImages[1][0].loadImage("City/satellite.jpg");
    cityImages[2][0].loadImage("City/satellite.jpg");
    cityImages[3][0].loadImage("City/satellite.jpg");
    
    cityImages[0][1].loadImage("City/map_height.jpg");
    cityImages[1][1].loadImage("City/satellite_height.jpg");
    cityImages[2][1].loadImage("City/satellite_height.jpg");
    cityImages[3][1].loadImage("City/satellite_height.jpg");*/
    
    
    trimmedMov[0].allocate(rectLength, rectLength, GL_RGB);
    trimmedMov[1].allocate(rectLength, rectLength, GL_RGB);
    
    trimMov 	= new unsigned char[rectLength * rectLength*3];
    
    currentCity = 0;
    previousCity = 0;
    
    for(int i = 0; i < cityNum; i++){
        for(int j = 0; j < 2; j++){
            cityMov[i][j].play();
            cityMov[i][j].setSpeed(0.7);
        }
    }
    
    mapShadow.loadImage("City/assets/map-shadow.png");
    loupe.loadImage("City/assets/loupe.png");
}

//--------------------------------------------------------------

void CityShapeObject::update() {
    float dt = 1.0f / ofGetFrameRate();
    loupeTargetPostion.update(dt);

    //for(int i = 0; i < cityNum; i++){
        for(int j = 0; j < 2; j++){
            if(sliderGrabbed){
                cityMov[currentCity][j].setPosition( time);
            }
            cityMov[currentCity][j].update();
        }
    //}
    //posX = int(pos.x * heightMapMovieSize / TOUCHSCREEN_SIZE_Y);
    //posY = int(pos.y * heightMapMovieSize / TOUCHSCREEN_SIZE_Y);
    
    int posX = int(loupeTargetPostion.getCurrentPosition().x * heightMapMovieSize / TOUCHSCREEN_SIZE_Y);
    int posY = int(loupeTargetPostion.getCurrentPosition().y * heightMapMovieSize / TOUCHSCREEN_SIZE_Y);
    //int y = int(pos.x * heightMapMovieSize / TOUCHSCREEN_SIZE_Y);
    
    if (cityMov[currentCity][0].isFrameNew() || loupeDragged){
        for (int i = 0; i < 2; i++){
            unsigned char * pixels = cityMov[currentCity][i].getPixels();
            for (int j = 0; j < rectLength; j++){ //x
                for (int k = 0; k < rectLength; k++) { //y
                    for(int l =0; l < 3; l++){ //rgb
                        trimMov[j*3+rectLength*k*3 +l] = pixels[(j+posX-rectLength/2)*3 + heightMapMovieSize *(k+posY-rectLength/2)*3 + l];
                        
                        if(i == 1) {
                            int value = trimMov[j*3+rectLength*k*3 +l] + 50;
                            trimMov[j*3+rectLength*k*3 +l] = CLAMP(value, LOW_THRESHOLD, HIGH_THRESHOLD);
                        }
                    }
                }
            }
            trimmedMov[i].loadData(trimMov, rectLength,rectLength, GL_RGB);
        }
    }
}

void CityShapeObject::reset() {
}

//--------------------------------------------------------------

void CityShapeObject::renderProjectorOverlay(int w, int h) {
    
    //trimmedMov[0].draw(510, 1242, 1100, -1100);//3151, 1778);
    trimmedMov[0].draw(510, 1010, 1065, -770);
    
    
}

//--------------------------------------------------------------

void CityShapeObject::renderTangibleShape(int w, int h) {
    
    trimmedMov[1].draw(0, h, w, -h);//(510, 242, 3151, 1778);//(0, 0, w, h);
}

//--------------------------------------------------------------

void CityShapeObject::renderTouchscreenGraphics(int w, int h) {
    
    realMap.draw(0,0,h,h);
    mapShadow.draw(0,0, h, h);
    
    loupe.draw(loupeTargetPostion.getCurrentPosition().x - loupe.width/2,
               loupeTargetPostion.getCurrentPosition().y - loupe.height/2, loupe.width, loupe.height);
    //loupeTargetPostion.drawCurve(<#int x#>, <#int y#>, <#int size#>)
    // debug graphics
    //trimmedMov[0].draw(0,0);
    //trimmedMov[1].draw(rectLength,0);
}

//--------------------------------------------------------------


void CityShapeObject::setMouseDragInfo(int x, int y, int button){
    ofPoint mousePosition = ofPoint(x - UI_LEFTPANE_WIDTH, y);
    
    if( mousePosition.x >= 0 && mousePosition.x< UI_CENTER_WIDTH
       && mousePosition.y >= 0 && mousePosition.y < UI_CENTER_HEIGHT){
        float speed = mousePosition.distance(loupeTargetPostion.getCurrentPosition()) * LOUPE_SPEED_SCALE;
        loupeTargetPostion.setDuration(speed);
        loupeTargetPostion.animateTo(mousePosition);
    }
    
    // Jareds old code --> replaced by daniel
    /*x = x-420;
    if( loupeDragged){
        pos.x = pos.x - (oldMouse.x - x);
        pos.x = ofClamp(pos.x,length/2,TOUCHSCREEN_SIZE_Y-length/2);
        
        pos.y = pos.y - (oldMouse.y - y);
        
        pos.y = ofClamp(pos.y,length/2,TOUCHSCREEN_SIZE_Y-length/2);
        oldMouse= ofVec2f(x,y);
    }*/
}

//--------------------------------------------------------------

void CityShapeObject::setMousePressedInfo(int x, int y){
    ofPoint mousePosition = ofPoint(x - UI_LEFTPANE_WIDTH, y);
    
    if( mousePosition.x >= 0 && mousePosition.x< UI_CENTER_WIDTH
       && mousePosition.y >= 0 && mousePosition.y < UI_CENTER_HEIGHT){
        float speed = mousePosition.distance(loupeTargetPostion.getCurrentPosition()) * LOUPE_SPEED_SCALE;
        loupeTargetPostion.setDuration(speed);
        loupeTargetPostion.animateTo(mousePosition);
    }
    
    // Jareds old code -> replaced by Daniel
    /*x = x-420;
     if( abs(x - pos.x) < length/2 && abs(y - pos.y) < length/2){
        oldMouse = ofVec2f(x,y);
        loupeDragged = true;
    } else {
        loupeDragged = false;
    }*/
    
}

//--------------------------------------------------------------

void CityShapeObject::setMouseReleasedInfo(){
    //   loupeDragged = false;
    
}

//--------------------------------------------------------------

float CityShapeObject:: getMovPosition(){
    
    return cityMov[currentCity][0].getPosition();
}

void CityShapeObject:: setMovPosition(float t){
    
    time = t;

}

void CityShapeObject:: chooseCity(int num){
    
    float val = cityMov[currentCity][0].getPosition();
    currentCity = num;
    
    for (int j = 0; j < 2; j++){
        cityMov[currentCity][j].setPosition(val);
        cityMov[currentCity][j].update();
    }
}
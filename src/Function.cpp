//
//  Function.cpp
//  cooperFORM
//
//  Created by Philipp Schoessler on 10/19/14.
//
//

#include "Function.h"

Function::Function() {
    loadShader();
    
    ofSetVerticalSync(true);
    for(unsigned int i = 0; i < RELIEF_SIZE_X; i++)
        for(unsigned int j = 0; j < RELIEF_SIZE_Y; j++) {
            prev[i][j] = 0;
            curr[i][j] = 0;
            next[i][j] = 0;
        }
    
    nextFunction("next",0);
    anim.setDuration(0.0f);
    
    text.loadFont("frabk.ttf", 100);
    
    ratio = 5;
    
    //store the width and height for convenience
    int width = RELIEF_SIZE_X;
    int height = RELIEF_SIZE_X;
    
    for (int y = 0; y < width; y++){
        for (int x = 0; x<height; x++){
            mainMesh.addVertex(ofPoint(x*5,y*5,0));	// mesh index = x + y*width
            // this replicates the pixel array within the camera bitmap...
            mainMesh.addColor(ofFloatColor(0,0,0));  // placeholder for colour data, we'll get this from the camera
        }
    }
    
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mainMesh.addIndex(x+y*width);				// 0
            mainMesh.addIndex((x+1)+y*width);			// 1
            mainMesh.addIndex(x+(y+1)*width);			// 10
            
            mainMesh.addIndex((x+1)+y*width);			// 1
            mainMesh.addIndex((x+1)+(y+1)*width);		// 11
            mainMesh.addIndex(x+(y+1)*width);			// 10
        }
    }
    
    //cam.setScale(1,-1,1);
    //cam.setScale(0.5);
    
    extrusionAmount = 300.0;
    
    ofVec3f centre((RELIEF_SIZE_X*ratio)/2.f,(RELIEF_SIZE_Y*ratio)/2.f, 0);//255/2.f);
    easycam.setTarget (centre);
    
    easycam.rotate(90, easycam.getUpDir() );
    easycam.rotate(80, easycam.getSideDir());
    easycam.rotate(10, easycam.getUpDir() );
    
    
    easycam.dolly(10000);
    
    ofImage* equation1Img = new ofImage();
    equation1Img->loadImage("Math/assets/equation1-editing.png");
    
    ofImage* equation2Img = new ofImage();
    equation2Img->loadImage("Math/assets/equation2-editing.png");
    
    ofImage* equation3Img = new ofImage();
    equation3Img->loadImage("Math/assets/equation3-editing.png");
    
    ofImage* equation4Img = new ofImage();
    equation4Img->loadImage("Math/assets/equation4-editing.png");
    
    ofImage* equation5Img = new ofImage();
    equation5Img->loadImage("Math/assets/equation5-editing.png");
    
    images.push_back(equation1Img);
    images.push_back(equation2Img);
    images.push_back(equation3Img);
    images.push_back(equation4Img);
    images.push_back(equation5Img);
}

//--------------------------------------------------------------

ofColor fcolor(float y) {
    
}

//--------------------------------------------------------------

void Function::update(float dt) {
    anim.update(dt);
    //if(anim.isAnimating())
    for (int i = 0; i < RELIEF_SIZE_X; i++){
        for (int j = 0; j < RELIEF_SIZE_Y; j++){
            curr[i][j] = ofLerp(prev[i][j],next[i][j],anim.getCurrentValue());
        }
    }
    
    for(int i = 0; i< RELIEF_SIZE_X; i++){
        for(int j = 0; j<RELIEF_SIZE_Y; j++){
            float height = (curr[i][j] + 1.0f) / 2.0f * 256.0f;
            
            //  height = std::min(std::max(height,0.0f),250.0f);
            float hue = std::min(std::max(height,0.0f),250.0f);
            
            // height = ofMap(height, 0.0, 255.0, 0.0, 300.0);
            
            
            ofFloatColor sampleColor(ofColor::fromHsb(hue,255.0f,255.0f));
            
            ofVec3f tmpVec = mainMesh.getVertex(i+j*RELIEF_SIZE_X);
            
            tmpVec.z = height/4;
            //ofLog(OF_LOG_NOTICE, "something" + ofToString(height) );
            
            mainMesh.setVertex(i+j*RELIEF_SIZE_X, tmpVec);
            
            mainMesh.setColor(i+j*RELIEF_SIZE_X, sampleColor);
        }
    }
    
    float rotateAmount = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 360);
    
    //move the camera around the mesh
    ofVec3f camDirection(0,0,1);
    ofVec3f centre((RELIEF_SIZE_X*ratio)/2.f,(RELIEF_SIZE_Y*ratio)/2.f,255/2.f);
    ofVec3f camDirectionRotated = camDirection.rotated(rotateAmount, ofVec3f(1,0,0));
    ofVec3f camPosition = centre + camDirectionRotated*1.0;// * extrusionAmount;
    
    cam.setPosition(camPosition);
    cam.lookAt(centre);
}

//--------------------------------------------------------------

void Function::nextFunction(string t, int func) {
    if(t == "next"){
        currFunc = (currFunc + 1) % 5;
        eq_val2 = -6;
        eq_val1 = 8;
    } else if(t == "button"){
        currFunc = func;
        eq_val2 = -6;
        eq_val1 = 8;
    }
    
    float eq_val1_f = eq_val1*0.125;
    float eq_val2_f = eq_val2*0.125;
    
    for (int i = 0; i < RELIEF_SIZE_X; i++) {
        for (int j = 0; j < RELIEF_SIZE_Y; j++) {
            // Copy current to previous
            prev[i][j] = curr[i][j];
            
            float x = ((float)i - (float)(RELIEF_SIZE_X-1) / 2.0f) / ((float)(RELIEF_SIZE_X-1) / 2.0f);
            float y = ((float)j - (float)(RELIEF_SIZE_Y-1) / 2.0f) / ((float)(RELIEF_SIZE_Y-1) / 2.0f);
            switch (currFunc) {
                case 0: next[i][j] = (x*eq_val1_f) * (y*eq_val2_f); break;
                case 1: next[i][j] = std::sqrt(abs(4.0f - 2.0f*(x*eq_val1_f)*(x*eq_val1_f) - 2.0f*(y*eq_val2_f)*(y*eq_val2_f))) - 1.0f; break;
                case 2: next[i][j] = (x*eq_val1_f)*(x*eq_val1_f) - (y*eq_val2_f)*(y*eq_val2_f); break;
                case 3: next[i][j] = std::cos(8.0f * ((x*eq_val1_f)*(x*eq_val1_f) + (y*eq_val2_f)*(y*eq_val2_f))) * std::exp(-(x*eq_val1_f)*(x*eq_val1_f) - (y*eq_val2_f)*(y*eq_val2_f)); break;
                case 4: next[i][j] = ((x*eq_val1_f)*(y*eq_val2_f)*(y*eq_val2_f)*(y*eq_val2_f) - (y*eq_val2_f)*(x*eq_val1_f)*(x*eq_val1_f)*(x*eq_val1_f)) / 0.2f;
                default:
                    break;
            }
        }
    }
    
    anim.setDuration(0.5f);
    anim.setCurve(EASE_IN_EASE_OUT);
    anim.animateFromTo(0.0f,1.0f);

}

//--------------------------------------------------------------

void Vertex(int i, int j, float curr[RELIEF_SIZE_X][RELIEF_SIZE_Y], int w, int h) {
    float x = w * (RELIEF_SIZE_X - 1) * float(i) / (RELIEF_SIZE_X-1) / (RELIEF_SIZE_X-1); // (1920 - 840) = TOUCHSCREEN_VISIBLE_X
    float y = h * (RELIEF_SIZE_Y - 1) * float(j) / (RELIEF_SIZE_Y-1) / (RELIEF_SIZE_Y-1);// 1080 = TOUCHSCREEN_SIZE_Y
    
    float height = (curr[i][j] + 1.0f) / 2.0f * 256.0f;
    float hue = std::min(std::max(height,0.0f),250.0f);
    
    ofSetColor(ofColor::fromHsb(hue,255.0f,255.0f));
    glVertex3f(x,y,height - 256);
}

//--------------------------------------------------------------

void Function::drawHeightMap(int w, int h) {
    heightMapShader.begin();
    glPushMatrix();
    ofClear(0,0,0);
    glBegin(GL_TRIANGLES);
    for(int i = 0;i < RELIEF_SIZE_X-1;i++)
        for(int j = 0; j < RELIEF_SIZE_Y-1; j++)
        {
            Vertex(i,j,curr,w,h); Vertex(i+1,j,curr,w,h); Vertex(i,j+1,curr,w,h);
            Vertex(i+1,j,curr,w,h); Vertex(i,j+1,curr,w,h); Vertex(i+1,j+1,curr,w,h);
        }
    
    glEnd();
    glPopMatrix();
    heightMapShader.end();
}

//--------------------------------------------------------------

void Function::drawGraphics(int w, int h) {
    ofSetColor(this->color);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    
    for(int i = 0;i < RELIEF_SIZE_X-1;i++)
        for(int j = 0; j < RELIEF_SIZE_Y-1; j++)
        {
            Vertex(i,j,curr,w,h); Vertex(i+1,j,curr,w,h); Vertex(i,j+1,curr,w,h);
            Vertex(i+1,j,curr,w,h); Vertex(i,j+1,curr,w,h); Vertex(i+1,j+1,curr,w,h);
        }
    
    glEnd();
    glPopMatrix();
}

//--------------------------------------------------------------

void Function::drawEquation() {
    ofEnableDepthTest();
    easycam.begin();
    
    //You can either draw the mesh or the wireframe
    // mainMesh.drawWireframe();
    mainMesh.drawFaces();
    easycam.end();
    ofDisableDepthTest();
    
}

//--------------------------------------------------------------

void Function::adjustVar(int num, int change){
    if(num == 1){
        if(change == 1){
            eq_val1 += 1;
            if(eq_val1>=10){
                eq_val1 = 9;
            }
        } else {
            eq_val1 -= 1;
            if(eq_val1<=-10){
                eq_val1 = -9;
            }
        }
    } else if (num==2){
        if(change == 1){
            eq_val2 += 1;
            if(eq_val2>=10){
                eq_val2 = 9;
            }
        } else {
            eq_val2 -= 1;
            if(eq_val2<=-10){
                eq_val2 = -9;
            }
        }
    }
    nextFunction("modify", 0);
}

//--------------------------------------------------------------

void Function::setEqVal1(float val) {
    eq_val1 = val;
}

//--------------------------------------------------------------

void Function::setEqVal2(float val) {
    eq_val2 = val;
}

//--------------------------------------------------------------

string Function::getEqVal1(){
    return ofToString(eq_val1);
}

//--------------------------------------------------------------

string Function::getEqVal2(){
    return ofToString(eq_val2);
}

//--------------------------------------------------------------

string Function::getEq(){
    switch (currFunc) {
        case 0: return "_x * _y";
        case 1: return "√(2 - (_x)² - (_y)²)";
        case 2: return "(_x)² - (_y)²";
        case 3: return "cos((_x)² + (_y)²)*e^(-(_x)² - (_y)²)";
        case 4: return "_x * (_y)³ - _y * (_x)³";
        default:
            break;
    }
}

//--------------------------------------------------------------
vector<OffsetAndFont> Function::getVal1XOffsets() {
    vector<OffsetAndFont> offsets;
    OffsetAndFont off, off1, off2, off3, off3b, off4, off4b;
    switch (currFunc) {
        case 0:
            off = OffsetAndFont();
            off.offsetX = 118;
            
            offsets.push_back(off);
            break;
        case 1:
            off1 = OffsetAndFont();
            off1.offsetX = 260;
            
            offsets.push_back(off1);
            break;
        case 2:
            off2 = OffsetAndFont();
            off2.offsetX = 125;
            
            offsets.push_back(off2);
            break;
        case 3:
            off3 = OffsetAndFont();
            off3.offsetX = 205;
            off3b = OffsetAndFont();
            off3b.offsetX = 627;
            off3b.offsetY = -20;
            off3b.fontSizeOffset = -2;
            
            offsets.push_back(off3);
            offsets.push_back(off3b);
            break;
        case 4:
            off4 = OffsetAndFont();
            off4.offsetX = 120;
            off4b = OffsetAndFont();
            off4b.offsetX = 480;
            
            offsets.push_back(off4);
            offsets.push_back(off4b);
            break;
        default:
            break;
    }
    return offsets;
}

//--------------------------------------------------------------

vector<OffsetAndFont> Function::getVal2XOffsets() {
    vector<OffsetAndFont> offsets;
    OffsetAndFont off, off1, off2, off3, off3b, off4, off4b;
    switch (currFunc) {
        case 0:
            off = OffsetAndFont();
            off.offsetX = 250;
            
            offsets.push_back(off);
            break;
        case 1:
            off1 = OffsetAndFont();
            off1.offsetX = 490;
            
            offsets.push_back(off1);
            break;
        case 2:
            off2 = OffsetAndFont();
            off2.offsetX = 350;
            
            offsets.push_back(off2);
            break;
            break;
        case 3:
            off3 = OffsetAndFont();
            off3.offsetX = 405;
            off3b = OffsetAndFont();
            off3b.offsetX = 782;
            off3b.offsetY = -20;
            off3b.fontSizeOffset = -2;
            
            offsets.push_back(off3);
            offsets.push_back(off3b);
            break;
        case 4:
            off4 = OffsetAndFont();
            off4.offsetX = 255;
            off4b = OffsetAndFont();
            off4b.offsetX = 638;
            
            offsets.push_back(off4);
            offsets.push_back(off4b);
            break;
        default:
            break;
    }
    return offsets;
}

//--------------------------------------------------------------

ofImage* Function::getEqImage() {
    return images.at(currFunc);
}

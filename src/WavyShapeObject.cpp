//
//  WavyShapeObject.cpp
//  basicExample
//
//  Created by Tangible Media Group on 3/21/14.
//
//

#include "WavyShapeObject.h"

WavyShapeObject::WavyShapeObject() { }
WavyShapeObject::WavyShapeObject(float width, float height, float cellSize) {
    int w = (int)(width/cellSize);
    int h = (int)(height/cellSize);
    depthImageInput.allocate(width, height, OF_IMAGE_COLOR);

    //cout << "initalizing wavy with width, height: " << w << ", " << h << endl;
    
    //for pixel grabbing
    allPixels = new unsigned char[RELIEF_SIZE];
    
    init(w, h);
}

//--------------------------------------------------------------

WavyShapeObject::WavyShapeObject(int numCols, int numRows) {
    init(numCols, numRows);
}

//--------------------------------------------------------------

void WavyShapeObject::init(int numCols, int numRows) {
    cols = numCols;
    rows = numRows;
    
    editor.allocate(numCols, numRows);
    depthData.allocate(cols, rows);
    depthOutputFBO.allocate(KINECT_X, KINECT_Y, GL_RGB);
    
    friction = 0.8f;
    speed = 1.f;
    
    idleWaveScalar = 1;
    
    // allocate arrays and images
    surface.allocate(cols, rows, OF_IMAGE_GRAYSCALE);
    
    
    interpolate = 0;
    int maxInterpolation = 0;
    density = new float*[cols];
    velocity = new float*[cols];
    
    taylorSeries = new float**[cols];
    
    for (int x = 0; x < cols; x++) {
        density[x] = new float[rows];
        velocity[x] = new float[rows];
        
        taylorSeries[x] = new float*[rows];
        for (int y = 0; y < rows; y++)
            taylorSeries[x][y] = new float[maxInterpolation];
        
    }
    
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            density[x][y] = 0;
            velocity[x][y] = 0;
            for (int i = 0; i < maxInterpolation; i++)
                taylorSeries[x][y][i] = 0;
            
        }
    }
    
    // setup time keeping
    fixedDeltaMS = 18;
    leftOverMS = 0;
    
    seaLevel = 127;
    waveAmplitude = 1;
    waveScalar = 1;
    waveScalarSetTime = ofGetElapsedTimeMillis();
    destWaveScalar = 1;
    
    idleWaveAmplitude = 0; // 60
    idleWaveFrequency = 8;
    
    minX = 0;
    minY = 0;
    maxX = cols;
    maxY = rows;
    
    reset();
}

// resets all the depth and velocity values
// and all of the time keeping values
void WavyShapeObject::reset() {
    // add initial "jump" to show the waves work
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            float val = 0;
            if (x == cols/4 || x == cols*3/4)
                val = 500 * sin(1.5 * y * 2 * PI / rows);
            if (y == rows/4  || y == rows*3/4)
                val = 500 * sin(1.5 * x * 2 * PI / cols);
            
            density[x][y] = 0;
            velocity[x][y] = val;
        }
    }
    
    currentMS = ofGetElapsedTimeMillis();
    previousMS = currentMS;
    
}

//--------------------------------------------------------------

void WavyShapeObject::interpolateSurface() {
    //cout << "wave interpolating";
    if (ofGetElapsedTimeMillis() - lastInterpolatedMS < 10)
        return;
    
    lastInterpolatedMS = ofGetElapsedTimeMillis();
    
    waveScalar = ofLerp(waveScalar, destWaveScalar, ofClamp((ofGetElapsedTimeMillis() - waveScalarSetTime) / 1000.f, 0,1));
    
    long deltaMS = ofGetElapsedTimeMillis() - previousMS;
    
    float fraction = (float)((double)leftOverMS / (double)(fixedDeltaMS));
    
    
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            int i = x + y * cols;
            
            float val = depthMap.getColor(x, y).getBrightness() - mKinectTracker->mFarThreshold;
            //if (val > 5)
            //    surface.getPixelsRef()[i] = (val + 255) * 0.5f;
            //else {
                float interpolatedVelocity = velocity[x][y];
                float factorial = 1;
                
                // taylor series approximation of the velocity
                for (int i = 0; i < interpolate; i++) {
                    factorial *= (0.8f / ((float)i + 1.f));
                    
                    interpolatedVelocity += fraction * factorial * taylorSeries[x][y][i];
                }
                
                // move the "resting" pos to seaLevel
                surface.getPixelsRef()[i] = ofClamp(waveScalar * (waveAmplitude * interpolatedVelocity + seaLevel), 0, 255);
          //  }
        }
    }
    surface.reloadTexture();
    
}

//--------------------------------------------------------------

int WavyShapeObject::getCols() {
    return cols;
}

//--------------------------------------------------------------

int WavyShapeObject::getRows() {
    return rows;
}



//--------------------------------------------------------------

void WavyShapeObject::setSeaLevel(float level) {
    seaLevel = ofClamp(level, 0, 255);
}

//--------------------------------------------------------------

float WavyShapeObject::getSeaLevel() {
    return seaLevel;
}

//--------------------------------------------------------------

void WavyShapeObject::setWaveAmplitude(float amplitude) {
    waveAmplitude = amplitude;
}

//--------------------------------------------------------------

float WavyShapeObject::getWaveAmplitude() {
    return waveAmplitude;
}

//--------------------------------------------------------------

void WavyShapeObject::setWaveScalar(float scalar) {
    destWaveScalar = scalar;
    waveScalarSetTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------

float WavyShapeObject::getWaveScalar() {
    return waveScalar;
}

//--------------------------------------------------------------

void WavyShapeObject::setIdleWaveScalar(float scalar) {
    idleWaveScalar = scalar;
}

//--------------------------------------------------------------

void WavyShapeObject::renderTangibleShape(int w, int h) {
    //cout << "wave rendering " << waveScalar << ", " << waveAmplitude;
    //if (interpolate > 0)
    interpolateSurface();
    surface.draw(0,0, w,h);

}

//--------------------------------------------------------------
/*
unsigned char * WavyShapeObject::getHeightMapPixels() {
    interpolateSurface();
    return surface.getPixels();
}
*/

//--------------------------------------------------------------

void WavyShapeObject::renderProjectorOverlay(int w, int h) {
    
    // interpolation should be done during height map drawing
    interpolateSurface();

    //surface.draw(273, 178, 562, 586); //0,0, w,h);
    surface.draw(510, 242, 1065, 814); //0,0, w,h);
}


//--------------------------------------------------------------

void WavyShapeObject::renderTouchscreenGraphics(int w, int h) {
    interpolateSurface();
    surface.draw(w,0, -w,h);
}

//--------------------------------------------------------------

void WavyShapeObject::update() {
    //cout << "wave updating";
    
    getDepthMapKinect();

//    idleWaves();
    
    currentMS = ofGetElapsedTimeMillis();
    long deltaMS = currentMS - previousMS;
    previousMS = currentMS; // reset previousTime
    
    int timestepCount = (int)((float)(deltaMS + leftOverMS) / (float)fixedDeltaMS);
    
    leftOverMS += (int)(deltaMS - (timestepCount * fixedDeltaMS));
    
    timestepCount = 1; //ofClamp(timestepCount, 0, 5); // limit to 5 so nothing freezes
    
    for (int t = 0; t < timestepCount; t++) {
        
        for (int x = minX; x < maxX; x++) {
            for (int y = minY; y < maxY; y++) {
                for (int i = interpolate-1; i >= 1; i--)
                    taylorSeries[x][y][i] = taylorSeries[x][y][i-1];
                if (interpolate > 0)
                    taylorSeries[x][y][0] = velocity[x][y];
            }
        }
        
        for (int i = 0; i < solveCount; i++)
            solveFluid();
        
        for (int x = minX; x < maxX; x++) {
            for (int y = minY; y < maxY; y++) {
                if (interpolate > 0)
                    taylorSeries[x][y][0] = velocity[x][y] - taylorSeries[x][y][0];
                for (int i = 1; i < interpolate; i++)
                    taylorSeries[x][y][i] = taylorSeries[x][y][i-1] - taylorSeries[x][y][i];
            }
        }
        
        for (int x = 0; x < depthMap.getWidth(); x++) {
            for (int y = 0; y < depthMap.getHeight(); y++) {
                // not sure why, but x and y is swapped for the depth map here
                
                float val = depthMap.getColor(x, y).getBrightness() - mKinectTracker->mFarThreshold;
                
                if (val != val)
                    val = 0; // avoid NaNs
                
                density[x][y] -= val * 2.f;
            }
        }
        
    }
    
    
    //    for (int i = 0; i < surface.getPixelsRef().size(); i++) {
    //        int x = i / cols;
    //        int y = i % cols;
    //
    //
    //        float val = 0; //depthMap.getColor(y, x).getBrightness();
    //
    //        if (val > 5)
    //            surface.getPixelsRef()[i] = (val + 255) * 0.5f;
    //        else // raise the fluid a bit and scale it by 0.5
    //            surface.getPixelsRef()[i] = ofClamp(velocity[y][x] + 127.f, 0, 255);
    //
    //    }
    //    surface.reloadTexture();
}

//--------------------------------------------------------------

void WavyShapeObject::solveFluid() {
    double densityAvg = 0;
    
    for (int x = minX; x < maxX; x++) {
        for (int y = minY; y < maxY; y++) {
            velocity[x][y] = friction * velocity[x][y] + (getAdjacentDensitySum(x,y) - (density[x][y] * 4)) * 0.1f;
            
            // no matter what I use for dt, speed would be bwar adjusted so this quantity = 0.1:         // * dt * 0.5f * speed;
            density[x][y] = density[x][y] + velocity[x][y];
        }
    }
    
    // solve again but backwards so it doesn't "pull" toward the top left quadrant
    for (int x = maxX-1; x >= minX; x--) {
        for (int y = maxY-1; y >= minY; y--) {
            velocity[x][y] = friction * velocity[x][y] + (getAdjacentDensitySum(x,y) - (density[x][y] * 4)) * 0.1f; // * dt * 0.5f * speed;
            density[x][y] = density[x][y] + velocity[x][y];
            
            densityAvg += density[x][y];
        }
    }
    
    densityAvg /= (maxX-minX) * (maxY-minY);
    
    // we "center" the density of every cell
    // so that no out-of-range values occur after long intervals of execution
    for (int x = minX; x < maxX; x++) {
        for (int y = minY; y < maxY; y++) {
            density[x][y] -= densityAvg;
        }
    }
}

//--------------------------------------------------------------

float WavyShapeObject::getAdjacentDensitySum(int x, int y) {
    float sum = 0;
    
    if (x-1 >= minX)
        sum += density[x-1][y];
    else
        sum += density[minX][y];
    
    if (x+1 < maxX)
        sum += density[x+1][y];
    else
        sum += density[maxX-1][y];
    
    if (y-1 >= minY)
        sum += density[x][y-1];
    else
        sum += density[x][minY];
    
    if (y+1 < maxY)
        sum += density[x][y+1];
    else
        sum += density[x][maxY-1];
    
    return sum;
}

//--------------------------------------------------------------

// @note if kinectTracker exposed native ofKinect object we could use
// getDepthPixels() method to eliminate this code
// we should either expose kinect OR add method for this to kinectTracker class
void WavyShapeObject::getDepthMapKinect(){
    depthData.begin();
    ofBackground(0);
    // kinect depthThresholdImage
    //depthImageInput.draw(0, 0, cols, rows);
//    mKinectTracker->drawDepthThreshedDiff(0, 0, cols, rows);
    mKinectTracker->drawThresholdImage(0, 0, cols, rows);
    
    // show heartbeat
    //if (useHeartbeat) mHeartbeatShapeObject->getDepthMap(35, 21);
    editor.draw(0,0, cols, rows);

    depthData.end();
    depthData.readToPixels(depthMap);
    
    editor.begin();
    ofBackground(0,0,0,0);
    editor.end();
}

//--------------------------------------------------------------

void WavyShapeObject::setTableValuesForShape(ShapeIOManager *pIOManager) {
    pIOManager->set_max_speed(200);
    pIOManager->set_gain_p(1.5f);
    pIOManager->set_gain_i(0.045f);
    pIOManager->set_max_i(25);
    pIOManager->set_deadzone(2);
}

unsigned char* WavyShapeObject::getPixels()
{
    return allPixels;
}

//--------------------------------------------------------------

void WavyShapeObject::beginEdit() {
    editor.begin();
}
void WavyShapeObject::endEdit() {
    editor.end();
}

void WavyShapeObject::idleWaves() {
    for (int i = 0; i < cols; i++) {
        velocity[i][minY] = idleWaveScalar * idleWaveScalar * idleWaveAmplitude * sin(ofGetElapsedTimeMillis() * idleWaveFrequency / 1000.f + i * 0.75);
        velocity[i][maxY-1] = idleWaveScalar * idleWaveScalar * idleWaveAmplitude * cos(ofGetElapsedTimeMillis() * -idleWaveFrequency / 1000.f * 0.5 + i);
    }
}

/*
 *  ReliefIOManager.cpp
 *  Relief
 *
 *  Created by Daniel Leithinger on 3/3/10.
 *  Copyright 2010 MIT Media Lab. All rights reserved.
 *
 */

#include "ShapeIOManager.h"

//--------------------------------------------------------------
//
// Create new shapeIOManager class
//
// loads settings, but you must manually connect / disconnect
// from the table.
//
//--------------------------------------------------------------
ShapeIOManager::ShapeIOManager() {
    setBoardConfiguration();
    mUseSerial = false;
    
    resetInterval = PID_RESET_INTERVALL; // milliseconds to reset table
    startTime = ofGetElapsedTimeMillis();
	
    tableValuesHaveChanged = false;
    
    // initialize table chart values
    for (int x = 0; x < RELIEF_SIZE_X; x++) {
        for (int y = 0; y < RELIEF_SIZE_Y; y++) {
            pinHeightToRelief[x][y] = 0;
            pinHeightFromRelief[x][y] = 0;
            pinDiscrepancy[x][y] = 0;
            pinStuckSinceTime[x][y] = startTime;
            pinEnabled[x][y] = true;
        }
    }
}

//--------------------------------------------------------------
//
// Destroy
//
//--------------------------------------------------------------
ShapeIOManager::~ShapeIOManager() {
    disconnectFromTable();
}

//--------------------------------------------------------------
//
// Connects to table, which opens serial connection to boards
// and sets global variable, which effects many
// other functions within class
//
//--------------------------------------------------------------
void ShapeIOManager::connectToTable() {
    if(mUseSerial == true) return;
    openSerialConnections();
    mUseSerial = true;
}

//--------------------------------------------------------------
//
// Disconnects from table the proper way
//
// resets pins heights to 0,
// sets boards to "off",
// and then closes the serial connection.
//
// @note should be called when exiting the app
//
//--------------------------------------------------------------
void ShapeIOManager::disconnectFromTable() {
    if(mUseSerial == false) return;
    resetPinsToValue(0);
    ofSleepMillis(1000);
    sendValueToAllBoards(TERM_ID_MAXSPEED, (unsigned char) 0); // effectively "turns off" pins by setting speed to 0
    mUseSerial = false; // stops commands to serial from writing, effectively stops app from overriding manager
    ofSleepMillis(1000);
    closeSerialConnections();
}

void ShapeIOManager::disconnectFromTableWithoutPinReset(){
    if(mUseSerial == false) return;
    ofSleepMillis(1000);
    sendValueToAllBoards(TERM_ID_MAXSPEED, (unsigned char) 0); // effectively "turns off" pins by setting speed to 0
    mUseSerial = false; // stops commands to serial from writing, effectively stops app from overriding manager
    ofSleepMillis(1000);
    closeSerialConnections();
}

//--------------------------------------------------------------
//
// Opens serial connection and stores that connection in array
// delete the array value to later close the connection
//
//--------------------------------------------------------------
void ShapeIOManager::openSerialConnections() {
    mSerialConnections[0] = new ShapeSerial(SERIAL_PORT_0, SERIAL_BAUD_RATE);
    mSerialConnections[1] = new ShapeSerial(SERIAL_PORT_1, SERIAL_BAUD_RATE);
    mSerialConnections[2] = new ShapeSerial(SERIAL_PORT_2, SERIAL_BAUD_RATE);
}

//--------------------------------------------------------------
//
// Close all serial connections to the table
//
//--------------------------------------------------------------
void ShapeIOManager::closeSerialConnections() {
    for (int i = 0; i < NUM_SERIAL_CONNECTIONS; i++) {
        delete mSerialConnections[i];
    }
}

//--------------------------------------------------------------
//
// Sets all pins to given value
//
// @note pin heights will be adjusted to be within clipping range
// regardless of value set
//
//--------------------------------------------------------------
void ShapeIOManager::resetPinsToValue(int value) {
    for (int i = 0; i < RELIEF_SIZE_X; i ++) {
		for (int j = 0; j < RELIEF_SIZE_Y; j ++) {
			pinHeightToRelief[i][j] = value;
		}
    }
    sendPinHeightToRelief();
}


//--------------------------------------------------------------
//
// Clips all values to be within range
//
//--------------------------------------------------------------
void ShapeIOManager::clipAllValuesToBeWithinRange() {
    for (int i = 0; i < RELIEF_SIZE_X; i ++) {
		for (int j = 0; j < RELIEF_SIZE_Y; j ++) {
            // rescale the values rather than clip them > this is broken right now!
            //pinHeightToRelief[i][j] = (255 * (pinHeightToRelief[i][j] - LOW_THRESHOLD)) / (HIGH_THRESHOLD - LOW_THRESHOLD);
			
            if (pinHeightToRelief[i][j] <= LOW_THRESHOLD) {
				pinHeightToRelief[i][j] = (unsigned char) LOW_THRESHOLD;
			}
			else if (pinHeightToRelief[i][j] >= HIGH_THRESHOLD) {
				pinHeightToRelief[i][j] = (unsigned char) HIGH_THRESHOLD;
			}
		}
    }
    
    // print the values;
    /*for (int j = 0; j < RELIEF_PHYSICAL_SIZE_Y; j ++) {
        for (int i = 0; i < RELIEF_PHYSICAL_SIZE_X; i ++) {
            cout << (int)(pinHeightToRelief[i][j]) << " ";
        }
        cout << endl;
    }
    cout << endl;*/
}


//--------------------------------------------------------------
//
// Given multiarray of values, sends all values to the table
//
//--------------------------------------------------------------
void ShapeIOManager::sendPinHeightToRelief() {
    if(mUseSerial == false) return;
    clipAllValuesToBeWithinRange();
    prepDepthDataForArduino();
    for (unsigned char i = 0; i < NUM_ARDUINOS; i++) {
        sendValuesToBoard(TERM_ID_HEIGHT, i + 1, reliefBoardValues[i].currentFramePinHeight, reliefBoardValues[i].serialConnection);
    }
}

//--------------------------------------------------------------
//
// Given multiarray of values, sends all values to the table AND recieves
// communication about current pin height
//
//--------------------------------------------------------------
void ShapeIOManager::sendAndReceivePinHeight() {
    
    if(mUseSerial == false) return;
    
    clipAllValuesToBeWithinRange();
    prepDepthDataForArduino();
    for (unsigned char i = 0; i < NUM_ARDUINOS; i++) {
        sendHeightToBoardAndRequestFeedback(i + 1, reliefBoardValues[i].currentFramePinHeight, reliefBoardValues[i].serialConnection);
    }
    readPinHeightsFromBoards(); // gets actual pin heights from arduino boards
}

//-----------------------------------------------------------
//
// gets pin height
//
//-----------------------------------------------------------
void ShapeIOManager::update(ofFbo buffer){
    
    unsigned char* pixels;
    ofPixels tempPixels;
    buffer.readToPixels(tempPixels);
    
    
    // Rotate and mirror the image to align the physical shape display orientation with the coordinate system of our program
    tempPixels.rotate90(1);
    tempPixels.mirror(true, false);
    pixels = tempPixels.getPixels();
    
    // it is necessary to remap the pin size from the physical area to the actual number of pins,
    // as the table has 3 separate blocks of actuators, which are spaced apart from each other
    for (int i = 0; i < RELIEF_PHYSICAL_SIZE_X; i ++) {
        for (int j = 0; j < RELIEF_PHYSICAL_SIZE_Y; j ++) {
            pinHeightToRelief[i][j] = pixels[((i + (j * RELIEF_PHYSICAL_SIZE_X)) * 4)];
        }
    }
    
    computePinDiscrepancy();
    
    // send the height map to the hardware interface
    sendAndReceivePinHeight();
    
    if(ofGetElapsedTimeMillis() >= startTime + resetInterval) {
        //cout << "RESETTING TABLE VALUES" << endl;
        startTime = ofGetElapsedTimeMillis();
        sendAllValuesToTable();
    } else {
        if(tableValuesHaveChanged) {
            sendAllValuesToTable();
            tableValuesHaveChanged = false;
            //cout << "VALUES HAVE CHANGED, updating table" << endl;
        }
    }
}


//--------------------------------------------------------------
//
// Copy data from data structure of image (2 dimensional array)
// to that of ardunios AND then flip the values where needed
// to match arduinos configuration
//
//--------------------------------------------------------------
void ShapeIOManager::prepDepthDataForArduino() {
    for (unsigned char i = 0; i < NUM_ARDUINOS; i++) { // iterate through each board
        for (int j = 0; j < NUM_PINS_ARDUINO; j++) {
            
            // copy the height values from the current frame values to the arduino pins
            reliefBoardValues[i].currentFramePinHeight[j] =     pinHeightToRelief[reliefBoardValues[i].pinCoordinates[j][0]][reliefBoardValues[i].pinCoordinates[j][1]];
            
            // invert the values if needed (this affects boards mounted upside down)
            if (reliefBoardValues[i].invertHeight) reliefBoardValues[i].currentFramePinHeight[j] = 255 - reliefBoardValues[i].currentFramePinHeight[j];
        }
    }
}


//--------------------------------------------------------------
//
// Reads actual pin heights from the boards
//
//--------------------------------------------------------------
void ShapeIOManager::readPinHeightsFromBoards() {
    // receive the pin heights from the table
    for (int i= 0; i< NUM_SERIAL_CONNECTIONS; i++) {
        while(mSerialConnections[i]->hasNewMessage()) {
            unsigned char messageContent[MSGS_SIZE_RECEIVE];
            mSerialConnections[i]->readMessage(messageContent);
            if(messageContent[0] == 253) {
                int boardAddress = messageContent[1] - 1;
                if (boardAddress >= 0 && boardAddress <= NUM_ARDUINOS) {
                    for (int j = 0; j < 6; j++) {
                        int height = messageContent[j+2];
                        if (reliefBoardValues[boardAddress].invertHeight) height = 255 - height;
                        
                        if (height >= 0 && height <= 255) {
                            int x = reliefBoardValues[boardAddress].pinCoordinates[j][0];
                            int y = reliefBoardValues[boardAddress].pinCoordinates[j][1];
                            pinHeightFromRelief[x][y] = height;
                        }
                    }
                }
            }
        }
    }
}

//
void ShapeIOManager::computePinDiscrepancy(){
    //int pinStuckSinceTime[RELIEF_SIZE_X][RELIEF_SIZE_Y];
    //bool pinEnabled[RELIEF_SIZE_X][RELIEF_SIZE_Y];
    //const int discrepancyThreshold = 20;
    //const int millisUntilPinOff = 1000;
    //const int millisUntilPinOn = 2000;
    
    unsigned long long timeStamp = ofGetElapsedTimeMillis();
    
    // draw the table depth map:
    for (int x = 0; x < RELIEF_SIZE_X; x++){
        for (int y = 0; y < RELIEF_SIZE_Y; y++) {
            int toHeight = pinHeightToRelief[x][y];
            int fromHeight = pinHeightFromRelief[x][y];
            pinDiscrepancy[x][y] = abs(toHeight - fromHeight);
            
            if (pinEnabled[x][y]) { // check if the pin is enabled.
                if(pinDiscrepancy[x][y] < discrepancyThreshold) { // if it is, check if it is reaching the target position
                    pinStuckSinceTime[x][y] = timeStamp; // if it has reached within threshold, update the time stamp
                }
                else { // if it has not reached, check how long it's been stuck for
                    if (timeStamp - pinStuckSinceTime[x][y] > millisUntilPinOff) {
                        // check if it exceeds the threshold for how long a pin can be stuck
                        pinEnabled[x][y] = false; // if so, disable the pin
                        pinStuckSinceTime[x][y] = timeStamp; // and store when we disabled it
                    }
                }
            }
            else { // if the pin is disabled, check if we should enable it again
                if (timeStamp - pinStuckSinceTime[x][y] > millisUntilPinOn) {
                    pinEnabled[x][y] = true;
                    pinStuckSinceTime[x][y] = timeStamp;
                } else { // if the time limit has not been reached yet, just overwrite the target position
                    pinHeightToRelief[x][y] = pinHeightFromRelief[x][y];
                }
            }
        }
    }
    
    
}


//--------------------------------------------------------------
//
// 8 byte and 10 byte versions of the same thing
// when recieving information from the kinect, we need a 10 byte
// message, compared to 8 when sending only.
//
//--------------------------------------------------------------

// 10 byte
void ShapeIOManager::sendHeightToBoardAndRequestFeedback(unsigned char boardId, unsigned char value[NUM_PINS_ARDUINO], int serialConnection) {
    unsigned char messageContents[10];
    messageContents[0] = TERM_ID_HEIGHT_FEEDBACK;
    messageContents[1] = boardId;
    for (int j = 0; j < NUM_PINS_ARDUINO; j++) {
        messageContents[j + 2] = value[j];
    }
    // xtra bytes!
    messageContents[8] = 255;
    messageContents[9] = 255;
    
    if(mUseSerial) {
        mSerialConnections[serialConnection]->writeMessageRequestFeedback(messageContents);
    }
}

// 8 byte
void ShapeIOManager::sendValuesToBoard(unsigned char termId, unsigned char boardId, unsigned char value[NUM_PINS_ARDUINO], int serialConnection) {
    unsigned char messageContents[8];
    messageContents[0] = termId;
    messageContents[1] = boardId;
    for (int j = 0; j < NUM_PINS_ARDUINO; j++) {
        messageContents[j + 2] = value[j];
    }
    if(mUseSerial) {
        mSerialConnections[serialConnection]->writeMessage(messageContents);
    }
}


//--------------------------------------------------------------
//
// Send a value to all boards, givin term id and term value
//
//--------------------------------------------------------------
void ShapeIOManager::sendValueToAllBoards(unsigned char termId, unsigned char value) {
    
    unsigned char messageContents[8];
    messageContents[0] = (unsigned char) termId;
    messageContents[1] = (unsigned char) 0;
    for (int i = 0; i < NUM_PINS_ARDUINO; i++) {
        messageContents[i + 2] = (unsigned char) value;
    }
    
    if(mUseSerial) {
        for (int i = 0; i < NUM_SERIAL_CONNECTIONS; i ++) {
            mSerialConnections[i]->writeMessage(messageContents);
        }
    }
}


//--------------------------------------------------------------
//
// Setters for table config
//
//--------------------------------------------------------------
void ShapeIOManager::set_gain_p(float value){
    if(value != _gain_P) tableValuesHaveChanged = true;
    _gain_P = value;
    //sendValueToAllBoards(TERM_ID_GAIN_P, (unsigned char) (_gain_P * 25));
}

void ShapeIOManager::set_gain_i(float value){
    if(value != _gain_I) tableValuesHaveChanged = true;
    _gain_I = value;
    //sendValueToAllBoards(TERM_ID_GAIN_I, (unsigned char) (_gain_I * 100));
}

void ShapeIOManager::set_max_i(int value){
    if(value != _max_I) tableValuesHaveChanged = true;
    _max_I = value;
    //sendValueToAllBoards(TERM_ID_MAX_I, (unsigned char)_max_I);
}

void ShapeIOManager::set_deadzone(int value){
    if(value != _deadZone) tableValuesHaveChanged = true;
    _deadZone = value;
    //sendValueToAllBoards(TERM_ID_DEADZONE, (unsigned char)_deadZone);
}

void ShapeIOManager::set_max_speed(int value){
    if(value != _maxSpeed) tableValuesHaveChanged = true;
    _maxSpeed = value;
    //sendValueToAllBoards(TERM_ID_MAXSPEED, (unsigned char)(_maxSpeed/2));
}

//--------------------------------------------------------------
//
// Sends all current table config vars to the table
//
// this method should be called periodically to reset the table and fix
// pins that appear broken (but really have invalid values that have
// changed over time because of firmware issues or connection noise)
//
//--------------------------------------------------------------
void ShapeIOManager::sendAllValuesToTable() {
    sendValueToAllBoards(TERM_ID_GAIN_P, (unsigned char) (_gain_P * 25));
    sendValueToAllBoards(TERM_ID_GAIN_I, (unsigned char) (_gain_I * 100));
    sendValueToAllBoards(TERM_ID_MAX_I, (unsigned char)_max_I);
    sendValueToAllBoards(TERM_ID_DEADZONE, (unsigned char)_deadZone);
    sendValueToAllBoards(TERM_ID_MAXSPEED, (unsigned char)(_maxSpeed/2));
}

void ShapeIOManager::snycValuesToTable() {
    sendAllValuesToTable();
}


//--------------------------------------------------------------
//
// Custom function per installation to setup table.
//
// @todo this should be within the reliefApp???
//
//--------------------------------------------------------------
void ShapeIOManager::setBoardConfiguration() {
    
    int rowOrder[24] = {0, 2, 1, 3, 5, 4, 6, 8, 7, 9, 11, 10, 12, 14, 13, 15, 17, 16, 18, 20, 19, 21, 23, 22};
    
    // set up coordinates for 
    for (int i = 0; i < NUM_ARDUINOS; i++) {
        int currentRow = (int)(i/4);
        currentRow = (rowOrder[currentRow]);
        
        // one every module, the modules on the second row
        // are mounted upside down, so invert the height
        reliefBoardValues[i].invertHeight = ((currentRow%3) == 2)? true : false;
        
        for (int j = 0; j < NUM_PINS_ARDUINO; j++) {
            int currentColumn = ((i%4) * NUM_PINS_ARDUINO) + j;
            reliefBoardValues[i].lastFramePinHeight[j] = 0;
            reliefBoardValues[i].currentFramePinHeight[j] = 0;
            reliefBoardValues[i].rollingAverageHeight[j] = 0;
            reliefBoardValues[i].pinIsIdle[j] = true;
            reliefBoardValues[i].pinCoordinates[j][0] = currentRow;
            reliefBoardValues[i].pinCoordinates[j][1] = currentColumn;
        }
        
        if(i < 36) {
            reliefBoardValues[i].serialConnection = 0;
        }
        else if (i < 60) {
            reliefBoardValues[i].serialConnection = 1;
        }
        else {
            reliefBoardValues[i].serialConnection = 2;
        }
        
        int pinCoordinateRows[NUM_PINS_ARDUINO];
        // invert pin order if the boards are mounted rotated
        for (int count = 0; count < NUM_PINS_ARDUINO; count++){
                pinCoordinateRows[NUM_PINS_ARDUINO - count - 1] = reliefBoardValues[i].pinCoordinates[count][1];
        }
        for (int count = 0; count < NUM_PINS_ARDUINO; count++){
            reliefBoardValues[i].pinCoordinates[count][1] = pinCoordinateRows[count];
        }
    }
    
    // print out the mapping
    for (int i = 0; i < NUM_ARDUINOS; i++) {
        
        printf("board: %d: ", i);
        for (int j = 0; j < NUM_PINS_ARDUINO; j++) {
            printf("%d,%d(%d); ", reliefBoardValues[i].pinCoordinates[j][0], reliefBoardValues[i].pinCoordinates[j][1], reliefBoardValues[i].invertHeight);
        }
        printf("\n");
    }
}
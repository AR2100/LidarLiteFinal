#include "mbed.h"
#include "LidarLiteController.h"

/* This static array must be declared outside of the header file to  
 *  avoid a linker error.
 */
LidarLite LidarLiteController::lidars[3];
int LidarLiteController::rawDistanceArr[3];

LidarLiteController::LidarLiteController() {
        
        lidars[0].setupLidar(0x12, PinName(p17), "left LidarLite");
        lidars[1].setupLidar(0x22, PinName(p18), "center LidarLite");
        lidars[2].setupLidar(0x32, PinName(p19), "right LidarLite"); 
}

int * LidarLiteController::getRawDistances(Serial *pcPtr, DigitalOut * lidarEnablePins){
    
    /* IMPORTANT!
     * When testing 3 LidarLites, be sure to change this loop!
     *
     * Attempt to call getDistance().
     *  If getDistance() fails for a particular LidarLite, we try to reset it.
     */
    for (int i = 0; i < 1; i++) {
        
        int distance = lidars[i].getDistance();
        rawDistanceArr[i] = distance;
        
        if (distance == -1) {
            
            pcPtr -> printf("Lost connection with the %s. Attempting to reset...\r\n", lidars[i].getName().c_str());
            
            bool resetSuccess = lidars[i].reset();
            
            if (resetSuccess) {
                pcPtr -> printf("Reset successful!\r\n");    
            } else {
                pcPtr -> printf("Reset failed! Will retry in 5 seconds...\r\n");
            }
        } 
    }
    
    return rawDistanceArr;
}

void LidarLiteController::enableAll() {
    for (int i = 0; i < 3; i++) {
        lidars[i].enable();    
    }
}

void LidarLiteController::disableAll() {
    for (int i = 0; i < 3; i++) {
        lidars[i].disable();    
    }
}
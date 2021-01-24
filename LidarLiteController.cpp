#include "mbed.h"
#include "LidarLiteController.h"

/* This static array must be declared outside of the header file to  
 *  avoid a linker error.
 */
LidarLite LidarLiteController::lidars[3];
int LidarLiteController::rawDistanceArr[3];

LidarLiteController::LidarLiteController() {
        
        /* Set all of the enable pins first. This disables all of the 
         *  LidarLites.
         * Then, we will enable the LidarLites, one at a time, assigning the
         *  custom I2C addresses.
         */
        lidars[0].setEnablePin(PinName(p17));
        lidars[1].setEnablePin(PinName(p18));
        lidars[2].setEnablePin(PinName(p19));
        
        lidars[0].setupLidar(0x12, "left LidarLite");
        lidars[1].setupLidar(0x22, "center LidarLite");
        lidars[2].setupLidar(0x32, "right LidarLite"); 
}

int * LidarLiteController::getRawDistances(Serial *pcPtr, DigitalOut * lidarEnablePins){
    
    /* IMPORTANT!
     * When testing 3 LidarLites, be sure to change this loop!
     *
     * Attempt to call getDistance().
     *  If getDistance() fails for a particular LidarLite, we try to reset it.
     */
    for (int i = 0; i < 3; i++) {
        
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
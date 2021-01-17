#include "mbed.h"
#include "LidarLite.h"
#include "LidarLiteController.h"
#include <sstream>
#include <iostream>

using namespace std;

Serial pc(USBTX, USBRX);
DigitalOut lidarEnablePins[3] = {DigitalOut(p17), DigitalOut(p18), DigitalOut(p19)};

int main() {
    #if 1
    pc.printf("\r\n~~~~~~~~~~~~~~~~~~~~~~~~ \r\n");
    pc.printf("Start: \r\n");
    pc.printf("\r\n~~~~~~~~~~~~~~~~~~~~~~~~ \r\n");
    
    //Initialize the three LidarLites
    LidarLiteController::LidarLiteController();
    
    while (true) {
        
        int* arr = LidarLiteController::getRawDistances(&pc, lidarEnablePins);
        
        pc.printf("val: %d \r\n", arr[0]);
        wait(0.1);
    }
    
    #endif
    
    #if 0
    
    /* 
     *Below code is working 
     *   without LidarLiteController.cpp and LidarLiteController.h
     */
    
    pc.printf("\r\n~~~~~~~~~~~~~~~~~~~~~~~~ \r\n");
    pc.printf("Start: \r\n");
    
    /*
     * Old setup
        PinName enablePinName(p17);
        LidarLite lidar1 = LidarLite(0x42, enablePinName);
     */
    
    LidarLite lidar1 = LidarLite();
    lidar1.setupLidar(0x42, &DigitalOut(p17));
    
    pc.printf("~~~~~~~~~~~~~~~~~~~~~~~~ \r\n");
    
    char serial_number[1];
    serial_number[0] = 0x00;
    
    //lidar1.changeI2CAddress(0x62, 0x42);
    
    lidar1.read(0x02, serial_number, 1, 0x42, false);
    pc.printf("register 0x02: %x \r\n", serial_number[0]);
    
    int distance = -1;
    
    int count = 0;
    
    while (count < 20) {
        distance = lidar1.getDistance(true);
        
        pc.printf("val: %d \r\n", distance);
        
        count++;
        wait(0.1);
    }
    
    lidar1.disable();
    
    #endif
}

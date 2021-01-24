#include "mbed.h"
#include "LidarLite.h"
#include "LidarLiteController.h"
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
        
        pc.printf("left %d : center %d : right %d \r\n", arr[0], arr[1], arr[2]);
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
    
    // *** Lidar 1 *** 
    LidarLite lidar1 = LidarLite();
    
    lidar1.setEnablePin(PinName(p17));
    lidar1.setupLidar(0x42, "left lidar");
    lidar1.enable();
    
    bool res1 = lidar1.changeI2CAddress(0x62, 0x42);
    bool res2 = lidar1.setLidarSettings();
    
    pc.printf("changeI2CAddress: %d \r\n", res1);
    pc.printf("setLidarSettings: %d \r\n", res2);
    
    //*** Lidar 2 ***
    
    LidarLite lidar2 = LidarLite();
    
    lidar2.setEnablePin(PinName(p18));
    lidar2.setupLidar(0x52, "center lidar");
    lidar2.enable();
    
    bool res3 = lidar2.changeI2CAddress(0x62, 0x52);
    bool res4 = lidar2.setLidarSettings();
    
    pc.printf("changeI2CAddress: %d \r\n", res3);
    pc.printf("setLidarSettings: %d \r\n", res4);
    
    pc.printf("~~~~~~~~~~~~~~~~~~~~~~~~ \r\n");
    
    char dataArr[1];
    unsigned char defAddr = 0x62;
    dataArr[0] = 0x08;
    
    char serial_number[1];
    serial_number[0] = 0x69;
    
    lidar1.read(0x02, serial_number, 1, 0x42);
    pc.printf("register 0x02, lidar1: %x \r\n", serial_number[0]);
    
    lidar2.read(0x02, serial_number, 1, 0x52);
    pc.printf("register 0x02, lidar2: %x \r\n", serial_number[0]);
    
    //char addr = lidar1.readI2CAddress(defaultAddr);
    //pc.printf("LidarLite Address: %x \r\n", addr);
    
    int distance1 = -1;
    int distance2 = -1;
    
    int count = 0;
    
    while (count < 20) {
        distance1 = lidar1.getDistance();
        distance2 = lidar2.getDistance();
        
        pc.printf("lidar1: %d, lidar2 %d \r\n", distance1, distance2);
        
        count++;
        wait(0.1);
    }
    
    lidar1.disable();
    
    #endif
}

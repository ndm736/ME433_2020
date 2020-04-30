#include "imu.h"

void imu_setup(){
    unsigned char who = 0;

    // read from IMU_WHOAMI
    
    if (who != 0b01101001){
        while(1){}
    }

    // init IMU_CTRL1_XL
    
    // init IMU_CTRL2_G

    // init IMU_CTRL3_C

}

void imu_read(unsigned char reg, signed short * data, int len){
    
    // read multiple from the imu, each data takes 2 reads so you need len*2 chars
    
    // turn the chars into the shorts
    
}
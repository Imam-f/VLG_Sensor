/**
 * adopted from
 * CMPS03 by: Aarom Berk
 * 
 * Bismillahirahmanirrahim
 */

#ifndef CMPS_KRAI_H
#define CMPS_KRAI_H

/**
 * Includes
 */
#include "mbed.h"

#define CMPS_DEFAULT_I2C_ADDRESS 0xC0
//set register kompas
#define SOFTWARE_REVISION_REG    0x0
#define COMPASS_BEARING_WORD_REG 0x2
#define CMPS12_CALIBRATION_STATE_REG 0x1E

#define SYSTEM_STATE 3
#define GYRO_STATE 2
#define ACCEL_STATE 1
#define MAG_STATE 0


//Inisiasi I2C komunikasi dari kompas
class CMPS_KRAI {

    I2C* i2c;
    int  i2cAddress;

public:

    /**
     * Constructor.
     *
     * @param sda mbed pin to use for I2C SDA
     * @param scl mbed pin to use for I2C SCL
     * @param address I2C address of this device.
     */
    CMPS_KRAI(PinName sda, PinName scl, int address);

    /**
     * Membaca revisi dari kompas
     */
    char readSoftwareRevision(void);

    /**
     * Membaca nilai dari kompas
     * Range nilai 0 - 3599
     */
    int readBearing(void);

    /**
     * Kalibrasi kompas  
     */
    void calibrate(void);

    /**
     * Stop calibrate
     */
    void stopCalibrate(void);
    
//    Menghapus calibration profile
    void eraseProfile();
    
    // Cek status kalibrasi
    int state(int sys);
};

#endif /* CMPS_KRAI_H */

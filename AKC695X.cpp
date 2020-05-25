#include <AKC695X.h>



/**
 * @brief Sets the I2C bus device address 
 * @details You do not need use this function if your i2c device address is 0x10 (default value)  
 * 
 * @param deviceAddress 
 */
void AKC695X::setI2CBusAddress(int deviceAddress)
{
    this->deviceAddress = deviceAddress;
};

/**
 * @brief Receiver startup 
 * @todo
 * @param resetPin 
 */
void AKC695X::setup(int resetPin)
{
    this->resetPin = resetPin;
}

/**
 * @brief Power the device on 
 * 
 * @details  Starts the AKC695X with some parameters.
 * 
 * @param fm_en     1 = FM mode;  0 = AM mode
 * @param tune      If 1 Trigger tune process. The STC bit is set high when the tune operation completes
 * @param mute      If 1 mute L/R audio 
 * @param seek      If 1 Trigger tune process. The STC bit is set high when the tune operation completes
 * @param seekup    Seek direction control bit. 0 = Seek down;  1 = Seek up
 */
void AKC695X::powerOn(uint8_t fm_en, uint8_t tune, uint8_t mute, uint8_t seek, uint8_t seekup)
{
    union { 
        akc595x_reg0 r;
        uint8_t raw;
    } p;

    p.r.power_on = 1;
    p.r.rsv = 0;
    p.r.fm_en = fm_en;
    p.r.mute = mute;
    p.r.seek = seek;
    p.r.seekup = seekup;
    p.r.tune = tune;

    setRegister(REG00, p.raw );

    this->currentMode = fm_en;  // Save the current mode (FM or AM)
}

/**
 * @brief Sets a given register with a given value 
 * @details It is a basic function to deal with the AKC695X devices 
 * @param reg  register number to be written (only for RW type registers) 
 * @param parameter  value to be written in the register 
 */
void AKC695X::setRegister(uint8_t reg, uint8_t parameter)
{
    Wire.beginTransmission(this->deviceAddress);
    Wire.write(reg);
    Wire.write(parameter);
    Wire.endTransmission();
    delayMicroseconds(3000);
}

/**
 * @brief Gets a given register content 
 * @details It is a basic function to get a value from a given AKC695X device register
 * @param reg  register number to be read (0 ~ 26) 
 * @return the register content
 */
uint8_t AKC695X::getRegister(uint8_t reg)
{
    Wire.beginTransmission(this->deviceAddress);
    Wire.write(reg);
    Wire.endTransmission();
    delayMicroseconds(3000);
    Wire.requestFrom(this->deviceAddress, 1);
    
    return  Wire.read();
}

void AKC695X::setFM() {
    this->currentMode = 1; 

}


void AKC695X::setAM(uint8_t band)
{
    this->currentMode = 0;
    this->amCurrentBand = band;
}


void AKC695X::setStep(int step) {

    this->currentStep =  step;
}

void AKC695X::setFrequency(uint16_t frequency) {

    this->currentFrequency = frequency;

}

void AKC695X::frequencyUp() {


}


void AKC695X::frequencyDown() {


}


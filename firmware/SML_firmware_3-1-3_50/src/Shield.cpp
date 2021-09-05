#include "shield.h"

// write a digital pot value
void Shield::digitalPotWrite(uint8_t potPin, uint8_t address, uint8_t value) {
  SPI.transfer(potPin, address,SPI_CONTINUE);
  SPI.transfer(potPin, value);
}

// initializes the measurement functionality
void Shield::setup(void)
{
    // set ESP8266 enable pin
    digitalWrite(ESP_EN, LOW);

    // init mux control switch
    muxSwitch.begin(0x20);
    Wire.setClock(400000);
    for(uint8_t i = 0; i < 16; i++) {
        muxSwitch.pinMode(i, OUTPUT);
    }
    muxSwitch.write(0x0088);

    // init SPI pots
    SPI.begin(POT1_SEL);
    SPI.setClockDivider(POT1_SEL, 84);
    SPI.begin(POT2_SEL);
    SPI.setClockDivider(POT2_SEL, 84);

    // set analog inputs to 12-bit resolution
    analogReadResolution(12);

    // set sensitivity to base resistance BASE_REF_RES
    for(uint8_t pot_ch = 0; pot_ch < 6; pot_ch++) {
        digitalPotWrite(POT1_SEL, pot_ch, map(BASE_REF_RES, 0, 100, 255, 0));
        digitalPotWrite(POT2_SEL, pot_ch, map(BASE_REF_RES, 0, 100, 255, 0));
    }
}

// reads the voltage for each pixel and stores it in 'pressureBuf'
void Shield::read_matrix(void)
{
    for (uint8_t mx_number = 0; mx_number < 1; mx_number++) {
        for (uint8_t row_sw = 0; row_sw < SENSOR_ROWS; row_sw++) { //set 20 rows
            muxSwitch.write(MUX_MASK[mx_number][row_sw]);
            for(uint8_t ai_sw = 0; ai_sw < SENSORS_IN_ROW; ai_sw++) { //read 12 channels
                uint16_t sum = 0;
                for(uint8_t smp = 0; smp < SAMPLES; smp++){
                    sum += analogRead(AI_INDEX[ai_sw]); //read ADC
                    delayMicroseconds(5); //100
                }
                pressureBuf[mx_number][row_sw][ai_sw] = (uint16_t)(sum / SAMPLES);
            }
        }
    }
    // set flag if measurement is done
    data_ready = true;
}
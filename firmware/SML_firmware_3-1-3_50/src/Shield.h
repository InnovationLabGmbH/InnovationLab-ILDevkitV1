#ifndef MY_SHIELD_H
#define MY_SHIELD_H

#include <SPI.h>
#include <Wire.h>
#include "PCF8575.h"
#include "consts.h"

class Shield {
    private:
        PCF8575 muxSwitch; //Mux I2C switch
        const uint16_t MUX_MASK [MATRIX_COUNT][SENSOR_ROWS] = {  //Pressure matrices buffer
            //matrix 1
            {0xFFEA, 0xFFEB, 0xFFEC, 0xFFED, 0xFFEE, 0xFFEF, 0xFFD8, 0xFFD9, 0xFFDA, 0xFFDB,
             0xFFE9, 0xFFE8, 0xFFF7, 0xFFF6, 0xFFF5, 0xFFF4, 0xFFF3, 0xFFF2, 0xFFF1, 0xFFF0},
            //matrix 2
            {0xFF7A, 0xFF7B, 0xFF7C, 0xFF7D, 0xFF7E, 0xFF7F, 0xFEF8, 0xFEF9, 0xFEFA, 0xFEFB,
             0xFF79, 0xFF78, 0xFFBF, 0xFFBE, 0xFFBD, 0xFFBC, 0xFFBB, 0xFFBA, 0xFFB9, 0xFFB8},
            //matrix 3
            {0xFBFA, 0xFBFB, 0xFBFC, 0xFBFD, 0xFBFE, 0xFBFF, 0xF7F8, 0xF7F9, 0xF7FA, 0xF7FB,
             0xFBF9, 0xFBF8, 0xFDFF, 0xFDFE, 0xFDFD, 0xFDFC, 0xFDFB, 0xFDFA, 0xFDF9, 0xFDF8},
            //matrix 4
            {0xDFFA, 0xDFFB, 0xDFFC, 0xDFFD, 0xDFFE, 0xDFFF, 0xBFF8, 0xBFF9, 0xBFFA, 0xBFFB,
             0xDFF9, 0xDFF8, 0xEFFF, 0xEFFE, 0xEFFD, 0xEFFC, 0xEFFB, 0xEFFA, 0xEFF9, 0xEFF8}
        };
        const int8_t AI_INDEX[SENSORS_IN_ROW] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};  //AI ports reading sequence

    public:
        Shield(){};
        void setup(void);
        void read_matrix(void);
        void digitalPotWrite(uint8_t potPin, uint8_t address, uint8_t value);

        bool data_ready = false;  // flag to determine if measurement is done
        uint16_t pressureBuf[MATRIX_COUNT][SENSOR_ROWS][SENSORS_IN_ROW] = {{{4095}}};  // data buffer
};
#endif
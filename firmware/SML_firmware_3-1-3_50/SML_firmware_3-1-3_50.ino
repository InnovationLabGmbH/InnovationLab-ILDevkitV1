// Version: 3.1.3.50
// Author: Florian Wiese - InnovationLab GmbH
// Description: Arduino Sketch that allows to connect the DevKit with SML.
// Compatibility: SML 3.1.3.X, 3.1.4.X
const unsigned short SKETCH_VERSION[4] = {3, 1, 3, 50};
/*
The first three numbers of the version show with which SML version this sketch is compatible.
The last digit show the current sketch version with a leading 5 to determine that this is an
DevKit sketch. E.g., the version 3.1.3.51 means, that the sketch was designed for SML v.3.1.3
and is the second version of this sketch.
*/

#include <FreeRTOS_ARM.h>

#include "src/consts.h"
#include "src/functions.h"

#include "src/Protocol.h"
#include "src/Shield.h"

// create protocol object to handle the communication between board and SML
Protocol prt = Protocol();
// create shield object that handles the measurment of the matrix
Shield shield = Shield();

// setup settings, board and threads
void setup() {
    // initialize settings
    for (short i = 0; i < 4; i++){
        prt.settings.version[i] = SKETCH_VERSION[i];
    }
    prt.settings.width = WIDTH;
    prt.settings.height = HEIGHT;
    prt.settings.frame_size = WIDTH * HEIGHT * 2 + 20;

    // initialize serials
    Serial.begin(BAUD_RATE);  // USB init
    Serial2.begin(BAUD_RATE);  // esp8266 connection init

    // initialize shield
    shield.setup();

    // initialize threads
    portBASE_TYPE s1, s2;
    s1 = xTaskCreate(Thread_matrixRead, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s2 = xTaskCreate(Thread_serialComm, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    if (s1 != pdPASS || s2 != pdPASS) {  // check for creation errors
        Serial.println(F("Creation problem"));
    }
    else {  // start scheduler
        vTaskStartScheduler();
        Serial.println("Insufficient RAM");
    }
    while(true);
}

// loop that transmit the latest measurements to SML
void session_loop() {
    byte buffer[2];
    short sensor_value;

    // initialize package ID and start time
    unsigned long start_time = millis();
    prt.settings.package_id = 0;

    // update and send first answer frame once
    prt.update_frame(FIRST_ANSWER_FRAME);
    prt.send_frame(FIRST_ANSWER_FRAME);

    // while session is not stopped ...
    while(prt.check_request() != STOP_REQUEST_FRAME){
        // check if new data is available
        if (!shield.data_ready){
            continue;
        }

        // update package ID and time stamp
        prt.settings.package_id += 1;
        prt.settings.time_stamp = millis() - start_time;

        //send answer frame data
        prt.update_frame(ANSWER_FRAME);
        prt.send_frame(ANSWER_FRAME);

        // send data
        for(short y = 0; y < prt.settings.height; y++) {
            for(short x = 0; x < prt.settings.width; x++) {
                if (TEST_MODE){
                    // compute a test value for pixel (x, y)
                    sensor_value = (float) x + (float) y * (float) prt.settings.width;
                    sensor_value = (unsigned short) sensor_value * (4095./(240. - 1.));
                }
                else{
                    // get the latest measurement value of pixel (x, y)
                    sensor_value = shield.pressureBuf[0][y][x];
                }
                // send the latest value
                int2bytes(sensor_value, buffer);
                Serial.write(buffer, 2);
            }
        }
    }
    // send a final response, that the session has ended
    prt.send_frame(STOP_RESPONSE_FRAME);
}

// thread to read the matrix (never stopping)
static void Thread_matrixRead(void* arg)
{
    while(true) {
        shield.read_matrix();
        // Serial2.write("AT+CIPSEND=0,1920\r\n"); //1440 //1920
        delay(5);
        // Serial2.write((uint8_t*)shield.pressureBuf, 1920);  //1440 //1920
        // Sleep for 5 milliseconds.
        vTaskDelay((5L * configTICK_RATE_HZ) / 1000L);
    }
}

// thread to communicate with the SML (never stopping)
static void Thread_serialComm(void* arg) {
    while (true) {
        // check if a request from SML has arrived
        unsigned short frame_id = prt.check_request();
        if (frame_id == START_REQUEST_FRAME){
            session_loop();
        }
    }
}

void loop() {
    // should never run
}
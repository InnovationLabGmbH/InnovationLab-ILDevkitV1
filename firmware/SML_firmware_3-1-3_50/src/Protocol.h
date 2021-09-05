#ifndef MY_PROTOCOL_H
#define MY_PROTOCOL_H

#include "consts.h"
#include "functions.h"

#include "Frames.h"
#include "Settings.h"

#include "Arduino.h"
// #include "functions.h"

class Protocol {

    private:
        Frames frames;

    public:
        Protocol();
        Settings settings;

        void update_frame(int frame_index);
        void send_frame(int frame_index);
        unsigned short check_request();
        //void flush_serial(void);  temporary not required
};
#endif
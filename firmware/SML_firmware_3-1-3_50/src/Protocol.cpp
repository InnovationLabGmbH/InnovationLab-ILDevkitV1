#include "Protocol.h"

Protocol::Protocol() {
    // frames = &Frames();
    settings = Settings();
}

// updates the response frames
void Protocol::update_frame(int frame_index){
    byte buffer[4];
    switch(frame_index){
        case FIRST_ANSWER_FRAME:
            // update width and height
            frames.first_answer[11] = (byte) settings.width;
            frames.first_answer[12] = (byte) settings.height;

            // update version
            frames.first_answer[32] = (byte) settings.version[0];
            frames.first_answer[33] = (byte) settings.version[1];
            frames.first_answer[35] = (byte) settings.version[2];
            frames.first_answer[36] = (byte) settings.version[3];
            break;

        case ANSWER_FRAME:
            // update frame length
            int2bytes(settings.frame_size, buffer);
            frames.answer[5] = buffer[0];
            frames.answer[6] = buffer[1];

            // update package ID
            int2bytes(settings.package_id, buffer);
            frames.answer[10] = buffer[0];
            frames.answer[11] = buffer[1];
            frames.answer[13] = buffer[2];
            frames.answer[14] = buffer[3];

            // update time stamp
            int2bytes(settings.time_stamp, buffer);
            frames.answer[16] = buffer[0];
            frames.answer[17] = buffer[1];
            frames.answer[19] = buffer[2];
            frames.answer[20] = buffer[3];
            break;

        case GET_RESPONSE_FRAME:
            int2bytes(settings.width, buffer);
            frames.get_response[11] = buffer[0];
            int2bytes(settings.height, buffer);
            frames.get_response[12] = buffer[0];
            break;

        default:
            break;
    }
}

// sends the response frames
void Protocol::send_frame(int frame_index){
    switch(frame_index){
        case FIRST_ANSWER_FRAME:
            Serial.write(frames.first_answer, sizeof(frames.first_answer));
            break;

        case ANSWER_FRAME:
            Serial.write(frames.answer, sizeof(frames.answer));
            break;

        case STOP_RESPONSE_FRAME:
            Serial.write(frames.stop_response, sizeof(frames.stop_response));
            break;

        case GET_RESPONSE_FRAME:
            Serial.write(frames.get_response, sizeof(frames.get_response));
            break;

        default:
            break;
    }
}

// check for requests and return the request type
unsigned short Protocol::check_request(){
    int bytes_available = Serial.available();  // check how many bytes are available
    // each frame has at least 9 bytes
    if (bytes_available < 9) {
        return -1;
    }
    //read serial bytes
    byte buffer[bytes_available];
    Serial.readBytes(buffer, bytes_available);

    //check the preamble bytes
    for (int i = 0; i < 4; i++) {
        if (buffer[i] != 0xFF) return -1;
    }

    //check command ID (9th byte of each frame)
    switch (buffer[8]) {
        case 0x02:
            return STOP_REQUEST_FRAME;

        case 0x08:  // TODO: SET_REQUEST_FRAME not implemented
            return -1;

        case 0x09:
            // update and send current configuration
            update_frame(GET_RESPONSE_FRAME);
            send_frame(GET_RESPONSE_FRAME);
            return GET_REQUEST_FRAME;

        case 0x0B:
            return START_REQUEST_FRAME;

        default:
            return -1;
    }
}

/*
Temporary not required

void Protocol::flush_serial(void)
{
    int bytes_available = Serial.available();
    byte trash[bytes_available];
    if (bytes_available > 0){
        Serial.readBytes(trash, bytes_available);
    }
}
*/
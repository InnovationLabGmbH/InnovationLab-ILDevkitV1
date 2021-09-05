#ifndef MY_FRAMES_H
#define MY_FRAMES_H

using byte = unsigned char;

/*
Updated with Confluence 2021.09.01
https://innovationlabgmbh.atlassian.net/wiki/spaces/PAS/pages/173506572/Protocol+USB

Table description:
Byte:           default byte value
ID:             ID of current byte in frame
Var:            Marks if a byte is changeable in code or during runtime
Description:    explains the function of a byte
*/
class Frames {
    public:
        // Start request frame from SML (without configuration)
        byte start_request[10] = {

        //  Byte      ID   Var  Description
        //_____________________________________________
            0xFF,  // 0         Preamble byte
            0xFF,  // 1         Preamble byte
            0xFF,  // 2         Preamble byte
            0xFF,  // 3         Preamble byte
            0x00,  // 4         ---- Divider field ----
            0x02,  // 5         Data length low byte
            0x00,  // 6         Data length high byte
            0x00,  // 7         ---- Divider field ----
            0x0B,  // 8         Command ID

        };

        // First answer frame for passive matrix
        byte first_answer[38] = {

        //  Byte      ID   Var  Description
        //_____________________________________________
            0xFF,  // 0         Preamble byte
            0xFF,  // 1         Preamble byte
            0xFF,  // 2         Preamble byte
            0xFF,  // 3         Preamble byte
            0x00,  // 4         ---- Divider field ----
            0x1F,  // 5         Data length low byte
            0x00,  // 6         Data length high byte
            0x00,  // 7         ---- Divider field ----
            0x0B,  // 8         Command ID
            0x00,  // 9         Shift X
            0x00,  // 10        Shift Y
            0xAA,  // 11   X    Length X
            0xAA,  // 12   X    Length Y
            0x00,  // 13        Samples number
            0x00,  // 14        Update frequency low byte
            0x00,  // 15        Update frequency high byte
            0x00,  // 16        ---- Divider field ----
            0x00,  // 17        ADC sample delay low byte
            0x00,  // 18        ADC sample delay high byte
            0x00,  // 19        ---- Divider field ----
            0x00,  // 20        Reference voltage low byte
            0x00,  // 21        Reference voltage high byte
            0x00,  // 22        Filter type
            0x00,  // 23        ---- Divider field ----
            0x00,  // 24        Unix time 0
            0x00,  // 25        Unix time 1
            0x00,  // 26        ---- Divider field ----
            0x00,  // 27        Unix time 2
            0x00,  // 28        Unix time 3
            0x00,  // 29        ---- Divider field ----
            0x00,  // 30        ADC value resolution
            0x00,  // 31        ---- Divider field ----
            0xAA,  // 32   X    Firmware version 1
            0xAA,  // 33   X    Firmware version 2
            0x00,  // 34        ---- Divider field ----
            0xAA,  // 35   X    Firmware version 3
            0xAA,  // 36   X    Hardware version
            0x00   // 37        Request status
        };

        // Second and following answer frames
        byte answer[27] = {

        //  Byte      ID   Var  Description
        //_____________________________________________
            0xFF,  // 0         Preamble byte
            0xFF,  // 1         Preamble byte
            0xFF,  // 2         Preamble byte
            0xFF,  // 3         Preamble byte
            0x00,  // 4         ---- Divider field ----
            0xAA,  // 5    X    Data length low byte
            0xAA,  // 6    X    Data length high byte
            0x00,  // 7         ---- Divider field ----
            0x04,  // 8         Command ID
            0x00,  // 9         ---- Divider field ----
            0xAA,  // 10   X    Package ID byte 0
            0xAA,  // 11   X    Package ID byte 1
            0x00,  // 12        ---- Divider field ----
            0xAA,  // 13   X    Package ID byte 2
            0xAA,  // 14   X    Package ID byte 3
            0x00,  // 15        ---- Divider field ----
            0xAA,  // 16   X    Time stamp byte 0
            0xAA,  // 17   X    Time stamp byte 1
            0x00,  // 18        ---- Divider field ----
            0xAA,  // 19   X    Time stamp byte 2
            0xAA,  // 20   X    Time stamp byte 3
            0x00,  // 21        ---- Divider field ----
            0x00,  // 22        Reserved
            0x00,  // 23        Reserved
            0x00,  // 24        ---- Divider field ----
            0x00,  // 25        Reserved
            0x00,  // 26        Reserved
        };

        // Stop request frame from SML
        byte stop_request[10] = {

        //  Byte      ID   Var  Description
        //_____________________________________________
            0xFF,  // 0         Preamble byte
            0xFF,  // 1         Preamble byte
            0xFF,  // 2         Preamble byte
            0xFF,  // 3         Preamble byte
            0x00,  // 4         ---- Divider field ----
            0x02,  // 5         Data length low byte
            0x00,  // 6         Data length high byte
            0x00,  // 7         ---- Divider field ----
            0x02,  // 8         Command ID

        };

        // Stop response frame after stop command was received
        byte stop_response[10] = {

        //  Byte      ID   Var  Description
        //_____________________________________________
            0xFF,  // 0         Preamble byte
            0xFF,  // 1         Preamble byte
            0xFF,  // 2         Preamble byte
            0xFF,  // 3         Preamble byte
            0x00,  // 4         ---- Divider field ----
            0x03,  // 5         Data length low byte
            0x00,  // 6         Data length high byte
            0x00,  // 7         ---- Divider field ----
            0x02,  // 8         Command ID
            0x00,  // 9         Request status

        };

        // Get request frame from SML
        byte get_request[9] = {

        //  Byte      ID   Var  Description
        //_____________________________________________
            0xFF,  // 0         Preamble byte
            0xFF,  // 1         Preamble byte
            0xFF,  // 2         Preamble byte
            0xFF,  // 3         Preamble byte
            0x00,  // 4         ---- Divider field ----
            0x02,  // 5         Data length low byte
            0x00,  // 6         Data length high byte
            0x00,  // 7         ---- Divider field ----
            0x09,  // 8         Command ID
        };

        // Get response frame after get command was received
        byte get_response[25] = {

        //  Byte      ID   Var  Description
        //_____________________________________________
            0xFF,  // 0         Preamble byte
            0xFF,  // 1         Preamble byte
            0xFF,  // 2         Preamble byte
            0xFF,  // 3         Preamble byte
            0x00,  // 4         ---- Divider field ----
            0x12,  // 5         Data length low byte
            0x00,  // 6         Data length high byte
            0x00,  // 7         ---- Divider field ----
            0x09,  // 8         Command ID
            0x00,  // 9         Shift X
            0x00,  // 10        Shift Y
            0xAA,  // 11   X    Length X
            0xAA,  // 12   X    Length Y
            0x00,  // 13        Number of samples
            0x00,  // 14        Update frequency low byte
            0x00,  // 15        Update frequency high byte
            0x00,  // 16        ---- Divider field ----
            0x00,  // 17        ADC sample delay low byte
            0x00,  // 18        ADC sample delay high byte
            0x00,  // 19        ---- Divider field ----
            0x00,  // 20        Offset voltage low byte
            0x00,  // 21        Offset voltage high byte
            0x00,  // 22        Reference voltage low byte
            0x00,  // 23        Reference voltage high byte
            0x00,  // 24        Filter type
        };
};
#endif
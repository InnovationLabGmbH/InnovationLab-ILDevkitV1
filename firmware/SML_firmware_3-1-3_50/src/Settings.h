#ifndef MY_SETTINGS_H
#define MY_SETTINGS_H

// Stores all the settings relevant for data transmission
class Settings {
    public:
        // general
        unsigned short version[4] = {0, 0, 0, 0};
        // session settings
        unsigned int width = 0;
        unsigned int height = 0;
        unsigned int frame_size = 0;
        // frame settings
        unsigned int package_id = 0;
        unsigned int time_stamp = 0;
};
#endif
// --- General settings
#define WIDTH 12
#define HEIGHT 20
#define BAUD_RATE 115200
#define TEST_MODE false

// --- Frame IDs
#define START_REQUEST_FRAME 0
#define ANSWER_FRAME 1
#define FIRST_ANSWER_FRAME 2
#define STOP_REQUEST_FRAME 3
#define STOP_RESPONSE_FRAME 4
#define GET_REQUEST_FRAME 5
#define GET_RESPONSE_FRAME 6

// --- Shield constants
// matrix count
#define MATRIX_COUNT 4
// sensors count (do not change! Requers PCB changing in schematics)
#define SENSORS_IN_ROW 12
#define SENSOR_ROWS 20
// ESP reset pin
#define ESP_RESET 3
#define ESP_EN 7
// Digital pots SPI SS pins
#define POT1_SEL 4
#define POT2_SEL 10
// ADC samples to read per every AI port for average
#define SAMPLES 10
// base reference resistance in kOhms
#define BASE_REF_RES 6
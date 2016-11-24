#ifndef ACQ_TYPES
#define ACQ_TYPES

enum trigger_edge_t {RISING,FALLING,BOTH};
enum range_t {R_100mV=100,R_1V=1,R_10V=10};
enum trigger_t {INTERNAL,EXTERNAL};

enum trigger_channel_t {CH1=1,CH2=2,CH3=3,CH4=4};

#define MAX_SAMPLES 2048

typedef struct {
    char acq_prog_path[100];
    char acq_buffer_path[100];
    char adc_board_pci_id[30];
} acq_path_settings_t;



typedef struct{
    range_t range;
    unsigned int presamples;
    unsigned int posamples;
    int trigger_threshold;
    unsigned int undersampling;
    trigger_t trigger;
    trigger_channel_t trigger_channel;
    trigger_edge_t trigger_edge;
    char board_id[5];
} acq_conf_t;


typedef struct{
    range_t range;
    double threshold_max;
    double threshold_min;
    double pre_samples_time;
    double pos_samples_time;
    unsigned long undersample;
    unsigned long sampling;

} acq_visual_conf_t;


typedef enum
{
  IDLE,
  RUNNING,
  NON_TRIGGERED
} DaqState_t;


#endif // ACQ_TYPES


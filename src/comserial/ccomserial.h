#ifndef CSERIALCOMM_H_CVLSDIF9
#define CSERIALCOMM_H_CVLSDIF9

#ifdef __cplusplus
extern "C" {
#endif

struct comserial_s;
typedef struct comserial_s *comserial_t;

comserial_t comserial_create_device(const char *device);
void comserial_destroy_device(comserial_t *device);

unsigned int comserial_get_speed(const comserial_t device);
unsigned int comserial_set_speed(comserial_t device, unsigned int speed);

unsigned int comserial_get_data_size(const comserial_t device);
unsigned int comserial_set_data_size(comserial_t device, unsigned int data_size);

unsigned int comserial_get_stop_size(const comserial_t device);
unsigned int comserial_set_stop_size(comserial_t device, unsigned int stop_size);

#ifdef __cplusplus
};
#endif

#endif /* end of include guard: CSERIALCOMM_H_CVLSDIF9 */

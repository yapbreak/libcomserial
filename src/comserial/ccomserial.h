#ifndef CSERIALCOMM_H_CVLSDIF9
#define CSERIALCOMM_H_CVLSDIF9

#ifdef __cplusplus
extern "C" {
#endif

struct comserial_s;
typedef struct comserial_s *comserial_t;

comserial_t comserial_create_device(const char *device);
void comserial_destroy_device(comserial_t *device);

#ifdef __cplusplus
};
#endif

#endif /* end of include guard: CSERIALCOMM_H_CVLSDIF9 */

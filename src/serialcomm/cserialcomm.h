#ifndef CSERIALCOMM_H_CVLSDIF9
#define CSERIALCOMM_H_CVLSDIF9

#ifdef __cplusplus
extern "C" {
#endif

struct serialcomm_s;
typedef struct serialcomm_s *serialcomm_t;

serialcomm_t serialcomm_create_device(const char *device);

#ifdef __cplusplus
};
#endif

#endif /* end of include guard: CSERIALCOMM_H_CVLSDIF9 */

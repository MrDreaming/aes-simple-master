#ifndef HEADER_RANDOM_H
#define HEADER_RANDOM_H

#ifdef  __cplusplus
extern "C" {
#endif

void RAND_seed(void); 
int  RAND_number(void);
int  RAND_bytes(unsigned char *buf, int num);
int  RAND_pseudo_bytes(unsigned char *buf, int num);

#ifdef  __cplusplus
}
#endif

#endif


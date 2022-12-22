#ifndef	TSC2007_H_
#define TSC2007_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#ifdef TSC2007_C_
	#define TSC2007_EXT
#else
	#define TSC2007_EXT	extern
#endif

TSC2007_EXT void TSC2007_Init(void);
TSC2007_EXT uint8_t TSC2007_DetectTouch(void);
TSC2007_EXT void TSC2007_Read(uint16_t *x, uint16_t *y);

#ifdef __cplusplus
}
#endif
#endif



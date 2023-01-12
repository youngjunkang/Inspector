#ifndef   __ADS8321_H__
#define   __ADS8321_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#ifdef __ADS8321_C__
	#define ADS8321_EXT
#else
	#define ADS8321_EXT extern
#endif

#pragma pack(push,1)

#pragma pack(pop)

ADS8321_EXT int16_t ADS8321_Read(void);
ADS8321_EXT float ADS8321_ReadVolt(void);
#ifdef __cplusplus
}
#endif

#endif

#ifndef __FOC_PARAMETER_H
#define __FOC_PARAMETER_H

#include "main.h"

/* Motor_M3508_Parameter Config BEGIN */
#ifndef PI
#define PI                            3.14159265358979f
#endif
#define Mec_Wheel_R                   0.152f
#define Mec_Wheeltrack                0.150f
#define Mec_Wheelbase                 0.125f

extern float Motor_M3508_ID01_V;
extern float Motor_M3508_ID02_V;
extern float Motor_M3508_ID03_V;
extern float Motor_M3508_ID04_V;

extern float Robot_Vcx;
extern float Robot_Vcy;
extern float Robot_Wc;
/* Motor_M3508_Parameter Config END */

#endif

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

typedef struct
{
  float ID01_W;
  float ID02_W;
  float ID03_W;
  float ID04_W;
} Motor_M3508_Typedef;

extern Motor_M3508_Typedef Motor_M3508_Data;

extern float Robot_Vcx;
extern float Robot_Vcy;
extern float Robot_Wc;
/* Motor_M3508_Parameter Config END */

#endif

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <malloc.h>

#include "psim.h"

#include "mc_pid.h"

PID sec_pi;

extern "C"
{
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
    typedef enum
    {
        NO_CHANGE,
        FALLING,
        RISING
    } PinStatus_t;
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
    PinStatus_t Pin_Change_Interrupt(double port, PinStatus_t *pin)
    {
        if(port > 0.7)
        {
            if(*pin == NO_CHANGE)
            {
                *pin = RISING;
            }
            else if(*pin == FALLING)
            {
                *pin = RISING;
                return *pin;
            }
        }
        else
        {
            if(*pin == NO_CHANGE)
            {
                *pin = FALLING;
            }
            else if(*pin == RISING)
            {
                *pin = FALLING;
                return *pin;
            }
        }
        return NO_CHANGE;
    }
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
    __declspec(dllexport)  void __cdecl SimulationStep(double t, double delt, double *in, double *out, int *pnError, char *szErrorMsg, void **ptrUserData, int nThreadIndex, void *pAppPtr)
    {
        //---------------------------------------------
        //------------  USER CODE ---------------------
        //---------------------------------------------
        static auto &ref_clock = in[0];
        static auto &output = out[0];
        static auto &ref_output = out[1];
        static double time_ref = 0;
        static double time_shift = 0;
        // static PinStatus_t ref_pin = NO_CHANGE;
        // static PinStatus_t shift_pin = NO_CHANGE;
        static double now = 2e-2;
        static double ms_tick_now = 0;
        static bool first = false;
        static int reset_count = 0;

        static int ref_second = 0;
        static int analog_second = 30;

        // if(Pin_Change_Interrupt(ref_clock, &ref_pin) == RISING)
        // {
        //     time_ref = t;
        // }

        if(t > (ms_tick_now + 1e-3))
        {
            ms_tick_now = t;
            if(++ref_second > 60)
            {
                ref_second = 0;
                ref_output = !ref_output;
            }
            if(++analog_second > 60)
            {
                analog_second = (int)sec_pi.pi_transfer(ref_second - analog_second);
                output = !output;
                out[2] = sec_pi.i_sum;
            }

            if(++reset_count > 100)
            {
                reset_count = 0;
                sec_pi.reset();
            }

        }

        //---------------------------------------------
        //------------  USER CODE END -----------------
        //---------------------------------------------

        *pnError = 0; //Success
    }

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
    __declspec(dllexport) void __cdecl SimulationBegin(const char *szId, int nInputCount, int nOutputCount, int nParameterCount, const char **pszParameters, int *pnError, char *szErrorMsg, void **ptrUserData, int nThreadIndex, void *AppPtr)
    {
        sec_pi.reset();
        sec_pi.param.kp = 0.1; //750
        sec_pi.param.ki = 0.01; //15
        sec_pi.param.kd = 0;
        sec_pi.param.kc = 0; // 10
        sec_pi.param.i_min = -10;
        sec_pi.param.i_max = +10;
        *pnError = 0; //Success
    }

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
    __declspec(dllexport)  void __cdecl SimulationEnd(const char *szId, void **ptrUserData, int nThreadIndex, void *pAppPtr)
    {

        *ptrUserData = NULL;
    }
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
}





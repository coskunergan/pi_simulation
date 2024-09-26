/*
    PID Lib

    Created on: March 13, 2023

    Author: Coskun ERGAN
*/

#ifndef __INCLUDE_CONTROL_MC_PID_H
#define __INCLUDE_CONTROL_MC_PID_H

class PID final
{
    using value_t = float;
public:
    struct Factors
    {
        value_t kp;

        value_t ki;

        value_t kd;

        value_t kg;

        value_t kc;

        value_t i_min;

        value_t i_max;
    };

    PID() = default;
    ~PID() = default;

    PID(const PID &) = delete;
    PID &operator=(const PID &) = delete;

    PID(PID &&) = delete;
    PID &operator=(PID &&) = delete;

    Factors param = {0};

    void reset()
    {
        i_sum = 0;
        sat_err = 0;
    }

    value_t p_transfer(value_t e) noexcept
    {
        value_t m = param.kp * e;
        value_t out
            = m > param.i_max ? param.i_max
              : m < param.i_min ? param.i_min
              : m;
        return out;
    }

    value_t pi_transfer(value_t e) noexcept
    {
        value_t sat = param.kp * e + i_sum;
        // U(s) = kp * E(s) + ki * E(s) / s
        value_t out = sat > param.i_max ? param.i_max
                      : sat < param.i_min ? param.i_min
                      : sat;

        sat_err = out - sat;

        i_sum += param.ki * e + param.kc * sat_err;

        if(i_sum > param.i_max)
        {
            i_sum = param.i_max;
        }
        else if(i_sum < param.i_min)
        {
            i_sum = param.i_min;
        }
        return out;
    }

    value_t pd_transfer(value_t e) noexcept
    {
        return 0;
    }

    value_t pid_transfer(value_t e) noexcept
    {
        return 0;
    }
    value_t i_sum = 0;
private:
    value_t sat_err = 0;
};

#endif
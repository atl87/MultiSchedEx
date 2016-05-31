/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   edf_schedulers.h
 * Author: abhilash
 *
 * Created on May 12, 2016, 12:37 PM
 */
#include "Tasks.h"
#ifndef EDF_SCHEDULERS_H
#define EDF_SCHEDULERS_H

int g_p_edf_schedule(real_time_taskset *taskset, float no_of_processors, int MAX_TIME, int print_log);
int eager_lp_edf_schedule(real_time_taskset *taskset, float no_of_processors, int MAX_TIME, int print_log);
int lazy_lp_edf_schedule(real_time_taskset *taskset, float no_of_processors, int MAX_TIME, int print_log);

#endif /* EDF_SCHEDULERS_H */


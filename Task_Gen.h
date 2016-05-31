/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Task_Gen.h
 * Author: abhilash
 *
 * Created on May 5, 2016, 5:10 AM
 */
#include"Tasks.h"

#ifndef TASK_GEN_H
#define TASK_GEN_H

int UUniFast(int number_of_tasks, float total_util, real_time_taskset *taskset, float deadline_percentage, int MAX_PERIOD, int MIN_PERIOD);
void create_NPRS(real_time_taskset *taskset, float num_of_processors, float npr_percentage);

#endif /* TASK_GEN_H */


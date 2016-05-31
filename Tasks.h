/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tasks.h
 * Author: abhilash
 *
 * Created on May 5, 2016, 12:23 AM
 */

#ifndef TASKS_H
#define TASKS_H

#ifdef __cplusplus
extern "C" {
#endif

    struct real_time_taskset{
    
    int task_no;
    int priority;
    float comp_time;
    float period;
    float deadline;
    float utilization;
    float largest_NPR;
    float no_of_pp;
    
    float saved_comp_time;
    
    float cur_NPR;
    float rem_comp_time;
    int no_of_preemptions;
    int executed;
    int no_of_deadline_misses;
    int abs_deadline;
    int is_executing;
    int no_of_deadlines_missed;
    
    float RT;
    float RT_our;
    float RT_guan;
    float RT_link;
    float RT_np;
    
    real_time_taskset *next_task;
};

int create_taskset(int number_of_tasks, real_time_taskset *taskset);
int delete_taskset(real_time_taskset *taskset, int print_result);
void print_taskset(real_time_taskset *tasket);
real_time_taskset *sort_task_set_DM(real_time_taskset *taskset);
int write_taskset_to_file(int task_set_no, real_time_taskset *taskset);
void restore_taskset(real_time_taskset *taskset);
void generate_inflated_taskset(real_time_taskset *taskset);
float return_utilization(real_time_taskset *taskset);
void generate_NP_taskset(real_time_taskset *taskset);
int count_tasks(real_time_taskset *taskset);
int calculate_LCM(real_time_taskset *FPS_tasks);

#ifdef __cplusplus
}
#endif

#endif /* TASKS_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fps_tests.h
 * Author: abhilash
 *
 * Created on May 12, 2016, 2:24 PM
 */

#ifndef FPS_TESTS_H
#define FPS_TESTS_H

int quick_test_RTA_FPS(real_time_taskset *taskset, float number_of_proc, int task_set_no, int print_log, int print_result);
int bertogna_chirinei_lipari(real_time_taskset *taskset, float number_of_proc, int task_set_no, int print_log, int print_result);
int guan_etal_test_p_fps(real_time_taskset *taskset, float number_of_proc, int task_set_no, int print_log, int print_result);
int fps_link_based_test(real_time_taskset *taskset, float number_of_proc, int task_set_no, int print_log, int print_result);
int eager_lp_fps_rta(real_time_taskset *taskset, float number_of_proc, int task_set_no, int print_log, int print_result);

#endif /* FPS_TESTS_H */


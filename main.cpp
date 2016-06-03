/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: abhilash
 *
 * Created on May 5, 2016, 12:22 AM
 */

#include <cstdlib>
#include<iostream>
#include "fps_experiments.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    cout<<"Simulation for Preemptions vs. Schedulability under Eager and Lazy Preemption Approaches\n\n";
    
    /*
     * Step 1: Generate tasks
     * Step 2: Perform schedulability tests under eager and lazy preemption approaches
     * Step 3: Count the number of preemptions for 50,000 time units
     * 
     * Vary:
     *      a) Utilization
     *      b) Number of tasks
     *      c) Number of processors
     *      d) Priority assignment-- i) RM ii)D-C
     */
    
    float NO_OF_PROCESSORS=(float)4.0000;    
    int MAX_NO_OF_TASKS=30;
    int MAX_TASKSETS_PER_SIMULATION=2;
    int MAX_PERIOD=495;
    int MIN_PERIOD=5;
    int MAX_TIME=5000;
    float DEADLINE_FRACTION=1;
    float npr_percentage=0.1;
    int print_results=1;
    
    varying_NPRs(NO_OF_PROCESSORS, MAX_NO_OF_TASKS, MAX_TASKSETS_PER_SIMULATION, MAX_PERIOD, MIN_PERIOD, MAX_TIME, DEADLINE_FRACTION, npr_percentage, print_results); 
    
    

    return 0;
}


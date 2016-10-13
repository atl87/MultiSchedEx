/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"Task_Gen.h"
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<time.h>

using namespace std;

int UUniFast(int number_of_tasks, float total_util, real_time_taskset* taskset, float deadline_percentage, int MAX_PERIOD, int MIN_PERIOD)
{
    float remaining_util=0.0000;
    int counter=0;
    float util_total=0.0000;
    
    float util_sum=total_util;
    real_time_taskset *helper=taskset;
    
    if(helper==NULL)
        exit(1);
    
    while(counter < number_of_tasks-1)
    {
        float power=1.0000/(number_of_tasks-counter);
        float base=(float) rand()/(float) RAND_MAX;
        float task_util=0.000;
        float base_power=pow(base,power);
        
        remaining_util=util_sum*base_power; 
        task_util=util_sum-remaining_util;
        
        if(task_util > 1)
        {
            continue;
        }

        
        helper->period=(float)(rand()%MAX_PERIOD+MIN_PERIOD);
        helper->deadline= floor(deadline_percentage*helper->period);
        helper->executed=0;
        
        helper->comp_time=floor(helper->period*task_util);
        if(helper->comp_time<=(float)0.0000)
            continue;
        
        helper->utilization=helper->comp_time/helper->period;
        util_total=util_total+helper->utilization;
        helper->no_of_preemptions=0;
        helper->no_of_deadlines_missed=0;

        
        if(helper->utilization > (float)1.0000)
        {
            return 0;
        }
        
        helper->task_no=counter+1;
        helper->largest_NPR=0;
        helper->no_of_preemptions=0;
        helper->no_of_pp=helper->comp_time-(float)1.0000;
        
        helper=helper->next_task;  
        util_sum=remaining_util;
        counter++;     
    }
    
    helper->period=(float)(rand()%MAX_PERIOD+MIN_PERIOD);
    helper->comp_time=floor(helper->period*util_sum);
    if(helper->comp_time<=(float)0.1)
            return 0;
    helper->utilization=helper->comp_time/helper->period;  
    util_total=util_total+helper->utilization;

    helper->deadline= floor(deadline_percentage*helper->period);
    
    if(helper->utilization > (float)1.0000)
    {
        return 0;
    }
    if(util_total<total_util-(float)0.1)
        return 0;

    helper->task_no=counter+1;
    helper->largest_NPR=0;
    helper->no_of_preemptions=0;
    helper->no_of_pp=helper->comp_time-(float)1.0000; 
    helper->no_of_preemptions=0;
    helper->no_of_deadlines_missed=0;
    helper->executed=0;
    helper->saved_comp_time=helper->comp_time;
    helper->rem_comp_time=helper->comp_time;
    
    return 1;
}

void create_NPRS(real_time_taskset *taskset, float num_of_processors, float npr_percentage)
{
    real_time_taskset *helper=taskset;
    int m=(int)num_of_processors;
    int i=1;
    while(helper)
    {
            helper->largest_NPR=ceil(npr_percentage*helper->comp_time);
        
            if(helper->largest_NPR>(float)0.0000)
                helper->no_of_pp=ceil(helper->comp_time/helper->largest_NPR)-1;
            else
                helper->no_of_pp=helper->comp_time-(float)1.0000;
        
        i++;
        helper=helper->next_task;
    }

    
}
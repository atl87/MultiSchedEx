/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"Tasks.h"
#include<iostream>
#include<cmath>
#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>

using namespace std;

int create_taskset(int number_of_tasks, real_time_taskset *taskset)
{
    real_time_taskset *helper=NULL;
    
    helper=taskset;   
    for(int i=1;i<number_of_tasks;i++)
    {
        helper->task_no=i+1;
        real_time_taskset *helper1=(real_time_taskset*)malloc(sizeof(real_time_taskset));
        helper->next_task=helper1;
        helper=helper->next_task;
    }  
    helper->next_task=NULL;
    
    return 1;   
}

int delete_taskset(real_time_taskset *taskset, int print_result)
{
    real_time_taskset *helper=taskset;
    
    while(taskset)
    {
        helper=taskset;
        taskset=taskset->next_task;
        free(helper);
    }
    
    if(print_result)
        cout<<"\nSuccessfully deleted the taskset!";
    return 1;
}

void print_taskset(real_time_taskset *taskset)
{
    real_time_taskset *help_ptr=taskset;
    cout<<"\n\nPrinting the taskset!!\n\n";
    int counter=1;
    cout<<"T.No\tC_i\tD_i\tT_i\tNPR\tNo_of_PP\tRT_O\tRT_L\tRT_G\n";
    while(help_ptr!=NULL)
    {
        help_ptr->task_no=counter;
        printf("%d\t%.0lf\t%.0lf\t%.0lf\t%.0lf\t%.0lf\t\t%.0lf\t%.0lf\t%.0lf\n",help_ptr->task_no,help_ptr->saved_comp_time,help_ptr->deadline,help_ptr->period,help_ptr->largest_NPR,help_ptr->no_of_pp,help_ptr->RT_our,help_ptr->RT_link,help_ptr->RT_guan);
        help_ptr=help_ptr->next_task;
        counter++;
    }
}
real_time_taskset *sort_task_set_DC(real_time_taskset *taskset)
{
    if(taskset==NULL)
        cout<<"Error: No task to print !";
    else
    { 
        real_time_taskset *sort_help1=taskset;
        while(sort_help1)
        {
            real_time_taskset *sort_help2=sort_help1->next_task;
            while(sort_help2)
            {
                if((sort_help1->deadline-sort_help1->comp_time) > (sort_help2->deadline-sort_help2->comp_time))
                {
                    real_time_taskset *prev_task1=taskset;
                    if(sort_help1!=taskset)
                    {             
                        while(prev_task1->next_task!=sort_help1)
                                prev_task1=prev_task1->next_task;
                    }

                    real_time_taskset *prev_task2=taskset;
                    while(prev_task2->next_task!=sort_help2)
                        prev_task2=prev_task2->next_task;

                    real_time_taskset *dummy=sort_help1->next_task;

                    if(sort_help1!=taskset)
                    {                        
                        prev_task2->next_task=sort_help1;
                        sort_help1->next_task=sort_help2->next_task;
                        if(prev_task1!=sort_help1)
                                prev_task1->next_task=sort_help2;

                        if(dummy!=sort_help2)
                                sort_help2->next_task=dummy;
                        else
                                sort_help2->next_task=sort_help1;
                    }
                    else
                    {
                        prev_task2->next_task=sort_help1;
                        sort_help1->next_task=sort_help2->next_task;

                        if(sort_help2!=dummy)
                                sort_help2->next_task=dummy;
                        else
                                sort_help2->next_task=sort_help1;

                        taskset=sort_help2;

                    }

                    dummy=sort_help1;
                    sort_help1=sort_help2;
                    sort_help2=dummy;

                }

                sort_help2=sort_help2->next_task;
            }

            sort_help1=sort_help1->next_task;
        }
        
        real_time_taskset *help_ptr=taskset;   
        int counter=1;
        while(help_ptr!=NULL)
        {
            help_ptr->task_no=counter;
            help_ptr=help_ptr->next_task;
            counter++;
        }
    }
    return taskset;
}
real_time_taskset *sort_task_set_DM(real_time_taskset *taskset)
{
    if(taskset==NULL)
        cout<<"Error: No task to print !";
    else
    {      
       real_time_taskset *sort_help1=taskset;
        while(sort_help1)
        {
            real_time_taskset *sort_help2=sort_help1->next_task;
            while(sort_help2)
            {
                if(sort_help1->task_no > sort_help2->task_no)
                {
                    real_time_taskset *prev_task1=taskset;
                    if(sort_help1!=taskset)
                    {             
                        while(prev_task1->next_task!=sort_help1)
                                prev_task1=prev_task1->next_task;
                    }
                        
                    real_time_taskset *prev_task2=taskset;
                    while(prev_task2->next_task!=sort_help2)
                        prev_task2=prev_task2->next_task;
                    
                    real_time_taskset *dummy=sort_help1->next_task;
                    
                    if(sort_help1!=taskset)
                    {                        
                        prev_task2->next_task=sort_help1;
                        sort_help1->next_task=sort_help2->next_task;
                        if(prev_task1!=sort_help1)
                                prev_task1->next_task=sort_help2;
                        
                        if(dummy!=sort_help2)
                                sort_help2->next_task=dummy;
                        else
                                sort_help2->next_task=sort_help1;
                    }
                    else
                    {
                        prev_task2->next_task=sort_help1;
                        sort_help1->next_task=sort_help2->next_task;
                        
                        if(sort_help2!=dummy)
                                sort_help2->next_task=dummy;
                        else
                                sort_help2->next_task=sort_help1;
                        
                        taskset=sort_help2;                       
                    }
                               
                    dummy=sort_help1;
                    sort_help1=sort_help2;
                    sort_help2=dummy;   
                }
                
                sort_help2=sort_help2->next_task;
            }
            
            sort_help1=sort_help1->next_task;
        }  
       
       real_time_taskset *help_ptr=taskset; 
       int counter=1;
        while(help_ptr!=NULL)
        {
            help_ptr->task_no=counter;
            help_ptr=help_ptr->next_task;
            counter++;
        }
    }
    return taskset;
}
real_time_taskset *sort_tasks(real_time_taskset *taskset)
{
    if(taskset==NULL)
        cout<<"Error: No task to print !";
    else
    {      
       real_time_taskset *sort_help1=taskset;
        while(sort_help1)
        {
            real_time_taskset *sort_help2=sort_help1->next_task;
            while(sort_help2)
            {
                if(sort_help1->task_no > sort_help2->task_no)
                {
                    real_time_taskset *prev_task1=taskset;
                    if(sort_help1!=taskset)
                    {             
                        while(prev_task1->next_task!=sort_help1)
                                prev_task1=prev_task1->next_task;
                    }
                        
                    real_time_taskset *prev_task2=taskset;
                    while(prev_task2->next_task!=sort_help2)
                        prev_task2=prev_task2->next_task;
                    
                    real_time_taskset *dummy=sort_help1->next_task;
                    
                    if(sort_help1!=taskset)
                    {                        
                        prev_task2->next_task=sort_help1;
                        sort_help1->next_task=sort_help2->next_task;
                        if(prev_task1!=sort_help1)
                                prev_task1->next_task=sort_help2;
                        
                        if(dummy!=sort_help2)
                                sort_help2->next_task=dummy;
                        else
                                sort_help2->next_task=sort_help1;
 
                    }
                    else
                    {
                        prev_task2->next_task=sort_help1;
                        sort_help1->next_task=sort_help2->next_task;
                        
                        if(sort_help2!=dummy)
                                sort_help2->next_task=dummy;
                        else
                                sort_help2->next_task=sort_help1;
                        
                        taskset=sort_help2;                        
                    }                               
                    dummy=sort_help1;
                    sort_help1=sort_help2;
                    sort_help2=dummy;
                }                
                sort_help2=sort_help2->next_task;
            }            
            sort_help1=sort_help1->next_task;
        }       
    }
 
    return taskset;
}
void restore_taskset(real_time_taskset *taskset)
{
    real_time_taskset *helper=taskset;

    while(helper!=NULL){
        helper->comp_time=helper->saved_comp_time;
        
        helper=helper->next_task;
    }
}

void generate_inflated_taskset(real_time_taskset *taskset)
{
    real_time_taskset *helper=taskset;
    
    while(helper!=NULL){ 
        real_time_taskset * lower_priority_task=helper->next_task;
        float blocking=(float)0.0000;
        
        while(lower_priority_task){
            
            if(blocking<lower_priority_task->largest_NPR){
                blocking=lower_priority_task->largest_NPR;
            } 
            lower_priority_task=lower_priority_task->next_task;
        }
        
        helper->comp_time=helper->comp_time+blocking;
        
        helper=helper->next_task;
    }
}

void generate_NP_taskset(real_time_taskset *taskset)
{
    real_time_taskset *helper=taskset;
    
    while(helper!=NULL){
        helper->largest_NPR=helper->saved_comp_time;
        helper->no_of_pp=0;
        
        helper=helper->next_task;
    }
}

int write_taskset_to_file(int task_set_no, real_time_taskset *taskset)
{ 
    char task_set_name[100];
    char utilization_filename[50];
    fstream fobj_task, fobj_utilization;
    real_time_taskset *helper=taskset;
    float total_util=0.00;
    
    sprintf(task_set_name,"./Tasksets/task_set%d.dat",task_set_no); 
    sprintf(utilization_filename,"./Tasksets/a-utilization.dat");
    
//    fobj_task.open(task_set_name,ios::out);
//    if(!fobj_task)
//    {
//        cout<<"\nError opening file: "<<task_set_name;
//        exit(1);
//    }
//    else
//    {
//        //cout<<"\nSuccessfully opened file: "<<task_set_name<<"\n";
//    }
    fobj_utilization.open(utilization_filename,ios::out|ios::app);
    if(!fobj_utilization)
    {
        cout<<"\nError opening file: "<<utilization_filename;
        exit(0);
    }
    else
    {
        //cout<<"\nSuccessfully opened file: "<<utilization_filename<<"\n";
    }
    while(helper)
    {
        //cout<<helper->task_no<<"\t"<<helper->comp_time<<"\t"<<helper->deadline<<"\t"<<helper->period<<"\n";
        //fobj_task<<helper->task_no<<"\t"<<helper->comp_time<<"\t"<<helper->deadline<<"\t"<<helper->period<<"\t"<<helper->utilization<<"\t"<<helper->largest_NPR<<"\n";
        total_util=total_util+helper->utilization;
        
        helper=helper->next_task;
    }

    fobj_utilization<<total_util<<"\n";    
    
    return 1;
}
float return_utilization(real_time_taskset *taskset)
{ 
    real_time_taskset *helper=taskset;
    float total_util=0.00;
    
    while(helper)
    {
        total_util=total_util+helper->utilization;
        
        helper=helper->next_task;
    }
    return total_util;
}
int count_tasks(real_time_taskset *taskset)
{
    int count=0;
    for(real_time_taskset *helper=taskset;helper!=NULL;)
    {
        helper=helper->next_task;
        count++;
    }
    return count;
}
int calculate_LCM(real_time_taskset *FPS_tasks)
{
    real_time_taskset *task_pointer, *help_pointer, *last_task=FPS_tasks;
    int LCM;
    int count=0, LCM_found=0;

    if(FPS_tasks)
    {
        task_pointer=FPS_tasks;
        LCM=task_pointer->period;
    }
    else
            return 0;

    while(last_task->next_task!=NULL)
        last_task=last_task->next_task;

    if(task_pointer)
    {
        while(! LCM_found)
        {
            help_pointer=task_pointer;
            count++;
            LCM=last_task->period*count;
            while(help_pointer!=NULL)
            {
                    if(LCM % (int)help_pointer->period == 0)
                    {
                        help_pointer=help_pointer->next_task;
                        LCM_found=1;
                    }
                    else
                    {
                        help_pointer=NULL;
                        LCM_found=0;
                    }
            }
        }
    }
    return LCM;
}
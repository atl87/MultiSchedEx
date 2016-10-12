#include <cstdlib>
#include<iostream>
#include<stdio.h>
#include "Tasks.h"
#include "Task_Gen.h"
#include "fps_schedulers.h"
#include"edf_schedulers.h"
#include "fps_tests.h"
#include<math.h>
#include <fstream>

using namespace std;


int varying_NPRs(float NO_OF_PROCESSORS, int MAX_NO_OF_TASKS, int MAX_TASKSETS_PER_SIMULATION, int MAX_PERIOD, int MIN_PERIOD,int MAX_TIME, float DEADLINE_FRACTION, float npr_percentage, int print_results)
{
    srand (time(NULL));
    fstream f_weighted, f_normal, f_schedulability_weighted, f_schedulability_normal;
    
    f_weighted.open("./results/preemptions_weighted_results_varying_NPR.txt",ios::out);
    if(!f_weighted)
    {
        cout<<"\nError opening file: ./results/preemptions_weighted_results_varying_NPR.txt";
        exit(1);
    }
    f_normal.open("./results/preemptions_normal_results_varying_NPR.txt",ios::out);
    if(!f_normal)
    {
        cout<<"\nError opening file: ./results/preemptions_normal_results_varying_NPR.txt";
        exit(1);
    }   
    f_schedulability_weighted.open("./results/schedulability_weighted_results_varying_NPR.txt",ios::out);
    if(!f_schedulability_weighted)
    {
        cout<<"\nError opening file: ./results/schedulability_weighted_results_varying_NPR.txt";
        exit(1);
    }
    f_schedulability_normal.open("./results/schedulability_normal_results_varying_NPR.txt",ios::out);
    if(!f_schedulability_normal)
    {
        cout<<"\nError opening file: ./results/schedulability_normal_results_varying_NPR.txt";
        exit(1);
    }
/******************************OUTPUT CONTROL VARIABLES******************************/    
    int print_basic=0;
    int print_log=0;
/******************************OUTPUT CONTROL VARIABLES******************************/
    
    int no_of_preemptions_fps=0;
    int no_of_preemptions_rds=0;
    int no_of_preemptions_ads=0;
    int no_of_preemptions_edf=0;
    int no_of_preemptions_rds_edf=0;
    int no_of_preemptions_ads_edf=0;

    float p_fps[20], eager_fps[20], lazy_fps[20];
    float p_edf[20], eager_edf[20], lazy_edf[20];
    float sched_p_fps[20], sched_eager_fps[20], sched_lazy_fps[20];
    
    float util_sum=0.0000*0;           
    float cur_util=1.0000;
    float max_util=NO_OF_PROCESSORS;
    
    for(int i=0;i<20;i++)
    {
        p_fps[i]=0.0000*0;
        eager_fps[i]=0.0000*0;
        lazy_fps[i]=0.0000*0;
        p_edf[i]=0.0000*0;
        eager_edf[i]=0.0000*0;
        lazy_edf[i]=0.0000*0;
        
        sched_p_fps[i]=0.0000*0;
        sched_eager_fps[i]=0.0000*0;
        sched_lazy_fps[i]=0.0000*0;
    }
        
    no_of_preemptions_fps=0;
    no_of_preemptions_rds=0;
    no_of_preemptions_ads=0;

    no_of_preemptions_edf=0;
    no_of_preemptions_rds_edf=0;
    no_of_preemptions_ads_edf=0;                
        
    cout<<"\nNumber of tasks: "<<MAX_NO_OF_TASKS<<"\n";  

    while(cur_util<=max_util)
    {
        if(print_basic)
            cout<<"\nUtilization: "<<cur_util<<"\n";

        int counter=1;
        while(counter<=MAX_TASKSETS_PER_SIMULATION)
        {
            int successful_parameter_generation=0;
            real_time_taskset *taskset=(real_time_taskset*) malloc(sizeof(real_time_taskset));
            if(print_log)
                cout<<"\n\nCreating real-time tasks: ";
            create_taskset(MAX_NO_OF_TASKS,taskset);  
            if(taskset==NULL)
            {
                cout<<"\n*****************task set not created ! *****************";
                exit(1);
            }
            else if(print_log)
                cout<<"\nCreated task set :"<<counter<<"\n";

            while(!successful_parameter_generation)
            {                   
                if(UUniFast(MAX_NO_OF_TASKS,cur_util,taskset,DEADLINE_FRACTION, MAX_PERIOD, MIN_PERIOD)==1)
                {
                    successful_parameter_generation=1; 
                    if(taskset==NULL)
                    {
                        cout<<"\n\n***************** parameters not generated ! *****************";
                        exit(1);
                    }
                    taskset=sort_task_set_DM(taskset);
                }
            }      
/****************************************************************************************YOUR CODE GOES HERE****************************************************************************************/                              
            int round=0;
            while(round<20)
            {
                npr_percentage=(float)0.05*(round+1);
                create_NPRS(taskset,NO_OF_PROCESSORS,npr_percentage);

                float taskset_util=return_utilization(taskset);
                int preemptions_fps=0, preemptions_rds=0, preemptions_ads=0, count=0, count1=0, count2, count3, count4, count5,count6;               
                int preemptions_edf=0, preemptions_rds_edf=0, preemptions_ads_edf=0;

                util_sum+=taskset_util;
                count=count_tasks(taskset);
                if(count!=MAX_NO_OF_TASKS)
                {
                    print_taskset(taskset);
                    cout<<"\n\n\tError in the number of tasks generated (expected: "<<MAX_NO_OF_TASKS<<" Actual: "<<count<<" )\n\n";
                    exit(1);
                }

                preemptions_fps=g_p_fps_schedule(taskset, NO_OF_PROCESSORS, MAX_TIME, print_log);
                no_of_preemptions_fps+=preemptions_fps;
                p_fps[round]+=taskset_util*preemptions_fps;

                count1=count_tasks(taskset);
                if(count1!=MAX_NO_OF_TASKS)
                {
                    print_taskset(taskset);
                    cout<<"\n\n\tError in the number of tasks after FPS (expected: "<<MAX_NO_OF_TASKS<<" Actual: "<<count1<<" )\n\n";
                    exit(1);          
                }

                preemptions_rds=eager_lp_fps_schedule(taskset, NO_OF_PROCESSORS, MAX_TIME, print_log);
                eager_fps[round]+=taskset_util*preemptions_rds;
                no_of_preemptions_rds+=preemptions_rds;

                count2=count_tasks(taskset);
                if(count2!=count1)
                {
                    print_taskset(taskset);
                    cout<<"\n\n\tError in the number of tasks after RDS (expected: "<<count1<<" Actual: "<<count2<<" )\n\n";
                    exit(1);       
                }

                preemptions_ads=lazy_lp_fps_schedule(taskset, NO_OF_PROCESSORS, MAX_TIME, print_log);
                lazy_fps[round]+=taskset_util*preemptions_ads;
                no_of_preemptions_ads+=preemptions_ads;

                count3=count_tasks(taskset);
                if(count3!=count2)
                {
                    print_taskset(taskset);
                    cout<<"\n\n\tError in the number of tasks after ADS (expected: "<<count2<<" Actual: "<<count3<<" )\n\n";
                    exit(1);       
                }

/*************************EDF starts here*************************/
//                preemptions_edf=g_p_edf_schedule(taskset, NO_OF_PROCESSORS, MAX_TIME, print_log);
//                p_edf[round]+=taskset_util*preemptions_edf;
//                no_of_preemptions_edf+=preemptions_edf;
//
//                count4=count_tasks(taskset);
//                if(count4!=count3)
//                {
//                    print_taskset(taskset);
//                    cout<<"\n\n\tError in the number of tasks after P-EDF (expected: "<<count3<<" Actual: "<<count4<<" )\n\n";
//                    exit(1);       
//                }                
//
//                preemptions_rds_edf=eager_lp_edf_schedule(taskset, NO_OF_PROCESSORS, MAX_TIME, print_log);
//                eager_edf[round]+=taskset_util*preemptions_rds_edf;
//                no_of_preemptions_rds_edf+=preemptions_rds_edf;
//
//                count5=count_tasks(taskset);
//                if(count5!=count4)
//                {
//                    print_taskset(taskset);
//                    cout<<"\n\n\tError in the number of tasks after EDF-RDS (expected: "<<count4<<" Actual: "<<count5<<" )\n\n";
//                    exit(1);       
//                }   
//
//                preemptions_ads_edf=lazy_lp_edf_schedule(taskset, NO_OF_PROCESSORS, MAX_TIME, print_log);
//                lazy_edf[round]+=taskset_util*preemptions_ads_edf;
//                no_of_preemptions_ads_edf+=preemptions_ads_edf;
//
//                count6=count_tasks(taskset);
//                if(count6!=count5)
//                {
//                    print_taskset(taskset);
//                    cout<<"\n\n\tError in the number of tasks after P-EDF (expected: "<<count5<<" Actual: "<<count6<<" )\n\n";
//                    exit(1);       
//                }   
/*************************EDF ends here*************************/
                sched_p_fps[round]+=(p_fps_test_guan(taskset, NO_OF_PROCESSORS,0,0)*taskset_util);
                sched_eager_fps[round]+=(eager_lp_fps_rta(taskset, NO_OF_PROCESSORS,0,0)*taskset_util);
                sched_lazy_fps[round]+=(lazy_lp_fps_test_linkbased(taskset, NO_OF_PROCESSORS,0,0)*taskset_util);
                
                round++;
            }

/****************************************************************************************YOUR CODE GOES ABOVE****************************************************************************************/
            delete_taskset(taskset,print_log); 
            counter++;
        }

        f_normal<<"\n"<<(no_of_preemptions_fps/MAX_TASKSETS_PER_SIMULATION)<<"\t"<<(no_of_preemptions_rds/MAX_TASKSETS_PER_SIMULATION)<<"\t"<<(no_of_preemptions_ads/MAX_TASKSETS_PER_SIMULATION);
        //f_normal<<"\t"<<(no_of_preemptions_edf/MAX_TASKSETS_PER_SIMULATION)<<"\t"<<(no_of_preemptions_rds_edf/MAX_TASKSETS_PER_SIMULATION)<<"\t"<<(no_of_preemptions_ads_edf/MAX_TASKSETS_PER_SIMULATION);


        if(print_results)
        {
            cout<<"\nUtilization: "<<cur_util;
            cout<<"\nPreemptions P-FPS: "<<(no_of_preemptions_fps/MAX_TASKSETS_PER_SIMULATION)<<" Preemptions RDS-FPS : "<<(no_of_preemptions_rds/MAX_TASKSETS_PER_SIMULATION);
            cout<<" Preemptions ADS-FPS : "<<(no_of_preemptions_ads/MAX_TASKSETS_PER_SIMULATION);
/*           
 *            cout<<"\nPreemptions P-EDF: "<<(no_of_preemptions_edf/MAX_TASKSETS_PER_SIMULATION)<<" Preemptions RDS-EDF : "<<(no_of_preemptions_rds_edf/MAX_TASKSETS_PER_SIMULATION);
 *            cout<<" Preemptions ADS-EDF : "<<(no_of_preemptions_ads_edf/MAX_TASKSETS_PER_SIMULATION);
 */
        }

        cur_util=cur_util+0.1;
    }
    
    
    for(int i=0;i<20;i++)
    {
        f_weighted<<(p_fps[i]/util_sum)<<"\t"<<(eager_fps[i]/util_sum)<<"\t"<<(lazy_fps[i]/util_sum);//<<"\t"<<(p_edf[i]/util_sum)<<"\t"<<(eager_edf[i]/util_sum)<<"\t"<<(lazy_edf[i]/util_sum)<<"\n";
        f_normal<<"\n\n";
        
        cout<<"\n\nWeighted preemptions P-FPS: "<<(p_fps[i]/util_sum)<<" Weighted preemptions RDS-FPS: "<<(eager_fps[i]/util_sum)<<" Weighted preemptions ADS-FPS: "<<(lazy_fps[i]/util_sum);
//        cout<<"\nWeighted preemptions P-EDF: "<<(p_edf[i]/util_sum)<<" Weighted preemptions RDS-EDF: "<<(eager_edf[i]/util_sum)<<" Weighted preemptions ADS-EDF: "<<(lazy_edf[i]/util_sum)<<"\n\n";
    }
        
    f_normal.close();
    f_weighted.close();

    return 0;
}

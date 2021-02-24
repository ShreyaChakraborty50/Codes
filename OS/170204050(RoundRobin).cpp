#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include<stdlib.h>
#include<string.h>
using namespace std;

struct process
{
    int num, arrival_time, cpu_time, last_execution, waiting_time, turnaround_time,completion_time;
} p[100];

bool cmp(struct process p1, struct process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

bool cmp2(struct process p1, struct process p2)
{
    return p1.num < p2.num;
}
int notChecked[100];
int arrival_time[100], cpu_time[100];
int main()
{
    memset(notChecked, 1, sizeof(notChecked));
    int num_of_process, quantum;
    cout << "Enter the number of processes: ";
    cin >> num_of_process;
    cout << "Enter the time quantum: ";
    cin >> quantum;
    cout << "Enter CPU Times: ";
    for (int i = 0; i < num_of_process; ++i)
    {
        cin >> cpu_time[i];
    }
    cout << "Enter Arrival Times: ";
    for (int i = 0; i < num_of_process; ++i)
    {
        cin >> arrival_time[i];
    }
    for (int i = 0; i < num_of_process; ++i)
    {
        p[i].arrival_time = p[i].last_execution = arrival_time[i];
        p[i].cpu_time = cpu_time[i];
        p[i].num = i;
    }

    sort(p, p + num_of_process, cmp);


    queue<int> q;
    q.push(0);
    notChecked[0] = 0;
    int total_time = p[0].arrival_time;
    //cout << endl
        // << "Gantt Chart" << endl;
    while (!q.empty())
    {
        int process_no = q.front();
        q.pop();
        int time_taken = min(quantum, p[process_no].cpu_time);
       // cout << total_time << "--p" << p[process_no].num + 1 << "--";
        p[process_no].waiting_time += max(0, (total_time - p[process_no].last_execution));
        p[process_no].cpu_time -= min(quantum, p[process_no].cpu_time);
        total_time += time_taken;
        p[process_no].last_execution = total_time;
        //cout << total_time << " | ";
        for (int i = 0; i < num_of_process; ++i)
        {
            if (p[i].arrival_time <= total_time && notChecked[i])
            {
                q.push(i);
                notChecked[i] = 0;
            }
        }
        if (p[process_no].cpu_time > 0)
        {
            q.push(process_no);
        }
        else{
            p[process_no].completion_time= total_time;
        }
        if(q.empty())
        {
            for (int i = 0; i < num_of_process; ++i)
            {
                if (notChecked[i])
                {
                    q.push(i);
                    notChecked[i] = 0;
                    total_time = p[i].arrival_time;
                    break;
                }
            }
        }
    }

    //cout << endl
        // << endl
        // << "Total Time: " << total_time << endl;
    sort(p, p + num_of_process, cmp2);
    double totalWaiting_time = 0.0, totalTurnaround_time = 0.0;
    for (int i = 0; i < num_of_process; ++i)
    {
        totalWaiting_time += p[i].waiting_time;

        p[i].turnaround_time = p[i].waiting_time + cpu_time[i];
        cout << "Process  " << i+1 << ": " << "Waiting Time :  " << p[i].waiting_time<< "   " << "Turnaround Time:  " << p[i].turnaround_time<< endl;

        totalTurnaround_time += p[i].turnaround_time;
    }

    cout << "======================\n";
    cout << "Average Waiting Time: " << totalWaiting_time / num_of_process << endl;
    cout << "Average Turn Around Time: " << totalTurnaround_time / num_of_process << endl;
    return 0;

}

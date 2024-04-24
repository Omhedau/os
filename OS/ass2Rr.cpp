#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <string.h>
using namespace std;

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compare1(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

bool compare2(process p1, process p2)
{
    return p1.pid < p2.pid;
}

int main()
{

    int n;
    int tq;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    int burst_remaining[100];
    int idx;

    cout << setprecision(2) << fixed;

    vector<int> Order_Of_Execution;
    vector<int> Time;

    cout << "\nEnter the number of processes: ";
    cin >> n;
    cout << "\nEnter time quantum: ";
    cin >> tq;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter ARRIVAL time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter BURST time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;

        // initially update burst_remaining time with total burst time.
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }

    sort(p, p + n, compare1);

    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mark[100];
    memset(mark, 0, sizeof(mark));
    mark[0] = 1;

    while (completed != n)
    {
        idx = q.front();
        q.pop();

        // To check same process is coming again Or
        // Another new process with 'burst_remaining time exactly equal to burst_time' is coming after context Switching.
        if (burst_remaining[idx] == p[idx].burst_time)
        {
            p[idx].start_time = max(current_time, p[idx].arrival_time);
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }

        if (burst_remaining[idx] - tq > 0)
        {
            burst_remaining[idx] -= tq;

            // order of execution and Time for Gantt chart ...
            Order_Of_Execution.push_back(p[idx].pid);
            Time.push_back(current_time);

            current_time += tq;
        }
        else
        {
            // burst_remaining time is less than equal to time quantum.
            // ---->
            // order of execution and Time for Gantt chart ...
            Order_Of_Execution.push_back(p[idx].pid);
            Time.push_back(current_time);

            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;

            if (completed == n)
            {
                // Final Completion time.
                Time.push_back(current_time);
            }

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
        }

        // starting from 'second process'(i = 1) because first(i = 0) arrived process present
        // in ready queue which is already executed.
        for (int i = 1; i < n; i++)
        {
            // all processes are already sorted according to their arrival time.
            // so..  only we have to push those processes into Ready Queue which have something burst_remaining time.
            if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0)
            {
                q.push(i);
                mark[i] = 1;
            }
        }

        // curent process which is not completely executed but only for time quantum coming at the
        // extreme end of the queue.
        if (burst_remaining[idx] > 0)
        {
            q.push(idx);
        }

        if (q.empty())
        {
            for (int i = 1; i < n; i++)
            {
                if (burst_remaining[i] > 0)
                {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;

    // because we have to print those processes in consecutive order of their process ID.
    sort(p, p + n, compare2);

    cout << endl
         << endl;

    cout << "" << endl;
    cout << "#P\t"
         << "AT\t"
         << "BT\t"
         << "CT\t"
         << "TAT\t"
         << "WT\t"
         << "RT\t" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t" << endl;
    }

    // Gantt chart...
    cout << "\n";
    cout << "Gantt Chart:\n"
         << "-----------"
         << "\n\n\n";
    for (int i = 0; i < Order_Of_Execution.size(); i++)
    {
        cout << "|" << Order_Of_Execution[i] << " ";
    }
    cout << "|";

    cout << "\n";

    for (int i = 0; i < Time.size(); i++)
    {
        cout << Time[i] << "\t";
    }

    cout << "\n\nAverage Turnaround Time = " << avg_turnaround_time << endl
         << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl
         << endl;
    cout << "Average Response Time = " << avg_response_time << endl
         << endl;

    return 0;
}

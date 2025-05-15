//
//  ECSimTaskScheduler2.cpp
//  

#include <vector>
#include <algorithm>
#include "ECSimTaskScheduler2.h"
#include "ECSimTask.h"

//***********************************************************
// ECSimLWTFTaskScheduler

ECSimLWTFTaskScheduler::ECSimLWTFTaskScheduler() {}

ECSimTask* ECSimLWTFTaskScheduler::ChooseTaskToSchedule(const std::vector<ECSimTask*>& listReadyTasks) const
{
    if (listReadyTasks.empty()) return nullptr;

    ECSimTask* best = listReadyTasks[0];
    int maxWait = best->GetTotWaitTime();
    for (auto* t : listReadyTasks) {
        int w = t->GetTotWaitTime();
        if (w > maxWait) {
            maxWait = w;
            best = t;
        }
    }
    return best;
}

//***********************************************************
// ECSimPriorityScheduler

ECSimPriorityScheduler::ECSimPriorityScheduler() {}

ECSimTask* ECSimPriorityScheduler::ChooseTaskToSchedule(const std::vector<ECSimTask*>& listReadyTasks) const
{
    if (listReadyTasks.empty()) return nullptr;

    ECSimTask* best = listReadyTasks[0];
    int bestPri = best->GetPriority();
    for (auto* t : listReadyTasks) {
        int p = t->GetPriority();
        if (p < bestPri) {
            bestPri = p;
            best = t;
        }
    }
    return best;
}

//***********************************************************
// ECSimRoundRobinTaskScheduler

ECSimRoundRobinTaskScheduler::ECSimRoundRobinTaskScheduler() {}

ECSimTask* ECSimRoundRobinTaskScheduler::ChooseTaskToSchedule(const std::vector<ECSimTask*>& listReadyTasks) const
{
    if (listReadyTasks.empty()) return nullptr;

    ECSimTask* best = listReadyTasks[0];
    int minRun = best->GetTotRunTime();
    for (auto* t : listReadyTasks) {
        int r = t->GetTotRunTime();
        if (r < minRun) {
            minRun = r;
            best = t;
        }
    }
    return best;
}

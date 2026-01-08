//
//  ECSimTaskScheduler2.h
//  Additional scheduler implementations
//

#ifndef ECSimTaskScheduler2_h
#define ECSimTaskScheduler2_h

#include "ECSimTaskScheduler.h"
#include <vector>

//***********************************************************
// Longest wait-time first scheduler: choose the task that has waited the longest so far; break ties by request order
class ECSimLWTFTaskScheduler : public ECSimTaskScheduler
{
public:
    ECSimLWTFTaskScheduler();
protected:
    virtual ECSimTask* ChooseTaskToSchedule(const std::vector<ECSimTask*>& listReadyTasks) const override;
};

//***********************************************************
// Priority-based scheduler: schedule the task with the highest priority (lowest pri value)
class ECSimPriorityScheduler : public ECSimTaskScheduler
{
public:
    ECSimPriorityScheduler();
protected:
    virtual ECSimTask* ChooseTaskToSchedule(const std::vector<ECSimTask*>& listReadyTasks) const override;
};

//***********************************************************
// Round-robin scheduler: choose the task that has run the fewest total ticks so far
class ECSimRoundRobinTaskScheduler : public ECSimTaskScheduler
{
public:
    ECSimRoundRobinTaskScheduler();
protected:
    virtual ECSimTask* ChooseTaskToSchedule(const std::vector<ECSimTask*>& listReadyTasks) const override;
};

#endif /* ECSimTaskScheduler2_h */

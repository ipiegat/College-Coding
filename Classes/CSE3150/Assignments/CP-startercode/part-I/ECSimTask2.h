//
//  ECSimTask2.h
//  
//
//  Simulation task: different types
//

#ifndef ECSimTask2_h
#define ECSimTask2_h

#include <string>
#include <vector>
#include <utility>
#include "ECSimTask.h"

//***********************************************************
// Multiple intervals task: a task spans multiple intervals of time; otherwise it behaves just like a single (soft) interval

class ECMultiIntervalsTask : public ECSimTask
{
public:
    ECMultiIntervalsTask(const std::string &tid);
    void AddInterval(int tmStart, int tmEnd);
    virtual bool IsReadyToRun(int tick) const override;
    virtual bool IsFinished(int tick) const override;

private:
    std::vector<std::pair<int,int>> intervals;
    int maxEnd;
};

//***********************************************************
// One-shot task: a task spans a single interval [a,b] of time; this task has hard requirement:
// it must start at a and end at b. If this condition is not met, it just won't run at all!

class ECHardIntervalTask : public ECSimTask
{
public:
    ECHardIntervalTask(const std::string &tid, int tmStart, int tmEnd);
    virtual bool IsReadyToRun(int tick) const override;
    virtual bool IsFinished(int tick) const override;

private:
    int tmStart;
    int tmEnd;
};

//***********************************************************
// Consecutive interval task: spans [a,b]; once it first runs, it must run through to b without interruption.

class ECConsecutiveIntervalTask : public ECSimTask
{
public:
    ECConsecutiveIntervalTask(const std::string &tid, int tmStart, int tmEnd);
    virtual bool IsReadyToRun(int tick) const override;
    virtual bool IsFinished(int tick) const override;
    virtual void Run(int tick, int duration) override;
    virtual void Wait(int tick, int duration) override;

private:
    int tmStart;
    int tmEnd;
    bool hasStarted;
    bool isValid;
    int lastRunTick;
};

//***********************************************************
// Periodic task: a recurrent task that runs periodically of certain length

class ECPeriodicTask : public ECSimTask
{
public:
    // tmStart: when to start this periodic task; runLen: how long to run each cycle; sleepLen: how long to sleep between runs
    ECPeriodicTask(const std::string &tid, int tmStart, int runLen, int sleepLen);
    virtual bool IsReadyToRun(int tick) const override;
    virtual bool IsFinished(int tick) const override;

private:
    int tmStart;
    int runLen;
    int sleepLen;
};

#endif /* ECSimTask2_h */

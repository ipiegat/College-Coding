//
//  ECSimTask2.cpp
//  
//

#include "ECSimTask2.h"

//***********************************************************
// ECMultiIntervalsTask

ECMultiIntervalsTask::ECMultiIntervalsTask(const std::string &tid)
: ECSimTask(tid), maxEnd(0)
{
}

void ECMultiIntervalsTask::AddInterval(int tmStart, int tmEnd)
{
    intervals.emplace_back(tmStart, tmEnd);
    if (tmEnd > maxEnd) {
        maxEnd = tmEnd;
    }
}

bool ECMultiIntervalsTask::IsReadyToRun(int tick) const
{
    for (const auto &interval : intervals) {
        if (tick >= interval.first && tick <= interval.second) {
            return true;
        }
    }
    return false;
}

bool ECMultiIntervalsTask::IsFinished(int tick) const
{
    return tick > maxEnd;
}

//***********************************************************
// ECHardIntervalTask

ECHardIntervalTask::ECHardIntervalTask(const std::string &tid, int start, int end)
: ECSimTask(tid), tmStart(start), tmEnd(end)
{
}

bool ECHardIntervalTask::IsReadyToRun(int tick) const
{
    int runSoFar = GetTotRunTime();
    if (tick < tmStart) {
        return false;
    }
    // if not yet started, only ready exactly at tmStart
    if (runSoFar == 0) {
        return tick == tmStart;
    }
    // once begun on time, it may run intermittently until tmEnd
    return tick <= tmEnd;
}

bool ECHardIntervalTask::IsFinished(int tick) const
{
    int runSoFar = GetTotRunTime();
    // if never started and missed start, it's done
    if (runSoFar == 0) {
        return tick > tmStart;
    }
    // if it started, it finishes after tmEnd
    return tick > tmEnd;
}

//***********************************************************
// ECConsecutiveIntervalTask

ECConsecutiveIntervalTask::ECConsecutiveIntervalTask(const std::string &tid, int start, int end)
: ECSimTask(tid),
  tmStart(start),
  tmEnd(end),
  hasStarted(false),
  isValid(true),
  lastRunTick(-1)
{
}

bool ECConsecutiveIntervalTask::IsReadyToRun(int tick) const
{
    if (!isValid) return false;
    if (tick < tmStart || tick > tmEnd) return false;
    if (!hasStarted) {
        // before first run, ready any time in [tmStart, tmEnd]
        return true;
    }
    // once started, only ready if it's exactly the next tick
    return tick == lastRunTick + 1;
}

bool ECConsecutiveIntervalTask::IsFinished(int tick) const
{
    // finishes if invalidated (interrupted) or past its window
    return (!isValid) || (tick > tmEnd);
}

void ECConsecutiveIntervalTask::Run(int tick, int duration)
{
    ECSimTask::Run(tick, duration);
    hasStarted = true;
    lastRunTick = tick;
}

void ECConsecutiveIntervalTask::Wait(int tick, int duration)
{
    // if it's been started and then forced to wait, it's broken
    if (hasStarted && isValid) {
        isValid = false;
    }
    ECSimTask::Wait(tick, duration);
}

//***********************************************************
// ECPeriodicTask

ECPeriodicTask::ECPeriodicTask(const std::string &tid, int start, int rLen, int sLen)
: ECSimTask(tid), tmStart(start), runLen(rLen), sleepLen(sLen)
{
}

bool ECPeriodicTask::IsReadyToRun(int tick) const
{
    if (tick < tmStart) {
        return false;
    }
    int cycle = runLen + sleepLen;
    int offset = tick - tmStart;
    return (offset % cycle) < runLen;
}

bool ECPeriodicTask::IsFinished(int /*tick*/) const
{
    // periodic tasks never self-terminate in Part I
    return false;
}

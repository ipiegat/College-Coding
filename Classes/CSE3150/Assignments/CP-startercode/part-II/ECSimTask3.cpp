//
//  ECSimTask3.cpp
//  
//

#include "ECSimTask3.h"
#include <iostream>
using namespace std;

//***********************************************************
// Basic task
//***********************************************************

//***********************************************************
// Interval task: a single interval.
// YW: you shouldn't need to change this class!

ECSimIntervalTask :: ECSimIntervalTask(const std::string &tidIn, int tmStartIn, int tmEndIn) : tid(tidIn), tmStart(tmStartIn), tmEnd(tmEndIn), tmTotWait(0), tmTotRun(0)
{
}

// Is task ready to run at certain time? tick: the current clock time (in simulation unit)
bool ECSimIntervalTask :: IsReadyToRun(int tick) const
{
    return tick >= tmStart && tick <= tmEnd;
}

// Is task complete at certain time? If so, scheduler may remove it from the list. tick the current clock time (in simulation unit)
bool ECSimIntervalTask :: IsFinished(int tick) const
{
    return tick > tmEnd;
}


//***********************************************************
// Consecutive task: a task that can early abort
// your code here
ECSimConsecutiveTask::ECSimConsecutiveTask(ECSimTask *pTask)
  : pBase(pTask), hasRun(false), aborted(false)
{}

std::string ECSimConsecutiveTask::GetId() const {
  return pBase->GetId();
}

bool ECSimConsecutiveTask::IsReadyToRun(int tick) const {
  return !aborted && pBase->IsReadyToRun(tick);
}

void ECSimConsecutiveTask::Run(int tick, int duration) {
  pBase->Run(tick, duration);
  hasRun = true;
}

void ECSimConsecutiveTask::Wait(int tick, int duration) {
  pBase->Wait(tick, duration);
  if (hasRun) {
    aborted = true;
  }
}

bool ECSimConsecutiveTask::IsFinished(int tick) const {
  return aborted || pBase->IsFinished(tick);
}

bool ECSimConsecutiveTask::IsAborted(int tick) const {
  return aborted || pBase->IsAborted(tick);
}

int ECSimConsecutiveTask::GetTotRunTime() const {
  return pBase->GetTotRunTime();
}

int ECSimConsecutiveTask::GetTotWaitTime() const {
  return pBase->GetTotWaitTime();
}

//***********************************************************
// Periodic task: a task that can early abort
// your code here
ECSimPeriodicTask::ECSimPeriodicTask(ECSimTask *pTask, int lenSleepIn)
  : pBase(pTask)
  , lenSleep(lenSleepIn)
  , origStart(-1)
  , origEnd(-1)
  , recording(true)
{}

std::string ECSimPeriodicTask::GetId() const {
  return pBase->GetId();
}

bool ECSimPeriodicTask::IsReadyToRun(int tick) const {
  // During initial recording, mirror the base’s readiness
  if (recording) {
    return pBase->IsReadyToRun(tick);
  }
  // After recording, map into the first window
  int runLen = origEnd - origStart + 1;
  int cycle  = runLen + lenSleep;
  if (tick < origStart) return false;
  int offset  = (tick - origStart) % cycle;
  int relTick = origStart + offset;
  return pBase->IsReadyToRun(relTick);
}

void ECSimPeriodicTask::Run(int tick, int duration) {
  // First-window recording: capture contiguous Run() ticks
  if (recording) {
    if (origStart < 0) {
      origStart = origEnd = tick;
    }
    else if (tick == origEnd + 1) {
      origEnd = tick;
    }
    else {
      // gap detected ⇒ stop recording
      recording = false;
    }
  }

  // Once recording is done, map tick back into the recorded window
  int execTick = tick;
  if (!recording && origStart >= 0) {
    int runLen = origEnd - origStart + 1;
    int cycle  = runLen + lenSleep;
    int offset = (tick - origStart) % cycle;
    execTick   = origStart + offset;
  }
  pBase->Run(execTick, duration);
}

void ECSimPeriodicTask::Wait(int tick, int duration) {
  // A Wait immediately after your last recorded run marks end of initial window
  if (recording && origEnd >= 0 && tick == origEnd + 1
      && pBase->IsReadyToRun(tick)) {
    recording = false;
  }

  // Map the Wait() call into the recorded window
  int waitTick = tick;
  if (!recording && origStart >= 0) {
    int runLen = origEnd - origStart + 1;
    int cycle  = runLen + lenSleep;
    int offset = (tick - origStart) % cycle;
    waitTick   = origStart + offset;
  }
  pBase->Wait(waitTick, duration);
}

bool ECSimPeriodicTask::IsFinished(int /*tick*/) const {
  // never self-terminate
  return false;
}

bool ECSimPeriodicTask::IsAborted(int tick) const {
  return pBase->IsAborted(tick);
}

int ECSimPeriodicTask::GetTotRunTime() const {
  return pBase->GetTotRunTime();
}

int ECSimPeriodicTask::GetTotWaitTime() const {
  return pBase->GetTotWaitTime();
}

//***********************************************************
// Task with a deadline to start: a task that must start by some time; otherwise terminate
// your code here
ECSimStartDeadlineTask::ECSimStartDeadlineTask(ECSimTask *pTask, int tmStartDeadlineIn)
  : pBase(pTask)
  , tmStartDeadline(tmStartDeadlineIn)
{}

std::string ECSimStartDeadlineTask::GetId() const {
  return pBase->GetId();
}

bool ECSimStartDeadlineTask::IsReadyToRun(int tick) const {
  return pBase->IsReadyToRun(tick);
}

void ECSimStartDeadlineTask::Run(int tick, int duration) {
  pBase->Run(tick, duration);
}

void ECSimStartDeadlineTask::Wait(int tick, int duration) {
  pBase->Wait(tick, duration);
}

bool ECSimStartDeadlineTask::IsAborted(int tick) const {
  return pBase->IsAborted(tick) ||
         (tick > tmStartDeadline && pBase->GetTotRunTime() == 0);
}

bool ECSimStartDeadlineTask::IsFinished(int tick) const {
  return pBase->IsFinished(tick) || IsAborted(tick);
}

int ECSimStartDeadlineTask::GetTotRunTime() const {
  return pBase->GetTotRunTime();
}

int ECSimStartDeadlineTask::GetTotWaitTime() const {
  return pBase->GetTotWaitTime();
}
//***********************************************************
// Task must end by some fixed time click: this is useful e.g. when a task is periodic
// your code here
ECSimEndDeadlineTask::ECSimEndDeadlineTask(ECSimTask *pTask,
                                           int tmEndDeadlineIn)
  : pBase(pTask)
  , tmEndDeadline(tmEndDeadlineIn)
{}

std::string ECSimEndDeadlineTask::GetId() const {
  return pBase->GetId();
}

bool ECSimEndDeadlineTask::IsReadyToRun(int tick) const {
  return tick <= tmEndDeadline
      && pBase->IsReadyToRun(tick);
}

void ECSimEndDeadlineTask::Run(int tick, int duration) {
  if (tick <= tmEndDeadline)
    pBase->Run(tick, duration);
}

void ECSimEndDeadlineTask::Wait(int tick, int duration) {
  if (tick <= tmEndDeadline)
    pBase->Wait(tick, duration);
}

bool ECSimEndDeadlineTask::IsAborted(int tick) const {
  return pBase->IsAborted(tick)
      || (tick > tmEndDeadline
          && !pBase->IsFinished(tmEndDeadline));
}

bool ECSimEndDeadlineTask::IsFinished(int tick) const {
  return pBase->IsFinished(tick)
      || IsAborted(tick);
}

int ECSimEndDeadlineTask::GetTotRunTime() const {
  return pBase->GetTotRunTime();
}

int ECSimEndDeadlineTask::GetTotWaitTime() const {
  return pBase->GetTotWaitTime();
}
//***********************************************************
// Composite task: contain multiple sub-tasks
// your code here
ECSimCompositeTask::ECSimCompositeTask(const std::string &tidIn)
  : tid(tidIn), tmTotRun(0), tmTotWait(0)
{}

std::string ECSimCompositeTask::GetId() const {
  return tid;
}

void ECSimCompositeTask::AddSubtask(ECSimTask *pTask) {
  subs.push_back(pTask);
}

bool ECSimCompositeTask::IsReadyToRun(int tick) const {
  for (auto s : subs) {
    if (!s->IsFinished(tick) && !s->IsAborted(tick)
        && s->IsReadyToRun(tick))
      return true;
  }
  return false;
}

void ECSimCompositeTask::Run(int tick, int duration) {
  // collect all subtasks that are ready this tick
  std::vector<ECSimTask*> ready;
  for (auto s : subs) {
    if (!s->IsFinished(tick) && !s->IsAborted(tick)
        && s->IsReadyToRun(tick))
      ready.push_back(s);
  }
  if (ready.empty()) return;

  // first ready subtask runs
  ready[0]->Run(tick, duration);
  tmTotRun += duration;

  // any others that were ready must wait
  for (std::size_t i = 1; i < ready.size(); ++i) {
    ready[i]->Wait(tick, duration);
    tmTotWait += duration;
  }
}

void ECSimCompositeTask::Wait(int tick, int duration) {
  // every subtask that's ready but didn't get the CPU must wait
  for (auto s : subs) {
    if (!s->IsFinished(tick) && !s->IsAborted(tick)
        && s->IsReadyToRun(tick))
    {
      s->Wait(tick, duration);
      tmTotWait += duration;
    }
  }
}

bool ECSimCompositeTask::IsFinished(int tick) const {
  // finished only when _all_ subtasks are finished
  for (auto s : subs) {
    if (!s->IsFinished(tick))
      return false;
  }
  return true;
}

bool ECSimCompositeTask::IsAborted(int tick) const {
  // if any subtask aborts, the composite aborts
  for (auto s : subs) {
    if (s->IsAborted(tick))
      return true;
  }
  return false;
}

int ECSimCompositeTask::GetTotRunTime() const {
  return tmTotRun;
}

int ECSimCompositeTask::GetTotWaitTime() const {
  return tmTotWait;
}
#include "GameTimer.h"
#include <iostream>
//#define _POSIX_C_SOURCE 199309L
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/** Returns current hardware time in milliseconds
 */
static unsigned long long int getCurrentTime() {
  struct timespec time;
  int r = clock_gettime(CLOCK_REALTIME, &time);
  if (r != 0) {
    perror("system clock error GameTimer.cpp getCurrentTime");
    exit(errno);
  }
  return time.tv_nsec / 1000000;
}

GameTimer::GameTimer()
    : mSecondsPerCount(0.0), mDeltaTime(0.0), mBaseTime(0), mPausedTime(0),
      mPrevTime(0), mCurrTime(0), mStopped(false) {
  /* TODO Timer
  long long int countsPerSec;
  QueryPerformanceFrequency((LARGE_INTEGER *)&countsPerSec);
  mSecondsPerCount = 1.0 / (double)countsPerSec;
  */
  mSecondsPerCount = 1.0;

  Reset();
  Tick();
}

float GameTimer::TotalTime() const {
  if (mStopped) {
    return (float)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
  } else {
    return (float)(((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
  }
}

double GameTimer::DeltaTime() const { return mDeltaTime; }

void GameTimer::Reset() {
  long long int currTime;
  /* TODO Timer
  QueryPerformanceCounter((LARGE_INTEGER *)&currTime);
  */
  currTime = getCurrentTime();

  mBaseTime = currTime;
  mPrevTime = currTime;
  mStopTime = 0;
  mStopped = false;
}

void GameTimer::Start() {
  long long int startTime;
  /* TODO Timer
  QueryPerformanceCounter((LARGE_INTEGER *)&startTime);
  */
  startTime = getCurrentTime();

  if (mStopped) {
    mPausedTime += (startTime - mStopTime);

    mPrevTime = startTime;
    mStopTime = 0;
    mStopped = false;
  }
}

void GameTimer::Stop() {
  if (!mStopped) {
    long long int currTime;
    /* TODO Timer
    QueryPerformanceCounter((LARGE_INTEGER *)&currTime);
    */
    currTime = getCurrentTime();

    mStopTime = currTime;
    mStopped = true;
  }
}

void GameTimer::Tick() {
  if (mStopped) {
    mDeltaTime = 0.0;
    return;
  }

  long long int currTime;
  /* TODO Timer
  QueryPerformanceCounter((LARGE_INTEGER *)&currTime);
  */
  currTime = getCurrentTime();
  mCurrTime = currTime;

  // Time difference between this frame and the previous.
  mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

  // Prepare for next frame.
  mPrevTime = mCurrTime;

  // Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the
  // processor goes into a power save mode or we get shuffled to another
  // processor, then mDeltaTime can be negative.
  if (mDeltaTime < 0.0) {
    mDeltaTime = 0.0;
  }
}

void GameTimer::SleepForDuration(const float &ms) {
  /* TODO TIMER
  unsigned long long int currentTime, previousTime;
  //QueryPerformanceCounter(&currentTime);
  currentTime = getCurrentTime();
  double remainingTime =
      ms - (double)(currentTime - mBaseTime) * mSecondsPerCount * 1000;

  while (remainingTime > 0.0) {
    previousTime = currentTime;
    //QueryPerformanceCounter(&currentTime);
    currentTime = getCurrentTime();

    double elapsedTime =
        (double)(currentTime - previousTime) *
        mSecondsPerCount * 1000;
    std::cout << elapsedTime << std::endl;
    remainingTime -= elapsedTime;

    if (remainingTime > 10.0) {
      Sleep(10);
    }
  }
  //*/
  usleep(ms * 1000.f);
}

/*
 *	Implementation of Frank Luna's GameTimer
 */

#pragma once

class GameTimer {
public:
  GameTimer();

  ///< summary>
  /// Returns the total time elapsed since Reset() was called, NOT counting any
  /// time when the clock is stopped.
  ///</summary>
  ///< returns>The total elapsed time in seconds</returns>
  float TotalTime() const; // in seconds

  ///< summary>
  /// Returns the time elapsed in between the last two <code>Tick()</code>
  /// calls.
  ///</summary>
  ///< returns>The time in between ticks in seconds</returns>
  double DeltaTime() const; // in seconds

  void Reset(); // Call before message loop.
  void Start(); // Call when unpaused.
  void Stop();  // Call when paused.
  void Tick();  // Call every frame.
  void SleepForDuration(const float &);

private:
  double mSecondsPerCount;
  double mDeltaTime;

  long long int mBaseTime;
  long long int mPausedTime;
  long long int mStopTime;
  long long int mPrevTime;
  long long int mCurrTime;

  bool mStopped;
};
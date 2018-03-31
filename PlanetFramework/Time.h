#pragma once

#include <chrono>
typedef std::chrono::steady_clock::time_point HighResTime;
typedef std::chrono::duration<long, std::nano> HighResDuration;

class Time {
public:
  Time();
  void Start();
  void Update();
  float GetTime();
  float DeltaTime();
  float FPS();

private:
  // Platform abstraction
  HighResTime Now() const;
  HighResDuration Diff(const HighResTime &start, const HighResTime &end) const;

  template <typename T>
  T HRTCast(const HighResDuration &lhs) const {
    return (static_cast<T>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(lhs)
                   .count())) *
           1e-9f;
  }

  HighResTime begin;
  HighResTime last;
  float m_DeltaTime = 0;
};

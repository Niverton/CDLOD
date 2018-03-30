#include "Time.h"
#include "stdafx.h"

Time::Time() {
  Start();
}

Time::~Time() {
}

void Time::Start() {
  begin = Now();
  last = begin;
}
void Time::Update() {
  auto end = Now();
  m_DeltaTime = HRTCast<float>(Diff(last, end));
  last = end;
}
float Time::GetTime() {
  auto end = Now();
  return HRTCast<float>(Diff(begin, end));
}
float Time::DeltaTime() {
  return m_DeltaTime;
}
float Time::FPS() {
  return (1.f / m_DeltaTime);
}

HighResTime Time::Now() const {
  return std::chrono::steady_clock::now();
}
HighResDuration Time::Diff(const HighResTime &start,
                           const HighResTime &end) const {
  return end - start;
}


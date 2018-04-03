#pragma once

#ifndef GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_LEFT_HANDED
#endif

template <class T>
inline void SafeDelete(T &pObjectToDelete) {
  if (pObjectToDelete != nullptr) {
    delete (pObjectToDelete);
    pObjectToDelete = nullptr;
  }
}

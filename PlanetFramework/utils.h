#pragma once

#ifndef GLM_LEFT_HANDED
#define GLM_LEFT_HANDED
#endif

template <class T>
inline void SafeDelete(T &pObjectToDelete) {
  if (pObjectToDelete != 0) {
    delete (pObjectToDelete);
    pObjectToDelete = 0;
  }
}

// TODO move this to a custom file with a solid ruleset
#define UINT32 unsigned int
#define UINT unsigned int
#define BYTE char
#define USHORT unsigned short
#define UCHAR unsigned char

# Infos importantes:

- Erreur dans libnvidia (probablement dû à des optimisations)
- Fuite dans SDL2
- Fuite dans InputManager
- Saut sur variable non initialisé Triangulator::GenerateGeometry

# Details:

``` sh

==5403== Memcheck, a memory error detector
==5403== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==5403== Using Valgrind-3.12.0.SVN and LibVEX; rerun with -h for copyright info
==5403== Command: ./PlanetRenderer
==5403== 
==5403== Syscall param writev(vector[...]) points to uninitialised byte(s)
==5403==    at 0x67F6EA0: __writev_nocancel (syscall-template.S:84)
==5403==    by 0xD46A41C: write_vec (xcb_conn.c:277)
==5403==    by 0xD46A41C: _xcb_conn_wait (xcb_conn.c:522)
==5403==    by 0xD46A81C: _xcb_out_send (xcb_out.c:458)
==5403==    by 0xD46A89C: xcb_writev (xcb_out.c:406)
==5403==    by 0xA6F3A7D: _XSend (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA6F3F71: _XReply (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA6DEE2E: XInternAtom (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0x5C2346A: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5C24364: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5C142EF: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5C1407E: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5B7A456: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==  Address 0x113d32b3 is 35 bytes inside a block of size 16,384 alloc'd
==5403==    at 0x4C2DBC5: calloc (vg_replace_malloc.c:711)
==5403==    by 0xA6E3EC5: XOpenDisplay (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0x5C2253F: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5C1402B: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5B7A456: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x115311: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== Conditional jump or move depends on uninitialised value(s)
==5403==    at 0x91500A4: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x90F6435: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x90F8C7D: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x920E5FF: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x920FB2D: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x91301F4: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9130571: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9130607: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x920DFE4: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9216EE0: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x8E3B875: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x8E3BBF7: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403== 
==5403== Conditional jump or move depends on uninitialised value(s)
==5403==    at 0x91500A4: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x90F6435: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x90F6CEC: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9242180: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x92435C0: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x91301F4: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9130571: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9130607: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9242466: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x921AEFA: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x90ED104: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x90CFEAB: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403== 
==5403== Warning: set address range perms: large range [0x19c4f040, 0x31c4f040) (undefined)
==5403== Warning: set address range perms: large range [0x395f8040, 0x515f8040) (undefined)
==5403== Warning: set address range perms: large range [0x19c4f028, 0x31c4f058) (noaccess)
==5403== Warning: set address range perms: large range [0x395f8028, 0x515f8058) (noaccess)
==5403== Conditional jump or move depends on uninitialised value(s)
==5403==    at 0x62302B2: tanf (s_tanf.c:33)
==5403==    by 0x11EED4: Triangulator::GenerateGeometry() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11E510: Triangulator::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11CADD: Planet::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x12304B: Scene::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x1155AD: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== Conditional jump or move depends on uninitialised value(s)
==5403==    at 0x622DE95: __kernel_tanf (k_tanf.c:49)
==5403==    by 0x623031D: tanf (s_tanf.c:33)
==5403==    by 0x11EED4: Triangulator::GenerateGeometry() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11E510: Triangulator::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11CADD: Planet::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x12304B: Scene::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x1155AD: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== Conditional jump or move depends on uninitialised value(s)
==5403==    at 0x622DE9D: __kernel_tanf (k_tanf.c:50)
==5403==    by 0x623031D: tanf (s_tanf.c:33)
==5403==    by 0x11EED4: Triangulator::GenerateGeometry() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11E510: Triangulator::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11CADD: Planet::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x12304B: Scene::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x1155AD: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== Conditional jump or move depends on uninitialised value(s)
==5403==    at 0x622DEA4: __kernel_tanf (k_tanf.c:51)
==5403==    by 0x623031D: tanf (s_tanf.c:33)
==5403==    by 0x11EED4: Triangulator::GenerateGeometry() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11E510: Triangulator::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11CADD: Planet::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x12304B: Scene::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x1155AD: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== Conditional jump or move depends on uninitialised value(s)
==5403==    at 0x622E09D: __kernel_tanf (k_tanf.c:54)
==5403==    by 0x623031D: tanf (s_tanf.c:33)
==5403==    by 0x11EED4: Triangulator::GenerateGeometry() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11E510: Triangulator::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11CADD: Planet::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x12304B: Scene::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x1155AD: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== Conditional jump or move depends on uninitialised value(s)
==5403==    at 0x91500A4: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x90F6435: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x90F79FF: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x92105B0: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x921131F: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x91301F4: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9130571: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x9130607: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x92102CC: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x92173C7: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x8E3BE42: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403==    by 0x921AE94: ??? (in /usr/lib/x86_64-linux-gnu/libnvidia-glcore.so.340.102)
==5403== 
==5403== Mismatched free() / delete / delete []
==5403==    at 0x4C2D2DB: operator delete(void*) (vg_replace_malloc.c:576)
==5403==    by 0x112C6C: InputManager::~InputManager() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x112CF5: InputManager::~InputManager() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x1157DC: Singleton<InputManager>::DestroyInstance() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11565B: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==  Address 0x11db1950 is 0 bytes inside a block of size 512 alloc'd
==5403==    at 0x4C2C93F: operator new[](unsigned long) (vg_replace_malloc.c:423)
==5403==    by 0x112D41: InputManager::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x115588: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== Mismatched free() / delete / delete []
==5403==    at 0x4C2D2DB: operator delete(void*) (vg_replace_malloc.c:576)
==5403==    by 0x112C8D: InputManager::~InputManager() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x112CF5: InputManager::~InputManager() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x1157DC: Singleton<InputManager>::DestroyInstance() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x11565B: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==  Address 0x11691b00 is 0 bytes inside a block of size 512 alloc'd
==5403==    at 0x4C2C93F: operator new[](unsigned long) (vg_replace_malloc.c:423)
==5403==    by 0x112D5D: InputManager::Init() (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403==    by 0x115588: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== 
==5403== HEAP SUMMARY:
==5403==     in use at exit: 119,724 bytes in 1,153 blocks
==5403==   total heap usage: 59,695 allocs, 58,542 frees, 1,998,410,748 bytes allocated
==5403== 
==5403== 72 bytes in 1 blocks are definitely lost in loss record 93 of 139
==5403==    at 0x4C2DBC5: calloc (vg_replace_malloc.c:711)
==5403==    by 0xA743A80: XkbGetMap (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0x5C1CB5E: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5C23085: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5C13E75: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5B7A456: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x115311: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== 144 bytes in 1 blocks are definitely lost in loss record 104 of 139
==5403==    at 0x4C2DBC5: calloc (vg_replace_malloc.c:711)
==5403==    by 0x5C212C8: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5C124D5: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x11533D: main (in /autofs/netapp/travail/jbernard0002/M1/CDLOD/build/PlanetRenderer)
==5403== 
==5403== 192 (16 direct, 176 indirect) bytes in 1 blocks are definitely lost in loss record 112 of 139
==5403==    at 0x4C2DDCF: realloc (vg_replace_malloc.c:785)
==5403==    by 0xA70669C: ??? (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA706C01: ??? (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA70850E: ??? (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA708D27: _XlcCreateLC (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA7259CF: _XlcDefaultLoader (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA7102BD: _XOpenLC (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA710407: _XlcCurrentLC (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0xA71043D: XSetLocaleModifiers (in /usr/lib/x86_64-linux-gnu/libX11.so.6.3.0)
==5403==    by 0x5C2310A: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5C13E75: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403==    by 0x5B7A456: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.4.1)
==5403== 
==5403== LEAK SUMMARY:
==5403==    definitely lost: 232 bytes in 3 blocks
==5403==    indirectly lost: 176 bytes in 4 blocks
==5403==      possibly lost: 0 bytes in 0 blocks
==5403==    still reachable: 119,316 bytes in 1,146 blocks
==5403==         suppressed: 0 bytes in 0 blocks
==5403== Reachable blocks (those to which a pointer was found) are not shown.
==5403== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==5403== 
==5403== For counts of detected and suppressed errors, rerun with: -v
==5403== Use --track-origins=yes to see where uninitialised values come from
==5403== ERROR SUMMARY: 23 errors from 14 contexts (suppressed: 0 from 0)

```

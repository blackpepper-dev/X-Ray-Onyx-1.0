# automatically generated Thu Jul 29 12:09:25 MST 2004
del shader.h geoshader.h mi_version.h
copy shader.34.h shader.h
copy geoshader.34.h geoshader.h
copy shader34x86.lib shader.lib
copy mi_version.34.h mi_version.h
cl -c -DDEBUG /Z7  /MDd /nologo /W3 -DWIN_NT -DEVIL_ENDIAN -D_WIN32_WINNT=0x0400 -DNV_CG -DHYPERTHREAD -DX86 -I. contourshade.c
cl -c -DDEBUG /Z7  /MDd /nologo /W3 -DWIN_NT -DEVIL_ENDIAN -D_WIN32_WINNT=0x0400 -DNV_CG -DHYPERTHREAD -DX86 -I. outimgshade.c
cl -c -DDEBUG /Z7  /MDd /nologo /W3 -DWIN_NT -DEVIL_ENDIAN -D_WIN32_WINNT=0x0400 -DNV_CG -DHYPERTHREAD -DX86 -I. outpsshade.c
link /delayload:opengl32.dll /nologo /nodefaultlib:LIBC.LIB /MAP:mapfile /OPT:NOREF /INCREMENTAL:NO /MACHINE:IX86 /STACK:0x200000,0x1000 /DEBUG /pdb:none  ws2_32.lib user32.lib mpr.lib largeint.lib opengl32.lib gdi32.lib delayimp.lib /DLL /OUT:contour.dll contourshade.obj outimgshade.obj outpsshade.obj shader.lib raylib.res

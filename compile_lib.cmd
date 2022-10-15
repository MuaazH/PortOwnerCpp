@echo off
cls
g++ -Wall PortOwner.c -static-libgcc -static-libstdc++ -liphlpapi -lPsapi -shared -m32 -o PortOwner32.dll -Wl,--subsystem,windows,--out-implib,PortOwner32.a
g++ -Wall PortOwner.c -static-libgcc -static-libstdc++ -liphlpapi -lPsapi -shared -m64 -o PortOwner64.dll -Wl,--subsystem,windows,--out-implib,PortOwner64.a

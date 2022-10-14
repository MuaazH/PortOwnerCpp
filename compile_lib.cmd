@echo off
cls
g++ -Wall PortOwner.cpp -static-libgcc -static-libstdc++ -liphlpapi -lPsapi -shared -m32 -o PortOwner32.dll
g++ -Wall PortOwner.cpp -static-libgcc -static-libstdc++ -liphlpapi -lPsapi -shared -m64 -o PortOwner64.dll

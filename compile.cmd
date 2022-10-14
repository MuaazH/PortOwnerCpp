@echo off
cls
g++ -Wall PortOwner.cpp main.cpp -static-libgcc -static-libstdc++ -liphlpapi -lPsapi -o test.exe

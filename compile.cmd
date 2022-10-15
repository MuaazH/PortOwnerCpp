@echo off
cls
g++ -Wall PortOwner.c main.cpp -static-libgcc -static-libstdc++ -liphlpapi -lPsapi -o test.exe

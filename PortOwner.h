#ifndef _PORT_OWNER_H_
#define _PORT_OWNER_H_

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) int GetUdp4Ports(void *pOut, unsigned int outSize);
__declspec(dllexport) int GetUdp6Ports(void *pOut, unsigned int outSize);

__declspec(dllexport) int GetTcp4Ports(void *pOut, unsigned int outSize);
__declspec(dllexport) int GetTcp6Ports(void *pOut, unsigned int outSize);

__declspec(dllexport) int GetProcessName(unsigned int pid, char *pOut, long unsigned int size);

#ifdef __cplusplus
}
#endif


#endif
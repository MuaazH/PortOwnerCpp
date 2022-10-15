#include "PortOwner.h"

#define WINVER 0x0601
#define AF_INET6        23

#include <iphlpapi.h>
#include <processthreadsapi.h>
//#include "psapi.h"
#include <winbase.h>


int GetUdp4Ports(void *pOut, unsigned int outSize) {
	PDWORD pDwOut = (PDWORD) pOut;
	*pDwOut = 0; // Zero values found

	if (outSize < 32) {
		return -1;
	}
	DWORD outCapacity = (outSize - sizeof(DWORD)) / (sizeof(DWORD) * 2);
	DWORD bufSize = outCapacity * sizeof(MIB_UDPROW_OWNER_PID) + sizeof(DWORD) + 8;
	char *pBuf = (char *) malloc(bufSize);
	if (!pBuf) {
		return -1;
	}
	DWORD ret;

	// call the blasted method
	ret = GetExtendedUdpTable(pBuf, &bufSize, false, AF_INET, UDP_TABLE_OWNER_PID, 0);

	if (!ret) {
		// Cast the buffer to the expected result type
		PMIB_UDPTABLE_OWNER_PID info = (PMIB_UDPTABLE_OWNER_PID) pBuf;

		// calculate the output capacity
		if (outCapacity > info->dwNumEntries) {
			outCapacity = info->dwNumEntries;
		}

		// Write the result size
		*pDwOut = info->dwNumEntries;
		pDwOut++;

		// write the port then the PID
		for (DWORD i = 0; i < outCapacity; i++) {
			DWORD bigEndianPort = info->table[i].dwLocalPort;

			*pDwOut = (bigEndianPort >> 8) | ((bigEndianPort & 0x00FF) << 8);
			pDwOut++;

			*pDwOut = info->table[i].dwOwningPid;
			pDwOut++;
		}
	}

	free(pBuf);
	return ret;
}

int GetUdp6Ports(void *pOut, unsigned int outSize) {
	PDWORD pDwOut = (PDWORD) pOut;
	*pDwOut = 0; // Zero values found

	if (outSize < 32) {
		return -1;
	}
	DWORD outCapacity = (outSize - sizeof(DWORD)) / (sizeof(DWORD) * 2);
	DWORD bufSize = outCapacity * sizeof(MIB_UDP6ROW_OWNER_PID) + sizeof(DWORD) + 8;
	char *pBuf = (char *) malloc(bufSize);
	if (!pBuf) {
		return -1;
	}
	DWORD ret;

	// call the blasted method
	ret = GetExtendedUdpTable(pBuf, &bufSize, false, AF_INET6, UDP_TABLE_OWNER_PID, 0);

	if (!ret) {
		// Cast the buffer to the expected result type
		PMIB_UDP6TABLE_OWNER_PID info = (PMIB_UDP6TABLE_OWNER_PID) pBuf;

		// calculate the output capacity
		if (outCapacity > info->dwNumEntries) {
			outCapacity = info->dwNumEntries;
		}

		// Write the result size
		*pDwOut = info->dwNumEntries;
		pDwOut++;

		// write the port then the PID
		for (DWORD i = 0; i < outCapacity; i++) {
			DWORD bigEndianPort = info->table[i].dwLocalPort;

			*pDwOut = (bigEndianPort >> 8) | ((bigEndianPort & 0x00FF) << 8);
			pDwOut++;

			*pDwOut = info->table[i].dwOwningPid;
			pDwOut++;
		}
	}

	free(pBuf);
	return ret;
}

int GetTcp4Ports(void *pOut, unsigned int outSize) {
	PDWORD pDwOut = (PDWORD) pOut;
	*pDwOut = 0; // Zero values found

	if (outSize < 32) {
		return -1;
	}
	DWORD outCapacity = (outSize - sizeof(DWORD)) / (sizeof(DWORD) * 2);
	DWORD bufSize = outCapacity * sizeof(MIB_TCPROW_OWNER_PID) + sizeof(DWORD) + 8;
	char *pBuf = (char *) malloc(bufSize);
	if (!pBuf) {
		return -1;
	}
	DWORD ret;

	// call the blasted method
	ret = GetExtendedTcpTable(pBuf, &bufSize, false, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);

	if (!ret) {
		// Cast the buffer to the expected result type
		PMIB_TCPTABLE_OWNER_PID info = (PMIB_TCPTABLE_OWNER_PID) pBuf;

		// calculate the output capacity
		if (outCapacity > info->dwNumEntries) {
			outCapacity = info->dwNumEntries;
		}

		// Skip the count
		pDwOut++;

		// write the port then the PID
		DWORD count = outCapacity;
		for (DWORD i = 0; i < outCapacity; i++) {
			DWORD state = info->table[i].dwState;
			if (state < MIB_TCP_STATE_LISTEN || MIB_TCP_STATE_ESTAB < state) {
				count--;
				continue;
			}

			DWORD bigEndianPort = info->table[i].dwLocalPort;
			if (!bigEndianPort) {
				count--;
				continue;
			}

			*pDwOut = (bigEndianPort >> 8) | ((bigEndianPort & 0x00FF) << 8);
			pDwOut++;

			*pDwOut = info->table[i].dwOwningPid;
			pDwOut++;
		}

		*((PDWORD) pOut) = count;
	}

	free(pBuf);
	return ret;
}

int GetTcp6Ports(void *pOut, unsigned int outSize) {
	PDWORD pDwOut = (PDWORD) pOut;
	*pDwOut = 0; // Zero values found

	if (outSize < 32) {
		return -1;
	}
	DWORD outCapacity = (outSize - sizeof(DWORD)) / (sizeof(DWORD) * 2);
	DWORD bufSize = outCapacity * sizeof(MIB_TCP6ROW_OWNER_PID) + sizeof(DWORD) + 8;
	char *pBuf = (char *) malloc(bufSize);
	if (!pBuf) {
		return -1;
	}
	DWORD ret;

	// call the blasted method
	ret = GetExtendedTcpTable(pBuf, &bufSize, false, AF_INET6, TCP_TABLE_OWNER_PID_ALL, 0);

	if (!ret) {
		// Cast the buffer to the expected result type
		PMIB_TCP6TABLE_OWNER_PID info = (PMIB_TCP6TABLE_OWNER_PID) pBuf;

		// calculate the output capacity
		if (outCapacity > info->dwNumEntries) {
			outCapacity = info->dwNumEntries;
		}

		// Skip the count
		pDwOut++;

		// write the port then the PID
		DWORD count = outCapacity;
		for (DWORD i = 0; i < outCapacity; i++) {
			DWORD state = info->table[i].dwState;
			if (state < MIB_TCP_STATE_LISTEN || MIB_TCP_STATE_ESTAB < state) {
				count--;
				continue;
			}

			DWORD bigEndianPort = info->table[i].dwLocalPort;
			if (!bigEndianPort) {
				count--;
				continue;
			}

			*pDwOut = (bigEndianPort >> 8) | ((bigEndianPort & 0x00FF) << 8);
			pDwOut++;

			*pDwOut = info->table[i].dwOwningPid;
			pDwOut++;
		}

		*((PDWORD) pOut) = count;
	}

	free(pBuf);
	return ret;
}

int GetProcessName(unsigned int pid, char *pOut, long unsigned int size) {
	HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pid);
	if (!h) {
		return -1;
	}
	BOOL b = QueryFullProcessImageNameA(h, 0, pOut, &size);
//	int len = GetProcessImageFileNameA(h, pOut, size);
	CloseHandle(h); // The error can go to hell.
//	if (len < 1) {
//		return -1;
//	}
	return b? size : -1;
}
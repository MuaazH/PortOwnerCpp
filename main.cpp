#include <iostream>
#include "PortOwner.h"

#define DWORD unsigned int
#define PDWORD unsigned int*

using namespace std;

int main(int argc, char **argv) {
	cout << "Starting..." << endl;
	unsigned int size = 256;
	char *pBuf = new char[256];
	int len = GetProcessName(18400, pBuf, size);
	if (len > 0) {
		cout << "Process name is : '" << pBuf << "'" << endl;
	} else {
		cout << "Error" << endl;
	}
	delete[] pBuf;
	return 0;
}

/*
int main(int argc, char **argv) {
	cout << "Starting..." << endl;

	DWORD count = 256;
	DWORD size = sizeof(DWORD) * 2 * count + sizeof(DWORD);
	char *pOut = new char[size];

	cout << "Memory allocated... size = " << size << " max entries = " << count << endl;
	int err = GetTcp6Ports(pOut, size);
	if (!err) {
		cout << "Success" << endl;
		PDWORD pBuf = (PDWORD) pOut;
		count = *pBuf;
		pBuf++;
		cout << count << " Entries found" << endl;
		for (DWORD i = 0; i < count; i++) {
			DWORD port = *pBuf;
			pBuf++;
			DWORD pid = *pBuf;
			pBuf++;
			cout << ">> Port " << port << " is open by pid " << pid << endl;
		}
	} else {
		cout << "Error " << err << endl;
	}


	delete[] pOut;
	return 0;
}
*/
#include <windows.h>
#include <stdio.h>
#define AWPE_TIME_INTERVAL 500 // Time in milliseconds.

unsigned long __stdcall AWPE( void* pVoid )
{
	unsigned long dwRecvCall = (unsigned long)GetProcAddress( GetModuleHandle( "WS2_32.dll" ), "recv" );
	unsigned long dwSendCall = (unsigned long)GetProcAddress( GetModuleHandle( "WS2_32.dll" ), "send" );
        unsigned char bOriginal[] = "\x8B\xFF\x55\x8B\xEC\x83\xEC\x10"; // First bytes of Send/Recv
        unsigned char szBuffer[8];
	int i;
	while(true)
	{
		ReadProcessMemory(GetCurrentProcess(), (void *)dwRecvCall, szBuffer, 8, 0);
		for(i=0; i<8; i++)
		{
			if(bOriginal[i] != szBuffer[i])
			{
				WriteProcessMemory(GetCurrentProcess(), (void *)dwRecvCall, bOriginal, 8, 0);
				break;
			}         
		}
		
		ReadProcessMemory(GetCurrentProcess(), (void *)dwSendCall, szBuffer, 8, 0);
		for(i=0; i<8; i++)
		{
			if(bOriginal[i] != szBuffer[i])
			{
				WriteProcessMemory(GetCurrentProcess(), (void *)dwSendCall, bOriginal, 8, 0);
				break;
			}
		}
                
		Sleep(AWPE_TIME_INTERVAL);
	}
	return 0;
};


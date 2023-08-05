#ifndef TLSCLIENTBAS_H
#define TLSCLIENTBAS_H

extern "C" {
	typedef char* (*ResizeFunction)(int, void*);

	__declspec(dllexport) void* StartDll();
	__declspec(dllexport) void EndDll(void* DllData);
	__declspec(dllexport) void* StartThread();
	__declspec(dllexport) void EndThread(void* DllData);

	__declspec(dllexport) void RequestBas(char* InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool* NeedToStop, bool* WasError);
	__declspec(dllexport) void GetCookies(char* InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool* NeedToStop, bool* WasError);
	__declspec(dllexport) void ClearSession(char* InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool* NeedToStop, bool* WasError);
}

#endif
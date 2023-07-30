#include "tlsClientBas.h"
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include <string>

typedef char* (*Request)(char *data);

extern "C" {

	std::string FindFile(const std::string& directory, const std::string& filename)
	{
		WIN32_FIND_DATAA findData;
		HANDLE hFind = INVALID_HANDLE_VALUE;

		std::string filePath;

		std::string searchPath = directory + "\\*";
		hFind = FindFirstFileA(searchPath.c_str(), &findData);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do {
				if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0)
					{
						std::string subDirectory = directory + "\\" + findData.cFileName;
						filePath = FindFile(subDirectory, filename);

						if (!filePath.empty())
							break;
					}
				}
				else
				{
					if (strcmp(findData.cFileName, filename.c_str()) == 0)
					{
						filePath = directory + "\\" + findData.cFileName;
						break;
					}
				}
			} while (FindNextFileA(hFind, &findData));

			FindClose(hFind);
		}

		return filePath;
	}

	void* StartDll() {

		char currentDirectory[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, currentDirectory);

		std::string fileName = "tls-client-windows-64-.dll";
		std::string foundPath = FindFile(currentDirectory, fileName);

		if(!foundPath.empty()) {

			HINSTANCE module = LoadLibraryA(foundPath.c_str());

			if (module != NULL) {
				return LoadLibraryA(foundPath.c_str());
			}
		}
		else {
		}
	}

	void EndDll(void * DllData) {
		HINSTANCE module = (HINSTANCE)DllData;

		if (module != NULL) {
			FreeLibrary(module);
		}
	}

	void* StartThread() {
		return 0;
	}

	void EndThread(void * DllData) {

	}

	void RequestBas(char* InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool* NeedToStop, bool* WasError) {

		HINSTANCE module = (HINSTANCE)DllData;

		if (module != NULL) {
			Request req = (Request)(GetProcAddress(module, "request"));

			char* data = (char*)(InputJson);
			char* res = req(data);

			char* ResMemory = AllocateSpace((int)strlen(res), AllocateData);
			memcpy(ResMemory, res, strlen(res));
		}
		
	}
}
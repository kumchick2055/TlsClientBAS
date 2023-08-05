﻿#include "tlsClientBas.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <stdio.h>
#include <cstring>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include <string>
#include <random>

typedef char* (*Request)(char* data);

extern "C" {
	std::string threadSession;

	std::string get_uuid() {
		static std::random_device dev;
		static std::mt19937 rng(dev());

		std::uniform_int_distribution<int> dist(0, 15);

		const char* v = "0123456789abcdef";
		const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

		std::string res;
		for (int i = 0; i < 16; i++) {
			if (dash[i]) res += "-";
			res += v[dist(rng)];
			res += v[dist(rng)];
		}

		return res;
	}

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

	std::string updateJsonString(const std::string& jsonString, const std::string& key, const std::string& value) {
		rapidjson::Document document;
		document.SetObject();

		document.Parse(jsonString.c_str());
		if (document.HasParseError()) {
			return jsonString; // Возвращаем исходную строку, если возникла ошибка при парсинге.
		}

		const char* keyPtr = key.c_str();
		const char* valuePtr = value.c_str();

		rapidjson::Value keyJson(rapidjson::StringRef(keyPtr));
		rapidjson::Value valueJson(rapidjson::StringRef(valuePtr));

		document.AddMember(keyJson, valueJson, document.GetAllocator());

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		std::string updatedJsonString = buffer.GetString();
		return updatedJsonString;
	}

	void* StartDll() {

		char currentDirectory[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, currentDirectory);

		std::string fileName = "tls-client-windows-64-.dll";
		std::string foundPath = FindFile(currentDirectory, fileName);

		if (!foundPath.empty()) {
			HINSTANCE loadLibrary = LoadLibraryA(foundPath.c_str());
			threadSession = get_uuid();

			if (loadLibrary != NULL) {
				return loadLibrary;
			}
		}
		
		return NULL;
	}

	void EndDll(void* DllData) {
		HINSTANCE library = reinterpret_cast<HINSTANCE>(DllData);

		if (library != NULL) {
			Request req = reinterpret_cast<Request>(GetProcAddress(library, "destroySession"));

			std::string result = "{\"sessionId\":\"" + threadSession + "\"}";
			req(result.data());
		}
	}

	void* StartThread() {
		return 0;
	}

	void EndThread(void* DllData) {

	}

	void RequestBas(char* InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool* NeedToStop, bool* WasError) {
		HINSTANCE library = reinterpret_cast<HINSTANCE>(DllData);

		if (library != NULL) {
			Request req = reinterpret_cast<Request>(GetProcAddress(library, "request"));
			std::string json = InputJson;
			std::string updatedJsonString = updateJsonString(json, "sessionId", threadSession);
			
			char* res = req(updatedJsonString.data());

			std::string responseStr = res;
			std::string responseId = responseStr.substr(7, 36);

			char* ResMemory = AllocateSpace(static_cast<int>(strlen(res)), AllocateData);
			memcpy(ResMemory, res, strlen(res));

			Request freeMemory = reinterpret_cast<Request>(GetProcAddress(library, "freeMemory"));
			freeMemory(const_cast<char*>(responseId.c_str()));
		}

	}

	void GetCookies(char* InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool* NeedToStop, bool* WasError) {
		HINSTANCE library = reinterpret_cast<HINSTANCE>(DllData);

		if (library != NULL) {
			Request req = reinterpret_cast<Request>(GetProcAddress(library, "getCookiesFromSession"));
			std::string json = InputJson;
			std::string updatedJsonString = updateJsonString(json, "sessionId", threadSession);

			char* res = req(updatedJsonString.data());

			char* ResMemory = AllocateSpace(static_cast<int>(strlen(res)), AllocateData);
			memcpy(ResMemory, res, strlen(res));
		}
	}

	void ClearSession(char* InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool* NeedToStop, bool* WasError) {
		HINSTANCE library = reinterpret_cast<HINSTANCE>(DllData);

		if (library != NULL) {
			Request req = reinterpret_cast<Request>(GetProcAddress(library, "destroySession"));

			std::string result = "{\"sessionId\":\"" + threadSession + "\"}";
			req(result.data());
		}
	}
}
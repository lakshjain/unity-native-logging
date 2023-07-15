#pragma once
#include "IUnityLog.h"

#include <string>

//holding the unity log ptr until plugin unloads
static IUnityLog* unityLogPtr = nullptr;

#define FORMAT(MESSAGE) std::string("[" + std::string(__FILE__) + ":" + std::to_string(__LINE__) + "] " + MESSAGE).c_str()
#define DEBUG_LOG(PTR, MESSAGE) UNITY_LOG(PTR, FORMAT(MESSAGE))
#define DEBUG_WARNING(PTR, MESSAGE) UNITY_LOG_WARNING(PTR, FORMAT(MESSAGE))
#define DEBUG_ERROR(PTR, MESSAGE) UNITY_LOG_ERROR(PTR, FORMAT(MESSAGE))

extern "C"
{
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfacesPtr)
	{
		//Get the unity log pointer once the Unity plugin gets loaded
		unityLogPtr = unityInterfacesPtr->Get<IUnityLog>();
	}

	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginUnload()
	{
		//Clearing the log ptr on unloading the plugin
		unityLogPtr = nullptr;
	}

	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API TestLog()
	{
		//Generate different type of logs on unity console
		UNITY_LOG(unityLogPtr, "log from dll");
		UNITY_LOG_WARNING(unityLogPtr, "log warning from dll");
		UNITY_LOG_ERROR(unityLogPtr, "log error from dll");

		//Wrapper on above loggers to provide more info in Logs regarding file and line number
		DEBUG_LOG(unityLogPtr, "more informative log from dll");
		DEBUG_WARNING(unityLogPtr, "more informative warning from dll");
		DEBUG_ERROR(unityLogPtr, "more informative error warning from dll");

	}
}
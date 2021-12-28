﻿#pragma once

// ref: https://docs.microsoft.com/en-us/cpp/cpp/using-dllimport-and-dllexport-in-cpp-classes?view=msvc-170
// ref: https://stackoverflow.com/questions/2479784/exporting-static-data-in-a-dll
#ifdef EYE_PLATFORM_WINDOWS
	#ifdef EYE_BUILD_DLL
		#define EYE_API __declspec(dllexport)
	#else
		#define EYE_API __declspec(dllimport)
	#endif // EYE_BUILD_DLD
#else
	#error Eye Engine only support Windows yet!
#endif // EYE_PLATFORM_WINDOWS

#define BIT(x) (1 << x) // 0001 / 0010 / 0100 / ...
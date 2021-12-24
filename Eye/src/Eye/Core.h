#pragma once

#ifdef EYE_PLATFORM_WINDOWS
	#ifdef EYE_BUILD_DLL
		#define EYE_API __declspec(dllexport)
	#else
		#define EYE_API __declspec(dllimport)
	#endif // EYE_BUILD_DLD
#else
	#error Eye Engine only support Windows yet!
#endif // EYE_PLATFORM_WINDOWS
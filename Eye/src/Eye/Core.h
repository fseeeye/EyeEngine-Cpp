#pragma once

// ref: https://docs.microsoft.com/en-us/cpp/cpp/using-dllimport-and-dllexport-in-cpp-classes?view=msvc-170
// ref: https://stackoverflow.com/questions/2479784/exporting-static-data-in-a-dll
#ifdef EYE_PLATFORM_WINDOWS
	#if EYE_DYNAMIC_LINK
		#ifdef EYE_BUILD_DLL
			#define EYE_API __declspec(dllexport)
		#else
			#define EYE_API __declspec(dllimport)
		#endif // EYE_BUILD_DLD
	#else
		#define EYE_API
	#endif // EYE_DYNAMIC_LINK	
#else
	#error Eye Engine only support Windows yet!
#endif // EYE_PLATFORM_WINDOWS

#ifdef EYE_DEBUG
	#define EYE_ENABLE_ASSERTS
#endif

#ifdef EYE_ENABLE_ASSERTS
	#define EYE_ASSERT(x, ...) { if (!(x)) { EYE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define EYE_CORE_ASSERT(x, ...) { if (!(x)) { EYE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define EYE_ASSERT(x, ...)
	#define EYE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x) // 0001 / 0010 / 0100 / ...

#define EYE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#pragma once

/* Platform detection using predefined macros */
// ref: https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
// Windows x64/x86
#ifdef _WIN32 // Defined as 1 when the compilation target is 32-bit ARM, 64-bit ARM, x86, or x64. Otherwise, undefined.
	// Windows x64
	#ifdef _WIN64 // Defined as 1 when the compilation target is 64-bit ARM or x64. Otherwise, undefined.
		#define EYE_PLATFORM_WINDOWS
	// Windows x86
	#else
		#define EYE_PLATFORM_WINDOWS32
		#error "Eye Engine does not support x86 Builds yet."
	#endif
// Apple
// tips: TARGET_OS_MAC exists on all the platforms
// so we must check all of them (in this order)
// to ensure that we're running on MAC
// and not some other Apple platform
#elif defined(_APPLE_) || defined(_MACH_)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "Eye Engine does not support IOS simulator yet."
	#elif TARGET_OS_IPHONE == 1
		#define HZ_PLATFORM_IOS
		#error "Eye Engine does not support IOS yet."
	#elif TARGET_OS_MAC == 1
		#define HZ_PLATFORM_MACOSX
		#error "Eye Engine does not support MacOS yet."
	#else
		#define HAZEL_API __declspec(dllimport)
		#error "Unknown Apple platform."
	#endif
// Android
// We also have to check __ANDROID__ before __linux__
// since android is based on the linux kernel
// it has __linux__ defined
#elif defined(__ANDROID__)
	#define HZ_PLATFORM_ANDROID
	#error "Eye Engine does not support Android yet."
// Linux
#elif defined(__linux__)
	#define HZ_PLATFORM_LINUX
	#error "Eye Engine does not support Linux yet."
#else
	#error "Unknown platform."
#endif // End of platform detection

/* DLL support */
#ifdef EYE_PLATFORM_WINDOWS
	#if EYE_DYNAMIC_LINK
		// ref: https://docs.microsoft.com/en-us/cpp/cpp/using-dllimport-and-dllexport-in-cpp-classes?view=msvc-170
		// ref: https://stackoverflow.com/questions/2479784/exporting-static-data-in-a-dll
		#ifdef EYE_BUILD_DLL
			#define EYE_API __declspec(dllexport)
		#else
			#define EYE_API __declspec(dllimport)
		#endif // EYE_BUILD_DLD
	#else
		#define EYE_API
	#endif // EYE_DYNAMIC_LINK	
#else
	#error "Eye Engine only support Windows x64!"
#endif // End of DLL support

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


#include <memory>

namespace Eye {

	// TODO
	//template<typename T>
	//class Scope
	//{
	//};

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using StrongRef = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr StrongRef<T> CreateStrongRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

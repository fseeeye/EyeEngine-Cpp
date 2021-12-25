#pragma once

#ifdef EYE_PLATFORM_WINDOWS

// All codes below will be included into Game Application
extern Eye::Application* Eye::CreateApplication();

int main(int argc, char** argv)
{
	Eye::Log::Init();
	EYE_CORE_WARN("Initialized!");
	int test_a = 5;
	EYE_INFO("Eyes Opened! Test Var={0}", test_a);

	auto app = Eye::CreateApplication();
	app->Run();
	delete app;
}

#endif // EYE_PLATFORM_WINDOWS
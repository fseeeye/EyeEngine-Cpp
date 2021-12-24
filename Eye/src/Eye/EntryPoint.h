#pragma once

#ifdef EYE_PLATFORM_WINDOWS

// All codes below will be included into Game Application
extern Eye::Application* Eye::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Eye::CreateApplication();
	app->Run();
	delete app;
}

#endif // EYE_PLATFORM_WINDOWS
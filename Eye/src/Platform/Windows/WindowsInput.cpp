#include "eyepch.h"
#include "WindowsInput.h"

#include "Eye/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Eye {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// TODO: EYE Key to GLFW Key
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT; // Waring: only GLFW_PRESS
	}

	bool WindowsInput::IsMouseButtonPreesedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// TODO: EYE Button to GLFW Key
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos_d, ypos_d;
		glfwGetCursorPos(window, &xpos_d, &ypos_d);
		return { static_cast<float>(xpos_d), static_cast<float>(ypos_d) };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [xpos, _ypos] = GetMousePositionImpl();
		return xpos;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [_xpos, ypos] = GetMousePositionImpl();
		return ypos;
	}

}

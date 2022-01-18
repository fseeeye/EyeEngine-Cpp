#include <Eye.h>

#include <imgui/imgui.h>

class ExampleLayer : public Eye::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//EYE_TRACE("ExampleLayer::Update");

		if (Eye::Input::IsKeyPressed(EYE_KEY_TAB))
			EYE_TRACE("key(TAB) is pressed! (poll)");
	}

	void OnImGuiRender() override
	{
		// TODO: solve link error
		//ImGui::Begin("TestGameApp");
		//ImGui::Text("Eye is Openning!");
		//ImGui::End();
	}

	void OnEvent(Eye::Event& event) override
	{
		//EYE_TRACE("ExampleLayer::OnEvent: {0}", event);
		if (event.GetEventType() == Eye::EventType::KeyPressed)
		{
			Eye::KeyPressedEvent& e = (Eye::KeyPressedEvent&)event;
			if (e.GetKeyCode() == EYE_KEY_TAB)
				EYE_TRACE("key(TAB) is pressed! (event)");
			EYE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Game : public Eye::Application
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
	}

	~Game()
	{

	}
};

Eye::Application* Eye::CreateApplication()
{
	return new Game();
}
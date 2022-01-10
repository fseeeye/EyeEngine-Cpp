#include <Eye.h>

class ExampleLayer : public Eye::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//EYE_TRACE("ExampleLayer::Update");
	}

	void OnEvent(Eye::Event& event) override
	{
		EYE_TRACE("ExampleLayer::OnEvent: {0}", event);
	}
};

class Game : public Eye::Application
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Eye::ImGuiLayer());
	}

	~Game()
	{

	}
};

Eye::Application* Eye::CreateApplication()
{
	return new Game();
}
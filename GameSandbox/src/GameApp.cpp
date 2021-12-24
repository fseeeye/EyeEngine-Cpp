#include <Eye.h>

class Game : public Eye::Application
{
public:
	Game()
	{

	}

	~Game()
	{

	}
};

Eye::Application* Eye::CreateApplication()
{
	return new Game();
}
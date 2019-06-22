#include "engine/GameWindow.h"

void Update(double dt)
{
	
}

int main(int argc, char* argv[])
{
	engine::GameWindow* window = new engine::GameWindow("shipgame", Update);
}

#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <conio.h>

#include "Game.h"

void Initialize();
void GetInput();
void Update(float deltaTime);
void Render();
void Shutdown();
char getKeyboardInput();

bool g_exitGame = true;
Game g_game;
std::future<char> future;

int main()
{
	Initialize();

	while (!g_exitGame)
	{
		GetInput();
		Update(0.0f);
		Render();
	}

	Shutdown();

	return 0;
}

void Initialize()
{
	future = std::async(std::launch::async, getKeyboardInput);

	g_game.OnInit();

	g_exitGame = false;
}

void GetInput()
{
	char ch = Game::EMPTY_KEY;
	
	if (future.wait_for(std::chrono::milliseconds(100)) == std::future_status::ready) {
		ch = future.get();
		g_game.OnInput(ch);
		future = std::async(std::launch::async, getKeyboardInput);
	}
}

void Update(float deltaTime)
{
	g_exitGame = g_game.OnUpdate(deltaTime);
}

void Render()
{
	g_game.OnRender();
}

void Shutdown()
{
	g_game.OnShutdown();
}

char getKeyboardInput()
{
	return _getch();
}
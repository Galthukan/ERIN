#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "AssetManager.h"

// test input
#include "GameObject.h"

class Engine
{
public:
	Engine();
	~Engine();

	void processInput();
	void update(int deltaTimeMs);
	int render(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow);

	HWND InitWindow(HINSTANCE hInstance);

	bool getRunning() { return running; };
private:
	bool running;
	Graphics* graphics;
	GameLogic* gameLogic;
	AssetManager* assetManager;

	// test input
	GameObject* gameObject;
};

#endif // !ENGINE_H
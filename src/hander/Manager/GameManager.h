#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "SingletonInstanceTemplate.h"
#include "../LogOutput.h"



/** GameManager.h 定义了游戏管理器
 * 
 *  该类负责初始化各个 SDL 库，引入其他类实现游戏功能。
 * 	该类为单例模式
 */
class GameManager : public SITemplate<GameManager> {
	friend class SITemplate<GameManager>;

public:
	int RunGame(int argc, char** argv) {
		(void)argc;
		(void)argv;
		while (IsProjectRunning) {
			while (SDL_PollEvent(&SDLEvent)) { On_Input(); }
			On_Updata();
			SDL_RenderPresent(SDLRenderer);
		}
		return 0;
	}
	
protected:
	GameManager() {
		// SDL initialization and assertion for each library 
		SDLInitAssert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL");
		SDLInitAssert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image");
		SDLInitAssert(Mix_Init(MIX_INIT_MP3), u8"SDL_Mixer");
		SDLInitAssert(!TTF_Init(), u8"SDL_TTF");
		// SDL_mixer audio settings
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		// SDL_image settings 
		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
		// Create and assert SDL window 
		SDLWindow = SDL_CreateWindow(u8"MeowWow520's Plants v.s. Zombies", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			WindowWidth, WindowHeight, 
			SDL_WINDOW_SHOWN);
		SDLInitAssert(SDLWindow, u8"SDL Window");
		// Create and assert SDL renderer
		SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, 
			SDL_RENDERER_ACCELERATED | 
			SDL_RENDERER_PRESENTVSYNC | 
			SDL_RENDERER_TARGETTEXTURE);
		SDLInitAssert(SDLRenderer, u8"SDL Renderer");
	};
	~GameManager() {
		// SDL library quit
		SDL_DestroyRenderer(SDLRenderer);
		SDL_DestroyWindow(SDLWindow);
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	};

private:
	int WindowWidth{1280};
	int WindowHeight{720};
	bool IsProjectRunning = true;
	const double CompareDelta = (double)(1000.0 / 60.0);
	Uint64 LastCounter = SDL_GetPerformanceCounter();
	const Uint64 CounterFrequency = SDL_GetPerformanceCounter();
	SDL_Event SDLEvent;
	SDL_Point PosCursor = { 0,0 };
	SDL_Window* SDLWindow = nullptr;
	SDL_Renderer* SDLRenderer = nullptr;

	void SDLInitAssert(bool flag, const char* InitType) {
		if (flag) {
			LogOutput::PrintfCurrentTime();
			const std::string SDLllbSuccessfulMsg = u8"loading successfully!";
			std::cout << InitType << " " << SDLllbSuccessfulMsg << std::endl;
			return;
		}
		const char SDLlibErrorMsg[24] = u8"SDL Library Load Error!";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDLlibErrorMsg, InitType, SDLWindow);
	}
	void ClearScreen() {
		SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
		SDL_RenderClear(SDLRenderer);
	}
	void LimitFrameRate() {
		Uint64 CurrentCounter = SDL_GetPerformanceCounter();
		double Detla = (double)(CurrentCounter - LastCounter) / CounterFrequency;
		LastCounter = CurrentCounter;
		if (Detla * 1000 < CompareDelta) SDL_Delay((Uint32)(CompareDelta - Detla * 1000));
	}
	void On_Input() {
		switch (SDLEvent.type) {
			// Quit event
		    case SDL_QUIT:
				IsProjectRunning = false;
				break;
			// Mouse button event
		    case SDL_MOUSEMOTION:
				PosCursor.x = SDLEvent.motion.x;
				PosCursor.y = SDLEvent.motion.y;
				break;
		}
	}
	void On_Updata() {
		LimitFrameRate();
		ClearScreen();
	}
	
};
#endif // !GAMEMANAGER_H
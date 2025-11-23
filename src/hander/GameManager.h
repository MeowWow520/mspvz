#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "SingletonInstanceTemplate.h"
#include "LogOutput.h"



class GameManager : public Manager<GameManager> {
	friend class Manager<GameManager>;
public:
	int RunGame(int argc, char** argv) {
		(void)argc;
		(void)argv;
		// Main loop
		while (IsProjectRunning) {
			// Input event
			while (SDL_PollEvent(&SDLEvent)) { On_Input(); }
			LimitFrameRate();
			On_Updata();

			// Set and Clear screen
			SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
			SDL_RenderClear(SDLRenderer);

			// Draw;
			On_Renderer();
			SDL_RenderPresent(SDLRenderer);
		}
		return 0;
	}
protected:
	GameManager() {
		// SDL initialization and assertion for each library 
		SDL_Init_Assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL");
		SDL_Init_Assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image");
		SDL_Init_Assert(Mix_Init(MIX_INIT_MP3), u8"SDL_Mixer");
		SDL_Init_Assert(!TTF_Init(), u8"SDL_TTF");
		// SDL_mixer audio settings
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		// SDL_image settings 
		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
		// Create and assert SDL window 
		SDLWindow = SDL_CreateWindow(u8"MeowWow520's Plants v.s. Zombies", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1980, 1080, SDL_WINDOW_SHOWN);
		SDL_Init_Assert(SDLWindow, u8"SDL Window");
		// Create and assert SDL renderer
		SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		SDL_Init_Assert(SDLRenderer, u8"SDL Renderer");
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
	bool IsProjectRunning = true;
	const double COMPARE_DELTA = (double)(1000.0 / 60.0);
	Uint64 Last_Counter = SDL_GetPerformanceCounter();
	const Uint64 COUNTER_FREQUENCY = SDL_GetPerformanceCounter();
	SDL_Event SDLEvent;
	SDL_Point PosCursor = { 0,0 };
	SDL_Window* SDLWindow = nullptr;
	SDL_Renderer* SDLRenderer = nullptr;
	void SDL_Init_Assert(bool flag, const char* c_Init_Type) {

		if (flag) {
			LogOutput::PrintfCurrentTime();
			const std::string STR_LOADING_SUCCESSFUL_MSG = u8"loading successfully!";
			std::cout << c_Init_Type << " " << STR_LOADING_SUCCESSFUL_MSG << std::endl;
			return;
		}
		const char LAOD_ERROR_MSG[24] = u8"SDL Library Load Error!";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, LAOD_ERROR_MSG, c_Init_Type, SDLWindow);
	}
	void On_Input() {}
	void On_Updata() {}
	void On_Renderer() {}
	void LimitFrameRate() {
		Uint64 Current_Counter = SDL_GetPerformanceCounter();
		double Detla = (double)(Current_Counter - Last_Counter) / COUNTER_FREQUENCY;
		Last_Counter = Current_Counter;
		if (Detla * 1000 < COMPARE_DELTA) SDL_Delay((Uint32)(COMPARE_DELTA - Detla * 1000));
	}
};
#endif // !GAMEMANAGER_H

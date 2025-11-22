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
		return 0;
	}
protected:
	GameManager() {
		SDL_Init_Assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL");
		SDL_Init_Assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image");
		SDL_Init_Assert(Mix_Init(MIX_INIT_MP3), u8"SDL_Mixer");
		SDL_Init_Assert(!TTF_Init(), u8"SDL_TTF");
	};
	~GameManager() = default;
private:
	bool IsProjectRunning = true;
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
};
#endif // !GAMEMANAGER_H

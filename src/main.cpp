#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED


#include "hander/GameManager.h"


int main(int argc, char** argv)
{
	return GameManager::Instance()->RunGame(argc, argv);
}
#include "Game.h"

#include <SDL3/SDL_events.h>

Game *game = nullptr;

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int main(int argc, char *argv[])
{
  printf("SDL Version: %d.%d\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

  Uint32 frameStart;
  int frameTime;

  SDL_Event e;

  game = TheGame::Instance();
  game->init("GameWindow", 1024, 768, false);

  while (game->running())
  {
    frameStart = SDL_GetTicks();

      // Poll events
    while (SDL_PollEvent(&e))
    {
        game->handleEvents(e);   // Pass the event to the game/state
    }
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (FRAME_DELAY > frameTime) {
      SDL_Delay(FRAME_DELAY - frameTime);
    }
  }

  game->clean();

  return 0;
}


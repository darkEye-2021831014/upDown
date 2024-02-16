#include "Background.hpp"

int main(int argc, char **argv)
{
    Background background;
    background.setBackgroundTexture("./Background/background.bmp");
    background.setObstacleWidth(30);

    while (background.getGameState())
    {
        background.processInput();
        SDL_RenderClear(background.getRenderer());
        background.renderBackground();
        background.detectCollosion();
        SDL_RenderPresent(background.getRenderer());
    }
    background.destroyWindow();

    return 0;
}
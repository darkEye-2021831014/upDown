#include <string>
#include <SDL2/SDL.h>
using namespace std;

class Background
{
public:
    Background()
    {
        initializeWindow();
        initializeBackground();
    }
    SDL_Renderer *getRenderer();
    void processInput();
    void setGameState(bool state);
    bool getGameState();
    int getScreenWidth();
    int getScreenHeight();
    void renderBackground();
    void setBackgroundTexture(string filePath);
    int getVSyncStatus();
    void setObstacleWidth(int width);
    void detectCollosion();
    void destroyWindow();

private:
    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
    bool gameIsRunning = false;
    const int SCREEN_WIDTH = 1080,
              SCREEN_HEIGHT = 540,
              ObstacleHeightMinimum = 100,
              characterHeight = 50,
              characterWidth = 80,
              totalObstacleInARow = 3;
    int vSyncActive,
        obstacleWidth = 30,
        freeSpace = 5,
        obstacleX = getScreenWidth() / totalObstacleInARow;
    SDL_Rect backgroundLeftFront, backgroundLeftBack, backgroundTopFront, backgroundTopBack,
        obstacleTopOne, obstacleTopTwo, obstacleTopThree, obstacleBottomOne, obstacleBottomTwo, obstacleBottomThree, charaacterControl;
    SDL_Texture *backgroundTexture = nullptr,
                *obstacleTexture = nullptr,
                *characterTexture = nullptr;

    void initializeWindow();
    void initializeBackground();
};
#include "Background.hpp"

void Background::initializeWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Failed To Initialize SDL!\nError: %s", SDL_GetError());
        return;
    }
    window = SDL_CreateWindow(
        "upDown",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);
    if (!window)
    {
        SDL_Log("Failed To Create Window!\nError: %s", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("Failed To Create Renderer!\nError: %s", SDL_GetError());
        return;
    }

    // vSyncActive = 0 means success and any non zero value for failure
    vSyncActive = SDL_RenderSetVSync(renderer, 1);

    gameIsRunning = true;
}

void Background::initializeBackground()
{
    // background image containers
    backgroundLeftFront = {0, 0, getScreenWidth(), getScreenHeight()};
    backgroundLeftBack = {-getScreenWidth(), 0, getScreenWidth(), getScreenHeight()};
    backgroundTopFront = {0, 0, getScreenWidth(), getScreenHeight()};
    backgroundTopBack = {0, -getScreenHeight(), getScreenWidth(), getScreenHeight()};

    obstacleTexture = SDL_CreateTextureFromSurface(getRenderer(), SDL_LoadBMP("Background/obstacle.bmp"));

    // obstacle containers
    srand((unsigned)time(0));
    int obstacleHeight =
        ObstacleHeightMinimum + rand() % (getScreenHeight() - ObstacleHeightMinimum) - characterHeight * freeSpace;
    obstacleTopOne = {obstacleX, 0, obstacleWidth, obstacleHeight};
    obstacleBottomOne = {obstacleX, obstacleHeight + freeSpace * characterHeight, obstacleWidth, (getScreenHeight() - obstacleHeight) - freeSpace * characterHeight};

    obstacleHeight = ObstacleHeightMinimum + rand() % (getScreenHeight() - ObstacleHeightMinimum) - characterHeight * freeSpace;
    obstacleTopTwo = {2 * obstacleX, 0, obstacleWidth, obstacleHeight};
    obstacleBottomTwo = {2 * obstacleX, obstacleHeight + freeSpace * characterHeight, obstacleWidth, (getScreenHeight() - obstacleHeight) - freeSpace * characterHeight};

    obstacleHeight = ObstacleHeightMinimum + rand() % (getScreenHeight() - ObstacleHeightMinimum) - characterHeight * freeSpace;
    obstacleTopThree = {3 * obstacleX, 0, obstacleWidth, obstacleHeight};
    obstacleBottomThree = {3 * obstacleX, obstacleHeight + freeSpace * characterHeight, obstacleWidth, (getScreenHeight() - obstacleHeight) - freeSpace * characterHeight};

    // character container
    charaacterControl = {0, 0, characterWidth, characterHeight};
    characterTexture = SDL_CreateTextureFromSurface(getRenderer(), SDL_LoadBMP("Background/character.bmp"));
}

void Background::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            gameIsRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                gameIsRunning = false;
                break;
            case SDLK_UP:
                charaacterControl.y -= 50;
                break;

            default:
                break;
            }
        default:
            break;
        }
    }
}

void Background::setBackgroundTexture(string filePath)
{
    // load background texture
    backgroundTexture = SDL_CreateTextureFromSurface(
        getRenderer(), SDL_LoadBMP(filePath.c_str()));
}

void Background::renderBackground()
{
    // handle the movements of the background
    backgroundLeftFront.x++;
    backgroundLeftBack.x++;
    backgroundTopFront.y++;
    backgroundTopBack.y++;
    if (backgroundLeftFront.x >= SCREEN_WIDTH || backgroundLeftBack.x >= SCREEN_WIDTH)
    {
        if (backgroundLeftFront.x > backgroundLeftBack.x)
            backgroundLeftFront.x = -SCREEN_WIDTH;
        else
            backgroundLeftBack.x = -SCREEN_WIDTH;
    }
    if (backgroundTopFront.y >= SCREEN_HEIGHT || backgroundTopBack.y >= SCREEN_HEIGHT)
    {
        if (backgroundTopFront.y > backgroundTopBack.y)
            backgroundTopFront.y = -SCREEN_HEIGHT;
        else
            backgroundTopBack.y = -SCREEN_HEIGHT;
    }

    // render background texture
    SDL_SetTextureBlendMode(backgroundTexture, SDL_BLENDMODE_ADD);
    SDL_RenderCopy(getRenderer(), backgroundTexture, NULL, &backgroundLeftFront);
    SDL_RenderCopy(getRenderer(), backgroundTexture, NULL, &backgroundLeftBack);
    SDL_RenderCopy(getRenderer(), backgroundTexture, NULL, &backgroundTopFront);
    SDL_RenderCopy(getRenderer(), backgroundTexture, NULL, &backgroundTopBack);

    // handle obstacle movements
    obstacleTopOne.x -= 5;
    obstacleTopTwo.x -= 5;
    obstacleTopThree.x -= 5;
    obstacleBottomOne.x -= 5;
    obstacleBottomTwo.x -= 5;
    obstacleBottomThree.x -= 5;
    if (obstacleTopOne.x + obstacleWidth < 0 || obstacleTopTwo.x + obstacleWidth < 0 || obstacleTopThree.x + obstacleWidth < 0)
    {
        int minn = min(obstacleTopOne.x, min(obstacleTopTwo.x, obstacleTopThree.x));

        int obstacleHeight =
            ObstacleHeightMinimum + rand() % (getScreenHeight() - ObstacleHeightMinimum) - characterHeight * freeSpace;
        if (minn == obstacleTopOne.x)
        {
            obstacleTopOne = {getScreenWidth(), 0, obstacleWidth, obstacleHeight};
            obstacleBottomOne = {getScreenWidth(), obstacleHeight + freeSpace * characterHeight, obstacleWidth, (getScreenHeight() - obstacleHeight) - freeSpace * characterHeight};
        }
        else if (minn == obstacleTopTwo.x)
        {
            obstacleTopTwo = {getScreenWidth(), 0, obstacleWidth, obstacleHeight};
            obstacleBottomTwo = {getScreenWidth(), obstacleHeight + freeSpace * characterHeight, obstacleWidth, (getScreenHeight() - obstacleHeight) - freeSpace * characterHeight};
        }
        else
        {
            obstacleTopThree = {getScreenWidth(), 0, obstacleWidth, obstacleHeight};
            obstacleBottomThree = {getScreenWidth(), obstacleHeight + freeSpace * characterHeight, obstacleWidth, (getScreenHeight() - obstacleHeight) - freeSpace * characterHeight};
        }
    }

    // render obstacle
    SDL_RenderCopy(getRenderer(), obstacleTexture, NULL, &obstacleTopOne);
    SDL_RenderCopy(getRenderer(), obstacleTexture, NULL, &obstacleBottomOne);
    SDL_RenderCopy(getRenderer(), obstacleTexture, NULL, &obstacleTopTwo);
    SDL_RenderCopy(getRenderer(), obstacleTexture, NULL, &obstacleBottomTwo);
    SDL_RenderCopy(getRenderer(), obstacleTexture, NULL, &obstacleTopThree);
    SDL_RenderCopy(getRenderer(), obstacleTexture, NULL, &obstacleBottomThree);

    // handle character movements
    charaacterControl.y += 3;
    // render character
    SDL_RenderCopy(getRenderer(), characterTexture, NULL, &charaacterControl);
}

int Background::getVSyncStatus()
{
    return vSyncActive;
}

void Background::setObstacleWidth(int width)
{
    obstacleWidth = width;
}

void Background::setGameState(bool state)
{
    gameIsRunning = state;
}

bool Background::getGameState()
{
    return gameIsRunning;
}

SDL_Renderer *Background::getRenderer()
{
    return renderer;
}

int Background::getScreenWidth()
{
    return SCREEN_WIDTH;
}

int Background::getScreenHeight()
{
    return SCREEN_HEIGHT;
}

void Background::detectCollosion()
{
    if (SDL_HasIntersection(&obstacleTopOne, &charaacterControl) ||
        SDL_HasIntersection(&obstacleBottomOne, &charaacterControl) ||
        SDL_HasIntersection(&obstacleTopTwo, &charaacterControl) ||
        SDL_HasIntersection(&obstacleBottomTwo, &charaacterControl) ||
        SDL_HasIntersection(&obstacleTopThree, &charaacterControl) ||
        SDL_HasIntersection(&obstacleBottomThree, &charaacterControl))
    {
        setGameState(false);
        return;
    }
    if (charaacterControl.y < 0 || charaacterControl.y > (getScreenHeight() - charaacterControl.h))
        setGameState(false);
}

void Background::destroyWindow()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyTexture(obstacleTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
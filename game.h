#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameFramework.h"
#include "physics2D.h"
#include "PadClass.h"
#include "BrickClass.h"
#include "BallClass.h"
#include "LevelClass.h"

enum TGameScreen {
    SplashScreen,
    NextLevelScreen,
    WonGameScreen,
    LostGameScreen,
    GameScreen
};

class CGame : public CCustomApplication {
    // Class fields;
    public:

    protected:

    private:
        CLevel* FLevel;
        CPad* FPad;
        CBall* FBall;
        TNumericFont FFont;
        unsigned int FBallTexture,
                     FPadTexture,
                     FBackgroundTexture,
                     FSplashScreenTexture,
                     FNextLevelTexture,
                     FWonGameTexture,
                     FLostGameTexture;
        unsigned int FLifes,
                     FCurrentLevel,
                     FMaxLevel,
                     FPoints;
        float FCurrentTime,
              FMaxTime;
        TGameScreen FCurrentScreen;
    // Class functions
    public: // Constructor/destructor.
        CGame(int AWidth, int AHeight);
        virtual ~CGame();
    public:

    protected:
        virtual void Logic() override;
        virtual void Render() override;
    private:
        bool CollisionVertical(TCircle ABall, TRectangle ARectangle);
        bool CollisionHorizontal(TCircle ABall, TRectangle ARectangle);
        bool CollisionWithBottom(TCircle ABall, TRectangle ARectangle);

        void DrawSplashScreen();
        void DrawNextLevelScreen();
        void DrawWonGameScreen();
        void DrawLostGameScreen();
        void DrawGameScreen();

        void GameLogic();
        void TimeScreenLogic();
        void KeyScreenLogic();
};

#endif // GAME_H_INCLUDED

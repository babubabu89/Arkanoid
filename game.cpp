#include "game.h"

// CGame Class
// ===== Constructor/Destructor =====

CGame::CGame(int AWidth, int AHeight) : CCustomApplication(AWidth, AHeight) {
    FBackgroundTexture = ImgToTexture("graphics/Background.png");
    FLevel = new CLevel(FBackgroundTexture);

    FPadTexture = ImgToTexture("graphics/Pad.png");
    FPad = new CPad (0.0f - 1.0f, 10.0f, FPadTexture);

    FBallTexture = ImgToTexture("graphics/Ball.png");
    FBall = new CBall (0.0f - 0.125f, 10.0f - 0.26f, FBallTexture);

    FSplashScreenTexture = ImgToTexture("graphics/SplashScreen.png");
    FNextLevelTexture = ImgToTexture("graphics/NextLevel.png");
    FWonGameTexture = ImgToTexture("graphics/WonGame.png");
    FLostGameTexture = ImgToTexture("graphics/LostGame.png");

    FFont = LoadFont(1.0f);

    FLifes = 3;

    FCurrentTime = 0.0f;
    FMaxTime = 1.0f;

    FCurrentLevel = 1;
    FMaxLevel = 4;

    FCurrentScreen = SplashScreen;
}

CGame::~CGame() {
    delete FPad;
    delete FBall;
    delete FLevel;
    DeleteTexture(FBallTexture);
    DeleteTexture(FPadTexture);
    DeleteTexture(FSplashScreenTexture);
    DeleteTexture(FNextLevelTexture);
    DeleteTexture(FWonGameTexture);
    DeleteTexture(FLostGameTexture);
    FreeFont(&FFont);
}

// ===== Public =====
// ===== Protected =====

void CGame::Logic() {
    switch (FCurrentScreen) {
        case SplashScreen:
            TimeScreenLogic();
            break;
        case NextLevelScreen:
            TimeScreenLogic();
            break;
        case WonGameScreen:
            KeyScreenLogic();
            break;
        case LostGameScreen:
            KeyScreenLogic();
            break;
        case GameScreen:
            GameLogic();
            break;
    }
}

void CGame::Render() {

    switch (FCurrentScreen) {
        case SplashScreen:
            DrawSplashScreen();
            break;
        case NextLevelScreen:
            DrawNextLevelScreen();
            break;
        case WonGameScreen:
            DrawWonGameScreen();
            break;
        case LostGameScreen:
            DrawLostGameScreen();
            break;
        case GameScreen:
            DrawGameScreen();
            break;
    }
}

// ===== Private =====

bool CGame::CollisionVertical(TCircle ABall, TRectangle ARectangle) {
    TSegment s1, s2;

    s1.a.x = ARectangle.LeftTopCorner.x;
    s1.a.y = ARectangle.LeftTopCorner.y;
    s1.b.x = ARectangle.LeftTopCorner.x;
    s1.b.y = ARectangle.LeftTopCorner.y + ARectangle.Height;

    s2.a.x = ARectangle.LeftTopCorner.x + ARectangle.Width;
    s2.a.y = ARectangle.LeftTopCorner.y;
    s2.b.x = ARectangle.LeftTopCorner.x + ARectangle.Width;
    s2.b.y = ARectangle.LeftTopCorner.y + ARectangle.Height;


    if (Collision(ABall, s1) || Collision(ABall, s2))
        return true;
    else
        return false;
}

bool CGame::CollisionHorizontal(TCircle ABall, TRectangle ARectangle) {
    TSegment s1, s2;

    s1.a.x = ARectangle.LeftTopCorner.x;
    s1.a.y = ARectangle.LeftTopCorner.y;
    s1.b.x = ARectangle.LeftTopCorner.x + ARectangle.Width;
    s1.b.y = ARectangle.LeftTopCorner.y;

    s2.a.x = ARectangle.LeftTopCorner.x;
    s2.a.y = ARectangle.LeftTopCorner.y + ARectangle.Height;
    s2.b.x = ARectangle.LeftTopCorner.x + ARectangle.Width;
    s2.b.y = ARectangle.LeftTopCorner.y + ARectangle.Height;

   return Collision(ABall, s1) || Collision(ABall, s2);
}

bool CGame::CollisionWithBottom(TCircle ABall, TRectangle ARectangle) {
    TSegment Segment;

    Segment.a.x = ARectangle.LeftTopCorner.x;
    Segment.a.y = ARectangle.LeftTopCorner.y + ARectangle.Height;
    Segment.b.x = ARectangle.LeftTopCorner.x + ARectangle.Width;
    Segment.b.y = ARectangle.LeftTopCorner.y + ARectangle.Height;

    return Collision(ABall, Segment);
}

void CGame::DrawSplashScreen() {
    TRectangle Rectangle = FLevel->GetRectangle();
    DrawQuadTexture(Rectangle.LeftTopCorner.x, Rectangle.LeftTopCorner.y, Rectangle.Width, Rectangle.Height, FSplashScreenTexture);
}

void CGame::DrawNextLevelScreen() {
    TRectangle Rectangle = FLevel->GetRectangle();
    DrawQuadTexture(Rectangle.LeftTopCorner.x, Rectangle.LeftTopCorner.y, Rectangle.Width, Rectangle.Height, FNextLevelTexture);
}

void CGame::DrawWonGameScreen() {
    TRectangle Rectangle = FLevel->GetRectangle();
    DrawQuadTexture(Rectangle.LeftTopCorner.x, Rectangle.LeftTopCorner.y, Rectangle.Width, Rectangle.Height, FWonGameTexture);
}

void CGame::DrawLostGameScreen() {
    TRectangle Rectangle = FLevel->GetRectangle();
    DrawQuadTexture(Rectangle.LeftTopCorner.x, Rectangle.LeftTopCorner.y, Rectangle.Width, Rectangle.Height, FLostGameTexture);
}

void CGame::DrawGameScreen() {
    FLevel->Draw();
    FPad->Draw();
    FBall->Draw();
    PrintInt(0, -13, FFont, FPoints);
}

void CGame::GameLogic() {
    if (KeyPressed(SDLK_RETURN)) {
        FBall->Start();
    }
    if (KeyPressed(SDLK_ESCAPE)) {
        Stop();
    }
    // Pad collisions with level.
    if (KeyPressed(SDLK_LEFT)) {
        // Calculating new position of pad.
        TRectangle PadNextPosition = FPad->GetRectangle();
        PadNextPosition.LeftTopCorner.x -= FPad->GetSpeed() * GetDeltaTime();
        if (RectInRect(PadNextPosition, FLevel->GetRectangle())) {
            FPad->MoveLeft(GetDeltaTime());
        }
    }
    if (KeyPressed(SDLK_RIGHT)) {
        // Calculating new position of pad.
        TRectangle PadNextPosition = FPad->GetRectangle();
        PadNextPosition.LeftTopCorner.x += FPad->GetSpeed() * GetDeltaTime();
        if (RectInRect(PadNextPosition, FLevel->GetRectangle())) {
            FPad->MoveRight(GetDeltaTime());
        }
    }
    // Calculating new position of ball.
    TCircle BallNextPosition = FBall->GetCircle();
    BallNextPosition.Center.x += FBall->GetSpeedX() * GetDeltaTime();
    BallNextPosition.Center.y += FBall->GetSpeedY() * GetDeltaTime();
    // Ball collisions with level.
    if (Collision(BallNextPosition, FLevel->GetRectangle())) {
        if (CollisionHorizontal(BallNextPosition, FLevel->GetRectangle())) {
            FBall->ChangeSpeedY();
        }
        if (CollisionVertical(BallNextPosition, FLevel->GetRectangle())) {
            FBall->ChangeSpeedX();
        }
        if (CollisionWithBottom(BallNextPosition, FLevel->GetRectangle())) {
            FBall->Stop();
            FBall->PutOnStartPosition();
            FPad->PutOnStartPosition();
            FLifes -= 1;
            if (FLifes <= 0) {
                FCurrentScreen = LostGameScreen;
                FCurrentLevel = 1;
                FLifes = 3;
                FLevel->Clear();
                FLevel->Init(FCurrentLevel);
                FBall->Stop();
                FBall->PutOnStartPosition();
                FPad->PutOnStartPosition();
            }
        }
    }

    // Ball collision with bricks
    for (unsigned int i = 0; i < FLevel->GetBrickCount(); i++) {
        TRectangle Brick = FLevel->GetBrickRectangle(i);
        if (Collision(BallNextPosition, Brick) && !FLevel->BrickDestroyed(i)) {
            if (CollisionHorizontal(BallNextPosition, Brick)) {
                FBall->ChangeSpeedY();
            }
            if (CollisionVertical(BallNextPosition, Brick)) {
                FBall->ChangeSpeedX();
            }
            FLevel->DestroyBrick(i);
            if (FLevel->GetLifes(i) <= 0) {
                FPoints += FLevel->GetPoints(i);
            }
        }
    }

    // Ball collisions with pad.
    if (Collision(BallNextPosition, FPad->GetRectangle())) {
        if (CollisionHorizontal(BallNextPosition, FPad->GetRectangle())) {
            FBall->ChangeSpeedY();
        }
        if (CollisionVertical(BallNextPosition, FPad->GetRectangle())) {
            FBall->ChangeSpeedX();
        }
    }

    if (FLevel->LevelClear()) {
        FCurrentLevel++;
        if (FCurrentLevel > FMaxLevel) {
            FCurrentLevel = 1;
            FCurrentScreen = WonGameScreen;
        }
        else {
            FCurrentScreen = NextLevelScreen;
        }
        FLevel->Clear();
        FLevel->Init(FCurrentLevel);
        FBall->Stop();
        FBall->PutOnStartPosition();
        FPad->PutOnStartPosition();
    }

    if (FBall->Moving()) {
        FBall->Move(GetDeltaTime());
    }
}

void CGame::TimeScreenLogic() {
    if (FCurrentTime > FMaxTime) {
        FCurrentScreen = GameScreen;
        FCurrentTime = 0;
    }
    FCurrentTime += GetDeltaTime();
}

void CGame::KeyScreenLogic() {
    if (KeyPressed(SDLK_RETURN)) {
        FCurrentScreen = GameScreen;
        FCurrentTime = 0;
    }
    if (KeyPressed(SDLK_ESCAPE)) {
        Stop();
    }
}

#include "LevelClass.h"

// CLevel Class;
// ===== Constructor/Destructor =====

CLevel::CLevel() {
    FBrickTexture = ImgToTexture("graphic/Brick.png");
    FBackground = ImgToTexture("graphic/Background.png");

    FRectangle.LeftTopCorner.x = -16.0f;
    FRectangle.LeftTopCorner.y = -12.0f;
    FRectangle.Width = 32.0f;
    FRectangle.Height = 24.0f;

    FBrickCount = 0;
    FBricks.reserve(128);
    Init(1);
}

CLevel::~CLevel() {
    Clear();
}

// ===== Public =====

void CLevel::Draw() {
    DrawQuadTexture(FRectangle.LeftTopCorner.x, FRectangle.LeftTopCorner.y, FRectangle.Width, FRectangle.Height, FBackground);

    for (unsigned int i = 0; i < FBricks.size(); i++) {
        FBricks[i]->Draw();
    }
}

TRectangle CLevel::GetRectangle() {
    return FRectangle;
}

TRectangle CLevel::GetBrickRectangle(int AIndex) {
    return FBricks[AIndex]->GetRectangle();
}

unsigned int CLevel::GetBrickCount() {
    return FBricks.size();
}

void CLevel::DestroyBrick(int AIndex) {
    FBricks[AIndex]->LooseLife();
    FBrickCount--;
    if (FBrickCount == 0) {
        FLevelClear = true;
    }
}

bool CLevel::BrickDestroyed(int AIndex) {
    return FBricks[AIndex]->GetLifes() == 0;
}

void CLevel::Init(unsigned int ALevel) {
    float Bx, By;

    char FileName[256] = {0};
    snprintf(FileName, sizeof(FileName) - 1, "maps/map%u.txt", ALevel);
    FILE *MapFile = fopen(FileName, "r");

    for (int y = 0; y < 8; y++){
        char Line[32];
        fgets(Line, sizeof(Line), MapFile);
        for (int x = 0; x < 16; x++) {
            Bx = (float)(x * 2 - 16.0);
            By = (float)(y - 10.0) ;
            switch (Line[x]) {
                case '1':
                    FBricks.push_back(new CBrick(Bx, By, 1, FBrickTexture));
                    FBrickCount++;
                    printf("FROM FILE   x: %i | y: %i\n", x, y);
                    printf("CALCULATED Bx: %f | By: %f\n\n", Bx, By);
                    break;
                case '2':
                    FBricks.push_back(new CBrick(Bx, By, 2, FBrickTexture));
                    FBrickCount++;
                    break;
                case '3':
                    FBricks.push_back(new CBrick(Bx, By, 3, FBrickTexture));
                    FBrickCount++;
                    break;
                case '4':
                    FBricks.push_back(new CBrick(Bx, By, 4, FBrickTexture));
                    FBrickCount++;
                    break;
                case '5':
                    FBricks.push_back(new CBrick(Bx, By, 5, FBrickTexture));
                    FBrickCount++;
                    break;
            }
        }
    }
    fclose(MapFile);

/*
    for (unsigned int i = 0; i < 128; i++) {
        Bx = (float)(IndexToX(i) * 2 - 16.0);
        By = (float)(IndexToY(i) - 10.0);
        FBricks.push_back(new CBrick(Bx, By, 1, FBrickTexture));
        FBrickCount++;
        printf("CALCULATED Bx: %f | By: %f\n\n", Bx, By);
    }
*/
    printf("Bricks vector size: %i\n", FBricks.size());
    printf("Bricks count: %i\n", FBrickCount);

    FLevelClear = false;
}

void CLevel::Clear() {
    for (unsigned int i = 0; i < FBrickCount; i++) {
        delete FBricks[i];
    }
    FBricks.clear();
}

bool CLevel::LevelClear() {
    return FLevelClear;
}

// ===== Protected =====
// ===== Private =====

int CLevel::IndexToY(int AIndex) {
    return int(AIndex / 16);
}

int CLevel::IndexToX(int AIndex) {
    return int(AIndex % 16);
}

int CLevel::XYToIndex(int Ax, int Ay) {
    return Ax + Ay * 16;
}

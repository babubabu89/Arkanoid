#include "LevelClass.h"

// CLevel Class;
// ===== Constructor/Destructor =====

CLevel::CLevel(unsigned int ATexture) : CRectangleGameObject(-16.0f, -12.0f, 32.0f, 24.0f, ATexture) {
    FBrickTexture1 = ImgToTexture("graphics/Brick1.png");
    FBrickTexture2 = ImgToTexture("graphics/Brick2.png");
    FBrickTexture3 = ImgToTexture("graphics/Brick3.png");

    FBrickCount = 0;
    FBricks.reserve(128);
    Init(1);
}

CLevel::~CLevel() {
    Clear();
    DeleteTexture(FBrickTexture1);
    DeleteTexture(FBrickTexture2);
    DeleteTexture(FBrickTexture3);
}

// ===== Public =====

void CLevel::Draw() {
    CRectangleGameObject::Draw();
    for (unsigned int i = 0; i < FBricks.size(); i++) {
        unsigned int BrickLifes = FBricks[i]->GetLifes();
        if (BrickLifes > 0) {
            FBricks[i]->Draw();
        }
    }
}

TRectangle CLevel::GetBrickRectangle(int AIndex) {
    return FBricks[AIndex]->GetRectangle();
}

unsigned int CLevel::GetBrickCount() {
    return FBricks.size();
}

unsigned int CLevel::GetPoints(int AIndex) {
    return FBricks[AIndex]->GetPoints();
}

unsigned int CLevel::GetLifes(int AIndex) {
    return FBricks[AIndex]->GetLifes();
}

void CLevel::DestroyBrick(int AIndex) {
    FBricks[AIndex]->LooseLife();
    if (FBricks[AIndex]->GetLifes() <= 0) {
        FBrickCount--;
    }
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
                    FBricks.push_back(new CBrick(Bx, By, 1, 1, FBrickTexture1));
                    FBrickCount++;
                    break;
                case '2':
                    FBricks.push_back(new CBrick(Bx, By, 2, 2, FBrickTexture2));
                    FBrickCount++;
                    break;
                case '3':
                    FBricks.push_back(new CBrick(Bx, By, 3, 3, FBrickTexture3));
                    FBrickCount++;
                    break;
            }
        }
    }
    fclose(MapFile);

    FLevelClear = false;
}

void CLevel::Clear() {
    for (unsigned int i = 0; i < FBricks.size(); i++) {
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

#include "BrickClass.h"

// CBrick Class;
// ===== Constructor/Destructor =====

CBrick::CBrick(float Ax, float Ay, unsigned int ALifes, unsigned int ATexture) {
    FRectangle.LeftTopCorner.x = Ax;
    FRectangle.LeftTopCorner.y = Ay;
    FRectangle.Width = 2.0f;
    FRectangle.Height = 1.0f;
    FLifes = ALifes;
    FTexture = ATexture;
}

CBrick::~CBrick() {

}

// ===== Public =====

void CBrick::Draw() {
    if (FLifes > 0) {
        DrawQuadTexture(FRectangle.LeftTopCorner.x, FRectangle.LeftTopCorner.y, FRectangle.Width, FRectangle.Height, FTexture);
    }
}

void CBrick::LooseLife() {
    FLifes--;
}

TRectangle CBrick::GetRectangle() {
   return FRectangle;
}

int CBrick::GetLifes() {
    return FLifes;
}
// ===== Protected =====
// ===== Private =====

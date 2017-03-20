#include "PadClass.h"

// CPad Class;
// ===== Constructor/Destructor =====

CPad::CPad(float Ax, float Ay, unsigned int ATexture) {
    FRectangle.LeftTopCorner.x = Ax;
    FRectangle.LeftTopCorner.y = Ay;
    FStartPosition.x = Ax;
    FStartPosition.y = Ay;
    FRectangle.Width = 2.0f;
    FRectangle.Height = 0.5f;
    FSpeed = 16.0f;

    FTexture = ATexture;
}

CPad::~CPad() {

}

// ===== Public =====

void CPad::Draw() {
    DrawQuadTexture(FRectangle.LeftTopCorner.x, FRectangle.LeftTopCorner.y, FRectangle.Width, FRectangle.Height, FTexture);
}

void CPad::MoveLeft(float ADeltaTime) {
    FRectangle.LeftTopCorner.x -= (FSpeed * ADeltaTime);
}

void CPad::MoveRight(float ADeltaTime) {
    FRectangle.LeftTopCorner.x += (FSpeed * ADeltaTime);
}

TRectangle CPad::GetRectangle() {
    return FRectangle;
}

float CPad::GetSpeed() {
    return FSpeed;
}

void CPad::PutOnStartPosition() {
    FRectangle.LeftTopCorner = FStartPosition;
}
// ===== Protected =====
// ===== Private =====

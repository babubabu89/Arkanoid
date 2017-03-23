#include "PadClass.h"

// CPad Class;
// ===== Constructor/Destructor =====

CPad::CPad(float Ax, float Ay, unsigned int ATexture) : CRectangleGameObject(Ax, Ay, 2.0f, 0.5f, ATexture) {
    FStartPosition.x = Ax;
    FStartPosition.y = Ay;
    FSpeed = 16.0f;
}

CPad::~CPad() {

}

// ===== Public =====

void CPad::MoveLeft(float ADeltaTime) {
    TRectangle CurrentRectangle = GetRectangle();
    CurrentRectangle.LeftTopCorner.x -= (FSpeed * ADeltaTime);
    SetNewPosition(CurrentRectangle.LeftTopCorner);
}

void CPad::MoveRight(float ADeltaTime) {
    TRectangle CurrentRectangle = GetRectangle();
    CurrentRectangle.LeftTopCorner.x += (FSpeed * ADeltaTime);
    SetNewPosition(CurrentRectangle.LeftTopCorner);
}

float CPad::GetSpeed() {
    return FSpeed;
}

void CPad::PutOnStartPosition() {
    SetNewPosition(FStartPosition);
}
// ===== Protected =====
// ===== Private =====

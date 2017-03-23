#include "BallClass.h"

// CBall Class;
// ===== Constructor/Destructor =====

CBall::CBall(float Ax, float Ay, unsigned int ATexture) : CCircleGameObject(Ax, Ay, 0.25f, ATexture){
    FStartPosition.x = Ax;
    FStartPosition.y = Ay;

    FSpeedX = 10.0f;
    FSpeedY = 10.0f;
    FMove = false;
}

CBall::~CBall() {

}

// ===== Public =====

void CBall::Move(float ADeltaTime){
    TCircle CurrentCircle = GetCircle();
    CurrentCircle.Center.x += FSpeedX * ADeltaTime;
    CurrentCircle.Center.y += FSpeedY * ADeltaTime;
    SetNewPosition(CurrentCircle.Center);
}

float CBall::GetSpeedX() {
    return FSpeedX;
}

float CBall::GetSpeedY() {
    return FSpeedY;
}

void CBall::ChangeSpeedX() {
  FSpeedX = FSpeedX * (-1);
}

void CBall::ChangeSpeedY() {
  FSpeedY = FSpeedY * (-1);
}

void CBall::Start() {
    FMove = true;
}

void CBall::Stop() {
    FMove = false;
}

bool CBall::Moving() {
    return FMove;
}

void CBall::PutOnStartPosition() {
    SetNewPosition(FStartPosition);
}
// ===== Protected =====
// ===== Private =====

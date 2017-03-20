#include "BallClass.h"

// CBall Class;
// ===== Constructor/Destructor =====

CBall::CBall(float Ax, float Ay, unsigned int ATexture) {
    FCircle.Center.x = Ax;
    FCircle.Center.y = Ay;
    FStartPosition.x = Ax;
    FStartPosition.y = Ay;
    FCircle.Radius = 0.25f;

    FSpeedX = 12.0f;
    FSpeedY = 12.0f;
    FMove = false;

    FTexture = ATexture;
}

CBall::~CBall() {

}

// ===== Public =====

void CBall::Draw() {
    DrawQuadTexture(FCircle.Center.x - FCircle.Radius, FCircle.Center.y - FCircle.Radius, FCircle.Radius * 2, FCircle.Radius * 2, FTexture);
}

void CBall::Move(float ADeltaTime){
    FCircle.Center.x += FSpeedX * ADeltaTime;
    FCircle.Center.y += FSpeedY * ADeltaTime;
}

TCircle CBall::GetCircle() {
    return FCircle;
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
    FCircle.Center = FStartPosition;
}
// ===== Protected =====
// ===== Private =====

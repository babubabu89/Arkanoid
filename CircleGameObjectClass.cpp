#include "CircleGameObjectClass.h"

// CCircleGameObject Class;
// ===== Constructor/Destructor =====

CCircleGameObject::CCircleGameObject(float Ax, float Ay, float ARadius, unsigned int ATexture) : CCustomGameObject(ATexture) {
    FCircle.Center.x = Ax;
    FCircle.Center.y = Ay;
    FCircle.Radius = ARadius;
}

CCircleGameObject::~CCircleGameObject() {

}

// ===== Public =====

void CCircleGameObject::Draw() {
    DrawQuadTexture(FCircle.Center.x - FCircle.Radius, FCircle.Center.y - FCircle.Radius, FCircle.Radius * 2, FCircle.Radius * 2, FTexture);
}

TCircle CCircleGameObject::GetCircle() {
    return FCircle;
}

// ===== Protected =====

void CCircleGameObject::SetNewPosition(TPoint APosition) {
    FCircle.Center = APosition;
}

// ===== Private =====

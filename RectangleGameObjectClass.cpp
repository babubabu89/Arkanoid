#include "RectangleGameObjectClass.h"

// CRectangleGameObject Class;
// ===== Constructor/Destructor =====

CRectangleGameObject::CRectangleGameObject(float Ax, float Ay, float AWidth, float AHeight, unsigned int ATexture) : CCustomGameObject(ATexture) {
    FRectangle.LeftTopCorner.x = Ax;
    FRectangle.LeftTopCorner.y = Ay;
    FRectangle.Width = AWidth;
    FRectangle.Height = AHeight;
}

CRectangleGameObject::~CRectangleGameObject() {

}

// ===== Public =====

void CRectangleGameObject::Draw() {
    DrawQuadTexture(FRectangle.LeftTopCorner.x, FRectangle.LeftTopCorner.y, FRectangle.Width, FRectangle.Height, FTexture);
}

TRectangle CRectangleGameObject::GetRectangle() {
    return FRectangle;
}

// ===== Protected =====

void CRectangleGameObject::SetNewPosition(TPoint APosition) {
    FRectangle.LeftTopCorner = APosition;
}

// ===== Private =====

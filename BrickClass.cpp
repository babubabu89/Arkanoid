#include "BrickClass.h"

// CBrick Class;
// ===== Constructor/Destructor =====

CBrick::CBrick(float Ax, float Ay, unsigned int ALifes, unsigned int APoints, unsigned int ATexture) : CRectangleGameObject(Ax, Ay, 2.0f, 1.0f, ATexture) {
    FLifes = ALifes;
    FPoints = APoints;
}

CBrick::~CBrick() {

}

// ===== Public =====

void CBrick::LooseLife() {
    FLifes--;
}

unsigned int CBrick::GetLifes() {
    return FLifes;
}

unsigned int CBrick::GetPoints() {
    return FPoints;
}

// ===== Protected =====
// ===== Private =====

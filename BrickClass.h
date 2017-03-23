#ifndef BRICKCLASS_H_INCLUDED
#define BRICKCLASS_H_INCLUDED

#include "GameFramework.h"
#include "physics2D.h"
#include "RectangleGameObjectClass.h"

class CBrick : public CRectangleGameObject {
    // Class fields
    public:
    protected:
    private:
        unsigned int FLifes;
        unsigned int FPoints;
    // Class functions
    public:
        CBrick(float Ax, float Ay, unsigned int ALifes, unsigned int APoints, unsigned int ATexture);
        ~CBrick();
    public:
        void LooseLife();
        unsigned int GetLifes();
        unsigned int GetPoints();
    protected:
    private:
};

#endif // BRICKCLASS_H_INCLUDED

#ifndef BRICKCLASS_H_INCLUDED
#define BRICKCLASS_H_INCLUDED

#include "GameFramework.h"
#include "physics2D.h"

class CBrick {
    // Class fields
    public:
    protected:
    private:
        unsigned int FTexture;
        TRectangle FRectangle;
        int FLifes;
    // Class functions
    public:
        CBrick(float Ax, float Ay, unsigned int ALifes, unsigned int ATexture);
        ~CBrick();
    public:
        void Draw();
        void LooseLife();
        TRectangle GetRectangle();
        int GetLifes();
    protected:
    private:
};

#endif // BRICKCLASS_H_INCLUDED

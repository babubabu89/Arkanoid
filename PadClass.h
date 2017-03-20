#ifndef PADCLASS_H_INCLUDED
#define PADCLASS_H_INCLUDED

#include "GameFramework.h"
#include "physics2D.h"

class CPad {
    // Class fields
    public:
    protected:
    private:
        unsigned int FTexture;
        TRectangle FRectangle;
        TPoint FStartPosition;
        float FSpeed;
    // Class functions
    public:
        CPad(float Ax, float Ay, unsigned int ATexture);
        ~CPad();
    public:
        void Draw();
        void MoveLeft(float ADeltaTime);
        void MoveRight(float ADeltaTime);
        TRectangle GetRectangle();
        float GetSpeed();
        void PutOnStartPosition();
    protected:
    private:
};

#endif // PADCLASS_H_INCLUDED

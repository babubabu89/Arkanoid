#ifndef PADCLASS_H_INCLUDED
#define PADCLASS_H_INCLUDED

#include "GameFramework.h"
#include "physics2D.h"
#include "RectangleGameObjectClass.h"

class CPad : public CRectangleGameObject {
    // Class fields
    public:
    protected:
    private:
        TPoint FStartPosition;
        float FSpeed;
    // Class functions
    public:
        CPad(float Ax, float Ay, unsigned int ATexture);
        ~CPad();
    public:
        void MoveLeft(float ADeltaTime);
        void MoveRight(float ADeltaTime);
        float GetSpeed();
        void PutOnStartPosition();
    protected:
    private:
};

#endif // PADCLASS_H_INCLUDED

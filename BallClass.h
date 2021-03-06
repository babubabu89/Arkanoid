#ifndef BALLCLASS_H_INCLUDED
#define BALLCLASS_H_INCLUDED

#include "GameFramework.h"
#include "physics2D.h"
#include "CircleGameObjectClass.h"

class CBall : public CCircleGameObject {
    // Class fields
    public:
    protected:
    private:
        unsigned int FTexture;
        float FSpeedX, FSpeedY;
        TCircle FCircle;
        TPoint FStartPosition;
        bool FMove;
    // Class functions
    public:
        CBall(float Ax, float Ay, unsigned int ATexture);
        ~CBall();
    public:
        void Move(float ADeltaTime);
        float GetSpeedX();
        float GetSpeedY();
        void ChangeSpeedX();
        void ChangeSpeedY();
        void Start();
        void Stop();
        bool Moving();
        void PutOnStartPosition();
    protected:
    private:
};

#endif // BALLCLASS_H_INCLUDED

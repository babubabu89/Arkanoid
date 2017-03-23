#ifndef CIRCLEGAMEOBJECTCLASS_H_INCLUDED
#define CIRCLEGAMEOBJECTCLASS_H_INCLUDED

#include "CustomGameObjectClass.h"
#include "GameFramework.h"
#include "physics2D.h"

class CCircleGameObject : public CCustomGameObject {
    // Class fields
    public:
    protected:
    private:
        TCircle FCircle;
    // Class functions
    public:
        CCircleGameObject(float Ax, float Ay, float ARadius, unsigned int ATexture);
        virtual ~CCircleGameObject();
    public:
        virtual void Draw();
        TCircle GetCircle();
    protected:
        void SetNewPosition(TPoint APosition);
    private:
};

#endif // CIRCLEGAMEOBJECTCLASS_H_INCLUDED

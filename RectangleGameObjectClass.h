#ifndef RECTANGLEGAMEOBJECTCLASS_H_INCLUDED
#define RECTANGLEGAMEOBJECTCLASS_H_INCLUDED

#include "CustomGameObjectClass.h"
#include "GameFramework.h"
#include "physics2D.h"

class CRectangleGameObject : public CCustomGameObject {
    // Class fields
    public:
    protected:
    private:
        TRectangle FRectangle;
    // Class functions
    public:
        CRectangleGameObject(float Ax, float Ay, float AWidth, float AHeight, unsigned int ATexture);
        virtual ~CRectangleGameObject();
    public:
        virtual void Draw();
        TRectangle GetRectangle();
    protected:
        void SetNewPosition(TPoint APosition);
    private:
};

#endif // RECTANGLEGAMEOBJECTCLASS_H_INCLUDED

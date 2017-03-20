#ifndef LEVELCLASS_H_INCLUDED
#define LEVELCLASS_H_INCLUDED

#include <vector>
#include <stdlib.h>
#include "GameFramework.h"
#include "BrickClass.h"

class CLevel {
    // Class fields
    public:
    protected:
    private:
        std::vector<CBrick*> FBricks;
        unsigned int FBackground;
        unsigned int FBrickTexture;
        TRectangle FRectangle;
        unsigned int FBrickCount;
        bool FLevelClear;
    // Class functions
    public:
        CLevel();
        ~CLevel();
    public:
        void Draw();
        TRectangle GetRectangle();
        TRectangle GetBrickRectangle(int AIndex);
        unsigned int GetBrickCount();
        void DestroyBrick(int AIndex);
        bool BrickDestroyed(int AIndex);
        void Init(unsigned int ALevel);
        void Clear();
        bool LevelClear();
    protected:
    private:
        int IndexToY(int AIndex);
        int IndexToX(int AIndex);
        int XYToIndex(int Ax, int Ay);
};

#endif // LEVELCLASS_H_INCLUDED

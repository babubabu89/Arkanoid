#ifndef LEVELCLASS_H_INCLUDED
#define LEVELCLASS_H_INCLUDED

#include <vector>
#include "GameFramework.h"
#include "BrickClass.h"

class CLevel : public CRectangleGameObject {
    // Class fields
    public:
    protected:
    private:
        std::vector<CBrick*> FBricks;
        unsigned int FBrickTexture1,
                     FBrickTexture2,
                     FBrickTexture3;
        unsigned int FBrickCount;
        bool FLevelClear;
    // Class functions
    public:
        CLevel(unsigned int ATexture);
        ~CLevel();
    public:
        void Draw() override;
        TRectangle GetBrickRectangle(int AIndex);
        unsigned int GetBrickCount();
        unsigned int GetPoints(int AIndex);
        unsigned int GetLifes(int AIndex);
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

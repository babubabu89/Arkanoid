#ifndef CUSTOMGAMEOBJECTCLASS_H_INCLUDED
#define CUSTOMGAMEOBJECTCLASS_H_INCLUDED

class CCustomGameObject {
    // Class fields
    public:
    protected:
        unsigned int FTexture;
    private:
    // Class functions
    public:
        CCustomGameObject(unsigned int ATexture);
        virtual ~CCustomGameObject();
    public:
        virtual void Draw() = 0;
    protected:
    private:
};

#endif // CUSTOMGAMEOBJECTCLASS_H_INCLUDED

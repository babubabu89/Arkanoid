#ifndef GAMEFRAMEWORK_H_INCLUDED
#define GAMEFRAMEWORK_H_INCLUDED

//#define DEBUG

#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cstring>

class CCustomApplication {
    // Class fields.
    public:


    protected:

    private:
        SDL_Window* FWindow;
        SDL_GLContext FGLContext;
        bool FRunning;
        float FDeltaTime;
        const Uint8* FKeys;
    // Class functions.
    public: // Constructor/Destructor.
        CCustomApplication(int AWidth, int AHeight);
        virtual ~CCustomApplication();
    public:
        void MainLoop();
    protected:
        virtual void Logic() = 0;
        virtual void Render() = 0;
    protected:
        bool KeyPressed(SDL_Keycode AKey);
        float GetDeltaTime();
        void Stop();
    private:
        bool InitSDL(int AWidth, int AHeight);
        bool InitOpenGL(int AWidth, int AHeight);
        void EventsQueue();
};

struct TNumericFont {
  std::vector<unsigned int> NumberTexture;
  float Width, Height;
};

void DrawQuad(float Ax, float Ay, float AWidth, float AHeight);
void DrawQuadRGBA(float Ax, float Ay, float AWidth, float AHeight, float ARed, float AGreen, float ABlue, float AAlpha);
void DrawQuadTexture(float Ax, float Ay, float AWidth, float AHeight, unsigned int ATexture_id);
unsigned int ImgToTexture(const char *AFileName);
void DeleteTexture(unsigned int ATexture);
TNumericFont LoadFont(float ASize);
void FreeFont(TNumericFont *AFont);
void PrintInt(float Ax, float Ay, TNumericFont AFont, int AInt);

#endif // GAMEFRAMEWORK_H_INCLUDED

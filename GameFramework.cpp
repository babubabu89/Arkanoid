#include "GameFramework.h"

// ===== Constructor/Destructor =====

CCustomApplication::CCustomApplication(int AWidth, int AHeight) {
    FWindow = NULL;
    FGLContext = NULL;

    FRunning = true;

    FRunning = InitSDL(AWidth, AHeight);
    FRunning = InitOpenGL(AWidth, AHeight);
}

CCustomApplication::~CCustomApplication() {
    SDL_Quit();
}

// ===== Public =====

void CCustomApplication::MainLoop() {
    unsigned int PrevTime = SDL_GetTicks();
    FDeltaTime = 0;
    while(FRunning)
    {
        EventsQueue();
        Logic();

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -25.0f);
        glScalef(1.0f, -1.0f, 1.0f);

        Render();

        SDL_GL_SwapWindow(FWindow);

        unsigned int CurrTime = SDL_GetTicks();
        FDeltaTime = (float)(CurrTime - PrevTime) / 1000.0f;
        PrevTime = CurrTime;
    }
    SDL_DestroyWindow(FWindow);
}

// ===== Protected =====

bool CCustomApplication::KeyPressed(SDL_Keycode AKey) {
    return FKeys[SDL_GetScancodeFromKey(AKey)];
}

float CCustomApplication::GetDeltaTime() {
    return FDeltaTime;
}

void CCustomApplication::Stop() {
    FRunning = false;
}

// ===== Private =====

bool CCustomApplication::InitSDL(int AWidth, int AHeight) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR: SDL Error - %s\n", SDL_GetError());
        return false;
    }
    else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        FWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, AWidth, AHeight, SDL_WINDOW_OPENGL);
        if (FWindow == NULL) {
            printf("ERROR: SDL Error- %s\n", SDL_GetError());
            return false;
        }
        else {
            FGLContext = SDL_GL_CreateContext(FWindow);
            if (FGLContext == NULL) {
                printf("ERROR: SDL Error - %s\n", SDL_GetError());
                return false;
            }
            else {
                if (SDL_GL_SetSwapInterval(0) < 0) {
                    printf("WARNING: Unable to set VSync! SDL Error - %s\n", SDL_GetError());
                }
            }
        }
    }
    return true;
}

bool CCustomApplication::InitOpenGL(int AWidth, int AHeight) {
    GLenum error = GL_NO_ERROR;

    float ratio;
    ratio = (float)AWidth / (float)AHeight;

    glShadeModel(GL_SMOOTH);
    glClearColor(0, 0, 0, 1);
    glViewport(0, 0, AWidth, AHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluPerspective( 60.0, ratio, 1.0, 1024.0 );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("ERROR: OpenGL Error - %s\n", gluErrorString(error));
        return false;
    }

    return true;
}

void CCustomApplication::EventsQueue() {
    SDL_Event Event;
    while (SDL_PollEvent(&Event) != 0) {
        FKeys = SDL_GetKeyboardState(NULL);
        switch(Event.type) {
            case SDL_QUIT :
                FRunning = false;
                break;
        }
    }
}

// ===== Other Functions =====

void DrawQuad(float Ax, float Ay, float AWidth, float AHeight) {
    AWidth /= 2.0f;
    AHeight /= 2.0f;

    float LeftX = Ax;
    float TopY = Ay;
    float RightX = Ax + AWidth * 2;
    float BottomY = Ay + AHeight * 2;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(LeftX, TopY);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(RightX, TopY);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(RightX, BottomY);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(LeftX, BottomY);
    glEnd();
}

void DrawQuadRGBA(float Ax, float Ay, float AWidth, float AHeight, float ARed, float AGreen, float ABlue, float AAlpha) {
    // Get old color.
    float current_color[4];
    glGetFloatv(GL_CURRENT_COLOR, current_color);

    // Set new color and draw quad.
    glColor4f(ARed, AGreen, ABlue, AAlpha);
    DrawQuad(Ax, Ay, AWidth, AHeight);

    // Set old color.
    glColor4fv(current_color);
}

void DrawQuadTexture(float Ax, float Ay, float AWidth, float AHeight, unsigned int ATexture_id) {
    // Enable texturing if needed.
    bool texturing_enabled = glIsEnabled(GL_TEXTURE_2D);
    if(!texturing_enabled)
        glEnable(GL_TEXTURE_2D);

    // Bind texture and draw.
    glBindTexture(GL_TEXTURE_2D, ATexture_id);
    DrawQuad(Ax, Ay, AWidth, AHeight);

    // Disable if was disable.
    if(!texturing_enabled)
        glDisable(GL_TEXTURE_2D);
}

unsigned int ImgToTexture(const char *AFileName) {
    // Load image.
    SDL_Surface *img = IMG_Load(AFileName);
    if(!img) {
        printf("ERROR: ImgToTexture could not load image \"%s\"\n", AFileName);
        return ~0;
    }

    // Image type? Only 24 and 32 supported, rest must be converted.
    unsigned int img_type = 0;

    if(img->format->BitsPerPixel == 32) {
        img_type = GL_RGBA;
    }
    else if(img->format->BitsPerPixel == 24) {
        img_type = GL_RGB;
    }
    else {
        // Convert to 32 bits.
        SDL_PixelFormat fmt = {SDL_PIXELFORMAT_RGBA32, NULL, 32, 4, 0, 0, 0, 0};

        SDL_Surface *nimg = SDL_ConvertSurface(img, &fmt, SDL_SWSURFACE);
        SDL_FreeSurface(img);

        if(!nimg) {
            printf("ERROR: ImgToTexture could not convert image \"%s\" to 32-bit\n", AFileName);
            return ~0;
        }

        // Done converting.
        img = nimg;
        img_type = GL_RGBA;
    }

    // Create texture.
    unsigned int texture_id = ~0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // You might want to play with these parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Gen texture.
    glTexImage2D(GL_TEXTURE_2D, 0, img_type, img->w, img->h, 0, img_type, GL_UNSIGNED_BYTE, img->pixels);

    printf("INFO: ImgToTexture loaded texture \"%s\" as %u\n", AFileName, texture_id);

    // Done
    SDL_FreeSurface(img);
    return texture_id;
}

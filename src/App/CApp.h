#include <iostream>
#include <SDL2/SDL.h>
#include <macros.h>

enum e_status{
    ST_ALL_CLEARED          = 0x0,
    ST_SDL_INITIALIZED      = 0x1,
    ST_SDL_ERROR_WINDOW     = 0x2,
    ST_SDL_ERROR_RENDERER   = 0x4
};

class CApp{
private:
    //Class attributes
    SDL_Window*       m_pWindow;
    SDL_Renderer*   m_pRenderer;
    int     m_iWidth, m_iHeight;
    uint32_t          m_uStatus;
    
    /*
        Private functions
        Note: the default constructor is private because I want people to use the overloaded one,
        that has window width and height as parameters
    */

    CApp():
        m_pWindow(nullptr),
        m_pRenderer(nullptr),
        m_iWidth(0),
        m_iHeight(0),
        m_uStatus(0)
    {};

    // This one is the place where the while(SDL_PollEvent(&event)) loop lives
    int EventsHandler();
public:

    /*
        Public functions

    */
    CApp(int iWidth, int iHeight);
    ~CApp();
    int Run();
};
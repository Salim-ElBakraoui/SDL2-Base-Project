#include "CApp.h"

CApp::CApp(int iWidth, int iHeight):
    m_pWindow(nullptr),
    m_pRenderer(nullptr),
    m_iWidth(iWidth),
    m_iHeight(iHeight),
    m_uStatus(0)
{
    SDL_Init(SDL_INIT_VIDEO);
    m_pWindow = SDL_CreateWindow("SDL2 Base", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_iWidth, m_iHeight, 0);
    if(!m_pWindow){
        std::cout << "Failed to initialize Window, closing app" << std::endl;
        mBitsSet(m_uStatus, ST_SDL_ERROR_WINDOW);
        return;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!m_pRenderer){
        std::cout << "Failed to initialize Renderer, switching to software mode" << std::endl;
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
        if(!m_pRenderer){
            std::cout << "Failed to initialize Software Renderer, closing app" << std::endl;
            mBitsSet(m_uStatus, ST_SDL_ERROR_RENDERER);
            return;
        }
    }

    mBitsSet(m_uStatus, ST_SDL_INITIALIZED);
}

CApp::~CApp(){
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    m_pRenderer = nullptr;
    m_pWindow = nullptr;
}

int CApp::Run(){
    if(mIsBitsClr(m_uStatus, ST_SDL_INITIALIZED))
        return EXIT_FAILURE;

    while(!EventsHandler()){
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(m_pRenderer);
        SDL_RenderPresent(m_pRenderer);
    }
    return EXIT_SUCCESS;
}

int CApp::EventsHandler(){
    SDL_Event event;
    int quit = 0;

    while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
                default:
                    break;
                }
                break;

            case SDL_WINDOWEVENT:
                switch(event.window.event){
                case SDL_WINDOWEVENT_CLOSE:
                    quit = 1;
                    break;
                default:
                    break;
                }
                break;

            case SDLK_ESCAPE:
                quit = 1;
                break;

            default:
                break;
            }
        }

    return quit;
}
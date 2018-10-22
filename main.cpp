#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Universe.h"


using namespace std;

class Application {
public:
    Application() {
        state = 0;
        window = nullptr;
        renderer = nullptr;
        texture = nullptr;
        image = nullptr;
    }

    void run() {
        init();
        mainLoop();
        cleanup();
    }

private:

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Surface* image;

    Universe universe;

    unsigned char state;

    enum States {
        STOP = 0,
        RUNNING = 1
    };

    const Uint32 timeWindow = 100;

    void initSDL() {
        SDL_Init( SDL_INIT_EVERYTHING );
        atexit( SDL_Quit );
        IMG_Init(IMG_INIT_JPG);
    }

    void createWindow() {

        int width = universe.getWidth();
        int height = universe.getHeight();

        window = SDL_CreateWindow( "SDL2",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   500, 500,
                                   //universe.getWidth(), universe.getHeight(),
                                   SDL_WINDOW_SHOWN );

        renderer = SDL_CreateRenderer( window,
                                       -1,
                                       SDL_RENDERER_ACCELERATED );

        texture = SDL_CreateTexture( renderer,
                                     SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     universe.getWidth(), universe.getHeight() );
    }

    void loadImage() {
        char* basePath = SDL_GetBasePath();
        std::string str(basePath);
        strcat(basePath, "../jec.png");

        image = IMG_Load(basePath);
        image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

        auto width = (unsigned int)image->w;
        auto height = (unsigned int)image->h;
        auto rawPixels = (unsigned char*)image->pixels;
        int size = image->w * image->h * 4;

        universe.init(width, height);

        universe.setPixels(rawPixels);

    }

    void loadRandomImage(int size) {

        universe.init(size,size);

        std::vector<unsigned char> pixels(size * size * 4);

        for( unsigned int i = 0; i < (size/2); i++ ) {
            const unsigned int x = rand() % size;
            const unsigned int y = rand() % size;
            const unsigned int offset = ( size * 4 * y ) + x * 4;

            const unsigned char whiteness = rand() % 256;

            pixels[ offset + 0 ] = whiteness;        // b
            pixels[ offset + 1 ] = whiteness;        // g
            pixels[ offset + 2 ] = whiteness;        // r
        }

        universe.setPixels(pixels.data());
    }


    void init() {
        initSDL();
        //loadImage();
        loadRandomImage(50);
        createWindow();
        universe.whitenessOnly();

    }

    void input() {
        SDL_Event event;
        while( SDL_PollEvent( &event ) ) {
            if( ( event.type == SDL_QUIT ) ||
                ( event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) ) {
            state = STOP;
            }
        }
    }

    void calculation() {
        universe.next();
    }

    void output() {
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );
        SDL_UpdateTexture( texture,
                           nullptr,
                           universe.getPixels().data(),
                           universe.getWidth() * 4 );
        SDL_RenderCopy( renderer, texture, nullptr, nullptr );
        SDL_RenderPresent( renderer );
    }


    void mainLoop() {
        state = RUNNING;
        while(state) {

            const Uint64 start = SDL_GetPerformanceCounter();

            input();
            calculation();
            output();

            const Uint64 end = SDL_GetPerformanceCounter();
            const static Uint64 freq = SDL_GetPerformanceFrequency();
            const double seconds = ( end - start ) / static_cast< double >( freq );
            cout << "Calculation time: " << seconds * 1000.0 << "ms" << endl;
            if(seconds * 1000 < timeWindow) {
                SDL_Delay(timeWindow - (Uint32)seconds);
            }
        }
    }

    void cleanup() {
        SDL_FreeSurface( image );
        SDL_DestroyTexture( texture );
        SDL_DestroyRenderer( renderer );
        SDL_DestroyWindow( window );
        IMG_Quit();
        SDL_Quit();
    }
};

int main() {
    Application app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
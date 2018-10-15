#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <random>

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

    unsigned char state;
    enum States {
        STOP = 0,
        RUNNING = 1
    };

    vector<unsigned char> pixels;

    unsigned int width = 500;
    unsigned int height = 500;
    const Uint32 timeWindow = 100;

    void initSDL() {
        SDL_Init( SDL_INIT_EVERYTHING );
        atexit( SDL_Quit );
        IMG_Init(IMG_INIT_JPG);
    }

    void createWindow() {
        window = SDL_CreateWindow( "SDL2",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width, height,
                                   SDL_WINDOW_SHOWN );

        renderer = SDL_CreateRenderer( window,
                                       -1,
                                       SDL_RENDERER_ACCELERATED );

        texture = SDL_CreateTexture( renderer,
                                     SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     width, height );
    }

    void loadImage() {
        char* basePath = SDL_GetBasePath();
        std::string str(basePath);
        strcat(basePath, "../eyeball.png");

        SDL_Surface* originalImage = IMG_Load(basePath);
        image = SDL_ConvertSurfaceFormat(originalImage, SDL_PIXELFORMAT_ARGB8888, 0);
        SDL_FreeSurface(originalImage);

        width = (unsigned int)image->w;
        height = (unsigned int)image->h;
        auto rawPixels = (unsigned char*)image->pixels;
        int offset = image->w * image->h * 4;

        pixels.assign(rawPixels, rawPixels + offset);
    }

    void loadRandomImage() {
        pixels.resize( width * height * 4, 0 );
        for( unsigned int i = 0; i < 100; i++ ) {
            const unsigned int x = rand() % width;
            const unsigned int y = rand() % height;
            const unsigned int offset = ( width * 4 * y ) + x * 4;

            const unsigned char whiteness = rand() % 256;

            pixels[ offset + 0 ] = whiteness;        // b
            pixels[ offset + 1 ] = whiteness;        // g
            pixels[ offset + 2 ] = whiteness;        // r
        }
    }

    void init() {
        initSDL();
        loadImage();
        createWindow();
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
        /*
        vector<unsigned char> newPixels(width * height * 4);

        for( unsigned int i = 0; i < newPixels.size(); i+=4 ) {
            const unsigned int x = ( i / 4 ) % width;
            const unsigned int y = i / ( 4 * width );

            //todo


        }
        */
    }

    void output() {

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );
        SDL_UpdateTexture( texture,
                           nullptr,
                           &pixels[0],
                           width * 4 );
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
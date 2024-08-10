#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <spdlog/spdlog.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <wldlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION
#include <nuklear.h>
#include <nuklear_sdl_renderer.h>

#include <math.hpp>
#include <tilemap.hpp>
#include <consts.hpp>
#include <globals.hpp>
#include <imgui.hpp>

#define LOAD_IMAGE(v, n)                                             \
    {                                                                \
        if (std::filesystem::exists(n))                              \
        {                                                            \
            v = SDL_CreateTextureFromSurface(renderer, IMG_Load(n)); \
        }                                                            \
        else                                                         \
        {                                                            \
            spdlog::error("Failed to load image {}", n);             \
        }                                                            \
    }

static SDL_Texture *item_3507;
static SDL_Texture *background_0;
static SDL_Texture *background_2;
static SDL_Texture *background_3;
static SDL_Texture *background_5;
static SDL_Texture *background_7;
static SDL_Texture *background_8;
static SDL_Texture *background_9;
static SDL_Texture *background_10;
static SDL_Texture *background_11;

static SDL_Texture *splash_9_0;
static SDL_Texture *logo;

static Mix_Music *overworldDay;
static Mix_Music *underground;
static Mix_Music *undergroundAlternative;
static Mix_Music *titleScreen;

static std::vector<SDL_Texture *> tileTextures;

static int selectedTile = 0;

static TTF_Font *font;

static Vector2i cameraPos = {0, 0};

static Mix_Music **currentlyPlaying = nullptr;

static nk_context *nkctx;

static double fps = 0;

static bool menu = true;

void drawSprite(SDL_Surface *screen, SDL_Surface *texture, int x, int y)
{
    SDL_Rect srcRect = {0, 0, texture->w, texture->h};
    SDL_Rect destRect = {x, y, texture->w, texture->h};
    SDL_BlitSurface(texture, &srcRect, screen, &destRect);
}

void setTile(Vector2i positionV, int id)
{
    tiles[XY(positionV.x, positionV.y)].id = id;
}

SDL_Point getsize(SDL_Texture *texture)
{
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    return {(int)w, (int)h};
}

void drawText(const char *text, SDL_Color textColor, int x, int y)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (!textSurface)
    {
        exit(1);
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Point size = getsize(textTexture);

    SDL_Rect destRect = {
        x, y,
        size.x, size.y};

    SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);
}

void draw(SDL_Surface *screen, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 53, 43, 243, 255);
    SDL_RenderClear(renderer);

    if (!menu)
    {

        SDL_Rect dest = {
            0, 0,
            1280, 720};

        SDL_Rect undergroundDest = {
            0,
            0,
            getsize(background_2).x * 8,
            getsize(background_2).y * 8,
        };

        SDL_Rect src = {
            0, 0,
            1, 1};
        if (cameraPos.y < -5000.0)
        {
            if (cameraPos.y < -6000.0)
            {
                if (cameraPos.y < -10000.0)
                {
                    if (currentlyPlaying != &undergroundAlternative)
                    {
                        Mix_PlayMusic(undergroundAlternative, 0);
                        currentlyPlaying = &undergroundAlternative;
                    }
                    // SDL_RenderCopy(renderer, background_5, nullptr, 1.0, &undergroundDest);
                }
                else
                {
                    if (currentlyPlaying != &undergroundAlternative)
                    {
                        Mix_PlayMusic(undergroundAlternative, 0);
                        currentlyPlaying = &undergroundAlternative;
                    }
                    // SDL_RenderTextureTiled(renderer, background_3, nullptr, 1.0, &undergroundDest);
                }
            }
            else
            {
                if (currentlyPlaying != &underground)
                {
                    Mix_PlayMusic(underground, 0);
                    currentlyPlaying = &underground;
                }
                // SDL_RenderTextureTiled(renderer, background_2, nullptr, 1.0, &undergroundDest);
            }
        }
        else
        {
            if (currentlyPlaying != &overworldDay)
            {
                Mix_PlayMusic(overworldDay, 0);
                currentlyPlaying = &overworldDay;
            }

            SDL_RenderCopy(renderer, background_0, nullptr, &dest);
            SDL_RenderCopy(renderer, background_7, nullptr, &dest);
            SDL_RenderCopy(renderer, background_8, nullptr, &dest);
            SDL_RenderCopy(renderer, background_9, nullptr, &dest);
            SDL_RenderCopy(renderer, background_10, nullptr, &dest);
            SDL_RenderCopy(renderer, background_11, nullptr, &dest);
        }

        Vector2i startPos = {-(int)round(cameraPos.x / 16), -(int)round(cameraPos.y / 16)};
        Vector2i endPos = {startPos.x + SCREEN_TILES_X, startPos.y + SCREEN_TILES_Y};

        for (int x = startPos.x; x <= endPos.x; ++x)
        {
            for (int y = startPos.y; y <= endPos.y; ++y)
            {
                if (x < 0 || y < 0)
                {
                    continue;
                }

                if (tiles[XY(x, y)].id != -1)
                {
                    SDL_Texture *tile = tileTextures[tiles[XY(x, y)].id];

                    drawTile(renderer, cameraPos, tile, v2(x, y), tiles[XY(x, y)].id);
                }
            }
        }
    }
    else
    {
        SDL_Rect dest = {
            0, 0, 1280, 720
        };

        SDL_Rect logoDest = {
            600, 50, getsize(logo).x, getsize(logo).y
        };

        SDL_RenderCopy(renderer, splash_9_0, nullptr, &dest);
        SDL_RenderCopy(renderer, logo, nullptr, &logoDest);

        if (currentlyPlaying != &titleScreen)
        {
            Mix_PlayMusic(titleScreen, 0);
            currentlyPlaying = &titleScreen;
        }
    }
}

void loadAssets()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        spdlog::error("Failed to initialize SDL3_image: {}", IMG_GetError());
    }

    LOAD_IMAGE(item_3507, "Content/Item_3507.png");

    for (int i = 0; i < 690; i++)
    {
        char buf[256];

        sprintf(buf, "Content/Tiles_%i.png", i);

        if (std::filesystem::exists(buf))
        {
            tileTextures.push_back(SDL_CreateTextureFromSurface(renderer, IMG_Load(buf)));

            spdlog::info("Loaded {}", buf);
        }
        else
        {
            spdlog::info("Failed to load {}: File not found", buf);
        }
    }

    LOAD_IMAGE(background_0, "Content/Background_0.png");
    LOAD_IMAGE(background_2, "Content/Background_2.png");
    LOAD_IMAGE(background_3, "Content/Background_3.png");
    LOAD_IMAGE(background_5, "Content/Background_5.png");
    LOAD_IMAGE(background_7, "Content/Background_7.png");
    LOAD_IMAGE(background_8, "Content/Background_8.png");
    LOAD_IMAGE(background_9, "Content/Background_9.png");
    LOAD_IMAGE(background_10, "Content/Background_10.png");
    LOAD_IMAGE(background_11, "Content/Background_11.png");

    LOAD_IMAGE(splash_9_0, "Content/Splash_9_0.png");
    LOAD_IMAGE(logo, "Content/Logo.png");

    overworldDay = Mix_LoadMUS("Content/Song_OverworldDay.mp3");
    underground = Mix_LoadMUS("Content/Song_Underground.mp3");
    undergroundAlternative = Mix_LoadMUS("Content/Song_AlternativeUnderground.mp3");
    titleScreen = Mix_LoadMUS("Content/Song_TitleScreen.mp3");

    font = TTF_OpenFont("Content/Font.ttf", 24);
}

static bool running = true;

enum MENUSECTION
{
    MENU_LOAD,
    MENU_QUIT,
    MENU_NEW,
    MENU_NONE
};

static std::vector<std::filesystem::path> worldPaths;

void loop()
{
    static SDL_Event event;
    static uint32_t lastTime = SDL_GetTicks();
    static int frameCount = 0;
    const int FPS_UPDATE_INTERVAL = 1000;

    draw(SDL_GetWindowSurface(window), renderer);

    int x, y;

    if (SDL_GetMouseState(&x, &y) == 1)
    {
        Vector2i tilepos = {(int)round((x - cameraPos.x) / tile_size.x), (int)round((y - cameraPos.y) / tile_size.y)};

        tiles[XY(tilepos.x, tilepos.y)].id = selectedTile;

        // spdlog::info("add tile at {}, {}", tilepos.x, tilepos.y);
    }
    else if (SDL_GetMouseState(&x, &y) == 4)
    {
        Vector2i tilepos = {(int)round((x - cameraPos.x) / tile_size.x), (int)round((y - cameraPos.y) / tile_size.y)};

        tiles[XY(tilepos.x, tilepos.y)].id = -1;
    }

    const Uint8 *keystate = SDL_GetKeyboardState(nullptr);

    if (keystate[SDL_SCANCODE_UP])
    {
        cameraPos.y += 5;
    }
    if (keystate[SDL_SCANCODE_DOWN])
    {
        cameraPos.y -= 5;
    }
    if (keystate[SDL_SCANCODE_LEFT])
    {
        cameraPos.x += 5;
    }
    if (keystate[SDL_SCANCODE_RIGHT])
    {
        cameraPos.x -= 5;
    }

    frameCount++;
    uint32_t currentTime = SDL_GetTicks();
    if (currentTime - lastTime >= FPS_UPDATE_INTERVAL)
    {
        fps = static_cast<double>(frameCount * 1000) / (currentTime - lastTime);
        spdlog::info("fps: {}", fps);
        lastTime = currentTime;
        frameCount = 0;
    }

    if (!menu)
    {
        auto drawFn = []()
        {
            /*
            {
                static char path[256];
                static wld_t *world = nullptr;

                ImGui::Begin("WorldTool");

                ImGui::InputText("Load Path", path, 256);

                if (ImGui::Button("Load"))
                {
                    world = wld_open(path);

                    spdlog::info("Loading world {}", world->header.name);

                    for (int x = 0; x < world->header.width; ++x)
                    {
                        for (int y = 0; y < world->header.height; ++y)
                        {
                            if (world->tiles[x][y].tile == 5 || world->tiles[x][y].tile == 7)
                                continue;
                            setTile({x, y}, world->tiles[x][y].tile);
                        }
                    }

                    spdlog::info("End!");

                    cameraPos.x = -world->header.spawn_x * tile_size.x;
                    cameraPos.y = -world->header.spawn_y * tile_size.y;

                    cameraPos.x += 1280 / 2;
                    cameraPos.y += 720 / 2;
                }

                ImGui::Separator();

                if (world != nullptr)
                {
                    static char savePath[256];
                    ImGui::InputText("Save Path", savePath, 256);
                    if (ImGui::Button("Save"))
                    {
                        spdlog::info("Saving world...");

                        for (int x = 0; x < world->header.width; ++x)
                        {
                            for (int y = 0; y < world->header.height; ++y)
                            {
                                world->tiles[x][y].tile = tiles[XY(x, y)].id;
                            }
                        }

                        world->npc_count = 0;

                        wld_write(world, savePath);
                    }
                }

                ImGui::End();
            }
            */
            {
                ImGui::Begin("CameraTool");

                float pos[] = {(float)cameraPos.x, (float)cameraPos.y};

                ImGui::InputFloat2("Position", pos);

                cameraPos.x = pos[0];
                cameraPos.y = pos[1];

                ImGui::End();
            }
            {
                ImGui::Begin("PaintTool");

                ImGui::InputInt("Tile", &selectedTile);

                ImGui::End();
            }
            {
                ImGui::Begin("Stats");

                ImGui::Text("FPS: %lf", fps);

                ImGui::End();
            }
        };

        imguiDraw(drawFn);
    }
    else
    {
        static MENUSECTION currentMenu = MENU_NONE;
        {
            if (nk_begin(nkctx, "Terraria SDL2", nk_rect(10, 10, 230, 700),
                         NK_WINDOW_BORDER | NK_WINDOW_TITLE))
            {

                nk_layout_row_static(nkctx, 40, 200, 1);
                nk_label(nkctx, "by ChickenChunk579", NK_TEXT_CENTERED);
                if (nk_button_label(nkctx, "New"))
                    currentMenu = MENU_NEW;
                if (nk_button_label(nkctx, "Load"))
                    currentMenu = MENU_LOAD;
                if (nk_button_label(nkctx, "Quit"))
                    currentMenu = MENU_QUIT;

                nk_layout_row_end(nkctx);
            }
            nk_end(nkctx);
        }

        if (currentMenu == MENU_NEW)
        {
            if (nk_begin(nkctx, "New", nk_rect(250, 10, 230, 700),
                         NK_WINDOW_BORDER | NK_WINDOW_TITLE))
            {
                nk_layout_row_static(nkctx, 40, 200, 1);

                if (nk_button_label(nkctx, "Close"))
                    currentMenu = MENU_NONE;

                nk_layout_row_end(nkctx);
            }
            nk_end(nkctx);
        }
        if (currentMenu == MENU_LOAD)
        {
            if (nk_begin(nkctx, "Load", nk_rect(250, 10, 230, 700),
                         NK_WINDOW_BORDER | NK_WINDOW_TITLE))
            {
                nk_layout_row_static(nkctx, 40, 200, 1);

                static wld_t *world;

                for (auto worldPath : worldPaths)
                {
                    if (nk_button_label(nkctx, worldPath.stem().c_str()))
                    {
                        world = wld_open(worldPath.c_str());

                        spdlog::info("Loading world {}", world->header.name);

                        for (int x = 0; x < world->header.width; ++x)
                        {
                            for (int y = 0; y < world->header.height; ++y)
                            {
                                if (world->tiles[x][y].tile == 5 || world->tiles[x][y].tile == 7)
                                    continue;
                                setTile({x, y}, world->tiles[x][y].tile);
                            }
                        }

                        spdlog::info("End!");

                        cameraPos.x = -world->header.spawn_x * tile_size.x;
                        cameraPos.y = -world->header.spawn_y * tile_size.y;

                        cameraPos.x += 1280 / 2;
                        cameraPos.y += 720 / 2;

                        menu = false;
                    }
                }

                if (nk_button_label(nkctx, "Close"))
                    currentMenu = MENU_NONE;

                nk_layout_row_end(nkctx);
            }
            nk_end(nkctx);
        }
        if (currentMenu == MENU_QUIT)
        {
            if (nk_begin(nkctx, "Quit", nk_rect(1280 / 2 - 100, 720 / 2 - 50, 200, 125),
                         NK_WINDOW_BORDER | NK_WINDOW_TITLE))
            {
                nk_layout_row_static(nkctx, 20, 178, 1);

                nk_label(nkctx, "Are you sure?", NK_TEXT_CENTERED);

                if (nk_button_label(nkctx, "Quit"))
                    running = false;
                if (nk_button_label(nkctx, "Back"))
                    currentMenu = MENU_NONE;

                nk_layout_row_end(nkctx);
            }
            nk_end(nkctx);
        }

        nk_sdl_render(NK_ANTI_ALIASING_ON);
    }

    SDL_RenderPresent(renderer);

    nk_input_begin(nkctx);
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_DestroyWindow(window);
            SDL_Quit();
            running = false;
#ifdef __EMSCRIPTEN__
            spdlog::info("End");
#endif
            break;
        }

        nk_sdl_handle_event(&event);
    }

    nk_input_end(nkctx);
}

int main()
{
    #ifndef EMSCRIPTEN
    for (const auto &entry : std::filesystem::directory_iterator("/home/rhys/.config/terraria-sdl2"))
    {
        worldPaths.push_back(entry.path());
    }
    #else
    worldPaths.push_back(std::filesystem::path(std::filesystem::path("Content/a_world.wld")));
    #endif

    tiles = new Tile[WORLD_AREA];

    for (int x = 0; x < WORLD_WIDTH; ++x)
    {
        for (int y = 0; y < WORLD_HEIGHT; ++y)
        {
            tiles[XY(x, y)].position = {x, y};
            tiles[XY(x, y)].id = -1;
        }
    }

    SDL_Event event;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        spdlog::error("Failed to initialize SDL: {}", SDL_GetError());
    }
    spdlog::info("Initialized SDL");
    window = SDL_CreateWindow(
        "Rougelike",
        100, 100,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, 0, 0);
    if (window == nullptr)
    {
        spdlog::error("Failed to create the window: {}", SDL_GetError());
    }
    spdlog::info("Created window");
    spdlog::info("Created renderer");

    assert(TTF_Init() == 0);

    spdlog::info("Initialized SDL2 TTF");


    #ifdef EMSCRIPTEN
        // Note: this requires a patched SDL_mixer currently
        Mix_OpenAudioDevice(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096, nullptr, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    #else
        Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    #endif

    spdlog::info("Initialized SDL2 Mixer");


    loadAssets();

    spdlog::info("Loaded assets");

    setTile({0, 0}, 1);

    Mix_PlayMusic(overworldDay, 0);

    imguiInit();

    spdlog::info("initialized IMGUI");

    nkctx = nk_sdl_init(window, renderer);

    {
        nk_font_atlas *atlas;
        struct nk_font_config config = nk_font_config(0);
        nk_font *font;

        nk_sdl_font_stash_begin(&atlas);

        font = nk_font_atlas_add_from_file(atlas, "Content/JetBrainsMono-Bold.ttf", 13, &config);

        nk_sdl_font_stash_end();

        nk_style_set_font(nkctx, &font->handle);
    }

    spdlog::info("initialized Nuklear");

#ifdef __EMSCRIPTEN__
    spdlog::info("Set Emscripten main loop");
    emscripten_set_main_loop(loop, 0, 1);
#else
    spdlog::info("Running main loop");
    while (running)
    {
        loop();
    }
#endif
}
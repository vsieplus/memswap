// Header for Menu State

#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "gameStates/gamestate.hpp"
#include "utils/bitmapfont.hpp"
#include "utils/texture.hpp"
#include "gui/button.hpp"

// class for the Menu State
class MenuState : public GameState {
    public:
        MenuState(MemSwap * game);

        void enterState(MemSwap * game) override;
        void exitState() override;

        void handleEvents(MemSwap * game, const SDL_Event & e) override;
        void update(MemSwap * game, float delta) override;
        void render(SDL_Renderer * renderer) const override;
    
    private:
        // enums for menu screens/their buttons
        enum MenuScreen {
            MENU_MAIN,        // main menu
            MENU_LVLS,        // level select
            MENU_STATS,       // player stats/data
            MENU_CONFIG,      // options/settings
            MENU_CREDITS,     // credits
        };

        enum MainButton {
            MAIN_LVLS,
            MAIN_STATS,
            MAIN_CONFIG,
            MAIN_CREDITS,
        };

        const int BG_PAD = 40;
        const int BUTTON_WIDTH = 128;
        const int BUTTON_HEIGHT = 64;

        // level select layout
        const int LVLS_ROWS = 3;
        const int LVLS_COLS = 10;

        const bool CLICKABLE = false;

        // ID's for gui resources
        const std::string FONT_ID = "mainFont";
        const std::string BG_ID = "play_menu_bg";
        const std::string MENU_BUTTON_ID = "menu_menu_btn";
        const std::string LVL_BUTTON_ID = "menu_lvl_btn";

        // bg texture
        std::shared_ptr<Texture> bgTexture;

        // font for text rendering
        std::shared_ptr<BitmapFont> menuFont;

        // map of button vectors, for each menu state
        std::unordered_map<MenuScreen, std::vector<Button>> stateButtons;

        // store button layouts, for general button focus changing
        // key: screen enum value, val: Pair of (rows, columns) [of buttons]
        std::unordered_map<MenuScreen, std::pair<int, int>> screenLayouts;

        // track curr screen and button focus
        MenuScreen currScreen = MENU_MAIN;
        int currButtonID = MAIN_LVLS;
        Button * currButton = nullptr;

        // button labels
        const std::vector<std::string> MAIN_LABELS = {
            "Play",         // -> level select
            "Stats",        // -> user stats/data
            "Settings",     // -> config
            "Credits",      // -> credits
        };

        const std::vector<std::string> LVLS_LABELS = {
            "tutorial",
            "1-1", "1-2", "1-3", "1-4", "1-5", "1-6", "1-7", "1-8", "1-9", "1-10",
            "2-1", "2-2", "2-3", "2-4", "2-5", "2-6", "2-7", "2-8", "2-9", "2-10",
            "3-1", "3-2", "3-3", "3-4", "3-5", "3-6", "3-7", "3-8", "3-9", "3-10"
        };

        // load buttons for each menu screen 
        void addMainButtons(MemSwap * game);
        void addLvlSelectButtons(MemSwap * game);
        void addStatsButtons(MemSwap * game);
        void addConfigButtons(MemSwap * game);
        void addCreditsButtons(MemSwap * game);

        void changeCurrButton(const SDL_Event & e);

        // handle button activations for each screen
        void activateMain();
        void activateLvlSelect();
        void activateStats();
        void activateConfig();
        void activateCredits();
};

#endif // MENUSTATE_HPP
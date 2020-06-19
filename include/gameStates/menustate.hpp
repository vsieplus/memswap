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
#include "gui/label.hpp"

// class for the Menu State
class MenuState : public GameState {
    public:
        MenuState(MemSwap * game);

        void enterState(MemSwap * game) override;
        void exitState() override;

        void handleEvents(MemSwap * game, const SDL_Event & e) override;
        void update(MemSwap * game, float delta) override;
        void render(SDL_Renderer * renderer) const override;

        // enums for menu screens/their buttons
        enum MenuScreen {
            MENU_MAIN,        // main menu
            MENU_LVLS,        // level select
            MENU_STATS,       // player stats/data
            MENU_HTP,      // options/settings
            MENU_CREDITS,     // credits
        };
    
    private:
        enum MainButton {
            MAIN_LVLS,
            MAIN_STATS,
            MAIN_HTP,
            MAIN_CREDITS,
        };

        const int BG_PAD = 40;

        const bool CLICKABLE = false;

        // if returning to the menu state, or first time entering
        bool returning = false;

        // ID's for gui resources
        const std::string FONT_ID = "mainFont";
        const std::string BG_ID = "play_menu_bg";
        const std::string MENU_BUTTON_ID = "menu_menu_btn";
        const std::string LVL_BUTTON_ID = "menu_lvl_btn";
        const std::string LVL_LOCKED_ID = "menu_lvl_locked";
        const std::string BACK_BUTTON_ID = "menu_back_btn";
        const std::string MENU_LABEL_LONG_ID = "menu_label_long";
        const std::string MENU_LABEL_SHORT_ID = "menu_label_short";
        const std::string MENU_TEXT_BOARD_ID = "menu_text_board";
        const std::string MENU_HTP_BOARD_ID = "menu_htp_board";

        // button labels
        const std::vector<std::string> MAIN_LABELS = {
            "Play",         // -> level select
            "Stats",        // -> user stats/data
            "How To Play",  // -> how to play
            "Credits",      // -> credits
        };

        const std::vector<std::string> LVLS_LABELS = {
            "1-1", "1-2", "1-3", "1-4", "1-5", "1-6", "1-7", "1-8", "1-9", "1-X",
            "2-1", "2-2", "2-3", "2-4", "2-5", "2-6", "2-7", "2-8", "2-9", "2-X",
            "3-1", "3-2", "3-3", "3-4", "3-5", "3-6", "3-7", "3-8", "3-9", "3-X"
        };

        const std::vector<std::string> STATS_LABELS = {"Reset Data"};

        // titles/labels for menu screens
        const std::string LVL_SELECT_TITLE = "Level Select";
        const std::string STATS_TITLE = "Player Stats";
        const std::string HTP_TITLE = "How To Play";
        const std::string CREDITS_TITLE = "Credits";

        // bg texture
        std::shared_ptr<Texture> bgTexture;

        // font for text rendering
        std::shared_ptr<BitmapFont> menuFont;

        // maps of menu labels + button vectors, for each menu screen
        // (eventually generalize -> dynamic/static GUI elems)
        std::unordered_map<MenuScreen, std::vector<Button>> stateButtons;
        std::unordered_map<MenuScreen, std::vector<Label>> stateLabels;

        // store button layouts, for general button focus changing [not including back-button]
        // key: screen enum value, val: Pair of (rows, columns) [of buttons]
        const std::unordered_map<MenuScreen, std::pair<int, int>> BTN_LAYOUTS =
            {
                {MenuScreen::MENU_MAIN, std::make_pair(2, 2)},
                {MenuScreen::MENU_LVLS, std::make_pair(3, 10)},
                {MenuScreen::MENU_STATS, std::make_pair(1, 1)},
                {MenuScreen::MENU_HTP, std::make_pair(0, 0)},
                {MenuScreen::MENU_CREDITS, std::make_pair(0, 0)},
            };

        // track curr screen and button focus
        MenuScreen currScreen = MENU_MAIN;
        int currButtonID = MAIN_LVLS;
        Button * currButton = nullptr;

        // load buttons for each menu screen 
        void addMainGUI(MemSwap * game);
        void addLvlSelectGUI(MemSwap * game);
        void addStatsGUI(MemSwap * game);
        void addHTPGUI(MemSwap * game);
        void addCreditsGUI(MemSwap * game);

        void addBackButton(std::vector<Button> & buttons, MemSwap * game);

         // add a label to the given label vector
        void addTitleLabel(std::vector<Label> & labels, std::string label,
            bool longLabel, MemSwap * game) const;

        void addTextBoard(std::vector<Label> & labels, std::string label, 
            MemSwap * game, Label::TextAlignment alignment);

        void changeCurrButton(const SDL_Event & e);
        void updateCurrButton();

        // handle button activations for each screen
        void activateMain(MemSwap * game);
        void activateLvlSelect(MemSwap * game);
        void activateStats();
        void activateHTP();
        void activateCredits();

        bool checkOnBackButton() const;

        // construct and return vector of spaced buttons
        std::vector<Button> getSpacedButtons(
            const std::vector<std::string> & buttonLabels,
            const std::shared_ptr<Texture> & buttonTexture, 
            const std::shared_ptr<BitmapFont> & buttonFont,
            int buttonAreaX, int buttonAreaY, int buttonAreaXEnd, int buttonAreaYEnd, 
            SDL_Color outlineColor, SDL_Color textColor,
            MenuScreen screen) const;

        // automatically compute space to evenly space buttons/gui elems in a specified area
        static int calculateInterHSpace(int buttonsPerRow, int buttonWidth,
            int startX, int endX);
        static int calculateInterVSpace(int buttonsPerCol, int buttonHeight,
            int startY, int endY);
};

#endif // MENUSTATE_HPP
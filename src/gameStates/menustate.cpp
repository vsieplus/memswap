/**
 * @file menustate.cpp
 * @author vsie
 * @brief implementation for menustate class
 * @version 0.1
 * @date 2020-05-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "memswap.hpp"

#include "gameStates/menustate.hpp"

MenuState::MenuState(MemSwap * game) : GameState(GAME_STATE_MENU) {
    // retrieve resources
    bgTexture = game->getResManager().getTexture(BG_ID);
    menuFont = game->getResManager().getFont(FONT_ID);

    // add buttons/other gui elements for each menu screen
    addMainGUI(game);
    addLvlSelectGUI(game);
    addStatsGUI(game);
    addConfigGUI(game);
    addCreditsGUI(game);

    // set current button to first button on main menu screen, first ptr
    currButton = &(stateButtons.at(currScreen).at(currButtonID));
}


void MenuState::enterState(MemSwap * game) {
    // reset screen to main
}

void MenuState::exitState() {
}

// functions to add buttons for the specified screen
void MenuState::addMainGUI(MemSwap * game) {
    // add title


    // add buttons
    std::vector<Button> mainButtons;

    // calc. button spacing in bottom (2/3) [4 buttons, 2 rows] inside border
    int interButtonVSpace = (((game->getScreenHeight() - (game->getScreenHeight()
        - (2 * BG_PAD)) / 3) - (BUTTON_HEIGHT * (MAIN_LABELS.size() / 2))) 
        / (MAIN_LABELS.size() / 2 + 1)) / 2;
    int interButtonHSpace = ((game->getScreenWidth() - BG_PAD) - (BUTTON_WIDTH *
        (MAIN_LABELS.size() / 2))) / (MAIN_LABELS.size() / 2 + 1);

    // start placing buttons in bottom 2/3 of inner-bg area
    int buttonAreaX = BG_PAD;
    int buttonAreaY = BG_PAD + ((game->getScreenHeight() - (2 * BG_PAD)) / 3);

    for(unsigned int i = 0; i < MAIN_LABELS.size() / 2; i++) {
        for(unsigned int j = 0; j < MAIN_LABELS.size() / 2; j++) {
            mainButtons.emplace_back(buttonAreaX + (j * BUTTON_WIDTH) + ((j + 1) *
                interButtonHSpace), buttonAreaY + (i * BUTTON_HEIGHT) + ((i + 1) *
                interButtonVSpace), CLICKABLE, 
                game->getResManager().getTexture(MENU_BUTTON_ID), 
                game->getOutlineColor(), MAIN_LABELS.at((i * 2) + j), menuFont);
        }
    }

    mainButtons.front().setFocus(true);

    stateButtons.emplace(MenuScreen::MENU_MAIN, mainButtons);
    screenLayouts.emplace(MenuScreen::MENU_MAIN, std::make_pair<int, int>(2, 2));
}

void MenuState::addLvlSelectGUI(MemSwap * game) {
    std::vector<Button> LvlSelectButtons;

    stateButtons.emplace(MenuScreen::MENU_LVLS, LvlSelectButtons);
    screenLayouts.emplace(MenuScreen::MENU_LVLS, std::make_pair(LVLS_COLS, LVLS_ROWS));
}

void MenuState::addStatsGUI(MemSwap * game) {
    std::vector<Button> StatsButtons;

    stateButtons.emplace(MenuScreen::MENU_STATS, StatsButtons);
    screenLayouts.emplace(MenuScreen::MENU_STATS, std::make_pair<int, int>(2, 1));
}

void MenuState::addConfigGUI(MemSwap * game) {
    std::vector<Button> ConfigButtons;

    stateButtons.emplace(MenuScreen::MENU_CONFIG, ConfigButtons);
    screenLayouts.emplace(MenuScreen::MENU_CONFIG, std::make_pair<int, int>(1, 1));
}

void MenuState::addCreditsGUI(MemSwap * game) {
    // only need a 'back' button
    std::vector<Button> creditsButtons;

    stateButtons.emplace(MenuScreen::MENU_CREDITS, creditsButtons);
    screenLayouts.emplace(MenuScreen::MENU_CREDITS, std::make_pair<int, int>(1, 1));
}

void MenuState::handleEvents(MemSwap * game, const SDL_Event & e) {
    currButton->handleEvents(e);

    // handle switching button focus (except for credit screen [only back btn])
    if(currScreen != MenuScreen::MENU_CREDITS &&  e.type == SDL_KEYDOWN) {
        changeCurrButton(e);
    }
}

// general function to change the current button focus (for any screen)
void MenuState::changeCurrButton(const SDL_Event & e) {
    currButton->setFocus(false);
    auto sym = e.key.keysym.sym;

    // depending on dir, change button in current direction, depending on 
    // button layout of the current screen

    // .first = buttons per row, .second = buttons per column
    auto layout = screenLayouts.at(currScreen);
    int & rowBtns = layout.first;
    int & colBtns = layout.second;
    int totalBtns = rowBtns * colBtns;

    int nextID = -1;

    switch(sym) {
        // user wants to move up
        case SDLK_w:
            // compute hypothetical next button
            nextID = currButtonID - rowBtns;

            // check for up move on first row -> same col, last row
            if(nextID < 0) {
                currButtonID = (totalBtns - ((rowBtns - 1) - currButtonID)) - 1;
            } else {
                currButtonID = nextID;
            }
            break;
        
        // similar as above
        case SDLK_a:
            nextID = currButtonID - 1;

            // move left when on first column -> last column, same row
            if(currButtonID % rowBtns == 0) {
                currButtonID = (currButtonID / rowBtns) * colBtns + colBtns - 1;
            } else {
                currButtonID = nextID;
            }
            break;
        case SDLK_s:
            nextID = currButtonID + rowBtns;

            // moving down when on last row [move to first row in same col.]
            if(nextID > totalBtns - 1) {
                currButtonID = currButtonID % rowBtns;
            } else {
                currButtonID = nextID;
            }
            break;
        case SDLK_d:
            nextID = currButtonID + 1;

            // moving right when on last column
            if((currButtonID + 1) % rowBtns == 0) {
                currButtonID = (currButtonID / rowBtns) * colBtns;
            } else {
                currButtonID = nextID;
            }
            break;      
        default:        
            break;                                         
    }

    currButton = &(stateButtons.at(currScreen).at(currButtonID));
    currButton->setFocus(true);
}

void MenuState::update(MemSwap * game, float delta) {
    currButton->update();

    // check if current button is activated
    if(currButton->isActivated()) {
        currButton->setActivated(false);

        switch(currScreen) {
            case MenuScreen::MENU_MAIN:
                activateMain();
                break;
            case MenuScreen::MENU_LVLS:
                activateLvlSelect();
                break;
            case MenuScreen::MENU_STATS:
                activateStats();
                break;
            case MenuScreen::MENU_CONFIG:
                activateConfig();
                break;
            case MenuScreen::MENU_CREDITS:
                activateCredits();
                break;
        }
    }
}

// handle button activations for each screen
void MenuState::activateMain() {
    switch(currButtonID) {
        case MainButton::MAIN_LVLS:
            currScreen = MenuScreen::MENU_LVLS;
            break;
        case MainButton::MAIN_STATS:
            currScreen = MenuScreen::MENU_STATS;
            break;
        case MainButton::MAIN_CONFIG:
            currScreen = MenuScreen::MENU_CONFIG;
            break;    
        case MainButton::MAIN_CREDITS:
            currScreen = MenuScreen::MENU_CREDITS;
            break;
    }

    currButtonID = 0;
}

void MenuState::activateLvlSelect() {
    
}

void MenuState::activateStats() {

}

void MenuState::activateConfig() {

}

void MenuState::activateCredits() {

}

/// Render function for the game state
void MenuState::render(SDL_Renderer * renderer) const {
    bgTexture->render(0, 0, renderer);

    // render each of the buttons for the current screen
    for(Button button: stateButtons.at(currScreen)) {
        button.render(renderer);
    }
}
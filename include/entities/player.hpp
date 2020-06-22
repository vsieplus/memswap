// Header file for Player class

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <utility>
#include <SDL.h>

#include "entities/movable.hpp"

class Player : public Movable {
    private:
        static const int PLAYER_VELOCITY = 6;

        // track when a player is undoing a buffer/set to BUFFER_CAP each time
        static const int UNDO_BUFFER_CAP = 15;
        int undoBuffer = 0;

        bool teleporting = false;
        
        // check if player has input movement
        void checkMovement(const Uint8 * keyStates, Level * level);

        // try to push a diamond
        void pushDiamond(Level * level);

        // check for portal
        void checkPortal(Level * level);
    public:
        const static std::string PLAYER_SHAPE;

        Player(int screenX, int screenY, int gridX, int gridY, int parity,
            std::shared_ptr<Sprite> entitySprite);

        // game loop stuff
        void handleEvents(const Uint8 * keyStates, Level * level) override;
        void update(Level * level, float delta) override;
        void render(SDL_Renderer* renderer) const override;

        bool isTeleporting() const;
        void setTeleporting(bool teleporting);
};

#endif // PLAYER_HPP
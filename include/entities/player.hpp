// Header file for Player class

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <utility>
#include <SDL.h>

#include "utlis/texture.hpp"

enum Directions {
    DIR_NONE,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

class Player : public Entity {
    private:
        // Movement progress + tracking
        float moveProg = 0.f;

        bool moving = false;
        bool bufferedMove = false;      // Allow buffered movement

        int startX, startY, endX, endY; // Start and end positions for movement
        
        int moveDir = DIR_NONE          // direction of player's move
        int bufferedDir = DIR_NONE;     // direction of player's buffered move
        int bufferedX = 0;              // buffered movement position
        int bufferedY = 0;              

        Uint32 moveStartTime = 0;       // time since movement started


    public:
        Player(int screenX, int screenY, int gridX, int gridY, 
            SDL_Renderer * renderer);

        static const int PLAYER_VELOCITY = 10;       // Pixels moved per sec.
        static const float MOVEMENT_BUFFER = 0.85f;  // How soon through the
                                                     // curr movement can buffer

        void handleEvents(const Uint8* keyStates, Level * level) override;
        void update(Level * level) override;
        void render(SDL_Renderer* renderer) override;

        void checkMovement(const Uint8* keyStates, Level * level);

        void initMovement(int direction);
        void initMovement(int xPosChange, int yPosChange, int xGridChange, 
            int yGridChange, Level * level);
        
        void move();

        static std::pair<int,int> lerp(int startX, int startY, int endX,
            int endY, float t);

        float getMoveProg();
};

#endif // PLAYER_HPP
// Implementation for Player class

#include <stdlib.h>

#include "entities/player.hpp"
#include "entities/receptor.hpp"
#include "entities/diamond.hpp"
#include "level/level.hpp"

const std::string Player::PLAYER_SHAPE = "player";

Player::Player(int screenX, int screenY, int gridX, int gridY, int parity,
    std::shared_ptr<Sprite> entitySprite) : Movable(screenX, screenY, gridX, 
    gridY, PLAYER_VELOCITY, parity, entitySprite, PLAYER_SHAPE) {}

void Player::handleEvents(const Uint8 * keyStates, Level * level) {
    // check for move undo ('u')
    if(keyStates[SDL_SCANCODE_U] && undoBuffer == 0) {
        undoBuffer = UNDO_BUFFER_CAP;
    } else if((!moving || (moveProg > MOVEMENT_BUFFER && bufferedDir == DIR_NONE)) &&
        boostPower == 0 && !merging && !teleporting) {

        // Check if player wants to start moving or buffer a move, when not boosted,
        // merging, or teleporting
        checkMovement(keyStates, level);
    }
}

void Player::update(Level * level, float delta) {
    // check for move undo
    if(undoBuffer > 0 && undoBuffer-- == UNDO_BUFFER_CAP) {
        if(level->isPerfect()) level->setPerfect(false);
        undoAction(level);
    } else if((moveDir != DIR_NONE || bufferedDir != DIR_NONE) && boostPower == 0) {
        // check for entity interaction if player tried to move + isn't boosted
        pushDiamond(level);
        checkReceptor(level);
        checkPortal(level);
    } else if(merging) {
        // if player not moving + is merging, check if level is complete
        if(!moving && !level->isCompleted()) level->checkComplete();
    }

    // update player movement
    Movable::update(level, delta);

    // Update player parity
    //tileParity = level->getTileParity(gridX, gridY);
}

void Player::render(SDL_Renderer* renderer) const {
    Movable::render(renderer);
    
    // render other player effects
}

void Player::checkMovement(const Uint8 * keyStates, Level * level) {
    Direction newDir = DIR_NONE;

    // Check for key inputs
    if(keyStates[SDL_SCANCODE_W]) {
        newDir = DIR_UP;
    } else if (keyStates[SDL_SCANCODE_S]) {
        newDir = DIR_DOWN;
    } else if (keyStates[SDL_SCANCODE_A]) {
        newDir = DIR_LEFT;
    } else if (keyStates[SDL_SCANCODE_D]) {
        newDir = DIR_RIGHT;       
    }
    
    // Update the buffered Direction if already moving, or set new moveDir
    if(moving) {
        bufferedDir = newDir;
    } else {
        moveDir = newDir;
    }
}

void Player::pushDiamond(Level * level) {
    Direction pushDir = currCheckDir();
    auto diamond = getEntity<Diamond>(level, pushDir);

    // set move direction of diamond if not already merging/merged w/receptor
    if(diamond.get() && !diamond->isMerging()) {
        // set the move direction of the diamond
        diamond->setMoveDir(pushDir);
    }
}

void Player::checkPortal(Level * level) {
    auto portal = getEntity<Portal>(level, currCheckDir());

    // check if portal is there, if so, activate teleport status
    if(portal.get()) {
        teleporting = true;

        portal->setActivated(true);

        // set portal's player, remove portals from grid temporarily
        portal->setPlayer(level->getGridElement<Player>(gridX, gridY));
        portal->removePortals(level);
    }
}

bool Player::isTeleporting() const {
    return teleporting;
}

void Player::setTeleporting(bool teleporting) {
    this->teleporting = teleporting;
}
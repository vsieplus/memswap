// Abstract Entity class

#include "entities/entity.hpp"
#include "level/level.hpp"

Entity::Entity(int sX, int sY, int gX, int gY, std::string texturePath) :
    screenX(sX), screenY(sY), gridX(gX), gridY(gY) {
    texture.loadTexture(texturePath);
}

/**
 * @brief Checks collision for current entity with the specified destination
 * 
 * @return true if there is a collision
 */
bool Entity::checkCollision(Level * level, int destGridX, int destGridY) {
    // Check if new position is in bounds
    if(!( (destGridX > 0 && destGridX < level->getGridWidth() - 1) && 
          (destGridY > 0 && destGridY < level->getGridHeight() - 1) )) {
        return true;
    }

    // check collision with dest position. Return true if non-null entity
    return level->getGrid()->at(Level::xyToIndex(destGridX, destGridY)) != nullptr;
}

int Entity::getScreenX() {
    return screenX;
}

int Entity::getScreenY() {
    return screenY;
}

int Entity::getGridX() {
    return gridX;
}

int Entity::getGridY() {
    return gridY;
}
#include "utils/sprite.hpp"

Sprite::Sprite(std::shared_ptr<Texture> spritesheet, const SDL_Rect & clip) :
    spritesheet(spritesheet), spriteClip(clip) {}

// render the sprite at the specified area
void Sprite::render(SDL_Renderer * renderer, const SDL_Rect & renderArea) const {
    SDL_RenderCopy(renderer, spritesheet->getTexture().get(), &spriteClip, &renderArea);
}
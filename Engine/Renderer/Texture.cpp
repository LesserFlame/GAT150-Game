#include "Texture.h" 
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL.h> 
#include <SDL_image.h> 

namespace jemgine
{
    Texture::~Texture()
    {
        // !! if texture not null SDL_DestroyTexture 
    }

    bool Texture::Create(std::string filename, ...)
    {
        va_list args;
        va_start(args, filename);
        Renderer& renderer = va_arg(args, Renderer);
        va_end(args);
        return Create(renderer, filename);
    }

    bool Texture::Create(Renderer& renderer, const std::string& filename)
    {
        // load surface 
        SDL_Surface* surface = IMG_Load(filename.c_str());// !! call IMG_Load with c-string of filename 
        if (surface == nullptr)
        {
            LOG(SDL_GetError());
            return false;
        }
        // create texture 
        // !! call SDL_CreateTextureFromSurface passing in renderer and surface 
        // !! the first parameter takes in the m_renderer from renderer 
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);// 
        if (m_texture == nullptr)
        {
            LOG(SDL_GetError());
            SDL_FreeSurface(surface);
            return false;
        }
            // !! call SDL_FreeSurface with surface as the parameter 
            // !! no need to keep surface after texture is created 
        SDL_FreeSurface(surface);
        return true;
    }

    bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer)
    {
        // destroy the current texture if one exists 
        if (m_texture) SDL_DestroyTexture(m_texture);
        // create texture 
            
        // !! call SDL_CreateTextureFromSurface passing in renderer and surface 
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

        // !! call SDL_FreeSurface passing in surface (surface no longer needed) 
        SDL_FreeSurface(surface);
        // !! check if m_texture is nullptr, if so then LOG error and return false 
        if (m_texture == nullptr)
        {
            LOG(SDL_GetError());
            return false;
        }

        return true;
    }

    Vector2 Texture::GetSize() const
    {
        SDL_Point point;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);

        return Vector2(point.x, point.y);
    }
}
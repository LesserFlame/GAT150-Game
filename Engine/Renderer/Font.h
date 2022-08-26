#pragma once 
// !! add necessary includes 
#include "Resource/Resource.h"
#include <string>
// !! forward declare the _TTF_Font struct 

struct _TTF_Font;
struct SDL_Surface;

namespace jemgine
{
	struct Color;
	
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		SDL_Surface* CreateSurface(const std::string& text, const Color& color);

		bool Create(std::string filename, ...) override;
		bool Load(const std::string& filename, int fontSize);

		friend class Text;

	private:
		_TTF_Font* m_ttfFont = nullptr;

		
	};
}
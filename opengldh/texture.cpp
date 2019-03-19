#include "texture.h"
#include "png.h"

#pragma comment(lib, "libpng16.lib")
#pragma comment(lib, "zlib.lib")

CTexture* CTexture::LoadTexture(const std::string& path)
{
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	return nullptr;
}

#include "texture.h"
#include "ggl.h"
#include "png.h"

#pragma comment(lib, "libpng16.lib")
#pragma comment(lib, "zlib.lib")

CTexture* CTexture::LoadTexture(const std::string& path)
{
	const unsigned char* png_info = DecodePng(path);

	return nullptr;
}

const unsigned char* CTexture::DecodePng(const std::string& path)
{
	png_structp png_ptr = nullptr;
	png_infop info_ptr = nullptr;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
		return nullptr;

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_write_struct(&png_ptr, NULL);
		return nullptr;
	}
	
	int ret_val = setjmp(png_jmpbuf(png_ptr));
	if (0 != ret_val)
	{
		fprintf(stderr, "´íÎóÂë£º%d\n", ret_val);
		return nullptr;
	}

	FILE* pFile = fopen(path.c_str(), "rb");
	if (pFile == nullptr)
	{
		return 0;
	}
	png_init_io(png_ptr, pFile);

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

	png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	png_uint_32 width = png_get_image_width(png_ptr, info_ptr);
	png_uint_32 height = png_get_image_height(png_ptr, info_ptr);

	png_bytepp p_rows = png_get_rows(png_ptr, info_ptr);

	unsigned char* buff = new unsigned char[height * width * 4];
	
	switch (color_type)
	{
	case PNG_COLOR_TYPE_RGB_ALPHA:
		for (png_uint_32 i = 0; i < height; ++i)
		{
			for (png_uint_32 j = 0; j < (width * 4); ++j)
			{
				buff[i*width * 4 + j] = p_rows[i][j];
			}
		}
		break;
	case PNG_COLOR_TYPE_RGB:
		for (png_uint_32 i = 0; i < height; ++i)
		{
			for (png_uint_32 j = 0; j < width; ++j)
			{
				buff[(i*width + j) * 4] = p_rows[i][j * 3];
				buff[(i*width + j) * 4 + 1] = p_rows[i][j * 3 + 1];
				buff[(i*width + j) * 4 + 2] = p_rows[i][j * 3 + 2];
				buff[(i*width + j) * 4 + 3] = 255;
			}
		}
		break;
	default:
		break;
	}

// 	for (int i = 0; i < height; ++i)
// 	{
// 	 	for (int j = 0; j < width; ++j)
// 	 	{
// 			printf("(%d,%d,%d,%d),", buff[(i*width + j) * 4]
// 				, buff[(i*width + j) * 4 + 1]
// 				, buff[(i*width + j) * 4 + 2]
// 				, buff[(i*width + j) * 4 + 3]
// 			);
// 	 	}
// 	 	printf("\n");
// 	}

//	printf("w:%d, h:%d\n", width, height);

	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
	fclose(pFile);

	return buff;
}

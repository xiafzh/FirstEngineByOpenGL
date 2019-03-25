#pragma once
#include "ggl.h"


class CTexture 
{

public:
	static CTexture* LoadTexture(const std::string& path);

private:
	static const unsigned char* DecodePng(const std::string& path);
};
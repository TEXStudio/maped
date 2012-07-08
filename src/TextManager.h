#pragma once
#include <GXBase.h>
#include <string>
#include "Utility.h"

class TextManager
{
private:
	GLuint _LetterTextures[42];
	GLuint LetterTexture(char in);
	void GenerateLetterTextures();
	int CreateTexture(std::string FileName);
public:
	TextManager() { }
	void Initialise();
	void RenderText(std::string Text, float x, float y, float r, float g, float b);
};
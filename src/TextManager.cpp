#include "TextManager.h"


void TextManager::GenerateLetterTextures()
{
	std::string sTemp = "";

	_LetterTextures[0] = CreateTexture("Font/a.tga");
	_LetterTextures[1] = CreateTexture("Font/b.tga");
	_LetterTextures[2] = CreateTexture("Font/c.tga");
	_LetterTextures[3] = CreateTexture("Font/d.tga");
	_LetterTextures[4] = CreateTexture("Font/e.tga");
	_LetterTextures[5] = CreateTexture("Font/f.tga");
	_LetterTextures[6] = CreateTexture("Font/g.tga");
	_LetterTextures[7] = CreateTexture("Font/h.tga");
	_LetterTextures[8] = CreateTexture("Font/i.tga");
	_LetterTextures[9] = CreateTexture("Font/j.tga");
	_LetterTextures[10] = CreateTexture("Font/k.tga");
	_LetterTextures[11] = CreateTexture("Font/l.tga");
	_LetterTextures[12] = CreateTexture("Font/m.tga");
	_LetterTextures[13] = CreateTexture("Font/n.tga");
	_LetterTextures[14] = CreateTexture("Font/o.tga");
	_LetterTextures[15] = CreateTexture("Font/p.tga");
	_LetterTextures[16] = CreateTexture("Font/q.tga");
	_LetterTextures[17] = CreateTexture("Font/r.tga");
	_LetterTextures[18] = CreateTexture("Font/s.tga");
	_LetterTextures[19] = CreateTexture("Font/t.tga");
	_LetterTextures[20] = CreateTexture("Font/u.tga");
	_LetterTextures[21] = CreateTexture("Font/v.tga");
	_LetterTextures[22] = CreateTexture("Font/w.tga");
	_LetterTextures[23] = CreateTexture("Font/x.tga");
	_LetterTextures[24] = CreateTexture("Font/y.tga");
	_LetterTextures[25] = CreateTexture("Font/z.tga");
	_LetterTextures[26] = CreateTexture("Font/0.tga");
	_LetterTextures[27] = CreateTexture("Font/1.tga");
	_LetterTextures[28] = CreateTexture("Font/2.tga");
	_LetterTextures[29] = CreateTexture("Font/3.tga");
	_LetterTextures[30] = CreateTexture("Font/4.tga");
	_LetterTextures[31] = CreateTexture("Font/5.tga");
	_LetterTextures[32] = CreateTexture("Font/6.tga");
	_LetterTextures[33] = CreateTexture("Font/7.tga");
	_LetterTextures[34] = CreateTexture("Font/8.tga");
	_LetterTextures[35] = CreateTexture("Font/9.tga");
	_LetterTextures[36] = CreateTexture("Font/space.tga");
	_LetterTextures[37] = CreateTexture("Font/fullstop.tga");
	_LetterTextures[38] = CreateTexture("Font/colon.tga");
	_LetterTextures[39] = CreateTexture("Font/hyphen.tga");
	_LetterTextures[40] = CreateTexture("Font/exclamation.tga");
	_LetterTextures[41] = CreateTexture("Font/question.tga");
}
int TextManager::CreateTexture(std::string FileName)
{
	gxbase::Image TempImage;
	
	GLuint TextureID[1] = {-1};

	TempImage.Load(FileName.c_str());
	if (!TempImage.IsEmpty())
	{
		glGenTextures(1, &TextureID[0]);
		glBindTexture(GL_TEXTURE_2D, TextureID[0]);
		TempImage.gluBuild2DMipmaps();
		TempImage.Free();
		return TextureID[0];
	}
	else return -1;
}
GLuint TextManager::LetterTexture(char in)
{
	switch(in)
	{
	case 'a':
	case 'A':
		return _LetterTextures[0];
		break;
	case 'b':
	case 'B':
		return _LetterTextures[1];
		break;
	case 'c':
	case 'C':
		return _LetterTextures[2];
		break;
	case 'd':
	case 'D':
		return _LetterTextures[3];
		break;
	case 'e':
	case 'E':
		return _LetterTextures[4];
		break;
	case 'f':
	case 'F':
		return _LetterTextures[5];
		break;
	case 'g':
	case 'G':
		return _LetterTextures[6];
		break;
	case 'h':
	case 'H':
		return _LetterTextures[7];
		break;
	case 'i':
	case 'I':
		return _LetterTextures[8];
		break;
	case 'j':
	case 'J':
		return _LetterTextures[9];
		break;
	case 'k':
	case 'K':
		return _LetterTextures[10];
		break;
	case 'l':
	case 'L':
		return _LetterTextures[11];
		break;
	case 'm':
	case 'M':
		return _LetterTextures[12];
		break;
	case 'n':
	case 'N':
		return _LetterTextures[13];
		break;
	case 'o':
	case 'O':
		return _LetterTextures[14];
		break;
	case 'p':
	case 'P':
		return _LetterTextures[15];
		break;
	case 'q':
	case 'Q':
		return _LetterTextures[16];
		break;
	case 'r':
	case 'R':
		return _LetterTextures[17];
		break;
	case 's':
	case 'S':
		return _LetterTextures[18];
		break;
	case 't':
	case 'T':
		return _LetterTextures[19];
		break;
	case 'u':
	case 'U':
		return _LetterTextures[20];
		break;
	case 'v':
	case 'V':
		return _LetterTextures[21];
		break;
	case 'w':
	case 'W':
		return _LetterTextures[22];
		break;
	case 'x':
	case 'X':
		return _LetterTextures[23];
		break;
	case 'y':
	case 'Y':
		return _LetterTextures[24];
		break;
	case 'z':
	case 'Z':
		return _LetterTextures[25];
		break;
	case '0':
		return _LetterTextures[26];
		break;
	case '1':
		return _LetterTextures[27];
		break;
	case '2':
		return _LetterTextures[28];
		break;
	case '3':
		return _LetterTextures[29];
		break;
	case '4':
		return _LetterTextures[30];
		break;
	case '5':
		return _LetterTextures[31];
		break;
	case '6':
		return _LetterTextures[32];
		break;
	case '7':
		return _LetterTextures[33];
		break;
	case '8':
		return _LetterTextures[34];
		break;
	case '9':
		return _LetterTextures[35];
		break;
	case '.':
		return _LetterTextures[37];
		break;
	case ':':
		return _LetterTextures[38];
		break;
	case '-':
		return _LetterTextures[39];
		break;
	case '!':
		return _LetterTextures[40];
		break;
	case '?':
		return _LetterTextures[41];
		break;
	default:
		return _LetterTextures[36];
		break;
	}
}


void TextManager::Initialise()
{
		GenerateLetterTextures();
}
void TextManager::RenderText(std::string Text, float x, float y, float r, float g, float b)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	GLuint iTemp = 0;
	float TempSize = 0.05f;
	glColor4f(r, g, b, 1.0f);
	float xLeft = x - TempSize * (int) Text.size() * 0.5f * 0.6f;
	float yBottom = y - TempSize * 0.5f; 
	
	for (int i = 0; i < (int)Text.size(); i ++)
	{
		iTemp =  LetterTexture(Text[i]);
		glBindTexture(GL_TEXTURE_2D, iTemp);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 1.0f);
			glVertex3f(xLeft + i*TempSize*0.6f, yBottom + TempSize, -2.8f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(xLeft + i*TempSize*0.6f, yBottom, -2.8f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(xLeft + (i+1)*TempSize*0.6f, yBottom, -2.8f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(xLeft + i*TempSize*0.6f, yBottom + TempSize, -2.8f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(xLeft + (i+1)*TempSize*0.6f, yBottom, -2.8f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(xLeft + (i+1)*TempSize*0.6f, yBottom + TempSize, -2.8f);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
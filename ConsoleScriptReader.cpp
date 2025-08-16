#include "Console.h"

void Vir::DrawPixel(int posX, int posY, int r, int g, int b, int a)
{
	if((posX < 128 || posX >= 0) && (posY <= 0 || posY > 0) && a > 0.0f)
	{
		screenBuffer[posX][posY] = glm::vec4(r, g, b, a);
	}

	if(a <= 0.0f)
	{
		screenBuffer[posX][posY] = backGroundColor;
	}
}

void Vir::DrawSprite(int spriteNum, int posX, int posY)
{
	if(spriteNum < sprites.size())
	{
		Sprite sprite = sprites[spriteNum];
		for(int i = 0; i<8; i++)
		{
			for(int j = 0; j<8; j++)
			{
				if(sprite.colors[i][j].a > 0.0f){ screenBuffer[posX + i][posY + j] = sprite.colors[i][j]; }
				else { screenBuffer[posX + i][posY + j] = backGroundColor; }
			}
		}
	}
}

void Vir::InitScriptReader()
{
	lua.open_libraries(sol::lib::base);
	lua.safe_script_file(scriptPath.c_str());

	lua.new_usertype<Vir>("renderer",
		"drawPixel", &Vir::DrawPixel,
		"drawSprite", &Vir::DrawSprite
	);

	lua["renderer"] = this;
}

void Vir::Start()
{
	lua.safe_script_file(scriptPath.c_str());
	lua["start"]();
}

void Vir::Update()
{
	lua["update"]();
}
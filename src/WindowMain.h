#pragma once
#include <GXBase.h>
#include "TextManager.h"

using namespace gxbase;

class WindowMain : public GLWindowEx
{
private:
	int _width, _height, _lastkey, _mousepos[2], 
		_powerupCount, _waypointCount, _sceneryCount;
	GLuint _bgID;
	bool _renderMode, _imageVisible; 
	int nInput;
	char cInput; 
	TextManager Text; 
	bool IsPaused;
	Vector3f Waypoints[50];
	Vector3f Powerups[25];
	Vector3f Scenery[100];
	Vector3f Start;
	gxbase::Image _background; 
public:
	WindowMain();
	void OnCreate();
	void OnDisplay();
	void OnIdle();
	void OnDestroy();
	void DisplayLoop();
	void CreateLoop();
	void OnMouseMove(int x, int y);
	void OnKeyboard(int key, bool down);
	void AddPowerup();
	void AddWaypoint(); 
	void AddScenery(); 
	void AddStart();
	void DumpToFile();
	void DumpToFile(std::string FileName);
};

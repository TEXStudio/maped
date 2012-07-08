#pragma once

#include "GXBase.h"
#include "WindowMain.h"
using namespace gxbase;



class AppMain:
	public App
{
private:
	WindowMain _w;
public:
	AppMain();
	void OnCreate();
};
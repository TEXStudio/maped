#include <glex.h>
#include "WindowMain.h"
#include <WinUser.h>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

WindowMain::WindowMain() : _width (800), _height (800), _lastkey (-1), 
	_powerupCount (0), _waypointCount (0), _sceneryCount (0),
	_bgID (-1), _renderMode (false), _imageVisible(true)
{
	SetDepthBits(24);
	SetStencilBits(1);
	SetTitle("Waypoint Editor Tool");
	_mousepos[0] = 512;
	_mousepos[1] = 512;
	IsPaused = false; 
	Start.x = 0.0f; 
	Start.y = 0.0f; 
	Start.z = 0.0f;
}

void WindowMain::OnCreate()
{
	GLWindowEx::OnCreate();
	//wglSwapIntervalEXT(0);

	SetSize(_width,_height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-0.08f,0.08f,-0.1f,0.1f,0.1f,20.0f);
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glViewport(0,0, _width,_height);

	// Use vertex information for diffuse and diffuse colour 
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glLineWidth(2.0f);

	Text.Initialise();
	_lastkey = 0;

	//CreateLoop();
	glLineWidth(20.0f);
	glPointSize(5.0f);
	_background.Load("map.tga"); 
	if (!_background.IsEmpty())
	{
		
		glGenTextures(1, &_bgID);
		glBindTexture(GL_TEXTURE_2D, _bgID);
		_background.gluBuild2DMipmaps();
	}
}

void WindowMain::OnDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPointSize(5.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -2.5f);

		if (_bgID != -1 && _imageVisible)
		{
		glEnable(GL_TEXTURE_2D);
			glColor3f(0.5f, 0.5f, 0.5f);
			glBindTexture(GL_TEXTURE_2D, _bgID);
			glBegin(GL_QUADS);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, -3.0f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-1.0f, -1.0f, -3.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(1.0f, -1.0f, -3.0f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(1.0f, 1.0f, -3.0f);
			glEnd();
		glDisable(GL_TEXTURE_2D);
		}

		std::stringstream sPowerup;
		sPowerup << "Powerups : " << _powerupCount;
		Text.RenderText(sPowerup.str(), 0.0f, -0.8f, 1.0f, 1.0f, 1.0f);
		std::stringstream sWaypoint;
		sWaypoint << "Waypoints : " << _waypointCount << "	Scenery : " << _sceneryCount;
		Text.RenderText(sWaypoint.str(), 0.0f, -0.9f, 1.0f, 1.0f, 1.0f);

		glPushMatrix();
			DisplayLoop();
		glPopMatrix();

	glPopMatrix();
	SwapBuffers();
}
void WindowMain::OnIdle()
{
	Redraw();
}
void WindowMain::OnMouseMove(int x, int y)
{
	_mousepos[0] = x;
	_mousepos[1] = y;
}
void WindowMain::OnKeyboard(int key, bool down)
{
	if ((down) && ( key != _lastkey))
	{ 
		_lastkey = key; 
		switch (key)
		{
			case VK_F1:
				AddWaypoint();
				break;
			case VK_F2:
				if (_waypointCount > 0) --_waypointCount;
				break;
			case VK_F3:
				AddStart();
				break;
			case VK_F5: 
				AddPowerup(); 
				break;
			case VK_F6:
				if (_powerupCount > 0) --_powerupCount;
				break;
			case VK_F7: 
				AddScenery(); 
				break;
			case VK_F8:
				if (_sceneryCount > 0) --_sceneryCount;
				break;
			case VK_F9:
				_renderMode = !_renderMode;
				break;
			case VK_F11:
				_imageVisible = !_imageVisible;
				break;
			case VK_F12:
				DumpToFile();
				break;
		}
	}
	else if (!down) _lastkey = -1; 
}

void WindowMain::DisplayLoop()
{
	if (_renderMode)
	{
		if (_waypointCount > 1)
		{
			glBegin(GL_LINES);	
			glColor3f(1.0f, 1.0f, 1.0f);
			for (int i = 1; i < _waypointCount; i++)
			{
				glVertex3f(Waypoints[i-1].x, Waypoints[i-1].y, -0.1f);
				glVertex3f(Waypoints[i].x, Waypoints[i].y, -0.1f);
			}
			glEnd();
		}
		glBegin(GL_POINTS);	
			for (int i = 0; i < _waypointCount; i++)
			{
				glColor3f(1.0f - ((float)i/49.0f), (float)i/49.0f, 0.0f); 
				glVertex3f(Waypoints[i].x, Waypoints[i].y, 0.0f);
			}
		glEnd();
	}
	else
	{
		if (_waypointCount > 1)
		{
			glBegin(GL_LINES);	
			for (int i = 1; i < _waypointCount; i++)
			{
				glColor3f(1.0f - ((float)(i-1)/49.0f), (float)(i-1)/49.0f, 0.0f);
				glVertex3f(Waypoints[i-1].x, Waypoints[i-1].y, -0.1f); 
				glColor3f(1.0f - ((float)i/49.0f), (float)i/49.0f, 0.0f);
				glVertex3f(Waypoints[i].x, Waypoints[i].y, -0.1f);
			}
			glEnd();
		}
	}




	glBegin(GL_POINTS);
		for (int i = 0; i < _powerupCount; i ++)
		{
			glColor3f((float)i/(float)(_powerupCount-1),
					  (float)i/(float)(_powerupCount-1),
					  1.0f - (float)i/(float)(_powerupCount-1));
			glVertex3f(Powerups[i].x, Powerups[i].y, 0.1f);
		}
	glEnd();

	glBegin(GL_POINTS);
	for (int i = 0; i < _sceneryCount; i ++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(Scenery[i].x, Scenery[i].y, 0.1f);
	}
	glEnd();

	glPointSize(10.0f); 
	glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f); 
		glVertex3f(Start.x, Start.y, 0.1f);
	glEnd();


	glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 1.0f, 1.0f);	
		
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);

	glEnd();

}



void WindowMain::CreateLoop()
{	
	for (int i = 0; i < 50; i++)
	{
		float temp = (float(i)/50.0f * 2.0f + 1.0f) * 3.145f; 
		Waypoints[i].x = sin(temp) * 0.8f;
		Waypoints[i].y = cos(temp) * 0.5f;
		Waypoints[i].z = 0.0f; 

		if ((Waypoints[i].x < -0.5) && (Waypoints[i].y < 0.25f) && (Waypoints[i].y > -0.25f)) 
		{
			Waypoints[i].x += (0.25f - std::abs(Waypoints[i].y)) * 1.5f;
		}

		if (Waypoints[i].x > 0.5f)
		{
			Waypoints[i].y *= min(1.0f, (float)(1.5f - Waypoints[i].x));
		}

		if (Waypoints[i].y > 0.4f)
		{
			Waypoints[i].y *= 1.5f - std::abs(Waypoints[i].x);
			if (Waypoints[i].x > -0.01f && Waypoints[i].x < 0.01f) Waypoints[i].y -= 0.05f;
		}
	}
}

void WindowMain::DumpToFile()
{
	std::ofstream outFile;
	outFile.open("Waypoints.ncf1");
	
	outFile << "# Generated by TEX Waypoint Editor" << std::endl;

	outFile << "startpoint = {" << std::endl;
	outFile << "	X = " << Start.x << std::endl 
			<< "	Y = " << Start.z << std::endl 
			<< "	Z = " << -Start.y << std::endl
			<< "}" << std::endl; 

	outFile << "waypoints = {" << std::endl;
	for (int i = 0; i < _waypointCount; i++)
	{
		outFile << "	WP";
		if (i < 9) outFile << 0;
		outFile << i + 1 << " = {" << std::endl;
		outFile << "		X = " << Waypoints[i].x << std::endl
				<< "		Y = " << Waypoints[i].z << std::endl 
				<< "		Z = " << -Waypoints[i].y << std::endl
				<< "	}" << std::endl;
	}
	outFile << "}" << std::endl << std::endl << std::endl;

	
	outFile << "powerups = {" << std::endl;
	for (int i = 0; i < _powerupCount; i++)
	{
		outFile << "	PP";
		if (i < 9) outFile << 0;
		outFile << i + 1 << " = {" << std::endl;
		outFile << "		X = " << Powerups[i].x << std::endl
				<< "		Y = " << Powerups[i].z << std::endl
				<< "		Z = " << -Powerups[i].y << std::endl
				<< "	}" << std::endl;
	}
	outFile << "}" << std::endl << std::endl << std::endl;

	outFile << "scenery = {" << std::endl;
	//outFile << "count = " << _sceneryCount << std::endl;	
	for (int i = 0; i < _sceneryCount; i++)
	{
		outFile << "	S";
		if (i < 9) outFile << 0;
		outFile << i + 1 << " = {" << std::endl
				<< "		X = " << Scenery[i].x << std::endl
				<< "		Y = " << Scenery[i].z << std::endl
				<< "		Z = " << -Scenery[i].y << std::endl
				<< "	}" << std::endl;
	}
	outFile << "}" << std::endl << std::endl << std::endl;



	outFile.close();
}

void WindowMain::DumpToFile(std::string FileName)
{

}

void WindowMain::AddPowerup()
{
	if (_powerupCount < 25)
	{
		Vector3f Pos; 
		Pos.z = 0.0f;
		Pos.x = ((float)_mousepos[0] / (float)_width) * 2.0f - 1.0f;
		Pos.y = ((float)_mousepos[1] / (float)_height) * 2.0f - 1.0f;

		unsigned char* _row;
		_row = _background.GetRowData((int)((float)_mousepos[1] / (float)_height));

		Pos.z = ((float)_row[(int)((float)_mousepos[0] / (float)_width)]/255.0f) * 2.0f - 1.0f;
		Pos.z += 0.1f;

		Powerups[_powerupCount] = Pos; 
		++_powerupCount;
	}
}

void WindowMain::AddWaypoint()
{
	if (_waypointCount < 50)
	{
		Vector3f Pos; 
		Pos.z = 0.0f;
		Pos.x = ((float)_mousepos[0] / (float)_width) * 2.0f - 1.0f;
		Pos.y = ((float)_mousepos[1] / (float)_height) * 2.0f - 1.0f;
		
		unsigned char* _row;
		float j = (float)_mousepos[1] /_height * (float)_background.Height();
		float i = 1.0f - (float)_mousepos[0] /_width * (float)_background.Width();
		_row = _background.GetRowData((int)j);
		Pos.z = (float)_row[(int)(i) * _background.GetPixelSize()]/255.0f + 0.1f;
		Pos.z = Pos.z * 2.0f - 1.0f; 

		Waypoints[_waypointCount] = Pos; 
		++_waypointCount;
	}
}

void WindowMain::AddScenery()
{
	if (_sceneryCount < 40)
	{
		Vector3f Pos; 
		Pos.z = 0.0f;
		Pos.x = ((float)_mousepos[0] / (float)_width) * 2.0f - 1.0f;
		Pos.y = ((float)_mousepos[1] / (float)_height) * 2.0f - 1.0f;
		
		unsigned char* _row;
		float j = (float)_mousepos[1] /_height * (float)_background.Height();
		float i = 1.0f - (float)_mousepos[0] /_width * (float)_background.Width();
		_row = _background.GetRowData((int)j);
		Pos.z = (float)_row[(int)(i) * _background.GetPixelSize()]/255.0f + 0.1f;
		Pos.z = Pos.z * 2.0f - 1.0f; 

		Scenery[_sceneryCount] = Pos; 
		++_sceneryCount;
	}
}

void WindowMain::AddStart()
{
		Vector3f Pos; 
		Pos.z = 0.0f;
		Pos.x = ((float)_mousepos[0] / (float)_width) * 2.0f - 1.0f;
		Pos.y = ((float)_mousepos[1] / (float)_height) * 2.0f - 1.0f;	

		unsigned char* _row;
		float j = (float)_mousepos[1] /_height * (float)_background.Height();
		float i = 1.0f - (float)_mousepos[0] /_width * (float)_background.Width();
		_row = _background.GetRowData((int)j);
		Pos.z = (float)_row[(int)(i) * _background.GetPixelSize()]/255.0f + 0.1f;
		Pos.z = Pos.z * 2.0f - 1.0f; 

		Start = Pos; 
}

void WindowMain::OnDestroy()
{
	_background.Free();
}
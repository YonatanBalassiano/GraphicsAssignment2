#include "InputManager.h"
// #include "../DisplayGLFW/display.h"
#include "game.h"
#include "../res/includes/glm/glm.hpp"
#include "../RayCasting-Assets/Reader/ConfigReader.h"
#include "../RayCasting-Assets/Components/Image.h"
#include <iostream>

int main(int argc,char *argv[])
{
	const int DISPLAY_WIDTH = 800;
	const int DISPLAY_HEIGHT = 800;
	const float CAMERA_ANGLE = 0.0f;
	const float NEAR = 1.0f;
	const float FAR = 100.0f;

	Game *scn = new Game(CAMERA_ANGLE,(float)DISPLAY_WIDTH/DISPLAY_HEIGHT,NEAR,FAR);
	
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	
	Init(display);
	
	scn->Init();

	display.SetScene(scn);

	std::string fileName = "C:/Users/galed/OneDrive/Desktop/GraphicsAssignment2/SceneConfigFiles/scene1.txt";

	// todo: implement differently
	ConfigReader sceneConfigure = ConfigReader();
    sceneConfigure.readConfigFile(fileName, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    Image img = sceneConfigure.RayCasting();
    scn->AddTexture(img.width, img.height, img.data);
	// 
	
	// !!! todo: here sceneConfigure is correct and than in thw next line it is deleted. WHY ?? 
	while(!display.CloseWindow())
	{
		scn->Draw(1,0,scn->BACK,true,false);
		scn->Motion();
		display.SwapBuffers();
		display.PollEvents();
	}
	delete scn;
	return 0;
}

#include "InputManager.h"
// #include "../DisplayGLFW/display.h"
#include "game.h"
#include "../res/includes/glm/glm.hpp"
#include "../RayCasting-Assets/Components/Image.h"
#include "../RayCasting-Assets/ImageConstructor/ImageConstructor.h"
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

	std::string fileName = "/Users/yonatanbal/Dev/BGU/graphics/GraphicsAssignment2/SceneConfigFiles/scene4.txt";

	ImageConstructor imgConstructor = ImageConstructor();
	Image img = imgConstructor.constructImage(fileName, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	std::cout << "Image constructed" << std::endl;

	 scn->AddTexture(img.width, img.height, img.data);

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

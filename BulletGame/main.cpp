#include<irrlicht.h>
#include<irrbullet.h>
#include"MyEventReceiver.h"
#include"Globals.h"
#include"Hero.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace gui;
using namespace scene;
using namespace io;
using namespace std;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrBullet.lib")

#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletSoftBody.lib")
#pragma comment(lib, "LinearMath.lib")
#pragma comment(lib, "BulletMultiThreaded.lib")
#pragma comment(lib, "BulletCollision.lib")
#endif

extern int width = 1366, height = 768;
extern IrrlichtDevice* device = createDevice(EDT_DIRECT3D9, dimension2d<u32>(width, height), 32, true, false, false, 0);
extern ISceneManager* smgr = device->getSceneManager();
extern IVideoDriver* driver = device->getVideoDriver();

int main()
{
	int speed = 0, textura=9;
	IGUIEnvironment *gui = device->getGUIEnvironment();
	vector3df position_camera(50, 15, 225), lookat_camera, scale_start(5,5,5);

	SAppContext context_game;
	context_game.device = device;
	context_game.gui = gui;
	MyEventReceiver receiver(context_game);
	device->setEventReceiver(&receiver);

	irrBulletWorld *world = createIrrBulletWorld(device, true, true);
	world->setGravity(vector3df(0, -10, 0));

	IMeshSceneNode *ground = device->getSceneManager()->addCubeSceneNode(1.0);
	ground->setScale(vector3df(1000, 3, 1000));
	ground->setPosition(vector3df(20, 0, 10));
	ground->setMaterialFlag(EMF_LIGHTING, false);
	ground->setMaterialTexture(0, device->getVideoDriver()->getTexture("../models/rockwall.jpg"));
	ICollisionShape *shapeground = new IBoxShape(ground, 0, false);
	IRigidBody *bodyground = world->addRigidBody(shapeground);

	for (u32 j = 0; j < 3; j++)
	{
		for (u32 i = 0; i < 5; i++)
		{
			ISceneNode *Node = device->getSceneManager()->addCubeSceneNode(1.0f);
			Node->setScale(vector3df(7, 7, 7));
			Node->setPosition(vector3df(7 * j, 7 * i + 7, 0));
			Node->setMaterialFlag(EMF_LIGHTING, false);
			Node->setMaterialTexture(0, device->getVideoDriver()->getTexture("../models/crate.jpg"));
			ICollisionShape *shape = new IBoxShape(Node, 3, false);
			IRigidBody *body = world->addRigidBody(shape);
		}
	}

	ICameraSceneNode* camera;
	u32 then = device->getTimer()->getTime();

	/*vector3df pos(camera->getPosition().X, camera->getPosition().Y, camera->getPosition().Z);
	ISceneNode *Node = smgr->addCubeSceneNode();
	Node->setScale(vector3df(0.2, 0.2, 0.2));
	Node->setMaterialFlag(EMF_LIGHTING, false);
	Node->setMaterialTexture(0, driver->getTexture("../rockwall.jpg"));
	ICollisionShape *shape = new IBoxShape(Node, 1, true);
	IRigidBody *body = world->addRigidBody(shape);
	body->setDamping(0.2, 0.2);
	body->setFriction(0.4f);
	body->setGravity(vector3df(0, -10, 0));*/

	Hero Hero;
	Hero.Create(textura, scale_start);
	Hero.Show();
	ICollisionShape *shape;
	IRigidBody *body;
	/*body->setDamping(0.2, 0.2);
	body->setFriction(0.4f);
	body->setGravity(vector3df(0, -10, 0));*/

	while (device->run())
	{
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f;
		then = now;
		camera = smgr->addCameraSceneNode(0, position_camera, lookat_camera);
		camera->setFarValue(27000);

		
		if (receiver.IsKeyDown(irr::KEY_KEY_W))
		{
			position_camera.Z -= 1;
			lookat_camera.Z -= 1;
			Hero.Move(0, 0, -1, 9, vector3df(5,5,5));
			shape = new IBoxShape(Hero.node, 1, true);
			body = world->addRigidBody(shape);
			body->setDamping(0.2, 0.2);
			body->setFriction(1.0f);
			body->setGravity(vector3df(0, -100, 0));
		}

		if (receiver.IsKeyDown(irr::KEY_KEY_D))
		{
			position_camera.X -= 1;
			lookat_camera.X -= 1;
			Hero.Move(-1, 0, 0, 9, vector3df(5, 5, 5));
			/*shape = new IBoxShape(Hero.node, 1, true);
			body = world->addRigidBody(shape);
			body->setDamping(0.2, 0.2);
			body->setFriction(0.4f);
			body->setGravity(vector3df(0, -100, 0));*/
		}

		if (receiver.IsKeyDown(irr::KEY_KEY_S))
		{
			position_camera.Z -= 1;
			lookat_camera.Z -= 1;
			/*matrix4 mat;
			mat.setRotationDegrees(Hero.hero_position);
			vector3df forwardDir(vector3df(mat[8], mat[9], mat[10]) * 120);
			body->setLinearVelocity(forwardDir);*/
			//body->getAttributes()->addBool("collide", true);
		}

		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		world->stepSimulation(frameDeltaTime, 120);
		world->debugDrawWorld(true);
		world->debugDrawProperties(true);
		smgr->drawAll();
		gui->drawAll();
		driver->endScene();
	}
}
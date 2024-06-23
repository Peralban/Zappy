/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tester
*/

#include <irrlicht/irrlicht.h>
#include <iostream>

using namespace irr;

// Event receiver to handle inputs
class MyEventReceiver : public IEventReceiver {
public:
    MyEventReceiver(scene::ISceneNode* node, scene::ICameraSceneNode* camera)
        : Model(node), Camera(camera), ZoomSpeed(10.0f), RotateSpeed(1.0f), Rotate(false) {}

    virtual bool OnEvent(const SEvent& event) {
        if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown) {
            switch (event.KeyInput.Key) {
                case KEY_ESCAPE:
                    // Close the window
                    if (Camera) {
                        Camera->drop();
                    }
                    if (Model) {
                        Model->remove();
                    }
                    exit(0);
                    return true;
                default:
                    break;
            }
        }

        if (event.EventType == EET_MOUSE_INPUT_EVENT) {
            switch (event.MouseInput.Event) {
                case EMIE_MOUSE_WHEEL:
                    Camera->setPosition(Camera->getPosition() +
                        (Camera->getTarget() - Camera->getPosition()).normalize() * (event.MouseInput.Wheel * ZoomSpeed));
                    return true;
                case EMIE_LMOUSE_PRESSED_DOWN:
                    Rotate = true;
                    LastMousePos = core::position2di(event.MouseInput.X, event.MouseInput.Y);
                    return true;
                case EMIE_LMOUSE_LEFT_UP:
                    Rotate = false;
                    return true;
                case EMIE_MOUSE_MOVED:
                    if (Rotate) {
                        core::position2di currentMousePos(event.MouseInput.X, event.MouseInput.Y);
                        core::position2di diff = currentMousePos - LastMousePos;

                        core::vector3df rotation = Model->getRotation();
                        rotation.Y += diff.X * RotateSpeed;
                        rotation.X += diff.Y * RotateSpeed;
                        Model->setRotation(rotation);

                        LastMousePos = currentMousePos;
                    }
                    return true;
                default:
                    break;
            }
        }

        return false;
    }

private:
    scene::ISceneNode* Model;
    scene::ICameraSceneNode* Camera;
    core::position2di LastMousePos;
    f32 ZoomSpeed;
    f32 RotateSpeed;
    bool Rotate;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path to .obj file>" << std::endl;
        return 1;
    }

    // Create device
    IrrlichtDevice* device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600), 16,
                                          false, false, false, 0);
    if (!device) {
        return 1;
    }

    device->setWindowCaption(L"3D Model Viewer - Irrlicht Engine");

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();

    // Load the .obj file
    const char* objPath = argv[1];
    scene::IAnimatedMesh* mesh = smgr->getMesh(objPath);
    if (!mesh) {
        std::cerr << "Error loading mesh: " << objPath << std::endl;
        device->drop();
        return 1;
    }

    scene::ISceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setPosition(core::vector3df(0, 0, 0));
         node->setScale(core::vector3df(10, 10, 10));
    }


    // Add a camera to view the model
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 10.0f, 0.1f);


    // Set up event receiver
    MyEventReceiver receiver(node, camera);
    device->setEventReceiver(&receiver);

    // Main loop
    while (device->run()) {
        driver->beginScene(true, true, video::SColor(255, 100, 101, 140));
        smgr->drawAll();
        driver->endScene();
    }

    device->drop();

    return 0;
}


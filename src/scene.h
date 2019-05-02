//
// scene.h
// Created By TheFatNinja
// 15-04-2019
//

#ifndef GL_ENGINE_SCENE_H
#define GL_ENGINE_SCENE_H

class Scene {

private:
//bacground
//sprites

public:
Scene();
virtual ~Scene();

bool HandleHeyPress(int keycode);
void Update();
void Draw();

};

#endif //GL_ENGINE_SCENE_H
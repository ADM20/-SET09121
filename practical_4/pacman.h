#pragma once
#include "scene.h"
//pacman.h
using namespace std;
using namespace sf;

extern shared_ptr<Scene> gameScene;
extern shared_ptr<Scene> menuScene;
extern shared_ptr<Scene> activeScene;
extern int gameWidth;
extern int gameHeight;

class MenuScene : public Scene {
private:
  Text text;
  Font font;
public:
  MenuScene()=default;
  void update(double dt) override;
  void render() override;
  void load()override;
};

class GameScene : public Scene {
private:
  Text text;
  Clock scoreClock;
  void respawn();

public:
  GameScene() = default;
  void update(double dt) override;
  void render()override;
  void load()override;
};
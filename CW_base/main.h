#include "engine.h"
#include "game.h"

using namespace std;

MenuScene menu;
Level1Scene steeringScene;
Level2Scene pathfindingScene;

int main() {
  Engine::Start(1280, 720, "Steering", &menu);
  return 0;
}
#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
SteeringScene steeringScene;
PathfindingScene pathfindingScene;

int main() {
  Engine::Start(1920, 1080, "Platformer",&menu);
}
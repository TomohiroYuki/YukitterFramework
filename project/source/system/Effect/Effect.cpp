#include "source\system\Effect\Effect.h"
std::list<std::unique_ptr<Effect>> EffectManager::effect_list;
std::shared_ptr<StaticMesh> EffectManager::effect[5];
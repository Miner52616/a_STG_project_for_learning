#pragma once
#include "core/LuaManager.h"
#include "phases/Phase.h"

class Resource;
class YellowPage;
class MidPhase;

class ScriptLoader
{
private:
    LuaManager& lua_;
    Resource* resource_;
    YellowPage* yellowpage_;

private:
    std::unique_ptr<MidPhase> createMidPhase();

public:
    ScriptLoader(LuaManager& lua,Resource* resource,YellowPage* yellowpage);
    std::unique_ptr<Phase> loadPhase(const std::string& path);
};
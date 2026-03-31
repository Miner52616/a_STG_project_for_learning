#include <sol/sol.hpp>

class LuaManager
{
public:
    sol::state lua_;

    LuaManager();
    void loadScript(const std::string& path);
};
#include "core/LuaObject.h"
#include "packages/LuaDependency.h"

LuaFunction::LuaFunction(sol::state& lua,const std::string& path,LuaDependency dependency)
{
    //从路径加载Lua文件
    sol::load_result load_result=lua.load_file(path);
    if (!load_result.valid())
    {
        sol::error err=load_result;
        throw std::runtime_error(err.what());
    }

    //执行Lua文件获得含Lua对象的表的返回值
    sol::protected_function script=load_result;
    sol::protected_function_result script_result=script();
    if (!script_result.valid())
    {
        sol::error err=script_result;
        throw std::runtime_error(err.what());
    }

    //从返回值中得到含Lua对象的表
    sol::table module=script_result.get<sol::table>();

    //获取模块中的new函数，调用new，创建Lua对象（初步约定以new为Lua“类”的构造函数）
    sol::protected_function constructor=module["new"];
    sol::protected_function_result object_result=constructor(dependency);//运行构造函数后返回的Lua对象
    if (!object_result.valid())
    {
        sol::error err=object_result;
        throw std::runtime_error(err.what());
    }

    //保存Lua对象到C++。以后可以通过这个对象自由调用Lua函数！
    instance_ = object_result.get<sol::table>();
}

void LuaFunction::function()
{
    //获取并调用Lua模块中的运行函数（初步约定以luafunction为Lua“类”提供的希望C++使用的Lua运行函数）
    sol::protected_function luafunction=instance_["luafunction"];
    sol::protected_function_result result=luafunction(instance_);
    if (!result.valid())
    {
        sol::error err = result;
        throw std::runtime_error(err.what());
    }
}
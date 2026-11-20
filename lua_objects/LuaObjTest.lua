local LuaObjTest={}
LuaObjTest.__index=LuaObjTest

function LuaObjTest.new(context)
    local self=
    {
        
    }

    setmetatable(self,LuaObjTest)

    return self
end

function LuaObjTest:luafunction()

end

-- 将模块返回给C++
return LuaObjTest
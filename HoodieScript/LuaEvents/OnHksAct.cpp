#include "pch.h"
#include  "OnHksAct.h"
#include "GameExtensions/GameExtensionsManager.h"
#include <LuaObjects/LuaArgs.h>
namespace hoodie_script {
    int OnHksAct::SubscribeToEventOnHksAct(sol::function function, int actId)
    {
        GameExtensionManager::tryRegisterHksActExtension(actId,
        [function](hksActExpansionLambdaArgs) {

            //logging::write_line(std::format("Doing Acttt = {0}, arg2 = {1}", extensionId, luaArgs.GetUint64(2)));
            sol::protected_function fun = function;
            sol::protected_function_result result = fun(senderCharacter, extensionId, luaArgs);
            if (!result.valid())
            {
                sol::error error = result;
                logging::write_line(error.what());
                logging::write_line(std::format("An error occured while calling HksAct Lua Event : Function Pointer = {0}", function.pointer()));
            }
        });

        return 0;
    }
}

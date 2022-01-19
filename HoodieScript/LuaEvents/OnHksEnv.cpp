#include "pch.h"
#include "OnHksEnv.h"
#include "GameExtensions/GameExtensionsManager.h"
#include <LuaObjects/LuaArgs.h>
namespace hoodie_script {
    int OnHksEnv::SubscribeToEventOnHksEnv(int envId, sol::function function)
    {
        GameExtensionManager::tryRegisterHksEnvExtension(envId,
        [function](hksEnvExpansionLambdaArgs) {

            //logging::write_line(std::format("Doing Acttt = {0}, arg2 = {1}", extensionId, luaArgs.GetUint64(2)));
            uint64_t resultStorage = 0;
            sol::protected_function fun = function;
            sol::protected_function_result result = fun(senderCharacter, extensionId, luaArgs);
            if (result.valid())
            {
                resultStorage = result;
                return resultStorage;
            }
            else
            {
                sol::error error = result;
                logging::write_line(error.what());
                logging::write_line(std::format("An error occured while calling HksEnv Lua Event : Function Pointer = {0}", function.pointer()));
            }
            return resultStorage;
        });

        return 0;
    }
}

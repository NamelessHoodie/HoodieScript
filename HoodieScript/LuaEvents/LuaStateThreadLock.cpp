#include "pch.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {
	std::mutex LuaStateThreadLock::luaThreadLock;
	void LuaStateThreadLock::Lock()
	{

		while (!luaThreadLock.try_lock())
		{

		}
	}
	void LuaStateThreadLock::Unlock()
	{
		luaThreadLock.unlock();
	}
	std::lock_guard<std::mutex> LuaStateThreadLock::GetLockObject()
	{
		return std::lock_guard<std::mutex>(luaThreadLock);
	}
}
#include "pch.h"
#include "LuaStateThreadLock.h"

namespace hoodie_script {
	std::mutex LuaStateThreadLock::luaThreadLock;
	void LuaStateThreadLock::Lock()
	{
		luaThreadLock.lock();
	}
	void LuaStateThreadLock::Unlock()
	{
		luaThreadLock.unlock();
	}
}
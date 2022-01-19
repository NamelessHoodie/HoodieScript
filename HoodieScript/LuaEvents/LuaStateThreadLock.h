#pragma once
#include <mutex>

namespace hoodie_script {
	class LuaStateThreadLock
	{
	public:
		static std::lock_guard<std::mutex> GetLockObject();
		static std::mutex luaThreadLock;
	private:
		static void Lock();
		static void Unlock();
	};
}
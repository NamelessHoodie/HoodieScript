#pragma once
#include <mutex>

namespace hoodie_script {
	class LuaStateThreadLock
	{
	public:
		static void Lock();
		static void Unlock();
	private:
		static std::mutex luaThreadLock;
	};
}
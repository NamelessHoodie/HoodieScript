#pragma once

namespace hoodie_script
{
	class LuaEventQueue
	{
	public:
		static void Push(std::function<sol::object()> function);
		static void Pop();
	private:

	};
}
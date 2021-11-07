#include "pch.h"
#include "hksActSetter_hook.h"

namespace hoodie_script {
	hksActSetter* hksActSetter::_instance = nullptr;

	hksActSetter::hksActSetter() : jump_hook(0x14098C510, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	void hksActSetter::on_invoke(uintptr_t* chrInsPtr, int32_t actId, uintptr_t luaStatePtr)
	{
		//0x14112df50
		uint64_t meme;

		ChrIns characterInstance(*chrInsPtr);
		switch (actId)
		{
		case 420:
			meme = call(0x140d9cca0, luaStatePtr, 2, 0x5a); //get second argument from lua function
			if (meme != 0x5a)
			{
				std::wcout << characterInstance.getCharacterString() << "-HPAct = " << meme << std::endl;
				characterInstance.SetHP(meme);
			}
			break;
		default:
			uint64_t(*originalFunction)(uintptr_t * chrInsPtr, int32_t actId, uintptr_t luaStatePtr);
			*(uintptr_t*)&originalFunction = _instance->get_original();
			originalFunction(chrInsPtr, actId, luaStatePtr);
			break;
		}
	}
}

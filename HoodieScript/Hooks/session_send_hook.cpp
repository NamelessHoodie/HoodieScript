/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#include "pch.h"
#include "session_send_hook.h"

namespace hoodie_script
{
	session_send_hook* session_send_hook::_instance = nullptr;

	session_send_hook::session_send_hook() : jump_hook(0x1407875D0, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	uint32_t session_send_hook::on_invoke(uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength)
	{
		return call(_instance->get_original(), networkSession, networkHandle, id, buffer, maxLength);
	}
}

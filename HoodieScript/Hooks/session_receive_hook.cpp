/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#include "pch.h"
#include "session_receive_hook.h"
#include "script_runtime.h"

namespace hoodie_script
{
	session_receive_hook* session_receive_hook::_instance = nullptr;

	session_receive_hook::session_receive_hook() : jump_hook(0x140787140, (uintptr_t)on_invoke)
	{
		_instance = this;
	}

	uint32_t session_receive_hook::on_invoke(uintptr_t networkSession, uintptr_t* networkHandle, int32_t id, char* buffer, uint32_t maxLength)
	{
		uint32_t receiveLength = call(_instance->get_original(), networkSession, networkHandle, id, buffer, maxLength);
		if (receiveLength == 0) return receiveLength;
		receiveLength = script_runtime::on_network_session_receive(networkSession, networkHandle, id, buffer, maxLength, receiveLength);
		return receiveLength;
	}
}
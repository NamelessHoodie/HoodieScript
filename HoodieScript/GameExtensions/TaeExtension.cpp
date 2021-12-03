#include "pch.h"
#include "TaeExtension.h"
namespace hoodie_script
{
	TaeExtension::TaeExtension(std::function<void(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)> extensionFunction)
	{
		taeExtensionFunction = extensionFunction;
	}

	void TaeExtension::CallExtension(ChrIns& senderCharacter, TaeEvent* eventData, int32_t extensionId)
	{
		taeExtensionFunction(senderCharacter, eventData, extensionId);
	}
}
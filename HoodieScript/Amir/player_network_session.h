/*
	* DS3RuntimeScripting
	* Contributers: Amir
	* Further notes on how to use this class:
*/

#pragma once
#include "memory_util.h"
#include "game_packet.h"
#include "Hooks/session_send_hook.h"

namespace hoodie_script {

class PlayerNetworkSession
{
public:
	PlayerNetworkSession(uintptr_t address);

	void packetSend(uintptr_t* networkHandle, int32_t packetId, char* packetBuffer, uint32_t packetSize);

	void packetSend(uintptr_t* networkHandle, packet::Packet* packet);

	void sessionPacketSend(int32_t packetId, char* packetBuffer, uint32_t packetSize);

	void sessionPacketSend(packet::Packet* packet);

	static void queueEquipmentPacket();

	static uintptr_t getInstance();

	static bool hasInstance();
private:
	uintptr_t address;
};

}
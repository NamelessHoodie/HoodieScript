#pragma once

#include "pch.h"
#include "player_network_session.h"
#include "databaseaddress.h"
#include "ds3runtime.h"

namespace hoodie_script {

PlayerNetworkSession::PlayerNetworkSession(uintptr_t address)
{
	this->address = address;
}

uintptr_t PlayerNetworkSession::getInstance()
{
	return *accessMultilevelPointer<uintptr_t>(DataBaseAddress::PlayerNetworkSession);
}

bool PlayerNetworkSession::hasInstance()
{
	return accessMultilevelPointer<uintptr_t>(DataBaseAddress::PlayerNetworkSession) != nullptr;
}

void PlayerNetworkSession::packetSend(uintptr_t* networkHandle, int32_t packetId, char* packetBuffer, uint32_t packetSize)
{
	auto hook = session_send_hook::_instance;
	void(*DebugPacketSend)(...);
	*(uintptr_t*)&DebugPacketSend = hook != nullptr ? hook->get_original() : 0x1407875D0;
	DebugPacketSend(address, networkHandle, packetId, packetBuffer, packetSize);
}

void PlayerNetworkSession::packetSend(uintptr_t* networkHandle, packet::Packet* packet) 
{
	packetSend(networkHandle, packet->getId(), &packet->getDataCopy()[0], packet->getLength());
}

void PlayerNetworkSession::sessionPacketSend(int32_t packetId, char* packetBuffer, const uint32_t packetSize)
{
	void(*SessionPacketSend)(...);
	*(uintptr_t*)&SessionPacketSend = 0x140787870;
	SessionPacketSend(address, packetId, packetBuffer, packetSize);
}

void PlayerNetworkSession::sessionPacketSend(packet::Packet* packet)
{
	sessionPacketSend(packet->getId(), &packet->getDataCopy()[0], packet->getLength());
}

void PlayerNetworkSession::queueEquipmentPacket()
{
	void(*function)();
	*(uintptr_t*)&function = 0x14077bbd0;
	function();
}

};
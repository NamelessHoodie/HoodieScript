#pragma once

#include "pch.h"
#include "Bullet_Spawn.h"

namespace hoodie_script {
    void bullet_spawn_request::set_owner(int32_t owner) {
        _owner = owner;
    }

    int32_t bullet_spawn_request::get_owner() {
        return _owner;
    }

    void bullet_spawn_request::set_bullet_param_id(bullet_type bulletType) {
        _bulletParamId = (int32_t)bulletType;
    }

    bullet_type bullet_spawn_request::get_bullet_param_id() {
        return (bullet_type)_bulletParamId;
    }

    void bullet_spawn_request::set_network_flag(int32_t networkFlag) {
        _networkFlag = networkFlag;
    }

    int32_t bullet_spawn_request::get_network_flag() {
        return _networkFlag;
    }

    void bullet_spawn_request::set_turret_flag(int32_t turretFlag) {
        _turretFlag = turretFlag;
    }

    int32_t bullet_spawn_request::get_turret_flag() {
        return _turretFlag;
    }

    void bullet_spawn_request::set_homing_flag(int32_t homingFlag) {
        _homingFlag = homingFlag;
    }

    int32_t bullet_spawn_request::get_homing_flag() {
        return _homingFlag;
    }

    void bullet_spawn_request::set_coordinates(std::vector<float> coordinates) {
        _coordinates = coordinates;
    }

    std::vector<float> bullet_spawn_request::get_coordinates() {
        return _coordinates;
    }

    void bullet_spawn_request::set_direction(std::vector<float> direction) {
        _direction = direction;
    }

    std::vector<float> bullet_spawn_request::get_direction() {
        return _direction;
    }

    void bullet_facade::spawn(bullet_spawn_request* request) {
        unsigned char data[0x700] = {};
        *(int32_t*)(data + 0x30) = request->get_owner();
        *(int32_t*)(data + 0x40) = (int32_t)request->get_bullet_param_id();
        *(int32_t*)(data + 0x48) = request->get_turret_flag();
        *(int32_t*)(data + 0x4C) = request->get_homing_flag();
        *(int32_t*)(data + 0x6C) = request->get_network_flag();
        const auto coordinates = request->get_coordinates();
        const auto direction = request->get_direction();

        for (uintptr_t i = 0; i < 3; i++) {
            *(float*)(data + 0x7C + i * 0x10) = coordinates[i];
            *(float*)(data + 0x78 + i * 0x10) = direction[i];
        }

        void(*SprjBulletManSpawn)(...);
        *(uintptr_t*)&SprjBulletManSpawn = 0x140978500;
        SprjBulletManSpawn(*(uintptr_t*)0x144772D78, data, data + 0x30);
    }
}
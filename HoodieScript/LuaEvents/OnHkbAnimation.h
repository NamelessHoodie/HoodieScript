#pragma once
#include "GameObjects/player_ins.h"

namespace hoodie_script {
    class MyClass
    {
    public:
        float value;
        MyClass(float valueFun);
        float GetValue();
    private:
    };

	class OnHkbAnimation {
		public:
			static int SubscribeToEventOnHkbAnimation(lua_State* L);
			static int DoOnHkbAnimation(lua_State* L, PlayerIns hkbCharacter, int animationId);
		private:
			static int OnHkbAnimationHandlers[1024];
			static int OnHkbAnimationEventSubscribersCount;
	};

}

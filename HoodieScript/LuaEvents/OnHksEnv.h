#pragma once

namespace hoodie_script {
	class OnHksEnv {
	public:
		static int SubscribeToEventOnHksEnv(sol::function function, int envId);
	private:
	};

}
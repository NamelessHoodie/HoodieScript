#pragma once

namespace hoodie_script {
	class OnHksEnv {
	public:
		static int SubscribeToEventOnHksEnv(int envId, sol::function function);
	private:
	};

}
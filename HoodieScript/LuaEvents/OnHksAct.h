#pragma once

namespace hoodie_script {
	class OnHksAct {
	public:
		static int SubscribeToEventOnHksAct(int actId, sol::function function);
	private:
	};

}

#include "pch.h"
#include "goods_use_hook.h"

namespace hoodie_script
{
	goods_use_hook *goods_use_hook::_instance = nullptr;

	goods_use_hook::goods_use_hook() : jump_hook(0x1408b0950, (uintptr_t) on_invoke)
	{
		_instance = this;
	}

	uintptr_t goods_use_hook::on_invoke(uintptr_t self, int goodsId)
	{
		script_runtime::on_goods_use(goodsId);
		uintptr_t (*originalFunction)(uintptr_t self, int id);
		*(uintptr_t*)&originalFunction = _instance->get_original();
		return originalFunction(self, goodsId);
	}
}
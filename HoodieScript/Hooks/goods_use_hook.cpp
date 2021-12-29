#include "pch.h"
#include "goods_use_hook.h"
#include "script_runtime.h"

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
		return call(_instance->get_original(), self, goodsId);
	}
}
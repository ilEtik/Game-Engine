#pragma once

#include "Engine/Core.h"

namespace GameEngine
{
	class GAMEENGINE_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return _instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return _instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePos() { return _instance->GetMousePosImpl(); }
		
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;

	private:
		static Input* _instance;
	};
}

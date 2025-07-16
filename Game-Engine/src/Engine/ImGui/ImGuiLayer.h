#pragma once

#include "Engine/Layer.h"

namespace GameEngine
{
	class GAMEENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		float _time;
	};
}

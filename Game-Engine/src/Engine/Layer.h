#pragma once

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace GameEngine
{
	class GAMEENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnImGuiRender() { }
		virtual void OnEvent(Event& event) { }

		inline const std::string& GetName() const { return _debugName; }

	protected:
		std::string _debugName;
	};
}

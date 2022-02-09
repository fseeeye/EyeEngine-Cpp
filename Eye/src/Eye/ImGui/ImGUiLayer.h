#pragma once

#include "Eye/Core.h"
#include "Eye/Layer.h"
#include "Eye/Events/KeyEvent.h"
#include "Eye/Events/MouseEvent.h"
#include "Eye/Events/ApplicationEvent.h"

namespace Eye {

	class EYE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void BeginImGuiRender();
		void EndImGuiRender();
	private:
		float m_Time = 0.0f;
	};

}
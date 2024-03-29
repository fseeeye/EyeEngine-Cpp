﻿#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Eye {

	// A wrapper of layers thing
	class EYE_API LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		// tips: overlay always be after layer.
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}

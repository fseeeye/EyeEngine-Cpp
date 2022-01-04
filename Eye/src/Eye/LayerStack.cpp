#include "eyepch.h"

#include "LayerStack.h"

namespace Eye {

	LayerStack::LayerStack()
	{
		m_LayerInsertPos = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsertPos = m_Layers.emplace(m_LayerInsertPos, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	// tip: Pop Layer / Overlay won't delete the layer
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			--m_LayerInsertPos;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}
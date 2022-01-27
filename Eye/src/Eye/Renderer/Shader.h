#pragma once

#include <string>

namespace Eye {

	// TODO: abstract Rendering API, for now, it's just OpenGL
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};

}
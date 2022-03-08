#pragma once

#include <string>

namespace Eye {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		//virtual void UploadVSRendererUniformBuffer(..);

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}

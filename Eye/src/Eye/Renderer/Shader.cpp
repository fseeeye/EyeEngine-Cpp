#include "eyepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Eye {

	StrongRef<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:   EYE_CORE_ASSERT(false, "`RendererAPI::None` is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
			default:                       EYE_CORE_ASSERT(false, "Unknow RendererAPI!"); return nullptr;
		}
	}

	StrongRef<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:   EYE_CORE_ASSERT(false, "`RendererAPI::None` is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		default:                       EYE_CORE_ASSERT(false, "Unknow RendererAPI!"); return nullptr;
		}
	}

	void ShaderLibrary::Add(const std::string& name, const StrongRef<Shader>& shader)
	{
		EYE_CORE_ASSERT(!Exists(name), "Shader name already exists!");

		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const StrongRef<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Eye::StrongRef<Eye::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);

		return shader;
	}

	Eye::StrongRef<Eye::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);

		return shader;
	}

	Eye::StrongRef<Eye::Shader> ShaderLibrary::Get(const std::string& name)
	{
		EYE_CORE_ASSERT(Exists(name), "Shader not found!");

		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}

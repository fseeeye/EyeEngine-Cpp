#pragma once

#include <string>
#include <unordered_map>

namespace Eye {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() = 0;

		//virtual void UploadVSRendererUniformBuffer(..);

		static StrongRef<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static StrongRef<Shader> Create(const std::string& filepath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const StrongRef<Shader>& shader);
		void Add(const StrongRef<Shader>& shader);

		StrongRef<Shader> Load(const std::string& filepath);
		StrongRef<Shader> Load(const std::string& name, const std::string& filepath);

		StrongRef<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, StrongRef<Shader>> m_Shaders;
	};

}

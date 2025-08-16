#include "Shader.h"

#include "RenderAPI.h"

#include "platform/OpenGL/OpenGLShader.h"

namespace Engine {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None: EG_CORE_ASSERT(false, "Cannot have RenderAPI::None");
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
		}

		EG_CORE_ASSERT(false, "Unknown renderAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None: EG_CORE_ASSERT(false, "Cannot have RenderAPI::None");
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		EG_CORE_ASSERT(false, "Unknown renderAPI");
		return nullptr;
	}

	void ShaderLibary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		EG_CORE_ASSERT(!Exists(name), "Shader already exists.");
		m_Shaders[name] = shader;
	}

	void ShaderLibary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibary::Load(const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		if (!shader->compiled)
			shader = Shader::Create("error", R"(
			#version 450 core
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			})",
				R"(
			#version 450 core
			out vec4 FragColor;

			void main()
			{
				FragColor = vec4(1.f, 0.f, 1.f, 1.f);
			})");

		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		if (!shader->compiled)
			shader = Shader::Create("error", R"(
			#version 450 core
			layout(location = 0) in vec4 a_Position;

			void main()
			{
				gl_Position = a_Position;
			})",
			R"(
			#version 450 core
			out vec4 FragColor;

			void main()
			{
				FragColor = vec4(1.f, 0.f, 1.f, 1.f);
			})");
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibary::Get(const std::string& name)
	{
		EG_CORE_ASSERT(Exists(name), "Shader not found.");
		return m_Shaders[name];
	}

}
#ifndef _GL_HELPER_SHADER_OBJECT_HPP_
#define _GL_HELPER_SHADER_OBJECT_HPP_

#include <vector>
#include <memory>

#include <glHelper/glHelper.h>
#include <glbinding/gl/gl.h>

#include <common/Utility.hpp>

namespace glhelper
{
	class GLShader;
	class GLProgram;

	namespace detail
	{
		template<class T>
		using SharedPtr = std::shared_ptr < T > ;

		static void LoadShaderFile(const std::wstring& shader_file, std::string& buffer);

		static std::string ShaderCompileErrorCheck(GLShader& shader);
	}
	
	class GL_HELPER_API GLShader
		: pfc::NonCopyable
	{
	public:
		GLShader();
		GLShader(const gl::GLenum type, const std::wstring& shader_file);
		GLShader(const gl::GLenum type, const std::vector<std::wstring>& shader_files);

		~GLShader();

		operator gl::GLuint() const { return deleted_ ? 0 : handle_; }

		void Generate(const gl::GLenum type, const std::wstring& shader_file);
		void Generate(const gl::GLenum type, const std::vector<std::wstring>& shader_files);

		void Delete();

	private:
		bool	   deleted_;
		gl::GLuint handle_;
	};
}

#endif

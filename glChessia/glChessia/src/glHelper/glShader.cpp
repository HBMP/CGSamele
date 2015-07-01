#include <glHelper/glShaderObject.hpp>

#include <common/Assert.hpp>
#include <common/Marco.h>

namespace glhelper
{
	namespace detail
	{
		void LoadShaderFile(const std::wstring& shader_file, std::string& buffer)
		{
			auto file_handle = 
				::CreateFileW(shader_file.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

			ENSURE_ASSERT(ENSURE(file_handle != INVALID_HANDLE_VALUE), "create file failure");

			ON_SCOPE_EXIT([&]{ ::CloseHandle(file_handle); });

			pfc::SimpleBuffer<char> file_buffer(4096);

			if (!buffer.empty())
			{
				buffer.clear();
			}

			do
			{
				DWORD buffer_readed = 0;

				::ReadFile(file_handle, file_buffer.Buffer(), file_buffer.Size(), &buffer_readed, nullptr);

				if (buffer_readed == 0)
				{
					break;
				}

				buffer += file_buffer.Buffer();
			} while (true);
		}

		std::string ShaderCompileErrorCheck(GLShader& shader)
		{
			using namespace gl;
			using namespace std;

			GLint compiled;
			glGetShaderiv(shader, GL_LINK_STATUS, &compiled);

			if (!compiled)
			{
				string log;

				GLsizei log_size;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);

				log.resize(log_size + 1);
				glGetShaderInfoLog(shader, log_size, &log_size, &log[0]);

				ON_SCOPE_EXIT([&]{ shader.Delete(); });

				return log;
			}
			
			return "success";
		}
	}

	GLShader::GLShader()
		: deleted_(false), handle_(0)
	{ }

	GLShader::GLShader( const gl::GLenum type, const std::wstring& shader_file ) 
		: deleted_(false), handle_(0)
	{
		Generate(type, shader_file);
	}

	GLShader::GLShader( const gl::GLenum type, const std::vector<std::wstring>& shader_files )
		: deleted_(false), handle_(0)
	{
		Generate(type, shader_files);
	}

	GLShader::~GLShader()
	{
		Delete();
	}

	void GLShader::Generate( const gl::GLenum type, const std::wstring& shader_file )
	{
		using namespace gl;
		using namespace std;

		ENSURE_ASSERT(ENSURE(!glIsShader(handle_) && !deleted_)(deleted_)(handle_), "shader has generated");

		handle_ = glCreateShader(type);

		ENSURE_ASSERT(ENSURE(glIsShader(handle_))(handle_), "create shader failure");

		string text_container;

		detail::LoadShaderFile(shader_file, text_container);

		const auto buf = text_container.c_str();

		glShaderSource(handle_, 1, &buf, nullptr);
		glCompileShader(handle_);

		ENSURE_WARNING(ENSURE(detail::ShaderCompileErrorCheck(shader) != "success")(detail::ShaderCompileErrorCheck(shader)), "shader compile fail");
	}

	void GLShader::Generate( const gl::GLenum type, const std::vector<std::wstring>& shader_files )
	{
		using namespace gl;
		using namespace std;

		ENSURE_ASSERT(ENSURE(!glIsShader(handle_) && !deleted_)(deleted_)(handle_), "shader has generated");

		handle_ = glCreateShader(type);

		ENSURE_ASSERT(ENSURE(glIsShader(handle_))(handle_), "create shader failure");

		vector<string> text_containers(shader_files.size());
		vector< const GLchar* const > compatibility_ptr(text_containers.size());

		for (size_t i = 0; i < text_containers.size(); ++i)
		{
			detail::LoadShaderFile(shader_files[i], text_containers[i]);
			compatibility_ptr[i] = text_containers[i].c_str();
		}

		glShaderSource(handle_, compatibility_ptr.size(), &compatibility_ptr[0], nullptr);
		glCompileShader(handle_);

		ENSURE_WARNING(ENSURE(detail::ShaderCompileErrorCheck(shader) != "success")(detail::ShaderCompileErrorCheck(shader)), "shader compile fail");
	}

	void GLShader::Delete()
	{
		gl::glDeleteShader(handle_);

		handle_  = 0;
		deleted_ = true;
	}
}

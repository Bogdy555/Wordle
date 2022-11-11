#ifndef WordleAPI_OpenGL_hpp

#define WordleAPI_OpenGL_hpp



#include "WordleAPI.hpp"



#define GL_DYNAMIC_DRAW 0x88E8

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_LINK_STATUS 0x8B82

#define GL_CLAMP_TO_EDGE 0x812F

#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF



namespace WordleAPI
{

	namespace GL
	{

		extern const ConstHModuleRef hDll;

		extern void* (__stdcall* wglGetProcAddress)(const char*);
		extern int(__stdcall* wglSwapIntervalEXT)(int);
		extern void(__stdcall* glViewport)(int, int, int, int);
		extern void(__stdcall* glClearColor)(float, float, float, float);
		extern void(__stdcall* glClear)(unsigned int);
		extern void(__stdcall* glUseProgram)(unsigned int);
		extern void(__stdcall* glBindVertexArray)(unsigned int);
		extern void(__stdcall* glDrawElements)(unsigned int, int, unsigned int, const void*);
		extern void(__stdcall* glEnable)(unsigned int);
		extern void(__stdcall* glBlendFunc)(unsigned int, unsigned int);
		extern void(__stdcall* glDepthFunc)(unsigned int);
		extern void(__stdcall* glGenBuffers)(int, unsigned int*);
		extern void(__stdcall* glBindBuffer)(unsigned int, unsigned int);
		extern void(__stdcall* glBufferData)(unsigned int, intptr_t, const void*, unsigned int);
		extern void(__stdcall* glGenVertexArrays)(int, unsigned int*);
		extern void(__stdcall* glEnableVertexAttribArray)(unsigned int);
		extern void(__stdcall* glVertexAttribPointer)(unsigned int, int, unsigned int, unsigned char, int, const void*);
		extern unsigned int(__stdcall* glCreateProgram)();
		extern unsigned int(__stdcall* glCreateShader)(unsigned int);
		extern void(__stdcall* glShaderSource)(unsigned int, int, const char* const*, int*);
		extern void(__stdcall* glCompileShader)(unsigned int);
		extern void(__stdcall* glAttachShader)(unsigned int, unsigned int);
		extern void(__stdcall* glLinkProgram)(unsigned int);
		extern void(__stdcall* glValidateProgram)(unsigned int);
		extern int(__stdcall* glGetUniformLocation)(unsigned int, const char*);
		extern void(__stdcall* glUniform1f)(int, float);
		extern void(__stdcall* glUniform2f)(int, float, float);
		extern void(__stdcall* glUniform3f)(int, float, float, float);
		extern void(__stdcall* glUniform4f)(int, float, float, float, float);
		extern void(__stdcall* glUniform1i)(int, int);
		extern void(__stdcall* glUniform2i)(int, int, int);
		extern void(__stdcall* glUniform3i)(int, int, int, int);
		extern void(__stdcall* glUniform4i)(int, int, int, int, int);
		extern void(__stdcall* glUniform1ui)(int, int);
		extern void(__stdcall* glUniformMatrix2fv)(int, int, unsigned char, const float*);
		extern void(__stdcall* glUniformMatrix3fv)(int, int, unsigned char, const float*);
		extern void(__stdcall* glUniformMatrix4fv)(int, int, unsigned char, const float*);
		extern void(__stdcall* glDetachShader)(unsigned int, unsigned int);
		extern void(__stdcall* glDeleteBuffers)(int, unsigned int*);
		extern void(__stdcall* glDeleteVertexArrays)(int, unsigned int*);
		extern void(__stdcall* glDisableVertexAttribArray)(unsigned int);
		extern void(__stdcall* glDeleteProgram)(unsigned int);
		extern void(__stdcall* glDeleteShader)(unsigned int);
		extern void(__stdcall* glGetShaderiv)(unsigned int, unsigned int, int*);
		extern void(__stdcall* glGetShaderInfoLog)(unsigned int, int, int*, char*);
		extern void(__stdcall* glGetProgramiv)(unsigned int, unsigned int, int*);
		extern void(__stdcall* glGetProgramInfoLog)(unsigned int, int, int*, char*);
		extern void(__stdcall* glGenTextures)(int, unsigned int*);
		extern void(__stdcall* glBindTexture)(unsigned int, unsigned int);
		extern void(__stdcall* glTexParameteri)(unsigned int, unsigned int, int);
		extern void(__stdcall* glTexImage2D)(unsigned int, int, int, int, int, int, unsigned int, unsigned int, const void*);
		extern void(__stdcall* glActiveTexture)(unsigned int);
		extern void(__stdcall* glDeleteTextures)(int, unsigned int*);
		extern void(__stdcall* glCullFace)(unsigned int);
		extern void(__stdcall* glFrontFace)(unsigned int);

		bool Load();
		void Unload();

		class Context
		{

		public:

			Context();
			Context(const Context& _Other) = delete;
			Context(Context&& _Other) noexcept;
			~Context();

			bool Create(Window* _WndPtr);
			void Destroy();
			bool Bind();

			const HGLRC GetHandle() const;

			Window* GetWndPtr();
			const Window* GetWndPtr() const;

			operator const HGLRC() const;

			void operator= (const Context& _Other) = delete;
			void operator= (Context&& _Other) noexcept;

			static void Unbind();

		private:

			HGLRC Handle;
			Window* WndPtr;

		};

		struct VertexData
		{
			glm::vec2 Position = glm::vec2(0.0f, 0.0f);
		};

		class VertexBuffer
		{

		public:

			VertexBuffer();
			VertexBuffer(const VertexBuffer& _Other) = delete;
			VertexBuffer(VertexBuffer&& _Other) noexcept;
			~VertexBuffer();

			bool Create(const VertexBufferCPUCash& _VBO_CPUCash);
			void Destroy();
			bool Bind();

			const bool CheckCreated() const;
			const unsigned int GetID() const;

			void operator= (const VertexBuffer& _Other) = delete;
			void operator= (VertexBuffer&& _Other) noexcept;

			static void Unbind();

		private:

			unsigned int ID;

		};

		class IndexBuffer
		{

		public:

			IndexBuffer();
			IndexBuffer(const IndexBuffer& _Other) = delete;
			IndexBuffer(IndexBuffer&& _Other) noexcept;
			~IndexBuffer();

			bool Create(const IndexBufferCPUCash& _IBO_CPUCash);
			void Destroy();
			bool Bind();

			const bool CheckCreated() const;
			const unsigned int GetID() const;

			void operator= (const IndexBuffer& _Other) = delete;
			void operator= (IndexBuffer&& _Other) noexcept;

			static void Unbind();

		private:

			unsigned int ID;

		};

		struct MeshCPUCash
		{
			VertexBufferCPUCash VBO;
			IndexBufferCPUCash IBO;
		};

		struct Mesh
		{
			VertexBuffer VBO;
			IndexBuffer IBO;
		};

		class VertexAttribArray
		{

		public:

			VertexAttribArray();
			VertexAttribArray(const VertexAttribArray& _Other) = delete;
			VertexAttribArray(VertexAttribArray&& _Other) noexcept;
			~VertexAttribArray();

			bool Create();
			void Destroy();
			bool Bind();
			bool EnableAttrib(const unsigned int _AttribID, const int _ElementsCount, const int _ElementsCountTotal, const size_t _Offset);
			bool DisableAttrib(const unsigned int _AttribID);

			const bool CheckCreated() const;
			const unsigned int GetID() const;

			void operator= (const VertexAttribArray& _Other) = delete;
			void operator= (VertexAttribArray&& _Other) noexcept;

			static void Unbind();

		private:

			unsigned int ID;

		};

		class Shader
		{

		public:

			Shader();
			Shader(const Shader& _Other) = delete;
			Shader(Shader&& _Other) noexcept;
			~Shader();

			bool Create(const char* _VS, const char* _FS);
			void Destroy();
			bool Bind();

			const bool CheckCreated() const;
			const unsigned int GetID() const;

			void operator= (const Shader& _Other) = delete;
			void operator= (Shader&& _Other) noexcept;

			static void Unbind();

		private:

			unsigned int ID;

		};

		class Uniform
		{

		public:

			Uniform();
			Uniform(const Uniform& _Other) = delete;
			Uniform(Uniform&& _Other) noexcept;
			~Uniform();

			bool GetLocation(const Shader& _Shader, const char* _Name);
			void ReleaseLocation();

			const bool CheckBind() const;
			const int GetID() const;

			bool Set1f(const float _x);
			bool Set2f(const float _x, const float _y);
			bool Set3f(const float _x, const float _y, const float _z);
			bool Set4f(const float _x, const float _y, const float _z, const float _w);

			bool Set1i(const int _x);
			bool Set2i(const int _x, const int _y);
			bool Set3i(const int _x, const int _y, const int _z);
			bool Set4i(const int _x, const int _y, const int _z, const int _w);

			bool Set1b(const bool _Value);

			bool Set1ui(const unsigned int _Value);

			bool SetMatrix2fv(const float* _Data);
			bool SetMatrix3fv(const float* _Data);
			bool SetMatrix4fv(const float* _Data);

			void operator= (const Uniform& _Other) = delete;
			void operator= (Uniform&& _Other) noexcept;

		private:

			int ID;

		};

		struct TextureData
		{
			unsigned int Width = 0, Height = 0;
			unsigned char* Data = nullptr;
			int WrapSType = GL_REPEAT;
			int WrapTType = GL_REPEAT;
			int MinFilter = GL_NEAREST;
			int MagFilter = GL_NEAREST;
		};

		class Texture2D
		{

		public:

			Texture2D();
			Texture2D(const Texture2D& _Other) = delete;
			Texture2D(Texture2D&& _Other) noexcept;
			~Texture2D();

			bool Create(const TextureData& _TexData);
			void Destroy();
			bool Bind();

			const bool CheckCreated() const;
			const unsigned int GetID() const;

			void operator= (const Texture2D& _Other) = delete;
			void operator= (Texture2D&& _Other) noexcept;

			static void Unbind();

		private:

			unsigned int ID;

		};

		const std::string GetUniformIndexName(const std::string _Name, const size_t _Index);
		bool LoadTexture(TextureData& _TexData, const wchar_t* _FileName);
		bool LoadTextureFromResource(TextureData& _TexData, HINSTANCE _hInstance, size_t _ResName);
		char* LoadShaderSourceFromResource(HINSTANCE _hInstance, size_t _ResName);

	}

}



#endif

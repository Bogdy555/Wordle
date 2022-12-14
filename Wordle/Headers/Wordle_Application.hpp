#ifndef Wordle_Application_hpp

#define Wordle_Application_hpp



#include "Wordle.hpp"



namespace Wordle
{

	class Application : public WordleAPI::Application
	{

	public:

		Application();
		Application(const Application& _Other) = delete;
		Application(Application&& _Other) noexcept = delete;
		~Application();

		WordleAPI::Window& GetWnd();
		const WordleAPI::Window& GetWnd() const;

		Window::UserData& GetWndUserData();
		const Window::UserData& GetWndUserData() const;

		WordleAPI::GL::Mesh& GetQuad();
		const WordleAPI::GL::Mesh& GetQuad() const;
		WordleAPI::GL::VertexAttribArray& GetVAO();
		const WordleAPI::GL::VertexAttribArray& GetVAO() const;
		WordleAPI::GL::Shader& GetTextureShader();
		const WordleAPI::GL::Shader& GetTextureShader() const;
		WordleAPI::GL::Shader& GetColorShader();
		const WordleAPI::GL::Shader& GetColorShader() const;
		WordleAPI::GL::Shader& GetCircleShader();
		const WordleAPI::GL::Shader& GetCircleShader() const;
		WordleAPI::GL::Texture2D& GetAlphabetTexture();
		const WordleAPI::GL::Texture2D& GetAlphabetTexture() const;

		std::vector<std::vector<char>>& GetDatabaseCuvinte();
		const std::vector<std::vector<char>>& GetDatabaseCuvinte() const;

		bool& GetKeysPressed(const size_t _Key, const size_t _Frame);
		const bool& GetKeysPressed(const size_t _Key, const size_t _Frame) const;

		void RenderSquare(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, WordleAPI::Vec4 _Color);
		void RenderCircle(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, WordleAPI::Vec4 _Color);
		void RenderTexture(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, WordleAPI::GL::Texture2D& _Texture, WordleAPI::Vec2 _TextureMultiplier, WordleAPI::Vec2 _TextureOffset, WordleAPI::Vec4 _Color = WordleAPI::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		void RenderFancySquare(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, WordleAPI::Vec4 _Color, float _Radius);
		void RenderText(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, std::vector<char>& _Cuv, WordleAPI::Vec4 _Color = WordleAPI::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		void RenderText(int32_t _Width, int32_t _Height, WordleAPI::Vec2 _Size, WordleAPI::Vec2 _Position, char* _Cuv, size_t _LenCuv, WordleAPI::Vec4 _Color = WordleAPI::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

		bool UpdateFullScreen();

		void Setup() override;
		void Update() override;
		void Stop() override;

		void operator= (const Application& _Other) = delete;
		void operator= (Application&& _Other) noexcept = delete;

	private:

		bool SuitableScreenSize();

		bool InitWindow();
		void DestroyWindow();

		bool InitOpenGL();
		void DestroyOpenGL();

		bool LoadDatabaseCuvinte();
		void DestroyDatabaseCuvinte();

		WordleAPI::Window Wnd;
		Window::UserData WndUserData;

		WordleAPI::GL::Mesh Quad;
		WordleAPI::GL::VertexAttribArray VAO;
		WordleAPI::GL::Shader TextureShader;
		WordleAPI::GL::Shader ColorShader;
		WordleAPI::GL::Shader CircleShader;
		WordleAPI::GL::Texture2D AlphabetTexture;

		std::vector<std::vector<char>> DatabaseCuvinte;

		bool KeysPressed[256][2];

	};

}



#endif

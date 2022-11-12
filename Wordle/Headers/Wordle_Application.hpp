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

		bool& GetKeysPressed(const size_t _Key, const size_t _Frame);
		const bool& GetKeysPressed(const size_t _Key, const size_t _Frame) const;

		void RenderSquare(int32_t _Width, int32_t _Height, glm::vec2 _Size, glm::vec2 _Position, glm::vec4 _Color);
		void RenderCircle(int32_t _Width, int32_t _Height, glm::vec2 _Size, glm::vec2 _Position, glm::vec4 _Color);
		void RenderTexture(int32_t _Width, int32_t _Height, glm::vec2 _Size, glm::vec2 _Position, WordleAPI::GL::Texture2D& _Texture, glm::vec2 _TextureMultiplier, glm::vec2 _TextureOffset);
		void RenderFancySquare(int32_t _Width, int32_t _Height, glm::vec2 _Size, glm::vec2 _Position, glm::vec4 _Color, float _Radius);
		void RenderText(int32_t _Width, int32_t _Height, glm::vec2 _Size, glm::vec2 _Position, std::vector<char>& _Cuv);

		bool UpdateFullScreen();

		void Setup() override;
		void Update() override;
		void Stop() override;

		void operator= (const Application& _Other) = delete;
		void operator= (Application&& _Other) noexcept = delete;

	private:

		bool InitWindow();
		void DestroyWindow();

		bool InitOpenGL();
		void DestroyOpenGL();

		WordleAPI::Window Wnd;
		Window::UserData WndUserData;

		WordleAPI::GL::Mesh Quad;
		WordleAPI::GL::VertexAttribArray VAO;
		WordleAPI::GL::Shader TextureShader;
		WordleAPI::GL::Shader ColorShader;
		WordleAPI::GL::Shader CircleShader;
		WordleAPI::GL::Texture2D AlphabetTexture;

		bool KeysPressed[256][2];

	};

}



#endif

#ifndef WordleAPI_Window_hpp

#define WordleAPI_Window_hpp



#include "WordleAPI.hpp"



namespace WordleAPI
{

	struct WindowCreationDescriptor
	{
		DWORD dwExStyle = NULL;
		LPCWSTR lpClassName = nullptr;
		LPCWSTR lpWindowName = nullptr;
		DWORD dwStyle = NULL;
		int X = 0;
		int Y = 0;
		int nWidth = 0;
		int nHeight = 0;
		HWND hWndParent = NULL;
		HMENU hMenu = NULL;
		HINSTANCE hInstance = NULL;
		LPVOID lpParam = nullptr;
		HACCEL hAccel = NULL;
		int ShowCmd = SW_HIDE;
		WindowInitFunc WndInitFunc = nullptr;
		void* UserData = nullptr;
	};

	class Window
	{

	public:

		Window();
		Window(const Window& _Other) = delete;
		Window(Window&& _Other) noexcept;
		~Window();

		const bool CheckOn() const;
		const HWND GetHandle() const;
		void* GetUserData();
		const void* GetUserData() const;

		bool Create(const WindowCreationDescriptor* _Descriptor);
		void Destroy();

		bool Show(const int _ShowCmd);
		bool UpdateContent();
		const bool GetClientSize(int32_t& _Width, int32_t& _Height) const;
		const bool GetWindowSize(int32_t& _Width, int32_t& _Height) const;

		operator const HWND() const;

		void operator= (const Window& _Other) = delete;
		void operator= (Window&& _Other) noexcept;

		static Window* GetWindowPtr(const HWND _hWnd);

	private:

		static void WndThreadFunc(bool* _Done, bool* _Fail, Window* _Wnd, const WindowCreationDescriptor* _Descriptor);

		static Window* LastWnd;

		bool On;
		HWND hWnd;
		std::thread WndThread;
		void* UserData;

	};

}



#endif

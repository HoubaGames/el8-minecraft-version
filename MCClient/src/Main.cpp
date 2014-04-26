#include <windows.h>

/* Declare Windows procedure */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	HWND hwnd; /* This is the handle for our window */
	MSG messages; /* Here messages to the application are saved */
	WNDCLASSEXW wincl; /* Data structure for the windowclass */

	ZeroMemory(&wincl, sizeof(wincl));
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = L"Main";
	wincl.lpfnWndProc = WindowProcedure;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof (WNDCLASSEXW);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	if (!RegisterClassExW(&wincl))
		return 0;

	/* The class is registered, let's create the program*/
	hwnd = CreateWindowExW (0, L"Main", L"Minecraft", WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT, 800, 500,
							NULL, NULL, hThisInstance, NULL);

	/* Make the window visible on the screen */
	ShowWindow (hwnd, nCmdShow);

	while (true)
	{
		if (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
		{
				/* Translate virtual-key messages into character messages */
			TranslateMessage(&messages);
			/* Send message to WindowProcedure */
			DispatchMessageW(&messages);
		}

	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return messages.wParam;
}

/* This function is called by the Windows function DispatchMessage() */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) /* handle the messages */
	{
	case WM_DESTROY:
		PostQuitMessage (0); /* send a WM_QUIT to the message queue */
		break;
	default: /* for messages that we don't deal with */
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
	return 0;
}

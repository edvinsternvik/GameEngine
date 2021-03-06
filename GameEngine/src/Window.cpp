#include "Window.h"
#include "Rendering/Debug.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace GameEngine {

	Window::Window(const std::string& title, unsigned int width, unsigned int height) {
		if (!glfwInit()) {
			std::cout << "Could not initialize glfw" << std::endl;
			exit(EXIT_FAILURE);
		}

		enableRendererDebugging();

		m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!m_window) {
			glfwTerminate();
			std::cout << "Could not create window" << std::endl;
			exit(EXIT_FAILURE);
		}

		m_data.title = title;
		glfwGetFramebufferSize(m_window, &m_data.windowSize.x, &m_data.windowSize.y);
		glfwGetWindowPos(m_window, &m_data.windowPos.x, &m_data.windowPos.y);

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);

		glfwSwapInterval(true);

		setEventCallbackFunctions();
	}

	Window::~Window() {
		glfwTerminate();
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(m_window);
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}

	GLFWwindow* Window::getWindow() const {
		return m_window;
	}

	void Window::setEventFunction(std::function<void(Event*)> eventFunction) {
		m_data.eventFunction = eventFunction;
	}

	void Window::setCursorMode(CursorMode cursorMode) {
		int cursorModeInt;
		switch(cursorMode) {
		case CursorMode::Normal: cursorModeInt = GLFW_CURSOR_NORMAL; break;
		case CursorMode::Hidden: cursorModeInt = GLFW_CURSOR_HIDDEN; break;
		case CursorMode::Disabled: cursorModeInt = GLFW_CURSOR_DISABLED; break;
		}

		glfwSetInputMode(m_window, GLFW_CURSOR, cursorModeInt);
		
		m_cursorMode = cursorMode;
	}

	CursorMode Window::getCursorMode() const {
		return m_cursorMode;
	}

	void Window::setEventCallbackFunctions() {
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);

			if(data.eventFunction) {
				WindowCloseEvent e;
				data.eventFunction(&e);
			}
		});

		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
			data.windowSize = Vector2i(width, height);

			if(data.eventFunction) {
				WindowResizeEvent e;
				e.width = width;
				e.height = height;
				data.eventFunction(&e);
			}
		});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x, int y) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
			data.windowPos = Vector2i(x, y);

			if(data.eventFunction) {
				WindowMovedEvent e;
				e.xpos = x;
				e.ypos = y;
				data.eventFunction(&e);
			}
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int keyInt, int scancode, int action, int mod) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
			Key key = static_cast<Key>(keyInt);

			if(data.eventFunction) {
				if(action == GLFW_PRESS) {
					KeyPress e(key, scancode, mod);
					data.eventFunction(&e);
				}
				else if(action == GLFW_RELEASE) {
					KeyReleased e(key, scancode, mod);
					data.eventFunction(&e);
				}
				else if(action == GLFW_REPEAT) {
					KeyTyped e(key, scancode, mod);
					data.eventFunction(&e);
				}
			}
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);

			if(data.eventFunction) {
				MouseMoved e(xpos, ypos);
				if(data.eventFunction) data.eventFunction(&e);
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int buttonInt, int action, int mods) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
			MouseButton button = static_cast<MouseButton>(buttonInt);

			if(data.eventFunction) {
				if(action == GLFW_PRESS) {
					MouseButtonPressed e(button, mods);
					if(data.eventFunction) data.eventFunction(&e);
				}
				else if(action == GLFW_RELEASE) {
					MouseButtonReleased e(button, mods);
					if(data.eventFunction) data.eventFunction(&e);
				}
			}
		});
	}
}
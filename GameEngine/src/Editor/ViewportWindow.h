#pragma once
#include "GuiWindow.h"

namespace GameEngine {

	class Editor;
	class Texture;

    class ViewportWindow : public GuiWindow {
    public:
        ViewportWindow(Application* application, Editor* editor);
        ~ViewportWindow();

        void setTexture(std::shared_ptr<Texture> texture);

        inline virtual const char* getWindowName() override { return "Viewport"; }
        virtual void renderWindow() override;

    private:
        std::shared_ptr<Texture> m_viewportTexture;
        Vector2i m_viewportSize;
    };


}

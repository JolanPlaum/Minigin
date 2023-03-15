//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "GuiManager.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl2.h>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void GuiManager::Init(SDL_Window* pWindow)
{
	m_pWindow = pWindow;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void GuiManager::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void GuiManager::OnGui()
{
	// New Frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	// Update GUI

	// Render
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------


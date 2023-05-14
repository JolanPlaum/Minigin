//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "ControlsDisplay.h"
#include <imgui.h>
#include <string>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void ControlsDisplay::UpdateGui()
{
    if (!m_IsOpen) return;

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    if (ImGui::Begin("Controls", &m_IsOpen, flags))
    {
        ImGui::Indent();

        ImGui::Text("Player 1:");
        ImGui::BulletText("Add points = Face button down (A on Xbox)");
        ImGui::BulletText("Lose life = Face button right (B on Xbox)");
        ImGui::Separator();

        ImGui::Text("Player 2:");
        ImGui::BulletText("Add points = Face button left (X on Xbox)");
        ImGui::BulletText("Lose life = Face button up (Y on Xbox)");

        ImGui::Unindent();
    }
    ImGui::End();
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "TrashTheCache.h"
#include <glm/gtc/constants.hpp>
#include <plugins/imgui_plot.h>
#include <imgui.h>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void TrashTheCache::Init()
{
    for (int i{ 1 }; i <= m_MaxStepSize; i *= 2)
    {
        m_TimeSteps.push_back(static_cast<float>(i));
    }
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void TrashTheCache::Update()
{
    UpdateSample<int>(m_StepSizeInt, m_AveragesInt, m_Ex1SampleCount);
    UpdateSample<GameObject3D>(m_StepSizeGameObject3D, m_AveragesGameObject3D, m_Ex2SampleCount);
    UpdateSample<GameObject3DAlt>(m_StepSizeGameObject3DAlt, m_AveragesGameObject3DAlt, m_Ex2SampleCount);
}

void TrashTheCache::UpdateGui()
{
    GuiExercise1();
    GuiExercise2();
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void TrashTheCache::GuiExercise1()
{
    // Main body of the window
    if (!ImGui::Begin(m_Ex1Name.c_str()))
    {
        ImGui::End();
        return;
    }

    // Contents of window
    ImGui::InputInt("# samples", &m_Ex1SampleCount);

    // Button 1
    if (m_StepSizeInt > 0)
        ImGui::Text("Wait for it...");
    else if (ImGui::Button(m_ButtonTextInt.c_str()))
        m_StepSizeInt = 1;

    // Plot 1
    if (!m_AveragesInt.empty() && m_StepSizeInt == 0)
    {
        ImGui::PlotConfig conf;
        conf.values.color = ImColor(255, 127, 0);
        conf.values.count = static_cast<int>(m_TimeSteps.size());
        conf.values.xs = m_TimeSteps.data();
        conf.values.ys = m_AveragesInt.data();
        //conf.grid_x.show = true;
        conf.grid_y.show = true;
        conf.frame_size = ImVec2(200, 100);
        conf.tooltip.show = true;
        conf.scale.min = *std::min_element(m_AveragesInt.begin(), m_AveragesInt.end());
        conf.scale.max = *std::max_element(m_AveragesInt.begin(), m_AveragesInt.end());
        ImGui::Plot("plot1", conf);
    }

    // Main body end
    ImGui::End();
}

void TrashTheCache::GuiExercise2()
{
    // Main body of the window
    if (!ImGui::Begin(m_Ex2Name.c_str()))
    {
        ImGui::End();
        return;
    }

    // Contents of window
    ImGui::InputInt("# samples", &m_Ex2SampleCount);

    // Button 1
    if (m_StepSizeGameObject3D > 0)
        ImGui::Text("Wait for it...");
    else if (ImGui::Button(m_ButtonTextGameObject3D.c_str()))
        m_StepSizeGameObject3D = 1;

    // Plot 1
    if (!m_AveragesGameObject3D.empty() && m_StepSizeGameObject3D == 0)
    {
        ImGui::PlotConfig conf;
        conf.values.color = ImColor(0, 255, 0);
        conf.values.count = static_cast<int>(m_TimeSteps.size());
        conf.values.xs = m_TimeSteps.data();
        conf.values.ys = m_AveragesGameObject3D.data();
        //conf.grid_x.show = true;
        conf.grid_y.show = true;
        conf.frame_size = ImVec2(200, 100);
        conf.tooltip.show = true;
        conf.scale.min = *std::min_element(m_AveragesGameObject3D.begin(), m_AveragesGameObject3D.end());
        conf.scale.max = *std::max_element(m_AveragesGameObject3D.begin(), m_AveragesGameObject3D.end());
        ImGui::Plot("plot1", conf);
    }

    // Button 2
    if (m_StepSizeGameObject3DAlt > 0)
        ImGui::Text("Wait for it...");
    else if (ImGui::Button(m_ButtonTextGameObject3DAlt.c_str()))
        m_StepSizeGameObject3DAlt = 1;

    // Plot 2
    if (!m_AveragesGameObject3DAlt.empty() && m_StepSizeGameObject3DAlt == 0)
    {
        ImGui::PlotConfig conf;
        conf.values.color = ImColor(0, 127, 255);
        conf.values.count = static_cast<int>(m_TimeSteps.size());
        conf.values.xs = m_TimeSteps.data();
        conf.values.ys = m_AveragesGameObject3DAlt.data();
        //conf.grid_x.show = true;
        conf.grid_y.show = true;
        conf.frame_size = ImVec2(200, 100);
        conf.tooltip.show = true;
        conf.scale.min = *std::min_element(m_AveragesGameObject3DAlt.begin(), m_AveragesGameObject3DAlt.end());
        conf.scale.max = *std::max_element(m_AveragesGameObject3DAlt.begin(), m_AveragesGameObject3DAlt.end());
        ImGui::Plot("plot2", conf);
    }

    // Plot 3
    if (!m_AveragesGameObject3D.empty() && m_StepSizeGameObject3D == 0 &&
        !m_AveragesGameObject3DAlt.empty() && m_StepSizeGameObject3DAlt == 0)
    {
        ImGui::Text("Combined:");
        static const float* y_data[] = { m_AveragesGameObject3D.data(), m_AveragesGameObject3DAlt.data() };
        static ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(0, 127, 255) };

        ImGui::PlotConfig conf;
        conf.values.colors = colors;
        conf.values.count = static_cast<int>(m_TimeSteps.size());
        conf.values.xs = m_TimeSteps.data();
        conf.values.ys_list = y_data;
        conf.values.ys_count = 2;
        //conf.grid_x.show = true;
        conf.grid_y.show = true;
        conf.frame_size = ImVec2(200, 100);
        conf.tooltip.show = true;

        float min1 = *std::min_element(m_AveragesGameObject3D.begin(), m_AveragesGameObject3D.end());
        float min2 = *std::min_element(m_AveragesGameObject3DAlt.begin(), m_AveragesGameObject3DAlt.end());
        float max1 = *std::max_element(m_AveragesGameObject3D.begin(), m_AveragesGameObject3D.end());
        float max2 = *std::max_element(m_AveragesGameObject3DAlt.begin(), m_AveragesGameObject3DAlt.end());
        conf.scale.min = std::min(min1, min2);
        conf.scale.max = std::max(max1, max2);
        ImGui::Plot("combined", conf);
    }

    // Main body end
    ImGui::End();
}


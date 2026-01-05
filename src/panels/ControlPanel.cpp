#include "panels/ControlPanel.h"
#include "imgui.h"

namespace GBDebug {

ControlPanel::ControlPanel()
    : visible_(true)
    , running_(false)
    , step_requested_(false)
    , exit_requested_(false) {
}

void ControlPanel::Render() {
    if (!visible_) {
        return;
    }
    
    // Set initial window position and size (only on first use)
    ImGui::SetNextWindowPos(ImVec2(10, 390), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
    
    ImGui::Begin(GetName());
    
    // Run/Stop button
    if (running_) {
        if (ImGui::Button("Stop (R)", ImVec2(180, 0))) {
            running_ = false;
        }
    } else {
        if (ImGui::Button("Run (R)", ImVec2(180, 0))) {
            running_ = true;
        }
    }
    
    // Step button (only enabled when not running)
    if (running_) {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("Step (S)", ImVec2(180, 0))) {
        step_requested_ = true;
    }
    if (running_) {
        ImGui::EndDisabled();
    }
    
    // Exit button
    if (ImGui::Button("Exit (ESC)", ImVec2(180, 0))) {
        exit_requested_ = true;
    }
    
    ImGui::End();
}

} // namespace GBDebug

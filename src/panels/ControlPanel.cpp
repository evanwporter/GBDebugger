#include "panels/ControlPanel.h"
#include "imgui.h"

namespace GBDebug {

ControlPanel::ControlPanel()
    : visible_(true)
    , running_(false)
    , step_requested_(false)
    , exit_requested_(false)
    , speed_index_(SPEED_1X_INDEX) {  // Start at 1x
}

float ControlPanel::GetSpeedMultiplier() const {
    // Index: 0=1/8x, 1=1/4x, 2=1/2x, 3=1x, 4=2x, 5=4x, 6=8x
    static const float multipliers[] = {0.125f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f, 8.0f};
    return multipliers[speed_index_];
}

void ControlPanel::CycleSpeedUp() {
    if (speed_index_ < SPEED_COUNT - 1) {
        speed_index_++;
    }
}

void ControlPanel::CycleSpeedDown() {
    if (speed_index_ > 0) {
        speed_index_--;
    }
}

void ControlPanel::SetSpeedIndex(int index) {
    if (index >= 0 && index < SPEED_COUNT) {
        speed_index_ = index;
    }
}

void ControlPanel::Render() {
    if (!visible_) {
        return;
    }
    
    // Set initial window position and size (only on first use)
    ImGui::SetNextWindowPos(ImVec2(10, 390), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200, 140), ImGuiCond_FirstUseEver);
    
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
    
    // Speed dropdown with fractional and multiplied speeds
    static const char* speed_labels[] = {"1/8x", "1/4x", "1/2x", "1x", "2x", "4x", "8x"};
    ImGui::SetNextItemWidth(130);
    if (ImGui::BeginCombo("Speed", speed_labels[speed_index_])) {
        for (int i = 0; i < SPEED_COUNT; i++) {
            bool is_selected = (speed_index_ == i);
            if (ImGui::Selectable(speed_labels[i], is_selected)) {
                speed_index_ = i;
            }
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    ImGui::TextDisabled("(T/Shift+T)");
    
    // Exit button
    if (ImGui::Button("Exit (ESC)", ImVec2(180, 0))) {
        exit_requested_ = true;
    }
    
    ImGui::End();
}

} // namespace GBDebug

#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "IDebuggerPanel.h"

namespace GBDebug {

/**
 * ControlPanel - Provides debugger control buttons
 * 
 * This panel displays Run/Stop, Step, Exit, and Speed controls for
 * the emulator execution. It communicates state changes back to the
 * main application through getter methods.
 * 
 * Usage:
 *   panel.Render();
 *   if (panel.IsStepRequested()) { step }
 *   if (panel.IsRunning()) { run }
 *   if (panel.IsExitRequested()) { exit }
 *   int multiplier = panel.GetSpeedMultiplier();
 */
class ControlPanel : public IDebuggerPanel {
public:
    ControlPanel();
    
    void Render() override;
    const char* GetName() const override { return "Controls"; }
    bool IsVisible() const override { return visible_; }
    void SetVisible(bool visible) override { visible_ = visible; }
    
    // State accessors
    bool IsRunning() const { return running_; }
    void SetRunning(bool running) { running_ = running; }
    void ToggleRunning() { running_ = !running_; }
    
    bool IsStepRequested() const { return step_requested_; }
    void ClearStepRequest() { step_requested_ = false; }
    
    bool IsExitRequested() const { return exit_requested_; }
    
    // Speed control: supports 1/8x, 1/4x, 1/2x, 1x, 2x, 4x, 8x
    // Returns multiplier as float (e.g., 0.125 for 1/8x, 8.0 for 8x)
    float GetSpeedMultiplier() const;
    void CycleSpeedUp();   // T: increases speed
    void CycleSpeedDown(); // Shift+T: decreases speed
    void SetSpeedIndex(int index);
    int GetSpeedIndex() const { return speed_index_; }

private:
    bool visible_;
    bool running_;
    bool step_requested_;
    bool exit_requested_;
    int speed_index_; // 0=1/8x, 1=1/4x, 2=1/2x, 3=1x, 4=2x, 5=4x, 6=8x
    static constexpr int SPEED_COUNT = 7;
    static constexpr int SPEED_1X_INDEX = 3;
};

} // namespace GBDebug

#endif // CONTROLPANEL_H

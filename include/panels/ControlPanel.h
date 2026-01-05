#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "IDebuggerPanel.h"

namespace GBDebug {

/**
 * ControlPanel - Provides debugger control buttons
 * 
 * This panel displays Run/Stop, Step, and Exit buttons for controlling
 * the emulator execution. It communicates state changes back to the
 * main application through getter methods.
 * 
 * Usage:
 *   panel.Render();
 *   if (panel.IsStepRequested()) { step }
 *   if (panel.IsRunning()) { run }
 *   if (panel.IsExitRequested()) { exit }
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

private:
    bool visible_;
    bool running_;
    bool step_requested_;
    bool exit_requested_;
};

} // namespace GBDebug

#endif // CONTROLPANEL_H

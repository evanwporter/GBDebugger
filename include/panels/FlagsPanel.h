#ifndef FLAGS_PANEL_H
#define FLAGS_PANEL_H

#include "IDebuggerPanel.h"
#include "DebuggerTypes.h"

namespace GBDebug {

/**
 * FlagsPanel - Displays CPU flag states with visual indicators
 * 
 * Renders an ImGui panel showing the state of the four CPU flags
 * (Zero, Subtract, Half-Carry, Carry) with color-coded SET/CLEAR
 * indicators for quick visual inspection during debugging.
 * 
 * Usage:
 *   1. Call Update() with current CPUState after each emulator step
 *   2. Call Render() each frame to draw the panel
 */
class FlagsPanel : public IDebuggerPanel {
public:
    FlagsPanel();
    ~FlagsPanel() override = default;
    
    // IDebuggerPanel interface
    void Render() override;
    const char* GetName() const override { return "CPU Flags"; }
    bool IsVisible() const override { return visible_; }
    void SetVisible(bool visible) override { visible_ = visible; }
    
    /**
     * Update the CPU state (flags are extracted from AF register)
     */
    void Update(const CPUState& state);

private:
    CPUState state_;
    bool visible_;
};

} // namespace GBDebug

#endif // FLAGS_PANEL_H

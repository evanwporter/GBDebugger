#ifndef IDEBUGGER_PANEL_H
#define IDEBUGGER_PANEL_H

namespace GBDebug {

/**
 * IDebuggerPanel - Abstract interface for all debugger UI panels
 * 
 * Defines the contract that all debugger panels must implement. Each panel
 * is a self-contained UI component responsible for rendering a specific
 * aspect of the emulator state (CPU registers, flags, memory, etc.).
 * 
 * Panels receive data through their specific Update() methods and render
 * that data when Render() is called during the frame loop.
 * 
 * Usage:
 *   1. Implement this interface for each distinct debugger view
 *   2. Call Update() methods to provide new state data
 *   3. Call Render() each frame to draw the panel
 */
class IDebuggerPanel {
public:
    virtual ~IDebuggerPanel() = default;
    
    /**
     * Render the panel using ImGui
     * Called once per frame when the debugger is visible
     */
    virtual void Render() = 0;
    
    /**
     * Get the panel's display name
     * Used for window titles and identification
     */
    virtual const char* GetName() const = 0;
    
    /**
     * Check if the panel is visible
     */
    virtual bool IsVisible() const = 0;
    
    /**
     * Set panel visibility
     */
    virtual void SetVisible(bool visible) = 0;
};

} // namespace GBDebug

#endif // IDEBUGGER_PANEL_H

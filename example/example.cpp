#include "GBDebugger.h"
#include <iostream>
#include <vector>
#include <cstdint>

/**
 * Simple example demonstrating GBDebugger API usage
 * 
 * This example shows how to:
 * 1. Create a GBDebugger instance
 * 2. Open the debugger window
 * 3. Update CPU state with sample data
 * 4. Update memory contents with sample data
 * 5. Render the debugger in a loop
 * 6. Close the debugger
 * 
 * Requirements: 7.1, 7.2, 7.3, 7.4, 7.5
 */

int main() {
    std::cout << "GBDebugger API Usage Example\n";
    std::cout << "============================\n\n";
    
    // Step 1: Create a GBDebugger instance
    std::cout << "Step 1: Creating GBDebugger instance...\n";
    GBDebug::GBDebugger debugger;
    std::cout << "  ✓ GBDebugger instance created\n\n";
    
    // Step 2: Open the debugger window
    std::cout << "Step 2: Opening debugger window...\n";
    if (debugger.Open()) {
        std::cout << "  ✓ Debugger opened successfully\n";
    } else {
        std::cerr << "  ✗ Failed to open debugger\n";
        return 1;
    }
    
    // Verify the debugger is open
    if (debugger.IsOpen()) {
        std::cout << "  ✓ Debugger is open (IsOpen() returned true)\n\n";
    }
    
    // Step 3: Update CPU state with sample data
    std::cout << "Step 3: Updating CPU state with sample data...\n";
    
    // Sample CPU state representing a GameBoy at boot
    uint64_t cycle = 12345;
    uint16_t pc = 0x0150;    // Program counter after boot ROM
    uint16_t sp = 0xFFFE;    // Stack pointer at top of memory
    uint16_t af = 0x01B0;    // A=0x01, F=0xB0 (Z=1, N=0, H=1, C=1)
    uint16_t bc = 0x0013;    // BC register
    uint16_t de = 0x00D8;    // DE register
    uint16_t hl = 0x014D;    // HL register
    bool ime = true;         // Interrupts enabled
    
    debugger.UpdateCPU(cycle, pc, sp, af, bc, de, hl, ime);
    
    std::cout << "  ✓ CPU state updated:\n";
    std::cout << "    - Cycle: " << cycle << "\n";
    std::cout << "    - PC: 0x" << std::hex << pc << "\n";
    std::cout << "    - SP: 0x" << sp << "\n";
    std::cout << "    - AF: 0x" << af << " (A=0x" << (af >> 8) << ", F=0x" << (af & 0xFF) << ")\n";
    std::cout << "    - BC: 0x" << bc << "\n";
    std::cout << "    - DE: 0x" << de << "\n";
    std::cout << "    - HL: 0x" << hl << "\n";
    std::cout << "    - IME: " << (ime ? "enabled" : "disabled") << "\n";
    std::cout << std::dec << "\n";
    
    // Step 4: Update memory with sample data
    std::cout << "Step 4: Updating memory with sample data...\n";
    
    // Create a 64KB memory buffer (full GameBoy address space)
    std::vector<uint8_t> memory(65536, 0);
    
    // Fill ROM area with sample data
    // Nintendo logo area (0x0104-0x0133)
    for (size_t i = 0x0104; i < 0x0134; i++) {
        memory[i] = static_cast<uint8_t>((i * 7) & 0xFF);
    }
    
    // ROM header area (0x0134-0x014F)
    const char* title = "EXAMPLE";
    for (size_t i = 0; i < 7 && title[i] != '\0'; i++) {
        memory[0x0134 + i] = static_cast<uint8_t>(title[i]);
    }
    
    // Sample code at PC location (0x0150)
    memory[0x0150] = 0x3E;  // LD A, 0x42
    memory[0x0151] = 0x42;
    memory[0x0152] = 0x06;  // LD B, 0x10
    memory[0x0153] = 0x10;
    memory[0x0154] = 0xC3;  // JP 0x0100
    memory[0x0155] = 0x00;
    memory[0x0156] = 0x01;
    
    // Fill VRAM with pattern
    for (size_t i = 0x8000; i < 0x9000; i++) {
        memory[i] = static_cast<uint8_t>((i & 0xFF));
    }
    
    // Fill WRAM with test data
    for (size_t i = 0xC000; i < 0xC100; i++) {
        memory[i] = static_cast<uint8_t>((i - 0xC000) & 0xFF);
    }
    
    // Update the debugger with memory contents
    if (debugger.UpdateMemory(memory.data(), memory.size())) {
        std::cout << "  ✓ Memory updated (65536 bytes)\n";
        std::cout << "    - ROM area filled with sample data\n";
        std::cout << "    - VRAM filled with pattern\n";
        std::cout << "    - WRAM filled with test data\n\n";
    } else {
        std::cerr << "  ✗ Failed to update memory\n";
        return 1;
    }
    
    // Step 5: Render the debugger in a loop
    std::cout << "Step 5: Rendering debugger...\n";
    std::cout << "  Note: In a real application with a window system (SDL/GLFW),\n";
    std::cout << "        you would call Render() in your main loop each frame.\n";
    std::cout << "        For this example, we simulate a few render calls:\n\n";
    
    // Simulate a few frames of rendering
    for (int frame = 0; frame < 5; frame++) {
        std::cout << "  Frame " << (frame + 1) << ": Calling debugger.Render()...\n";
        debugger.Render();
        
        // Simulate CPU state changes between frames
        cycle += 1000;
        pc += 3;
        debugger.UpdateCPU(cycle, pc, sp, af, bc, de, hl, ime);
    }
    
    std::cout << "  ✓ Render loop completed\n\n";
    
    std::cout << "  In a real emulator integration, your main loop would look like:\n";
    std::cout << "    while (running) {\n";
    std::cout << "      // Run emulator for one frame\n";
    std::cout << "      emulator.RunFrame();\n";
    std::cout << "      \n";
    std::cout << "      // Update debugger with current state\n";
    std::cout << "      debugger.UpdateCPU(cpu.cycle, cpu.pc, cpu.sp, ...);\n";
    std::cout << "      debugger.UpdateMemory(memory.data(), memory.size());\n";
    std::cout << "      \n";
    std::cout << "      // Render debugger UI\n";
    std::cout << "      debugger.Render();\n";
    std::cout << "      \n";
    std::cout << "      // Swap buffers, handle events, etc.\n";
    std::cout << "    }\n\n";
    
    // Step 6: Close the debugger
    std::cout << "Step 6: Closing debugger...\n";
    debugger.Close();
    std::cout << "  ✓ Debugger closed\n";
    
    // Verify the debugger is closed
    if (!debugger.IsOpen()) {
        std::cout << "  ✓ Debugger is closed (IsOpen() returned false)\n\n";
    }
    
    std::cout << "============================\n";
    std::cout << "Example completed successfully!\n";
    std::cout << "============================\n\n";
    
    std::cout << "Summary of API usage:\n";
    std::cout << "  1. GBDebug::GBDebugger debugger;           // Create instance\n";
    std::cout << "  2. debugger.Open();                        // Open window\n";
    std::cout << "  3. debugger.UpdateCPU(...);                // Update CPU state\n";
    std::cout << "  4. debugger.UpdateMemory(buffer, size);    // Update memory\n";
    std::cout << "  5. debugger.Render();                      // Render (in loop)\n";
    std::cout << "  6. debugger.Close();                       // Close window\n";
    
    return 0;
}

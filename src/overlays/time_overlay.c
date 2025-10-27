#include "time_overlay.h"
#include "../raylib/raylib.h"
#include <stdio.h>

// Simulation state
static SimulationState s_simState = SIM_PAUSED;
static float s_virtualTime = 0.0f;
static float s_lastDeltaTime = 0.0f;

void TimeOverlay_Init(void) {
    s_simState = SIM_PAUSED;
    s_virtualTime = 0.0f;
    s_lastDeltaTime = 0.0f;
}

void TimeOverlay_Update(void) {
    // Update virtual time if simulation is playing
    if (s_simState == SIM_PLAYING) {
        s_lastDeltaTime = GetFrameTime();
        s_virtualTime += s_lastDeltaTime;
    } else {
        s_lastDeltaTime = 0.0f;
    }
    
    // Check mouse clicks for buttons
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        const int pad = 15;
        const int timeBoxW = 220;
        float timeX = (float)pad;
        float timeY = (float)pad;
        float btnY = timeY + 100;
        float btnW = 60;
        float btnH = 30;
        float btnSpacing = 8;
        
        Rectangle playBtn = { timeX + pad, btnY, btnW, btnH };
        Rectangle pauseBtn = { timeX + pad + btnW + btnSpacing, btnY, btnW, btnH };
        Rectangle resetBtn = { timeX + pad + 2 * (btnW + btnSpacing), btnY, btnW, btnH };
        
        if (CheckCollisionPointRec(mousePos, playBtn)) {
            TimeOverlay_Play();
        } else if (CheckCollisionPointRec(mousePos, pauseBtn)) {
            TimeOverlay_Pause();
        } else if (CheckCollisionPointRec(mousePos, resetBtn)) {
            TimeOverlay_Reset();
        }
    }
}

void TimeOverlay_Draw(void) {
    const int pad = 15;
    const int timeBoxW = 220;
    const int timeBoxH = 140;
    float timeX = (float)pad;
    float timeY = (float)pad;
    
    Rectangle timeRect = { timeX, timeY, (float)timeBoxW, (float)timeBoxH };
    DrawRectangleRec(timeRect, Fade(BLACK, 0.7f));
    DrawRectangleLinesEx(timeRect, 2, YELLOW);
    
    // Time header
    DrawText("SIMULATION TIME", (int)timeX + pad, (int)timeY + 8, 16, YELLOW);
    
    // Virtual time display
    char timeText[64];
    int minutes = (int)(s_virtualTime / 60.0f);
    float seconds = s_virtualTime - (minutes * 60.0f);
    snprintf(timeText, sizeof(timeText), "%02d:%05.2f", minutes, seconds);
    DrawText(timeText, (int)timeX + pad, (int)timeY + 32, 24, LIME);
    
    // State indicator
    const char* stateText = (s_simState == SIM_PLAYING) ? "RUNNING" : "PAUSED";
    Color stateColor = (s_simState == SIM_PLAYING) ? GREEN : ORANGE;
    DrawText(stateText, (int)timeX + pad, (int)timeY + 64, 18, stateColor);
    
    // Control buttons
    float btnY = timeY + 100;
    float btnW = 60;
    float btnH = 30;
    float btnSpacing = 8;
    
    // Play button
    Rectangle playBtn = { timeX + pad, btnY, btnW, btnH };
    Color playColor = (s_simState == SIM_PLAYING) ? GREEN : DARKGREEN;
    DrawRectangleRec(playBtn, playColor);
    DrawRectangleLinesEx(playBtn, 2, (s_simState == SIM_PLAYING) ? LIME : LIGHTGRAY);
    DrawText("Play", (int)playBtn.x + 12, (int)playBtn.y + 8, 14, WHITE);
    
    // Pause button
    Rectangle pauseBtn = { timeX + pad + btnW + btnSpacing, btnY, btnW, btnH };
    Color pauseColor = (s_simState == SIM_PAUSED) ? ORANGE : DARKGRAY;
    DrawRectangleRec(pauseBtn, pauseColor);
    DrawRectangleLinesEx(pauseBtn, 2, (s_simState == SIM_PAUSED) ? YELLOW : LIGHTGRAY);
    DrawText("Pause", (int)pauseBtn.x + 6, (int)pauseBtn.y + 8, 14, WHITE);
    
    // Reset button
    Rectangle resetBtn = { timeX + pad + 2 * (btnW + btnSpacing), btnY, btnW, btnH };
    DrawRectangleRec(resetBtn, RED);
    DrawRectangleLinesEx(resetBtn, 2, LIGHTGRAY);
    DrawText("Reset", (int)resetBtn.x + 8, (int)resetBtn.y + 8, 14, WHITE);
}

void TimeOverlay_Close(void) {
    // Cleanup if needed
}

// Simulation control functions
SimulationState TimeOverlay_GetSimState(void) { 
    return s_simState; 
}

float TimeOverlay_GetVirtualTime(void) { 
    return s_virtualTime; 
}

float TimeOverlay_GetDeltaTime(void) { 
    return (s_simState == SIM_PLAYING) ? s_lastDeltaTime : 0.0f; 
}

void TimeOverlay_Play(void) { 
    s_simState = SIM_PLAYING; 
}

void TimeOverlay_Pause(void) { 
    s_simState = SIM_PAUSED; 
}

void TimeOverlay_Reset(void) { 
    s_simState = SIM_PAUSED;
    s_virtualTime = 0.0f;
    s_lastDeltaTime = 0.0f;
}

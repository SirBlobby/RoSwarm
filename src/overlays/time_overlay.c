#include "time_overlay.h"
#include "../raylib/raylib.h"
#include <stdio.h>
#include <math.h>

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
        const int boxW = 280;
        const int boxH = 120;
        float boxX = (float)pad;
        float boxY = (float)pad;
        
        const int btnW = 65;
        const int btnH = 28;
        const int btnSpacing = 10;
        const int btnAreaY = (int)boxY + boxH - btnH - 12;
        
        // Center buttons horizontally in the overlay
        int totalBtnWidth = 2 * btnW + btnSpacing;
        int btnStartX = (int)boxX + (boxW - totalBtnWidth) / 2;
        
        Rectangle playPauseBtn = { (float)btnStartX, (float)btnAreaY, (float)btnW, (float)btnH };
        Rectangle resetBtn = { (float)(btnStartX + btnW + btnSpacing), (float)btnAreaY, (float)btnW, (float)btnH };
        
        if (CheckCollisionPointRec(mousePos, playPauseBtn)) {
            if (s_simState == SIM_PLAYING) {
                TimeOverlay_Pause();
            } else {
                TimeOverlay_Play();
            }
        } else if (CheckCollisionPointRec(mousePos, resetBtn)) {
            TimeOverlay_Reset();
        }
    }
}

void TimeOverlay_Draw(void) {
    const int pad = 15;
    const int boxW = 280;
    const int boxH = 120;
    float boxX = (float)pad;
    float boxY = (float)pad;
    
    // Main overlay box - match settings overlay transparency
    Rectangle timeRect = { boxX, boxY, (float)boxW, (float)boxH };
    DrawRectangleRec(timeRect, Fade(BLACK, 0.7f));
    
    // Header section with status
    const int headerY = (int)boxY + 8;
    const char* statusText = (s_simState == SIM_PLAYING) ? "RUNNING" : "PAUSED";
    Color statusColor = (s_simState == SIM_PLAYING) ? GREEN : ORANGE;
    
    DrawText("SIMULATION:", (int)boxX + pad, headerY, 16, RAYWHITE);
    int statusX = (int)boxX + pad + MeasureText("SIMULATION: ", 16);
    DrawText(statusText, statusX, headerY, 16, statusColor);
    
    // Draw pulsing dot for running state
    if (s_simState == SIM_PLAYING) {
        float pulse = (sinf(s_virtualTime * 3.0f) + 1.0f) / 2.0f;
        int dotX = statusX + MeasureText(statusText, 16) + 8;
        DrawCircle(dotX, headerY + 8, 4, Fade(GREEN, 0.5f + pulse * 0.5f));
    }
    
    // Time display section
    const int timeY = (int)boxY + 38;
    char timeText[64];
    int minutes = (int)(s_virtualTime / 60.0f);
    float seconds = s_virtualTime - (minutes * 60.0f);
    snprintf(timeText, sizeof(timeText), "%02d:%05.2f", minutes, seconds);
    
    // Center the time text
    int timeTextW = MeasureText(timeText, 28);
    int timeX = (int)boxX + (boxW - timeTextW) / 2;
    
    DrawText(timeText, timeX, timeY, 28, RAYWHITE);
    
    // Time label
    const char* timeLabel = "MM:SS.MS";
    int labelW = MeasureText(timeLabel, 10);
    DrawText(timeLabel, (int)boxX + (boxW - labelW) / 2, timeY + 32, 10, Fade(RAYWHITE, 0.6f));
    
    // Control buttons section
    const int btnW = 65;
    const int btnH = 28;
    const int btnSpacing = 10;
    const int btnAreaY = (int)boxY + boxH - btnH - 12;
    
    // Center buttons horizontally
    int totalBtnWidth = 2 * btnW + btnSpacing;
    int btnStartX = (int)boxX + (boxW - totalBtnWidth) / 2;
    
    Vector2 mousePos = GetMousePosition();
    
    // Play/Pause button (toggle)
    Rectangle playPauseBtn = { (float)btnStartX, (float)btnAreaY, (float)btnW, (float)btnH };
    bool hoverPlayPause = CheckCollisionPointRec(mousePos, playPauseBtn);
    
    Color btnColor = (s_simState == SIM_PLAYING) ? ORANGE : GREEN;
    
    DrawRectangleRec(playPauseBtn, Fade(btnColor, hoverPlayPause ? 0.9f : 0.7f));
    DrawRectangleLinesEx(playPauseBtn, 2, hoverPlayPause ? RAYWHITE : LIGHTGRAY);
    
    const char* btnText = (s_simState == SIM_PLAYING) ? "PAUSE" : "PLAY";
    int btnTextW = MeasureText(btnText, 14);
    DrawText(btnText, 
        (int)playPauseBtn.x + (btnW - btnTextW) / 2, 
        (int)playPauseBtn.y + 7, 
        14, WHITE);
    
    // Reset button
    Rectangle resetBtn = { (float)(btnStartX + btnW + btnSpacing), (float)btnAreaY, (float)btnW, (float)btnH };
    bool hoverReset = CheckCollisionPointRec(mousePos, resetBtn);
    
    DrawRectangleRec(resetBtn, Fade(RED, hoverReset ? 0.9f : 0.7f));
    DrawRectangleLinesEx(resetBtn, 2, hoverReset ? RAYWHITE : LIGHTGRAY);
    
    int resetTextW = MeasureText("RESET", 14);
    DrawText("RESET", 
        (int)resetBtn.x + (btnW - resetTextW) / 2, 
        (int)resetBtn.y + 7, 
        14, WHITE);
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

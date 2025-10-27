#include "settings_overlay.h"
#include "../scenes/room.h"
#include "../raylib/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char s_widthInput[8] = "35";
static char s_heightInput[8] = "20";
static int s_widthInputActive = 0;
static int s_heightInputActive = 0;

void SettingsOverlay_Init(void) {
    snprintf(s_widthInput, sizeof(s_widthInput), "%d", room_get_width_meters());
    snprintf(s_heightInput, sizeof(s_heightInput), "%d", room_get_height_meters());
    s_widthInputActive = 0;
    s_heightInputActive = 0;
}

void SettingsOverlay_Update(void) {
    // Handle text input for width and height
    int key = GetCharPressed();
    
    // Check mouse clicks for activating input fields
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        const int pad = 15;
        const int boxW = 280;
        float x = (float)GetScreenWidth() - boxW - pad;
        float y = (float)pad;
        
        // Make entire row clickable for width and height inputs
        Rectangle widthBox = { x + pad, y + 56, boxW - 2 * pad, 25 };
        Rectangle heightBox = { x + pad, y + 86, boxW - 2 * pad, 25 };
        
        if (CheckCollisionPointRec(mousePos, widthBox)) {
            s_widthInputActive = 1;
            s_heightInputActive = 0;
        } else if (CheckCollisionPointRec(mousePos, heightBox)) {
            s_widthInputActive = 0;
            s_heightInputActive = 1;
        } else {
            s_widthInputActive = 0;
            s_heightInputActive = 0;
        }
    }
    
    // Handle keyboard input for active field
    if (s_widthInputActive || s_heightInputActive) {
        char* activeInput = s_widthInputActive ? s_widthInput : s_heightInput;
        int maxLen = 7;
        int currentLen = strlen(activeInput);
        
        // Handle backspace
        if (IsKeyPressed(KEY_BACKSPACE) && currentLen > 0) {
            activeInput[currentLen - 1] = '\0';
        }
        
        // Handle number input
        while (key > 0) {
            if ((key >= '0' && key <= '9') && currentLen < maxLen) {
                activeInput[currentLen] = (char)key;
                activeInput[currentLen + 1] = '\0';
            }
            key = GetCharPressed();
        }
        
        // Apply changes immediately on any input change
        int width = atoi(s_widthInput);
        int height = atoi(s_heightInput);
        if (width > 0 && height > 0) {
            room_set_size(width, height);
        }
        
        // Also apply on Enter and deactivate
        if (IsKeyPressed(KEY_ENTER)) {
            s_widthInputActive = 0;
            s_heightInputActive = 0;
        }
    }
}

void SettingsOverlay_Draw(void) {
    int fps = GetFPS();
    const int pad = 15;
    const int boxW = 280;
    const int boxH = 120;
    float x = (float)GetScreenWidth() - boxW - pad;
    float y = (float)pad;

    Rectangle rect = { x, y, (float)boxW, (float)boxH };
    DrawRectangleRec(rect, Fade(BLACK, 0.7f));

    // FPS display
    char fpsText[32];
    snprintf(fpsText, sizeof(fpsText), "FPS: %d", fps);
    DrawText(fpsText, (int)x + pad, (int)y + 8, 20, RAYWHITE);
    DrawText("Press O to toggle overlay", (int)x + pad, (int)y + 30, 10, RAYWHITE);
    
    // Room width input - entire row is clickable
    Rectangle widthBox = { x + pad, y + 56, boxW - 2 * pad, 25 };
    DrawRectangleRec(widthBox, s_widthInputActive ? Fade(DARKGRAY, 0.8f) : Fade(GRAY, 0.5f));
    DrawRectangleLinesEx(widthBox, 2, s_widthInputActive ? YELLOW : LIGHTGRAY);
    DrawText("Width (m):", (int)x + pad + 5, (int)y + 60, 14, RAYWHITE);
    DrawText(s_widthInput, (int)x + pad + 90, (int)y + 60, 16, WHITE);
    
    // Room height input - entire row is clickable
    Rectangle heightBox = { x + pad, y + 86, boxW - 2 * pad, 25 };
    DrawRectangleRec(heightBox, s_heightInputActive ? Fade(DARKGRAY, 0.8f) : Fade(GRAY, 0.5f));
    DrawRectangleLinesEx(heightBox, 2, s_heightInputActive ? YELLOW : LIGHTGRAY);
    DrawText("Height (m):", (int)x + pad + 5, (int)y + 90, 14, RAYWHITE);
    DrawText(s_heightInput, (int)x + pad + 90, (int)y + 90, 16, WHITE);
}

void SettingsOverlay_Close(void) {
    // Cleanup if needed
}

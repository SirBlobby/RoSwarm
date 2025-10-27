#include "overlay_manager.h"
#include "time_overlay.h"
#include "settings_overlay.h"
#include "../raylib/raylib.h"
#include <stddef.h>

static Overlay s_overlays[OVERLAY_COUNT];
static int s_allVisible = 1;

void OverlayManager_Init(void) {
    // Initialize time/control overlay
    s_overlays[OVERLAY_TIME_CONTROL].visible = 1;
    s_overlays[OVERLAY_TIME_CONTROL].update = TimeOverlay_Update;
    s_overlays[OVERLAY_TIME_CONTROL].draw = TimeOverlay_Draw;
    
    // Initialize settings overlay
    s_overlays[OVERLAY_SETTINGS].visible = 1;
    s_overlays[OVERLAY_SETTINGS].update = SettingsOverlay_Update;
    s_overlays[OVERLAY_SETTINGS].draw = SettingsOverlay_Draw;
    
    TimeOverlay_Init();
    SettingsOverlay_Init();
    
    s_allVisible = 1;
}

void OverlayManager_Update(void) {
    // Toggle all overlays with 'O' key
    if (IsKeyPressed(KEY_O)) {
        OverlayManager_ToggleAll();
    }
    
    // Update visible overlays
    for (int i = 0; i < OVERLAY_COUNT; i++) {
        if (s_overlays[i].visible && s_overlays[i].update != NULL) {
            s_overlays[i].update();
        }
    }
}

void OverlayManager_Draw(void) {
    if (!s_allVisible) return;
    
    // Draw visible overlays
    for (int i = 0; i < OVERLAY_COUNT; i++) {
        if (s_overlays[i].visible && s_overlays[i].draw != NULL) {
            s_overlays[i].draw();
        }
    }
}

void OverlayManager_Close(void) {
    TimeOverlay_Close();
    SettingsOverlay_Close();
}

void OverlayManager_Show(OverlayType type) {
    if (type >= 0 && type < OVERLAY_COUNT) {
        s_overlays[type].visible = 1;
    }
}

void OverlayManager_Hide(OverlayType type) {
    if (type >= 0 && type < OVERLAY_COUNT) {
        s_overlays[type].visible = 0;
    }
}

void OverlayManager_Toggle(OverlayType type) {
    if (type >= 0 && type < OVERLAY_COUNT) {
        s_overlays[type].visible = !s_overlays[type].visible;
    }
}

int OverlayManager_IsVisible(OverlayType type) {
    if (type >= 0 && type < OVERLAY_COUNT) {
        return s_overlays[type].visible && s_allVisible;
    }
    return 0;
}

void OverlayManager_ToggleAll(void) {
    s_allVisible = !s_allVisible;
}

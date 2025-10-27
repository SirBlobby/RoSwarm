#include "overlay.h"
#include "overlay_manager.h"

// Legacy wrapper functions that redirect to overlay manager
void Overlay_Init(void) {
    OverlayManager_Init();
}

void Overlay_Update(void) {
    OverlayManager_Update();
}

void Overlay_Draw(void) {
    OverlayManager_Draw();
}

void Overlay_Close(void) {
    OverlayManager_Close();
}

void Overlay_Toggle(void) {
    OverlayManager_ToggleAll();
}

int Overlay_IsVisible(void) {
    return OverlayManager_IsVisible(OVERLAY_TIME_CONTROL) || 
           OverlayManager_IsVisible(OVERLAY_SETTINGS);
}

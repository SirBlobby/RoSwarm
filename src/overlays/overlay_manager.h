#ifndef OVERLAY_MANAGER_H
#define OVERLAY_MANAGER_H

typedef enum OverlayType {
    OVERLAY_TIME_CONTROL,
    OVERLAY_SETTINGS,
    OVERLAY_COUNT
} OverlayType;

typedef struct Overlay {
    int visible;
    void (*update)(void);
    void (*draw)(void);
} Overlay;

// Overlay manager API
void OverlayManager_Init(void);
void OverlayManager_Update(void);
void OverlayManager_Draw(void);
void OverlayManager_Close(void);

// Overlay visibility control
void OverlayManager_Show(OverlayType type);
void OverlayManager_Hide(OverlayType type);
void OverlayManager_Toggle(OverlayType type);
int OverlayManager_IsVisible(OverlayType type);

// Toggle all overlays
void OverlayManager_ToggleAll(void);

#endif // OVERLAY_MANAGER_H

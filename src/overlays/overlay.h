#ifndef OVERLAY_H
#define OVERLAY_H

#include "time_overlay.h"

// Legacy API - redirects to overlay manager and time overlay
void Overlay_Init(void);
void Overlay_Update(void);
void Overlay_Draw(void);
void Overlay_Close(void);
void Overlay_Toggle(void);
int Overlay_IsVisible(void);

// Simulation control API - redirects to time overlay
#define Overlay_GetSimState TimeOverlay_GetSimState
#define Overlay_GetVirtualTime TimeOverlay_GetVirtualTime
#define Overlay_GetDeltaTime TimeOverlay_GetDeltaTime
#define Overlay_Play TimeOverlay_Play
#define Overlay_Pause TimeOverlay_Pause
#define Overlay_Reset TimeOverlay_Reset

#endif // OVERLAY_H

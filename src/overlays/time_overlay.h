#ifndef TIME_OVERLAY_H
#define TIME_OVERLAY_H

typedef enum SimulationState {
    SIM_PAUSED,
    SIM_PLAYING
} SimulationState;

// Time overlay API
void TimeOverlay_Init(void);
void TimeOverlay_Update(void);
void TimeOverlay_Draw(void);
void TimeOverlay_Close(void);

// Simulation control API
SimulationState TimeOverlay_GetSimState(void);
float TimeOverlay_GetVirtualTime(void);
float TimeOverlay_GetDeltaTime(void);
void TimeOverlay_Play(void);
void TimeOverlay_Pause(void);
void TimeOverlay_Reset(void);

#endif // TIME_OVERLAY_H

#ifndef SPEAKER_H
#define SPEAKER_H

#include <Arduino.h>

// Public API
void initSPIFFS();
void initSpeaker();

int playStart();
int playEnd();

#endif // SPEAKER_H

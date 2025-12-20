#ifndef SPEAKER_H
#define SPEAKER_H

#include <Arduino.h>

// Public API
void initSPIFFS();
void initSpeaker();

int playStart(int playCount);
int playEnd(int state);
void playFalseStart();

#endif // SPEAKER_H

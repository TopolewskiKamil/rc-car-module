#include "speaker.h"

#include "Audio.h"
#include "SPIFFS.h"

// ===== MAX98357A I2S pins =====
#define MAX98357A_I2S_DOUT 27
#define MAX98357A_I2S_BCLK 14
#define MAX98357A_I2S_LRC  12

// ===== Module-private objects & state =====
static Audio audio;

static bool started = false;

// ===== Initialization =====
void initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS Mount Failed");
    while (1)
      delay(100);
  }
}

void initSpeaker()
{
  audio.setPinout(
      MAX98357A_I2S_BCLK,
      MAX98357A_I2S_LRC,
      MAX98357A_I2S_DOUT);

  audio.setVolume(50);
}

// ===== Playback logic =====
int playStart(int playCount)
{
  if (!audio.isRunning() && playCount <= 2)
  {
    Serial.println("Start, count: " + String(playCount));
    audio.connecttoFS(SPIFFS, "/mario-start.wav");
    playCount++;
  } 
  
  audio.loop();
  return playCount;
}

int playEnd(int speakerEndState)
{
  bool audioRunning = audio.isRunning();
  if (!audioRunning && speakerEndState == 0)
  {
    Serial.println("End, count: ");
    audio.connecttoFS(SPIFFS, "/mario-end.wav");
    speakerEndState = 1;
  } else if (!audioRunning){
    Serial.println("Finish");
    speakerEndState = 2;
  }
  Serial.print("Play");
  audio.loop();
  return speakerEndState;
}

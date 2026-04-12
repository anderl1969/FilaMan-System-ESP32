#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h>
#include "config.h"

// Note
struct Note {
  int16_t freq;
  int16_t duration;
};

// Melody
struct Melody {
  const Note* notes;
  size_t length;
};

// Sound-IDs
enum SoundId {
  SND_SUCCESS,
  SND_FAIL,
  SND_WAIT,
  SND_BOOT,
  SND_START,
  SND_JINGLE
};

class SoundPlayer {
public:
  void play(const Melody& melody);
  void playSound(SoundId id);
  void enqueueSound(SoundId id);

  void begin();
  void update();
  bool isPlaying();

private:
  static const int QUEUE_SIZE = 5;

  Melody _queue[QUEUE_SIZE];
  int _queueStart = 0;
  int _queueEnd = 0;

  Melody _current = {nullptr, 0};

  size_t _index = 0;
  bool _toneActive = false;
  unsigned long _lastChange = 0;

  void startNext();
  void enqueue(const Melody& melody);
  const Melody& getMelody(SoundId id);
};

extern SoundPlayer player;

void startSoundPlayer();

#endif

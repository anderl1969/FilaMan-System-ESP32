#include "sound.h"
#include "pitches.h"
#include "display.h"
#include "lang.h"

// Melodien
const Note successNotes[] = {{NOTE_B5, 100}, {NOTE_FS6, 120}, {NOTE_B6, 150}};
const Note failNotes[] = {{NOTE_B6, 150}, {NOTE_D6, 200}, {NOTE_G5, 300}};
const Note waitNotes[] = {{NOTE_FS6, 100}, {0, 400}, {NOTE_FS6, 100}, {0, 400}, {NOTE_FS6, 100}, {0, 400}};
const Note bootNotes[] = {{NOTE_G5, 100}, {NOTE_D6, 100}, {NOTE_G6, 100}, {NOTE_B6, 150}};
const Note startNotes[] = {{NOTE_C4, 325}, {NOTE_G3, 163}, {NOTE_G3, 163}, {NOTE_A3, 325}, {NOTE_G3, 325}, {0, 325}, {NOTE_B3, 325}, {NOTE_C4, 325}};
const Note jingleNotes[] = {{NOTE_C5, 120}, {NOTE_E5, 120}, {NOTE_G5, 120}, {NOTE_C6, 180}};


// Melody-Wrapper
const Melody melodies[] = {
  {successNotes, 3}, // SND_SUCCESS
  {failNotes,    3}, // SND_FAIL
  {waitNotes,    6}, // SND_WAIT
  {bootNotes,    4}, // SND_BOOT
  {startNotes,   8}, // SND_START
  {jingleNotes,  4}  // SND_JINGLE
};

// Mapping
const Melody& SoundPlayer::getMelody(SoundId id) {
  return melodies[id];
}

// API
void SoundPlayer::playSound(SoundId id) {
  play(getMelody(id));
  Serial.print("BUZ: Started melody ");
  Serial.println(id);
}

void SoundPlayer::enqueueSound(SoundId id) {
  enqueue(getMelody(id));
}

// bestehende Logik
void SoundPlayer::play(const Melody& melody) {
  _queueStart = _queueEnd = 0;
  _current = melody;
  _index = 0;
  _toneActive = false;
  _lastChange = millis();
}

void SoundPlayer::enqueue(const Melody& melody) {
  int next = (_queueEnd + 1) % QUEUE_SIZE;
  if (next == _queueStart) return;

  _queue[_queueEnd] = melody;
  _queueEnd = next;
}

void SoundPlayer::startNext() {
  if (_queueStart == _queueEnd) {
    _current = {nullptr, 0};
    return;
  }

  _current = _queue[_queueStart];
  _queueStart = (_queueStart + 1) % QUEUE_SIZE;

  _index = 0;
  _toneActive = false;
}

void SoundPlayer::begin() {
  ledcSetup(BUZZER_CHANNEL, 2000, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  Serial.println("BUZZER initialized");
}

void SoundPlayer::update() {
  if (_current.notes == nullptr) {
    startNext();
    return;
  }

  unsigned long now = millis();

  if (!_toneActive) {
    ledcWriteTone(BUZZER_CHANNEL, _current.notes[_index].freq);
    _lastChange = now;
    _toneActive = true;
  }
  else {
    if (now - _lastChange >= _current.notes[_index].duration) {
      ledcWriteTone(BUZZER_CHANNEL, 0);
      _toneActive = false;
      _lastChange = now;

      _index++;

      if (_index >= _current.length) {
        startNext();
      }
    }
  }
}

bool SoundPlayer::isPlaying() {
  return (_current.notes != nullptr) || (_queueStart != _queueEnd);
}

SoundPlayer player;

void startSoundPlayer() {
  oledShowProgressBar(5, NUM_SETUP_STEPS, DISPLAY_BOOT_TEXT, tr(STR_BUZ_INIT));
  player.begin();
}

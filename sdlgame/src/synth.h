#include <fluidsynth.h>
#include <unistd.h>
#include "datareader.h"

typedef struct Melody {
    unsigned int time; // milliseconds offset from previous note
    int note;
    bool checked;
} Melody;

class Synth {
public:
    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_audio_driver_t* adriver;
    fluid_sequencer_t* sequencer;
    static unsigned int melodyStart;
    static unsigned int now;
    static int noteIndex;
    int sfont_id;
    int seqId;
    short mySeqId;
    int currentBank;
    int currentProg;
    int seqduration;
    std::vector<std::vector<Melody> > tracks;
    Synth() {
        seqduration = 1000;
        currentBank = 0;
        currentProg = 0;
        settings = new_fluid_settings();
        synth = new_fluid_synth(settings);
        adriver = new_fluid_audio_driver(settings, synth);
        sfont_id = fluid_synth_sfload(synth, "piano/MO3.sf2", 1);
        fluid_synth_program_select(synth, 0, sfont_id, currentBank, currentProg);
        sequencer = new_fluid_sequencer2(0);
        seqId = fluid_sequencer_register_fluidsynth(sequencer, synth);
        mySeqId = fluid_sequencer_register_client(sequencer, "me", Synth::seq_callback, NULL);


        // int i, key;
        // for (i = 0; i < 12; i++) {
        //
        //     /* Generate a random key */
        //     key = 60 + (int) (12.0f * rand() / (float) RAND_MAX);
        //     printf("Playing note\n");
        //     /* Play a note */
        //     fluid_synth_noteon(synth, 0, 60, 127);
        //
        //     /* Sleep for 1 second */
        //     sleep(1);
        //
        //     /* Stop the note */
        //     fluid_synth_noteoff(synth, 0, 60);
        // }
    }

    bool hitNote(int note1, int note2, int time1, int time2) {
        if (note1 != note2) {
            return false;
        }

        int difference = time1 - time2;
        if (difference > -10 && difference < 10) {
            return true;
        }
        if (difference > -100 && difference < 100) {
            return true;
        }

        return false;
    }

    void playNote(int note) {
        fluid_synth_noteon(synth, 0, note, 127);
        now = fluid_sequencer_get_tick(sequencer);
        if (melodyStart == 0) {
            return;
        }
//        printf("Now: %i\n", now);
        // have current time
        // need to compare current time and note with the melody's time and note
        for (int i = 0; i < tracks[0].size(); i++) {
            if (tracks[0][i].checked) {
                continue;
            }

            tracks[0][i].checked = true;
            if (i < noteIndex - 1) {
                printf("failed note %i\n", i);
                continue;
            }
            // if (now - (melodyStart+tracks[0][i].time) > 0) {
            //
            // }
            bool good = hitNote(note, tracks[0][i].note, now, melodyStart+tracks[0][i].time);
            if (good) {
                printf("good!\n");
            } else {
                printf("bad\n");
            }
            break;
        }
    }

    void releaseNote(int note) {
        fluid_synth_noteoff(synth, 0, note);
    }

    void updateProgram() {
        fluid_synth_program_select(synth, 0, sfont_id, currentBank, currentProg);
    }

    void nextInstrument() {
        currentProg++;
        updateProgram();
    }
    void prevInstrument() {
        currentProg--;
        updateProgram();
    }

    static void seq_callback(unsigned int time, fluid_event_t* event, fluid_sequencer_t* seq, void* data) {
        // printf("melo: %i\n", melodyStart);
        // printf("note: %i\n", fluid_event_get_key(event));
        // printf("index: %i\n", noteIndex);
        noteIndex++;
    }

    void sendnoteon(int chan, short key, unsigned int date, bool isPlayable) {
        //printf("sending note at time %i\n", date);
        int fluid_res;
        fluid_event_t *evt = new_fluid_event();
        fluid_event_set_source(evt, -1);
        fluid_event_set_dest(evt, seqId);
        fluid_event_noteon(evt, chan, key, 127);
        fluid_res = fluid_sequencer_send_at(sequencer, evt, date, 1);
        fluid_event_noteoff(evt, chan, key);
        fluid_res = fluid_sequencer_send_at(sequencer, evt, date+1000, 1);

        if (isPlayable) {
            fluid_event_set_dest(evt, mySeqId);
            fluid_sequencer_send_at(sequencer, evt, date, 1);
        }

        delete_fluid_event(evt);
    }

    void getSong() {
        std::vector<std::vector<int> > trackData = loadSong("data/song.xml");
        for (int i = 0; i < trackData.size(); i++) {
            std::vector<Melody> melody;
            for (int j = 0; j < trackData[i].size(); j++) {
                melody.push_back((Melody){1000 * j, trackData[i][j]});
            }
            tracks.push_back(melody);
        }
    }

    void playSong() {
        getSong();

        melodyStart = fluid_sequencer_get_tick(sequencer);
        noteIndex = 0;
        //printf("melody start: %i\n", melodyStart);
        for (int i = 0; i < tracks.size(); i++) {
            for (int j = 0; j < tracks[i].size(); j++) {
                tracks[i][j].checked = false;
                sendnoteon(1, tracks[i][j].note, melodyStart + tracks[i][j].time, i == 0);
            }
        }
    }

    ~Synth() {
        delete_fluid_sequencer(sequencer);
        delete_fluid_audio_driver(adriver);
        delete_fluid_synth(synth);
        delete_fluid_settings(settings);
    }

};

unsigned int Synth::melodyStart;
unsigned int Synth::now;
int Synth::noteIndex;

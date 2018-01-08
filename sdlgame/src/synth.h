#include <fluidsynth.h>
#include <unistd.h>

class Synth {
public:
    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_audio_driver_t* adriver;
    int sfont_id;
    Synth() {
        settings = new_fluid_settings();
        synth = new_fluid_synth(settings);
        //fluid_settings_setstr(settings, "audio.driver", "coreaudio");
        adriver = new_fluid_audio_driver(settings, synth);
        sfont_id = fluid_synth_sfload(synth, "piano/Compress Piano.sf2", 1);
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

    void playNote(int note) {
        fluid_synth_noteon(synth, 0, note, 127);
    }

    void releaseNote(int note) {
        fluid_synth_noteoff(synth, 0, note);
    }

    ~Synth() {
        delete_fluid_audio_driver(adriver);
        delete_fluid_synth(synth);
        delete_fluid_settings(settings);
    }

};

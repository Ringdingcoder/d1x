#ifndef _ALLG_SND
#define _ALLG_SND

extern char allegro_error[];

#define DIGI_VOICES           32       /* Theoretical maximums: */
#define MIDI_VOICES           32       /* actual drivers may not be */
#define MIDI_TRACKS           32       /* able to handle this many */


typedef struct SAMPLE                  /* a sample */
{
   int bits;                           /* 8 or 16 */
   int freq;                           /* sample frequency */
   int priority;                       /* 0-255 */
   unsigned long len;                  /* length (in samples) */
   unsigned long loop_start;           /* loop start position */
   unsigned long loop_end;             /* loop finish position */
   unsigned long param;                /* for internal use by the driver */
   void *data;                         /* sample data */
} SAMPLE;


typedef struct MIDI                    /* a midi file */
{
   int divisions;                      /* number of ticks per quarter note */
   struct {
      unsigned char *data;             /* MIDI message stream */
      int len;                         /* length of the track data */
   } track[MIDI_TRACKS]; 
} MIDI;


typedef struct AUDIOSTREAM
{
   int voice;                          /* the voice we are playing on */
   SAMPLE *samp;                       /* the sample we are using */
   void *b1, *b2;                      /* two audio buffers */
   int bufnum;                         /* which buffer is currently playing */
   int len;                            /* buffer length */
} AUDIOSTREAM;


#define DIGI_AUTODETECT       -1       /* for passing to install_sound() */
#define DIGI_NONE             0

#ifdef DJGPP 

/* for djgpp */
#define DIGI_SB               1
#define DIGI_SB10             2 
#define DIGI_SB15             3 
#define DIGI_SB20             4 
#define DIGI_SBPRO            5 
#define DIGI_SB16             6 
#define DIGI_GUS              7

#endif

#define MIDI_AUTODETECT       -1
#define MIDI_NONE             0 

#ifdef DJGPP 

/* for djgpp */
#define MIDI_ADLIB            1 
#define MIDI_OPL2             2 
#define MIDI_2XOPL2           3 
#define MIDI_OPL3             4
#define MIDI_SB_OUT           5
#define MIDI_MPU              6 
#define MIDI_GUS              7
#define MIDI_DIGMID           8
#define MIDI_AWE32            9

#else 

/* for linux */
#define MIDI_LINUX_SOUND_NOT_IMPLEMENTED_YET

#endif 


typedef struct DIGI_DRIVER             /* driver for playing digital sfx */
{
   char *name;                         /* driver name */
   char *desc;                         /* description string */
   int  voices;                        /* available voices */
   int  basevoice;                     /* voice number offset */
   int  max_voices;                    /* maximum voices we can support */
   int  def_voices;                    /* default number of voices to use */

   /* setup routines */
   int  (*detect)(); 
   int  (*init)(int voices); 
   void (*exit)(); 
   int  (*mixer_volume)(int volume);

   /* voice control functions */
   void (*init_voice)(int voice, SAMPLE *sample);
   void (*release_voice)(int voice);
   void (*start_voice)(int voice);
   void (*stop_voice)(int voice);
   void (*loop_voice)(int voice, int playmode);

   /* position control functions */
   int  (*get_position)(int voice);
   void (*set_position)(int voice, int position);

   /* volume control functions */
   int  (*get_volume)(int voice);
   void (*set_volume)(int voice, int volume);
   void (*ramp_volume)(int voice, int time, int endvol);
   void (*stop_volume_ramp)(int voice);

   /* pitch control functions */
   int  (*get_frequency)(int voice);
   void (*set_frequency)(int voice, int frequency);
   void (*sweep_frequency)(int voice, int time, int endfreq);
   void (*stop_frequency_sweep)(int voice);

   /* pan control functions */
   int  (*get_pan)(int voice);
   void (*set_pan)(int voice, int pan);
   void (*sweep_pan)(int voice, int time, int endpan);
   void (*stop_pan_sweep)(int voice);

   /* effect control functions */
   void (*set_echo)(int voice, int strength, int delay);
   void (*set_tremolo)(int voice, int rate, int depth);
   void (*set_vibrato)(int voice, int rate, int depth);
} DIGI_DRIVER;


typedef struct MIDI_DRIVER             /* driver for playing midi music */
{
   char *name;                         /* driver name */
   char *desc;                         /* description string */
   int  voices;                        /* available voices */
   int  basevoice;                     /* voice number offset */
   int  max_voices;                    /* maximum voices we can support */
   int  def_voices;                    /* default number of voices to use */
   int  xmin, xmax;                    /* reserved voice range */

   /* setup routines */
   int  (*detect)();
   int  (*init)(int voices);
   void (*exit)();
   int  (*mixer_volume)(int volume);

   /* raw MIDI output to MPU-401, etc. */
   void (*raw_midi)(unsigned char data);

   /* dynamic patch loading routines */
   int  (*load_patches)(char *patches, char *drums);
   void (*adjust_patches)(char *patches, char *drums);

   /* note control functions */
   void (*key_on)(int inst, int note, int bend, int vol, int pan);
   void (*key_off)(int voice);
   void (*set_volume)(int voice, int vol);
   void (*set_pitch)(int voice, int note, int bend);
   void (*set_pan)(int voice, int pan);
   void (*set_vibrato)(int voice, int amount);
} MIDI_DRIVER;


extern DIGI_DRIVER digi_none;

#ifdef DJGPP
/* for djgpp */
extern DIGI_DRIVER digi_sb, digi_gus;
#else
/* for linux */
extern DIGI_DRIVER digi_linux_sound_not_implemented_yet;
#endif

extern MIDI_DRIVER midi_none;

#ifdef DJGPP
/* for djgpp */
extern MIDI_DRIVER midi_adlib, midi_sb_out, midi_mpu401, midi_gus, midi_digmid, midi_awe32;
#else
/* for linux */
extern MIDI_DRIVER midi_linux_sound_not_implemented_yet;
#endif


typedef struct _DIGI_DRIVER_INFO       /* info about a digital driver */
{
   int driver_id;                      /* integer ID */
   DIGI_DRIVER *driver;                /* the driver structure */
   int autodetect;                     /* set to allow autodetection */
} _DIGI_DRIVER_INFO;


typedef struct _MIDI_DRIVER_INFO       /* info about a MIDI driver */
{
   int driver_id;                      /* integer ID */
   MIDI_DRIVER *driver;                /* the driver structure */
   int autodetect;                     /* set to allow autodetection */
} _MIDI_DRIVER_INFO;


/* driver tables for autodetection */
extern _DIGI_DRIVER_INFO _digi_driver_list[];
extern _MIDI_DRIVER_INFO _midi_driver_list[];


/* macros for constructing the driver lists */
#define DECLARE_DIGI_DRIVER_LIST(list...)                                    \
   _DIGI_DRIVER_INFO _digi_driver_list[] =                                   \
   {                                                                         \
      list                                                                   \
      {  DIGI_NONE,        &digi_none,          TRUE  },                     \
      {  0,                NULL,                0     }                      \
   };

#define DECLARE_MIDI_DRIVER_LIST(list...)                                    \
   _MIDI_DRIVER_INFO _midi_driver_list[] =                                   \
   {                                                                         \
      list                                                                   \
      {  MIDI_NONE,        &midi_none,          TRUE  },                     \
      {  0,                NULL,                0     }                      \
   };

#define DIGI_DRIVER_GUS                                                      \
      {  DIGI_GUS,         &digi_gus,           TRUE   },

#define DIGI_DRIVER_SB                                                       \
      {  DIGI_SB,          &digi_sb,            TRUE   },                    \
      {  DIGI_SB10,        &digi_sb,            FALSE  },                    \
      {  DIGI_SB15,        &digi_sb,            FALSE  },                    \
      {  DIGI_SB20,        &digi_sb,            FALSE  },                    \
      {  DIGI_SBPRO,       &digi_sb,            FALSE  },                    \
      {  DIGI_SB16,        &digi_sb,            FALSE  },

#define MIDI_DRIVER_AWE32                                                    \
      {  MIDI_AWE32,       &midi_awe32,         TRUE   },

#define MIDI_DRIVER_DIGMID                                                   \
      {  MIDI_DIGMID,      &midi_digmid,        TRUE   },

#define MIDI_DRIVER_ADLIB                                                    \
      {  MIDI_ADLIB,       &midi_adlib,         TRUE   },                    \
      {  MIDI_OPL2,        &midi_adlib,         FALSE  },                    \
      {  MIDI_2XOPL2,      &midi_adlib,         FALSE  },                    \
      {  MIDI_OPL3,        &midi_adlib,         FALSE  },

#define MIDI_DRIVER_SB_OUT                                                   \
      {  MIDI_SB_OUT,      &midi_sb_out,        FALSE  },

#define MIDI_DRIVER_MPU                                                      \
      {  MIDI_MPU,         &midi_mpu401,        FALSE  },


extern DIGI_DRIVER *digi_driver;       /* the drivers currently in use */
extern MIDI_DRIVER *midi_driver;

extern int digi_card, midi_card;

extern volatile long midi_pos;         /* current position in the midi file */

extern long midi_loop_start;           /* where to loop back to at EOF */
extern long midi_loop_end;             /* loop when we hit this position */

int detect_digi_driver(int driver_id);
int detect_midi_driver(int driver_id);

void reserve_voices(int digi_voices, int midi_voices);
int install_sound(int digi_card, int midi_card, char *cfg_path);
void remove_sound();
void set_volume(int digi_volume, int midi_volume);

int load_ibk(char *filename, int drums);

SAMPLE *load_sample(char *filename);
SAMPLE *load_wav(char *filename);
SAMPLE *load_voc(char *filename);
void destroy_sample(SAMPLE *spl);

int play_sample(SAMPLE *spl, int vol, int pan, int freq, int loop);
void stop_sample(SAMPLE *spl);
void adjust_sample(SAMPLE *spl, int vol, int pan, int freq, int loop);

int allocate_voice(SAMPLE *spl);
void deallocate_voice(int voice);
void reallocate_voice(int voice, SAMPLE *spl);
void release_voice(int voice);
void voice_start(int voice);
void voice_stop(int voice);
void voice_set_priority(int voice, int priority);
SAMPLE *voice_check(int voice);

#define PLAYMODE_PLAY           0
#define PLAYMODE_LOOP           1
#define PLAYMODE_FORWARD        0
#define PLAYMODE_BACKWARD       2
#define PLAYMODE_BIDIR          4

void voice_set_playmode(int voice, int playmode);

int voice_get_position(int voice);
void voice_set_position(int voice, int position);

int voice_get_volume(int voice);
void voice_set_volume(int voice, int volume);
void voice_ramp_volume(int voice, int time, int endvol);
void voice_stop_volumeramp(int voice);

int voice_get_frequency(int voice);
void voice_set_frequency(int voice, int frequency);
void voice_sweep_frequency(int voice, int time, int endfreq);
void voice_stop_frequency_sweep(int voice);

int voice_get_pan(int voice);
void voice_set_pan(int voice, int pan);
void voice_sweep_pan(int voice, int time, int endpan);
void voice_stop_pan_sweep(int voice);

void voice_set_echo(int voice, int strength, int delay);
void voice_set_tremolo(int voice, int rate, int depth);
void voice_set_vibrato(int voice, int rate, int depth);

MIDI *load_midi(char *filename);
void destroy_midi(MIDI *midi);
int play_midi(MIDI *midi, int loop);
int play_looped_midi(MIDI *midi, int loop_start, int loop_end);
void stop_midi();
void midi_pause();
void midi_resume();
int midi_seek(int target);
void midi_out(unsigned char *data, int length);
int load_midi_patches();

extern void (*midi_msg_callback)(int msg, int byte1, int byte2);
extern void (*midi_meta_callback)(int type, unsigned char *data, int length);
extern void (*midi_sysex_callback)(unsigned char *data, int length);

AUDIOSTREAM *play_audio_stream(int len, int bits, int freq, int vol, int pan);
void stop_audio_stream(AUDIOSTREAM *stream);
void *get_audio_stream_buffer(AUDIOSTREAM *stream);
void free_audio_stream_buffer(AUDIOSTREAM *stream);

void allg_snd_init();
MIDI *load_hmp(char *filename);

// return true if using the digmid driver
int allegro_using_digmid();

#endif

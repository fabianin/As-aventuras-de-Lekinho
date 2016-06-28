#include <stdio.h>
#include <math.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

//Como compilar: g++ main.cpp -o main -lopenal -lalut -fpermissive -w
//OpenAL: sudo apt-get install libopenal0a libopenal-dev
//ALUT: sudo apt-get install libalut0 libalut-dev

// Maximum data buffers we will need.
#define NUM_BUFFERS 3

// Maximum emissions we will need.
#define NUM_SOURCES 3

// These index the buffers and sources.
#define GAME 0
#define ARROW   1
#define RECORD   2

// Buffers hold sound data.
ALuint Buffers[NUM_BUFFERS];

// Sources are points of emitting sound.
ALuint Sources[NUM_SOURCES];

// Position of the source sounds.
ALfloat SourcesPos[NUM_SOURCES][3];

// Velocity of the source sounds.
ALfloat SourcesVel[NUM_SOURCES][3];

// Position of the listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// Velocity of the listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

/*
 * ALboolean LoadALData()
 *
 *	This function will load our sample data from the disk using the alut
 *	utility and send the data into OpenAL as a buffer. A source is then
 *	also created to play that buffer.
 */
ALboolean LoadALData(){
	// Variables to load into.
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into buffers.
	alGenBuffers(NUM_BUFFERS, Buffers);

	if(alGetError() != AL_NO_ERROR)	return AL_FALSE;

	alutLoadWAVFile("wavdata/Casio-MT-45-16-Beat.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[GAME], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("wavdata/Button_Press_3-Marianne_Gagnon-771871963.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[ARROW], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("wavdata/record.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[RECORD], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	// Bind buffers into audio sources.
	alGenSources(NUM_SOURCES, Sources);

	if(alGetError() != AL_NO_ERROR) return AL_FALSE;

	alSourcei (Sources[GAME], AL_BUFFER,   Buffers[GAME]   );
	alSourcef (Sources[GAME], AL_PITCH,    1.0f              );
	alSourcef (Sources[GAME], AL_GAIN,     1.0f              );
	alSourcefv(Sources[GAME], AL_POSITION, SourcesPos[GAME]);
	alSourcefv(Sources[GAME], AL_VELOCITY, SourcesVel[GAME]);
	alSourcei (Sources[GAME], AL_LOOPING,  AL_TRUE           );

	alSourcei (Sources[ARROW], AL_BUFFER,   Buffers[ARROW]   );
	alSourcef (Sources[ARROW], AL_PITCH,    1.0f            );
	alSourcef (Sources[ARROW], AL_GAIN,     1.0f            );
	alSourcefv(Sources[ARROW], AL_POSITION, SourcesPos[ARROW]);
	alSourcefv(Sources[ARROW], AL_VELOCITY, SourcesVel[ARROW]);
	alSourcei (Sources[ARROW], AL_LOOPING,  AL_FALSE        );

	alSourcei (Sources[RECORD], AL_BUFFER,   Buffers[RECORD]   );
	alSourcef (Sources[RECORD], AL_PITCH,    1.0f            );
	alSourcef (Sources[RECORD], AL_GAIN,     1.0f            );
	alSourcefv(Sources[RECORD], AL_POSITION, SourcesPos[RECORD]);
	alSourcefv(Sources[RECORD], AL_VELOCITY, SourcesVel[RECORD]);
	alSourcei (Sources[RECORD], AL_LOOPING,  AL_FALSE        );

	// Do another error check and return.
	if(alGetError() != AL_NO_ERROR) return AL_FALSE;

	return AL_TRUE;
}

/*
 * void SetListenerValues()
 *
 *	We already defined certain values for the listener, but we need
 *	to tell OpenAL to use that data. This function does just that.
 */
void SetListenerValues(){
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

/*
 * void KillALData()
 *
 *	We have allocated memory for our buffers and sources which needs
 *	to be returned to the system. This function frees that memory.
 */
void KillALData(){
	alDeleteBuffers(NUM_BUFFERS, Buffers);
	alDeleteSources(NUM_SOURCES, Sources);
	alutExit();
}

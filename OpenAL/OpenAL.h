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
#define BATTLE 0
#define GUN1   1
#define GUN2   2

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
	alBufferData(Buffers[BATTLE], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

//	alutLoadWAVFile("wavdata/Gun1.wav", &format, &data, &size, &freq, &loop);
//	alBufferData(Buffers[GUN1], format, data, size, freq);
//	alutUnloadWAV(format, data, size, freq);

//	alutLoadWAVFile("wavdata/Gun2.wav", &format, &data, &size, &freq, &loop);
//	alBufferData(Buffers[GUN2], format, data, size, freq);
//	alutUnloadWAV(format, data, size, freq);

	// Bind buffers into audio sources.
	alGenSources(NUM_SOURCES, Sources);

	if(alGetError() != AL_NO_ERROR) return AL_FALSE;

	alSourcei (Sources[BATTLE], AL_BUFFER,   Buffers[BATTLE]   );
	alSourcef (Sources[BATTLE], AL_PITCH,    1.0f              );
	alSourcef (Sources[BATTLE], AL_GAIN,     1.0f              );
	alSourcefv(Sources[BATTLE], AL_POSITION, SourcesPos[BATTLE]);
	alSourcefv(Sources[BATTLE], AL_VELOCITY, SourcesVel[BATTLE]);
	alSourcei (Sources[BATTLE], AL_LOOPING,  AL_TRUE           );

	alSourcei (Sources[GUN1], AL_BUFFER,   Buffers[GUN1]   );
	alSourcef (Sources[GUN1], AL_PITCH,    1.0f            );
	alSourcef (Sources[GUN1], AL_GAIN,     1.0f            );
	alSourcefv(Sources[GUN1], AL_POSITION, SourcesPos[GUN1]);
	alSourcefv(Sources[GUN1], AL_VELOCITY, SourcesVel[GUN1]);
	alSourcei (Sources[GUN1], AL_LOOPING,  AL_FALSE        );

	alSourcei (Sources[GUN2], AL_BUFFER,   Buffers[GUN2]   );
	alSourcef (Sources[GUN2], AL_PITCH,    1.0f            );
	alSourcef (Sources[GUN2], AL_GAIN,     1.0f            );
	alSourcefv(Sources[GUN2], AL_POSITION, SourcesPos[GUN2]);
	alSourcefv(Sources[GUN2], AL_VELOCITY, SourcesVel[GUN2]);
	alSourcei (Sources[GUN2], AL_LOOPING,  AL_FALSE        );

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

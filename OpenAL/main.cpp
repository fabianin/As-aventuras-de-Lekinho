#include "OpenAL.h"

int main(int argc, char *argv[]){
	// Initialize OpenAL and clear the error bit.
	alutInit(NULL, 0);
	alGetError();

	// Load the wav data.
	if(LoadALData() == AL_FALSE) return 0;

	SetListenerValues();

	//Setup an exit procedure.
	//atexit(KillALData);
	//Begin the battle sample to play.
	//alSourcePlay(Sources[BATTLE]);
  	alSourcePlay(Sources[BATTLE]);
 
	return 0;
}

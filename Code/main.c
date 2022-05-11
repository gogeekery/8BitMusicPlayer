// 2012 Warren Scott
// One 8-bit style music
#include <windows.h>
#include <mmsystem.h>

#include <stdio.h>
#include <stdlib.h>



// Note Defines =========
// ========================

#define	A1		55
#define	A2		110
#define	A3		220
#define	A4		440
#define	A5		880
#define	A6		1760
#define	A7		3520
#define	A8		7040

#define	Bb1		29
#define	Bb2		58
#define	Bb3		116
#define	Bb4		233
#define	Bb5		466
#define	Bb6		932
#define	Bb7		1865
#define	Bb8		3729

#define As1		Bb1
#define As2		Bb2
#define As3		Bb3
#define As4		Bb4
#define As5		Bb5
#define As6		Bb6
#define As7		Bb7
#define As8		Bb8

#define	B1		62
#define	B2		123
#define	B3		247
#define	B4		494
#define	B5		988
#define	B6		1976
#define	B7		3951
#define B8		7459

#define	C1		33
#define	C2		65
#define	C3		131
#define	C4		262
#define	C5		523
#define	C6		1047
#define	C7		2093
#define	C8		4186

#define	Db1		35
#define	Db2		69
#define	Db3		139
#define	Db4		277
#define	Db5		554
#define	Db6		1109
#define	Db7		2218
#define	Db8		4435

#define	Cs1		Db1
#define	Cs2		Db2
#define	Cs3		Db3
#define	Cs4		Db4
#define	Cs5		Db5
#define	Cs6		Db6
#define	Cs7		Db7
#define	Cs8		Db8

#define	D1		37
#define	D2		73
#define	D3		147
#define	D4		294
#define	D5		587
#define	D6		1175
#define	D7		2350
#define	D8		4699

#define	Eb1		39
#define	Eb2		78
#define	Eb3		156
#define	Eb4		311
#define	Eb5		622
#define	Eb6		1245
#define	Eb7		2489
#define	Eb8		4979

#define Ds1		Eb1
#define Ds2		Eb2
#define Ds3		Eb3
#define Ds4		Eb4
#define Ds5		Eb5
#define Ds6		Eb6
#define Ds7		Eb7
#define Ds8		Eb8

#define	E1		41
#define	E2		82
#define	E3		165
#define	E4		330
#define	E5		659
#define	E6		1319
#define	E7		2638
#define	E8		5275

#define	F1		44
#define	F2		87
#define	F3		175
#define	F4		349
#define	F5		699
#define	F6		1397
#define	F7		2795
#define	F8		5589

#define	Gb1		46
#define	Gb2		92
#define	Gb3		185
#define	Gb4		370
#define	Gb5		740
#define	Gb6		1480
#define	Gb7		2961
#define	Gb8		5922

#define Fs1		Gb1
#define Fs2		Gb2
#define Fs3		Gb3
#define Fs4		Gb4
#define Fs5		Gb5
#define Fs6		Gb6
#define Fs7		Gb7
#define Fs8		Gb8


#define	G1		49
#define	G2		98
#define	G3		196
#define	G4		392
#define	G5		784
#define	G6		1568
#define	G7		3137
#define	G8		6274

#define	Ab1		52
#define	Ab2		104
#define	Ab3		208
#define	Ab4		415
#define	Ab5		831
#define	Ab6		1662
#define	Ab7		3324
#define	Ab8		6647

#define Gs1		Ab1
#define Gs2		Ab2
#define Gs3		Ab3
#define Gs4		Ab4
#define Gs5		Ab5
#define Gs6		Ab6
#define Gs7		Ab7
#define Gs8		Ab8

#define Ps		1	// Pause

// ----------------------------




// Type Defines ======
// =====================

#define U8	unsigned char
#define U16	unsigned short
#define U32 unsigned long
#define U64 unsigned long long

#define S8	signed char
#define S16	signed short
#define S32 signed long
#define S64 signed long long




// Data Container ======
// =======================


#define BitsPerS	8//16

#define cBlockSize	2	// Notes per block
//#define cBlockNum	2//8//4	// Num of blocks to stack on the queue


#define BPM			120//160							// Beats Per Minute
#define SPS			44100								// Samples Per Second
#define BPS			(((60*SPS)/BPM)*(BitsPerS/8))		// Beats Per Sample



// The song length MUST be divisable by cBlockSize,
// cBlockSize*cBlockNum MUST be less then the song!



// Song Data =======
// ===================

//static CRITICAL_SECTION waveCriticalSection;

WAVEHDR			WaveHeader[2];
HWAVEOUT		hWaveOut;          // Handle to sound card output
WAVEFORMATEX	WaveFormat;        // The sound format



U8 CurNote = 0;	// Position withing song data (for streaming)
U8 CurWave = 0;	// Current Block...

char* WaveData[2];
U32 DataLen[2];


struct {

	const U16 Freq;
	const U8 Len;

} SongData[] = {	// All this (minus the last note) makes it to 4 seconds!
/*
	{1480, 4},	// SMB3 - 240 BPM
	{1568, 4}, 
	{1568, 4}, 
	{1568, 4},
	{740, 4}, 
	{784, 4}, 
	{784, 4}, 
	{784, 4},
	{370, 4}, 
	{392, 4}, 
	{370, 4}, 
	{392, 4}, 
	{392, 4}, 
	{196, 4},
	{Ps, 1},
*/

	// Tantegel Castle

	{A4, 8},
	{E6, 8},	{D6, 8},	{E6, 8},	{C6, 8},	{E6, 8},	{B5, 8},	{E6, 8},	{A5, 8},
	{A4, 8},	{C5, 8},	{E5, 8},	{A5, 8},	{G5, 8},	{F5, 8},	{E5, 8},	{D5, 8},

	{F6, 8},	{E6, 8},	{F6, 8},	{D6, 8},	{F6, 8},	{C6, 8},	{F6, 8},	{B5, 8},
	{E5, 8},	{Gs5, 8},	{B5, 8},	{E6, 8},	{E5, 8},	{Fs5, 8},	{Gs5, 8},	{A5, 8},

	{G6, 8},	{F6, 8},	{G6, 8},	{E6, 8},	{G6, 8},	{Cs6, 8},
	{G6, 8},	{F6, 8},	{A5, 8},	{G6, 8},	{A5, 8},	{A6, 8},
	{A5, 8},	{G6, 8},	{F6, 8},	{E6, 8},
	{G5, 8},	{C6, 8},	{E6, 8},	{D6, 8},	{G5, 8},	{Ds6, 8},

	{G5, 8},	{E6, 8},	{E5, 8},	{Gs5, 8},
	{B5, 8},	{E6, 8},	{D6, 8},	{C6, 8},	{B5, 8},


	{A4, 8},
	{A6, 16},	{Gs6, 16},	{A6, 8},
	{E6, 16},	{Ds6, 16},	{E6, 8},
	{C6, 16},	{B5, 16},	{C6, 8},
	{A5, 8},

	{G4, 8},
	{A6, 16},	{Gs6, 16},	{A6, 8},
	{E6, 16},	{Ds6, 16},	{E6, 8},
	{C6, 16},	{B5, 16},	{C6, 8},
	{A5, 8},


	{B5, 8},	{G5, 8},	{C6, 8},
	{G5, 8},	{F6, 8},	{A5, 8},
	{C6, 8},	{A5, 8},	{E6, 8},
	{E5, 8},	{Gs5, 8},	{B5, 8},
	{E6, 8},	{G5, 8},	{Cs6, 8},
	{E6, 8},


	{D5, 8},
	{A6, 16},	{Gs6, 16},	{A6, 8},
	{F6, 16},	{E6, 16},	{F6, 8},
	{D6, 16},	{Cs6, 16},	{D6, 8},
	{A5, 8},

	{C5, 8},
	{A6, 16},	{Gs6, 16},	{A6, 8},
	{F6, 16},	{E6, 16},	{F6, 8},
	{D6, 16},	{Cs6, 16},	{D6, 8},
	{A5, 8},


	{B5, 8},	{G5, 8},	{C6, 8},
	{G5, 8},	{F6, 8},	{A5, 8},
	{C6, 8},	{F6, 8},	{E6, 8},
	{A5, 8},	{Gs5, 8},	{F5, 8},
	{E5, 8},	{D5, 8},	{C5, 8},
	{B4, 8},

	{Ps, 1},

	// Tetris

	{E5,4},		{B4,8},		{C5,8},		{D5,4},		{C5,8},		{B4,8},
	{A4,4},		{A4,8},		{C5,8},		{E5,4},		{D5,8},		{C5,8},
	{B4,4},		{C5,8},		{D5,4},		{E5,4},
	{C5,4},		{A4,4},		{A4,8},		{A4,8},		{B4,8},		{C5,8},

	{D5,4},		{F5,8},		{A5,4},		{G5,8},		{F5,8},
	{E5,4},		{C5,8},		{E5,4},		{D5,8},		{C5,8},
	{B4,4},		{B4,8},		{C5,8},		{D5,4},		{E5,4},
	{C5,4},		{A4,4},		{A4,4},		{Ps,4},

	{E5,2},		{C5,2},		{D5,2},		{B4,2},		{C5,2},		{A4,2},
	{Ab4,2},	{B4,4},		{Ps,4},		{E5,2},		{C5,2},		{D5,2},
	{B4,2},		{C5,4},		{E5,4},		{A5,2},		{Ab5,2},

	{Ps,1}

};


void AddNotes() {

	U16 Pos;
	U32 TempLen = 0;
	char* TempData;

	for (Pos = 0; Pos < cBlockSize; ++Pos)	// Get the size of the new data!
		TempLen += (U16)(BPS*(4/(double)SongData[CurNote+Pos].Len));

	TempData = (char*)malloc(TempLen);


	U16 Note;
	S8 Amp = 16;
	U32 DataPos = 0;

#if 1
	// Square Wave
	for (Note = 0; Note < cBlockSize; ++Note) {

		Amp = 16;
		for (Pos = 0; Pos < (U16)(BPS*(4/(double)SongData[CurNote+Note].Len)); ++Pos) {

			TempData[DataPos++] = 128+Amp;

			if (!(Pos % (U16)(SPS/(double)SongData[CurNote+Note].Freq)))	// SPS (Samples Per Second)
				Amp = -Amp;

		}

	}
#else

	// Saw Wave
	for (Note = 0; Note < cBlockSize; ++Note) {

		Amp = 0;
		for (Pos = 0; Pos < (U16)(BPS*(4/(double)SongData[CurNote+Note].Len)); ++Pos) {

			TempData[DataPos++] = 128+Amp;

			Amp += (U8)(((double)SongData[CurNote+Note].Freq/SPS)*127);
			if (!(Pos % (U16)(SPS/(double)SongData[CurNote+Note].Freq)))	// SPS (Samples Per Second)
				Amp = 0;

		}

	}
#endif


	while (!(WaveHeader[CurWave].dwFlags & WHDR_DONE))	// Wait until it is free
		Sleep(1);


	if (WaveHeader[CurWave].dwFlags & WHDR_PREPARED) {
		waveOutUnprepareHeader(hWaveOut, &WaveHeader[CurWave], sizeof(WAVEHDR));
		free(WaveData[CurWave]);	// Free the old Data!
	}


	WaveData[CurWave] = TempData;
	DataLen	[CurWave] = TempLen;

}



// Adds a beep to the sound buffer! (Freq, Starting Position, Length of Beep)
void PlayNotes() {

	WaveHeader[CurWave].lpData			= WaveData[CurWave];
	WaveHeader[CurWave].dwBufferLength	= DataLen [CurWave];

	waveOutPrepareHeader(hWaveOut, &WaveHeader[CurWave], sizeof(WAVEHDR));
	waveOutWrite		(hWaveOut, &WaveHeader[CurWave], sizeof(WAVEHDR));

	CurWave = !CurWave;//(CurWave+1)%cBlockNum;

}


int main() {

{

	U8 Pos;

	// Init the sound format for the Waveform
	WaveFormat.wFormatTag		= WAVE_FORMAT_PCM;		// Uncompressed sound format
	WaveFormat.nChannels		= 1;					// Mono, Stereo
	WaveFormat.wBitsPerSample	= BitsPerS;				// Bits per sample per channel
	WaveFormat.nSamplesPerSec	= SPS;					// Sample Per Second

	WaveFormat.nBlockAlign		= WaveFormat.nChannels * (BitsPerS/8);
	WaveFormat.nAvgBytesPerSec	= BitsPerS * WaveFormat.nBlockAlign;
	WaveFormat.cbSize			= 0;


	WaveHeader[0].dwFlags = WHDR_DONE;
	WaveHeader[0].dwLoops = 0;
	WaveHeader[1].dwFlags = WHDR_DONE;
	WaveHeader[1].dwLoops = 0;


	waveOutOpen(&hWaveOut, WAVE_MAPPER, &WaveFormat, /*(DWORD_PTR)CallBack*/0, 0, CALLBACK_NULL/*FUNCTION*/);


	AddNotes();
	CurNote += cBlockSize;

}

	for (;;) {

		PlayNotes();
		AddNotes();	// Add the (next) notes to be played to CurPos/Wave!

		CurNote = (CurNote+cBlockSize)%(sizeof(SongData)/sizeof(SongData[0]));

	}


	waveOutClose(hWaveOut);

	return 0;

}

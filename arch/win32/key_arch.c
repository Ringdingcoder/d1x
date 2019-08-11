#include "winhdr.h"
#include <stdio.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
//#include "inferno.h"
#include "fix.h"
#include "timer.h"
#include "key.h"

extern void PumpMessages(void);

// These are to kludge up a bit my slightly broken GCC directx port.
#ifndef E_FAIL
#define E_FAIL (HRESULT)0x80004005L
#endif
#ifndef SUCCEEDED
#define SUCCEEDED(a) ((HRESULT)(a) >= 0)
#endif
#ifndef S_OK
#define S_OK 0
#define S_FALSE 1
#endif

extern void PumpMessages(void);

unsigned char WMKey_Handler_Ready=0;


LPDIRECTINPUT g_lpdi;
LPDIRECTINPUTDEVICE g_lpdidKeybd;
extern HWND g_hWnd;

typedef int KEYCODE;

static BOOL EnsureInit (void)
{
	if (g_lpdidKeybd == NULL)
	{
		key_init ();
	}

	return g_lpdidKeybd != NULL;
}

void arch_key_init()
{
	HRESULT hr;

	keyd_fake_repeat=1;//direct input doesn't repeat. -MPM

	hr = CoCreateInstance(&CLSID_DirectInput, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectInput7, &g_lpdi);
	if (SUCCEEDED (hr))
	{
		if (SUCCEEDED(hr = IDirectInput7_Initialize(g_lpdi, GetModuleHandle(NULL), DIRECTINPUT_VERSION))
			&& SUCCEEDED (hr = IDirectInput7_CreateDevice (g_lpdi, (void *)&GUID_SysKeyboard, &g_lpdidKeybd, NULL)))
		{
			DIPROPDWORD dipdw;

			dipdw.diph.dwSize = sizeof (DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof (DIPROPHEADER);
			dipdw.diph.dwObj = 0;
			dipdw.diph.dwHow = DIPH_DEVICE;
			dipdw.dwData = 40;

			if (SUCCEEDED (hr = IDirectInputDevice7_SetDataFormat (g_lpdidKeybd, &c_dfDIKeyboard)) &&
								SUCCEEDED (hr = IDirectInputDevice7_SetCooperativeLevel (g_lpdidKeybd, g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)) &&
				SUCCEEDED (hr = IDirectInputDevice7_SetProperty (g_lpdidKeybd, DIPROP_BUFFERSIZE, &dipdw.diph)) &&
				SUCCEEDED (hr = IDirectInputDevice7_Acquire (g_lpdidKeybd)))
			{
				// fine
				WMKey_Handler_Ready = 1;

			}
			else
			{
				IDirectInputDevice7_Release (g_lpdidKeybd);
				g_lpdidKeybd = NULL;
			}
		}
	}
}

void arch_key_close(void)
{
	WMKey_Handler_Ready = 0;
	if (g_lpdidKeybd != NULL)
	{
		IDirectInputDevice7_Unacquire (g_lpdidKeybd);
		IDirectInputDevice7_Release (g_lpdidKeybd);
		g_lpdidKeybd = NULL;
	}
	if (g_lpdi != NULL)
	{
		IDirectInput7_Release (g_lpdi);
		g_lpdi = NULL;
	}
}

HRESULT ReadKey (DIDEVICEOBJECTDATA *pdidod)
{
	DWORD cElements = 1;
	HRESULT hr;
	if (g_lpdidKeybd == NULL)
		return E_FAIL;
	hr = IDirectInputDevice7_Acquire (g_lpdidKeybd);
	if (SUCCEEDED (hr))
	{
		hr = IDirectInputDevice7_GetDeviceData (
			g_lpdidKeybd,
			sizeof (*pdidod),
			pdidod,
			&cElements,
			0);
		if (SUCCEEDED (hr) && cElements != 1)
			hr = E_FAIL;
	}

	return hr;
}

void UpdateState (DIDEVICEOBJECTDATA *pdidod)
{
	generic_key_handler(pdidod->dwOfs,(pdidod->dwData & 0x80));
}

void keyboard_handler()
{
//        static int peekmsgcount = 0;
	DIDEVICEOBJECTDATA didod;
	while (SUCCEEDED (ReadKey (&didod)))
	{
		UpdateState (&didod);
		
		//added 02/20/99 by adb to prevent message overflow
		//(this should probably go somewhere else...)
//              if (++peekmsgcount == 64) // 64 = wild guess...
//              {
//                      peekmsgcount = 0;
//              }
		//end additions
	}
	PumpMessages();
}



void arch_key_flush()
{
	if (EnsureInit ())
	{
		DWORD cElements = INFINITE;
//                HRESULT hr =
		IDirectInputDevice7_GetDeviceData (
			g_lpdidKeybd,
			sizeof (DIDEVICEOBJECTDATA),
			NULL,
			&cElements,
			0);

	}
}



void arch_key_poll(void)
{
	keyboard_handler();
}

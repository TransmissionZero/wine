/*
 * GDI initialization code
 */

#include "windef.h"
#include "wingdi.h"
#include "wine/winbase16.h"

#include "gdi.h"
#include "global.h"
#include "tweak.h"
#include "win16drv.h"
#include "winbase.h"

/***********************************************************************
 *           GDI initialisation routine
 */
BOOL WINAPI MAIN_GdiInit(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    HINSTANCE16 instance;

    if ( GDI_HeapSel ) return TRUE;

    /* Create GDI heap */
    if ((instance = LoadLibrary16( "GDI.EXE" )) < 32) return FALSE;
    GDI_HeapSel = GlobalHandleToSel16( instance );

    if (!TWEAK_Init()) return FALSE;

    /* GDI initialisation */
    if(!GDI_Init()) return FALSE;

    /* Create the Win16 printer driver */
    if (!WIN16DRV_Init()) return FALSE;

    /* PSDRV initialization */
    if (!LoadLibraryA( "wineps" )) return FALSE;

    return TRUE;
}


/***********************************************************************
 *           Copy   (GDI.250)
 */
void WINAPI Copy16( LPVOID src, LPVOID dst, WORD size )
{
    memcpy( dst, src, size );
}

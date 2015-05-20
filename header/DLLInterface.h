

#ifndef _DLLINTERFACE_
#define _DLLINTERFACE_
 
#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT// __declspec (dllimport)
#endif /* Not BUILDING_DLL */
 

#ifdef __cplusplus

extern "C" {
#endif

DLLIMPORT void startCAM();
 
DLLIMPORT void stopCAM();

DLLIMPORT void pauseTrack();

DLLIMPORT void setIndexCAM(int index);

DLLIMPORT void setScreenSize(int width, int height);

DLLIMPORT int getLeftGazeX();

DLLIMPORT int getLeftGazeY();

DLLIMPORT int getLeftBlink();

DLLIMPORT int getRightGazeX();

DLLIMPORT int getRightGazeY();

DLLIMPORT int getRightBlink();

DLLIMPORT double getTeethArcLength();

DLLIMPORT double getTeethAreaContour();

DLLIMPORT bool isTracking();

DLLIMPORT void clearTracking();

DLLIMPORT void setSensibility(int n);

DLLIMPORT int getGazeHH();

DLLIMPORT int getGazeMM();

DLLIMPORT int getGazeSS();

DLLIMPORT int getMouthHH();

DLLIMPORT int getMouthMM();

DLLIMPORT int getMouthSS();

DLLIMPORT int getLostCount();

DLLIMPORT double getFPS();

#ifdef __cplusplus
}

#endif
#endif

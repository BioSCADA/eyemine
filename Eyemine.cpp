// Eyemine.cpp : Defines the entry point for the console application.
//
/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library  
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
//
                     For Open Source Biosignal SCADA
//
// Copyright (C) 2010, Diego Schmaedech, all rights reserved.
//
// Third party copyrights are property of their respective owners.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/


#include "cv.h"
#include "highgui.h"
#include "Demand.h"
#include <stdio.h>
#include <stdlib.h> 
#include "IOGlobals.h"
#include "TrackerDetector.h"
#include "MultiCamera.h"
#include "DLLInterface.h"
#include "JavaStartInterface.h"
#include "FaceHeuristics.h"
#include "FaceDetect.h" 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>

#define CV_NO_BACKWARD_COMPATIBILITY

TrackerDetector trackerDetector;
MultiCamera multiCamera;
char winName[] = "Eyemine Tracking";
JavaStartInterface javaStartInterface;
double loopTime = 0;
double somaLoopTime = 0;
int nFrames = 0;
int fps = 0;
CvRect initPoint;
FILE *ofp;
char *timestamp;

struct timeb tbi, tbf;


void mainWrapper();

void mouseHandler(int event, int x, int y, int flags, void *param) {

    switch (event) {
        case CV_EVENT_LBUTTONDOWN:
            initPoint = cvRect(cvRound(multiCamera.GetFrameWidth() / 2 - 10), cvRound(multiCamera.GetFrameHeight() / 2 - 10), 20, 20);
            if (x > initPoint.x && x < initPoint.x + initPoint.width && y > initPoint.y && y < initPoint.y + initPoint.height) {
                javaStartInterface.SetStart(true);
            }
            break;
        case CV_EVENT_RBUTTONDOWN:
            trackerDetector.lostTracking();
            javaStartInterface.SetStart(false);
            break;
    }

}

DLLIMPORT void startCAM() {
    mainWrapper();
}

DLLIMPORT void stopCAM() {
    javaStartInterface.SetStop(true);
}

DLLIMPORT void pauseTrack() {
    trackerDetector.lostTracking();
    javaStartInterface.SetStart(false);
}

DLLIMPORT void setIndexCAM(int index) {
    javaStartInterface.SetIndexCAM(index);
}

DLLIMPORT void setScreenSize(int width, int height) {
    javaStartInterface.SetScreenWidth(width);
    javaStartInterface.SetScreenHeight(height);
}

DLLIMPORT int getLeftGazeX() {
    return FaceHeuristics::GazeLeftX;
}

DLLIMPORT int getLeftGazeY() {
    return FaceHeuristics::GazeLeftY;
}

DLLIMPORT int getLeftBlink() {
    return FaceHeuristics::GazeLeftBlink;
}

DLLIMPORT int getRightGazeX() {
    return FaceHeuristics::GazeRightX;
}

DLLIMPORT int getRightGazeY() {
    return FaceHeuristics::GazeRightY;
}

DLLIMPORT int getRightBlink() {
    return FaceHeuristics::GazeRightBlink;
}

DLLIMPORT double getTeethArcLength() {
    return MouthContours::TeethArcLength;
}

DLLIMPORT double getTeethAreaContour() {
    return MouthContours::TeethAreaContour;
}

DLLIMPORT bool isTracking() {
    return javaStartInterface.IsStart();
}

DLLIMPORT void setSensibility(int sens) {
    javaStartInterface.SetSensibility(sens);
}

DLLIMPORT int getGazeHH() {
    return FaceHeuristics::GazeHH;
}

DLLIMPORT int getGazeMM() {
    return FaceHeuristics::GazeMM;
}

DLLIMPORT int getGazeSS() {
    return FaceHeuristics::GazeSS;
}

DLLIMPORT int getMouthHH() {
    return MouthContours::MouthHH;
}

DLLIMPORT int getMouthMM() {
    return MouthContours::MouthMM;
}

DLLIMPORT int getMouthSS() {
    return MouthContours::MouthSS;
}

DLLIMPORT int getLostCount() {
    return TrackerDetector::lostCount;
}

DLLIMPORT double getFPS() {
    return fps;
}

void mainWrapper() {
    (void) ftime(&tbi);
    (void) ftime(&tbf);

    // ESSE � O MILAGRE
    timestamp = ctime(&tbi.time);

    printf("%.19s.%hu %s", timestamp, tbi.millitm, &timestamp[20]);

    multiCamera.setup(javaStartInterface.GetIndexCAM());
    cvNamedWindow(winName, CV_WINDOW_AUTOSIZE);
    cvSetMouseCallback(winName, mouseHandler, NULL);
    ofp = fopen("log.txt", "w");
    fprintf(ofp, "timestamp\tfps\tLeftGazeX\tLeftGazeY\tRightGazeX\tRightGazeY\tLeftBlink\tRightBlink\t\n");
    int freio = 0;
    for (;;) {

        nFrames++;
        double t = (double) cvGetTickCount();

        if (multiCamera.queryFrame() == 0)
            continue;


        CvPoint startPoint = cvPoint(cvRound(multiCamera.GetFrameWidth() / 2), cvRound(multiCamera.GetFrameHeight() / 2));

        if (javaStartInterface.IsStart()) {
            //double t = (double)cvGetTickCount();
            trackerDetector.execute(multiCamera.GetFrame());
            //t = (double)cvGetTickCount() - t;
            //printf( "%g\n",  t/((double)cvGetTickFrequency()*1000.) );
            //printf( "%d\n", FaceHeuristics::GazeLeftX );
            cvCircle(multiCamera.GetFrame(), startPoint, 10, CV_RGB(255, 255, 255), 0);
            fprintf(ofp, "%g\t%g\t%d\t%d\t%d\t%d\t%d\t%d\t\n", t / ((double) cvGetTickFrequency()*1000.), getFPS(), getLeftGazeX(), getLeftGazeY(), getRightGazeX(), getRightGazeY(), getLeftBlink(), getRightBlink());
        } else {
            cvCircle(multiCamera.GetFrame(), startPoint, 10, CV_RGB(255, 255, 255), -1);

        }
        if ((cvWaitKey(10) & 255) == 27)
            freio = 1; //break;  //Test for Escape-key press 
        if (javaStartInterface.IsStop())
            freio = 1; //break; 

        if (javaStartInterface.GetScreenWidth() > 0)
            cvMoveWindow(winName, cvRound(javaStartInterface.GetScreenWidth() / 2 - multiCamera.GetFrameWidth() / 2), cvRound(javaStartInterface.GetScreenHeight() / 2 - multiCamera.GetFrameHeight() / 2));

        //cvSmooth( multiCamera.GetFrame()  , BiFrame , CV_BILATERAL, 5, 5, sigma, sigma);
        cvShowImage(winName, multiCamera.GetFrame());

        t = (double) cvGetTickCount() - t;
        loopTime = t / ((double) cvGetTickFrequency()*1000.);
        somaLoopTime += loopTime;
        if (somaLoopTime > 1000) {
            fps = nFrames;
            //printf( "%g\n", getFPS() );
            nFrames = 0;
            somaLoopTime = 0;
        }

        if (freio) {
            //break;
        }
    }

    fclose(ofp);
    cvDestroyWindow(winName);
    exit(0);
}

int main(int argc, char** argv) {

    mainWrapper();
    return 0;
}


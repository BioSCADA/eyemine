/* 
 * File:   TrackerDetector.h
 * Author: diego
 *
 * Created on May 26, 2010, 6:11 PM
 */
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
// Copyright (C) 2010, Laboratório de Educação Cerebral, all rights reserved.
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
#ifndef _TRACKERDETECTOR_H
#define	_TRACKERDETECTOR_H
#include <cv.h>
#include "FaceDetect.h"
#include "RightEyeDetect.h"
#include "LeftEyeDetect.h"
#include "MouthDetect.h"
#include "NoseDetect.h"

#include "RightEyeTrack.h"
#include "LeftEyeTrack.h"
#include "MouthTrack.h"
#include "NoseTrack.h"
#include "FaceHeuristics.h"

class TrackerDetector {
public:
    TrackerDetector();
    TrackerDetector(const TrackerDetector& orig);
    virtual ~TrackerDetector();
    virtual void execute(IplImage *img);
    void lostTracking();
    void detectFace(IplImage *frame);
    void detectLeftEye(IplImage *frame);
    void detectRightEye(IplImage *frame);
    void detectMouth(IplImage *frame);
    void detectNose(IplImage *frame);
    void trackLeftEye(IplImage *frame);
    void trackRightEye(IplImage *frame);
    void trackMouth(IplImage *frame);
    void trackNose(IplImage *frame);
    void lostLeftEye( );
    void lostRightEye( );
    void lostMouth( );
    void lostNose( );
    void lostFace();
    void setMouthTracking(bool mouthTracking);
    bool isMouthTracking() const;
    void setNoseTracking(bool noseTracking);
    bool isNoseTracking() const;
    void setLeftEyeTracking(bool leftEyeTracking);
    bool isLeftEyeTracking() const;
    void setRightEyeTracking(bool rightEyeTracking);
    bool isRightEyeTracking() const;
    void setFaceTracking(bool faceTracking);
    bool isFaceTracking() const;
    void setWindowFace(CvRect windowFace);
    CvRect getWindowFace() const;
    void setFaceDetected(bool faceDetected);
    bool isFaceDetected() const;
    void setMouthDetected(bool mouthDetected);
    bool isMouthDetected() const;
    void setNoseDetected(bool noseDetected);
    bool isNoseDetected() const;
    void setLeftEyeDetected(bool leftEyeDetected);
    bool isLeftEyeDetected() const;
    void setRightEyeDetected(bool rightEyeDetected);
    bool isRightEyeDetected() const;
     
    static int lostCount;
private:

    IplImage *pryDownFrame;
    IplImage *pryUpFrame;

    bool rightEyeTracking;
    bool leftEyeTracking;
    bool noseTracking;
    bool mouthTracking;
    bool faceTracking;

    bool rightEyeDetected;
    bool leftEyeDetected;
    bool noseDetected;
    bool mouthDetected;
    bool faceDetected;

    CvRect windowFace;

    FaceHeuristics faceHeuristics;
    FaceDetect faceDetect;
    RightEyeDetect rightEyeDetect;
    LeftEyeDetect leftEyeDetect;
    MouthDetect mouthDetect;
    NoseDetect noseDetect;

    RightEyeTrack rightEyeTrack;
    LeftEyeTrack leftEyeTrack;
    MouthTrack mouthTrack;
    NoseTrack noseTrack;
};

#endif	/* _TRACKERDETECTOR_H */


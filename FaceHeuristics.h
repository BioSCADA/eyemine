/* 
 * File:   FaceHeuristics.h
 * Author: diego schmaedech
 *
 * Created on June 4, 2010, 4:53 PM
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
//                  For Open Source Biosignal SCADA
//
// Copyright (C) 2010, Laboratorio de Educacao Cerebral, all rights reserved.
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
#ifndef _FACEHEURISTICS_H
#define	_FACEHEURISTICS_H
#include <cv.h>
#include <time.h>
#include <time.h>
#include <stdio.h>

class FaceHeuristics {
    
public:

    FaceHeuristics();
    FaceHeuristics(const FaceHeuristics& orig);
    virtual ~FaceHeuristics();
 
    void calcRefAngleEyes();
    void calcTrackAngleEyes();
    void verifyDistances();
     
    void SetTrackPointMouth(CvPoint trackPointMouth);
    CvPoint GetTrackPointMouth() const;
    void SetTrackPointNose(CvPoint trackPointNose);
    CvPoint GetTrackPointNose() const;
    void SetTrackPointRightEye(CvPoint trackPointRightEye);
    CvPoint GetTrackPointRightEye() const;
    void SetTrackPointLeftEye(CvPoint trackPointLeftEye);
    CvPoint GetTrackPointLeftEye() const;
    void SetRefPointMouth(CvPoint refPointMouth);
    CvPoint GetRefPointMouth() const;
    void SetRefPointNose(CvPoint refPointNose);
    CvPoint GetRefPointNose() const;
    void SetRefPointRightEye(CvPoint refPointRightEye);
    CvPoint GetRefPointRightEye() const;
    void SetRefPointLeftEye(CvPoint refPointLeftEye);
    CvPoint GetRefPointLeftEye() const;
    void SetNose(bool nose);
    bool IsNose() const;
    void SetEyes(bool eyes);
    bool IsEyes() const;
    void SetRefAngleEyes(double refAngleEyes);
    double GetRefAngleEyes() const;
    void SetTrackAngleEyes(double trackAngleEyes);
    double GetTrackAngleEyes() const;
    void SetETrackDistanceMouth(double eTrackDistanceMouth);
    double GetETrackDistanceMouth() const;
    void SetETrackDistanceNose(double eTrackDistanceNose);
    double GetETrackDistanceNose() const;
    void SetETrackDistanceEye(double eTrackDistanceEye);
    double GetETrackDistanceEye() const;
    void SetERefDistanceMouth(double eRefDistanceMouth);
    double GetERefDistanceMouth() const;
    void SetERefDistanceNose(double eRefDistanceNose);
    double GetERefDistanceNose() const;
    void SetERefDistanceEye(double eRefDistanceEye);
    double GetERefDistanceEye() const;
    void SetEMaxDistanceEye(double eMaxDistanceEye);
    double GetEMaxDistanceEye() const;
    void SetEMinDistanceEye(double eMinDistanceEye);
    double GetEMinDistanceEye() const;
    void SetMouth(bool mouth);
    bool IsMouth() const;
    void SetEPrevRightGaze(double ePrevRightGaze);
    double GetEPrevRightGaze() const;
    void SetEPrevLeftGaze(double ePrevLeftGaze);
    double GetEPrevLeftGaze() const;
    void SetERightGaze(double eRightGaze);
    double GetERightGaze() const;
    void SetELeftGaze(double eLeftGaze);
    double GetELeftGaze() const;
    static int GazeLeftX;
    static int GazeLeftY;
    static int GazeLeftBlink;
    static int GazeRightX;
    static int GazeRightY;
    static int GazeRightBlink;
    static int GazeHH;
    static int GazeMM;
    static int GazeSS;
private:
    CvPoint refPointLeftEye;
    CvPoint refPointRightEye;
    CvPoint refPointNose;
    CvPoint refPointMouth;
    CvPoint trackPointLeftEye;
    CvPoint trackPointRightEye;
    CvPoint trackPointNose;
    CvPoint trackPointMouth;

    CvPoint gazePointLeftEye;
    CvPoint gazePointRightEye;

    double eRefDistanceEye;
    double eRefDistanceNose;
    double eRefDistanceMouth;
    double eTrackDistanceEye;
    double eTrackDistanceNose;
    double eTrackDistanceMouth;

    double eMinDistanceEye;
    double eMaxDistanceEye;

    double eLeftGaze;
    double eRightGaze;

    double ePrevLeftGaze;
    double ePrevRightGaze; 

    double refAngleEyes;
    double trackAngleEyes;
    bool eyes;
    bool nose;
    bool mouth;
 
};


#endif	/* _FACEHEURISTICS_H */


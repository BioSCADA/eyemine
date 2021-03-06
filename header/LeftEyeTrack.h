/* 
 * File:   LeftEyeTrack.h
 * Author: diego
 *
 * Created on May 25, 2010, 3:16 PM
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
// Copyright (C) 2010, Laborat�rio de Educa��o Cerebral, all rights reserved.
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
#ifndef _LEFTEYETRACK_H
#define	_LEFTEYETRACK_H
#include <cv.h>
#include "LeftContours.h"
class LeftEyeTrack {
    
public:
    virtual void execute(IplImage *img,IplImage* drw);
    void makeTemplate(IplImage *img, CvPoint point, int width, int height);
    LeftEyeTrack();
    LeftEyeTrack(const LeftEyeTrack& orig);
    virtual ~LeftEyeTrack();
    void setResultPoint(CvPoint resultPoint);
    CvPoint getResultPoint() const;
    void setTracking(bool tracking);
    bool isTracking() const;
    void setTemplPoint(CvPoint templPoint);
    CvPoint getTemplPoint() const;
    void setLeftEyeBoxHeight(int leftEyeBoxHeight);
    int getLeftEyeBoxHeight() const;
    void setLeftEyeBoxWidth(int leftEyeBoxWidth);
    int getLeftEyeBoxWidth() const;
    void setLeftEyeTplHeight(int leftEyeTplHeight);
    int getLeftEyeTplHeight() const;
    void setLeftEyeTplWidth(int leftEyeTplWidth);
    int getLeftEyeTplWidth() const;
private:
    IplImage *imgTempl;
    IplImage *imgResult;
    CvPoint resultPoint;
    CvPoint templPoint;
    bool tracking;
    IplImage *imgLeftContours;
    LeftContours leftContours;
    int leftEyeTplWidth;
    int leftEyeTplHeight;
    int leftEyeBoxWidth;
    int leftEyeBoxHeight;

};

#endif	/* _LEFTEYETRACK_H */


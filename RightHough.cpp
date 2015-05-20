/* 
 * File:   RightHough.cpp
 * Author: susi
 * 
 * Created on 23 de Julho de 2010, 16:12
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
#include "stdafx.h"
#include "RightHough.h"
#include <highgui.h>
#include "Demand.h"
#include "IOGlobals.h"

int param1 = 25, param2 = 25, min_dist = 10;

void RightHough::performHough(IplImage *img){

    
    allocateOnDemand( &storageRightHough );
    cvCvtColor(img, grayRightHough, CV_BGR2GRAY);
    cvSmooth(grayRightHough, grayRightHough, CV_GAUSSIAN, 9, 9);
    cvCanny( grayRightHough, grayRightHough, 70, 70, 3 );
    CvSeq* circles = cvHoughCircles(grayRightHough, storageRightHough, CV_HOUGH_GRADIENT, 2, grayRightHough->height/(min_dist+1), param1+1, param2+1);
    int i;

    for (i = 0; i < circles->total; i++) {
         float* p = (float*)cvGetSeqElem( circles, i );
         cvCircle( img, cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
         cvCircle( img, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
    }
    
    cvShowImage( "right eye", img);
    cvClearMemStorage( storageRightHough );
} 

RightHough::RightHough() {
    this->grayRightHough = 0;
    this->storageRightHough = 0;
    cvNamedWindow( "right eye", 600 );
    cvCreateTrackbar( "param1", "right eye", &param1, 500, 0 );
    cvCreateTrackbar( "param2", "right eye", &param2, 500, 0 );
    cvCreateTrackbar( "min_dist", "right eye", &min_dist, 10, 0 );
    allocateOnDemand( &grayRightHough, cvSize( EYE_BOX_WIDTH, EYE_BOX_HEIGHT ), IPL_DEPTH_8U, 1 );
}

RightHough::RightHough(const RightHough& orig) {
}

RightHough::~RightHough() {
    if(CV_IS_STORAGE(storageRightHough)){
        cvReleaseMemStorage( &storageRightHough );
    }
}


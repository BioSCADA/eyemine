/*
 * File:   RightContours.cpp
 * Author: diego
 *
 * Created on June 7, 2010, 11:24 PM
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
#include "stdafx.h"
#include "RightContours.h"
#include "Demand.h"
#include <stdio.h>
#include <time.h>
#include "IOGlobals.h"
#include <highgui.h>

void RightContours::execute(IplImage* img){

    CvSeq* contours;
    allocateOnDemand( &storageRightContours );
    allocateOnDemand( &grayRightContours, cvSize( img->width, img->height ), IPL_DEPTH_8U, 1 );
    cvCvtColor(img, grayRightContours, CV_BGR2GRAY);

    if(CV_IS_STORAGE((storageRightContours))){
        contours = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvContour), sizeof(CvPoint), storageRightContours );

        int sigma = 1;
        int ksize = (sigma*5)|1;

        cvSmooth( grayRightContours , grayRightContours, CV_GAUSSIAN, ksize, ksize, sigma, sigma);
        //cvEqualizeHist( small_img_grey, small_img_grey );
        cvCanny( grayRightContours, grayRightContours, 100, 100, 3 );

        cvDilate( grayRightContours, grayRightContours, NULL, 1 );
        cvErode( grayRightContours, grayRightContours, NULL, 1 );

        cvFindContours( grayRightContours, storageRightContours, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
        if(CV_IS_SEQ(contours)){
            contours = cvApproxPoly( contours, sizeof(CvContour), storageRightContours, CV_POLY_APPROX_DP, 1, 1 );
            if( contours->total > 0 ){
                for( ;contours; contours = contours->h_next ){
//                    if( contours->total <  4 )
//                        continue;

                    cvDrawContours( img, contours, CV_RGB(0,100,255), CV_RGB(255,255,100), 5, 1, CV_AA, cvPoint(0,0) );
                    RightContours::RightContoursArcLength = cvArcLength(  contours, CV_WHOLE_SEQ, -1);
                    RightContours::RightContoursAreaContour = cvContourArea( contours, CV_WHOLE_SEQ);
                    time_t ltime;
                    struct tm *Tm;
                    ltime=time(NULL);
                    Tm=localtime(&ltime);
                    RightContours::RightContoursHH = Tm->tm_hour;
                    RightContours::RightContoursMM = Tm->tm_min;
                    RightContours::RightContoursSS = Tm->tm_sec;

                }
            }else{
                    RightContours::RightContoursHH = 0;
                    RightContours::RightContoursMM = 0;
                    RightContours::RightContoursSS = 0;
                    RightContours::RightContoursArcLength = 0;
                    RightContours::RightContoursAreaContour = 0;
                }

        }else{
            RightContours::RightContoursHH = 0;
            RightContours::RightContoursMM = 0;
            RightContours::RightContoursSS = 0;
            RightContours::RightContoursArcLength = 0;
            RightContours::RightContoursAreaContour = 0;
        }
        cvNamedWindow( "right eye", CV_WINDOW_AUTOSIZE );
        cvShowImage( "right eye", img);
        cvClearMemStorage( storageRightContours );
        if(CV_IS_IMAGE(grayRightContours)){
            cvReleaseImage(&grayRightContours);
        }
    }
     
}
RightContours::RightContours() {
    this->grayRightContours = 0;
    
    this->storageRightContours = 0;
    
}

RightContours::RightContours(const RightContours& orig) {
}

RightContours::~RightContours() {

    
    if(CV_IS_IMAGE(grayRightContours)){
        cvReleaseImage(&grayRightContours);
    }
    if(CV_IS_STORAGE((storageRightContours))){
        cvReleaseMemStorage( &storageRightContours );
    }
}

double RightContours::RightContoursAreaContour = 0.0;
double RightContours::RightContoursArcLength = 0.0;
int RightContours::RightContoursHH = 0;
int RightContours::RightContoursMM = 0;
int RightContours::RightContoursSS = 0;

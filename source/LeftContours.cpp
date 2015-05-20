/*
 * File:   LeftContours.cpp
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
#include "LeftContours.h"
#include "Demand.h"
#include <stdio.h>
#include <time.h>
#include "IOGlobals.h"
#include <highgui.h>

void LeftContours::execute(IplImage* img){

    CvSeq* contours;
    allocateOnDemand( &storageLeftContours );
    allocateOnDemand( &grayLeftContours, cvSize( img->width, img->height ), IPL_DEPTH_8U, 1 );
    cvCvtColor(img, grayLeftContours, CV_BGR2GRAY);

    if(CV_IS_STORAGE((storageLeftContours))){
        contours = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvContour), sizeof(CvPoint), storageLeftContours );

        int sigma = 1;
        int ksize = (sigma*5)|1;

        cvSmooth( grayLeftContours , grayLeftContours, CV_GAUSSIAN, ksize, ksize, sigma, sigma);
        //cvEqualizeHist( small_img_grey, small_img_grey );
        cvCanny( grayLeftContours, grayLeftContours, 100, 100, 3 );

        cvDilate( grayLeftContours, grayLeftContours, NULL, 1 );
        cvErode( grayLeftContours, grayLeftContours, NULL, 1 );

        cvFindContours( grayLeftContours, storageLeftContours, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
        if(CV_IS_SEQ(contours)){
            contours = cvApproxPoly( contours, sizeof(CvContour), storageLeftContours, CV_POLY_APPROX_DP, 1, 1 );
            if( contours->total > 0 ){
                for( ;contours; contours = contours->h_next ){
//                    if( contours->total <  4 )
//                        continue;

                    cvDrawContours( img, contours, CV_RGB(0,100,255), CV_RGB(255,255,100), 5, 1, CV_AA, cvPoint(0,0) );
                    LeftContours::LeftContoursArcLength = cvArcLength(  contours, CV_WHOLE_SEQ, -1);
                    LeftContours::LeftContoursAreaContour = cvContourArea( contours, CV_WHOLE_SEQ);
                    time_t ltime;
                    struct tm *Tm;
                    ltime=time(NULL);
                    Tm=localtime(&ltime);
                    LeftContours::LeftContoursHH = Tm->tm_hour;
                    LeftContours::LeftContoursMM = Tm->tm_min;
                    LeftContours::LeftContoursSS = Tm->tm_sec;

                }
            }else{
                    LeftContours::LeftContoursHH = 0;
                    LeftContours::LeftContoursMM = 0;
                    LeftContours::LeftContoursSS = 0;
                    LeftContours::LeftContoursArcLength = 0;
                    LeftContours::LeftContoursAreaContour = 0;
                }

        }else{
            LeftContours::LeftContoursHH = 0;
            LeftContours::LeftContoursMM = 0;
            LeftContours::LeftContoursSS = 0;
            LeftContours::LeftContoursArcLength = 0;
            LeftContours::LeftContoursAreaContour = 0;
        }
        cvNamedWindow( "left eye", CV_WINDOW_AUTOSIZE );
        cvShowImage( "left eye", img);
        cvClearMemStorage( storageLeftContours );
        if(CV_IS_IMAGE(grayLeftContours)){
            cvReleaseImage(&grayLeftContours);
        }
    }

}
LeftContours::LeftContours() {
    this->grayLeftContours = 0;
    //cvNamedWindow( "left eye", CV_WINDOW_AUTOSIZE );
    this->storageLeftContours = 0;

}

LeftContours::LeftContours(const LeftContours& orig) {
}

LeftContours::~LeftContours() {


    if(CV_IS_IMAGE(grayLeftContours)){
        cvReleaseImage(&grayLeftContours);
    }
    if(CV_IS_STORAGE((storageLeftContours))){
        cvReleaseMemStorage( &storageLeftContours );
    }
}

double LeftContours::LeftContoursAreaContour = 0.0;
double LeftContours::LeftContoursArcLength = 0.0;
int LeftContours::LeftContoursHH = 0;
int LeftContours::LeftContoursMM = 0;
int LeftContours::LeftContoursSS = 0;

/* 
 * File:   MouthContours.cpp
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
#include "MouthContours.h"
#include "Demand.h"
#include <stdio.h>
#include <time.h>

void MouthContours::execute(IplImage* img, IplImage* drw, CvRect mouthSearch){

    CvSeq* contours;
    if(CV_IS_IMAGE(imgGrey)){
        cvReleaseImage(&imgGrey);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }
    allocateOnDemand( &storageTeeth );
    allocateOnDemand( &imgTempl, cvSize( img->width, img->height ), IPL_DEPTH_8U, 3 );
    cvCopy( img,  imgTempl, 0 );
    allocateOnDemand( &imgGrey, cvSize( img->width, img->height ), IPL_DEPTH_8U, 1 );

    if(CV_IS_STORAGE((storageTeeth))){
        contours = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvContour), sizeof(CvPoint), storageTeeth );
        cvCvtColor( imgTempl, imgGrey, CV_BGR2GRAY );
        int sigma = 1;
        int ksize = (sigma*5)|1;
        cvSetImageROI(imgGrey, mouthSearch);
        cvSetImageROI(drw, mouthSearch);

        cvSmooth( imgGrey , imgGrey, CV_GAUSSIAN, ksize, ksize, sigma, sigma);
        //cvEqualizeHist( small_img_grey, small_img_grey );
        cvCanny( imgGrey, imgGrey, 70, 70, 3 );

        cvDilate( imgGrey, imgGrey, NULL, 1 );
        cvErode( imgGrey, imgGrey, NULL, 1 );

        cvFindContours( imgGrey, storageTeeth, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
        if(CV_IS_SEQ(contours)){
            contours = cvApproxPoly( contours, sizeof(CvContour), storageTeeth, CV_POLY_APPROX_DP, 5, 1 ); 
            if( contours->total > 0 ){ 
                for( ;contours; contours = contours->h_next ){
                    if( contours->total <  4 )  
                        continue;     
                                        
                    cvDrawContours( drw, contours, CV_RGB(255,0,0), CV_RGB(0,255,0), 5, 1, CV_AA, cvPoint(0,0) );
                    MouthContours::TeethArcLength = cvArcLength(  contours, CV_WHOLE_SEQ, -1);
                    MouthContours::TeethAreaContour = cvContourArea( contours, CV_WHOLE_SEQ); 
                    time_t ltime;
                    struct tm *Tm;     
                    ltime=time(NULL);
                    Tm=localtime(&ltime); 
                    MouthContours::MouthHH = Tm->tm_hour;
                    MouthContours::MouthMM = Tm->tm_min;
                    MouthContours::MouthSS = Tm->tm_sec; 
                    
                }
            }else{
                    MouthContours::MouthHH = 0;
                    MouthContours::MouthMM = 0;
                    MouthContours::MouthSS = 0; 
                    MouthContours::TeethArcLength = 0;
                    MouthContours::TeethAreaContour = 0;
                }

        }else{
              MouthContours::MouthHH = 0;
                    MouthContours::MouthMM = 0;
                    MouthContours::MouthSS = 0; 
            MouthContours::TeethArcLength = 0;
            MouthContours::TeethAreaContour = 0;
        }
        
        cvClearMemStorage( storageTeeth );
         
    }
    cvResetImageROI(imgGrey);
    cvResetImageROI(drw);
    
}
MouthContours::MouthContours() {
    this->imgGrey = 0;
    this->imgTempl = 0;
    this->storageTeeth = 0;
    
}

MouthContours::MouthContours(const MouthContours& orig) {
}

MouthContours::~MouthContours() {
    
    if(CV_IS_IMAGE(imgGrey)){
        cvReleaseImage(&imgGrey);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }
    if(CV_IS_STORAGE((storageTeeth))){
        cvReleaseMemStorage( &storageTeeth );
    }
}

double MouthContours::TeethAreaContour = 0.0;
double MouthContours::TeethArcLength = 0.0;
int MouthContours::MouthHH = 0;
int MouthContours::MouthMM = 0;
int MouthContours::MouthSS = 0;

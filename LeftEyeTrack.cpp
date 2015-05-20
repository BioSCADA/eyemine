/* 
 * File:   LeftEyeTrack.cpp
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
#include "LeftEyeTrack.h"
#include "IOGlobals.h"
#include "Demand.h"
#include "LeftEyeDetect.h"
#include <cv.h>
#include <highgui.h>

void LeftEyeTrack::makeTemplate(IplImage* frame, CvPoint point, int width, int height){
    setTemplPoint( point );
    setLeftEyeTplWidth(width);
    setLeftEyeTplHeight(height);
    setLeftEyeBoxWidth(width+20);
    setLeftEyeBoxHeight(height+10);
    if(CV_IS_IMAGE(imgResult)){
        cvReleaseImage(&imgResult);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }
    if(CV_IS_IMAGE(imgLeftContours)){
        cvReleaseImage(&imgLeftContours);
    }
    allocateOnDemand( &imgLeftContours, cvSize( getLeftEyeBoxWidth(), getLeftEyeBoxHeight() ), IPL_DEPTH_8U, 3 );
    allocateOnDemand( &imgTempl, cvSize( getLeftEyeTplWidth(), getLeftEyeTplHeight() ), IPL_DEPTH_8U, 3 );
    allocateOnDemand( &imgResult, cvSize( getLeftEyeBoxWidth()  - getLeftEyeTplWidth()  + 1, getLeftEyeBoxHeight() - getLeftEyeTplHeight() + 1 ), IPL_DEPTH_32F, 1 );

    cvSetImageROI( frame, cvRect( getTemplPoint().x, getTemplPoint().y, getLeftEyeTplWidth(), getLeftEyeTplHeight() ) );
    cvCopy( frame,  imgTempl, 0 );
    cvResetImageROI( frame );
    setResultPoint( point );
    setTracking(true);


    //    IplImage *dst_save  = cvCreateImage( cvGetSize(imgTempl), 8, 3 );
//    cvCopy(imgTempl,dst_save,0);
//    cvSaveImage("leftTpl.png" , dst_save );
//    cvReleaseImage( &dst_save );

}

void LeftEyeTrack::execute(IplImage* img, IplImage* drw){
    CvPoint minloc, maxloc;
    double  minval, maxval;
    CvRect leftEyeSearch = cvRect( getLeftEyeTplWidth()/2+getResultPoint().x-getLeftEyeBoxWidth()/2,getLeftEyeTplHeight()/2+ getResultPoint().y-getLeftEyeBoxHeight()/2, getLeftEyeBoxWidth(), getLeftEyeBoxHeight() );
    cvRectangle( drw, cvPoint( leftEyeSearch.x, leftEyeSearch.y ), cvPoint( leftEyeSearch.x + getLeftEyeBoxWidth(), leftEyeSearch.y + getLeftEyeBoxHeight() ), CV_RGB( 255, 255, 0  ), 1, 0, 0 );
    cvSetImageROI( img, leftEyeSearch );
    cvCopy(img,imgLeftContours,0);
    leftContours.execute(imgLeftContours);
    if(leftEyeSearch.x > 0 && leftEyeSearch.y >0 && leftEyeSearch.x < img->width-getLeftEyeBoxWidth() && leftEyeSearch.y < img->height-getLeftEyeBoxHeight()){
        cvMatchTemplate( img, imgTempl, imgResult, CV_TM_SQDIFF_NORMED );
        cvNormalize( imgResult, imgResult, 1, 0, CV_MINMAX);
        cvMinMaxLoc( imgResult, &minval, &maxval, &minloc, &maxloc, 0 );
        cvResetImageROI( img );
        CvPoint minPoint = cvPoint( (leftEyeSearch.x+minloc.x), (leftEyeSearch.y+minloc.y) );
        CvPoint drwPoint = cvPoint( (leftEyeSearch.x+minloc.x)+getLeftEyeTplWidth()/2, (leftEyeSearch.y+minloc.y)+getLeftEyeTplHeight()/2 );
        cvCircle( drw, drwPoint , 2, CV_RGB(255, 255, 255), 0 );
        setResultPoint( minPoint );
        setTracking(true);
    }else{
        cvResetImageROI( img );
        setTracking(false);
    }
     
}

LeftEyeTrack::LeftEyeTrack() {
 
    this->imgResult = 0;
    this->imgTempl = 0;
    this->imgLeftContours = 0;
    this->tracking = false;
    setTemplPoint(cvPoint(0,0));
    setLeftEyeTplWidth(0);
    setLeftEyeTplHeight(0);
    setLeftEyeBoxWidth(0);
    setLeftEyeBoxHeight(0);
}

LeftEyeTrack::LeftEyeTrack(const LeftEyeTrack& orig) {
}

LeftEyeTrack::~LeftEyeTrack() {
    if(CV_IS_IMAGE(imgResult)){
        cvReleaseImage(&imgResult);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }
    
    
}

void LeftEyeTrack::setResultPoint(CvPoint resultPoint) {
    this->resultPoint = resultPoint;
}

CvPoint LeftEyeTrack::getResultPoint() const {
    return resultPoint;
}

void LeftEyeTrack::setTracking(bool tracking) {
    this->tracking = tracking;
}

bool LeftEyeTrack::isTracking() const {
    return tracking;
}

void LeftEyeTrack::setTemplPoint(CvPoint templPoint) {
    this->templPoint = templPoint;
}

CvPoint LeftEyeTrack::getTemplPoint() const {
    return templPoint;
}
void LeftEyeTrack::setLeftEyeBoxHeight(int leftEyeBoxHeight) {
    this->leftEyeBoxHeight = leftEyeBoxHeight;
}
int LeftEyeTrack::getLeftEyeBoxHeight() const {
    return leftEyeBoxHeight;
}
void LeftEyeTrack::setLeftEyeBoxWidth(int leftEyeBoxWidth) {
    this->leftEyeBoxWidth = leftEyeBoxWidth;
}
int LeftEyeTrack::getLeftEyeBoxWidth() const {
    return leftEyeBoxWidth;
}
void LeftEyeTrack::setLeftEyeTplHeight(int leftEyeTplHeight) {
    this->leftEyeTplHeight = leftEyeTplHeight;
}
int LeftEyeTrack::getLeftEyeTplHeight() const {
    return leftEyeTplHeight;
}
void LeftEyeTrack::setLeftEyeTplWidth(int leftEyeTplWidth) {
    this->leftEyeTplWidth = leftEyeTplWidth;
}
int LeftEyeTrack::getLeftEyeTplWidth() const {
    return leftEyeTplWidth;
}


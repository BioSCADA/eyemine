/*
 * File:   RightEyeTrack.cpp
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

#include "RightEyeTrack.h"

#include "IOGlobals.h"
#include "Demand.h"
#include "RightEyeDetect.h"
#include <cv.h>
#include <highgui.h>
#include <math.h> 

void RightEyeTrack::makeTemplate(IplImage* frame, CvPoint point, int width, int height){
    setTemplPoint( point );
    setRightEyeTplWidth(width);
    setRightEyeTplHeight(height);
    setRightEyeBoxWidth(width+20);
    setRightEyeBoxHeight(height+10);
    if(CV_IS_IMAGE(imgResult)){
        cvReleaseImage(&imgResult);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }
    if(CV_IS_IMAGE(imgRightContours)){
        cvReleaseImage(&imgRightContours);
    }
    allocateOnDemand( &imgRightContours, cvSize( getRightEyeBoxWidth(), getRightEyeBoxHeight() ), IPL_DEPTH_8U, 3 );
    allocateOnDemand( &imgTempl, cvSize( getRightEyeTplWidth(), getRightEyeTplHeight() ), IPL_DEPTH_8U, 3 );
    allocateOnDemand( &imgResult, cvSize( getRightEyeBoxWidth()  - getRightEyeTplWidth()  + 1, getRightEyeBoxHeight() - getRightEyeTplHeight() + 1 ), IPL_DEPTH_32F, 1 );
    cvSetImageROI( frame, cvRect( getTemplPoint().x, getTemplPoint().y, getRightEyeTplWidth(), getRightEyeTplHeight() ) );
    cvCopy( frame,  imgTempl, 0 );
    cvResetImageROI( frame );
    setResultPoint( point );
    setTracking(true);
//    IplImage *dst_save  = cvCreateImage( cvGetSize(imgTempl), 8, 3 );
//    cvCopy(imgTempl,dst_save,0);
//    cvSaveImage("rightTpl.png" , dst_save );
//    cvReleaseImage( &dst_save );
}

void RightEyeTrack::execute(IplImage* img, IplImage* drw){
    CvPoint minloc, maxloc;
    double  minval, maxval;

    CvRect rightEyeSearch = cvRect( getRightEyeTplWidth()/2+getResultPoint().x-getRightEyeBoxWidth()/2, getRightEyeTplHeight()/2+ getResultPoint().y-getRightEyeBoxHeight()/2, getRightEyeBoxWidth(), getRightEyeBoxHeight() );
    cvRectangle( drw, cvPoint( rightEyeSearch.x, rightEyeSearch.y ), cvPoint( rightEyeSearch.x + getRightEyeBoxWidth(), rightEyeSearch.y + getRightEyeBoxHeight() ), CV_RGB( 255, 255, 0 ), 1, 0, 0 );
    cvSetImageROI( img, rightEyeSearch );
    cvCopy(img,imgRightContours,0);
    rightContours.execute(imgRightContours);
    if(rightEyeSearch.x > 0 && rightEyeSearch.y >0 && rightEyeSearch.x < img->width-getRightEyeBoxWidth() && rightEyeSearch.y < img->height-getRightEyeBoxHeight()){
        cvMatchTemplate( img, imgTempl, imgResult, CV_TM_SQDIFF_NORMED );
        cvNormalize( imgResult, imgResult, 1, 0, CV_MINMAX);
        cvMinMaxLoc( imgResult, &minval, &maxval, &minloc, &maxloc, 0 );
        cvResetImageROI( img );
        CvPoint minPoint = cvPoint( (rightEyeSearch.x+minloc.x), (rightEyeSearch.y+minloc.y) );
        CvPoint drwPoint = cvPoint( getRightEyeTplWidth()/2+(rightEyeSearch.x+minloc.x), getRightEyeTplHeight()/2+(rightEyeSearch.y+minloc.y) );
        cvCircle( drw, drwPoint , 2, CV_RGB(255, 255, 255), 0 );
        setResultPoint( minPoint );
        setTracking(true);
    }else{
        cvResetImageROI( img );
        setTracking(false);
    } 
    
}

RightEyeTrack::RightEyeTrack() {
    
    this->imgResult = 0;
    this->imgTempl = 0;
    this->imgRightContours = 0;
    this->tracking = false;
    setTemplPoint(cvPoint(0,0));
    setRightEyeTplWidth(0);
    setRightEyeTplHeight(0);
    setRightEyeBoxWidth(0);
    setRightEyeBoxHeight(0);
}

RightEyeTrack::RightEyeTrack(const RightEyeTrack& orig) {
}
RightEyeTrack::~RightEyeTrack() {
    if(CV_IS_IMAGE(imgResult)){
        cvReleaseImage(&imgResult);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }
    if(CV_IS_IMAGE(imgRightContours)){
        cvReleaseImage(&imgRightContours);
    }
}
void RightEyeTrack::setResultPoint(CvPoint resultPoint) {
    this->resultPoint = resultPoint;
}
CvPoint RightEyeTrack::getResultPoint() const {
    return resultPoint;
}
void RightEyeTrack::setTracking(bool tracking) {
    this->tracking = tracking;
}
bool RightEyeTrack::isTracking() const {
    return tracking;
}
void RightEyeTrack::setTemplPoint(CvPoint templPoint) {
    this->templPoint = templPoint;
}
CvPoint RightEyeTrack::getTemplPoint() const {
    return templPoint;
}
void RightEyeTrack::setRightEyeBoxHeight(int RightEyeBoxHeight) {
    this->RightEyeBoxHeight = RightEyeBoxHeight;
}
int RightEyeTrack::getRightEyeBoxHeight() const {
    return RightEyeBoxHeight;
}
void RightEyeTrack::setRightEyeBoxWidth(int RightEyeBoxWidth) {
    this->RightEyeBoxWidth = RightEyeBoxWidth;
}
int RightEyeTrack::getRightEyeBoxWidth() const {
    return RightEyeBoxWidth;
}
void RightEyeTrack::setRightEyeTplHeight(int RightEyeTplHeight) {
    this->RightEyeTplHeight = RightEyeTplHeight;
}
int RightEyeTrack::getRightEyeTplHeight() const {
    return RightEyeTplHeight;
}
void RightEyeTrack::setRightEyeTplWidth(int RightEyeTplWidth) {
    this->RightEyeTplWidth = RightEyeTplWidth;
}
int RightEyeTrack::getRightEyeTplWidth() const {
    return RightEyeTplWidth;
}


/*
 * File:   MouthTrack.cpp
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
#include "MouthTrack.h"
#include "IOGlobals.h"
#include "Demand.h"
#include "MouthDetect.h"
#include <cv.h>
#include <highgui.h>


void MouthTrack::makeTemplate(IplImage* frame, CvPoint point, int width, int height){
    setTemplPoint( point );
    setMouthTplWidth(width);
    setMouthTplHeight(height);
    setMouthBoxWidth(width+10);
    setMouthBoxHeight(height+10);
    if(CV_IS_IMAGE(imgResult)){
        cvReleaseImage(&imgResult);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }
    allocateOnDemand( &imgTempl, cvSize( getMouthTplWidth(), getMouthTplHeight() ), IPL_DEPTH_8U, 3 );
    allocateOnDemand( &imgResult, cvSize( getMouthBoxWidth()  - getMouthTplWidth()  + 1, getMouthBoxHeight() - getMouthTplHeight() + 1 ), IPL_DEPTH_32F, 1 );
    cvSetImageROI( frame, cvRect( getTemplPoint().x, getTemplPoint().y, getMouthTplWidth(), getMouthTplHeight() ) );
    cvCopy( frame,  imgTempl, 0 );
    cvResetImageROI( frame );
    setResultPoint( point );
    setTracking(true);
}

void MouthTrack::execute(IplImage* img,IplImage* drw){

    CvPoint minloc, maxloc;
    double  minval, maxval;
    CvRect mouthSearch = cvRect( getMouthTplWidth()/2+getResultPoint().x-getMouthBoxWidth()/2,getMouthTplHeight()/2+ getResultPoint().y-getMouthBoxHeight()/2, getMouthBoxWidth(), getMouthBoxHeight() );
    cvRectangle( drw, cvPoint( mouthSearch.x, mouthSearch.y ), cvPoint( mouthSearch.x + getMouthBoxWidth(), mouthSearch.y + getMouthBoxHeight() ), CV_RGB( 255, 255, 0 ), 1, 0, 0 );
    cvSetImageROI( img, mouthSearch );
    if(mouthSearch.x > 0 && mouthSearch.y >0 && mouthSearch.x < img->width-getMouthBoxWidth() && mouthSearch.y < img->height-getMouthBoxHeight()){
        cvMatchTemplate( img, imgTempl, imgResult, CV_TM_SQDIFF_NORMED );
        cvNormalize( imgResult, imgResult, 1, 0, CV_MINMAX);
        cvMinMaxLoc( imgResult, &minval, &maxval, &minloc, &maxloc, 0 );
        cvResetImageROI( img );
        CvPoint minPoint = cvPoint( (mouthSearch.x+minloc.x), (mouthSearch.y+minloc.y) );
        //CvRect mouthTpl = cvRect( minPoint.x, minPoint.y, getMouthTplWidth(), getMouthTplHeight() );
        mouthContours.execute( img, drw, mouthSearch );
        CvPoint drwPoint = cvPoint( (mouthSearch.x+minloc.x)+getMouthTplWidth()/2, (mouthSearch.y+minloc.y)+getMouthTplHeight()/2 );
        cvCircle( drw, drwPoint , 2, CV_RGB(255, 255, 255), 0 );
        setResultPoint( minPoint );
        setTracking(true);
    }else{
        cvResetImageROI( img );
        setTracking(false);
    }
}

MouthTrack::MouthTrack() {
    this->imgResult = 0;
    this->imgTempl = 0;
    this->tracking = false;
    setTemplPoint(cvPoint(0,0));
    setMouthTplWidth(0);
    setMouthTplHeight(0);
    setMouthBoxWidth(0);
    setMouthBoxHeight(0);
}

MouthTrack::MouthTrack(const MouthTrack& orig) {
}

MouthTrack::~MouthTrack() {
    if(CV_IS_IMAGE(imgResult)){
        cvReleaseImage(&imgResult);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }

}
void MouthTrack::setResultPoint(CvPoint resultPoint) {
    this->resultPoint = resultPoint;
}
CvPoint MouthTrack::getResultPoint() const {
    return resultPoint;
}
void MouthTrack::setTracking(bool tracking) {
    this->tracking = tracking;
}
bool MouthTrack::isTracking() const {
    return tracking;
}
void MouthTrack::setTemplPoint(CvPoint templPoint) {
    this->templPoint = templPoint;
}
CvPoint MouthTrack::getTemplPoint() const {
    return templPoint;
}
void MouthTrack::setMouthBoxHeight(int mouthBoxHeight) {
    this->mouthBoxHeight = mouthBoxHeight;
}
int MouthTrack::getMouthBoxHeight() const {
    return mouthBoxHeight;
}
void MouthTrack::setMouthBoxWidth(int mouthBoxWidth) {
    this->mouthBoxWidth = mouthBoxWidth;
}
int MouthTrack::getMouthBoxWidth() const {
    return mouthBoxWidth;
}
void MouthTrack::setMouthTplHeight(int mouthTplHeight) {
    this->mouthTplHeight = mouthTplHeight;
}
int MouthTrack::getMouthTplHeight() const {
    return mouthTplHeight;
}
void MouthTrack::setMouthTplWidth(int mouthTplWidth) {
    this->mouthTplWidth = mouthTplWidth;
}
int MouthTrack::getMouthTplWidth() const {
    return mouthTplWidth;
}


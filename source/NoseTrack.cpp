/*
 * File:   NoseTrack.cpp
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
#include "NoseTrack.h"
#include "IOGlobals.h"
#include "Demand.h"
#include "NoseDetect.h"
#include <highgui.h>
#include <stdio.h>

void NoseTrack::makeTemplate(IplImage* frame, CvPoint point, int width, int height){
    setTemplPoint( point );
    setNoseTplWidth(width);
    setNoseTplHeight(height);
    setNoseBoxWidth(width+10);
    setNoseBoxHeight(height+10);
    if(CV_IS_IMAGE(imgResult)){
        cvReleaseImage(&imgResult);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }
    allocateOnDemand( &imgTempl, cvSize( getNoseTplWidth(), getNoseTplHeight() ), IPL_DEPTH_8U, 3 );
    allocateOnDemand( &imgResult, cvSize( getNoseBoxWidth()  - getNoseTplWidth()  + 1, getNoseBoxHeight() - getNoseTplHeight() + 1 ), IPL_DEPTH_32F, 1 );
    cvSetImageROI( frame, cvRect( getTemplPoint().x, getTemplPoint().y, getNoseTplWidth(), getNoseTplHeight() ) );
    cvCopy( frame,  imgTempl, 0 );
    cvResetImageROI( frame );
    setResultPoint( point );
    setTracking(true);
}

void NoseTrack::execute(IplImage* img, IplImage* drw){

    CvPoint minloc, maxloc;
    double  minval, maxval;
    CvRect noseSearch = cvRect( getNoseTplWidth()/2+getResultPoint().x-getNoseBoxWidth()/2,getNoseTplHeight()/2+ getResultPoint().y-getNoseBoxHeight()/2, getNoseBoxWidth(), getNoseBoxHeight() );
    cvRectangle( drw, cvPoint( noseSearch.x, noseSearch.y ), cvPoint( noseSearch.x + noseSearch.width, noseSearch.y + noseSearch.height ), CV_RGB( 255, 255, 0 ), 1, 0, 0 );
    cvSetImageROI( img, noseSearch );
    if(noseSearch.x > 0 && noseSearch.y > 0 && noseSearch.x < img->width-getNoseBoxWidth() && noseSearch.y < img->height-getNoseBoxHeight() ){
        cvMatchTemplate( img, imgTempl, imgResult, CV_TM_SQDIFF_NORMED );
        cvNormalize( imgResult, imgResult, 1, 0, CV_MINMAX );
        cvMinMaxLoc( imgResult, &minval, &maxval, &minloc, &maxloc, 0 );
        cvResetImageROI( img );
        CvPoint minPoint = cvPoint( (noseSearch.x+minloc.x), (noseSearch.y+minloc.y) );
        CvPoint drwPoint = cvPoint( (noseSearch.x+minloc.x)+getNoseTplWidth()/2, (noseSearch.y+minloc.y)+getNoseTplHeight()/2 );
        cvCircle( drw, drwPoint , 2, CV_RGB(255, 255, 255), 0 );
        setResultPoint( minPoint );
        setTracking(true);

    }else{
        cvResetImageROI( img );
        setTracking(false);
    }



}

NoseTrack::NoseTrack() {
    this->imgResult = 0;
    this->imgTempl = 0;
    this->tracking = false;
    setTemplPoint(cvPoint(0,0));
    setNoseTplWidth(0);
    setNoseTplHeight(0);
    setNoseBoxWidth(0);
    setNoseBoxHeight(0);
}

NoseTrack::NoseTrack(const NoseTrack& orig) {
}

NoseTrack::~NoseTrack() {
    if(CV_IS_IMAGE(imgResult)){
        cvReleaseImage(&imgResult);
    }
    if(CV_IS_IMAGE(imgTempl)){
        cvReleaseImage(&imgTempl);
    }

}
void NoseTrack::setResultPoint(CvPoint resultPoint) {
    this->resultPoint = resultPoint;
}
CvPoint NoseTrack::getResultPoint() const {
    return resultPoint;
}
void NoseTrack::setTracking(bool tracking) {
    this->tracking = tracking;
}
bool NoseTrack::isTracking() const {
    return tracking;
}
void NoseTrack::setTemplPoint(CvPoint templPoint) {
    this->templPoint = templPoint;
}
CvPoint NoseTrack::getTemplPoint() const {
    return templPoint;
}
void NoseTrack::setNoseBoxHeight(int noseBoxHeight) {
    this->noseBoxHeight = noseBoxHeight;
}
int NoseTrack::getNoseBoxHeight() const {
    return noseBoxHeight;
}
void NoseTrack::setNoseBoxWidth(int noseBoxWidth) {
    this->noseBoxWidth = noseBoxWidth;
}
int NoseTrack::getNoseBoxWidth() const {
    return noseBoxWidth;
}
void NoseTrack::setNoseTplHeight(int noseTplHeight) {
    this->noseTplHeight = noseTplHeight;
}
int NoseTrack::getNoseTplHeight() const {
    return noseTplHeight;
}
void NoseTrack::setNoseTplWidth(int noseTplWidth) {
    this->noseTplWidth = noseTplWidth;
}
int NoseTrack::getNoseTplWidth() const {
    return noseTplWidth;
}


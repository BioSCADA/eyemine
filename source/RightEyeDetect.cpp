/*
 * File:   RightEyeDetect.cpp
 * Author: diego
 *
 * Created on May 24, 2010, 7:22 PM
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
#include "RightEyeDetect.h"
#include "Demand.h"
#include "IOGlobals.h"
 
const char* RightEyeDetect::getClassifierName(){ return "haarcascade_eye.xml"; }
 
void RightEyeDetect::execute(IplImage* img, CvRect rect){
    allocateOnDemand( &storageRightEye );
     
    CvRect windowRightEye = cvRect(
                    cvRound( rect.x + rect.width/2 ),
                    cvRound( rect.y +rect.height/6),
                    cvRound( rect.width/2 ),
                    cvRound( rect.height/2 )
                    );
    if( cascadeRightEye ){
            cvSetImageROI( img, windowRightEye );
            CvSeq* rightEye = cvHaarDetectObjects( img, cascadeRightEye, storageRightEye, 1.2, 2, CV_HAAR_DO_ROUGH_SEARCH, cvSize(rect.width/(10*SCALE), rect.height/(10*SCALE)) );
            //CvSeq* rightEye = cvHaarDetectObjects( img, cascadeRightEye, storageRightEye, 1.2, 2, 0, cvSize(rect.width/(10*SCALE), rect.height/(10*SCALE)) );
            cvResetImageROI( img );
            if(rightEye->total > 0){
                setRectRightEye( (CvRect*)cvGetSeqElem( rightEye, 0 ) );
                getRectRightEye()->x += windowRightEye.x ;
                getRectRightEye()->y += windowRightEye.y ;
				int rmrew = getRectMeanRightEye().width;
				int rmreh = getRectMeanRightEye().height;

                setRectMeanRightEye( cvRect(0,0, rmrew += getRectRightEye()->width,rmreh += getRectRightEye()->height));
                setPointMeanRightEye( cvPoint(getPointMeanRightEye().x+getRectRightEye()->x, getPointMeanRightEye().y+getRectRightEye()->y) );
                setFind(true);
                setNtrack(getNtrack()+1);
            }else{
                setFind(false);
            }
    } else{

    }
    cvClearMemStorage( storageRightEye );
}

RightEyeDetect::RightEyeDetect() {
    this->storageRightEye = 0;
    this->cascadeRightEye = (CvHaarClassifierCascade*)cvLoad( getClassifierName(), 0, 0, 0 );
    this->find = false;
    this->ntrack = 0;
    setPointMeanRightEye(cvPoint(0,0)); 
    setRectMeanRightEye(cvRect(0,0,0,0));
}

RightEyeDetect::RightEyeDetect(const RightEyeDetect& orig) {
}

RightEyeDetect::~RightEyeDetect() {
    if(CV_IS_STORAGE(storageRightEye)){
        cvReleaseMemStorage( &storageRightEye );
    }
    cvReleaseHaarClassifierCascade( &cascadeRightEye );
}
void RightEyeDetect::setFind(bool find) {
    this->find = find;
}
bool RightEyeDetect::isFind() const {
    return find;
}
void RightEyeDetect::setNtrack(int ntrack) {
    this->ntrack = ntrack;
}
int RightEyeDetect::getNtrack() const {
    return ntrack;
}
void RightEyeDetect::setRectRightEye(CvRect* rectRightEye) {
    this->rectRightEye = rectRightEye;
}
CvRect* RightEyeDetect::getRectRightEye() const {
    return rectRightEye;
}
void RightEyeDetect::setPointMeanRightEye(CvPoint pointMeanRightEye) {
    this->pointMeanRightEye = pointMeanRightEye;
}
CvPoint RightEyeDetect::getPointMeanRightEye() const {
    return pointMeanRightEye;
}
void RightEyeDetect::setRectMeanRightEye(CvRect rectMeanRightEye) {
    this->rectMeanRightEye = rectMeanRightEye;
}
CvRect RightEyeDetect::getRectMeanRightEye() const {
    return rectMeanRightEye;
}


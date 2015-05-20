/* 
 * File:   LeftEyeDetect.cpp
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
#include "LeftEyeDetect.h"
#include "Demand.h"
#include "IOGlobals.h"

const char* LeftEyeDetect::getClassifierName(){ return "haarcascade_eye.xml"; }

void LeftEyeDetect::execute(IplImage* img, CvRect rect){
    allocateOnDemand( &storageLeftEye );
    
    CvRect windowLeftEye = cvRect(
                    cvRound( rect.x ),
                    cvRound( rect.y +rect.height/6),
                    cvRound( rect.width/2 ),
                    cvRound( rect.height/2 )
                    );
    if( cascadeLeftEye ){
        cvSetImageROI( img, windowLeftEye );
        CvSeq* faces = cvHaarDetectObjects( img, cascadeLeftEye, storageLeftEye, 1.2, 2, CV_HAAR_DO_ROUGH_SEARCH , cvSize(rect.width/(10*SCALE), rect.height/(10*SCALE)) );
        //CvSeq* faces = cvHaarDetectObjects( img, cascadeLeftEye, storageLeftEye, 1.2, 2, 0 , cvSize(rect.width/(10*SCALE), rect.height/(10*SCALE)) );
        cvResetImageROI( img );
        if(faces->total > 0){
            setRectLeftEye( (CvRect*)cvGetSeqElem( faces, 0 ) );
            getRectLeftEye()->x += windowLeftEye.x;
            getRectLeftEye()->y += windowLeftEye.y;
			int rmlew = getRectMeanLeftEye().width;
		    int rmleh = getRectMeanLeftEye().height;
            setRectMeanLeftEye(cvRect(0,0,rmlew += getRectLeftEye()->width,rmleh += getRectLeftEye()->height));
            setPointMeanLeftEye( cvPoint(getPointMeanLeftEye().x+getRectLeftEye()->x, getPointMeanLeftEye().y+getRectLeftEye()->y) );
            setFind(true);
            setNtrack(getNtrack()+1);
        }else{
            setFind(false);
        }
        
    } else{
        
    }
    cvClearMemStorage( storageLeftEye );
}

LeftEyeDetect::LeftEyeDetect() {
    this->storageLeftEye = 0;
    this->cascadeLeftEye = (CvHaarClassifierCascade*)cvLoad( getClassifierName(), 0, 0, 0 );;
    this->find = false;
    this->ntrack = 0;
    setPointMeanLeftEye(cvPoint(0,0));
    setRectMeanLeftEye(cvRect(0,0,0,0));
}

LeftEyeDetect::LeftEyeDetect(const LeftEyeDetect& orig) {
}

LeftEyeDetect::~LeftEyeDetect() {
    if(CV_IS_STORAGE(storageLeftEye)){
        cvReleaseMemStorage( &storageLeftEye );
    }
    cvReleaseHaarClassifierCascade( &cascadeLeftEye );
}

void LeftEyeDetect::setFind(bool find) {
    this->find = find;
}
bool LeftEyeDetect::isFind() const {
    return find;
}
void LeftEyeDetect::setNtrack(int ntrack) {
    this->ntrack = ntrack;
}
int LeftEyeDetect::getNtrack() const {
    return ntrack;
}
void LeftEyeDetect::setRectLeftEye(CvRect* rectLeftEye) {
    this->rectLeftEye = rectLeftEye;
}
CvRect* LeftEyeDetect::getRectLeftEye() const {
    return rectLeftEye;
}
void LeftEyeDetect::setPointMeanLeftEye(CvPoint pointMeanLeftEye) {
    this->pointMeanLeftEye = pointMeanLeftEye;
}
CvPoint LeftEyeDetect::getPointMeanLeftEye() const {
    return pointMeanLeftEye;
}
void LeftEyeDetect::setRectMeanLeftEye(CvRect rectMeanLeftEye) {
    this->rectMeanLeftEye = rectMeanLeftEye;
}
CvRect LeftEyeDetect::getRectMeanLeftEye() const {
    return rectMeanLeftEye;
}

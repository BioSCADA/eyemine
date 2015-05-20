/*
 * File:   NoseDetect.cpp
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
#include "NoseDetect.h"
#include "Demand.h"
#include "IOGlobals.h"

const char* NoseDetect::getClassifierName(){ return "haarcascade_mcs_nose.xml"; }

void NoseDetect::execute(IplImage* img, CvRect rect){
    allocateOnDemand( &storageNose );
     
    CvRect windowNose = cvRect(
                    cvRound( rect.x + rect.width/4 ),
                    cvRound( rect.y + rect.height/4 ),
                    cvRound( rect.width/2 ),
                    cvRound( rect.height/2 )
            );
    if( cascadeNose ){
        cvSetImageROI( img, windowNose );
        CvSeq* nose = cvHaarDetectObjects( img, cascadeNose, storageNose, 1.2, 2, 4|CV_HAAR_FIND_BIGGEST_OBJECT, cvSize(rect.width/(10*SCALE), rect.height/(10*SCALE)) );
        //CvSeq* nose = cvHaarDetectObjects( img, cascadeNose, storageNose, 1.2, 2, 0, cvSize(rect.width/(10*SCALE), rect.height/(10*SCALE)) );
        cvResetImageROI( img );
        if(nose->total > 0){
            setRectNose( (CvRect*)cvGetSeqElem( nose, 0 ) );
            getRectNose()->x += windowNose.x;
            getRectNose()->y += windowNose.y;
			int rmnw = getRectMeanNose().width;
		    int rmnh = getRectMeanNose().height;
            setRectMeanNose(cvRect(0,0,rmnw += getRectNose()->width,rmnh += getRectNose()->height));
            setPointMeanNose( cvPoint(getPointMeanNose().x+getRectNose()->x, getPointMeanNose().y+getRectNose()->y) );
            setFind(true);
            setNtrack(getNtrack()+1);
        }else{
            setFind(false);
        }

    } else{

    }
    cvClearMemStorage( storageNose );

}

NoseDetect::NoseDetect() {
    this->storageNose = 0;
    this->cascadeNose = (CvHaarClassifierCascade*)cvLoad( getClassifierName(), 0, 0, 0 );;
    this->find = false;
    this->ntrack = 0;
    setPointMeanNose(cvPoint(0,0));
    setRectMeanNose(cvRect(0,0,0,0));
}

NoseDetect::NoseDetect(const NoseDetect& orig) {
}

NoseDetect::~NoseDetect() {
    if(CV_IS_STORAGE(storageNose)){
        cvReleaseMemStorage( &storageNose );
    }
    cvReleaseHaarClassifierCascade( &cascadeNose );
}
void NoseDetect::setFind(bool find) {
    this->find = find;
}
bool NoseDetect::isFind() const {
    return find;
}
void NoseDetect::setNtrack(int ntrack) {
    this->ntrack = ntrack;
}
int NoseDetect::getNtrack() const {
    return ntrack;
}
void NoseDetect::setRectNose(CvRect* rectNose) {
    this->rectNose = rectNose;
}
CvRect* NoseDetect::getRectNose() const {
    return rectNose;
}
void NoseDetect::setPointMeanNose(CvPoint pointMeanNose) {
    this->pointMeanNose = pointMeanNose;
}
CvPoint NoseDetect::getPointMeanNose() const {
    return pointMeanNose;
}
void NoseDetect::setRectMeanNose(CvRect rectMeanNose) {
    this->rectMeanNose = rectMeanNose;
}
CvRect NoseDetect::getRectMeanNose() const {
    return rectMeanNose;
}

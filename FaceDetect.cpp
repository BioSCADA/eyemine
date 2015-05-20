/* 
 * File:   FaceDetect.cpp
 * Author: diego schmaedech
 * 
 * Created on May 24, 2010, 3:44 PM
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
#include "FaceDetect.h"
#include "Demand.h"
#include "IOGlobals.h" 
#include <cv.h> 
 
void FaceDetect::execute(IplImage* img){
    
    if( cascadeFace ){ 
        faces  = cvHaarDetectObjects( img, cascadeFace, storageFace, 1.2, 2, 4|CV_HAAR_FIND_BIGGEST_OBJECT, cvSize(img->width/(2*SCALE), img->height/(2*SCALE)) );
        //faces  = cvHaarDetectObjects( img, cascadeFace, storageFace, 1.2, 2, 0, cvSize(img->width/(2*SCALE), img->height/(2*SCALE)) );
        if(faces->total > 0){
            setRectFace( (CvRect*)cvGetSeqElem( faces, 0 ) );
            setNtrack(getNtrack()+1);
            setFind(true);
        }else{
            setFind(false);
        } 
    } else{
         
    }
    cvClearMemStorage( storageFace );

}

const char* FaceDetect::getClassifierName(){ return "haarcascade_frontalface_alt.xml"; }

FaceDetect::FaceDetect(const FaceDetect& orig) { }

FaceDetect::FaceDetect() {
    this->storageFace = 0;
    this->cascadeFace = (CvHaarClassifierCascade*)cvLoad( getClassifierName(), 0, 0, 0 );
    this->ntrack = 0;
    allocateOnDemand( &storageFace );
}

FaceDetect::~FaceDetect() {
    if(CV_IS_STORAGE(storageFace)){
        
        cvReleaseMemStorage( &storageFace );
        //cvReleaseHaarClassifierCascade( &cascadeFace );
    }
    
}

void FaceDetect::setNtrack(int ntrack) {
        this->ntrack = ntrack;
}

int FaceDetect::getNtrack() const {
    return ntrack;
}

void FaceDetect::setRectFace(CvRect* rectFace) {
    this->rectFace = rectFace;
}

CvRect* FaceDetect::getRectFace() const {
    return rectFace;
}
void FaceDetect::setFind(bool find) {
    this->find = find;
}
bool FaceDetect::isFind() const {
    return find;
}


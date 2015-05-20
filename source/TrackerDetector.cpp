/* 
 * File:   TrackerDetector.cpp
 * Author: diego
 * 
 * Created on May 26, 2010, 6:11 PM
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
#include "TrackerDetector.h" 
#include "Demand.h"
#include "IOGlobals.h"
#include "FaceHeuristics.h"

void TrackerDetector::lostTracking(){
    lostLeftEye();
    lostRightEye();
    lostMouth();
    lostNose();
}

void TrackerDetector::detectFace(IplImage *frame){ 
    faceDetect.execute(pryDownFrame);
    if( faceDetect.isFind() ){
        CvPoint faceP1 = cvPoint(SCALE*faceDetect.getRectFace()->x, SCALE*faceDetect.getRectFace()->y);
        CvPoint faceP2 = cvPoint(SCALE*faceDetect.getRectFace()->x + SCALE*faceDetect.getRectFace()->width, SCALE*faceDetect.getRectFace()->y + SCALE*faceDetect.getRectFace()->height);
        cvRectangle(frame, faceP1, faceP2, CV_RGB(255,255,255) , 1, 8, 0 );
        setWindowFace(cvRect(faceDetect.getRectFace()->x,faceDetect.getRectFace()->y, faceDetect.getRectFace()->width, faceDetect.getRectFace()->height));
        setFaceDetected(true);
    }

}

void TrackerDetector::detectLeftEye(IplImage* frame){
    leftEyeDetect.execute(pryDownFrame, windowFace);
    if(leftEyeDetect.isFind()){
        CvPoint leftEyeP1 = cvPoint( SCALE*leftEyeDetect.getRectLeftEye()->x,  SCALE*leftEyeDetect.getRectLeftEye()->y);
        CvPoint leftEyeP2 = cvPoint( leftEyeP1.x + SCALE*leftEyeDetect.getRectLeftEye()->width, leftEyeP1.y + SCALE*leftEyeDetect.getRectLeftEye()->height);
        cvRectangle(frame, leftEyeP1, leftEyeP2, CV_RGB(255,255,255) , 2, 8, 0 );
        if(leftEyeDetect.getNtrack() > NTRACK){
            //int meanX = SCALE*(leftEyeDetect.getPointMeanLeftEye().x/leftEyeDetect.getNtrack()+leftEyeDetect.getRectLeftEye()->width/4);
            int meanX = SCALE*(leftEyeDetect.getPointMeanLeftEye().x/leftEyeDetect.getNtrack()+leftEyeDetect.getRectLeftEye()->width/4);
            int meanY = SCALE*(leftEyeDetect.getPointMeanLeftEye().y/leftEyeDetect.getNtrack()+leftEyeDetect.getRectLeftEye()->height/3);
            int meanWidth = SCALE*(leftEyeDetect.getRectMeanLeftEye().width/leftEyeDetect.getNtrack()/2);
            int meanHeight = SCALE*(leftEyeDetect.getRectMeanLeftEye().height/leftEyeDetect.getNtrack()/3);
            CvPoint meanPoint = cvPoint( meanX, meanY );
            cvCircle( frame, meanPoint, 2, CV_RGB(255, 0, 0), CV_FILLED );
            leftEyeTrack.makeTemplate( pryUpFrame, meanPoint, meanWidth, meanHeight);
            setLeftEyeTracking(leftEyeTrack.isTracking());
            setLeftEyeDetected(true);
        }
    }

}

void TrackerDetector::detectRightEye(IplImage* frame){
    rightEyeDetect.execute(pryDownFrame, windowFace);
    if(rightEyeDetect.isFind()){
        CvPoint rightEyeP1 = cvPoint( SCALE*rightEyeDetect.getRectRightEye()->x, SCALE*rightEyeDetect.getRectRightEye()->y);
        CvPoint rightEyeP2 = cvPoint( rightEyeP1.x + SCALE*rightEyeDetect.getRectRightEye()->width, rightEyeP1.y + SCALE*rightEyeDetect.getRectRightEye()->height);
        cvRectangle(frame, rightEyeP1, rightEyeP2, CV_RGB(255,255,255) , 2, 8, 0 );
        if(rightEyeDetect.getNtrack() > NTRACK){
            //CvPoint meanPoint = cvPoint( SCALE*rightEyeDetect.getPointMeanRightEye().x/rightEyeDetect.getNtrack()+SCALE*rightEyeDetect.getRectRightEye()->width/2, SCALE*rightEyeDetect.getPointMeanRightEye().y/rightEyeDetect.getNtrack()+SCALE*rightEyeDetect.getRectRightEye()->height/3);
            int meanX = SCALE*(rightEyeDetect.getPointMeanRightEye().x/rightEyeDetect.getNtrack()+rightEyeDetect.getRectRightEye()->width/4);
            int meanY = SCALE*(rightEyeDetect.getPointMeanRightEye().y/rightEyeDetect.getNtrack()+rightEyeDetect.getRectRightEye()->height/3);
            int meanWidth = SCALE*(rightEyeDetect.getRectMeanRightEye().width/rightEyeDetect.getNtrack()/2);
            int meanHeight = SCALE*(rightEyeDetect.getRectMeanRightEye().height/rightEyeDetect.getNtrack()/3);
            CvPoint meanPoint = cvPoint( meanX, meanY );
            cvCircle( frame, meanPoint , 2, CV_RGB(255, 0, 0), CV_FILLED );
            rightEyeTrack.makeTemplate( pryUpFrame, meanPoint, meanWidth, meanHeight );
            setRightEyeTracking(rightEyeTrack.isTracking());
            setRightEyeDetected(true);
        }
    }
     
}

void TrackerDetector::detectMouth(IplImage* frame){
    mouthDetect.execute(pryDownFrame, windowFace);
    if(mouthDetect.isFind()){
        CvPoint mouthP1 = cvPoint( SCALE*mouthDetect.getRectMouth()->x, SCALE*mouthDetect.getRectMouth()->y);
        CvPoint mouthP2 = cvPoint( mouthP1.x + SCALE*mouthDetect.getRectMouth()->width, mouthP1.y + SCALE*mouthDetect.getRectMouth()->height);
        cvRectangle(frame, mouthP1, mouthP2, CV_RGB(255,255,255) , 2, 8, 0 );
        if(mouthDetect.getNtrack() > NTRACK){
            int meanX = SCALE*(mouthDetect.getPointMeanMouth().x/mouthDetect.getNtrack());
            int meanY = SCALE*(mouthDetect.getPointMeanMouth().y/mouthDetect.getNtrack() );
            int meanWidth = SCALE*(mouthDetect.getRectMeanMouth().width/mouthDetect.getNtrack());
            int meanHeight = SCALE*(mouthDetect.getRectMeanMouth().height/mouthDetect.getNtrack());
            CvPoint meanPoint = cvPoint( meanX , meanY );
            cvCircle( frame, meanPoint , 2, CV_RGB(255, 0, 0), CV_FILLED );
            mouthTrack.makeTemplate( pryUpFrame, meanPoint, meanWidth, meanHeight);
            setMouthTracking(mouthTrack.isTracking());
            setMouthDetected(true);
        }
    }

}

void TrackerDetector::detectNose(IplImage* frame){
    noseDetect.execute(pryDownFrame, windowFace);
    if(noseDetect.isFind()){
        CvPoint noseP1 = cvPoint( SCALE*noseDetect.getRectNose()->x, SCALE*noseDetect.getRectNose()->y);
        CvPoint noseP2 = cvPoint( noseP1.x + SCALE*noseDetect.getRectNose()->width, noseP1.y + SCALE*noseDetect.getRectNose()->height);
        cvRectangle(frame, noseP1, noseP2, CV_RGB(255,255,255) , 2, 8, 0 );
        if(noseDetect.getNtrack() > NTRACK){
            int meanX = SCALE*(noseDetect.getPointMeanNose().x/noseDetect.getNtrack());
            int meanY = SCALE*(noseDetect.getPointMeanNose().y/noseDetect.getNtrack());
            int meanWidth = SCALE*(noseDetect.getRectMeanNose().width/noseDetect.getNtrack());
            int meanHeight = SCALE*(noseDetect.getRectMeanNose().height/noseDetect.getNtrack()); 
            CvPoint meanPoint = cvPoint( meanX, meanY);
            cvCircle( frame, meanPoint , 2, CV_RGB(255, 0, 0), CV_FILLED );
            noseTrack.makeTemplate( pryUpFrame, meanPoint, meanWidth, meanHeight );
            setNoseTracking(noseTrack.isTracking());
            setNoseDetected(true);
        }
    }

}

void TrackerDetector::lostRightEye(){
    setRightEyeDetected(false);
    rightEyeDetect.setNtrack(0);
    rightEyeDetect.setPointMeanRightEye(cvPoint(0,0));
    rightEyeDetect.setRectMeanRightEye(cvRect(0,0,0,0));
    lostFace();
}

void TrackerDetector::lostLeftEye(){
    setLeftEyeDetected(false);
    leftEyeDetect.setNtrack(0);
    leftEyeDetect.setPointMeanLeftEye(cvPoint(0,0));
    leftEyeDetect.setRectMeanLeftEye(cvRect(0,0,0,0));
    lostFace();
}

void TrackerDetector::lostMouth(){
    setMouthDetected(false);
    mouthDetect.setNtrack(0);
    mouthDetect.setPointMeanMouth(cvPoint(0,0));
    mouthDetect.setRectMeanMouth(cvRect(0,0,0,0));
    lostFace();
}

void TrackerDetector::lostNose(){
    setNoseDetected(false);
    noseDetect.setNtrack(0);
    noseDetect.setPointMeanNose(cvPoint(0,0));
    noseDetect.setRectMeanNose(cvRect(0,0,0,0));
    lostFace();
}

void TrackerDetector::lostFace(){
    setFaceDetected(false);
    faceDetect.setNtrack(0);
}

void TrackerDetector::trackRightEye(IplImage* frame){
    rightEyeTrack.execute(pryUpFrame,frame);
    if(rightEyeTrack.isTracking()){
        CvPoint refP1 = rightEyeTrack.getTemplPoint();
        CvPoint refP2 = cvPoint(rightEyeTrack.getTemplPoint().x+rightEyeTrack.getRightEyeTplWidth(),rightEyeTrack.getTemplPoint().y+rightEyeTrack.getRightEyeTplHeight());
        CvPoint trackP1 = rightEyeTrack.getResultPoint();
        CvPoint trackP2 = cvPoint(rightEyeTrack.getResultPoint().x+rightEyeTrack.getRightEyeTplWidth(),rightEyeTrack.getResultPoint().y+rightEyeTrack.getRightEyeTplHeight());
        cvRectangle(frame, refP1, refP2, CV_RGB(0,0,0) , 1, 8, 0 );
        faceHeuristics.SetRefPointRightEye(refP1);
        cvRectangle(frame, trackP1, trackP2, CV_RGB(0,100,255) , 1, 8, 0 );
        faceHeuristics.SetTrackPointRightEye(trackP1);
    }else{
        lostRightEye();
    }
}

void TrackerDetector::trackLeftEye(IplImage* frame){
    leftEyeTrack.execute(pryUpFrame,frame);
    if(leftEyeTrack.isTracking()){
        CvPoint refP1 = leftEyeTrack.getTemplPoint();
        CvPoint refP2 = cvPoint(leftEyeTrack.getTemplPoint().x+leftEyeTrack.getLeftEyeTplWidth(),leftEyeTrack.getTemplPoint().y+leftEyeTrack.getLeftEyeTplHeight());
        CvPoint trackP1 = leftEyeTrack.getResultPoint();
        CvPoint trackP2 = cvPoint(leftEyeTrack.getResultPoint().x+leftEyeTrack.getLeftEyeTplWidth(),leftEyeTrack.getResultPoint().y+leftEyeTrack.getLeftEyeTplHeight());
        cvRectangle(frame, refP1, refP2, CV_RGB(0,0,0) , 1, 8, 0 );
        faceHeuristics.SetRefPointLeftEye(refP1);
        cvRectangle(frame, trackP1, trackP2, CV_RGB(0,100,255) , 1, 8, 0 );
        faceHeuristics.SetTrackPointLeftEye(trackP1);
    }else{
        lostLeftEye();
    }
}

void TrackerDetector::trackMouth(IplImage* frame){
    mouthTrack.execute(pryUpFrame,frame);
    if(mouthTrack.isTracking()){
        CvPoint refP1 = mouthTrack.getTemplPoint();
        CvPoint refP2 = cvPoint(mouthTrack.getTemplPoint().x+mouthTrack.getMouthTplWidth(),mouthTrack.getTemplPoint().y+mouthTrack.getMouthTplHeight());
        CvPoint trackP1 = mouthTrack.getResultPoint();
        CvPoint trackP2 = cvPoint(mouthTrack.getResultPoint().x+mouthTrack.getMouthTplWidth(),mouthTrack.getResultPoint().y+mouthTrack.getMouthTplHeight());
        cvRectangle(frame, refP1, refP2, CV_RGB(0,0,0) , 1, 8, 0 );
        faceHeuristics.SetRefPointMouth(refP1);
        cvRectangle(frame, trackP1, trackP2, CV_RGB(0,100,255) , 1, 8, 0 );
        faceHeuristics.SetTrackPointMouth(trackP1);
    }else{
        lostMouth();
    }

}

void TrackerDetector::trackNose(IplImage* frame){
    noseTrack.execute(pryUpFrame,frame);
    if(noseTrack.isTracking()){
        CvPoint refP1 = noseTrack.getTemplPoint();
        CvPoint refP2 = cvPoint(noseTrack.getTemplPoint().x+noseTrack.getNoseTplWidth(),noseTrack.getTemplPoint().y+noseTrack.getNoseTplHeight());
        CvPoint trackP1 = noseTrack.getResultPoint();
        CvPoint trackP2 = cvPoint(noseTrack.getResultPoint().x+noseTrack.getNoseTplWidth(),noseTrack.getResultPoint().y+noseTrack.getNoseTplHeight());
        cvRectangle(frame, refP1, refP2, CV_RGB(0,0,0) , 1, 8, 0 );
        faceHeuristics.SetRefPointNose(refP1);
        cvRectangle(frame, trackP1, trackP2, CV_RGB(0,100,255) , 1, 8, 0 );
        faceHeuristics.SetTrackPointNose(trackP1);
    }else{
        lostNose();
    }

}

void TrackerDetector::execute(IplImage* frame){

    allocateOnDemand( &pryDownFrame, cvSize(frame->width/SCALE, frame->height/SCALE), frame->depth, frame->nChannels );
    cvPyrDown(frame, pryDownFrame, CV_GAUSSIAN_5x5);

    allocateOnDemand( &pryUpFrame, cvSize(pryDownFrame->width*SCALE, pryDownFrame->height*SCALE), pryDownFrame->depth, pryDownFrame->nChannels );
    cvPyrUp(pryDownFrame, pryUpFrame, CV_GAUSSIAN_5x5);

    if( isFaceDetected() ){
 
        if(isLeftEyeDetected() && isRightEyeDetected() && isNoseDetected()){
            trackLeftEye(frame);
            trackRightEye(frame);
            trackNose(frame);
            faceHeuristics.verifyDistances();
            if(!faceHeuristics.IsEyes() || !faceHeuristics.IsNose()){
                lostLeftEye();
                lostRightEye();
                lostNose();
                lostMouth();
                TrackerDetector::lostCount += 1;
                FaceHeuristics::GazeHH = 0;
                FaceHeuristics::GazeMM = 0;
                FaceHeuristics::GazeSS = 0;
            }
        }else{
            detectLeftEye(frame);
            detectRightEye(frame);
            detectNose(frame);
            
        }



        if(isMouthDetected()){
            trackMouth(frame);
            if(!faceHeuristics.IsMouth()){
                lostMouth();
                MouthContours::MouthHH = 0;
                MouthContours::MouthMM = 0;
                MouthContours::MouthSS = 0;
            }
        }else{
            detectMouth(frame);
            
        }
        
    }else{
        detectFace(frame);
    }



}

TrackerDetector::TrackerDetector() {
    this->pryDownFrame = 0;
    this->pryUpFrame = 0;
    this->rightEyeTracking = false;
    this->leftEyeTracking = false;
    this->noseTracking = false;
    this->mouthTracking = false;
}

void TrackerDetector::setMouthTracking(bool mouthTracking) {
    this->mouthTracking = mouthTracking;
}
bool TrackerDetector::isMouthTracking() const {
    return mouthTracking;
}
void TrackerDetector::setNoseTracking(bool noseTracking) {
    this->noseTracking = noseTracking;
}
bool TrackerDetector::isNoseTracking() const {
    return noseTracking;
}
void TrackerDetector::setLeftEyeTracking(bool leftEyeTracking) {
    this->leftEyeTracking = leftEyeTracking;
}
bool TrackerDetector::isLeftEyeTracking() const {
    return leftEyeTracking;
}
void TrackerDetector::setRightEyeTracking(bool rightEyeTracking) {
    this->rightEyeTracking = rightEyeTracking;
}
bool TrackerDetector::isRightEyeTracking() const {
    return rightEyeTracking;
}
void TrackerDetector::setFaceTracking(bool faceTracking) {
    this->faceTracking = faceTracking;
}
bool TrackerDetector::isFaceTracking() const {
    return faceTracking;
}
void TrackerDetector::setWindowFace(CvRect windowFace) {
    this->windowFace = windowFace;
}
CvRect TrackerDetector::getWindowFace() const {
    return windowFace;
}
void TrackerDetector::setFaceDetected(bool faceDetected) {
    this->faceDetected = faceDetected;
}
bool TrackerDetector::isFaceDetected() const {
    return faceDetected;
}
void TrackerDetector::setMouthDetected(bool mouthDetected) {
    this->mouthDetected = mouthDetected;
}
bool TrackerDetector::isMouthDetected() const {
    return mouthDetected;
}
void TrackerDetector::setNoseDetected(bool noseDetected) {
    this->noseDetected = noseDetected;
}
bool TrackerDetector::isNoseDetected() const {
    return noseDetected;
}
void TrackerDetector::setLeftEyeDetected(bool leftEyeDetected) {
    this->leftEyeDetected = leftEyeDetected;
}
bool TrackerDetector::isLeftEyeDetected() const {
    return leftEyeDetected;
}
void TrackerDetector::setRightEyeDetected(bool rightEyeDetected) {
    this->rightEyeDetected = rightEyeDetected;
}
bool TrackerDetector::isRightEyeDetected() const {
    return rightEyeDetected;
}
TrackerDetector::TrackerDetector(const TrackerDetector& orig) {
}
TrackerDetector::~TrackerDetector() {
}

int TrackerDetector::lostCount = 0;

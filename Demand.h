// 
// File:   ImageDemand.h
// Author: diego schmaedech
//
// Created on September 9, 2009, 3:15 PM
//

#ifndef _DEMAND_H
#define	_DEMAND_H
#include <cv.h>
 

inline static void allocateOnDemand( IplImage **img, CvSize size, int depth, int channels){
     if ( *img != NULL ) 
         return;
     *img = cvCreateImage( size, depth, channels );
      
}

inline static void allocateOnDemand( CvMemStorage **storage){
     if ( *storage != NULL ) 
         return;
     *storage = cvCreateMemStorage(0);
     
}
 
#endif	/* _IMAGEDEMAND_H */


/*
 * ITrackPointListener.h
 *
 *  Created on: 2010-07-14
 *      Author: Mateusz Nowak
 */

#ifndef ITRACKPOINTLISTENER_H_
#define ITRACKPOINTLISTENER_H_

#include "TrackPoint.h"
/**
 * @interface ITrackPointListener
 * @brief Interfejs uzywany do pobierania lokalizacji z GPSu
 * @see TrackPoint, GpsSensorListener
 */

class ITrackPointListener {

	// Operations
public:
	/**
	 * Poprzez ta metode dostajemy aktualna lokazlizacje z GPS Sensora.
	 *  Nie uzywac explicite! Do wykorzystania przez inne obiekty.
	 * @param trackPoint    Dane pobrane z GPSu
	 */
	virtual void SentNewTrackPoint(TrackPoint& trackPoint)=0;
};

#endif /* ITRACKPOINTLISTENER_H_ */

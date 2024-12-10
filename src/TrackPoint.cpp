/*
 * TrackPoint.cpp
 *
 *  Created on: 2010-07-14
 *      Author: Mateusz Nowak
 */

#include "TrackPoint.h"

using Tizen::Locations::Coordinates;
using Tizen::Base::TimeSpan;

TrackPoint::TrackPoint(Coordinates& coordinates, TimeSpan& timespan) :
	_timeSpan(timespan) {
	_Init(coordinates.GetLatitude(), coordinates.GetLongitude(),
			coordinates.GetAltitude());
}

TrackPoint::TrackPoint(float latitude, float longitude, float altitude,
		long timestamp, float speed) :
	_timeSpan(timestamp), _speed(speed){
	_Init(latitude, longitude, altitude);
}

int TrackPoint::Compare(const TrackPoint & t1, const TrackPoint & t2) {
	return TimeSpan::Compare(t1.GetTime(), t2.GetTime());
}

int TrackPoint::CompareTo(const TrackPoint & value) const {
	return _timeSpan.CompareTo(value.GetTime());
}

int TrackPoint::GetHashCode(void) const {
	int multipler = 100000000;
	return int(GetLatitude() * multipler) ^ int(GetLongitude() * multipler)
			^ int(GetAltitude() * multipler) ^ _timeSpan.GetHashCode();
}

bool TrackPoint::Equals(const Object & obj) const {
	return GetHashCode() == obj.GetHashCode();
}

TrackPoint::TrackPoint(const TrackPoint & trackPoint) :
	_timeSpan(trackPoint.GetTime()), _speed(trackPoint.GetSpeed()){
	_Init(trackPoint.GetLatitude(), trackPoint.GetLongitude(),
			trackPoint.GetAltitude());

}

TrackPoint & TrackPoint::operator =(TrackPoint & trackPoint) {
	_Init(trackPoint.GetLatitude(), trackPoint.GetLongitude(),
			trackPoint.GetAltitude());
	_timeSpan = trackPoint.GetTime();
	_speed = trackPoint.GetSpeed();

	return *this;
}


void TrackPoint::SetSpeed(float speed)
{
	_speed = speed;
}

float TrackPoint::GetSpeed(void) const
{
	return _speed;
}

void TrackPoint::_Init(float latitude, float longitude, float altitude) {
	SetLatitude(latitude);
	SetLongitude(longitude);
	SetAltitude(altitude);
}

TimeSpan TrackPoint::GetTime(void) const {
	return _timeSpan;
}




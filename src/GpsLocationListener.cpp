/*
 * GpsLocationListener.cpp
 *
 *  Created on: 2010-11-08
 *      Author: Mateusz
 */

#include "GpsLocationListener.h"
#include "FSystem.h"
#include <FLocations.h>
#include <FLocLocationProvider.h>

using Tizen::Base::Collection::IEnumeratorT;
using Tizen::Locations::Coordinates;
using Tizen::Locations::LocationServiceStatus;
using namespace Tizen::Locations;

//using Tizen::Locations::LOC_PROVIDER_TEMPORARILY_UNAVAILABLE;

GpsLocationListener::GpsLocationListener() :
		_isLocked(true), _lastPoint(0, 0, 0, 0, 0) {
	_locationProvider = new Tizen::Locations::LocationProvider();

}

GpsLocationListener::~GpsLocationListener() {
	if (null != _locationProvider) {
		_locationProvider->StopLocationUpdates();
		delete _locationProvider;
		_locationProvider = null;
	}

}

result GpsLocationListener::Construct(void) {
	Tizen::Locations::LocationCriteria criteria;
	criteria.SetAccuracy(Tizen::Locations::LOC_ACCURACY_HUNDRED_METERS);
	result r = _locationProvider->Construct(criteria, *this);
	if (IsFailed(r)) {
		AppLogException("Nie moge utworozyc LocationProvidera");
		return E_FAILURE;
	}

	r = _locationProvider->StartLocationUpdatesByInterval(
			GpsLocationListener::GetIntervalInMs() / 1000);
	if (IsFailed(r)) {
		AppLogException("Nie mozna dodac ILocationListenera");
		return E_FAILURE;
	}
	bool awake = true;
	_locationProvider->KeepLocationUpdateAwake(awake);
	return E_SUCCESS;
}

result GpsLocationListener::RemoveListener(
		ITrackPointListener * pTrackPointListener) {
	AppAssertf(pTrackPointListener != 0,
			"Proba usuniecia null pointera z listy");
	result r = _listeners.Remove(pTrackPointListener);
	return r;
}

GpsLocationListener::GpsLocationListener(
		const GpsLocationListener & gpsLocationListener) {
}

result GpsLocationListener::AddListener(
		ITrackPointListener *pTrackPointListener) {
	AppAssertf(pTrackPointListener != 0,
			"Proba dodania null pointera do listy");
	result r = _listeners.Add(pTrackPointListener);
	return r;
}

void GpsLocationListener::_unlockForms(LockReason lockReason) {
	ILockedForm * pForm = null;
	IEnumeratorT<ILockedForm*> *pEnum = _lockedForms.GetEnumeratorN();
	while (E_SUCCESS == pEnum->MoveNext()) {
		pEnum->GetCurrent(pForm);
		pForm->Unlock(lockReason);
	}
	if (null != pEnum) {
		delete pEnum;
	}
	_isLocked = false;
}

void GpsLocationListener::_lockForms(LockReason lockReason) {
	ILockedForm * pForm = null;
	IEnumeratorT<ILockedForm*> *pEnum = _lockedForms.GetEnumeratorN();
	while (E_SUCCESS == pEnum->MoveNext()) {
		pEnum->GetCurrent(pForm);
		pForm->Lock(lockReason); // TODO: Moze trzeba dodac paramter?
	}
	if (null != pEnum) {
		delete pEnum;
	}
	_isLocked = true;
}

void GpsLocationListener::OnLocationUpdated(const Location & location) {
	Coordinates q = location.GetCoordinates();

	if (location.IsValid()) {
		if (true == _isLocked) {
			_unlockForms(LOCK_REASON_LOCATION_FOUND);
		}

		_latitude = q.GetLatitude();
		_longitude = q.GetLongitude();
		_altitude = q.GetAltitude();
		_timestamp = location.GetTimestamp().GetMillisecond();
		_speed = location.GetSpeed();

		// Tworzymy obiekt do przekazania
		TrackPoint point(_latitude, _longitude, _altitude, _timestamp, _speed);

		CalculateAccurateSpeed(point);

		ITrackPointListener* pCurrent = NULL;
		IEnumeratorT<ITrackPointListener*> *pEnum = _listeners.GetEnumeratorN();

		// Do kazdego obiektu z listy przekazujemy aktualna lokalizacje
		while (E_SUCCESS == pEnum->MoveNext()) {
			pEnum->GetCurrent(pCurrent);
			pCurrent->SentNewTrackPoint(point);
		}
		if (null != pEnum) {
			delete pEnum;
		}
	} else { // Nie dostajemy poprawnych koordynatow z GPSu
		if (false == _isLocked) {
			_lockForms(LOCK_REASON_NO_LOCATION_FOUND);

		}

#ifdef ENABLE_SATELITES_NUMBER
		const Tizen::Locations::SatelliteInfo *s = location.GetSatelliteInfo();
		if (s != null) {
			ILockedForm *pForm = null;
			IEnumeratorT<ILockedForm*> *pEnum = _lockedForms.GetEnumeratorN();
			while (pEnum->MoveNext() == E_SUCCESS) {
				pEnum->GetCurrent(pForm);
				pForm->SendSomethingToForm(counter++);
			}
			if (null != pEnum) {
				delete pEnum;
			}
		}
#endif //ENABLE_SATELITES_NUMBER
	}

}
void GpsLocationListener::OnLocationUpdateStatusChanged(
		Tizen::Locations::LocationServiceStatus status) {
	if (status == Tizen::Locations::LOC_SVC_STATUS_NOT_FIXED
			|| status == Tizen::Locations::LOC_SVC_STATUS_DENIED
			|| status == Tizen::Locations::LOC_SVC_STATUS_PAUSED) {
		//_locationProvider->StopLocationUpdates();

		if (_isLocked == false) {
			_lockForms(LOCK_REASON_SIGNAL_LOST);
		}
	} else if (status == Tizen::Locations::LOC_SVC_STATUS_RUNNING) {
		if (_isLocked == true) {
			_unlockForms(LOCK_REASON_LOCATION_FOUND);
		}

	}
}

int GpsLocationListener::GetIntervalInMs(void) {
	return 1000;
}

result GpsLocationListener::RemoveLockedForm(ILockedForm *pLockedForm) {
	AppAssertf(pLockedForm != 0, "Proba usuniecia null pointera z listy");
	result r = _lockedForms.Remove(pLockedForm);
	return r;
}

result GpsLocationListener::AddLockedForm(ILockedForm *pLockedForm) {
	AppAssertf(pLockedForm != 0, "Proba dodania null pointera do listy");
	result r = _lockedForms.Add(pLockedForm);
	return r;
}

GpsLocationListener & GpsLocationListener::operator =(
		const GpsLocationListener & rhs) {
	return *this;
}

void GpsLocationListener::CalculateAccurateSpeed(TrackPoint &__point) {
	if (_lastPoint.GetLongitude() == 0 && _lastPoint.GetLatitude() == 0
			&& _lastPoint.GetAltitude() == 0) {
		_lastPoint = __point;
		return;
	}
	float speed = _lastPoint.GetDistanceTo(__point) * 3.6;
	if (__point.GetSpeed() == 0.0 && speed <= 1.0)
		__point.SetSpeed(speed);
	if (speed <= __point.GetSpeed() + 0.9 && speed >= __point.GetSpeed() - 0.9)
		__point.SetSpeed(speed);
	_lastPoint = __point;

}


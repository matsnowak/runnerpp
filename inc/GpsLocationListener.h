/*
 * GpsLocationListener.h
 *
 *  Created on: 2010-11-08
 *      Author: Mateusz
 */

#ifndef GPSLOCATIONLISTENER_H_
#define GPSLOCATIONLISTENER_H_

#include <FBaseColLinkedListT.h>
#include "ILockedForm.h"
#include "ITrackPointListener.h"
#include "FLocations.h"

using Tizen::Locations::Location;

typedef
enum {
	LOCK_REASON_NO_LOCATION_FOUND 	=	0x0,	// Nie znaleziono jescze sygnalu
	LOCK_REASON_LOCATION_FOUND		= 	0x2,	// Znaleziono sygnal
	LOCK_REASON_SIGNAL_LOST			=	0x4		// Sygnal spierdolil

} LockReason;

/**
 * @class GpsLocationListener
 * Pobiera punkty przy pomocy LocationProvider i wysla jed do ITrackPointListener
 */
class GpsLocationListener: public Tizen::Locations::ILocationProviderListener {
public:
	// Lifecycle
	GpsLocationListener();
	virtual ~GpsLocationListener();

	/**
	 * Konstruktor drugo fazowy. Musi zostac wywolany zaraz po konstruktorze domyslnym
	 * @return	@c E_SUCCESS	jesli udalo sie zaalokowac pamiec
	 * 			@c E_FAILURE	w przeciwnym wypadku
	 */
	result Construct(void);

	// Operations
public:

	/**
	 * Dodaje obiekt do listy, aby zostal uaktualniony przy kazdym otrzymaniu
	 * puntku z GPSu
	 *
	 * @param pTrackPointListener	wskaznik na obiekt implementujacy ITrackPointListener
	 * @see RemoveListener(), OnDataReceived()
	 */
	virtual result AddListener(ITrackPointListener* pTrackPointListener);

	/**
	 * Usuwa listener z listy obiektow nasluchujacych
	 *
	 * @param pTrackPointListener	wskaznik na obiekt implementujacy ITrackPointListener
	 * @see AddListener(), OnDataReceived()
	 */
	virtual result RemoveListener(ITrackPointListener * pTrackPointListener);

	/**
	 * Dodaje obiekt,  ktory mozna blokowac do listy
	 *
	 * @param pLockedForm	wskaznik na obiekt implementujacy pLockedForm
	 */
	virtual result AddLockedForm(ILockedForm* pLockedForm);

	/**
	 * Usuwa listener z listy obiektow nasluchujacych
	 *
	 * @param pLockedForm	wskaznik na obiekt implementujacy ILockedForm
	 */
	virtual result RemoveLockedForm(ILockedForm *pLockedForm);
	/*
	 * Wymagane przez interfejs ILocationListener,
	 * Wywoane przy pobieraniu punktu z GPSu
	 */
	virtual void OnLocationUpdated(const Location &location);
virtual void OnLocationUpdateStatusChanged(Tizen::Locations::LocationServiceStatus status);
	virtual void OnAccuracyChanged(Tizen::Locations::LocationAccuracy accuracy) {}
	virtual void OnRegionEntered(Tizen::Locations::RegionId regionId) {}
	virtual virtual void OnRegionLeft(Tizen::Locations::RegionId regionId) {}
	virtual void OnRegionMonitoringStatusChanged(Tizen::Locations::LocationServiceStatus status) {}


	/**
	 * Zwraca interwal w milisekundach
	 */
	static int GetIntervalInMs(void);

private:

	// Blokujemy mozliwosc kopiowania i przypisywania (bo niby po co to robic?)
	/**
	 * Prywatny konstruktor kopiujacy
	 * Nie pozwala robic kopii obiektu.
	 * @param rhs Obiekt do skopiowania
	 */
	GpsLocationListener(const GpsLocationListener& gpsLocationListener);

	/**
	 * Prywatny operator przypisania
	 * Nie pozwala robic kopii obiektu.
	 * @param gpsSensorListener Obiekt do skopiowania
	 * @return referencje do samego siebie
	 */
	GpsLocationListener& operator=(const GpsLocationListener& rhs);
	void CalculateAccurateSpeed(TrackPoint &__track);
	void _lockForms(LockReason lockReason);
	void _unlockForms(LockReason lockReason);
	Tizen::Base::Collection::LinkedListT<ITrackPointListener*> _listeners;
	Tizen::Base::Collection::LinkedListT<ILockedForm*> _lockedForms;
	Tizen::Locations::LocationProvider *_locationProvider;
	long long int	_timestamp;
	double _latitude;
	double _longitude;
	double _altitude;
	int counter;
	float _speed;
	bool _isLocked;
	TrackPoint _lastPoint;
};

#endif /* GPSLOCATIONLISTENER_H_ */

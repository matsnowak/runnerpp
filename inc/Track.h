/*
t * Track.h
 *
 *  Created on: 2010-07-14
 *      Author: Mateusz Nowak
 */

#ifndef TRACK_H_
#define TRACK_H_

#include <FBaseColLinkedListT.h>
#include "TrackPoint.h"


using Tizen::Base::TimeSpan;


/**
 * @class Track
 * @brief Reprezentuje trase w postaci kolekcji punktow
 * @see TrackPoint
 */
class Track {
public:
	// Lifecycle
	/**
	 * Domyslny konstruktor
	 * @remarks Po utworzeniu obiektu mysisz wywolac @b Track::Construct
	 * @see Construct
	 */
	Track(void);

	/**
	 * Drugofazowy konstruktor, inicjalizuje pamiec
	 * @return	@c E_SUCCESS jesli udalo sie zaalokowac pamiec dla obiektu @n
	 * 			@c E_FAILURE w przeciwnym wypadku
	 * @remarks Musi byc wywolany zaraz po konstruktorze
	 */
	result Construct(void);

	/**
	 * Wirtualny destruktor zwalniajacy pamiec
	 */
	virtual ~Track();

	// Operations
public:
	/**
	 * Dodaje punkt do trasy
	 * @param	trackPoint	referencja do aktualnych wspolrzednych
	 * @return	@c E_SUCCESS	jesli uda sie dodac punkt do kolekcji
	 * 			@c E_FAILURE	w przeciwnym wypadku
	 */
	result AddPoint(TrackPoint& trackPoint);

	/**
	 * Usuwa wszystkie punkty z kolekcji oraz resetuje wartosci
	 */
	void ClearAll(void);

	/**
	 * Zwraca srednia predkosc
	 * @return srednia predkosc w km/h
	 */
	float GetAvrageSpeed(void) const;

	/**
	 * Ustawia srednia predkosc
	 * @param speed predkosc w km/h
	 */
	void SetAvrageSpeed(float speed);

	/**
	 * Zwraca przebyty dystans
	 * @return dystans w metrach
	 */
	int GetDistance(void) const;

	/**
	 * Ustawia przebyty dystans
	 * @param dystans w metrach
	 */
	void SetDistance(int distance);

	/**
	 * Zwraca czas biegu
	 * Jesli bieg trwa, to zwrocony zostaje akutalny czas.
	 * Jesli bieg sie zakonczyl to zwrocony zostaje calkowity czas biegu.
	 * @return czas w milisekundach
	 */
	TimeSpan GetTotalTime(void) const;

	/**
	 * Ustawia calkowity czas biegu
	 * @param time czas w milisekundach
	 */
	void SetTotalTime(TimeSpan time);

	/**
	 * Zwraca czas rozpoczecia biegu
	 * @return czas w milisekundach od 1.1.01r
	 */
	TimeSpan GetStarTime(void) const;

	/**
	 * Ustawia czas rozpoczecia biegu
	 * @param time czas w milisekundach od 1.1.01r
	 */
	void SetStartTime(TimeSpan time);

	/**
	 * Zwraca czas zakonczenia biegu
	 * @return czas w milisekundach od 1.1.01r
	 */
	TimeSpan GetEndTime(void) const;

	/**
	 * Ustawia czas zakonczenia biegu
	 * @param time czas w milisekundach od 1.1.01r
	 */
	void SetEndTime(TimeSpan time);

	/**
	 * Zwraca czas postoju podczas biegu
	 * @return czas w milisekundach
	 */
	TimeSpan GetPauseTime(void) const;

	/**
	 * Ustawia czas postoju podczas biegu
	 * @param time czas w milisekundach
	 */
	void SetPauseTime(TimeSpan time);

	/**
	 * Zwraca wskaznik do enumeratora  do poczatku listy
	 * @b UWAGA: Nalezy potem zwolnic wskaznik
	 */
	virtual Tizen::Base::Collection::IEnumeratorT<TrackPoint*>* GetEnumeratorN(
			void);

	/**
	 * Zwraca ilosc punktow w trasie
	 * @return Zwraca ilosc punktow w trasie
	 */
	int GetCount(void) const;

	/**
	 * Zwraca ilosc spalonych kcal
	 * @return	liczba kcal
	 */
	int GetCalories(void) const;

	/**
	 * Ustawia ilosc spalonych kcal
	 * @param calories
	 */
	void SetCalories(int kcal);

	// Characteristics class operations

	/**
	 * Zwraca maksymalna osiagnieta wysokosc na trasie
	 * @return wyskosc w metrach
	 */
	float GetMaxAltitude() const;
	/**
	 * Zwraca maksymalna osiagnieta szerokosc geograficzna na trasie
	 * @return szerokosc geograficzna w stopniach
	 */
	float GetMaxLatitude() const;
	/**
	 * Zwraca maksymalna osiagnieta dlugosc geograficzna na trasie
	 * @return szerokosc dlugosc w stopniach
	 */
	float GetMaxLongitude() const;
	/**
	 * Zwraca minimalna osiagnieta wysokosc na trasie
	 * @return wyskosc w metrach
	 */
	float GetMinAltitude() const;
	/**
	 * Zwraca minimalna osiagnieta szerokosc geograficzna na trasie
	 * @return szerokosc geograficzna w stopniach
	 */
	float GetMinLatitude() const;
	/**
	 * Zwraca minimalna osiagnieta dlugosc geograficzna na trasie
	 * @return szerokosc dlugosc w stopniach
	 */
	float GetMinLongitude() const;
	/**
	 * Ustawia maksymalna osiagnieta wysokosc na trasie
	 * @param _maxAltitude wyskosc w metrach
	 */
	void SetMaxAltitude(float maxAltitude);
	/**
	 * Ustawia maksymalna osiagnieta szerokosc geograficzna na trasie
	 * @param _maxLatitude szerokosc geograficzna w stopniach
	 */
	void SetMaxLatitude(float maxLatitude);
	/**
	 * Ustawia maksymalna osiagnieta dlugosc geograficzna na trasie
	 * @param _maxLongitude szerokosc dlugosc w stopniach
	 */
	void SetMaxLongitude(float maxLongitude);
	/**
	 * Ustawia minimalna osiagnieta wysokosc na trasie
	 * @param _minAltitude wyskosc w metrach
	 */
	void SetMinAltitude(float minAltitude);
	/**
	 * Ustawia minimalna osiagnieta szerokosc geograficzna na trasie
	 * @param _minLatitude szerokosc geograficzna w stopniach
	 */
	void SetMinLatitude(float minLatitude);

	/**
	 * Ustawia minimalna osiagnieta dlugosc geograficzna na trasie
	 * @param _minLongitude szerokosc dlugosc w stopniach
	 */
	void SetMinLongitude(float minLongitude);

	/**
	 * Zwraca maksymalna predkosc osiagnieta podczas biegu
	 * @return predkosc w km/h
	 */
	float GetMaxSpeed(void) const;
	/**
	 * Ustawia maksymalna predkosc osiagnieta podczas biegu
	 * @param speed predkosc w km/h
	 */
	void SetMaxSpeed(float speed);

	/**
	 * Ustawia _save
	 * @param state wiesz ocb
	 */
	void SetSave(bool state);

	TrackPoint* GetTrackPointAt(int n);


private:
	void _Reset();

	//Attributes
private:
	Tizen::Base::Collection::LinkedListT<TrackPoint*>* _points;

	// Stats
private:
	float 		_avrageSpeed;
	int 		_distance;
	TimeSpan 	_startTime; // czas rozpoczecia biegu
	TimeSpan 	_endTime; // czas zakonczenia biegu
	TimeSpan 	_totalTime; // calkowity czas biegu
	TimeSpan 	_pauseTime; // czas postoju
	int			_Calories;

	// Characteristics
private:
	float _maxAltitude;
	float _minAltitude;
	float _maxLongitude;
	float _minLongitude;
	float _maxLatitude;
	float _minLatitude;
	float _maxSpeed;

	bool _save;

};

#endif /* TRACK_H_ */

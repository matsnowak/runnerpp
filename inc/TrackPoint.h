/*
 * TrackPoint.h
 *
 *  Created on: 2010-07-14
 *      Author: Mateusz Nowak
 */

#ifndef TRACKPOINT_H_
#define TRACKPOINT_H_

#include <FLocations.h>
#include <FBase.h>

/**
 * @class TrackPoint
 * @brief Reprezentuje punkt na trasie.
 *
 * Przechowuje informacje:
 *  -# wspolrzedne geograficzne
 *  -# wysokosc nad poziomem morza
 *  -# czas zarejestrowania (w milisekundach)
 *
 *  @b Uwaga: Klasa dzedziczy po @b Tizen::Locations::Coordinates, wiec zawiera wszystkie jej metody,
 *   nie opisane tutaj!
 *   @see Tizen::Locations::Coordinates (BadaSDK)
 */
class TrackPoint: public Tizen::Locations::Coordinates {
	// Lifecycle
public:
	/**
	 *  Konstruktor przyjmujacy wspolrzedne i czas w postaci 4 osobnych zmiennych
	 * @param latitude	dlugosc geograficzna
	 * @param longitude	szerokosc geograficzna
	 * @param altitude	wysokosc nad poziomem morza
	 * @param timestamp czas zarejestrowania punktu
	 * @param speed		prdkosc w m/s
	 */
	TrackPoint(float latitude = 0.0f, float longitude = 0.0f, float altitude = 0.0f, long timestamp = 0, float speed = 1.0f);

	/**
	 * Konstruktor przyjmujacy wspolrzedne spakowane w jednej zmiennej, a czas w drugiej
	 * @param coordinates	wspolrzedne geograficzne
	 * @param timespan		czas zarejestrowania punkut
	 * @see Tizen::Base::TimeSpan (BadaSDK)
	 * @see Tizen::Locations::Coordinates (BadaSDK)
	 */
	TrackPoint(Tizen::Locations::Coordinates& coordinates,
			Tizen::Base::TimeSpan& timespan);

	/**
	 * Konstrukotor kopiujacy
	 * @param trackPoint	punkt do skopiowania
	 */
	TrackPoint(const TrackPoint& trackPoint);

	// Accessors
public:
	/**
	 *	Zwraca liczbe milisekund (TimeSpan) od poczatku liczenia czasu (GetMinValue(void)).
	 *
	 *	@return		Obiekt typu TimeSpan (czas w milisekundach)
	 *	@remarks	Zwracana wartosc jest liczba milisekund liczona od wartosci GetMinValue(void).
	 *	@see Tizen::Base::TimeSpan (BadaSDK)
	 */
	Tizen::Base::TimeSpan GetTime(void) const;

	// Operations
public:
	/**
	 * Ustawia predkosc
	 * @param speed predkosc w m/s
	 */
	void SetSpeed(float speed);

	/**
	 * @return zwraca predkosc w m/s
	 */
	float GetSpeed(void ) const;

	/**
	 * Porownuje dwie instancje TrackPoint (pod wzgledem TimeSpan)
	 *
	 * @return		32-bitowa liczba calkowita ze znakiem
	 * @code
	 * <  0  jesli wartosc t1 jest mniejsza niz wartosc t2.
	 * == 0  jesli wartosc t1 jest rowna wartosci t2.
	 * >  0  jesli wartosc t1 jest wieksza niz wartosc t2.
	 * @endcode
	 * @param[in]	t1	Instancja obiekut TrackPoint do porownania
	 * @param[in]	t2	Instancja obiekut TrackPoint do porownania
	 */
	static int Compare(const TrackPoint& t1, const TrackPoint& t2);

	/**
	 * Porownuje aktualna instancje obiektu typu TrackPoint z instacja przekazana jako parametr.
	 * (pod wzgledem TimeSpan)
	 *
	 * @return		32-bitowa liczba calkowita ze znakiem
	 * @code
	 * <  0  jesli wartosc akutalnej instancji jest mniejsza niz wartosc value.
	 * == 0  jesli wartosc akutalnej instancji jest rowna wartosci value.
	 * >  0  jesli wartosc akutalnej instancji jest wieksza niz wartosc value.
	 * @endcode
	 * @param[in]	value	Instancja obiekut TrackPoint do porownania
	 */
	int CompareTo(const TrackPoint& value) const;

	/**
	 * Sprawdza czy instancja podana jako parametr jest rowna instancji wywolujacej
	 *
	 * @return		@c true, jesli instancje sa rowne @n
	 *				@c false, w przeciwnym wypadku
	 * @param[in]	obj Obiekt do porownania z aktualna instancja
	 * @see			GetHashCode()
	 */
	virtual bool Equals(const Object& obj) const;

	/**
	 * Generuje hash dla aktualnego obiektu.
	 *
	 * @return		hash instancji wywolujacej
	 * @see			Tizen::Base::Object::Equals() (BadaSDK)
	 */
	virtual int GetHashCode(void) const;

	/**
	 * Operator przypisania
	 * @param trackPoint obiekt do skopiowania
	 * @return referencja do obiektu po lewej sronie przypisania
	 */
	TrackPoint& operator=(TrackPoint& trackPoint);

	// Attributes
private:
	Tizen::Base::TimeSpan _timeSpan;
	float _speed;  // Predkosc w kilometrach na godzina
	void _Init(float latitude, float longitude, float altitude);

};

#endif /* TRACKPOINT_H_ */

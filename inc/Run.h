/*
 * Run.h
 *
 *  Created on: 2010-07-16
 *      Author: Mateusz Nowak
 */

#ifndef RUN_H_
#define RUN_H_

#include <FSystem.h>
#include <FBase.h>

#include "ITrackPointListener.h"
#include "Track.h"
#include "Vibe.h"
#include "Personalities.h"

/**
 * @enum RunState
 * Opisuje stan biegu
 */
enum RunState {
	RUN_STATE_NOT_STARTED_YET = 0, //!< Bieg sie jeszcze nie rozpoczal
	RUN_STATE_RUNNING, //!< Bieg sie rozpoczal i trwa
	RUN_STATE_PAUSED, //!< Bieg zostal wstrzymany
	RUN_STATE_STOPPED
//!< Bieg zostal zakonczony
};

/**
 * @class Run
 * @brief Klasa reprezentujaca bieg odbywajacy sie w czasie rzeczywistym
 */
class Run: public ITrackPointListener {
	// LifeCycle
public:
	/**
	 * Konstruktor domyslny @n
	 * @b UWAGA: Musisz po nim wywolac @b Construct
	 */
	Run();

	/**
	 * Konstruktor drugo fazowy. Musi zostac wywolany zaraz po konstruktorze domyslnym
	 * @return	@c E_SUCCESS	jesli udalo sie zaalokowac pamiec
	 * 			@c E_FAILURE	w przeciwnym wypadku
	 */
	result Construct(void);
	/**
	 * Destruktor
	 */
	virtual ~Run();

	// Operations
public:
	/**
	 * Rozpoczecie biegu
	 * @return E_SUCCESS jesli da sie roczpoczac bieg (RUN_STATE_NOT_STARTED_YET)
	 * @return E_FAILURE kazda inna wartosc GetState()
	 */
	result Start(void);

	/**
	 * Wstrzymanie biegu
	 * @return	E_SUCCESS jesli da sie wstrzymac bieg (RUN_STATE_RUNNING)@n
	 * @return E_FAILURE kazda inna wartosc GetState()
	 * @see Resume
	 * @see RunState
	 */
	result Pause(void);

	/**
	 * Wznowienie biegu
	 * @return	E_SUCCESS jesli da sie wznowic bieg (RUN_STATE_PAUSED)
	 * @return E_FAILURE kazda inna wartosc GetState()
	 *
	 * @see Pause
	 * @see RunState
	 */
	result Resume(void);

	/**
	 * Zakonczenie biegu
	 * @return E_SUCCESS jesli da sie zakonczyc bieg (RUN_STATE_PAUSED)
	 * @return E_FAILURE kazda inna wartosc GetState()
	 */
	result End(void);

	/**
	 * Dodaje nowy punkt i aktualizuje stan biegu
	 * Nie uzywac explicite! Do wykorzystania przez inne obiekty.
	 * @param trackPoint	nowe polozenie
	 * @see TrackPoint
	 */
	virtual void SentNewTrackPoint(TrackPoint& trackPoint);

	/**
	 * Zwraca srednia predkosc
	 * @return srednia predkosc w km/h
	 */
	float GetAvrageSpeed(void) const;

	/**
	 * Zwraca aktualna predkosc
	 * @return predkosc chwilowa w km/h
	 */
	float GetCurrentSpeed(void) const;

	/**
	 * Zwraca przebyty dystans
	 * @return dystans w metrach
	 */
	float GetDistance(void) const;

	/**
	 * Zwraca ilosc spalonych kcal podczas biegu
	 * @return	ilosc kcal
	 */
	int GetCalories(void) const;

	/**
	 * Zwraca czas biegu
	 * Jesli bieg trwa, to zwrocony zostaje akutalny czas.
	 * Jesli bieg sie zakonczyl to zwrocony zostaje calkowity czas biegu.
	 * @return czas w milisekundach
	 */
	Tizen::Base::TimeSpan GetTime(void) const;

	/**
	 * Zwraca wskaznik do enumeratora  do poczatku kolekcji punktow
	 * @b UWAGA: Nalezy potem zwolic wskaznik
	 */
	virtual Tizen::Base::Collection::IEnumeratorT<TrackPoint*>* GetEnumeratorN(
			void);

	/**
	 * Zwraca ilosc punktow zarejestrowanych podczas biegu
	 * @return	ilosc punktow w biegu
	 */
	int GetPointsCount(void) const;

	/**
	 * Zwraca stan biegu
	 * @return stan biegu
	 * @see RunState
	 */
	RunState GetState(void) const;

	/**
	 * Zwraca wskaznik do trasy @n
	 * @c UWAGA: Bierzesz go na wlasna odpowiedzialnosc, jak zostanie usuniety to
	 * miej pretensje do siebie.
	 * @return wskaznik do trasy
	 */
	Track* GetTrackN(void);

	/**
	 * Zwraca stan biegu
	 * @return	@c true		jesli trwa bieg
	 * 			@c false	w kazdym innym przypadku
	 */
	bool IsRunning(void) const;

private:
	void _setState(RunState state);

	void _calculateTotalDistance(TrackPoint& newPoint);
	void _calculateLastDistance(TrackPoint& newPoint);
	void _calculateAvrageSpeed(TrackPoint& newPoint);
	void _calculateCurrentSpeed(TrackPoint& newPoint);
	void _calculateLastTime(TrackPoint& newPoint);
	void _calculateCalories(void);

	void _playSounds(int distance);

	// Attributes
private:
	float _avrageSpeed;
	float _currentSpeed;
	float _totalDistance;
	float _lastDistance; // odleglosc pomiedzy dwoma ostatnimi pomiarami
	long long _startTimeWatch; // czas rozpoczecia biegu,potrzebny do ladnej animacji biegu
	long long _totalPauseTime; // czas postoju
	long long _endTimeWatch; // czas zakonczenia biegu,potrzebny do ladnej animacji biegu
	long long _currTime; // aktualny czas pobrany z zegara
	long long _totalTime; // calkowity czas biegu (koniec - poczatek)
	DateTime _startTime;//prawdziwy czas poczatku biegu ! (taki jak ma na zegarze na komorce)
	DateTime _endTime;//prawdziwy koniec biegu

	int	_totalCalories; // Ilosc spalonych kalorii

	long long _pauseStartTime; // czas rozpoczecia pojedynczego postoju
	long long _pauseEndTime; // czas zakonczenia pojedynczego postoju

	TimeSpan _lastTime; // roznica czasu pomiedzy dwoma ostatnimi pomiarami
	RunState _state;

	TrackPoint _lastPoint;
	Track* _track;

	bool _isOnePointAdded;
	bool _isOnePointReceinved;

	void SetTrack();

	/* Do obslugi dzwieku  i wibracji */

	static const int DISTANCE_MARKERS_ARRAY_SIZE = 17;

	//Tablica dystansow, wypelniamy po jakim dystansie ma zostac odegrane powiadomienie
	static const int DISTANCE_MARKERS_ARRAY[];
	int _currIndex;
	Vibe _vibrator;

	// Liczba spalonych kalorii / 1 min / 1km/h / 1 kg / 1cm   ~= 9,7455648926237161531279178338002e-5
	static const double KCAL_UNIT = 835 / 60 / 12 / 70 / 170;
	int _weight;
	int _height;

};

#endif /* RUN_H_ */

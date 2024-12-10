/*
 * Run.cpp
 *
 *  Created on: 2010-07-16
 *      Author: Mateusz Nowak
 */

#include "Run.h"
#include "RunnerPP.h"

using Tizen::Base::TimeSpan;
using namespace Tizen::App;

Run::Run() :
	_avrageSpeed(0.0f), _currentSpeed(0.0f), _totalDistance(0.0f),
			_lastTime(0), _totalPauseTime(0), _lastPoint(0, 0, 0, 0), _state(
					RUN_STATE_NOT_STARTED_YET), _isOnePointReceinved(false),
			_endTimeWatch(0), _startTimeWatch(0), _pauseEndTime(0), _pauseStartTime(0),
			_totalTime(0), _totalCalories(0) {
	Personalities temp;
	temp.Construct();

	_weight = temp.GetWeight();
	_height = temp.GetHeight();
}

result Run::Construct(void) {
	result r;
	_track = new Track();
	if (null != _track) {
		_track->Construct();

		SetTrack();
		r = E_SUCCESS;
	} else
		r = E_FAILURE;
	_vibrator.Construct();
	return r;
}

Run::~Run() {
	//	if (null != _track) {
	//		delete _track;
	//		_track = null;
	//	}

}

result Run::Start(void) {
	if (RUN_STATE_NOT_STARTED_YET == _state) {
		_setState(RUN_STATE_RUNNING);
		Tizen::System::SystemTime::GetTicks(_startTimeWatch);
		Tizen::System::SystemTime::GetCurrentTime(WALL_TIME,_startTime);
		_currIndex = 0;
		_isOnePointReceinved = false;
		return E_SUCCESS;
	}
	return E_FAILURE;
}

result Run::End(void) {
	if (RUN_STATE_PAUSED == _state) {
		_setState(RUN_STATE_STOPPED);
		Tizen::System::SystemTime::GetTicks(_endTimeWatch);
		Tizen::System::SystemTime::GetTicks(_pauseEndTime);
		Tizen::System::SystemTime::GetCurrentTime(WALL_TIME,_endTime);
		_totalTime = _endTimeWatch - _startTimeWatch - _totalPauseTime;
		_setState(RUN_STATE_STOPPED);

		_track->SetAvrageSpeed(_avrageSpeed);
		_track->SetDistance((int)_totalDistance);
		_track->SetEndTime(_endTime.GetTime().GetTicks());
		_track->SetPauseTime(_totalPauseTime);
		_track->SetStartTime(_startTime.GetTime().GetTicks());
		_track->SetTotalTime(_totalTime);
		_track->SetCalories(_totalCalories);

		return E_SUCCESS;
	}
	return E_FAILURE;
}

void Run::SentNewTrackPoint(TrackPoint& trackPoint) {
	switch (_state) {
	case RUN_STATE_RUNNING: {

		if (false == _isOnePointReceinved) {
			_isOnePointReceinved = true;
		} else {

			// UWAGA! Nie zmieniac kolejnosci obliczen
			_calculateLastDistance(trackPoint);
			_calculateTotalDistance(trackPoint);

			_calculateLastTime(trackPoint);

			_calculateCurrentSpeed(trackPoint);
			_calculateAvrageSpeed(trackPoint);

			_calculateCalories();

			_track->AddPoint(trackPoint);
			if (_currentSpeed > _track->GetMaxSpeed())
				_track->SetMaxSpeed(_currentSpeed);

			//AppLog("currSpeed:%f avrageSpeed:%f distance:%f calories:%d",_currentSpeed,_avrageSpeed,_totalDistance,_totalCalories);


			// Obsluga vibracji
			_vibrator.Vibrate(_totalDistance);
		}
	}
		break;
	case RUN_STATE_PAUSED:
		if (false == _isOnePointAdded) {
			_track->AddPoint(trackPoint);
			_isOnePointAdded = true;
		}
		break;
	default:
		break;
	}

	_lastPoint = trackPoint;
}

float Run::GetDistance(void) const {
	return _totalDistance;
}

float Run::GetAvrageSpeed(void) const {
	return _avrageSpeed;
}

float Run::GetCurrentSpeed(void) const {
	return _currentSpeed;
}

TimeSpan Run::GetTime(void) const {
	long long currTime;
	if (true == IsRunning()) {
		Tizen::System::SystemTime::GetTicks(currTime);
		return TimeSpan(currTime - _startTimeWatch - _totalPauseTime);
	} else
		return TimeSpan(_endTimeWatch - _startTimeWatch - _totalPauseTime);
}

bool Run::IsRunning(void) const {
	return RUN_STATE_RUNNING == _state;
}

void Run::_calculateTotalDistance(TrackPoint & newPoint) {
		_totalDistance += _lastDistance;
}

void Run::_calculateCurrentSpeed(TrackPoint & newPoint) {
	// Mamy m/ms, mnozymy przez ilosc milisekund w godzinie, zeby dostac m/h
	// i dzielimy przez 1000 zeby dostac km/h
	_currentSpeed = newPoint.GetSpeed();
}

void Run::_calculateAvrageSpeed(TrackPoint & newPoint) {
	// Mamy m/ms, mnozymy przez ilosc milisekund w godzinie, zeby dostac m/h
	// i dzielimy przez 1000 zeby dostac km/h
	_avrageSpeed = ((_totalDistance / GetTime().GetTicks())
			* TimeSpan::NUM_OF_TICKS_IN_HOUR) / 1000;
	//AppLog("%f",_avrageSpeed);
}

void Run::_calculateLastDistance(TrackPoint & newPoint) {
	// odleglosc miedzy dwoma ostatnimi punktami pomiaru
	//_lastDistance = newPoint.Distance(_lastPoint);

	_lastDistance = ((newPoint.GetSpeed()/3.6)+newPoint.GetDistanceTo(_lastPoint))/2;

}

Tizen::Base::Collection::IEnumeratorT<TrackPoint*> *Run::GetEnumeratorN(void) {
	return _track->GetEnumeratorN();
}

int Run::GetPointsCount(void) const {
	return _track->GetCount();
}

RunState Run::GetState(void) const {
	return _state;
}

result Run::Pause(void) {
	if (RUN_STATE_RUNNING == _state) {
		_setState(RUN_STATE_PAUSED);
		Tizen::System::SystemTime::GetTicks(_pauseStartTime);
		_isOnePointReceinved = false;
		_lastDistance = 0.0f;
		_currentSpeed = 0.0f;
		return E_SUCCESS;
	}
	return false;
}

result Run::Resume(void) {
	if (RUN_STATE_PAUSED == _state) {
		Tizen::System::SystemTime::GetTicks(_pauseEndTime);
		_setState(RUN_STATE_RUNNING);
		_totalPauseTime += (_pauseEndTime - _pauseStartTime);

		return E_SUCCESS;
	}
	return false;
}

void Run::_setState(RunState state) {
	_state = state;
}

Track *Run::GetTrackN(void) {
	return _track;
}

void Run::_calculateLastTime(TrackPoint & newPoint) {
	_lastTime = newPoint.GetTime() - _lastPoint.GetTime();
}

int Run::GetCalories(void) const {
	return _totalCalories;
}

void Run::_calculateCalories(void) {
	//AppLog("Wtf: %d",GetTime().GetTicks());
	//AppLog("kcal: %f",_avrageSpeed);
	//AppLog("cal: %d",_totalCalories);
	float cal1 = _height * _weight * 0.00009;
	float cal2 = (float)GetTime().GetTicks()/60000;
	float cal3 = cal1*cal2* _avrageSpeed;
	//FIXME: poprawic ten shit
	//AppLog("cal1 ! %f cal2 ! %f cal3 ! %f",cal1,cal2,cal3);
	_totalCalories = (int)cal3;
}

void Run::_playSounds(int distance) {
	int kilometers = distance / 1000;
	int onesNumber = distance % 10;
	kilometers /= 10;
	int tensNumber = distance % 10;

}

void Run::SetTrack(){
	RunnerPP* run =static_cast<RunnerPP*>(Application::GetInstance());
	run->SetTrack(_track);
	run->NewTrack();

	// nazwa_globalnej_zmiennej_track = track;

}


//Przykladowa funkcja wypisujaca tekst, zamiast odegrania dzwieku
void P(int number) {
	for (int i = 0; i < number; i++) {
		//AppLog("Odczekam sobie sekundke");
		Tizen::Base::Runtime::Thread::Sleep(1000);
	}
}


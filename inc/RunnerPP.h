#ifndef __RUNNERPP_H__
#define __RUNNERPP_H__

#include <FApp.h>
#include <FBase.h>
#include <FGraphics.h>
#include <FSystem.h>

#include "Track.h"

/**
 * [RunnerPP] application must inherit from Application class
 * which provides basic features necessary to define an application.
 */
class RunnerPP :
	public Tizen::App::Application,
	public Tizen::System::IScreenEventListener
{
public:
	// [RunnerPP] application must have a factory method that creates an instance of itself.
	static Tizen::App::Application* CreateInstance(void);

public:
	RunnerPP();
	~RunnerPP();

public:


	// Called when the application is initializing.
	bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);

	// Called when the application is terminating.
	bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);

	// Called when the application's frame moves to the top of the screen.
	void OnForeground(void);

	// Called when this application's frame is moved from top of the screen to the background.
	void OnBackground(void);

	// Called when the system memory is not sufficient to run the application any further.
	void OnLowMemory(void);

	// Called when the battery level changes.
	void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);

	// Called when the screen turns on.
	void OnScreenOn (void);

	// Called when the screen turns off.
	void OnScreenOff (void);

	void NewTrack();
	void TrackSaved();

	Track* GetTrack();
	void SetTrack(Track* __value);
	void ClearTrack();

	bool NeedToBeSaved();

private:
	Track* _pTrack;//globalny wskaznik na obiekt klasy track
	bool _newTrack;//jak mamy cos zapisac to to musi byc ustawione !
};

#endif	//__RUNNERPP_H__

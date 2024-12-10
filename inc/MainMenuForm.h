/*
 * MainMenuForm.h
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#ifndef MAINMENUFORM_H_
#define MAINMENUFORM_H_

#define ADS

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>
#include <FApp.h>
#include <FSystem.h>
#if defined(ADS)
#include "Smaato/IAdResponseListener.h"
#include "Smaato/AdControl.h"
#endif
#include "IBaseForm.h"
#include "FormMgr.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;


class MainMenuForm :
	public IBaseForm,
	public IActionEventListener
#if defined(ADS)
	,public Smaato::AdSDK::IAdResponseListener
#endif
{
private:
	Bitmap* _pBackground;
#if defined(ADS)
	Smaato::AdSDK::AdControl * _pAd;
	Tizen::Ui::Controls::Button* _pExit;
#endif

	static const int ID_RUN		= 100;
	static const int ID_STATS	= 101;
	static const int ID_OPTIONS	= 102;
	static const int ID_INFO	= 103;
	static const int ID_EXIT	= 104;

	bool _isGpsEnabled;


public:
	MainMenuForm();
	virtual ~MainMenuForm();

	bool Initialize();
	result OnDraw();
	result OnInitializing();
	result OnTerminating();

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
#if defined(ADS)
	virtual void OnComunicationError(result r, const Tizen::Base::String& desc);
	virtual void OnNewAdAvailable(Smaato::AdSDK::AdContainer& adContainer);
#endif

private:
	result CheckGpsState();

};

#endif /* MAINMENUFORM_H_ */

/*
 * StatsForm.h
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#ifndef STATSFORM_H_
#define STATSFORM_H_

#include "IBaseForm.h"
#include "FormMgr.h"

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>

/**
 * @class	StatsForm
 * @brief	Widok Statystyk globalnych
 * 			Klasa raczej Copy&Paste
 */

class StatsForm :
	public IBaseForm,
	public Tizen::Ui::IActionEventListener
{
private:
	Tizen::Graphics::Bitmap* _pBackground;
	Tizen::Graphics::EnrichedText* _pFormName;
	Tizen::Graphics::EnrichedText* _pTotalTime;
	Tizen::Graphics::EnrichedText* _pTotalDistance;
	Tizen::Graphics::EnrichedText* _pTotalCalories;
	Tizen::Graphics::EnrichedText* _pLongestRun;
	Tizen::Graphics::EnrichedText* _pFurthestRun;
	Tizen::Graphics::EnrichedText* _pMaxSpeed;
	Tizen::Graphics::EnrichedText* _pAvrageSpeed;

	static const int ID_TO_CHOOSE_TRACK=100;
	static const int ID_TO_MAINMENU=101;
	void CreateTexts();
	void CreateText(Tizen::Base::String id, Tizen::Graphics::EnrichedText *& eText, Tizen::Graphics::Font *& pFont);

public:
	StatsForm();
	virtual ~StatsForm();

	bool Initialize();
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
};

#endif /* STATSFORM_H_ */

/*
 * TrackStatsFormForm.h
 *
 *  Created on: 2010-07-28
 *      Author: Pavel
 */

#ifndef TRACKSTATSFORM_H_
#define TRACKSTATSFORM_H_


#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>

#include "IBaseForm.h"

/**
 * @class	TrackStatsForm
 * @brief	Widok TrackStatsForm
 * 			Klasa raczej Copy&Paste
 */

class TrackStatsForm :
	public IBaseForm,
	public Tizen::Ui::IActionEventListener
{
private:
	Tizen::Graphics::Bitmap* _pBackground;
	Tizen::Graphics::EnrichedText* _pTime;
	Tizen::Graphics::EnrichedText* _pDistance;
	Tizen::Graphics::EnrichedText* _pCalories;
	Tizen::Graphics::EnrichedText* _pMaxSpeed;
	Tizen::Graphics::EnrichedText* _pAvrageSpeed;
	Tizen::Graphics::EnrichedText* _pFormName;

	static const int ID_TO_MAINMENU = 100;
	static const int ID_TO_CHOOSEFORM = 101;
	static const int ID_RIGHT_ARROW = 102;
	static const int ID_SAVE = 103;
    void CreateTexts();
    void CreateText(Tizen::Base::String id, Tizen::Graphics::EnrichedText *& eText, Tizen::Graphics::Font *& pFont);
public:
	TrackStatsForm();
	virtual ~TrackStatsForm();

	bool Initialize();
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
};

#endif /* TRACKSTATSFORM_H_ */

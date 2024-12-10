/*
 * OptionsForm.h
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#ifndef OPTIONSFORM_H_
#define OPTIONSFORM_H_


#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>

#include "IBaseForm.h"
#include "FormMgr.h"
#include "Options.h"


/**
 * @class	OptionsForm
 * @brief	Widok Options
 * 			Klasa raczej Copy&Paste
 */

class OptionsForm :
	public IBaseForm,
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::IAdjustmentEventListener

{
private:
	Tizen::Graphics::Bitmap* _pBackground;
	Tizen::Graphics::Bitmap* _pON;
	Tizen::Graphics::Bitmap* _pOFF;
	Tizen::Ui::Controls::Slider* _pWeightImput;
	Tizen::Ui::Controls::Slider* _pHeightImput;
	Tizen::Ui::Controls::Button* _pVibe;
	Tizen::Ui::Controls::Slider* _pVibeImputLevel;
	Tizen::Ui::Controls::Slider* _pVibeImputDistance;
	Tizen::Ui::Controls::Button* _pClearDB;
	Tizen::Ui::Controls::ScrollPanel* _pScrollPanel;
	Options* _pOptions;
	bool _showVibe;
	Tizen::Graphics::EnrichedText* _pFormName;


	static const int ID_TO_MAINMENU = 100;

	static const int ID_ON_OFF = 200;
	static const int ID_CLEAR_DB = 201;

	void VibeOnOff();
	Tizen::Graphics::Bitmap* CreateBitmapText(Tizen::Base::String str, int width,int height,int size);
	void CreateOnOffBitmaps();
public:
	OptionsForm();
	virtual ~OptionsForm();

	bool Initialize();
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	virtual void OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment);

};

#endif /* OPTIONSFORM_H_ */

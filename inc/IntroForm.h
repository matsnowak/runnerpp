/*
 * IntroForm.h
 *
 *  Created on: 2010-08-30
 *      Author: Pavel
 */

#ifndef INTROFORM_H_
#define INTROFORM_H_
#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>

#include "IBaseForm.h"
#include "FormMgr.h"
#include "Options.h"


/**
 * @class	InfoForm
 * @brief	Forma Info ;D
 */

class IntroForm :
	public IBaseForm,
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::IAdjustmentEventListener
{
private:
	Tizen::Graphics::Bitmap* _pBackground;

	static const int ID_TO_MAINMENU=100;

	Tizen::Ui::Controls::Slider* _pWeightImput;
	Tizen::Ui::Controls::Slider* _pHeightImput;
	Tizen::Graphics::EnrichedText* _pGreeting;
	Tizen::Graphics::EnrichedText* _pWeightAndHeight;
	Tizen::Graphics::EnrichedText* _pInformation;
	Options* _pOptions;
    void WelcomeText();
public:
	IntroForm();
	virtual ~IntroForm();

	bool Initialize();
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	void OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment);
};

#endif /* INTROFORM_H_ */

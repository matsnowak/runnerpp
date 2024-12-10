/*
 * OptionsForm.h
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#ifndef SavingFormCF_H_
#define SavingFormCF_H_


#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>

#include "IBaseForm.h"
#include "FormMgr.h"



/**
 * @class	SavingForm
 * @brief	Pokazuje napis Zapisuje i zapisuje w tle ! ;D
 * 			Klasa raczej Copy&Paste
 */

class SavingFormCF :
	public IBaseForm,
	public Tizen::Base::Runtime::ITimerEventListener
{
private:
	Tizen::Graphics::Bitmap* _pBackground;
	Tizen::Base::Runtime::Timer* _pTimer;
public:
	SavingFormCF();
	virtual ~SavingFormCF();

	bool Initialize();
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	virtual void  OnTimerExpired (Tizen::Base::Runtime::Timer &timer);



};

#endif /* SavingForm_H_ */

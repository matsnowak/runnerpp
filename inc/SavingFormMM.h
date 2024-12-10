/*
 * OptionsForm.h
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#ifndef SavingFormMM_H_
#define SavingFormMM_H_


#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>

#include "IBaseForm.h"
#include "FormMgr.h"
#include "Options.h"


/**
 * @class	SavingForm
 * @brief	Pokazuje napis Zapisuje i zapisuje w tle ! ;D
 * 			Klasa raczej Copy&Paste
 */

class SavingFormMM :
	public IBaseForm

{
private:
	Tizen::Graphics::Bitmap* _pBackground;
public:
	SavingFormMM();
	virtual ~SavingFormMM();

	bool Initialize();
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

};

#endif /* SavingFormMM_H_ */

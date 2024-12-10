/*
 * InfoForm.h
 *
 *  Created on: 2010-08-30
 *      Author: Pavel
 */

#ifndef INFOFORM_H_
#define INFOFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>
#include <FWeb.h>

#include "IBaseForm.h"
#include "FormMgr.h"


/**
 * @class	AboutForm
 * @brief	Forma About ;D
 */

class InfoForm :
	public IBaseForm,
	public Tizen::Ui::IActionEventListener
{
private:
	Tizen::Graphics::Bitmap* _pBackground;
	Tizen::Web::Controls::Web* _pWeb;

	static const int ID_TO_MAINMENU=100;
	static const int ID_FORM1 = 101;

public:
	InfoForm();
	virtual ~InfoForm();

	bool Initialize();
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
};

#endif /* INFOFORM_H_ */

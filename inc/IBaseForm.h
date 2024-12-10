/*
 * MainMenuForm.h
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#ifndef IBASEFORM_H_
#define IBASEFORM_H_

#define SCALE_FACTOR 1.5f

#include <FBase.h>
#include <FUi.h>

class IBaseForm: public Tizen::Ui::Controls::Form {
public:
//	IBaseForm();
//	virtual ~IBaseForm();

	virtual bool Initialize() = 0;
//	virtual result OnDraw();
//	virtual result OnInitializing();
//	virtual result OnTerminating();
};

#endif /* IBASEFORM_H_ */

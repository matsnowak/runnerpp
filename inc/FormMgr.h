/*
 * FormMgr.h
 *
 *  Created on: 2010-07-27
 *      Author: Mateusz Nowak & Pawel Huber
 */

#ifndef FORMMGR_H_
#define FORMMGR_H_

#include <FBaseColArrayList.h>
#include <FBaseCol.h>
#include <FUi.h>
#include <FApp.h>

#include "IBaseForm.h"
#include "TrackStatsForm.h"
#include "Graph/Graph.h"


using namespace Tizen::Base;
using namespace Tizen::App;


class FormMgr: public Tizen::Ui::Controls::Form {
public:
	FormMgr();
	virtual ~FormMgr();

	bool Initialize(void);
	bool SetStarterForm(RequestId requestId,
			Tizen::Base::Collection::IList* pArgs);

	static const RequestId REQUEST_MENUFORM = 100;
	static const RequestId REQUEST_RUNFORM = 101;
	static const RequestId REQUEST_STATSFORM = 102;
	static const RequestId REQUEST_CHOOSETRACKFORM = 103;
	static const RequestId REQUEST_OPTIONSFORM = 104;
	static const RequestId REQUEST_INFOFORM = 105;
	static const RequestId REQUEST_HELPFORM = 106;
	static const RequestId REQUEST_ABOUTFORM = 107;
	static const RequestId REQUEST_INTROFORM= 108;
	static const RequestId REQUEST_SAVEFORM =109;
	static const RequestId REQUEST_ERRORFORM =110;

	static const RequestId REQUEST_TRACKSTATSFORM = 200;
	static const RequestId REQUEST_GRAPHFORM = 201;
	static const RequestId REQUEST_EXIT_TO_CHOOSEFORM = 203;
	static const RequestId REQUEST_EXIT_TO_MAINMENU = 204;

protected:
	void SwitchToForm(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
	IBaseForm* _pCurrentForm;

public:
	virtual void OnUserEventReceivedN(RequestId requestId,
			Tizen::Base::Collection::IList* pArgs);
};

#endif /* FORMMGR_H_ */

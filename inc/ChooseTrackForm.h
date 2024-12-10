/*
 * ChooseTrackForm.h
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#ifndef CHOOSETRACKFORM_H_
#define CHOOSETRACKFORM_H_


#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>

#include "IBaseForm.h"
#include "FormMgr.h"
#include "DatabaseScanner.h"
#include "RunnerPP.h"
#include "ListContextMenu.h"


/**
 * @class	ChooseTrackForm
 * @brief	Widok w ktorym wybieramy jaki Track wybrac z bazy
 * 			Klasa raczej Copy&Paste
 */

class ChooseTrackForm :
	public IBaseForm,
	public Tizen::Ui::IActionEventListener,
	public IListContextMenuListener
{
private:
	Tizen::Graphics::Bitmap* _pBackground;
	Tizen::Graphics::EnrichedText* _pFormName;
	Tizen::Ui::Controls::List* _pList;
	ListContextMenu *_pContextMenu;

	static const int ID_LEFT_ARROW = 100;
	static const int ID_TO_MAINMENU= 101;
	static const int ID_TRACKSTATS=102;

	static const int ID_SHOW=200;
	static const int ID_DELETE=201;
    void DeleteTrack(int  itemId);
    void LoadList();
    void UpdateList();


public:
	ChooseTrackForm();
	virtual ~ChooseTrackForm();

	bool Initialize();
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	void OnShowStateChanged(bool show);
	void OnListContextMenuAction(int &actionId, int &itemId);
	void ShowTrack(int id);
};

#endif /* CHOOSETRACKFORM_H_ */

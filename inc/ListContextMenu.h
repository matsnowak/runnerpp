/*
 * ListContextMenu.h
 *
 *      Author: Wit, BadaDev
 */

#ifndef LISTCONTEXTMENU_H_
#define LISTCONTEXTMENU_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>

#include "IListContextMenuListener.h"

class ListContextMenu :
	public Tizen::Ui::Controls::ContextMenu,
	protected Tizen::Ui::ITouchEventListener,
	protected Tizen::Ui::IActionEventListener
{
public:
	ListContextMenu();
	virtual ~ListContextMenu();

	result Construct(Tizen::Ui::Control &alist, IListContextMenuListener &listener);
	void BindList(Tizen::Ui::Controls::List &list);
	void BindList(Tizen::Ui::Controls::CustomList &customlist);
	void ShowContextMenu(bool show);

protected:
	Tizen::Ui::Controls::List * list_;
	Tizen::Ui::Controls::CustomList * customlist_;
	IListContextMenuListener * listener_;
	long long int  _start;
	long long int _end;

	int selected_list_item_;
	int selected_id;

	bool _moved;


// callbacks
protected:
	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	void OnTouchPressed(const Tizen::Ui::Control& source,
		const Tizen::Graphics::Point& currentPosition,const Tizen::Ui::TouchEventInfo & touchInfo);
	void OnTouchLongPressed(const Tizen::Ui::Control& source,
		const Tizen::Graphics::Point& currentPosition ,const Tizen::Ui::TouchEventInfo & touchInfo);
	void OnTouchReleased(const Tizen::Ui::Control& source,
		const Tizen::Graphics::Point& currentPosition ,const Tizen::Ui::TouchEventInfo & touchInfo);
	void OnTouchMoved(const Tizen::Ui::Control& source,
		const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo & touchInfo);
	void OnTouchDoublePressed(const Tizen::Ui::Control& source,
		const Tizen::Graphics::Point& currentPosition,const Tizen::Ui::TouchEventInfo & touchInfo);
	void OnTouchFocusIn(const Tizen::Ui::Control& source,
		const Tizen::Graphics::Point& currentPosition,const Tizen::Ui::TouchEventInfo & touchInfo);
	void OnTouchFocusOut(const Tizen::Ui::Control& source,
		const Tizen::Graphics::Point& currentPosition,const Tizen::Ui::TouchEventInfo & touchInfo);
};

#endif /* LISTCONTEXTMENU_H_ */

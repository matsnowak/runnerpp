/*
 * ListContextMenu.cpp
 *
 *      Author: Wit, BadaDev
 */

#include "ListContextMenu.h"
#include <FSystem.h>
#include <FBase.h>

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::System;

ListContextMenu::ListContextMenu() : list_(NULL), customlist_(NULL), listener_(NULL), selected_list_item_(-1),_start(0),_end(0),
		_moved(false)
{}

ListContextMenu::~ListContextMenu() {
	// TODO Auto-generated destructor stub
}


result
ListContextMenu::Construct(Control &alist, IListContextMenuListener &listener)
{
	result r = ContextMenu::Construct(Point(50,50), CONTEXT_MENU_STYLE_LIST);
	listener_ = &listener;

	List * list = NULL;
	CustomList * customlist = NULL;
	list = dynamic_cast<List *>(&alist);
	customlist = dynamic_cast<CustomList *>(&alist);
	if(list) BindList(*list);
	if(customlist) BindList(*customlist);

	this->AddActionEventListener(*this);
	return r;
}


void
ListContextMenu::BindList(List &list)
{
	list_ = &list;
	list_->AddTouchEventListener(*this);
	customlist_ = NULL;
}

void
ListContextMenu::BindList(CustomList &customlist)
{
	customlist_ = &customlist;
	customlist_->AddTouchEventListener(*this);
	list_ = NULL;
}


void
ListContextMenu::ShowContextMenu(bool show)
{
	 this->SetShowState(show);
	 if (show == true)
		 this->Show();
	 if(listener_) listener_->OnShowStateChanged(show);
}


void
ListContextMenu::OnActionPerformed(const Control& source, int actionId)
{
	if(listener_) listener_->OnListContextMenuAction(actionId, selected_id);
}

void
ListContextMenu::OnTouchPressed(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo){
	Tizen::System::SystemTime::GetTicks(_start);
}

void
ListContextMenu::OnTouchLongPressed(const Control& source,
	const Point& currentPosition ,const TouchEventInfo & touchInfo)
{

}

void
ListContextMenu::OnTouchReleased(const Control& source,
	const Point& currentPosition ,const TouchEventInfo & touchInfo){
	if(_moved) {
		_moved = false;
		return;
	}
	Tizen::System::SystemTime::GetTicks(_end);
	if((_end-_start)>=1000){
		if(&source!=list_ && &source!=customlist_) return;
			if(&source==list_)
			{
				selected_list_item_ = list_->GetItemIndexFromPosition(currentPosition);
				if(selected_list_item_ == -1) return;
				selected_id = list_->GetItemIdAt(selected_list_item_);
				this->SetPosition(currentPosition.x + list_->GetBounds().x, currentPosition.y + list_->GetBounds().y+38);
			} else if (&source==customlist_){
				selected_list_item_ = customlist_->GetItemIndexFromPosition(currentPosition);
				if(selected_list_item_ == -1) return;
				this->SetPosition(currentPosition.x + customlist_->GetBounds().x, currentPosition.y + customlist_->GetBounds().y+38);
			} else {
				selected_list_item_ = -1;
			}

			if(selected_list_item_ >= 0) ShowContextMenu(true);
	} else {
		selected_list_item_= list_->GetItemIndexFromPosition(currentPosition);
		if(selected_list_item_ != -1){
			selected_id = list_->GetItemIdAt(selected_list_item_);
			listener_->ShowTrack(selected_id);
		}
	}
}

void
ListContextMenu::OnTouchMoved(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo){
	_moved = true;
}

void
ListContextMenu::OnTouchDoublePressed(const Control& source,
	const Point& currentPosition,const TouchEventInfo & touchInfo){}

void
ListContextMenu::OnTouchFocusIn(const Control& source,
		const Point& currentPosition,const TouchEventInfo & touchInfo){
}

void
ListContextMenu::OnTouchFocusOut(const Control& source,
		const Point& currentPosition,const TouchEventInfo & touchInfo){
}

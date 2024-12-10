/*
 * IListContextMenuListener.h
 *
 *      Author: Wit, BadaDev
 */

#ifndef ILISTCONTEXTMENULISTENER_H_
#define ILISTCONTEXTMENULISTENER_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>

class IListContextMenuListener {
public:
	virtual void OnShowStateChanged(bool show) = 0;
	virtual void OnListContextMenuAction(int &actionId, int &itemId) = 0;
	virtual void ShowTrack(int id) = 0;
};

#endif /* ILISTCONTEXTMENULISTENER_H_ */

/***********************************************************************
Menu - Subclass of RowColumn that only contains buttons and acts as a
pop-up menu.
Copyright (c) 2001-2005 Oliver Kreylos

This file is part of the GLMotif Widget Library (GLMotif).

The GLMotif Widget Library is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GLMotif Widget Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with the GLMotif Widget Library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
***********************************************************************/

#ifndef GLMOTIF_MENU_INCLUDED
#define GLMOTIF_MENU_INCLUDED

#include <Misc/CallbackData.h>
#include <Misc/CallbackList.h>
#include <GLMotif/Button.h>
#include <GLMotif/RowColumn.h>

namespace GLMotif {

class Menu:public RowColumn
	{
	/* Embedded classes: */
	public:
	class CallbackData:public Misc::CallbackData // Base class for callback data sent by menu widgets
		{
		/* Elements: */
		public:
		Menu* menu; // Pointer to the menu widget that caused the event
		
		/* Constructors and destructors: */
		CallbackData(Menu* sMenu)
			:menu(sMenu)
			{
			}
		};
	
	class EntrySelectCallbackData:public CallbackData // Class for callback data sent when a menu entry is selected
		{
		/* Elements: */
		public:
		Button* selectedButton; // Pointer to the button causing the event
		Button::SelectCallbackData* selectCallbackData; // Callback data generated by the button event
		
		/* Constructors and destructors: */
		EntrySelectCallbackData(Menu* sMenu,Button* sSelectedButton,Button::SelectCallbackData* sSelectCallbackData)
			:CallbackData(sMenu),selectedButton(sSelectedButton),selectCallbackData(sSelectCallbackData)
			{
			}
		};
	
	/* Elements: */
	protected:
	Misc::CallbackList entrySelectCallbacks; // List of callbacks to be called when a menu entry is selected
	
	/* Protected methods: */
	static void childrenSelectCallbackWrapper(Misc::CallbackData* callbackData,void* userData); // Callback that is called when a child is selected
	
	/* Constructors and destructors: */
	public:
	Menu(const char* sName,Container* sParent,bool manageChild =true);
	
	/* Methods inherited from Container: */
	virtual void addChild(Widget* newChild);
	
	/* New methods: */
	void addEntry(const char* newEntryLabel); // Adds a new menu entry button with the given label
	Misc::CallbackList& getEntrySelectCallbacks(void) // Returns list of entry select callbacks
		{
		return entrySelectCallbacks;
		}
	int getEntryIndex(const Button* entry) const; // Returns the index of the given menu entry, or -1 if the button is not a child of the menu
	};

}

#endif
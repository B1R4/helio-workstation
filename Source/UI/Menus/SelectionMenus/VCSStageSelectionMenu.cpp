/*
    This file is part of Helio Workstation.

    Helio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helio. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Common.h"
#include "VCSStageSelectionMenu.h"
#include "VersionControl.h"
#include "CommandIDs.h"
#include "Icons.h"

static CommandPanel::Items createDefaultPanel()
{
    CommandPanel::Items cmds;

    cmds.add(CommandItem::withParams(Icons::copy, CommandIDs::CopyEvents,
        TRANS("menu::selection::stage::reset")));

    cmds.add(CommandItem::withParams(Icons::cut, CommandIDs::CutEvents,
        TRANS("menu::selection::stage::commit")));

    // TODO
    //cmds.add(CommandItem::withParams(Icons::trash, CommandIDs::DeleteEvents,
    //    TRANS("menu::selection::stage::stash")));

    cmds.add(CommandItem::withParams(Icons::trash, CommandIDs::DeleteEvents,
        TRANS("menu::selection::stage::selectall")));

    return cmds;
}

VCSStageSelectionMenu::VCSStageSelectionMenu(const SparseSet<int> &selectedChanges, VersionControl &vcs) :
    selectedChanges(selectedChanges),
    vcs(vcs)
{
    this->updateContent(createDefaultPanel(), CommandPanel::SlideRight);
}

void VCSStageSelectionMenu::handleCommandMessage(int commandId)
{
    if (commandId == CommandIDs::Back)
    {
        this->updateContent(createDefaultPanel(), CommandPanel::SlideRight);
        return;
    }
    else if (commandId == CommandIDs::CopyEvents)
    {
        this->dismiss();
        return;
    }
}

void VCSStageSelectionMenu::dismiss() const
{
    if (Component *parent = this->getParentComponent())
    {
        parent->exitModalState(0);
    }
}

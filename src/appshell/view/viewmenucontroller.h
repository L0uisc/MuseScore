//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2021 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================
#ifndef MU_APPSHELL_VIEWMENUCONTROLLER_H
#define MU_APPSHELL_VIEWMENUCONTROLLER_H

#include "modularity/ioc.h"
#include "async/asyncable.h"
#include "iapplicationactioncontroller.h"
#include "notation/inotationactionscontroller.h"
#include "palette/ipaletteactionscontroller.h"
#include "actions/actiontypes.h"
#include "appshelltypes.h"
#include "globaltypes.h"
#include "notation/notationtypes.h"

#include "iviewmenucontroller.h"

namespace mu::appshell {
class ViewMenuController : public IViewMenuController, public async::Asyncable
{
    INJECT(appshell, notation::INotationActionsController, notationController)
    INJECT(appshell, palette::IPaletteActionsController, paletteController)
    INJECT(appshell, IApplicationActionController, applicationController)

public:
    void init();

    bool contains(const actions::ActionCode& actionCode) const override;

    bool actionAvailable(const actions::ActionCode& actionCode) const override;
    async::Channel<actions::ActionCodeList> actionsAvailableChanged() const override;

private:
    using AvailableCallback = std::function<bool ()>;
    std::map<actions::ActionCode, AvailableCallback> actions() const;

    bool isPanelAvailable(PanelType panelType) const;
    bool isMasterPaletteAvailable() const;
    bool isZoomInAvailable() const;
    bool isZoomOutAvailable() const;
    bool isSplitAvailable(framework::Orientation orientation) const;
    bool isScoreConfigAvailable(notation::ScoreConfigType configType) const;
    bool isFullScreenAvailable() const;

    std::string scoreConfigActionCode(notation::ScoreConfigType configType) const;

    async::Channel<actions::ActionCodeList> m_actionsReceiveAvailableChanged;
};
}

#endif // MU_NOTATION_VIEWMENUCONTROLLER_H

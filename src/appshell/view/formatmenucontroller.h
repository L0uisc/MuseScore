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
#ifndef MU_APPSHELL_FORMATMENUCONTROLLER_H
#define MU_APPSHELL_FORMATMENUCONTROLLER_H

#include "modularity/ioc.h"
#include "async/asyncable.h"
#include "notation/inotationactionscontroller.h"
#include "notation/notationtypes.h"

#include "iformatmenucontroller.h"

namespace mu::appshell {
class FormatMenuController : public IFormatMenuController, public async::Asyncable
{
    INJECT(appshell, notation::INotationActionsController, controller)

public:
    void init();

    bool contains(const actions::ActionCode& actionCode) const override;

    bool actionAvailable(const actions::ActionCode& actionCode) const override;
    async::Channel<actions::ActionCodeList> actionsAvailableChanged() const override;

private:
    using AvailableCallback = std::function<bool ()>;
    std::map<actions::ActionCode, AvailableCallback> actions() const;

    bool isEditStyleAvailable() const;
    bool isPageSettingsAvailable() const;
    bool isStretchIncreaseAvailable() const;
    bool isStretchDecreaseAvailable() const;
    bool isResetAvailable(notation::ResettableValueType resettableValueType) const;
    bool isLoadStyleAvailable() const;
    bool isSaveStyleAvailable() const;

    std::string resetableValueTypeActionCode(notation::ResettableValueType valueType) const;

    async::Channel<actions::ActionCodeList> m_actionsReceiveAvailableChanged;
};
}

#endif // MU_APPSHELL_FORMATMENUCONTROLLER_H

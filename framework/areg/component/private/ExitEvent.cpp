/************************************************************************
 * This file is part of the AREG SDK core engine.
 * AREG SDK is dual-licensed under Free open source (Apache version 2.0
 * License) and Commercial (with various pricing models) licenses, depending
 * on the nature of the project (commercial, research, academic or free).
 * You should have received a copy of the AREG SDK license description in LICENSE.txt.
 * If not, please contact to info[at]aregtech.com
 *
 * \copyright   (c) 2017-2021 Aregtech UG. All rights reserved.
 * \file        areg/component/private/ExitEvent.hpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit 
 * \author      Artak Avetyan
 * \brief       AREG Platform, Exit Event declaration.
 *              All dispatchers receiving this event should be stopped
 *              and start preparing exit procedure
 *
 ************************************************************************/
#include "areg/component/private/ExitEvent.hpp"

IMPLEMENT_RUNTIME_EVENT(ExitEvent, Event)

ExitEvent::ExitEvent( void )
    : Event   ( Event::eEventType::EventExternal )
{
}

ExitEvent::~ExitEvent( void )
{
}

ExitEvent & ExitEvent::getExitEvent( void )
{
    static ExitEvent  _exitEvent;
    return _exitEvent;
}

void ExitEvent::destroy( void )
{
}

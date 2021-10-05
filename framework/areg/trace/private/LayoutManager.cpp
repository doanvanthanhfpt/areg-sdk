/************************************************************************
 * This file is part of the AREG SDK core engine.
 * AREG SDK is dual-licensed under Free open source (Apache version 2.0
 * License) and Commercial (with various pricing models) licenses, depending
 * on the nature of the project (commercial, research, academic or free).
 * You should have received a copy of the AREG SDK license description in LICENSE.txt.
 * If not, please contact to info[at]aregtech.com
 *
 * \copyright   (c) 2017-2021 Aregtech UG. All rights reserved.
 * \file        areg/trace/private/LayoutManager.cpp
 * \ingroup     AREG Asynchronous Event-Driven Communication Framework
 * \author      Artak Avetyan
 * \brief       The Layout Manager to output text messages.
 ************************************************************************/
#include "areg/trace/private/LayoutManager.hpp"

#include "areg/trace/private/Layouts.hpp"
#include "areg/trace/private/NELogConfig.hpp"
#include "areg/base/NEUtilities.hpp"

LayoutManager::LayoutManager(void)
    : mLayoutList   ( )
{
}

LayoutManager::~LayoutManager(void)
{
    deleteLayouts();
}

bool LayoutManager::createLayouts( const char * layoutFormat )
{
    deleteLayouts();
    int len = NEString::isEmpty<char>(layoutFormat) == false ? NEString::getStringLength<char>( layoutFormat ) + 1 : 0;
    char * strFormat = len != 0 ? DEBUG_NEW char[ static_cast<unsigned int>(len) ] : nullptr;

    if ( strFormat != nullptr )
    {
        NEString::copyString( strFormat, len, layoutFormat );
        char * pos          = strFormat;
        const char * pos1   = pos;
        bool hasExclusive   = false;

        while ( *pos != '\0' )
        {
            if ( *pos == '%' )
            {
                char ch = *(pos + 1);
                IELayout * newLayout = nullptr;
                switch ( static_cast<NELogConfig::eLayouts>(ch) )
                {
                case NELogConfig::eLayouts::LayoutTickCount:
                    newLayout   = DEBUG_NEW TickCountLayout();
                    break;

                case NELogConfig::eLayouts::LayoutDayTime:
                    newLayout   = DEBUG_NEW DayTimeLaytout();
                    break;

                case NELogConfig::eLayouts::LayoutExecutableId:
                    newLayout   = DEBUG_NEW ModuleIdLayout();
                    break;

                case NELogConfig::eLayouts::LayoutMessage:
                    if ( hasExclusive == false )
                    {
                        newLayout   = DEBUG_NEW MessageLayout();
                        hasExclusive= true;
                    }
                    break;

                case NELogConfig::eLayouts::LayoutEndOfLine:
                    newLayout   = DEBUG_NEW EndOfLineLayout();
                    break;

                case NELogConfig::eLayouts::LayoutPriority:
                    newLayout   = DEBUG_NEW PriorityLayout();
                    break;

                case NELogConfig::eLayouts::LaytoutScopeId:
                    newLayout   = DEBUG_NEW ScopeIdLayout();
                    break;

                case NELogConfig::eLayouts::LayoutThreadId:
                    newLayout   = DEBUG_NEW ThreadIdLayout();
                    break;

                case NELogConfig::eLayouts::LayoutExecutableName:
                    newLayout   = DEBUG_NEW ModuleNameLayout();
                    break;

                case NELogConfig::eLayouts::LayoutThreadName:
                    newLayout   = DEBUG_NEW ThreadNameLayout();
                    break;

                case NELogConfig::eLayouts::LaytoutScopeName:
                    if ( hasExclusive == false )
                    {
                        newLayout   = DEBUG_NEW ScopeNameLayout();
                        hasExclusive= true;
                    }
                    break;

                case NELogConfig::eLayouts::LayoutUndefined:  // fall through
                case NELogConfig::eLayouts::LayoutAnyText:    // fall through
                default:
                    if ( ch == '%' )
                    {
                        *(pos + 1) = '\0';
                        newLayout   = DEBUG_NEW AnyTextLayout(pos1);
                        pos1 = pos; // <== will automatically move 2 positions when newLayout is not nullptr;
                    }
                    else
                    {
                        pos += ch != '\0' ? 2 : 1;
                    }
                    break;
                }

                if ( newLayout != nullptr )
                {
                    *pos = '\0';
                    if ( pos1 != static_cast<const char *>(pos) )
                        mLayoutList.pushLast( static_cast<IELayout *>(DEBUG_NEW AnyTextLayout(pos1)) );

                    mLayoutList.pushLast( newLayout );

                    *(++ pos) = '\0';
                    pos1 = ++ pos;                        
                }
            }
            else
            {
                ++ pos;
            }
        }

        if ( pos1 != static_cast<const char *>(pos) )
        {
            mLayoutList.pushLast( static_cast<IELayout *>(DEBUG_NEW AnyTextLayout( pos1 )) );
        }

        delete [] strFormat;
    }

    return (mLayoutList.isEmpty() == false);
}

void LayoutManager::deleteLayouts(void)
{
    for ( STACKPOS pos = mLayoutList.firstPosition(); pos != nullptr; pos = mLayoutList.nextPosition(pos))
        delete static_cast<IELayout *>(mLayoutList.getAt(pos));

    mLayoutList.removeAll();
}

bool LayoutManager::logMessage(const NETrace::sLogMessage & logMsg, IEOutStream & stream) const
{
    bool result = false;
    if (isValid())
    {
        if ( logMsg.lmTrace.traceMessagePrio == NETrace::PrioIgnoreLayout )
        {
            stream.write( logMsg.lmTrace.traceMessage );
        }
        else
        {
            for ( LISTPOS pos = mLayoutList.firstPosition(); pos != nullptr; pos = mLayoutList.nextPosition(pos) )
                mLayoutList.getAt(pos)->logMessage(logMsg, stream);
        }

        result = true;
    }

    return result;
}

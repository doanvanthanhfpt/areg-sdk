/************************************************************************
 * \file        areg/base/private/posix/MutexIX.cpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       AREG Platform, POSIX Mutex wrapper class.
 *
 ************************************************************************/

 /************************************************************************
  * Includes
  ************************************************************************/

#include "areg/base/private/posix/MutexIX.hpp"

#ifdef  _POSIX

//////////////////////////////////////////////////////////////////////////
// MutexIX class implementation
//////////////////////////////////////////////////////////////////////////

MutexIX::MutexIX( bool initLocked /*= false*/, const char * asciiName /* = NULL */)
    : IESynchObjectBaseIX   ( NESynchTypesIX::SoMutex, asciiName)

    , mPosixMutex           ( )
    , mMutexValid           ( false )
    , mPosixMutexAttr       ( )
    , mMutexAttrValid       ( false )
{
    _initPosixMutex( true );
    if (initLocked)
    {
        pthread_mutex_lock( &mPosixMutex );
    }
}

MutexIX::MutexIX( NESynchTypesIX::eSynchObject synchType, bool isRecursive, const char * asciiName /* = NULL */ )
    : IESynchObjectBaseIX   ( synchType, asciiName )

    , mPosixMutex           ( )
    , mMutexValid           ( false )
    , mPosixMutexAttr       ( )
    , mMutexAttrValid       ( false )
{
    _initPosixMutex( isRecursive );
}

MutexIX::~MutexIX( void )
{
    if (mMutexValid)
        pthread_mutex_destroy(&mPosixMutex);
    if (mMutexAttrValid)
        pthread_mutexattr_destroy(&mPosixMutexAttr);

    mMutexValid     = false;
    mMutexAttrValid = false;
}

inline void MutexIX::_initPosixMutex( bool isRecursive )
{
    if ( RETURNED_OK == pthread_mutexattr_init( &mPosixMutexAttr ) )
    {
        mMutexValid = true;
        if ( RETURNED_OK == pthread_mutexattr_settype( &mPosixMutexAttr, isRecursive ? PTHREAD_MUTEX_RECURSIVE : PTHREAD_MUTEX_DEFAULT ) )
        {
            if ( RETURNED_OK == pthread_mutex_init( &mPosixMutex, &mPosixMutexAttr ) )
            {
                mMutexAttrValid = true;
            }
            else
            {
                pthread_mutexattr_destroy( &mPosixMutexAttr );
                mMutexAttrValid = false;
                mMutexValid     = false;

            }
        }
        else
        {
            pthread_mutexattr_destroy( &mPosixMutexAttr );
            mMutexAttrValid = false;
        }
    }
}

bool MutexIX::lock( unsigned int msTimeout /*= IESynchObject::WAIT_INFINITE*/ ) const
{
    bool result = false;
    if ( mMutexValid )
    {
        if ( IESynchObject::WAIT_INFINITE == msTimeout )
        {
            result = RETURNED_OK == pthread_mutex_lock( &mPosixMutex );
        }
        else
        {
            timespec now;
            NESynchTypesIX::timeoutFromNow(now, msTimeout);
            result = RETURNED_OK == pthread_mutex_timedlock( &mPosixMutex, &now );
        }
    }

    return result;
}

bool MutexIX::tryLock( void ) const
{
    return (RETURNED_OK == pthread_mutex_trylock( &mPosixMutex ) );
}

void MutexIX::unlock( void ) const
{
    pthread_mutex_unlock( &mPosixMutex );
}

bool MutexIX::isValid( void ) const
{
    return (mMutexValid && mMutexAttrValid);
}

void MutexIX::freeResources(void)
{
    pthread_mutex_unlock( &mPosixMutex );
}

#endif // _POSIX

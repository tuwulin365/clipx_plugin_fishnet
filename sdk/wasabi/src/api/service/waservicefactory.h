// ----------------------------------------------------------------------------
// Generated by InterfaceFactory [Wed May 07 00:57:16 2003]
// 
// File        : waservicefactory.h
// Class       : waServiceFactory
// class layer : Dispatchable Interface
// ----------------------------------------------------------------------------

#ifndef __WASERVICEFACTORY_H
#define __WASERVICEFACTORY_H

#include <bfc/dispatch.h>
#include <bfc/common.h>
#include <bfc/nsguid.h>
#include <api/api.h>

// ----------------------------------------------------------------------------

class COMEXP NOVTABLE waServiceFactory: public Dispatchable {
  protected:
    waServiceFactory() {}
    ~waServiceFactory() {}
  protected:
  
 public:

    FOURCC getServiceType();
    const char *getServiceName();
    GUID getGuid();
    void *getInterface(int global_lock = TRUE);
    int supportNonLockingGetInterface();
    int releaseInterface(void *ifc);
    const char *getTestString();
    int serviceNotify(int msg, int param1 = 0, int param2 = 0);
  
  protected:
    enum {
      WASERVICEFACTORY_GETSERVICETYPE = 100,
      WASERVICEFACTORY_GETSERVICENAME = 200,
      WASERVICEFACTORY_GETGUID = 210,
      WASERVICEFACTORY_GETINTERFACE = 300,
      WASERVICEFACTORY_SUPPORTNONLOCKINGGETINTERFACE = 301,
      WASERVICEFACTORY_RELEASEINTERFACE = 310,
      WASERVICEFACTORY_GETTESTSTRING = 500,
      WASERVICEFACTORY_SERVICENOTIFY = 600,
    };
};

// ----------------------------------------------------------------------------

inline FOURCC waServiceFactory::getServiceType() {
  FOURCC __retval = _call(WASERVICEFACTORY_GETSERVICETYPE, (FOURCC)NULL);
  return __retval;
}

inline const char *waServiceFactory::getServiceName() {
  const char *__retval = _call(WASERVICEFACTORY_GETSERVICENAME, (const char *)0);
  return __retval;
}

inline GUID waServiceFactory::getGuid() {
  GUID __retval = _call(WASERVICEFACTORY_GETGUID, INVALID_GUID);
  return __retval;
}

inline void *waServiceFactory::getInterface(int global_lock) {
  void *__retval = _call(WASERVICEFACTORY_GETINTERFACE, (void *)NULL, global_lock);
  
  // -- generated code - edit in waservicefactoryi.h
  // support old code that always locks even when global_lock==FALSE
  if (!global_lock && __retval != NULL && !supportNonLockingGetInterface())
    WASABI_API_SVC->service_unlock(__retval);

  return __retval;
}

inline int waServiceFactory::supportNonLockingGetInterface() {
  int __retval = _call(WASERVICEFACTORY_SUPPORTNONLOCKINGGETINTERFACE, (int)0);
  return __retval;
}

inline int waServiceFactory::releaseInterface(void *ifc) {
  int __retval = _call(WASERVICEFACTORY_RELEASEINTERFACE, (int)0, ifc);
  return __retval;
}

inline const char *waServiceFactory::getTestString() {
  const char *__retval = _call(WASERVICEFACTORY_GETTESTSTRING, (const char *)0);
  return __retval;
}

inline int waServiceFactory::serviceNotify(int msg, int param1, int param2) {
  int __retval = _call(WASERVICEFACTORY_SERVICENOTIFY, (int)0, msg, param1, param2);
  return __retval;
}

// ----------------------------------------------------------------------------

#endif // __WASERVICEFACTORY_H

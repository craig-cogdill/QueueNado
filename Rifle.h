#pragma once
#include "czmq.h"
#include "CZMQToolkit.h"

#define SIZE_OF_STAKE_BUNDLE 100

class Rifle {
public:
   Rifle(const std::string& location);
   bool Aim();
   std::string GetBinding() const;
   bool Fire(const std::string& bullet, const int waitToFire = 10000);
   bool FireStake(const void* stake,const int waitToFire = 10000);
   bool FireStakes(const std::vector<std::pair<void*, unsigned int> >& stakes,
           const int waitToFire = 10000);

   bool FireZeroCopy( std::string* zero, const size_t size, void (*FreeFunction)(void*,void*), const int waitToFire = 10000);
   int GetHighWater();
   void SetHighWater(const int hwm);
   int GetIOThreads();
   void SetIOThreads(const int count);
   void SetOwnSocket(const bool own);
   bool GetOwnSocket();
   virtual ~Rifle();
protected:
   void Destroy();
private:
   std::string mLocation;
   int mHwm;
   void* mChamber;
   zctx_t* mContext;
   int mLinger;
   int mIOThredCount;
   bool mOwnSocket;
};

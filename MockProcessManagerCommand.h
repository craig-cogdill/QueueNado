#pragma once
#include "ProcessManager.h"
#include "Conf.h"
#include <g2log.hpp>
#include <string>
#include <vector>
#include "include/global.h"

class MockProcessManagerCommand : public ProcessManager {
public:

   MockProcessManagerCommand(const Conf& conf) 
   : ProcessManager(conf, global::GetProgramName()),
   mReturnCode(0),
   mInit(true),
   mSuccess(true),
   mCountNumberOfRuns(0),
   mResult{"Success"} {
   }

   bool Initialize() {
      return mInit;
   }

   const std::string& getRunCommand() {
      return mRunCommand;
   }

   const std::string& getRunArgs() {
      return mRunArgs;
   }
   
   const std::vector<std::string>& getTotalRunCommands() {
      return mTotalRunCommands;
   }

   const std::vector<std::string>& getTotalRunArgs() {
      return mTotalRunArgs;
   }
   

   virtual void setInit(bool init) {
      mInit = init;
   }

   virtual void SetReturnCode(const int returnCode) {
      mReturnCode = returnCode;

   }

   virtual void SetSuccess(const bool success) {
      mSuccess = success;

   }

   virtual void SetResult(const std::string result) {
      mResult = result;
   }

   protoMsg::ProcessReply RunProcess(const std::string& execPath, const std::string& args) {
      ++mCountNumberOfRuns;
      LOG(INFO) << "Executing: " << execPath << " " << args;
             
      mRunCommand.clear();
      mRunCommand = execPath;
      mRunArgs.clear();
      mRunArgs = args;
      mTotalRunCommands.push_back(mRunCommand);
      mTotalRunArgs.push_back(mRunArgs);
      
      protoMsg::ProcessReply reply;
      reply.set_success(mSuccess);
      reply.set_returncode(mReturnCode);
      reply.set_result(mResult);
      return reply;
   }

   virtual ~MockProcessManagerCommand() {
   }


   int mReturnCode;
   bool mInit;
   bool mSuccess;
   size_t mCountNumberOfRuns;
   std::string mResult;
   std::string mRunCommand;
   std::string mRunArgs;
   std::vector<std::string>  mTotalRunCommands;
   std::vector<std::string>  mTotalRunArgs;
   
   private:
};

#pragma once
#include<string>
#include "NonCopyable.h"
#include<cstdint>
#include "json/json.h"
#include<memory>
#include<mutex>
#include "Singleton.h"
#include "Logger.h"
#include "FileLog.h"

namespace fmps
{
    namespace base
    {
        struct LogInfo
        {
            LogLevel level;
            std::string path;
            std::string name;
            RotateType rotate_type{kRotateNone};
        };
        using LogInfoPtr = std::shared_ptr<LogInfo>;

        class Config
        {
        public:
            Config() = default;
            ~Config() = default;

            bool LoadConfig(const std::string &file);
            LogInfoPtr& GetLogInfo();

            std::string name_;
            int32_t cpu_start_{0};
            int32_t thread_nums_{1};
        private:
            bool ParseLogInfo(const Json::Value &root);
            LogInfoPtr log_info_;
        };
        
        using ConfigPtr =std::shared_ptr<Config>;
    
        class ConfigMgr : public NonCopyable
        {
        public:
            ConfigMgr() = default;
            ~ConfigMgr() = default;

            bool LoadConfig(const std::string& file);
            ConfigPtr GetConfig();
        private:
            ConfigPtr config_;
            std::mutex lock_;
        };
    }
    #define sConfigMgr fmps::base::Singleton<fmps::base::ConfigMgr>::Instance()
}
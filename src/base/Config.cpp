#include "Config.h"
#include "LogStream.h"

using namespace fmps::base;

bool Config::LoadConfig(const std::string &file)
{
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(file,root))
    {
        LOG_DEBUG << "config file:" << file << " parse error."; 
        return false;
    }

    Json::Value nameObj = root["name"];
    if (!nameObj.isNull())
    {
        name_ = nameObj.asString();
    }

    Json::Value cpusObj = root["cpu_start"];
    if (!cpusObj.isNull())
    {
        cpu_start_ = cpusObj.asInt();
    }

    Json::Value threadsObj = root["threads"];
    if (!threadsObj.isNull())
    {
        thread_nums_ = threadsObj.asInt();
    }

    Json::Value logObj = root["log"];
    if (!logObj.isNull())
    {
        ParseLogInfo(logObj);
    }
    return true;
}
bool Config::ParseLogInfo(const Json::Value &root)
{
    log_info_ = std::make_shared<LogInfo>();
    Json::Value levelObj = root["level"];
    if (!levelObj.isNull())
    {
        log_info_->level = levelObj.asString();
    }
    Json::Value pathObj = root["path"];
    if (!pathObj.isNull())
    {
        log_info_->path = pathObj.asString();
    }
    Json::Value nameOnj = root["name"];
    if (!nameOnj.isNull())
    {
        log_info_->name = nameOnj.asString();
    }
    return true;
}
LogInfoPtr &Config::GetLogInfo()
{
    return log_info_;
}

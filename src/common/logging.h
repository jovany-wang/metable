#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"

namespace metable {
enum class MetableLogLevel {
    RLL_DEBUG,
    RLL_INFO,
    RLL_WARNING,
    RLL_ERROR,
    RLL_FATAL,
    RLL_NOLEVEL
};
class MetableLogBase {
public:
    virtual ~MetableLogBase(){};

    virtual bool IsEnabled() const { return false; };

    template <typename T>
    MetableLogBase &operator<<(const T &t) {
        if (IsEnabled()) {
            ss_ << t;
        }
        return *this;
    }

    //    MetableLogBase &operator<<(NodeID &id) {
    //        if (IsEnabled()) {
    //            id << ss_;
    //        }
    //        return *this;
    //    }

protected:
    std::stringstream ss_;
};

class MetableLog : public MetableLogBase {
public:
    MetableLog(const char *file_name, int line_number, MetableLogLevel severity);

    ~MetableLog();

    static void StartMetableLog(const std::string &log_file_name,
                                MetableLogLevel severity, uint32_t log_file_roll_size_mb,
                                uint32_t log_file_roll_cout);

    bool IsEnabled() const;

    static bool IsLevelEnabled(MetableLogLevel log_level);

    static void ShutDownMetableLog();

private:
    bool is_enabled_;
    MetableLogLevel log_level_;
    std::string filename_;
    int line_number_;
    static std::shared_ptr<spdlog::logger> logging_provider;
    static MetableLogLevel severity_threshold_;

protected:
};

class Voidify {
public:
    Voidify() { std::abort(); }

    void operator&(MetableLogBase &) {}
};

#ifdef _WIN32
#define spdlogfilename(x) strrchr(x, '\\') ? strrchr(x, '\\') + 1 : x
#else
#define spdlogfilename(x) strrchr(x, '/') ? strrchr(x, '/') + 1 : x
#endif

#define METABLE_LOG_INTERNAL(level) \
    ::metable::MetableLog(spdlogfilename(__FILE__), __LINE__, level)
#define METABLE_LOG(level)                                                    \
    if (metable::MetableLog::IsLevelEnabled(metable::MetableLogLevel::level)) \
    METABLE_LOG_INTERNAL(metable::MetableLogLevel::level)

#define METABLE_LOG_ENABLED(level) \
    metable::MetableLog::IsLevelEnabled(metable::MetableLogLevel::level)
#define METABLE_IGNORE_EXPR(expr) ((void)(expr))
#define METABLE_CHECK(condition)                                                 \
    (condition) ? METABLE_IGNORE_EXPR(0)                                         \
                : ::metable::Voidify() &                                         \
                      ::metable::MetableLog(__FILE__, __LINE__,                  \
                                            metable::MetableLogLevel::RLL_FATAL) \
                          << " Check failed: " #condition " "
}  // namespace metable

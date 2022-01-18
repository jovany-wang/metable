#include "logging.h"

namespace metable {
static spdlog::level::level_enum GetMappedSeverity(MetableLogLevel severity) {
    switch (severity) {
    case MetableLogLevel::RLL_DEBUG:
        return spdlog::level::debug;
    case MetableLogLevel::RLL_INFO:
        return spdlog::level::info;
    case MetableLogLevel::RLL_WARNING:
        return spdlog::level::warn;
    case MetableLogLevel::RLL_ERROR:
        return spdlog::level::err;
    case MetableLogLevel::RLL_FATAL:
        return spdlog::level::critical;
    default:
        return spdlog::level::critical;
    }
}

MetableLog::MetableLog(const char *file_name, int line_number, MetableLogLevel severity)
    : filename_(file_name),
      line_number_(line_number),
      log_level_(std::move(severity)),
      is_enabled_(severity >= severity_threshold_) {}

MetableLog::~MetableLog() {
    try {
        if (is_enabled_) {
            logging_provider->log(GetMappedSeverity(log_level_), "in {} line:{} {}",
                                  filename_, line_number_, ss_.str());
        }
    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "logging_provider->log failed: " << ex.what() << std::endl;
    }
}

void MetableLog::StartMetableLog(const std::string &log_file_name,
                                 MetableLogLevel severity, uint32_t log_file_roll_size_mb,
                                 uint32_t log_file_roll_cout) {
    severity_threshold_ = severity;
    if (logging_provider == nullptr) {
        try {
            logging_provider = ::spdlog::rotating_logger_mt(
                "Metable_log", log_file_name, 1024 * 1024 * 1024 * log_file_roll_size_mb,
                log_file_roll_cout);
            spdlog::set_level(GetMappedSeverity(severity));
            logging_provider->flush_on(spdlog::level::debug);
        } catch (const spdlog::spdlog_ex &ex) {
            std::cout << "MetableLog failed: " << ex.what() << std::endl;
        }
    }
}

bool MetableLog::IsEnabled() const { return is_enabled_; }

bool MetableLog::IsLevelEnabled(MetableLogLevel log_level) {
    return log_level >= severity_threshold_;
}

void MetableLog::ShutDownMetableLog() { spdlog::shutdown(); }

std::shared_ptr<spdlog::logger> MetableLog::logging_provider = nullptr;
MetableLogLevel MetableLog::severity_threshold_ = MetableLogLevel::RLL_NOLEVEL;

}  // namespace metable

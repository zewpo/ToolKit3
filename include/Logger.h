#ifndef LOGGER_H
#define LOGGER_H

// Logger.h
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>

#include <wx/textctrl.h>

namespace Logger {

    static const std::string kLogLevelDebug = "DEBUG";
    static const std::string kLogLevelInfo = "INFO";
    static const std::string kLogLevelError = "ERROR";

    void log(const std::string& msg, const std::string& log_level = kLogLevelInfo );
    std::string get_now_string();
    void setTxtCtrlLog(wxTextCtrl* txtCtrlLog );

}

// Definition of a multithread safe singleton logger class
class Logger_t
{
    public:

        // Returns a reference to the singleton Logger object
        static Logger_t& instance();

        // Logs a single message at the given log level
        void log(const std::string& inMessage, const std::string& inLogLevel);

        // Logs a vector of messages at the given log level
        void log(const std::vector<std::string>& inMessages, const std::string& inLogLevel);

        void setTxtCtrlLog_inner(wxTextCtrl* txtCtrlLog );

    protected:
        // Static variable for the one-and-only instance
        static Logger_t* pInstance;

        // Constant for the filename
        static const char* const kLogFileName;

        // Data member for the output stream
        std::ofstream mOutputStream;

        //std::ostream logStream;

        wxTextCtrl* tkLog;

        // Embedded class to make sure the single Logger
        // instance gets deleted on program shutdown.
        friend class Cleanup;
        class Cleanup
        {
        public:
            ~Cleanup();
        };

        // Logs message. The thread should own a lock on sMutex
        // before calling this function.
        void logHelper(const std::string& inMessage, const std::string& inLogLevel);


    private:
        Logger_t();
        virtual ~Logger_t();
        Logger_t(const Logger_t&);
        Logger_t& operator=(const Logger_t&);
        static std::mutex sMutex;
};

#endif // LOGGER_H

// Implementation of a multithread safe singleton logger class
#include "Logger.h"

using namespace std;

namespace Logger
{
    void log(const std::string& msg, const std::string& log_level){
        Logger_t::instance().log(msg, log_level);
    }

    void setTxtCtrlLog(wxTextCtrl* txtCtrlLog ){
        Logger_t::instance().setTxtCtrlLog_inner(txtCtrlLog);
    }

    std::string get_now_string()
    {

        const auto currentTime = std::chrono::system_clock::now( );

        time_t time = std::chrono::system_clock::to_time_t( currentTime );
        auto currentTimeRounded = std::chrono::system_clock::from_time_t( time );
        if( currentTimeRounded > currentTime ) {
            -- time;
            currentTimeRounded -= std::chrono::seconds( 1 );
        }
        const tm *values = localtime( &time );
        std::string  year = std::to_string( values->tm_year + 1900 );
        std::string  month = std::to_string( values->tm_mon +1 );
        std::string  day = std::to_string( values->tm_mday );
        std::string  hours = std::to_string( values->tm_hour );
        std::string  minutes = std::to_string( values->tm_min );
        std::string  seconds = std::to_string( values->tm_sec );
        std::string  milliseconds = std::to_string( std::chrono::duration_cast<std::chrono::duration<int,std::milli> >( currentTime - currentTimeRounded ).count( ) );

        std::ostringstream oss;
        oss << setw(4)<<setfill('0')<<year
                  <<":"<<setw(2)<<setfill('0')<<month
                  <<":"<<setw(2)<<setfill('0')<<day
                  <<"-"<<setw(2)<<setfill('0')<<hours
                  <<":"<<setw(2)<<setfill('0')<<minutes
                  <<":"<<setw(2)<<setfill('0')<<seconds
                  <<"."<<setw(3)<<setfill('0')<<milliseconds ;

        return oss.str();
    }

}

const char* const Logger_t::kLogFileName = "output.log";

Logger_t* Logger_t::pInstance = nullptr;

mutex Logger_t::sMutex;

Logger_t& Logger_t::instance()
{
	static Cleanup cleanup;

	lock_guard<mutex> guard(sMutex);
	if (pInstance == nullptr)
		pInstance = new Logger_t();
	return *pInstance;
}

Logger_t::Cleanup::~Cleanup()
{
	lock_guard<mutex> guard(Logger_t::sMutex);
	delete Logger_t::pInstance;
	Logger_t::pInstance = nullptr;
}

Logger_t::~Logger_t()
{
	mOutputStream.close();
}

Logger_t::Logger_t()
{
	mOutputStream.open(kLogFileName, ios_base::app);
	if (!mOutputStream.good()) {
		throw runtime_error("Unable to initialize the Logger!");
	}
}

void Logger_t::log(const string& inMessage, const string& inLogLevel)
{
	lock_guard<mutex> guard(sMutex);
	logHelper(inMessage, inLogLevel);
}

void Logger_t::log(const vector<string>& inMessages, const string& inLogLevel)
{
	lock_guard<mutex> guard(sMutex);
	for (size_t i = 0; i < inMessages.size(); i++) {
		logHelper(inMessages[i], inLogLevel);
	}
}

void Logger_t::logHelper(const std::string& inMessage, const std::string& inLogLevel)
{
    std::string msg;
    msg.append( Logger::get_now_string() );
    msg.append(  " - " ).append( inLogLevel );
    msg.append(  ":  " ).append( inMessage );

    mOutputStream << msg << endl;
    tkLog->WriteText(msg+"\n");

  //  *tkLog << msg << endl;

    //logStream.flush();

}

void Logger_t::setTxtCtrlLog_inner(wxTextCtrl* txtCtrlLog ){
    this->tkLog = txtCtrlLog;
    // logStream.basic_ostream() = new ostream(tkLog);
}


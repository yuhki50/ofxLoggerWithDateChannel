#pragma once

#include "ofLog.h"
#include "ofUtils.h"

/// \brief Set the logging to ouptut with date to the console.
///
/// This is the default state and can be called to reset console logging
/// after ofLogToFile or ofSetLoggerChannel has been called.
void ofLogWithDateToConsole();

/// \brief Set the logging to output with date to a file instead of the console.
/// \param path The path to the log file to use.
/// \param append True if you want to append to the existing file.
void ofLogWithDateToFile(const string& path, bool append = false);

/// \brief A logger channel that logs its messages with date to the console.
class ofxConsoleLoggerWithDateChannel : public ofBaseLoggerChannel {
   public:
    /// \brief Destroy the console logger channel.
    virtual ~ofxConsoleLoggerWithDateChannel(){};
    void log(ofLogLevel level, const string& module, const string& message);
    void log(ofLogLevel level, const string& module, const char* format, ...) OF_PRINTF_ATTR(4, 5);
    void log(ofLogLevel level, const string& module, const char* format, va_list args);
};

/// \brief A logger channel that logs its messages with date to a log file.
class ofxFileLoggerWithDateChannel : public ofBaseLoggerChannel {
   public:
    /// \brief Create an ofxFileLoggerWithDateChannel.
    ofxFileLoggerWithDateChannel();

    /// \brief Create an ofxFileLoggerWithDateChannel with parameters.
    /// \param path The file path for the log file.
    /// \param append True if the log data should be added to an existing file.
    ofxFileLoggerWithDateChannel(const string& path, bool append);

    /// \brief Destroy the file logger channel.
    virtual ~ofxFileLoggerWithDateChannel();

    /// \brief Set the log file.
    /// \param path The file path for the log file.
    /// \param append True if the log data should be added to an existing file.
    void setFile(const string& path, bool append = false);

    void log(ofLogLevel level, const string& module, const string& message);
    void log(ofLogLevel level, const string& module, const char* format, ...) OF_PRINTF_ATTR(4, 5);
    void log(ofLogLevel level, const string& module, const char* format, va_list args);

    /// \brief CLose the log file.
    void close();

   private:
    ofFile file;  ///< The location of the log file.
};

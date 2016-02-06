#include "ofxLoggerWithDateChannel.h"

void ofLogWithDateToConsole() { ofLog::setChannel(shared_ptr<ofxConsoleLoggerWithDateChannel>(new ofxConsoleLoggerWithDateChannel)); }

void ofLogWithDateToFile(const string& path, bool append) { ofLog::setChannel(shared_ptr<ofxFileLoggerWithDateChannel>(new ofxFileLoggerWithDateChannel(path, append))); }

void ofxConsoleLoggerWithDateChannel::log(ofLogLevel level, const string& module, const string& message) {
    // print to cerr for OF_LOG_ERROR and OF_LOG_FATAL_ERROR, everything else to cout
    ostream& out = level < OF_LOG_ERROR ? cout : cerr;
    out << ofGetTimestampString() << " ";
    out << "[" << ofGetLogLevelName(level, true) << "] ";
    // only print the module name if it's not ""
    if (module != "") {
        out << module << ": ";
    }
    out << message << endl;
}

void ofxConsoleLoggerWithDateChannel::log(ofLogLevel level, const string& module, const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(level, module, format, args);
    va_end(args);
}

void ofxConsoleLoggerWithDateChannel::log(ofLogLevel level, const string& module, const char* format, va_list args) {
    // thanks stefan!
    // http://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html
    FILE* out = level < OF_LOG_ERROR ? stdout : stderr;
    fprintf(out, "[%s] ", ofGetLogLevelName(level, true).c_str());
    if (module != "") {
        fprintf(out, "%s: ", module.c_str());
    }
    vfprintf(out, format, args);
    fprintf(out, "\n");
}

ofxFileLoggerWithDateChannel::ofxFileLoggerWithDateChannel() {}

ofxFileLoggerWithDateChannel::ofxFileLoggerWithDateChannel(const string& path, bool append) { setFile(path, append); }

ofxFileLoggerWithDateChannel::~ofxFileLoggerWithDateChannel() { close(); }

void ofxFileLoggerWithDateChannel::close() { file.close(); }

void ofxFileLoggerWithDateChannel::setFile(const string& path, bool append) {
    file.open(path, append ? ofFile::Append : ofFile::WriteOnly);
    file << endl;
    file << endl;
    file << "--------------------------------------- " << ofGetTimestampString() << endl;
}

void ofxFileLoggerWithDateChannel::log(ofLogLevel level, const string& module, const string& message) {
    file << ofGetTimestampString() << " ";
    file << "[" << ofGetLogLevelName(level, true) << "] ";
    if (module != "") {
        file << module << ": ";
    }
    file << message << endl;
}

void ofxFileLoggerWithDateChannel::log(ofLogLevel level, const string& module, const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(level, module, format, args);
    va_end(args);
}

void ofxFileLoggerWithDateChannel::log(ofLogLevel level, const string& module, const char* format, va_list args) {
    file << "[" << ofGetLogLevelName(level, true) << "] ";
    if (module != "") {
        file << module << ": ";
    }
    file << ofVAArgsToString(format, args) << endl;
}
# ofxLoggerWithDateChannel

Custom logger channel. Output following log.

`2016-02-07-05-05-05-958 [verbose] Test Log`


## Usage

Replace openFrameworks official API `ofLogToConsole`, `ofLogToFile` to  `ofLogWithDateToConsole`, `ofLogWithDateToFile`.

```
ofLogWithDateToConsole();
ofLogWithDateToFile("of.log", true);
```


## License

MIT License

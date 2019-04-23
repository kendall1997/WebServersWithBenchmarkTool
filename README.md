# WebServersWithBenchmarkTool
WebServers that will implement concurrency, scheduling, real time scheduling in a docker environment that will be tested with our own benchmark tool, all written in C language.


## Content
- Benchmark: Contains the source code of the Benchmark and bclient tool, see its README to install dependencies, compile and run.

-mythreads: Contains the source code of the mypthreads library.
-mythreads_test: Contains the source code of the mypthreads library but named for be changed by pthread.
- WebServer: Contains the WebServer's source code.
- WebServer_mythread: Contains the WebServer's source code with mypthread library (Makefile in src C_Flags lpthread was removed and headers added to the files that uses Thread.
#ifndef _MainLoop_H    // Put these two lines at the top of your file.
#define _MainLoop_H    // (Use a suitable name, usually based on the file name.)

void loop(void) {
    http_rest_server.handleClient();
}

#endif // _MainLoop_H    // Put this line at the end of your file.
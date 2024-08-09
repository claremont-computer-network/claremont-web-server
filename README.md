# claremont-web-server
Claremont Web Server (CWS) is an open source web server software that the Claremont Computer Network uses for its web infrastructure. CWS is one of many services used inside Claremont's ecosystem for website hosting.

**CWS** currently is used to host the following:

- **tesfaasmara.com**
- **ourplaceprod.com**
- A database for the **Pomona Research in Mathematic Experience**


### How to Use:

1. **Build the program:**
   ```bash
   make build
   ```
   This will compile `cws.c` into the executable `cws`.

2. **Run the program with `sudo`:**
   ```bash
   make run
   ```
   This will first build the program (if it hasn't been built yet) and then execute `sudo ./cws`.

3. **Clean the directory:**
   ```bash
   make clean
   ```
   This will remove the `cws` executable.

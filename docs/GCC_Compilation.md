If you were to manually perform all the steps that CMake handles for you in the `CMakeLists.txt` file, here is how you could accomplish each task using `g++` commands directly.

### 1. **Compiling the Shared Library `librender.so`**

The first step is to compile the `librender.cpp` file into a **shared library** (`librender.so`), and for that, you need to use `-fPIC` (Position Independent Code) and `-shared`.

```bash
g++ -fPIC -shared -o librender.so librender.cpp
```

- `-fPIC`: Ensures the code can be loaded at any memory location, which is required for shared libraries.
- `-shared`: Tells the compiler to create a shared object (`.so`) file.

### 2. **Compiling the Shared Library `libplugin.so`**

Similarly, you need to compile the `libplugin.cpp` file into another shared library (`libplugin.so`).

```bash
g++ -fPIC -shared -o libplugin.so libplugin.cpp
```

This creates `libplugin.so` that can be dynamically loaded at runtime.

### 3. **Compiling the Main Program and Linking `librender.so`**

Next, you compile the `main.cpp` file and **dynamically link** it with the `librender.so` shared library. The `-L.` flag specifies the current directory as the location to search for libraries, and the `-lrender` flag tells the compiler to link against `librender.so`.

```bash
g++ -o game_engine main.cpp -L. -lrender -ldl
```

- `-L.`: Specifies that the linker should look for shared libraries in the current directory (`.`).
- `-lrender`: Links the `librender.so` shared library. The `l` flag automatically looks for `lib<name>.so`, so `-lrender` links to `librender.so`.
- `-ldl`: Links the dynamic loading library (`dlopen`, `dlsym`), required for dynamically loading `libplugin.so`.

### 4. **Setting the `RPATH` Using `chrpath` (Optional)**

In CMake, we use the `INSTALL_RPATH` property to ensure that the executable can find the shared libraries in the same directory. To achieve this on the command line, you can use `chrpath` or `patchelf` to modify the `RPATH` of the executable so that it looks for shared libraries in its own directory (`$ORIGIN`).

For example, using `chrpath`:

```bash
chrpath -r '$ORIGIN' game_engine
```

This modifies the `RPATH` of the `game_engine` executable to `$ORIGIN`, which tells it to look for the `librender.so` and `libplugin.so` libraries in the directory where the executable resides.

**Note**: You can also set the `RPATH` at link time using the `-Wl,-rpath` option:

```bash
g++ -o game_engine main.cpp -L. -lrender -ldl -Wl,-rpath,'$ORIGIN'
```

This tells the linker to set the `RPATH` directly during compilation. The `$ORIGIN` variable is replaced by the actual path where the executable resides when it is run.

### 5. **Summary of Commands**

Here’s a step-by-step list of all the commands that CMake automates:

1. **Compile `librender.so` (Shared Library)**:
   ```bash
   g++ -fPIC -shared -o librender.so librender.cpp
   ```

2. **Compile `libplugin.so` (Shared Library)**:
   ```bash
   g++ -fPIC -shared -o libplugin.so libplugin.cpp
   ```

3. **Compile `game_engine` (Main Executable) and Link with `librender.so`**:
   ```bash
   g++ -o game_engine main.cpp -L. -lrender -ldl -Wl,-rpath,'$ORIGIN'
   ```

4. **(Optional) Modify the `RPATH` Using `chrpath` or `patchelf`**:
   ```bash
   chrpath -r '$ORIGIN' game_engine
   ```

### **Conclusion**

By using these commands, you manually replicate what CMake does behind the scenes. CMake simplifies the build process, especially for larger projects, but understanding how to do these steps manually with `g++` is important for debugging or setting up simpler projects without CMake.

Let me know if you need further clarification or help with any specific part of the process!

## Optional: Library Path

**Option 1**: Using `LD_LIBRARY_PATH`

```bash
g++ -fPIC -shared -o librender.so librender.cpp
g++ -fPIC -shared -o libplugin.so libplugin.cpp
g++ -o game_engine main.cpp -L. -lrender -ldl

# Set LD_LIBRARY_PATH to the current directory and run the executable
LD_LIBRARY_PATH=. ./game_engine
```

**Option 2**: Using `RPATH` 

```bash
g++ -fPIC -shared -o librender.so librender.cpp
g++ -fPIC -shared -o libplugin.so libplugin.cpp
g++ -o game_engine main.cpp -L. -lrender -ldl -Wl,-rpath,'$ORIGIN'

# No need to set LD_LIBRARY_PATH, just run the executable
./game_engine
```


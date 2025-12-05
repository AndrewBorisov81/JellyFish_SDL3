Build project

// Ninja
mkdir build-ninja
cd build-ninja
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

// Unix
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
# JellyFish_SDL3

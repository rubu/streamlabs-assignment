# Layout #

- `electron-quick-start` - folder containing the electron quick start sample plus the added changes
- `obs-studio` - submodule for obs-studio
- `obs-studio-build` - out of tree build of obs-studio
- `obs-studio-dependencies` - contents of the dependencies2019.zip (https://obsproject.com/downloads/dependencies2019.zip) for obs build on windows
- `obs-studio-install` - placoholder folder for installation of the `obs-studio` build
- `streamlabs-assignment` - contains solution/project that references the `twitch-addon` project and also contains the relevant html/js files so that all work can be done inside visual studio
- `twitch-addon` - node native module that contains all the twitch streaming related functionality

# Setup #

1. download the obs dependencies from https://obsproject.com/downloads/dependencies2019.zip and extract to obs-studio-dependencies (you should end up with having win64/win32 directories under obs-studio-dependencies)
2. there is a pre configured visual studio code task `configure lib-obs build (windows/x64)` to configure the obs build, run that and after that run `build & install configured lib-obs`, these two steps should produce an obs build in `obs-studio-install`
3. run `configure twitch-addon (windows/x64/debug)` task to generate the project for the node addon
4. open the streamlabs-assignment.vcxproj and debug the `twich-addon` project

# Weird issues that took time #

1. what is the proper way to bundle stuff with cmake-js - does it support install command, can the build .node file be depoyled to the electron-quick-start folder in a nice way?
2. what is the best way for debugging under visual studio - currently there is some visual studio relevant stuff in CMakeLists.txt under twitch-addon which effectively just attempts to debug npm start (but debbing cmd really does not seem the proper way), eventually just put a non cmake generated visual studio sln/vcproj in the `streamlabs-assignment` which references the `twitch-addon` project
3. what is the proper way to work around library search paths without proper bundling while debugging? I added the `obs-studio-install/bin/64bit` to to path in visual studio with merge environment, but that again seems like a big hack, but as soon as the dynamic dependencies come into play `npm run start` also seems to fail

# Some general thoughts on electron vs cef directly
1. much more robust visual studio workflow - the main cef process + all the subprocesses (renderer/gpu/...) can be debugged directly, it is easy to understand what is going wrong if something is not working (in comparison here, it took time to understand which dlls and why are not loaded)
2. adding a reactive frontend seems easier - in cef scheme/resource handlers can be used to serve assets from disk where they would be watched/genereated by vue/react/something (and bundled inside the binary in release mode) where in this case w/o konwledge of electron it is not exactly clear how to change and hot reload the frontend while the process is running
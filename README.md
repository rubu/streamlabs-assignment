# Layout #

- `electron-quick-start` - folder containing the electron quick start sample plus the added changes
- `obs-studio` - submodule for obs-studio
- `obs-studio-build` - out of tree build of obs-studio
- `obs-studio-dependencies` - contents of the dependencies2019.zip (https://obsproject.com/downloads/dependencies2019.zip) for obs build on windows
- `obs-studio-install` - placoholder folder for installation of the `obs-studio` build
- `twitch-module` - node native module that contains all the twitch streaming related functionality

# Setup #

1. download the obs dependencies from https://obsproject.com/downloads/dependencies2019.zip and extract to obs-studio-dependencies (you should end up with having win64/win32 directories under obs-studio-dependencies)
2. there is a pre configured visual studio code task `configure lib-obs build (windows/x64)` to configure the obs build, run that and after that run `build & install configured lib-obs`, these two steps should produce an obs build in `obs-studio-install`

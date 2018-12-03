set BUILD_DIR=vc12x64-MD_Build

if exist %BUILD_DIR% (
  :remove_dir
  rmdir /S /Q %BUILD_DIR%
  if exist %BUILD_DIR% (
    echo "Cannot remove %BUILD_DIR%."
    goto remove_dir
  )
)
if not exist %BUILD_DIR% (
  mkdir %BUILD_DIR%
)

set INSTALL_DIR=D:\INSTALL\RT-vc12x64-MD
set STATIC_RUNTIME=OFF

cd %BUILD_DIR%
cmake -G "Visual Studio 12 Win64" .. -DCMAKE_INSTALL_PREFIX="%INSTALL_DIR%" -DMSVC_STATIC_RUNTIME=%STATIC_RUNTIME%

set CONFIG_TYPE=Release
cmake --build . --config %CONFIG_TYPE%

cd ..
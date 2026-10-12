@echo off
if not exist build mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config RELEASE
if errorlevel 1 (
    echo Sorry, error :(
    exit /b 1
)    
cls
echo =========================                                                                                                                                                                                                                                                            
echo      SUCESS!!!!!!!
echo      GOOD WORK :)
echo =========================
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    

pause

@echo off


xcopy Bin_Original Src\_Debug /E /I /Y
xcopy Bin_Original Src\_Release /E /I /Y
xcopy Bin_Original Src\_ReleaseSingleExe /E /I /Y
xcopy Bin_Original Src\_Shipping /E /I /Y
xcopy Bin_Original Src\_ShippingSingleExe /E /I /Y

mklink /j /D "Src\Data\" Data
mklink /j /D "Src\Localization\" Localization
mklink /j /D  "Src\Profiles\" Profiles

pause()
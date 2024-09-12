cd ../Bin
:"../Src/_Debug/H6_EditorC.exe" import -t Skeleton.skins Skeleton.animations StaticMesh
:"../Src/_Debug/H6_EditorC.exe" import Hero/_.SKEL.xdb
:"../Src/_Debug/H6_EditorC.exe" import Hero/_.SKEL.xdb -f=animations
:""../Src/_Debug/H6_EditorC.exe" import Hero/_.SKEL.xdb -f=skins
"../Src/_Debug/H6_EditorC.exe" %1 %2 %3 %4
pause

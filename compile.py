# -*- coding: utf-8 -*-
"""

"""

from __future__ import division
from __future__ import print_function
from __future__ import absolute_import

__author__ = "timmyliang"
__email__ = "820472580@qq.com"
__date__ = "2022-07-15 15:24:38"


import json
import os
import glob
import subprocess

DIR = os.path.dirname(os.path.abspath(__file__))

program = os.environ["ProgramData"]
data_path = os.path.join(
    program, "Epic", "UnrealEngineLauncher", "LauncherInstalled.dat"
)


def main():
    with open(data_path, "r") as rf:
        ue_data = json.load(rf)

    for uproject in glob.iglob(os.path.join(DIR, "*.uproject")):
        # project_name = os.path.basename(os.path.splitext(uproject)[0])
        with open(uproject, "r") as rf:
            project_data = json.load(rf)

        project_version = project_data.get("EngineAssociation")

        for app in ue_data.get("InstallationList", []):
            ue_location = app.get("InstallLocation")
            app_name = app.get("ArtifactId")
            version = app_name.split("_")[-1]
            if version == project_version:
                break
        
        print(ue_location)
        UBT = os.path.join(ue_location, "Engine", "Binaries", "DotNET", "UnrealBuildTool.exe")
        command = " ".join([UBT,'Development','Win64','-Project="{proj}"'.format(proj=uproject),'-TargetType=Editor' , "-Progress", "-NoEngineChanges"])
        print(command)
        subprocess.run(command)
        
    
# D:/EpicGames/UE_4.27/Engine/Binaries/DotNET/UnrealBuildTool.exe Development Win64 -Project="D:/EpicGames/Unreal_Playground/Unreal_Playground.uproject" -TargetType=Editor -Progress -NoEngineChanges -NoHotReloadFromIDE
# Engine/Binaries/DotNET/UnrealBuildTool.exe  -projectfiles -project="D:/EpicGames/test_plugin/test_plugin.uproject" -game -engine -progress 

if __name__ == "__main__":
    main()

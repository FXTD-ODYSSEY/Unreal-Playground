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
import logging
import argparse
import signal

signal.signal(signal.SIGINT, signal.SIG_DFL)

logging.basicConfig(level=logging.INFO)


DIR = os.path.dirname(os.path.abspath(__file__))

program = os.environ["ProgramData"]
data_path = os.path.join(
    program, "Epic", "UnrealEngineLauncher", "LauncherInstalled.dat"
)


def get_ue_location():
    with open(data_path, "r") as rf:
        ue_data = json.load(rf)

    for uproject in glob.iglob(os.path.join(DIR, "*.uproject")):
        with open(uproject, "r") as rf:
            project_data = json.load(rf)

        project_version = project_data.get("EngineAssociation")

        for app in ue_data.get("InstallationList", []):
            ue_location = app.get("InstallLocation")
            app_name = app.get("ArtifactId")
            version = app_name.split("_")[-1]
            if version == project_version:
                return uproject, ue_location


def run_command(command, callback=None, *args, **kwargs):
    logging.info(command)
    if not callback:
        subprocess.run(command)
    else:
        callback(command, *args, **kwargs)


def main():
    collections = get_ue_location()
    if not collections:
        logging.error("No UE project or engine location found")
        return
    uproject, ue_location = collections

    UBT = os.path.join(
        ue_location, "Engine", "Binaries", "DotNET", "UnrealBuildTool.exe"
    )
    UE = os.path.join(ue_location, "Engine", "Binaries", "Win64", "UE4Editor.exe")

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-a",
        "--action",
        help="display a square of a given number",
        type=str,
        default="",
    )

    args = parser.parse_args()
    action = args.action.lower()

    compile_command = " ".join(
        [
            UBT,
            "Development",
            "Win64",
            '-Project="{proj}"'.format(proj=uproject),
            "-TargetType=Editor",
            "-Progress",
            "-NoEngineChanges",
        ]
    )

    if action in ("generate_project", "gp"):
        run_command(
            " ".join(
                [
                    UBT,
                    "-projectfiles",
                    '-Project="{proj}"'.format(proj=uproject),
                    "-game",
                    "-engine",
                    "-progress",
                ]
            )
        )
    elif action in ("launch_project", "lp"):
        run_command(
            " ".join([UE, uproject, "-skipcompile"]),
            subprocess.Popen,
        )
    elif action in ("compile_project", "cp"):
        run_command(compile_command)
    else:
        run_command(compile_command)


# D:/EpicGames/UE_4.27/Engine/Binaries/DotNET/UnrealBuildTool.exe Development Win64 -Project="D:/EpicGames/Unreal_Playground/Unreal_Playground.uproject" -TargetType=Editor -Progress -NoEngineChanges -NoHotReloadFromIDE
# Engine/Binaries/DotNET/UnrealBuildTool.exe  -projectfiles -project="D:/EpicGames/test_plugin/test_plugin.uproject" -game -engine -progress

if __name__ == "__main__":
    main()

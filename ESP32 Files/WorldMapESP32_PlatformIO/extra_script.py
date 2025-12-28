Import("env")
from subprocess import call
from os import path

def upload_fs(source, target, env):
    upload_cmd = "pio run -t uploadfs -e " + env["PIOENV"]
    print("Uploading filesystem using: " + upload_cmd)
    call(upload_cmd, shell=True)

env.AddPreAction("uploadfs", upload_fs)

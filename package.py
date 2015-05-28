# coding=UTF-8

#!/usr/bin/python 

'''
文件夹结构 --zip
            animate
            unzip.py
            release
'''

import os, sys, zipfile
import shutil
import commands

# Config
dir = "equip"
output = "output"


def texturePacker(floder, oriName):
    '''
    打包图片
    '''
    target = "../" + floder + "/"

    #pwd
    #--content-protection 64baaa7a545a4eb7a90f7a452a703f13

    ##打包 atlas
    cmd = "TexturePacker --size-constraints NPOT --force-squared  --multipack --force-word-aligned --algorithm MaxRects --premultiply-alpha --format spine --opt RGBA4444 --dither-atkinson-alpha  --data " + target + oriName +  ".atlas --texture-format png --sheet " + target + oriName + ".png "  + "./"
    #cmd = "TexturePacker --size-constraints NPOT --force-squared --content-protection 64baaa7a545a4eb7a90f7a452a703f13 --multipack --force-word-aligned --algorithm MaxRects --reduce-border-artifacts --format cocos2d --opt RGBA4444 --dither-fs-alpha --data " + target + "animate.plist --texture-format pvr2ccz --sheet " + target + "animate.pvr.ccz " + target + "texture/"


    print commands.getoutput(cmd)
    print "-------" + oriName + " is success-----"


def run():


    nameConfig = {"horse": ["ma-bz", "ma-jiao-q", "ma-dt-q", "ma-xt-q", "ma-pg", "ma-yao", "ma-xiong", "ma-jiao-h", "ma-dt-h", "ma-xt-h", "ma-wb-s", "ma-tou", "ma-jiao-h-01", "ma-dt-h-01", "ma-xt-h-01", "ma-jiao-q-01", "ma-dt-q-01", "ma-xt-q-01"], 
    "helmet":["tou-tk", "tou-tk-s", "tou-tf-r", "tou-tf-l", "tou-tk-h"], 
    "armour":["db-r-s", "xb-r", "yd", "qz-r", "qz-l", "qz-m", "xt-l", "dt-r", "yao-q", "xiong", "bozi", "pg", "yao", "shou-l", "shou-r", "xb-l", "db-l-s", "db-l", "pf", "xiong-q"],
    "weapon":["wq-r", "wq-l"],
    "face": ["tou"],
    "face1": ["tou1"],
    "face2": ["tou2"],
    "face3": ["tou3"],
    "face4": ["tou4"],
    "face5": ["tou5"],
    "face6": ["tou6"],
    "face7": ["tou7"],
    "face8": ["tou8"],
    "face9": ["tou9"]
    }

    list = os.listdir(dir)

    if os.path.exists(output):
        shutil.rmtree(output)
        os.mkdir(output)


    for l in list:
        tf = os.path.join(dir, l)

        if os.path.isdir(tf):
            #os.chdir(tf)

            #pngList = os.listdir(os.getcwd())
            for (key , value) in nameConfig.items():

                print key, value

                tmp = os.path.join(output, "tmp")
                if os.path.exists(tmp) == False:
                    os.mkdir(tmp)

                for e in value :
                    copyFile = os.path.join(os.getcwd(), tf,  e + ".png")
                    if os.path.exists(copyFile):
                        shutil.copy(copyFile, tmp)


                tmpLen = len(os.listdir(tmp))
                os.chdir(os.path.join(output, "tmp"))

                #print("HHHHHHH:" + len(os.listdir(tmp)))
                if  tmpLen > 0:
                    texturePacker(l, key)               

                os.chdir("../../")
                shutil.rmtree(tmp)

            

    return

#main fun
run()

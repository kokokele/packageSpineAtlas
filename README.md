`动画播放时有时会出出现回到了旧的皮肤文件的的现象,这时需要删动作json里animate下的脏数据.`
`skeleton.html 工具重新生成即可. data.js就是需要更换的动作数据. 生成后的数据拷贝到之前的动作数据即可.`

# packageSpineAtlas

- 代码主要解决spine不能单独更换外部图片换装的问题。
- 将图片打包成atlas格式的文件后，就可以使用接口单独更换spine的皮肤了。
- package.py 用于批量打包atlas使用，里面的配置可以根据自己需求配置。


# 使用说明:

### 步骤1

 将 ChangeAttachmentForSpine.h 导入到 项目Classes下 lua_module_register.h 中

```c++
#include "ChangeAttachmentForSpine.h"

static int lua_module_register(lua_State* L)
{
    //Dont' change the module register order unless you know what your are doing
    register_cocosdenshion_module(L);
    register_network_module(L);
    register_cocosbuilder_module(L);
    register_cocostudio_module(L);
    register_ui_moudle(L);
    register_extension_module(L);
    register_spine_module(L);
    register_cocos3d_module(L);
    register_audioengine_module(L);
    
    register_extendsToLua_module(L);
    return 1;
}
```


### 步骤2

```lua
local sd = sp.SkeletonAnimation:create("animate/hero/skeleton.json", "animate/hero/skeleton.atlas", 0.9)

--1设置默认皮肤
sd:setSkin("lv0")

--2更换头盔相关挂件
sd:changeSkin("animate/hero/lv1/helmet.atlas")

--3替换单个当atlas文件名不对应的情况 "wq-r" 是挂件名称
sd:changeSkin("animate/hero/lv2/horse.atlas", "wq-r")

-- 4清空挂件 "wq-r"
sd:changeSkin("", "wq-r")
```




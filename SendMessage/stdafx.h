// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include <Windows.h>
#include <tchar.h>
#include "resource.h"

// manifest 清单指明 ComCtl32.dll 控件的版本为6.0 （XP风格控件）
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// 使用ComCtl32的控件
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib") // comctl32.lib  可以在项目属性 -> 链接器 -> 附件依赖项 里面添加

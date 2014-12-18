#Win32 Ln
`forked from malash/win32-ln`

Windows链接生成器，可用于生成符号链接、硬链接、目录联接。

###安装

运行 `src/install.reg` 导入注册表即可使用。

（注：默认路径为`C:\Program Files\win32ln\win32ln.exe`，如不同请手动修改install.reg文件）

###使用方法
为复制文件/目录，在目标目录中点击右键——粘贴为链接。

或者复制文件路径列表，如

    C:\3 3.txt
    C:\1.txt
    C:\2.txt
    C:\新建文件夹

再在目标目录中点击右键——粘贴为链接。
命令行参数 `-hard` : 创建目录的Junction，文件的Hard链接
（见 `src/install-hard.reg` ）

###推荐环境

Qt >= 5.0.0

Windows >= 7

编译器 =MSVC2010SP1

CLogin.h 为登陆界面头文件
CLogin.cpp 是对应的实现文件

CRegister.h 是注册界面头文件
CRegister.cpp 是相应的实现

然后编译器调成Release模式，x64 ，然后右击项目选择生成。(运行会报错，项目不能单独跑)
生成文件默认路径是在x64/Release下
那个MFCLibrary1.dll 就是生成的库，可以直接复制拿走用，
因为项目名是MFCLibrary1，我也没有改生成文件的命名，
所以默认是这个，复制后可以改名用，比如改成Login.dll，项目运行前要将项目属性->高级->使用
的字符集，改为多字符字符集



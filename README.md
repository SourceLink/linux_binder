
Test app for Binder, wrote by C language.
=======================================

test_client.c
test_server.c
service_manager.c

1. 在非Android系统:
----------------
##1.1 编译:
执行 make 即可
它会生成 service_manager,test_server,test_client

##1.2 测试:
./service_manager &  
./test_server &  
./test_client hello  
./test_client hello 100ask.taobao.com  
./test_client goodbye  
./test_client goodbye 100ask.taobao.com  

2. 在Android系统:
----------------
##2.1 编译  
把APP_0003_Binder_C_App整个目录放入Android源码目录里:  
. setenv  
lunch // 选择单板  
cd APP_0003_Binder_C_App  
mmm .  // 它会生成 service_manager_my,test_server,test_client  
  
##2.2 测试:  
// Android系统中已经有service_manager, 所以不要再次执行它  
./test_server &  
./test_client hello  
./test_client hello 100ask.taobao.com  
./test_client goodbye  
./test_client goodbye 100ask.taobao.com  
  

本文件对server端的源代码文件进行了相关的解析与介绍，server端相关代码按照功能划分，主要分为3个部分。

（1）微服务程序编译：
Makefile：顶层makefile，进入所有需要构建的文件夹，调用对应子文件夹下的makefile进行构建和删除操作。
bin：编译完成后自动将程序的可执行文件复制到该目录下。
common：系统共用编译源文件（.cpp/.cc）
include：系统共用编译头文件（.h）

register：注册微服务源代码。
login：登录微服务源代码。
admin：管理员微服务源代码。
user：普通用户微服务源代码。
stationer：站点人员微服务源代码。

以上5个微服务子文件夹下有各自的Makefile和protos文件夹，功能如下：
protos：存放本路径下所使用的protocol buffers协议文件。
makefile：主要有系统版本自检、预处理构建、正式构建和删除模块组成。

（2）测试程序
init_sql：自动化构建测试数据的脚本，在测试时将生成的init_create.sql和init_insert.sql文件导入MySQL数据库中执行。
benchmark_test：基于以上模拟的测试数据，进行大量数据单元测试。在该文件夹中同样有Makefile和protos文件夹，具体内容同（1）中所示。

（3）镜像制作
lib：存放制作微服务镜像时需要导入的库文件。
kube_cluster：存放需要部署在kubernetes集群中的.yaml配置文件。
Dockerfile_*：共有5个文件，分别对应文件名相关的微服务，通过执行该文件制作微服务镜像。

/*创建镜像并push到内网仓*/
docker build -f ./Dockerfile_myadmin -t registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:admin .
docker build -f ./Dockerfile_mylogin -t registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:login .
docker build -f ./Dockerfile_myregister -t registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:register .
docker build -f ./Dockerfile_mystationer -t registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:stationer .
docker build -f ./Dockerfile_myuser -t registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:user .

docker push registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:admin
docker push registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:login
docker push registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:register
docker push registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:stationer
docker push registry.cn-hangzhou.aliyuncs.com/xpf_images/my_log_system:user

